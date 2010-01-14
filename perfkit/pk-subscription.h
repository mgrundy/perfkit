/* pk-subscription.h
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

#if !defined (__PERFKIT_INSIDE__) && !defined (PERFKIT_COMPILATION)
#error "Only <perfkit/perfkit.h> can be included directly."
#endif

#ifndef __PK_SUBSCRIPTION_H__
#define __PK_SUBSCRIPTION_H__

#include <glib-object.h>

#include "pk-encoder.h"
#include "pk-manifest.h"

G_BEGIN_DECLS

#define PK_TYPE_SUBSCRIPTION            (pk_subscription_get_type())
#define PK_SUBSCRIPTION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PK_TYPE_SUBSCRIPTION, PkSubscription))
#define PK_SUBSCRIPTION_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), PK_TYPE_SUBSCRIPTION, PkSubscription const))
#define PK_SUBSCRIPTION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  PK_TYPE_SUBSCRIPTION, PkSubscriptionClass))
#define PK_IS_SUBSCRIPTION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PK_TYPE_SUBSCRIPTION))
#define PK_IS_SUBSCRIPTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  PK_TYPE_SUBSCRIPTION))
#define PK_SUBSCRIPTION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  PK_TYPE_SUBSCRIPTION, PkSubscriptionClass))

typedef struct _PkSubscription        PkSubscription;
typedef struct _PkSubscriptionClass   PkSubscriptionClass;
typedef struct _PkSubscriptionPrivate PkSubscriptionPrivate;

struct _PkSubscription
{
	GObject parent;

	/*< private >*/
	PkSubscriptionPrivate *priv;
};

struct _PkSubscriptionClass
{
	GObjectClass parent_class;
};

GType       pk_subscription_get_type      (void) G_GNUC_CONST;
PkEncoder*  pk_subscription_get_encoder   (PkSubscription *subscription);
PkManifest* pk_subscription_get_manifest  (PkSubscription *subscription);
gboolean    pk_subscription_enable        (PkSubscription *subscription, GError **error);
gboolean    pk_subscription_disable       (PkSubscription *subscription, GError **error);

G_END_DECLS

#endif /* __PK_SUBSCRIPTION_H__ */
