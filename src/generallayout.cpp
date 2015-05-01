/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * generallayout.cc
 * Copyright (C) 2015 Dejardin Gilbert <dejarding@gmail.com>
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

#include <glibmm/main.h>
#include "generallayout.hpp"

GeneralLayout::GeneralLayout() :
	Gtk::DrawingArea()
{
	GeneralModule* GM = new GeneralModule();
	mGMs.push_back(GM);
	GM->moveTo(-0.5,-0.2);

	mxZoom = 1.0;
	myZoom = 1.0;
	mautoZoom = true;
	mxPan = 0.0;
	myPan = 0.0;
	mautoPan = true;

	Glib::signal_timeout().connect(sigc::mem_fun(*this,&GeneralLayout::on_timeout),20);
}

GeneralLayout::~GeneralLayout()
{
}

bool GeneralLayout::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	// Récupération des informations de notre surface de travail
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// Centrage
	cr->translate(width / 2.0, height / 2.0);

	// Taille unitaire
	cr->scale((width<height)?width:height,
						(width<height)?width:height);
	
	// Paramètres par défaut
	cr->set_line_width(0.02);

	// Définition de la couleur de fond
	cr->set_source_rgba(0.2,0.2,0.3,1.0);
	cr->paint();

	// Dessin du fond d'écran
	cr->save();
	cr->set_source_rgba(0.0,0.0,0.0,1.0);
	cr->arc(0, 0, 0.42, 0, 2*M_PI);
	cr->fill();
	cr->set_source_rgba(1.0,1.0,1.0,1.0);
	cr->arc(0, 0, 0.42, 0, 2*M_PI);
	cr->stroke();
	cr->restore();

	// Gestion du zoom
	cr->scale(mautoZoom?mxZoom:1.0,
						mautoZoom?myZoom:1.0);

	// Position automatique
	cr->translate(mautoPan?mxPan:0.0,
								mautoPan?myPan:0.0);

	// Affichage des modules
	std::list<GeneralModule*>::iterator it = mGMs.begin();
	(*it)->update(20);
	(*it)->draw(cr);
	
	cr->clip();
	
	return true;
}

bool GeneralLayout::on_timeout()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0,0, get_allocation().get_width(),get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}

void GeneralLayout::randomAllModulePosition()
{
	std::list<GeneralModule*>::iterator it = mGMs.begin();
	while(it != mGMs.end())
		{
			it++;
		}
}
