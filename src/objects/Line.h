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
                Config::getFacade().stroke(color);
                Config::getFacade().line(pos1.x, pos1.y, pos2.x, pos2.y);
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


            if((string) m.AddressPattern() == getOscRootAddress() + "/position1"
                && (string) m.TypeTags() == "ii")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos1.x = (arg++)->AsInt32();
                pos1.y = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position1/x"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos1.x = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position1/y"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos1.y = (arg++)->AsInt32();
                return true;
            }


            else if((string) m.AddressPattern() == getOscRootAddress() + "/position2"
                && (string) m.TypeTags() == "ii")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos2.x = (arg++)->AsInt32();
                pos2.y = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position2/x"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos2.x = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/position2/y"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                pos2.y = (arg++)->AsInt32();
                return true;
            }


            return false;
        }

        vmml::Vector2i pos1, pos2;
};

#endif // LINE_H
