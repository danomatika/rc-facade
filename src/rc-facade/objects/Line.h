/*==============================================================================

Line.h

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
#ifndef LINE_H
#define LINE_H

#include "Config.h"

#include "DrawableObject.h"

class Line : public DrawableObject
{
	public:

		Line(string name) : DrawableObject("line"), pos1(0, 0), pos2(0, 0)
		{
			// add variables to Xml
			addXmlAttribute("x", "position1", XML_TYPE_INT, &pos1.x);
			addXmlAttribute("y", "position1", XML_TYPE_INT, &pos1.y);
			addXmlAttribute("x", "position2", XML_TYPE_INT, &pos2.x);
			addXmlAttribute("y", "position2", XML_TYPE_INT, &pos2.y);

			setName(name);
		}

		void draw()
		{
			if(bVisible)
			{
				Config::instance().getFacade().stroke(color);
				Config::instance().getFacade().line(pos1.x, pos1.y, pos2.x, pos2.y);
			}
		}

	protected:

		bool processOscMessage(const osc::ReceivedMessage& message, 
		                       const osc::MessageSource& source)
		{
			// call the base class
			if(DrawableObject::processOscMessage(message, source))
			{
				return true;
			}


			if(message.path() == getOscRootAddress() + "/position1" &&
			   message.types() == "ii")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos1.x = message.asInt32(0);
				pos1.y = message.asInt32(1);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/position1/x" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos1.x = message.asInt32(0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/position1/y" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos1.y = message.asInt32(0);
				return true;
			}

			else if(message.path() == getOscRootAddress() + "/position2" &&
			        message.types() == "ii")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos2.x = message.asInt32(0);
				pos2.y = message.asInt32(1);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/position2/x" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos2.x = message.asInt32(0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/position2/y" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				pos2.y = message.asInt32(0);
				return true;
			}

			return false;
		}

		vmml::Vector2i pos1, pos2;
};

#endif // LINE_H
