/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * general-module.h
 * Copyright (C) 2015 Gilbert Dejardin <dejarding@gmail.com>
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

#ifndef _GENERAL_MODULE_H_
#define _GENERAL_MODULE_H_

#include <gtkmm/drawingarea.h>

class GeneralModule
{
public:
	 GeneralModule();
	 virtual ~GeneralModule();
	 void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;
	 void moveTo(const double x, const double y);
	 void update(const double time);

protected:

private:
	 double mxdesired, mydesired; // Position à atteindre
	 double mx,my;	// Position
	 double mvx,mvy;	// Vitesse
	 double max,may;	// Accélération
	 double breaker;	// coéficient de freinage

	// Couleur du bord
	double mBorderR;
	double mBorderG;
	double mBorderB;
	double mBorderA;

	// Couleur du fond
	double mBackgroundR;
	double mBackgroundG;
	double mBackgroundB;
	double mBackgroundA;

};

#endif // _GENERAL_MODULE_H_

