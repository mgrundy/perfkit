/* pk-manifest.c
 *
 * Copyright (C) 2010 Christian Hergert
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <egg-buffer.h>
#include <egg-time.h>

#include "pk-manifest.h"
#include "pk-log.h"
#include "pk-util.h"


typedef struct _PkManifestReal PkManifestReal;


static gboolean decode (PkManifest *manifest,
                        EggBuffer  *buffer);


#define MANIFEST_MAGIC 0x0BADFACE
#define PK_IS_MANIFEST(_m) \
    ((_m) && (((PkManifestReal *)(_m))->magic == MANIFEST_MAGIC))


struct _PkManifestReal
{
	gdouble         time;       /* Must stay in sync with PkManifest */
	guint32         magic;      /* Magic bytes to check instance */
	volatile gint   ref_count;  /* The structures reference count */
	struct timespec ts;         /* Timespec matching time field */
	PkResolution    resolution; /* Resolution of sample time precision */
	gint            source_id;  /* The source the manifest belongs to */
	gint            n_rows;     /* Number of rows in manifest (Delete?) */
	GArray         *rows;       /* Actual rows */
};

typedef struct
{
	gint   id;
	GType  type;
	GQuark name;
} PkManifestRow;

static void
pk_manifest_destroy (PkManifest *manifest) /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;

	g_return_if_fail(manifest != NULL);

	ENTRY;

	/* free row array */
	g_array_unref(real->rows);

	/* mark fields as canaries */
	real->rows = NULL;
	real->source_id = -1;
	EXIT;
}

static PkManifest*
pk_manifest_new (void)
{
	PkManifestReal *real;

	real = g_slice_new0(PkManifestReal);
	real->magic = MANIFEST_MAGIC;
	real->ref_count = 1;
	real->rows = g_array_new(FALSE, FALSE, sizeof(PkManifestRow));
	return (PkManifest *)real;
}

gint
pk_manifest_get_source_id (PkManifest *manifest) /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	g_return_val_if_fail(PK_IS_MANIFEST(real), -1);
	return real->source_id;
}

gint
pk_manifest_get_row_id (PkManifest  *manifest,
                        const gchar *name)
{
	GQuark quark;

	g_return_val_if_fail(PK_IS_MANIFEST(manifest), -1);
	g_return_val_if_fail(name != NULL, -1);

	if (!(quark = g_quark_try_string(name))) {
		return -1;
	}
	return pk_manifest_get_row_id_from_quark(manifest, quark);
}


gint
pk_manifest_get_row_id_from_quark (PkManifest  *manifest,
                                   GQuark       quark)
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	PkManifestRow *row;
	gint i;

	g_return_val_if_fail(PK_IS_MANIFEST(real), -1);
	g_return_val_if_fail(real->rows != NULL, -1);
	g_return_val_if_fail(quark > 0, -1);

	for (i = 0; i < real->rows->len; i++) {
		row = &g_array_index(real->rows, PkManifestRow, i);
		if (quark == row->name) {
			return i + 1;
		}
	}

	return -1;
}


/**
 * pk_manifest_new_from_data:
 * @data: The manifest data.
 * @length: The length of data.
 *
 * Creates a new instance of #PkManifest from a buffer of data.
 *
 * Returns: the newly created #PkManifest instance.
 *
 * Side effects: None.
 */
PkManifest*
pk_manifest_new_from_data (const guint8 *data,   /* IN */
                           gsize         length) /* IN */
{
	PkManifest *manifest;
	EggBuffer *buffer;

	ENTRY;
	manifest = pk_manifest_new();
	buffer = egg_buffer_new_from_data(data, length);
	if (!decode(manifest, buffer)) {
		GOTO(error);
	}
	egg_buffer_unref(buffer);
	RETURN(manifest);

  error:
	egg_buffer_unref(buffer);
	pk_manifest_unref(manifest);
	RETURN(NULL);
}

/**
 * pk_manifest_ref:
 * manifest: A #PkManifest
 *
 * Atomically increments the reference count of @manifest by one.
 *
 * Returns: The @manifest pointer with its reference count incremented.
 *
 * Side effects: None.
 */
