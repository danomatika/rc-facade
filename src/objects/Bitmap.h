#ifndef BITMAP_H
#define BITMAP_H

#include "Config.h"

#include "DrawableObject.h"

class Bitmap : public DrawableObject
{
    public:

        Bitmap(string name);

        void draw();
        void draw(int x, int y);

        void setBitmap(std::vector<bool> bitmap) {this->bitmap = bitmap;}

        void setDrawFromCenter(bool yesno) {bDrawFromCenter = yesno;}

        unsigned int getFrameTime() {return frameTime;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);
        bool writeXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& m);

        std::vector<bool> bitmap;   /// actual bitmap

        unsigned int frameTime;     /// how long to display in ms
        vmml::Vector2i pos;
        unsigned int width, height;
        bool bDrawFromCenter;       /// draw from the center using pos
};

#endif // BITMAP_H
