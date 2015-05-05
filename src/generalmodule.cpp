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
	mDesired.set(0.0,0.0);
	mBreaker = 0.984;

	mSize.set(1.0,1.0);
	
	setBorderColor(1.0,0.0,0.0,1.0);

	setBackgroundColor(1.0,0.0,1.0,0.5);
}

GeneralModule::~GeneralModule()
{
}

void GeneralModule::collide(GeneralModule& gm)
{
	if((mPosition.getX() + mSize.getX() * 1.1 > gm.getPosition().getX() - gm.getSize().getX() * 1.1) &&
		 (mPosition.getX() - mSize.getX() * 1.1 < gm.getPosition().getX() + gm.getSize().getX() * 1.1) &&
		 (mPosition.getY() + mSize.getY() * 1.1 > gm.getPosition().getY() - gm.getSize().getY() * 1.1) &&
		 (mPosition.getY() - mSize.getY() * 1.1 < gm.getPosition().getY() + gm.getSize().getY() * 1.1))
		{
			mAcceleration = mPosition - gm.mPosition;
			
			//mAcceleration.set(mPosition.getX()-
			//									gm.getPosition().getX(),
			//									mPosition.getY()-
			//									gm.getPosition().getY());
			
			//todo: make collision move... mDesired or mAcceleration must be changed...
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
	
	if (mPosition.getX() < -0.5)
	{
		mPosition.setX(mPosition.getX() +
									 (-0.5 - mPosition.getX()) * 2.0);
		mSpeed.setX(-mSpeed.getX());
	}
	if (mPosition.getX() > 0.5)
	{
		mPosition.setX(mPosition.getX() -
									 (mPosition.getX() - 0.5) * 2.0);
		mSpeed.setX(-mSpeed.getX());
	}
	if (mPosition.getY() < -0.5)
	{
		mPosition.setY(mPosition.getX() +
									 (-0.5 - mPosition.getY()) * 2.0);
		mSpeed.setY(-mSpeed.getY());
	}
	if (mPosition.getY() > 0.5)
	{
		mPosition.setY(mPosition.getY() -
									 (mPosition.getY() - 0.5) * 2.0);
		mSpeed.setY(-mSpeed.getY());
	}
}

void GeneralModule::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
//	std::cout << "GeneralModule::draw" << std::endl;
	cr->save();
	cr->set_line_width(0.01);
	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_source_rgba(mBackgroundR,
											mBackgroundG,
											mBackgroundB,
											mBackgroundA);
	cr->rectangle(-0.2 + mPosition.getX(),
								-0.2 + mPosition.getY(),
								0.4,
								0.4);
	cr->fill();
//	cr->stroke();
	cr->set_source_rgba(mBorderR,
											mBorderG,
											mBorderB,
											mBorderA);
	cr->rectangle(-0.2 + mPosition.getX(),
								-0.2 + mPosition.getY(),
								0.4,
								0.4);
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

void GeneralModule::ramdomMove(const double x1,
															 const double y1,
															 const double x2,
															 const double y2)
{
	double x = (x2 - x1) * rand() / (double)RAND_MAX + x1;
	double y = (y2 - y1) * rand() / (double)RAND_MAX + y1;
}

void GeneralModule::setBorderColor(const double r,
																	 const double g,
																	 const double b,
																	 const double a)
{
	mBorderR = r;
	mBorderG = g;
	mBorderB = b;
	mBorderA = a;
}

void GeneralModule::setBackgroundColor(const double r,
																			 const double g,
																			 const double b,
																			 const double a)
{
	mBackgroundR = r;
	mBackgroundG = g;
	mBackgroundB = b;
	mBackgroundA = a;
}
