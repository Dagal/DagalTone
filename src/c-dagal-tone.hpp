/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
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
#include <gtkmm/menubar.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/paned.h>
#include <gtkmm/toolpalette.h>
#include <gtkmm/frame.h>
#include "generallayout.h"
//#include <gtkmm/layout.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/toolitemgroup.h>

class CDagalTone: public Gtk::Window 
{
public:
	 CDagalTone(const Glib::RefPtr<Gtk::Application>& app);
	 virtual ~CDagalTone();

	 GeneralLayout mGL;

protected:

private:
	 // Signal handlers:
	 void on_quit_pressed();
	 void on_input_pressed();
	 void on_layout_draw();

	 // Child widgets:
	 Gtk::Box mMainBox;

	 // Référence Action, Menu et ToolBar
	 Glib::RefPtr<Gtk::Builder> m_refMainMenu;
	 Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
	 Glib::RefPtr<Gio::SimpleAction> m_refActionRain;
	 Gtk::MenuBar* mpMenuBar;
	 Gtk::Toolbar mToolBar;

	 // Centre 
	 Gtk::Paned mPaned;
	 Gtk::Frame mFrameLayout1;
	 Gtk::ToolPalette mToolPalette;
	 Gtk::ToolItemGroup mToolItemGroup;
	 Gtk::Frame mFrameLayout;

	 // StatusBar
	 Gtk::Statusbar mStatusBar;

	 // Test Tool Button
	 Gtk::ToolButton mButton1;
	 Gtk::ToolButton mButton2;
	 Gtk::Button mButton3;
};

#endif // _C_DAGAL_TONE_H_

