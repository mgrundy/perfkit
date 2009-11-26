/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_pkd_channel_MARSHAL_H__
#define __dbus_glib_marshal_pkd_channel_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:BOXED,POINTER (/tmp/dbus-binding-tool-c-marshallers.MFFT3U:1) */
extern void dbus_glib_marshal_pkd_channel_BOOLEAN__BOXED_POINTER (GClosure     *closure,
                                                                  GValue       *return_value,
                                                                  guint         n_param_values,
                                                                  const GValue *param_values,
                                                                  gpointer      invocation_hint,
                                                                  gpointer      marshal_data);
void
dbus_glib_marshal_pkd_channel_BOOLEAN__BOXED_POINTER (GClosure     *closure,
                                                      GValue       *return_value G_GNUC_UNUSED,
                                                      guint         n_param_values,
                                                      const GValue *param_values,
                                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                                      gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_POINTER) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:UINT,POINTER (/tmp/dbus-binding-tool-c-marshallers.MFFT3U:2) */
extern void dbus_glib_marshal_pkd_channel_BOOLEAN__UINT_POINTER (GClosure     *closure,
                                                                 GValue       *return_value,
                                                                 guint         n_param_values,
                                                                 const GValue *param_values,
                                                                 gpointer      invocation_hint,
                                                                 gpointer      marshal_data);
void
dbus_glib_marshal_pkd_channel_BOOLEAN__UINT_POINTER (GClosure     *closure,
                                                     GValue       *return_value G_GNUC_UNUSED,
                                                     guint         n_param_values,
                                                     const GValue *param_values,
                                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                                     gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__UINT_POINTER) (gpointer     data1,
                                                          guint        arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     data2);
  register GMarshalFunc_BOOLEAN__UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_uint (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:POINTER (/tmp/dbus-binding-tool-c-marshallers.MFFT3U:3) */
extern void dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER (GClosure     *closure,
                                                            GValue       *return_value,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint,
                                                            gpointer      marshal_data);
void
dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER (GClosure     *closure,
                                                GValue       *return_value G_GNUC_UNUSED,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint G_GNUC_UNUSED,
                                                gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__POINTER) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gpointer     data2);
  register GMarshalFunc_BOOLEAN__POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:POINTER,POINTER (/tmp/dbus-binding-tool-c-marshallers.MFFT3U:4) */
extern void dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER (GClosure     *closure,
                                                                    GValue       *return_value,
                                                                    guint         n_param_values,
                                                                    const GValue *param_values,
                                                                    gpointer      invocation_hint,
                                                                    gpointer      marshal_data);
void
dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER (GClosure     *closure,
                                                        GValue       *return_value G_GNUC_UNUSED,
                                                        guint         n_param_values,
                                                        const GValue *param_values,
                                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                                        gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__POINTER_POINTER) (gpointer     data1,
                                                             gpointer     arg_1,
                                                             gpointer     arg_2,
                                                             gpointer     data2);
  register GMarshalFunc_BOOLEAN__POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,POINTER (/tmp/dbus-binding-tool-c-marshallers.MFFT3U:5) */
extern void dbus_glib_marshal_pkd_channel_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                                   GValue       *return_value,
                                                                   guint         n_param_values,
                                                                   const GValue *param_values,
                                                                   gpointer      invocation_hint,
                                                                   gpointer      marshal_data);
void
dbus_glib_marshal_pkd_channel_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                       GValue       *return_value G_GNUC_UNUSED,
                                                       guint         n_param_values,
                                                       const GValue *param_values,
                                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                                       gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_POINTER) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

G_END_DECLS

#endif /* __dbus_glib_marshal_pkd_channel_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_pkd_channel_methods[] = {
  { (GCallback) pkd_channel_get_target_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER, 0 },
  { (GCallback) pkd_channel_set_target_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__STRING_POINTER, 58 },
  { (GCallback) pkd_channel_get_args_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER, 112 },
  { (GCallback) pkd_channel_set_args_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__BOXED_POINTER, 167 },
  { (GCallback) pkd_channel_get_pid_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER, 218 },
  { (GCallback) pkd_channel_set_pid_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__UINT_POINTER, 270 },
  { (GCallback) pkd_channel_get_env_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER, 318 },
  { (GCallback) pkd_channel_set_env_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__BOXED_POINTER, 371 },
  { (GCallback) pkd_channel_get_dir_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER_POINTER, 420 },
  { (GCallback) pkd_channel_set_dir_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__STRING_POINTER, 472 },
  { (GCallback) pkd_channel_start, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER, 520 },
  { (GCallback) pkd_channel_stop, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER, 559 },
  { (GCallback) pkd_channel_pause, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER, 597 },
  { (GCallback) pkd_channel_unpause, dbus_glib_marshal_pkd_channel_BOOLEAN__POINTER, 636 },
  { (GCallback) pkd_channel_add_source_dbus, dbus_glib_marshal_pkd_channel_BOOLEAN__BOXED_POINTER, 677 },
};

const DBusGObjectInfo dbus_glib_pkd_channel_object_info = {
  0,
  dbus_glib_pkd_channel_methods,
  15,
"com.dronelabs.Perfkit.Channel\0GetTarget\0S\0target\0O\0F\0N\0s\0\0com.dronelabs.Perfkit.Channel\0SetTarget\0S\0target\0I\0s\0\0com.dronelabs.Perfkit.Channel\0GetArgs\0S\0args\0O\0F\0N\0as\0\0com.dronelabs.Perfkit.Channel\0SetArgs\0S\0args\0I\0as\0\0com.dronelabs.Perfkit.Channel\0GetPid\0S\0pid\0O\0F\0N\0u\0\0com.dronelabs.Perfkit.Channel\0SetPid\0S\0pid\0I\0u\0\0com.dronelabs.Perfkit.Channel\0GetEnv\0S\0env\0O\0F\0N\0as\0\0com.dronelabs.Perfkit.Channel\0SetEnv\0S\0env\0I\0as\0\0com.dronelabs.Perfkit.Channel\0GetDir\0S\0dir\0O\0F\0N\0s\0\0com.dronelabs.Perfkit.Channel\0SetDir\0S\0dir\0I\0s\0\0com.dronelabs.Perfkit.Channel\0Start\0S\0\0com.dronelabs.Perfkit.Channel\0Stop\0S\0\0com.dronelabs.Perfkit.Channel\0Pause\0S\0\0com.dronelabs.Perfkit.Channel\0Unpause\0S\0\0com.dronelabs.Perfkit.Channel\0AddSource\0S\0path\0I\0o\0\0\0",
"\0",
"com.dronelabs.Perfkit.Channel\0Dir\0com.dronelabs.Perfkit.Channel\0Args\0com.dronelabs.Perfkit.Channel\0Target\0com.dronelabs.Perfkit.Channel\0Env\0com.dronelabs.Perfkit.Channel\0Pid\0\0"
};

