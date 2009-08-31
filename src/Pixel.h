/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef PIXEL_H
#define PIXEL_H

#include "Config.h"

#include "DrawableObject.h"

class Pixel : public DrawableObject
{
    public:

        Pixel(string name) : DrawableObject("pixel"), pos(0, 0)
        {
            // add variables to Xml
            addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
            addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);

            setName(name);
        }

        void draw()
        {
            if(bVisible)
            {
                Config::getFacade().stroke(color);
                Config::getFacade().pixel(pos.x, pos.y);
            }
        }

    protected:

        bool processOscMessage(const osc::ReceivedMessage& m)
        {
            // call the base class
            if(DrawableObject::processOscMessage(m))
            {
                return true;
            }


            else if((string) m.AddressPattern() == getOscRootAddress() + "/position"
                && (string) m.TypeTags() == "ii")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos.x = (arg++)->AsInt32();
                pos.y = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position/x"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos.x = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position/y"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos.y = (arg++)->AsInt32();
                return true;
            }


            return false;
        }

        vmml::Vector2i pos;
};

#endif // PIXEL_H
