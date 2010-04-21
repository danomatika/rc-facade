#include "Sprite.h"

Sprite::Sprite(string name) : DrawableObject("sprite"),
    pos(0, 0), bAnimate(true), bLoop(true), bPingPong(true),
    bDrawFromCenter(false), bDrawAllLayers(false),
    currentFrame(0), timestamp(0), bForward(true)
{
    // add variables to Xml
    addXmlAttribute("x", "position", XML_TYPE_INT, &pos.x);
    addXmlAttribute("y", "position", XML_TYPE_INT, &pos.y);
    addXmlAttribute("animate", "animation", XML_TYPE_BOOL, &bAnimate);
    addXmlAttribute("loop", "animation",XML_TYPE_BOOL, &bAnimate);
    addXmlAttribute("pingpong", "animation",XML_TYPE_BOOL, &bAnimate);
    addXmlAttribute("drawFromCenter", "drawing",XML_TYPE_BOOL, &bDrawFromCenter);
    addXmlAttribute("drawAllLayers", "drawing", XML_TYPE_BOOL, &bDrawAllLayers);

    // detach variables from Xml
    removeXmlAttribute("R", "color");
    removeXmlAttribute("G", "color");
    removeXmlAttribute("B", "color");
    removeXmlAttribute("A", "color");
    removeXmlAttribute("width", "size");
    removeXmlAttribute("height", "size");

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
        Bitmap* b = bitmapList.at(i);
        delete b;
    }
    bitmapList.clear();
}

void Sprite::nextFrame()
{
    if(bitmapList.size() < 2)
        return;

    currentFrame++;

    if(currentFrame >= (int) bitmapList.size())
    {
        if(bPingPong)
        {
            bForward = false;
            currentFrame = bitmapList.size()-2;
        }
        else
         currentFrame = 0;
    }
}

void Sprite::prevFrame()
{
    if(bitmapList.size() < 2)
        return;

    currentFrame--;

    if(currentFrame < 0)
    {
        if(bPingPong)
        {
            bForward = true;
            currentFrame = 1;
        }
        else
        {
            currentFrame = bitmapList.size()-1;
        }
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

    // animate frames?
    if(bAnimate)
    {
        // go to next frame if time has elapsed
        if(Graphics::getMillis() - timestamp > bitmapList.at(currentFrame)->getFrameTime())
        {
            if(bForward)
                nextFrame();
            else
                prevFrame();
            timestamp = Graphics::getMillis();
        }
    }

    // draw frame(s)?
    if(bVisible)
    {
        if(bDrawAllLayers)
        {
            for(unsigned int i = 0; i < bitmapList.size(); ++i)
            {
                Bitmap* b = bitmapList.at(i);
                b->draw(pos.x, pos.y);
            }
        }
        else if(currentFrame >= 0 && currentFrame < (int) bitmapList.size())
        {
            Bitmap* b = bitmapList.at(currentFrame);
            b->draw(pos.x, pos.y);
        }
    }
}

void Sprite::setDrawFromCenter(bool yesno)
{
    for(unsigned int i = 0; i < bitmapList.size(); ++i)
    {
        Bitmap* b = bitmapList.at(i);
        b->setDrawFromCenter(bDrawFromCenter);
    }
}

bool Sprite::readXml(TiXmlElement* e)
{
    string name;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "bitmap")
        {
            LOG << "fhshfjdhfd" << endl;
            if((name = Xml::getAttrString(child, "name")) != "")
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

    // init all loaded bitmaps draw settings
    setDrawFromCenter(bDrawFromCenter);

    return true;
}

bool Sprite::processOscMessage(const osc::ReceivedMessage& message,
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
       // osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        pos.y = message.asInt32(0);
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/center" &&
    		message.types() == "i")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        bDrawFromCenter= (bool) message.asInt32(0);
        return true;
    }


    else if(message.path() == getOscRootAddress() + "/animate" &&
    		message.types() == "i")
    {
        //osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
        bAnimate= (bool) message.asInt32(0);
        return true;
    }


    return false;
}