PkManifest*
pk_manifest_ref (PkManifest *manifest) /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;

	g_return_val_if_fail(PK_IS_MANIFEST(real), NULL);
	g_return_val_if_fail(real->ref_count > 0, NULL);

	g_atomic_int_inc(&real->ref_count);
	return manifest;
}

/**
 * pk_manifest_unref:
 * manifest: A #PkManifest
 *
 * Atomically decrements the reference count of @manifest by one.
 * When the reference count reaches zero, the structures resources as well as
 * the structure are freed.
 *
 * Returns: The @manifest pointer with its reference count incremented.
 *
 * Side effects: None.
 */
void
pk_manifest_unref (PkManifest *manifest)
{
	PkManifestReal *real = (PkManifestReal *)manifest;

	g_return_if_fail(PK_IS_MANIFEST(real));
	g_return_if_fail(real->ref_count > 0);

	if (g_atomic_int_dec_and_test(&real->ref_count)) {
		pk_manifest_destroy(manifest);
		g_slice_free(PkManifestReal, real);
	}
}

/**
 * pk_manifest_get_resolution:
 * @manifest: A #PkManifest.
 *
 * Retrieves the time resolution of the manifest here-forth.  This can be
 * used for bucketing of samples.
 *
 * Returns: The #PkResolution of the manifest.
 *
 * Side effects: None.
 */
PkResolution
pk_manifest_get_resolution (PkManifest *manifest) /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	g_return_val_if_fail(PK_IS_MANIFEST(real), 0);
	return real->resolution;
}

/**
 * pk_manifest_get_n_rows:
 * @manifest: A #PkManifest.
 *
 * Retrieves the number of rows in the manifest.
 *
 * Returns: The number of rows.
 *
 * Side effects: None.
 */
gint
pk_manifest_get_n_rows (PkManifest *manifest) /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	g_return_val_if_fail(PK_IS_MANIFEST(real), 0);
	return real->n_rows;
}

/**
 * pk_manifest_get_row_type:
 * @manifest: A #PkManifest.
 * @row: row number which starts from 1.
 *
 * Retrieves the #GType for the row content.
 *
 * Returns: A #GType.
 *
 * Side effects: None.
 */
GType
pk_manifest_get_row_type (PkManifest *manifest, /* IN */
                          gint        row)      /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;

	g_return_val_if_fail(PK_IS_MANIFEST(real), 0);
	g_return_val_if_fail(real->rows != NULL, G_TYPE_INVALID);
	g_return_val_if_fail(row > 0, G_TYPE_INVALID);
	g_return_val_if_fail(row <= real->n_rows, G_TYPE_INVALID);

	return g_array_index(real->rows, PkManifestRow, --row).type;
}

/**
 * pk_manifest_get_row_name:
 * @manifest: A #PkManifest.
 * @row: row number which starts from 1.
 *
 * Retrieves the name of a row.
 *
 * Returns:
 *
 * Side effects: None.
 */
const gchar*
pk_manifest_get_row_name (PkManifest *manifest, /* IN */
                          gint        row)      /* IN */
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	PkManifestRow *mrow;

	g_return_val_if_fail(PK_IS_MANIFEST(real), NULL);
	g_return_val_if_fail(row > 0, NULL);
	g_return_val_if_fail(row <= real->n_rows, NULL);

	mrow = &g_array_index(real->rows, PkManifestRow, row - 1);
	return g_quark_to_string(mrow->name);
}

/**
 * pk_manifest_get_timespec:
 * @manifest: A #PkManifest.
 * @ts: A struct timespec.
 *
 * Retrieves the struct timespec for with the manifest is authoritative.
 *
 * Returns: None.
 * Side effects: None.
 */
void
pk_manifest_get_timespec (PkManifest      *manifest, /* IN */
                          struct timespec *ts)       /* OUT */
{
	PkManifestReal *real = (PkManifestReal *)manifest;

	g_return_if_fail(PK_IS_MANIFEST(real));
	g_return_if_fail(ts != NULL);

	*ts = real->ts;
}

GType
pk_manifest_get_type (void)
{
	static GType type_id = 0;
	GType _type_id;

	if (g_once_init_enter((gsize *)&type_id)) {
		_type_id =
			g_boxed_type_register_static("PkManifest",
			                             (GBoxedCopyFunc)pk_manifest_ref,
			                             (GBoxedFreeFunc)pk_manifest_unref);
		g_once_init_leave((gsize *)&type_id, _type_id);
	}
	return type_id;
}

