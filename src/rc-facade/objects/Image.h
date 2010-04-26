#ifndef IMAGE_H
#define IMAGE_H


#include "Config.h"

#include "DrawableObject.h"

class Image : public DrawableObject
{
    public:

        Image(string name);
        ~Image();

        void draw();
        void draw(int x, int y);

        bool loadFile(string filename);

        void setDrawFromCenter(bool yesno) {bDrawFromCenter = yesno;}

        unsigned int getFrameTime() {return frameTime;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);
        bool writeXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
        					   const osc::MessageSource& source);

        vector<visual::Color> bitmap;	/// bitmap of colors

		string filename;			/// filename to load
        unsigned int frameTime;     /// how long to display in ms
        vmml::Vector2i pos;
        unsigned int width, height;
        bool bDrawFromCenter;       /// draw from the center using pos
};

#endif // IMAGE_H
