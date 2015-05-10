/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * general-module.cc
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

#include <iostream>
#include "generalmodule.hpp"

GeneralModule::GeneralModule()
{
	mName = "General Module";
	mDesired.set(0.0,0.0);
	mBreaker = 0.984;

	mSize.set(1.0,1.0);
	
	setColor(1.0,0.0,0.0);

	setAlpha(0.5);
}

GeneralModule::~GeneralModule()
{
}

void GeneralModule::collide(GeneralModule& gm)
{
	if((mPosition.getX() + mSize.getX() / 2.0 >
			gm.mPosition.getX() - gm.mSize.getX() / 2.0) &&
		 (mPosition.getX() - mSize.getX() / 2.0 <
			gm.mPosition.getX() + gm.mSize.getX() / 2.0) &&
		 (mPosition.getY() + mSize.getY() / 2.0 >
			gm.mPosition.getY() - gm.mSize.getY() / 2.0) &&
		 (mPosition.getY() - mSize.getY() / 2.0 <
			gm.mPosition.getY() + gm.mSize.getY() / 2.0))
		{
			mBlue = 1.0;
			gm.mGreen = 1.0;
			// Équation d'une droite y = p.x + d
			// p = (y2 - y1) / (x2 - x1)
			// Dans notre cas (x1,y1) correspond au centre du module
			// Et (x2,y2) au coin supérieur droit du module
			// Par simplification mathématique, on obtient
			// p = SizeY / SizeX
			// Ce qui correspond à la tangente ... à réfléchir pour la suite
			double p1 = mSize.getY() / mSize.getX();
			// d = y - p.x
			// Si on prend la position du module comme point de passage, on a
			double d1 = mPosition.getY() - p1 * mPosition.getX();
			// On a besoin des valeurs de la pente inverse également
			double p2 = -p1;
			double d2 = mPosition.getY() - p2 * mPosition.getX();
			Vector2D middleSize = (gm.mSize + mSize) / 2.0;
			
			// Comparaison de la position du deuxième point par rapport à la première droite
			if (gm.mPosition.getY() >= p1 * gm.mPosition.getX() + d1)
				{
					// Idem sur l'autre droite
					if (gm.mPosition.getY() >= p2 * gm.mPosition.getX() + d2)
						{
							// On est au dessus
							gm.moveTo(gm.mPosition.getX(),
												mPosition.getY() +
												padding +
												middleSize.getY());
						}
					else
						{
							// On est à droite
							gm.moveTo(mPosition.getX() -
												padding -
												middleSize.getX(),
												gm.mPosition.getY());
						}
				}
			else
				{
					// On recommence le même test
					if (gm.mPosition.getY() >= p2 * gm.mPosition.getX() + d2)
						{
							// On est à gauche
							gm.moveTo(mPosition.getX() +
												padding +
												middleSize.getX(),
												gm.mPosition.getY());
						}
					else
						{
							// On est en bas
							gm.moveTo(gm.mPosition.getX(),
												mPosition.getY() -
												padding -
												middleSize.getY());
						}
				}
			
		}
	else
		{
			mBlue = 0.0;
			gm.mGreen = 0.0;
		}
}


void GeneralModule::update(const double time)
{
	mAcceleration.setX((mDesired.getX() - mPosition.getX()));
	mAcceleration.setY((mDesired.getY() - mPosition.getY()));
	mSpeed.setX((mSpeed.getX() +
							 mAcceleration.getX() * time / 1000.0) * mBreaker);
	mSpeed.setY((mSpeed.getY() +
							 mAcceleration.getY() * time / 1000.0) * mBreaker);
	mPosition.setX(mPosition.getX() +
								 mSpeed.getX() * time / 1000.0 +
								 mAcceleration.getX() * time * time / 2000000.0);
	mPosition.setY(mPosition.getY() +
								 mSpeed.getY() * time / 1000.0 +
								 mAcceleration.getY() * time * time / 2000000.0);
}

void GeneralModule::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
//	std::cout << "GeneralModule::draw" << std::endl;
	cr->save();
	cr->set_line_width(0.01);
	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_source_rgba(mRed,
											mGreen,
											mBlue,
											mAlpha);
	cr->rectangle(mSize.getX() / -2.0 + mPosition.getX(),
								mSize.getY() / -2.0 + mPosition.getY(),
								mSize.getX(),
								mSize.getY());
	cr->fill();
//	cr->stroke();
	cr->set_source_rgba(mRed,
											mGreen,
											mBlue,
											1.0);
	cr->rectangle(mSize.getX() / -2.0 + mPosition.getX(),
								mSize.getY() / -2.0 + mPosition.getY(),
								mSize.getX(),
								mSize.getY());
	cr->stroke();
	cr->restore();
}

const Vector2D& GeneralModule::getDestination() const
{
	return mDesired;
}

const Vector2D& GeneralModule::getPosition() const
{
	return mPosition;
}

const Vector2D& GeneralModule::getSpeed() const
{
	return mSpeed;
}

const Vector2D& GeneralModule::getAcceleration() const
{
	return mAcceleration;
}

const Vector2D& GeneralModule::getSize() const
{
	return mSize;
}

void GeneralModule::moveTo(const double x, const double y)
{
	mDesired.set(x,y);
}

void GeneralModule::moveTo(const Vector2D& destination)
{
	mDesired = destination;
}

void GeneralModule::relMoveTo(const double x, const double y)
{
	Vector2D tmp(x, y);
	mDesired += tmp;
}

void GeneralModule::relMoveTo(const Vector2D& destination)
{
	mDesired += destination;
}

void GeneralModule::ramdomMove(const double x1,
															 const double y1,
															 const double x2,
															 const double y2)
{
	double x = (x2 - x1) * rand() / (double)RAND_MAX + x1;
	double y = (y2 - y1) * rand() / (double)RAND_MAX + y1;
	moveTo(x,y);
}

void GeneralModule::setColor(const double r,
														 const double g,
														 const double b)
{
	mRed = r;
	mGreen = g;
	mBlue = b;
}

void GeneralModule::setAlpha(const double a)
{
	mAlpha = a;
}

double GeneralModule::padding = 0.1;
