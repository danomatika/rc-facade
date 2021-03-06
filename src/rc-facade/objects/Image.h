/*==============================================================================

Image.h

rc-facade: a simple 2d graphics engine for the AEC facade

Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#ifndef IMAGE_H
#define IMAGE_H

#include "Common.h"

#include "DrawableObject.h"

class Image : public DrawableObject
{
	public:

		Image(string name);
		~Image();

		bool loadFile(string filename="");
		
		void setup();

		void draw();
		void draw(int x, int y);

		void setDrawFromCenter(bool yesno) {bDrawFromCenter = yesno;}

		unsigned int getFrameTime() {return frameTime;}

	protected:

		/* ***** XML CALLBACKS ***** */

		bool readXml(TiXmlElement* e);
		bool writeXml(TiXmlElement* e);

		/* ***** OSC CALLBACKS ***** */

		bool processOscMessage(const osc::ReceivedMessage& message,
		                       const osc::MessageSource& source);

		vector<visual::Color> bitmap; /// bitmap of colors

		string filename;            /// filename to load
		unsigned int frameTime;     /// how long to display in ms
		vmml::Vector2i pos;
		unsigned int width, height;
		bool bDrawFromCenter;       /// draw from the center using pos
};

#endif // IMAGE_H
