/* pause-task.vala
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

using GLib;
using Gtk;
using Perfkit;

namespace Ppg {
	public class PauseTask: Ppg.Task {
		public Session session { get; set; }

		public override void run () {
			if (session == null) {
				finish_with_error();
			}

			try {
				session.pause();
				finish();
			} catch (GLib.Error error) {
				finish_with_error(error);
			}
		}
	}
}