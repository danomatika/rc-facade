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

        bool processOscMessage(const osc::ReceivedMessage& m);

        SDL_Surface* image;         /// contians pixel data

        unsigned int frameTime;     /// how long to display in ms
        vmml::Vector2i pos;
        bool bDrawFromCenter;       /// draw from the center using pos
};

#endif // IMAGE_H
