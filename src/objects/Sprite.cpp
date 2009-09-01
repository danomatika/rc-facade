#include "Sprite.h"

Sprite::Sprite(string name) : DrawableObject("sprite"),
    pos(0, 0), width(1), height(1), bDrawFromCenter(false),
    currentFrame(0), timestamp(0)
{
    // add variables to Xml
    addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);

    addXmlAttribute("width", "size", XML_TYPE_UINT, &width);
    addXmlAttribute("height", "size", XML_TYPE_UINT, &height);

    addXmlAttribute("yesno", "animate", XML_TYPE_BOOL, &bAnimate);
    addXmlAttribute("yesno", "center", XML_TYPE_BOOL, &bDrawFromCenter);

    // detach variables from Xml
    removeXmlAttribute("R", "color");
    removeXmlAttribute("G", "color");
    removeXmlAttribute("B", "color");
    removeXmlAttribute("A", "color");

    setName(name);

    timestamp = Graphics::getMillis();
}

Sprite::~Sprite()
{
    clear();
}

void Sprite::addBitmap(Bitmap* bitmap)
{
    if(bitmap == NULL)
    {
        LOG_ERROR << "BitmapManager: Cannot add NULL bitmap" << endl;
        return;
    }

    addXmlObject(bitmap);

    bitmapList.push_back(bitmap);
}

void Sprite::removeBitmap(Bitmap* bitmap)
{
    if(bitmap == NULL)
    {
        LOG_ERROR << "BitmapManager: Cannot remove NULL bitmap" << endl;
        return;
    }

    vector<Bitmap*>::iterator iter;
    iter = find(bitmapList.begin(), bitmapList.end(), bitmap);
    if(iter != bitmapList.end())
    {
        removeXmlObject((*iter));
        bitmapList.erase(iter);
    }
}

void Sprite::clear()
{
    /// delete all the bitmaps
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        Bitmap* o = bitmapList.at(i);
        delete o;
    }
    bitmapList.clear();
}

void Sprite::nextFrame()
{
    currentFrame++;

    if(currentFrame >= (int) bitmapList.size())
    {
        currentFrame = 0;
    }
}

void Sprite::prevFrame()
{
    currentFrame--;

    if(currentFrame < 0)
    {
        currentFrame = bitmapList.size()-1;
    }
}

void Sprite::gotoFrame(unsigned int num)
{
    if(currentFrame >= (int) bitmapList.size())
    {
        LOG_WARN << "Sprite: Cannot goto frame num " << num
                 << ", index out of range" << endl;
        return;
    }

    currentFrame = num;
}

void Sprite::gotoFrame(string name)
{
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        if(name == bitmapList.at(i)->getName())
        {
            currentFrame = i;

            return;
        }
    }
}

void Sprite::draw()
{
    if(bitmapList.empty())
        return;

    if(bAnimate)
    {
        // go to next frame if time has elapsed
        if(Graphics::getMillis() - timestamp > bitmapList.at(currentFrame)->getFrameTime())
        {
            nextFrame();
            timestamp = Graphics::getMillis();
        }
    }

    if(bVisible)
    {
        if(currentFrame >= 0 && currentFrame < (int) bitmapList.size())
        {
            Bitmap* b = bitmapList.at(currentFrame);
            b->setDrawFromCenter(bDrawFromCenter);
            b->draw(pos.x, pos.y);
        }
    }
}

bool Sprite::readXml(TiXmlElement* e)
{
    string name;
LOG << "fdf: " << e->ValueStr() << endl;
    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "bitmap")
        {
            LOG << "fhshfjdhfd" << endl;
            if(Xml::getAttrString(child, "name", &name))
            {
                LOG_DEBUG << "Sprite: Loading bitmap \"" << name << "\"" << std::endl;

                Bitmap* b = new Bitmap(name);
                b->loadXml(child);
                addBitmap(b);
            }
            else
            {

                LOG_WARN << "Bitmap: Cannot load bitmap without name, line "
                         << child->Row() << endl;
            }
        }

        child = child->NextSiblingElement();
    }

    return true;
}

bool Sprite::processOscMessage(const osc::ReceivedMessage& m)
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


    else if((string) m.AddressPattern() == getOscRootAddress() + "/animate"
        && (string) m.TypeTags() == "i")
    {
        osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        bAnimate= (bool) (arg++)->AsInt32();
        return true;
    }


    return false;
}
