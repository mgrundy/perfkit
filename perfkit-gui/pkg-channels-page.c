/* pkg-channels-page.c
 *
 * Copyright (C) 2010 Christian Hergert <chris@dronelabs.com>
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

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib/gi18n.h>

#include "pkg-channels-page.h"
#include "pkg-path.h"
#include "pkg-log.h"

/**
 * SECTION:pkg-channels-page
 * @title: PkgChannelsPage
 * @short_description: 
 *
 * Section overview.
 */

G_DEFINE_TYPE(PkgChannelsPage, pkg_channels_page, GTK_TYPE_ALIGNMENT)

struct _PkgChannelsPagePrivate
{
	PkConnection *connection;
	GtkBuilder   *builder;
	GtkWidget    *container;
	GtkWidget    *channels;
	GtkWidget    *add;
	GtkWidget    *remove;
};

enum
{
	PROP_0,
	PROP_CONNECTION,
};

/**
 * pkg_channels_page_new:
 *
 * Creates a new instance of #PkgChannelsPage.
 *
 * Returns: the newly created instance of #PkgChannelsPage.
 * Side effects: None.
 */
GtkWidget*
pkg_channels_page_new (PkConnection *connection)
{
	GtkWidget *page;

	ENTRY;
	page = g_object_new(PKG_TYPE_CHANNELS_PAGE,
	                    "connection", connection,
	                    NULL);
	RETURN(page);
}

void
pkg_channels_page_reload (PkgChannelsPage *page)
{
	PkgChannelsPagePrivate *priv;

	g_return_if_fail(PKG_IS_CHANNELS_PAGE(page));

	ENTRY;
	priv = page->priv;
	EXIT;
}

static void
pkg_channels_page_add_channel_cb (PkConnection    *connection,
                                  GAsyncResult    *result,
                                  PkgChannelsPage *page)
{
	PkgChannelsPagePrivate *priv;
	GError *error = NULL;
	gint channel;

	g_return_if_fail(PK_IS_CONNECTION(connection));
	g_return_if_fail(G_IS_ASYNC_RESULT(result));
	g_return_if_fail(PKG_IS_CHANNELS_PAGE(page));

	ENTRY;
	priv = page->priv;
	if (!pk_connection_manager_add_channel_finish(priv->connection, result,
	                                              &channel, &error)) {
		WARNING(Channels, "Failed to add new channel: %s", error->message);
		pkg_util_dialog_warning(gtk_widget_get_toplevel(GTK_WIDGET(page)),
		                        "",
		                        _("There was an error adding the channel."),
		                        error->message,
		                        TRUE);
		g_error_free(error);
		GOTO(fail);
	}
	DEBUG(Channels, "Added channel %d to system.", channel);
  fail:
	EXIT;
}

static void
pkg_channels_page_add_clicked_cb (GtkWidget       *button,
                                  PkgChannelsPage *page)
{
	PkgChannelsPagePrivate *priv;

	g_return_if_fail(PKG_IS_CHANNELS_PAGE(page));

	ENTRY;
	priv = page->priv;
	pk_connection_manager_add_channel_async(
			priv->connection, NULL,
			(GAsyncReadyCallback)pkg_channels_page_add_channel_cb,
			page);
	EXIT;
}

static void
pkg_channels_page_remove_clicked_cb (GtkWidget       *button,
                                     PkgChannelsPage *page)
{
	g_return_if_fail(PKG_IS_CHANNELS_PAGE(page));
	DEBUG(Channels, "Remove channel");
}

static void
pkg_channels_page_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
	PkgChannelsPagePrivate *priv;

	ENTRY;
	priv = PKG_CHANNELS_PAGE(object)->priv;
	switch (prop_id) {
	CASE(PROP_CONNECTION);
		priv->connection = g_object_ref(g_value_get_object(value));
		BREAK;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
	EXIT;
}

static void
pkg_channels_page_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
	PkgChannelsPagePrivate *priv;

	ENTRY;
	priv = PKG_CHANNELS_PAGE(object)->priv;
	switch (prop_id) {
	CASE(PROP_CONNECTION);
		g_value_set_object(value, priv->connection);
		BREAK;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
	EXIT;
}

static void
pkg_channels_page_dispose (GObject *object)
{
	G_OBJECT_CLASS(pkg_channels_page_parent_class)->dispose(object);
}

static void
pkg_channels_page_finalize (GObject *object)
{
	G_OBJECT_CLASS(pkg_channels_page_parent_class)->finalize(object);
}

static void
pkg_channels_page_class_init (PkgChannelsPageClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS(klass);
	object_class->finalize = pkg_channels_page_finalize;
	object_class->dispose = pkg_channels_page_dispose;
	object_class->set_property = pkg_channels_page_set_property;
	object_class->get_property = pkg_channels_page_get_property;
	g_type_class_add_private(object_class, sizeof(PkgChannelsPagePrivate));

	g_object_class_install_property(object_class,
	                                PROP_CONNECTION,
	                                g_param_spec_object("connection",
	                                                    "Connection",
	                                                    "Connection",
	                                                    PK_TYPE_CONNECTION,
	                                                    G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

static void
pkg_channels_page_init (PkgChannelsPage *page)
{
	PkgChannelsPagePrivate *priv;
	gchar *path;

	ENTRY;
	page->priv = G_TYPE_INSTANCE_GET_PRIVATE(page,
	                                         PKG_TYPE_CHANNELS_PAGE,
	                                         PkgChannelsPagePrivate);
	priv = page->priv;

	path = pkg_path_for_data("ui", "pkg-channels-page.ui", NULL);
	priv->builder = gtk_builder_new();
	gtk_builder_add_from_file(priv->builder, path, NULL);

	#define EXTRACT_WIDGET(_n, _f)  \
		priv->_f = GTK_WIDGET(gtk_builder_get_object(priv->builder, _n))

	EXTRACT_WIDGET("channels-page", container);
	EXTRACT_WIDGET("channels", channels);
	EXTRACT_WIDGET("add", add);
	EXTRACT_WIDGET("remove", remove);

	gtk_widget_unparent(priv->container);
	gtk_container_add(GTK_CONTAINER(page), priv->container);

	g_signal_connect(priv->add,
	                 "clicked",
	                 G_CALLBACK(pkg_channels_page_add_clicked_cb),
	                 page);
	g_signal_connect(priv->remove,
	                 "clicked",
	                 G_CALLBACK(pkg_channels_page_remove_clicked_cb),
	                 page);

	EXIT;
}
