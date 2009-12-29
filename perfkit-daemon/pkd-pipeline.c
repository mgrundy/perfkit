/* pkd-pipeline.c
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>
#include <glib/gthread.h>

#include "pkd-config.h"
#include "pkd-pipeline.h"

static GMainLoop *loop = NULL;
static GPtrArray *listeners = NULL;
static GPtrArray *subscriptions = NULL;
static GList     *source_infos = NULL;
static GList     *sources = NULL;
static GList     *channels = NULL;
static GList     *encoder_infos = NULL;

G_LOCK_DEFINE(channels);
G_LOCK_DEFINE(listeners);
G_LOCK_DEFINE(source_infos);
G_LOCK_DEFINE(sources);
G_LOCK_DEFINE(subscriptions);
G_LOCK_DEFINE(encoder_infos);

extern void pkd_listener_source_info_added  (PkdListener *listener,
											PkdSourceInfo *source_info);
extern void pkd_listener_source_added       (PkdListener *listener,
											PkdSource *source);
extern void pkd_listener_channel_added      (PkdListener *listener,
											PkdChannel *channel);
extern void pkd_listener_subscription_added (PkdListener *listener,
											PkdSubscription *subscription);
extern void pkd_listener_encoder_info_added (PkdListener *listener,
                                            PkdEncoderInfo *encoder_info);

/**
 * pkd_pipeline_init:
 *
 * Initializes the pipeline subsystem.
 *
 * Side effects:
 *     The mainloop is initialized.
 */
void
pkd_pipeline_init (void)
{
	static gsize init = 0;

	if (g_once_init_enter(&init)) {
		g_message("Initializing pipeline.");
		loop = g_main_loop_new(NULL, FALSE);
		listeners = g_ptr_array_sized_new(4);
		subscriptions = g_ptr_array_sized_new(4);
		g_once_init_leave(&init, (gsize)loop);
	}
}

/**
 * pkd_pipeline_run:
 *
 * Runs the mainloop for the agent.  This method blocks until a call to
 * pkd_pipeline_quit() as been made.
 *
 * Side effects: None.
 */
void
pkd_pipeline_run (void)
{
	GError *error;
	gint i;

	g_return_if_fail(loop != NULL);

	if (listeners->len == 0) {
		g_message("No listeners configured! Exiting gracefully.");
		return;
	}

	g_message("Starting active listeners.");
	for (i = 0 ; i < listeners->len ; i++) {
		error = NULL;
		if (!pkd_listener_start(listeners->pdata[i], &error)) {
			g_warning("%s: %s",
			          g_type_name(G_TYPE_FROM_INSTANCE(listeners->pdata[i])),
			          error->message);
			g_error_free(error);
		} else {
			g_message("%s started.",
			          g_type_name(G_TYPE_FROM_INSTANCE(listeners->pdata[i])));
		}
	}

	g_message("Starting mainloop.");
	g_main_loop_run(loop);
}

/**
 * pkd_pipeline_quit:
 *
 * Quits the mainloop for the agent.  The blocked thread who called
 * pkd_pipeline_run() will resume execution.
 *
 * Side effects: The caller of pkd_pipeline_run() will resume.
 */
void
pkd_pipeline_quit (void)
{
	g_return_if_fail(loop != NULL);
	g_message("Stopping mainloop.");
	g_main_loop_quit(loop);
}

/**
 * pkd_pipeline_shutdown:
 *
 * Cleans up the process prior to exit.
 */
void
pkd_pipeline_shutdown (void)
{
	gint i;

	for (i = 0; i < listeners->len; i++) {
		(void)g_object_ref(listeners->pdata[i]);
		pkd_listener_stop(listeners->pdata[i]);
		g_object_unref(listeners->pdata[i]);
	}
}

/**
 * pkd_pipeline_add_source_info:
 * @source_info: A #PkdSourceInfo
 *
 * Adds a #PkdSourceInfo to the list of known source type descriptions.
 */
