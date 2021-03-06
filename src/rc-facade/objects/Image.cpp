/*==============================================================================

Image.cpp

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
#include "Image.h"

#include <sstream>

Image::Image(string name) : DrawableObject("image"), frameTime(0),
	pos(0, 0), bDrawFromCenter(false)
{
	// add variables to Xml
	addXmlAttribute("name", "image", XML_TYPE_STRING, &name);
	addXmlAttribute("file", "image", XML_TYPE_STRING, &filename);
	addXmlAttribute("frametime", "image", XML_TYPE_UINT, &frameTime);
	addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
	addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);
	addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
	addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
	addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

	// detach variables from Xml
	removeXmlAttribute("R", "color");
	removeXmlAttribute("G", "color");
	removeXmlAttribute("B", "color");
	removeXmlAttribute("A", "color");

	setName(name);
}

Image::~Image()
{
	bitmap.clear();
}

bool Image::loadFile(string filename)
{
	if(filename == "")
		filename = this->filename;
	
	visual::Image image;
	image.load(filename);
	if(!image.isLoaded())
		return false;

	if(image.width() != (int) width || image.height() != (int) height)
	{
		// resize image
		LOG_DEBUG << "Image: \"" << name << "\" resized to "
		          << width << "x" << height << std::endl;  
		image.pixelate(image.width()/width, image.height()/height);
		image.resize(width, height);
	}
	
	// clear the bitmap
	bitmap.clear();
	
	// load the image values into the bitmap
	for(unsigned int y = 0; y < height; ++y)
	{
		for(unsigned int x = 0; x < width; ++x)
		{	
			visual::Color c = image.getPixel(x, y);
			bitmap.push_back(c);
		}
	}
	
	return true;
}

void Image::setup()
{
	loadFile();
}

void Image::draw()
{
	draw(pos.x, pos.y);
}

void Image::draw(int x, int y)
{
	if(bitmap.empty())
		return;

	if(bVisible)
	{
		int xPos = x, yPos = y;

		if(bDrawFromCenter)
		{
			xPos = xPos - width/2;
			yPos = yPos - height/2;
		}

		for(unsigned int _y = 0; _y < height; ++_y)
		{
			for(unsigned int _x = 0; _x < width; ++_x)
			{
				Config::instance().getFacade().stroke(bitmap.at(_y*width + _x));
				Config::instance().getFacade().pixel(xPos+_x, yPos+_y);
			}
		}
	}
}

bool Image::readXml(TiXmlElement* e)
{
	return true;
}

bool Image::writeXml(TiXmlElement* e)
{
	return true;
}

bool Image::processOscMessage(const osc::ReceivedMessage& message,
                              const osc::MessageSource& source)
{
	// call the base class
	if(DrawableObject::processOscMessage(message, source))
	{
		return true;
	}

	if(message.path() == getOscRootAddress() + "/position" &&
	   message.types() == "ii")
	{
		pos.x = message.asInt32(0);
		pos.y = message.asInt32(1);
		return true;
	}
	else if(message.path() == getOscRootAddress() + "/position/x" &&
	        message.types() == "i")
	{
		pos.x = message.asInt32(0);
		return true;
	}
	else if(message.path() == getOscRootAddress() + "/position/y" &&
	        message.types() == "i")
	{
		pos.y = message.asInt32(0);
		return true;
	}
	else if(message.path() == getOscRootAddress() + "/center" &&
	        message.types() == "i")
	{
		bDrawFromCenter = message.asBool(0);
		return true;
	}

	return false;
}
