/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * generallayout.h
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

#ifndef _GENERALLAYOUT_H_
#define _GENERALLAYOUT_H_

#include <list>
#include <gtkmm/drawingarea.h>
#include "generalmodule.hpp"
//#include "vector2D.hpp"

class GeneralLayout: public Gtk::DrawingArea
{
public:
	GeneralLayout();
	virtual ~GeneralLayout();

	void randomAllModulePosition();

	std::list<GeneralModule*> mGMs;

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_timeout();

private:
	double mZoom;
	bool mautoZoom;
	Vector2D mPan;
	bool mautoPan;
};

#endif // _GENERALLAYOUT_H_

