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
