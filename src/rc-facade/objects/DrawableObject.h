/*==============================================================================

DrawableObject.h

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
#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "../Common.h"

#include "../Config.h"

class DrawableObject : public XmlObject, public OscObject
{
	public:

		DrawableObject(string objectName) :
			XmlObject(objectName), OscObject(objectName), bVisible(true)
		{
			// attach variables to Xml
			addXmlAttribute("R", "color", XML_TYPE_BYTE, &color.R);
			addXmlAttribute("G", "color", XML_TYPE_BYTE, &color.G);
			addXmlAttribute("B", "color", XML_TYPE_BYTE, &color.B);
			addXmlAttribute("A", "color", XML_TYPE_BYTE, &color.A);

			addXmlAttribute("yesno", "visible", XML_TYPE_BOOL, &bVisible);

			addXmlAttribute("name", objectName, XML_TYPE_STRING, &name);
		}

		virtual void setup() {}
		virtual void draw() = 0;

		/// sets the name and osc address, call this after the Config::_listener
		/// root address has been set
		void setName(string name)
		{
			// set osc address relative to root in listener
			setOscRootAddress(Config::instance().getReceiver().getOscRootAddress() + "/" + name);

			LOG << name << " " << getOscRootAddress() << endl;

			this->name = name;
		}

		string getName() {return name;}

	protected:

		/// process one osc message, derived objects should call this
		/// using DrawableObject::processOscMessage() to handle the base variables
		virtual bool processOscMessage(const ReceivedMessage& message,
		                               const MessageSource& source)
		{
			if(message.path() == getOscRootAddress() + "/color" &&
			   message.types() == "iiii")
			{
				color.R  = message.asInt32(0);
				color.G  = message.asInt32(1);
				color.B  = message.asInt32(2);
				color.A  = message.asInt32(3);
				
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/color/R" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				color.R  = message.asInt32(0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/color/G" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				color.G  = message.asInt32(0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/color/B" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				color.B  = message.asInt32(0);
				return true;
			}
			else if(message.path() == getOscRootAddress() + "/color/A" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				color.A  = message.asInt32(0);
				return true;
			}


			else if(message.path() == getOscRootAddress() + "/visible" &&
			        message.types() == "i")
			{
				//osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				bVisible = (bool) message.asInt32(0);
				return true;
			}


			return false;
		}

		visual::Color color;
		bool bVisible;
		string name;
};

#endif // DRAWABLE_OBJECT_H
