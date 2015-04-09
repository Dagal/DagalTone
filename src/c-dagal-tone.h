/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * c-dagal-tone.h
 * Copyright (C) 2015 Dagal <dejarding@gmail.com>
 *
 * audio is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * audio is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _C_DAGAL_TONE_H_
#define _C_DAGAL_TONE_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <giomm/simpleactiongroup.h>

class CDagalTone: public Gtk::Window 
{
public:
	 CDagalTone(const Glib::RefPtr<Gtk::Application>& app);
	 virtual ~CDagalTone();

protected:

private:
	 // Signal handlers:
	 void on_quit_pressed();

	 // Child widgets:
	 Gtk::Box mMainBox;
	 
	 Glib::RefPtr<Gtk::Builder> m_refMainMenu;
	 Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
	 Glib::RefPtr<Gio::SimpleAction> m_refActionRain;
};

#endif // _C_DAGAL_TONE_H_

