#include "Image.h"

#include <SDL/SDL_image.h>

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
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    // detach variables from Xml
    removeXmlAttribute("R", "color");
    removeXmlAttribute("G", "color");
    removeXmlAttribute("B", "color");
    removeXmlAttribute("A", "color");
    removeXmlAttribute("width", "size");
    removeXmlAttribute("height", "size");

    setName(name);
}

Image::~Image()
{}

bool Image::loadFile(string filename)
{
	if(filename == "")
    	filename = this->filename;
       
//    if(!image(filename))
//    	return false;

    

    return true;
}

void Image::draw()
{
    draw(pos.x, pos.y);
}

void Image::draw(int x, int y)
{
/*
    if(bitmap == NULL)
        return;

    if(bVisible)
    {
        int xPos = x, yPos = y;

        if(bDrawFromCenter)
        {
            xPos = xPos - bitmap->w/2;
            yPos = yPos - bitmap->h/2;
        }

        for(int _y = 0; _y < image->h; ++_y)
        {
            for(int _x = 0; _x < image->w; ++_x)
            {
            	Config::instance().getFacade().stroke(bitmap.at(_y*width + _x));
                Config::instance().getFacade().pixel(xPos+_x, yPos+_y);
            }
        }
    }
    */
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
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        pos.x = message.asInt32(0);
        pos.y = message.asInt32(1);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/x" &&
    		message.types() == "i")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        pos.x = message.asInt32(0);
        return true;
    }
    else if(message.path() == getOscRootAddress() + "/position/y" &&
    		message.types() == "i")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        pos.y = message.asInt32(0);
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/center" &&
    		message.types() == "i")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        bDrawFromCenter = message.asBool(0);
        return true;
    }


    return false;
}
