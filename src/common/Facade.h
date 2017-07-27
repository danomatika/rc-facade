/*==============================================================================

Facade.h

Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

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
#ifndef FACADE_H
#define FACADE_H

#include <visualframework/visualframework.h>
#include <xmlframework/xmlframework.h>
#include <facade/Facade.h>

class Facade : public facade::Facade, public xml::XmlObject
{
	public:

		Facade();
		virtual ~Facade();
		
		/// setup the sending destination
		void setup(std::string addr, unsigned int port);
		
		// draw the framebuffer
		void draw(int x=0, int y=0);
		
		/// send a facade frame
		void send();
		
		/// draw the individual sides with different colors for debugging placement,
		/// ignores background (off by default)
		inline void showSides(bool yesno) {_bShowSides = yesno;}
		inline void showSidesToggle()     {_bShowSides = !_bShowSides;}
		
		/// should the sides draw outlines around the windows?
		inline void drawOutlines(bool yesno) {_bDrawOutlines = yesno;}
		inline void drawOutlinesToggle()     {_bDrawOutlines = !_bDrawOutlines;}
		
		/// set/get the draw size of a window in pixels
		/// note: aspect ration is 3:1
		inline void setWindowSize(unsigned int size) {_windowSize = size;}
		inline unsigned int getWindowSize()          {return _windowSize;}
		
		/// get the draw width and height, based on windowSize
		unsigned int getDrawWidth();
		unsigned int getDrawHeight();
		
	protected:
	
			/// xml read callback
		bool readXml(TiXmlElement* e);
		
		/// parse xml for one side
		void parseSideXml(TiXmlElement* e, facade::FacadeSide side);

	private:
		
		visual::Image _facadeImage;
		visual::Image _facadeMask;
		
		visual::UdpSender _sender;
		UdpPacket* _packet;
		
		bool _bDrawOutlines;
		bool _bShowSides;
		unsigned int _windowSize;
};

#endif // FACADE_H
