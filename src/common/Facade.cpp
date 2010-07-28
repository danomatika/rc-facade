/*==============================================================================

	Facade.cpp
  
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
#include "Facade.h"

#define FACADE_WIN_ASPECT_WIDTH 3

using namespace std;
using namespace visual;
using namespace xml;

Facade::Facade() : XmlObject("mapping"), _packet(NULL),
	_bDrawOutlines(false), _bShowSides(false), _windowSize(6)
{
    // allocate packet
    _packet = SDLNet_AllocPacket(getPacketLen());
    _packet->len = getPacketLen();
}

Facade::~Facade()
{
	SDLNet_FreePacket(_packet); // cleanup
}

void Facade::setup(string addr, unsigned int port)
{
	_sender.setup(addr, 8080, getPacketLen());
}

void Facade::draw(int x, int y)
{
    int xPos = x, yPos = y, xStart = xPos;
    
    if(!_bDrawOutlines)
        Graphics::noStroke();
    
    for(unsigned int y = 0; y < getHeight(); ++y)
    {
        for(unsigned int x = 0; x < getWidth(); ++x)
        {
			// draw mask overlay
            if(_bShowSides)
            {
            	Color color;
                color.setWithAlpha(getMask()[y*getWidth()+x]);
                if(color.argb != 0)
                {
                	//color.A = 100;
            		Graphics::fill(color);
            		Graphics::rectangle(xPos, yPos, _windowSize*FACADE_WIN_ASPECT_WIDTH, _windowSize);
				}
            }
			
        	// draw framebufer
            Graphics::fill(Color(getFrameBuffer()[y*getWidth()+x]));
            if(_bDrawOutlines)
            	visual::Graphics::stroke(0x666666);
			if(_bShowSides)
			{
				//if(getCl
			}
			else
            	Graphics::rectangle(xPos, yPos, _windowSize*FACADE_WIN_ASPECT_WIDTH, _windowSize);
            
            xPos += _windowSize*FACADE_WIN_ASPECT_WIDTH;
        }
        xPos = xStart;
        yPos += _windowSize;
    }
}
        
void Facade::send()
{
	// send the facade frame packet
    try
    {
        memcpy(_packet->data, getPacket(), getPacketLen());
        _sender.send(_packet);
    }
    catch(std::exception& e)
    {
        LOG_ERROR << "Facade: Could not send packet: " << e.what() << endl;
    }
}

unsigned int Facade::getDrawWidth()
{
	return _windowSize*FACADE_WIN_ASPECT_WIDTH*getWidth();
}

unsigned int Facade::getDrawHeight()
{
	return _windowSize*getHeight();
}

/* ***** PROTECTED ***** */

bool Facade::readXml(TiXmlElement* e)
{
	// reset for reloading
	reset();

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "move")
        {
			int x = Xml::getAttrInt(child, "x");
			int y = Xml::getAttrInt(child, "y"); 
            moveSides(x, y);
			LOG_DEBUG << "Facade: Moving sides: " << x << " " << y << endl;
        }
		else if(child->ValueStr() == "sides")
		{
			TiXmlElement* child2 = child->FirstChildElement();
			while(child2 != NULL)
			{
				if(child2->ValueStr() == "MainEast")
					parseSideXml(child2, facade::SIDE_MAIN_EAST);
				else if(child2->ValueStr() == "MainNorth")
					parseSideXml(child2, facade::SIDE_MAIN_NORTH);
				else if(child2->ValueStr() == "MainWest")
					parseSideXml(child2, facade::SIDE_MAIN_WEST);
				else if(child2->ValueStr() == "MainSouth")
					parseSideXml(child2, facade::SIDE_MAIN_SOUTH);
				else if(child2->ValueStr() == "MainSouthStreet")
					parseSideXml(child2, facade::SIDE_MAIN_SOUTH_STREET);
				else if(child2->ValueStr() == "LabEast")
					parseSideXml(child2, facade::SIDE_LAB_EAST);
				else if(child2->ValueStr() == "LabNorth")
					parseSideXml(child2, facade::SIDE_LAB_NORTH);
				else if(child2->ValueStr() == "LabSouth")
					parseSideXml(child2, facade::SIDE_LAB_SOUTH);
				else
					LOG_WARN << "Facade: Unknown element \""
							 << child->ValueStr() << "\"" << endl;
					
				 child2 = child2->NextSiblingElement();
			}
		}

        child = child->NextSiblingElement();
    }

    recomputeSize();

    return true;
}

void Facade::parseSideXml(TiXmlElement* e, facade::FacadeSide side)
{
	enableSide(side, Xml::getAttrBool(e, "enabled", true));
	
	TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
		if(child->ValueStr() == "move")
		{
			int x = Xml::getAttrInt(child, "x");
			int y = Xml::getAttrInt(child, "y"); 
			moveSide(side, x, y);
			LOG_DEBUG << "Facade: Moving " << getSideName(side)
					  << ": " << x << " " << y << endl;
		}
		else if(child->ValueStr() == "pos")
		{
			int x = Xml::getAttrInt(child, "x");
			int y = Xml::getAttrInt(child, "y"); 
			setSidePos(side, x, y);
			LOG_DEBUG << "Facade: Pos " << getSideName(side)
					  << ": " << x << " " << y << endl;
		}
		else if(child->ValueStr() == "flip")
		{
			bool x = Xml::getAttrBool(child, "x", false);
			bool y = Xml::getAttrBool(child, "y", false);
			flipSide(side, x, y);
			LOG_DEBUG << "Facade: Flip " << getSideName(side)
					  << ": " << x << " " << y << endl;
		}
		else
		{
			LOG_WARN << "Facade: Unknown element \""
					 << child->ValueStr() << "\"" << endl;
		}

		child = child->NextSiblingElement();
	}
}
