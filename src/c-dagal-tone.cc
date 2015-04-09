/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * c-dagal-tone.cc
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

#include <iostream>
#include "c-dagal-tone.h"

#include <gtkmm/menubar.h>

CDagalTone::CDagalTone(const Glib::RefPtr<Gtk::Application>& app):
	mMainBox(Gtk::ORIENTATION_VERTICAL)
{
		// Window properties
		set_title ("DagalTone");

		// Layout
		add(mMainBox);
		
		// Action des menus et toolbars
		m_refActionGroup = Gio::SimpleActionGroup::create();
		// Menu fichier
		m_refActionGroup->add_action("quit", sigc::mem_fun (*this, &CDagalTone::on_quit_pressed));

		insert_action_group ("example", m_refActionGroup);

		// Création du menu à l'aide de balise xml
		m_refMainMenu = Gtk::Builder::create();
		Glib::ustring ui_info =
			"<interface>"
			"   <!-- menubar -->"
			"   <menu id='mainmenu'>"
			"	   <submenu>"
			"		<attribute name='label' translatable='yes'>_File</attribute>"
			"		<section>"
			"			<item>"
			"				<attribute name='label' translatable='yes'>_Quit</attribute>"
			"				<attribute name='action'>example.quit</attribute>"
			"				<attribute name='accel'>&lt;Primary&gt;q</attribute>"
			"			</item>"
			"		</section>"
			"	   </submenu>"
			"   </menu>"
			"</interface>";

		try
		{
			m_refMainMenu->add_from_string (ui_info);
		}
		catch (const Glib::Error& ex)
		{
			std::cerr << "La création du menu a échoué!:" << ex.what() << std::endl;
		}

		Glib::RefPtr<Glib::Object> object = m_refMainMenu->get_object("mainmenu");
		Glib::RefPtr<Gio::Menu> appMenu = Glib::RefPtr<Gio::Menu>::cast_dynamic (object);
		if (!appMenu)
		{
			g_warning("appMenu is not here");
		}
		else
		{
			pMenuBar = Gtk::manage(new Gtk::MenuBar(appMenu));
			mMainBox.pack_start(*pMenuBar, Gtk::PACK_SHRINK);
		}
		show_all_children ();
}

CDagalTone::~CDagalTone()
{
}

void CDagalTone::on_quit_pressed()
{
	std::cerr << "Good bye the world!" << std::endl;
}