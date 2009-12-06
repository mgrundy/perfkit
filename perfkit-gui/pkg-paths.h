/* pkg-paths.h
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

#ifndef __PKG_PATHS_H__
#define __PKG_PATHS_H__

#include <glib.h>

G_BEGIN_DECLS

G_CONST_RETURN gchar *  pkg_paths_get_data_dir    (void);
G_CONST_RETURN gchar *  pkg_paths_get_locale_dir  (void);

G_END_DECLS

#endif /* __PKG_PATHS_H__ */