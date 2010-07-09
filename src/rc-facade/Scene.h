#ifndef SCENE_H
#define SCENE_H

#include "Common.h"

#include "objects/DrawableObject.h"

class Scene : public XmlObject, public OscObject
{
    public:

        Scene(string name);
        virtual ~Scene();

        /// add an object
        void addObject(DrawableObject* object);

        /// remove an object
        void removeObject(DrawableObject* object);

        /// clears (deletes) all the objects in the list
        void clear();
        
        /// setup resources
        void setup();

        /// draw all the objects in the list
        void draw();

        /* ***** UTIL ***** */

        inline string getName() {return _name;}

        inline visual::Color getBackground() {return _background;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

    private:

        string _name;
        vector<DrawableObject*> _objectList;
        visual::Color _background;
};

#endif // SCENE_H
