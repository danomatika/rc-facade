#include "SceneManager.h"

SceneManager::SceneManager() :
    XmlObject("facade"), OscObject(""), _currentScene(0)
{}

SceneManager::~SceneManager()
{
    clear();
}

void SceneManager::addObject(Scene* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "SceneManager: Cannot add NULL object" << endl;
        return;
    }

    addXmlObject(object);

    _objectList.push_back(object);
}

void SceneManager::removeObject(Scene* object)
{
    if(object == NULL)
    {
        LOG_ERROR << "SceneManager: Cannot remove NULL object" << endl;
        return;
    }

    vector<Scene*>::iterator iter;
    iter = find(_objectList.begin(), _objectList.end(), object);
    if(iter != _objectList.end())
    {
        removeXmlObject((*iter));
        _objectList.erase(iter);
    }
}

void SceneManager::clear()
{
    /// delete all the objects
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        Scene* o = _objectList.at(i);
        removeXmlObject(o);
        delete o;
    }
    _objectList.clear();
}

void SceneManager::nextScene()
{
    _currentScene++;

    if(_currentScene >= (int) _objectList.size())
    {
        _currentScene = 0;
    }
}

void SceneManager::prevScene()
{
    _currentScene--;

    if(_currentScene < 0)
    {
        _currentScene = _objectList.size()-1;
    }
}

void SceneManager::gotoScene(unsigned int num)
{
    if(_currentScene >= (int) _objectList.size())
    {
        LOG_WARN << "SceneManager: Cannot goto scene num " << num
                 << ", index out of range" << endl;
        return;
    }

    _currentScene = num;

    LOG_DEBUG << "SceneManager: Changing scene to \""
              << _objectList.at(_currentScene)->getName() << endl;
}

void SceneManager::gotoScene(string name)
{
    for(unsigned int i = 0; i < _objectList.size(); ++i)
    {
        if(name == _objectList.at(i)->getName())
        {
            _currentScene = i;

            LOG_DEBUG << "SceneManager: Changing scene to \""
                      << _objectList.at(_currentScene)->getName() << "\"" << endl;

            return;
        }
    }
}

void SceneManager::draw()
{
    if(_currentScene >= 0 && _currentScene < (int) _objectList.size())
    {
       _objectList.at(_currentScene)->draw();
    }
}

/* ***** XML CALLBACKS ***** */

bool SceneManager::readXml(TiXmlElement* e)
{
    string name;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "scene")
        {
            if(Xml::getAttrString(child, "name", &name))
            {
                LOG_DEBUG << "SceneManager: Loading scene \"" << name << "\"" << std::endl;

                Scene* s = new Scene(name);
                s->loadXml(child);
                addObject(s);
            }
            else
            {

                LOG_WARN << "SceneManager: Cannot load scene without name, line "
                         << child->Row() << endl;
            }
        }

        child = child->NextSiblingElement();
    }

    return true;
}

/* ***** OSC CALLBACKS ***** */

bool SceneManager::processOscMessage(const osc::ReceivedMessage& m)
{
    if(_currentScene >= 0 && _currentScene < (int) _objectList.size())
    {
        return _objectList.at(_currentScene)->processOsc(m);
    }

    return false;
}
