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

        bool processOscMessage(const osc::ReceivedMessage& message,
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


            else if(message.path() == getOscRootAddress() + "/size" &&
                	message.types() == "ii")
            {
                //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                width = message.asInt32(0);
                height = message.asInt32(1);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/size/width" &&
                	message.types() == "i")
            {
                //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                width = message.asInt32(0);
                return true;
            }
            else if(message.path() == getOscRootAddress() + "/size/height" &&
                	message.types() == "i")
            {
                //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                height = message.asInt32(0);
                return true;
            }


            else if(message.path() == getOscRootAddress() + "/filled" &&
            		message.types() == "i")
            {
                //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bFilled = message.asBool(0);
                return true;
            }


            return false;
        }

        vmml::Vector2i pos;
        unsigned int width, height;
        bool bFilled;
};


#endif // RECT_H