#include "Image.h"

#include <SDL/SDL_image.h>

#include <sstream>

Image::Image(string name) : DrawableObject("image"), frameTime(0),
    pos(0, 0), bDrawFromCenter(false)
{
    // add variables to Xml
    addXmlAttribute("name", "image", XML_TYPE_STRING, &name);
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
{
    if(image != NULL)
    {
        SDL_FreeSurface(image);
    }
}

bool Image::loadFile(string filename)
{
    if(image != NULL)
    {
        SDL_FreeSurface(image);
    }

    image = IMG_Load(filename.c_str());
    if(image == NULL)
    {

        return false;
    }

    return true;
}

void Image::draw()
{
    draw(pos.x, pos.y);
}

void Image::draw(int x, int y)
{
    if(image == NULL)
        return;

    if(bVisible)
    {
        int xPos = x, yPos = y;

        if(bDrawFromCenter)
        {
            xPos = xPos - image->w/2;
            yPos = yPos - image->h/2;
        }

        Config::getFacade().stroke(color);

        for(int _y = 0; _y < image->h; ++_y)
        {
            for(int _x = 0; _x < image->w; ++_x)
            {

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
