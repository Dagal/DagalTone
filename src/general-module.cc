/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
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
#include "general-module.h"

GeneralModule::GeneralModule()
{
}

GeneralModule::~GeneralModule()
{
}

void GeneralModule::update(const double time)
{
	max = -mx;
	may = -my;
	mvx = mvx + max * time / 1000.0;
	mvy = mvy + may * time / 1000.0;
	mx = mx + mvx * time / 1000.0 + max * time * time / 2000000.0;
	my = my + mvy * time / 1000.0 + may * time * time / 2000000.0;
}

void GeneralModule::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
//	std::cout << "GeneralModule::draw" << std::endl;
	cr->save();
	cr->set_line_width(0.01);
	cr->set_source_rgba(1.0,0.0,0.0,0.8);
	cr->rectangle(-0.2 + mx,-0.2 + my,0.4,0.4);
	cr->fill_preserve();
	cr->restore();
	cr->stroke();
}

void GeneralModule::moveTo(const double x, const double y)
{
	mx = x;
	my = y;
}