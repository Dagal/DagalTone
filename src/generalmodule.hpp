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
#include <glibmm/ustring.h>
#include "vector2D.hpp"

class GeneralModule
{
public:
	GeneralModule();
	virtual ~GeneralModule();

	void collide(GeneralModule& gm);
	void draw(const Cairo::RefPtr<Cairo::Context>& cr);
	const Vector2D& getDestination() const;
	const Vector2D& getPosition() const;
	const Vector2D& getSpeed() const;
	const Vector2D& getAcceleration() const;
	const Vector2D& getSize() const;
	void moveTo(const double x,
							const double y);
	void moveTo(const Vector2D& destination);
	void relMoveTo(const double x,
								 const double y);
	void relMoveTo(const Vector2D& destination);
	void ramdomMove(const double x1,
									const double y1,
									const double x2,
									const double y2);
	void setColor(const double r,
								const double g,
								const double b);
	void setAlpha(const double a);
	void update(const double time);

	// Espace entre module
	static double padding;

protected:

private:
	Glib::ustring mName; // Nom du module
	Pango::FontDescription mFont;
	Glib::RefPtr<Pango::Layout> mLayout;
	double mTextWidth, mTextHeight;
	
	Vector2D mDesired; // Position à atteindre
	Vector2D mPosition;	// Position
	Vector2D mSpeed;	// Vitesse
	Vector2D mAcceleration;	// Accélération
	double mBreaker;	// coéficient de freinage

	// Couleur
	double mRed;
	double mGreen;
	double mBlue;

	// Transparance
	double mAlpha;

	// Taille
	Vector2D mSize;
	double mBorderSize;
};

#endif // _GENERAL_MODULE_H_
