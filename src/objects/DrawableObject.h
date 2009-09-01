/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "Common.h"

#include "Config.h"

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

        virtual void draw() = 0;

        /// sets the name and osc address, call this after the Config::_listener
        /// root address has been set
        void setName(string name)
        {
            // set osc address relative to root in listener
            setOscRootAddress(Config::getListener().getOscRootAddress() + "/" + name);

            LOG << name << " " << getOscRootAddress() << endl;

            this->name = name;
        }

        string getName() {return name;}

    protected:

        /// process one osc message, derived objects should call this
        /// using DrawableObject::processOscMessage() to handle the base variables
        virtual bool processOscMessage(const osc::ReceivedMessage& m)
        {
            if((string) m.AddressPattern() == getOscRootAddress() + "/color" &&
                (string) m.TypeTags() == "iiii")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                color.R  = (arg++)->AsInt32();
                color.G  = (arg++)->AsInt32();
                color.B  = (arg++)->AsInt32();
                color.A  = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/color/R" &&
                (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                color.R  = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/color/G" &&
                (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                color.G  = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/color/B" &&
                (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                color.B  = (arg++)->AsInt32();
                return true;
            }
            else if((string) m.AddressPattern() == getOscRootAddress() + "/color/A" &&
                (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                color.A  = (arg++)->AsInt32();
                return true;
            }


            else if((string) m.AddressPattern() == getOscRootAddress() + "/visible"
                && (string) m.TypeTags() == "i")
            {
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bVisible = (bool) (arg++)->AsInt32();
                return true;
            }


            return false;
        }

        Color color;
        bool bVisible;
        string name;
};

#endif // DRAWABLE_OBJECT_H
