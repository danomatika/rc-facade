#include "Scene.h"

#include "objects/Objects.h"

Scene::Scene(string name) : XmlObject("scene"), OscObject(""), _name(name)
{}

Scene::~Scene()
{
    clear();
}

void Scene::addObject(DrawableObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Scene \"" << _name << "\": Cannot add NULL object" << endl;
        return;
    }

    addXmlObject(object);
    addOscObject(object);

    _objectList.push_back(object);
}

void Scene::removeObject(DrawableObject* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "Scene \"" << _name << "\": Cannot remove NULL object" << endl;
        return;
    }

    vector<DrawableObject*>::iterator iter;
    iter = find(_objectList.begin(), _objectList.end(), object);
    if(iter != _objectList.end())
    {
        removeXmlObject((*iter));
        removeOscObject((*iter));

        _objectList.erase(iter);
    }
}

void Scene::clear()
{
    /// delete all the objects
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        DrawableObject* o = _objectList.at(i);

        removeXmlObject(o);
        removeOscObject(o);

        delete o;
    }
    _objectList.clear();
}

void Scene::draw()
{
    vector<DrawableObject*>::iterator iter;
    for(iter = _objectList.begin(); iter != _objectList.end(); ++iter)
    {
        // remove any NULL objects
        if((*iter) == NULL)
        {
            _objectList.erase(iter);
            LOG_ERROR << "Scene \"" << _name << "\": Removed NULL object" << endl;
        }
        else
            (*iter)->draw();
    }
}

/* ***** XML CALLBACKS ***** */

bool Scene::readXml(TiXmlElement* e)
{
    string objName;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "pixel")
        {
            if(Xml::getAttrString(child, "name", &objName))
            {
                LOG_DEBUG << "Scene \"" << _name << "\": Loading pixel \"" << objName << "\"" << std::endl;

                Pixel* p = new Pixel(objName);
                p->loadXml(child);
                addObject(p);
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load pixel without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "line")
        {
            if(Xml::getAttrString(child, "name", &objName))
            {
                LOG_DEBUG << "Scene \"" << _name << "\": Loading line \"" << objName << "\"" << std::endl;

                Line* l = new Line(objName);
                l->loadXml(child);
                addObject(l);
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load line without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "rect")
        {
            if(Xml::getAttrString(child, "name", &objName))
            {
                LOG_DEBUG << "Scene \"" << _name << "\": Loading rect \"" << objName << "\"" << std::endl;

                Rect* r = new Rect(objName);
                r->loadXml(child);
                addObject(r);
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load rect without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "bitmap")
        {
            if(Xml::getAttrString(child, "name", &objName))
            {
                LOG_DEBUG << "Scene \"" << _name << "\": Loading bitmap \"" << objName << "\"" << std::endl;

                Bitmap* b = new Bitmap(objName);
                b->loadXml(child);
                addObject(b);
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load bitmap without name, line "
                         << child->Row() << endl;
            }
        }

        else if(child->ValueStr() == "sprite")
        {
            if(Xml::getAttrString(child, "name", &objName))
            {
                LOG_DEBUG << "Scene \"" << _name << "\": Loading sprite \"" << objName << "\"" << std::endl;

                Sprite* s = new Sprite(objName);
                s->loadXml(child);
                addObject(s);
            }
            else
            {
                LOG_WARN << "Scene \"" << _name << "\": cannot load sprite without name, line "
                         << child->Row() << endl;
            }
        }

        child = child->NextSiblingElement();
    }

    return true;
}
