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

        /// draw all the objects in the list
        void draw();

        /* ***** UTIL ***** */

        string getName() {return _name;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

    private:

        string _name;
        vector<DrawableObject*> _objectList;
};

#endif // SCENE_H
