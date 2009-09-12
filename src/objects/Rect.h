#ifndef RECT_H
#define RECT_H

#include "Config.h"

#include "DrawableObject.h"

class Rect : public DrawableObject
{
    public:

        Rect(string name) : DrawableObject("rect"), pos(0, 0),
            width(1), height(1), bFilled(false)
        {
            // add variables to Xml
            addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
            addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);
            addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
            addXmlAttribute("height", "size", XML_TYPE_UINT, &height);
            addXmlAttribute("yesno", "filled", XML_TYPE_BOOL, &bFilled);

            setName(name);
        }

        void draw()
        {
            if(bVisible)
            {
                Config::getFacade().stroke(color);

                if(bFilled)
                    Config::getFacade().box(pos.x, pos.y, width, height);
                else
                    Config::getFacade().rect(pos.x, pos.y, width, height);
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


            if((string) m.AddressPattern() == getOscRootAddress() + "/position"
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


            else if((string) m.AddressPattern() == getOscRootAddress() + "/size"
                && (string) m.TypeTags() == "ii")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                width = (arg++)->AsInt32();
                height = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/size/width"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                width = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/size/height"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                height = (arg++)->AsInt32();
                return true;
            }


            else if((string) m.AddressPattern() == getOscRootAddress() + "/filled"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bFilled = (bool) (arg++)->AsInt32();
                return true;
            }


            return false;
        }

        vmml::Vector2i pos;
        unsigned int width, height;
        bool bFilled;
};


#endif // RECT_H