static gint
sort_func (gconstpointer a,
           gconstpointer b)
{
	const PkManifestRow *row_a = a,
	                    *row_b = b;

	return (row_a->id == row_b->id) ? 0 : row_a->id - row_b->id;
}

static gboolean
decode (PkManifest *manifest,
        EggBuffer  *buffer)
{
	PkManifestReal *real = (PkManifestReal *)manifest;
	guint field, tag, u32, len;
	guint64 u64;
	gsize end;
	gint i;

	g_return_val_if_fail(PK_IS_MANIFEST(real), FALSE);
	g_return_val_if_fail(buffer != NULL, FALSE);

	/* timestamp */
	if (!egg_buffer_read_tag(buffer, &field, &tag)) {
		return FALSE;
	}
	if (tag != EGG_BUFFER_UINT64 || field != 1) {
		return FALSE;
	}
	if (!egg_buffer_read_uint64(buffer, &u64)) {
		return FALSE;
	}
	timespec_from_usec(&real->ts, u64);
	real->time = real->ts.tv_sec
	           + real->ts.tv_nsec / 1000000000.0;

	/* resolution */
	if (!egg_buffer_read_tag(buffer, &field, &tag)) {
		return FALSE;
	}
	if (tag != EGG_BUFFER_UINT || field != 2) {
		return FALSE;
	}
	if (!egg_buffer_read_uint(buffer, &u32)) {
		return FALSE;
	}
	if (u32 > PK_RESOLUTION_HOUR) {
		return FALSE;
	}
	real->resolution = u32;

	/* source */
	if (!egg_buffer_read_tag(buffer, &field, &tag)) {
		return FALSE;
	}
	if (tag != EGG_BUFFER_UINT || field != 3) {
		return FALSE;
	}
	if (!egg_buffer_read_uint(buffer, &u32)) {
		return FALSE;
	}
	real->source_id = u32;

	/* columns */
	if (!egg_buffer_read_tag(buffer, &field, &tag)) {
		return FALSE;
	}
	if (tag != EGG_BUFFER_REPEATED || field != 4) {
		return FALSE;
	}

	/* len of data */
	if (!egg_buffer_read_uint(buffer, &len)) {
		return FALSE;
	}

	/* determine end of buffer */
	end = egg_buffer_get_pos(buffer) + len;

	/* get manifest rows */
	while (egg_buffer_get_pos(buffer) < end) {
		PkManifestRow row;
		gchar *name = NULL;
		guint row_id = 0;
		GType row_type = 0;

		/* row data length */
		if (!egg_buffer_read_uint(buffer, &u32)) {
			return FALSE;
		}

		/* row id */
		if (!egg_buffer_read_tag(buffer, &field, &tag)) {
			return FALSE;
		}
		if (field != 1 || tag != EGG_BUFFER_UINT) {
			return FALSE;
		}
		if (!egg_buffer_read_uint(buffer, &row_id)) {
			return FALSE;
		}

		/* row type */
		if (!egg_buffer_read_tag(buffer, &field, &tag)) {
			return FALSE;
		}
		if (field != 2 || tag != EGG_BUFFER_ENUM) {
			return FALSE;
		}
		if (!egg_buffer_read_uint(buffer, (guint *)&row_type)) {
			return FALSE;
		}

		/* row name */
		if (!egg_buffer_read_tag(buffer, &field, &tag)) {
			return FALSE;
		}
		if (field != 3 || tag != EGG_BUFFER_STRING) {
			return FALSE;
		}
		if (!egg_buffer_read_string(buffer, &name)) {
			return FALSE;
		}

		row.id = row_id;
		row.type = row_type;
		row.name = g_quark_from_string(name);

		g_array_append_val(real->rows, row);
		g_array_sort(real->rows, sort_func);
		real->n_rows++;

		g_free(name);
	}

	/* make sure all rows were sent */
	for (i = 0; i < real->n_rows; i++) {
		PkManifestRow *row;

		row = &g_array_index(real->rows, PkManifestRow, i);
		if (row->id != (i + 1)) {
			return FALSE;
		}
	}

	return TRUE;
}
