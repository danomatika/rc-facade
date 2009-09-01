#include "Bitmap.h"

#include <sstream>

Bitmap::Bitmap(string name) : DrawableObject("bitmap"), frameTime(0),
    pos(0, 0), width(1), height(1), bDrawFromCenter(false)
{
    // add variables to Xml
    addXmlAttribute("frametime", "bitmap", XML_TYPE_UINT, &frameTime);

    addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);

    addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
    addXmlAttribute("height", "size", XML_TYPE_UINT, &height);

    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    setName(name);
}

void Bitmap::draw()
{
    draw(pos.x, pos.y);
}

void Bitmap::draw(int x, int y)
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

        Config::getFacade().stroke(color);

        for(unsigned int _y = 0; _y < height; ++_y)
        {
            for(unsigned int _x = 0; _x < width; ++_x)
            {
                if(bitmap.at(_y*width + _x))
                    Config::getFacade().pixel(xPos+_x, yPos+_y);
            }
        }
    }
}

bool Bitmap::readXml(TiXmlElement* e)
{
    TiXmlElement* child = Xml::getElement(e, "frame");
    if(child != NULL)
    {
        stringstream frame(Xml::getText(child));
        string line;
        unsigned int numPix= 0;

        // read through all the chars
        while(!frame.eof())
        {
            frame >> line;
            cout << "       " << line << endl;

            stringstream chars(line);

            char c;
            chars >> c;
            while(!chars.eof())
            {
                switch(c)
                {
                    case '*':   // filled
                        bitmap.push_back(true);
                        numPix++;
                        break;
                    case '-':   // empty
                        bitmap.push_back(false);
                        numPix++;
                        break;
                    default:
                        break;
                }
                chars >> c;
            }
        }

        // correct size?
        if(numPix != width*height)
        {
            LOG_WARN << "Bitmap: Not enough pixels in frame: " << numPix
                     << ", need " << width*height << std::endl;
            bitmap.clear();
            return false;
        }
    }

    return true;
}

bool Bitmap::writeXml(TiXmlElement* e)
{
    stringstream frame;
    frame << std::endl;  // endl

    // read through all the chars
    for(unsigned int y = 0; y < height; ++y)
    {
        for(unsigned int x = 0; x < width; ++x)
        {
            if(bitmap[y*width + x])
                frame << '*';   // filled
            else
                frame << '-';      // empty
        }
        frame << std::endl;  // endl
    }

    return true;
}

bool Bitmap::processOscMessage(const osc::ReceivedMessage& m)
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


    else if((string) m.AddressPattern() == getOscRootAddress() + "/center"
        && (string) m.TypeTags() == "i")
    {
        osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        bDrawFromCenter= (bool) (arg++)->AsInt32();
        return true;
    }


    return false;
}
