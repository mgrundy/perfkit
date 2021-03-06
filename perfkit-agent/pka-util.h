/* pka-util.h
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

#ifndef PKA_UTIL_H
#define PKA_UTIL_H

#include <glib.h>

G_BEGIN_DECLS

#define pka_str_empty(_s)  (!(_s)[0])
#define pka_str_empty0(_s) (!(_s) || pka_str_empty(_s))
#define pka_get_user_runtime_path(...) g_build_filename(pka_get_user_runtime_dir(), ## __VA_ARGS__)

const gchar* pka_get_user_runtime_dir (void);

G_END_DECLS

#endif /* PKA_UTIL_H */