void
pkd_pipeline_add_source_info (PkdSourceInfo *source_info)
{
	g_return_if_fail(source_info != NULL);

	g_message("Registering %s source type.",
	          pkd_source_info_get_uid(source_info));

	G_LOCK(source_infos);
	source_infos = g_list_append(source_infos, g_object_ref(source_info));
	G_UNLOCK(source_infos);

	source_info = g_object_ref(source_info);
	g_ptr_array_foreach(listeners,
	                    (GFunc)pkd_listener_source_info_added,
	                    source_info);
	g_object_unref(source_info);
}

/**
 * pkd_pipeline_add_source:
 * @source: A #PkdSource
 *
 * Adds a #PkdSource to the list of known sources.
 */
void
pkd_pipeline_add_source (PkdSource *source)
{
	g_return_if_fail(PKD_IS_SOURCE(source));

	G_LOCK(sources);
	sources = g_list_append(sources, g_object_ref(source));
	G_UNLOCK(sources);

	source = g_object_ref(source);
	g_ptr_array_foreach(listeners,
	                    (GFunc)pkd_listener_source_added,
	                    source);
	g_object_unref(source);
}

/**
 * pkd_pipeline_add_channel:
 * @channel: A #PkdChannel
 *
 * Adds a #PkdChannel to the list of known channels.
 */
void
pkd_pipeline_add_channel (PkdChannel *channel)
{
	g_return_if_fail(PKD_IS_CHANNEL(channel));

	G_LOCK(channels);
	channels = g_list_append(channels, g_object_ref(channel));
	G_UNLOCK(channels);

	channel = g_object_ref(channel);
	g_ptr_array_foreach(listeners,
	                    (GFunc)pkd_listener_channel_added,
	                    channel);
	g_object_unref(channel);
}

/**
 * pkd_pipeline_add_listener:
 * @listener: A #PkdListener
 *
 * Add a listener to the pipeline.  This is typically called from the
 * "pkd_listener_register" symbol in a listener shared object.
 */
void
pkd_pipeline_add_listener (PkdListener *listener)
{
	g_return_if_fail(listeners != NULL);
	g_return_if_fail(PKD_IS_LISTENER(listener));

	G_LOCK(listeners);
	g_ptr_array_add(listeners, g_object_ref(listener));
	G_UNLOCK(listeners);
}

/**
 * pkd_pipeline_add_subscription:
 * @subscription: A #PkdSubscription
 *
 * Adds a subscription to the pipeline.  Listeners are notified of the
 * subscription creation.
 */
void
pkd_pipeline_add_subscription (PkdSubscription *subscription)
{
	g_return_if_fail(subscriptions != NULL);
	g_return_if_fail(subscription != NULL);

	G_LOCK(subscriptions);
	g_ptr_array_add(subscriptions, pkd_subscription_ref(subscription));
	G_UNLOCK(subscriptions);

	subscription = pkd_subscription_ref(subscription);
	g_ptr_array_foreach(listeners,
						(GFunc)pkd_listener_subscription_added,
						subscription);
	pkd_subscription_unref(subscription);
}

/**
 * pkd_pipeline_add_encoder_info:
 * @encoder_info: A #PkdEncoderInfo
 *
 * Adds a #PkdEncoderInfo to the pipeline.  Listeners are notified of the newly
 * available encoder.
 */
void
pkd_pipeline_add_encoder_info (PkdEncoderInfo *encoder_info)
{
	g_return_if_fail(PKD_IS_ENCODER_INFO(encoder_info));

	g_message("Registering %s encoder.",
	          pkd_encoder_info_get_uid(encoder_info));

	G_LOCK(encoder_infos);
	encoder_infos = g_list_append(encoder_infos, g_object_ref(encoder_info));
	G_UNLOCK(encoder_infos);

	encoder_info = g_object_ref(encoder_info);
	g_ptr_array_foreach(listeners,
	                    (GFunc)pkd_listener_encoder_info_added,
	                    encoder_info);
	g_object_unref(encoder_info);
}