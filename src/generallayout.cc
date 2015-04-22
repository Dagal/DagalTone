/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
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
#include "generallayout.h"

GeneralLayout::GeneralLayout() :
	Gtk::DrawingArea()
{
		mGM.moveTo(-1,-0.6);
		
		Glib::signal_timeout().connect(sigc::mem_fun(*this,&GeneralLayout::on_timeout),20);
}

GeneralLayout::~GeneralLayout()
{
}

bool GeneralLayout::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	cr->scale(width,height);
	cr->translate(0.5,0.5);
	cr->set_line_width(0.05);
  cr->save();
	cr->set_source_rgba(0.337,0.612,0.117,0.9);
	cr->paint();
	cr->restore();
	cr->arc(0, 0, 0.42, 0, 2*M_PI);
	cr->save();
	cr->set_source_rgba(1.0,1.0,1.0,0.8);
	cr->fill_preserve();
	cr->restore();
	cr->stroke();

	mGM.update(20);
	mGM.draw(cr);
	
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
