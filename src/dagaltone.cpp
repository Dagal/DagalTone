/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
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
#include "dagaltone.hpp"

#include <gtkmm/menubar.h>

CDagalTone::CDagalTone(const Glib::RefPtr<Gtk::Application>& app):
	mMainBox(Gtk::ORIENTATION_VERTICAL),
	mPaned(Gtk::ORIENTATION_HORIZONTAL),
	mInputModuleGroup("Entrée"),
	mMidiInputButton("Entrées Midi"),
	mAudioInputButton("Entrées Audio"),
	mOutputModuleGroup("Sortie"),
	mMidiOutputButton("Sorties Midi"),
	mAudioOutputButton("Sorties Audio"),
	mGeneratorGroup("Générateur de signaux"),
	mSinusoidGeneratorButton("Sinusoïde"),
	mEffectGroup("Effets"),
	mVolumeControlButton("Contrôle de volume"),
	mButton1("Test Button 1"),
	mButton2("Test Button 2"),
	mButton3("Test Button 3")
{
	// Window properties
	set_title ("DagalTone");

	// Layout
	add(mMainBox);

	// Action des menus et toolbars
	m_refActionGroup = Gio::SimpleActionGroup::create();
	// Menu fichier
	m_refActionGroup->add_action("quit", sigc::mem_fun (*this, &CDagalTone::on_quit_pressed));
	m_refActionGroup->add_action("input", sigc::mem_fun (*this, &CDagalTone::on_input_pressed));

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
		"	   <submenu>"
		"		<attribute name='label' translatable='yes'>_Edit</attribute>"
		"		<section>"
		"			<item>"
		"				<attribute name='label' translatable='yes'>_Copy</attribute>"
		"				<attribute name='action'>example.copy</attribute>"
		"				<attribute name='accel'>&lt;Primary&gt;c</attribute>"
		"			</item>"
		"		</section>"
		"	   </submenu>"
		"	   <submenu>"
		"		<attribute name='label' translatable='yes'>_View</attribute>"
		"		<section>"
		"			<item>"
		"				<attribute name='label' translatable='yes'>_Center</attribute>"
		"				<attribute name='action'>example.center</attribute>"
		"				<attribute name='accel'>&lt;Primary&gt;t</attribute>"
		"			</item>"
		"		</section>"
		"	   </submenu>"
		"	   <submenu>"
		"		<attribute name='label' translatable='yes'>_Control</attribute>"
		"		<section>"
		"			<item>"
		"				<attribute name='label' translatable='yes'>_Input</attribute>"
		"				<attribute name='action'>example.input</attribute>"
		"				<attribute name='accel'>&lt;Primary&gt;i</attribute>"
		"			</item>"
		"		</section>"
		"	   </submenu>"
		"	   <submenu>"
		"		<attribute name='label' translatable='yes'>_Help</attribute>"
		"		<section>"
		"			<item>"
		"				<attribute name='label' translatable='yes'>_About</attribute>"
		"				<attribute name='action'>example.about</attribute>"
		"				<attribute name='accel'>&lt;Primary&gt;a</attribute>"
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
		mpMenuBar = Gtk::manage(new Gtk::MenuBar(appMenu));
		mMainBox.pack_start(*mpMenuBar, Gtk::PACK_SHRINK);
	}

	mMainBox.pack_start(mToolBar, Gtk::PACK_SHRINK);
	mToolBar.add(mButton1);
	mToolBar.add(mButton2);

	// Gestion de la palette
	mInputModuleGroup.insert(mMidiInputButton);
	mInputModuleGroup.insert(mAudioInputButton);
	mToolPalette.add(mInputModuleGroup);

	mOutputModuleGroup.insert(mMidiOutputButton);
	mOutputModuleGroup.insert(mAudioOutputButton);
	mToolPalette.add(mOutputModuleGroup);

	mGeneratorGroup.insert(mSinusoidGeneratorButton);
	mToolPalette.add(mGeneratorGroup);

	mEffectGroup.insert(mVolumeControlButton);
	mToolPalette.add(mEffectGroup);
	
	mFrameLayout1.add(mToolPalette);

	mPaned.add1(mFrameLayout1);
	mFrameLayout.add(mGL);
	mPaned.add2(mFrameLayout);

	mMainBox.pack_start(mPaned, Gtk::PACK_EXPAND_WIDGET);
	mMainBox.set_center_widget(mPaned);

	mMainBox.pack_end(mStatusBar, Gtk::PACK_SHRINK);
	mStatusBar.push("Ready!");

	show_all_children ();
}

CDagalTone::~CDagalTone()
{
}

void CDagalTone::on_quit_pressed()
{
	std::cerr << "Good bye the world!" << std::endl;
	hide();
}

void CDagalTone::on_input_pressed()
{
	std::cerr << "Add Input Module" << std::endl;
	//double x = rand() / (double)RAND_MAX - 0.5;
	//double y = rand() / (double)RAND_MAX - 0.5;
	//std::list<GeneralModule*>::iterator it = mGL.mGMs.begin();
	//(*it)->moveTo(x,y);
	mGL.randomAllModulePosition();
	//std::cerr << "DÃ©placement vers " << x << "," << y << std::endl;
}

void CDagalTone::on_layout_draw()
{
}
