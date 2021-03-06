/*==============================================================================

Scene.cpp

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
#include "Scene.h"

#include "objects/Objects.h"

Scene::Scene(string name) : XmlObject("scene"), OscObject(""), _name(name), _background(0x00000)
{
	// attach variables to Xml
	addXmlAttribute("R", "background", XML_TYPE_BYTE, &_background.R);
	addXmlAttribute("G", "background", XML_TYPE_BYTE, &_background.G);
	addXmlAttribute("B", "background", XML_TYPE_BYTE, &_background.B);
	addXmlAttribute("A", "background", XML_TYPE_BYTE, &_background.A);

	addXmlAttribute("name", "scene", XML_TYPE_STRING, &_name);
}

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

void Scene::setup()
{
	for(unsigned int i = 0; i < _objectList.size(); ++i)
	{
		_objectList.at(i)->setup();
	}
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
			if((objName = Xml::getAttrString(child, "name")) != "")
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
			if((objName = Xml::getAttrString(child, "name")) != "")
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
			if((objName = Xml::getAttrString(child, "name")) != "")
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
			if((objName = Xml::getAttrString(child, "name")) != "")
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
			if((objName = Xml::getAttrString(child, "name")) != "")
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
		
		else if(child->ValueStr() == "image")
		{
			if((objName = Xml::getAttrString(child, "name")) != "")
			{
				LOG_DEBUG << "Scene \"" << _name << "\": Loading image \"" << objName << "\"" << std::endl;

				Image* i = new Image(objName);
				i->loadXml(child);
				addObject(i);
			}
			else
			{
				LOG_WARN << "Scene \"" << _name << "\": cannot load image without name, line "
						 << child->Row() << endl;
			}
		}

		else if(child->ValueStr() != "background")
		{
			LOG_WARN << "Scene \"" << _name << "\": ignoring unknown element \""
					 << child->ValueStr() << "\"" << endl;
		}


		child = child->NextSiblingElement();
	}

	return true;
}
