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

	GM = new GeneralModule();
	mGMs.push_back(GM);
	GM->moveTo(0.3,0.1);

	GM = new GeneralModule();
	mGMs.push_back(GM);
	GM->moveTo(0.2,0.4);

	mZoom.set(1.0,1.0); // Zoom 1:1
	mautoZoom = true;
	mlockZoom = true;
	mPan.set(0.0,0.0); // Origine au centre
	mautoPan = true;

	Glib::signal_timeout().connect
		(sigc::mem_fun(*this,
									 &GeneralLayout::on_timeout),
		 20);
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

	// Calcul du zoom automatique
	double maxX, maxY, minX, minY;
	std::list<GeneralModule*>::iterator it = mGMs.begin();
	minX = (*it)->getPosition().getX() - (*it)->getSize().getX() / 2.0;
	maxX = (*it)->getPosition().getX() + (*it)->getSize().getX() / 2.0;
	minY = (*it)->getPosition().getY() - (*it)->getSize().getY() / 2.0;
	maxY = (*it)->getPosition().getY() + (*it)->getSize().getY() / 2.0;
	it++;
	while (it != mGMs.end())
		{
			double x = (*it)->getPosition().getX();
			double y = (*it)->getPosition().getY();
			double sx = (*it)->getSize().getX();
			double sy = (*it)->getSize().getY();
			if(x - sx < minX) minX = x - sx;
			if(x + sx > maxX) maxX = x + sx;
			if(y - sy < minY) minY = y - sy;
			if(y + sy > maxY) maxY = y + sy;
			it++;
		}

	mZoom.set(1.0 / (maxX - minX),
						1.0 / (maxY - minY));
	mPan.set((maxX + minX) / -2.0,
					 (maxY + minY) / -2.0);

	// Gestion du zoom
	cr->scale(mautoZoom?mZoom.getX():1.0,
						mautoZoom?mZoom.getY():1.0);

	// Position automatique
	cr->translate(mautoPan?mPan.getX():0.0,
								mautoPan?mPan.getY():0.0);

	// Affichage et contrôle des modules
	it = mGMs.begin();
	while (it != mGMs.end())
		{
			(*it)->update(20); // Mise à jour des positions
			// Détection de collision avec le reste des modules
			std::list<GeneralModule*>::iterator it2 = mGMs.begin();
			while (it2 != mGMs.end())
				{
					if (it != it2)
						{
							(*it)->collide(**it2);
						}
					it2++;
				}
			(*it)->draw(cr); // Dessin des modules
			it++;
		}
	
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
			(*it)->ramdomMove(-2,-2,2,2);
			it++;
		}
}
