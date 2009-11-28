/* pkd-source-simple.h
 * 
 * Copyright (C) 2009 Christian Hergert
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PKD_SOURCE_SIMPLE_H__
#define __PKD_SOURCE_SIMPLE_H__

#include "pkd-sample.h"
#include "pkd-source.h"

G_BEGIN_DECLS

#define PKD_TYPE_SOURCE_SIMPLE              (pkd_source_simple_get_type ())
#define PKD_SOURCE_SIMPLE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), PKD_TYPE_SOURCE_SIMPLE, PkdSourceSimple))
#define PKD_SOURCE_SIMPLE_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST ((obj), PKD_TYPE_SOURCE_SIMPLE, PkdSourceSimple const))
#define PKD_SOURCE_SIMPLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass),  PKD_TYPE_SOURCE_SIMPLE, PkdSourceSimpleClass))
#define PKD_IS_SOURCE_SIMPLE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PKD_TYPE_SOURCE_SIMPLE))
#define PKD_IS_SOURCE_SIMPLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass),  PKD_TYPE_SOURCE_SIMPLE))
#define PKD_SOURCE_SIMPLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj),  PKD_TYPE_SOURCE_SIMPLE, PkdSourceSimpleClass))

typedef struct _PkdSourceSimple        PkdSourceSimple;
typedef struct _PkdSourceSimpleClass   PkdSourceSimpleClass;
typedef struct _PkdSourceSimplePrivate PkdSourceSimplePrivate;

typedef PkdSample* (*PkdSourceSimpleSampleFunc) (PkdSourceSimple  *source,
                                                 gpointer          user_data,
                                                 GError          **error);

struct _PkdSourceSimple
{
	PkdSource parent;

	/*< private >*/
	PkdSourceSimplePrivate *priv;
};

struct _PkdSourceSimpleClass
{
	PkdSourceClass parent_class;
};

GType        pkd_source_simple_get_type        (void) G_GNUC_CONST;
PkdSource*   pkd_source_simple_new             (void);
void         pkd_source_simple_set_sample_func (PkdSourceSimple           *source,
                                                PkdSourceSimpleSampleFunc  sample_func,
                                                gpointer                   user_data,
                                                GDestroyNotify             notify);

G_END_DECLS

#endif /* __PKD_SOURCE_SIMPLE_H__ */