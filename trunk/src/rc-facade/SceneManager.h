/*==============================================================================

	SceneManager.h

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
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Common.h"

#include "Config.h"
#include "Scene.h"

class SceneManager : public XmlObject, public OscObject
{
    public:

        SceneManager();
        virtual ~SceneManager();

        /// add an object
        void addObject(Scene* object);

        /// remove an object
        void removeObject(Scene* object);

        /// clears (deletes) all the objects in the list
        void clear(bool keepCurScene=false);

		// scene transport
        void nextScene();
        void prevScene();
        void gotoScene(unsigned int num);
        void gotoScene(string name);
        
        /// loads graphics resources
		void setup();

        /// draw all the objects in the list
        void draw();
        
        /// reload the scene file
        void reload();

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
                               const osc::MessageSource& source);

    private:

        int _currentScene;
        vector<Scene*> _objectList;
};

#endif // SCENE_MANAGER_H
