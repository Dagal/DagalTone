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
#include "vector2D.hpp"

class GeneralModule
{
public:
	GeneralModule();
	virtual ~GeneralModule();

	void collide(GeneralModule& gm);
	void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;
	const Vector2D& getDestination() const;
	const Vector2D& getPosition() const;
	const Vector2D& getSpeed() const;
	const Vector2D& getAcceleration() const;
	const Vector2D& getSize() const;
	void moveTo(const double x,
							const double y);
	void moveTo(const Vector2D& destination);
	void ramdomMove(const double x1,
									const double y1,
									const double x2,
									const double y2);
	void setBorderColor(const double r,
											const double g,
											const double b,
											const double a);
	void setBackgroundColor(const double r,
													const double g,
													const double b,
													const double a);
	void update(const double time);

protected:

private:
	Vector2D mDesired; // Position à atteindre
	Vector2D mPosition;	// Position
	Vector2D mSpeed;	// Vitesse
	Vector2D mAcceleration;	// Accélération
	double mBreaker;	// coéficient de freinage

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

	// Taille
	Vector2D mSize;
};

#endif // _GENERAL_MODULE_H_

