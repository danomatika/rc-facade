/*==============================================================================

SceneManager.cpp

rc-facade: a simple 2d graphics engine for the AEC facade

Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "SceneManager.h"

SceneManager::SceneManager() : XmlObject("facade"), OscObject(""), _currentScene(-1)
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

void SceneManager::clear(bool keepCurScene)
{
	/// delete all the objects
	for(unsigned int i = 0; i < _objectList.size(); ++i)
	{
		Scene* o = _objectList.at(i);
		removeXmlObject(o);
		delete o;
	}
	_objectList.clear();
	
	if(!keepCurScene)
	{
		_currentScene = 0;
	}
}

void SceneManager::nextScene()
{
	if(_objectList.empty())
		return;

	_currentScene++;

	if(_currentScene >= (int) _objectList.size())
	{
		_currentScene = 0;
	}

	LOG_DEBUG << "SceneManager: Changed to scene \"" << _objectList.at(_currentScene)->getName() << "\"" << std::endl;

	Config::instance().getFacade().setClearColor(_objectList.at(_currentScene)->getBackground());
}

void SceneManager::prevScene()
{
	if(_objectList.empty())
		return;

	_currentScene--;

	if(_currentScene < 0)
	{
		_currentScene = _objectList.size()-1;
	}

	LOG_DEBUG << "SceneManager: Changed to scene \"" << _objectList.at(_currentScene)->getName() << "\"" << std::endl;


	Config::instance().getFacade().setClearColor(_objectList.at(_currentScene)->getBackground());
}

void SceneManager::gotoScene(unsigned int num)
{
	if(_objectList.empty())
		return;

	if(_currentScene >= (int) _objectList.size())
	{
		LOG_WARN << "SceneManager: Cannot goto scene num " << num
		         << ", index out of range" << endl;
		return;
	}

	_currentScene = num;

	LOG_DEBUG << "SceneManager: Changed scene to \""
	          << _objectList.at(_currentScene)->getName() << "\""<< endl;

	Config::instance().getFacade().setClearColor(_objectList.at(_currentScene)->getBackground());
}

void SceneManager::gotoScene(string name)
{
	for(unsigned int i = 0; i < _objectList.size(); ++i)
	{
		if(name == _objectList.at(i)->getName())
		{
			_currentScene = i;

			LOG_DEBUG << "SceneManager: Changed scene to \""
			          << _objectList.at(_currentScene)->getName() << "\"" << endl;

			Config::instance().getFacade().setClearColor(_objectList.at(_currentScene)->getBackground());

			return;
		}
	}
}

void SceneManager::setup()
{
	// setup all scenes
	for(unsigned int i = 0; i < _objectList.size(); ++i)
	{
		_objectList.at(i)->setup();
	}

	// try to load the first scene
	if(_currentScene < 0)
		gotoScene(0);
}

void SceneManager::draw()
{
	if(_currentScene >= 0 && _currentScene < (int) _objectList.size())
	{
	   _objectList.at(_currentScene)->draw();
	}
}

void SceneManager::reload()
{
	closeXmlFile();
	clear(true);
	loadXmlFile();
	setup();
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
			if((name = Xml::getAttrString(child, "name")) != "")
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

	// try to load the first scene
	if(_currentScene < 0)
		gotoScene(0);

	return true;
}

/* ***** OSC CALLBACKS ***** */

bool SceneManager::processOscMessage(const osc::ReceivedMessage& message,
                                     const osc::MessageSource& source)
{
	if(_currentScene >= 0 && _currentScene < (int) _objectList.size())
	{
		return _objectList.at(_currentScene)->processOsc(message, source);
	}

	return false;
}
