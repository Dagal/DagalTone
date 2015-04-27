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
	mxdesired = mydesired = 0.0;
	breaker = 0.984;
}

GeneralModule::~GeneralModule()
{
}

void GeneralModule::update(const double time)
{
	max = (mxdesired - mx);
	may = (mydesired - my);
	mvx = (mvx + max * time / 1000.0) * breaker;
	mvy = (mvy + may * time / 1000.0) * breaker;
	mx = mx + mvx * time / 1000.0 + max * time * time / 2000000.0;
	my = my + mvy * time / 1000.0 + may * time * time / 2000000.0;
	if (mx < -0.5)
	{
		mx = mx + (-0.5 - mx) * 2.0;
		mvx = -mvx;
	}
	if (mx > 0.5)
	{
		mx = mx - (mx - 0.5) * 2.0;
		mvx = -mvx;
	}
	if (my < -0.5)
	{
		my = my + (-0.5 - my) * 2.0;
		mvy = -mvy;
	}
	if (my > 0.5)
	{
		my = my - (my - 0.5) * 2.0;
		mvy = -mvy;
	}
}

void GeneralModule::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
//	std::cout << "GeneralModule::draw" << std::endl;
	cr->save();
	cr->set_line_width(0.01);
	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_source_rgba(1.0,1.0,0.0,0.5);
	cr->rectangle(-0.2 + mx,-0.2 + my,0.4,0.4);
	cr->fill();
//	cr->stroke();
	cr->set_source_rgba(1.0,0.0,0.0,1.0);
	cr->rectangle(-0.2 + mx,-0.2 + my,0.4,0.4);
	cr->stroke();
	cr->restore();
}

void GeneralModule::moveTo(const double x, const double y)
{
	mxdesired = x;
	mydesired = y;
}
