#ifndef SPRITE_H
#define SPRITE_H

#include "Config.h"

#include "DrawableObject.h"
#include "Bitmap.h"

class Sprite : public DrawableObject
{
    public:

        Sprite(string name);
        ~Sprite();

        void addBitmap(Bitmap* bitmap);
        void removeBitmap(Bitmap* bitmap);
        void clear();

        void nextFrame();
        void prevFrame();
        void gotoFrame(unsigned int num);
        void gotoFrame(string name);

        void draw();

        void setDrawFromCenter(bool yesno);
        void setDrawAllLayers(bool yesno) {bDrawAllLayers = yesno;}

    protected:

        /* ***** XML CALLBACKS ***** */

        bool readXml(TiXmlElement* e);

        /* ***** OSC CALLBACKS ***** */

        bool processOscMessage(const osc::ReceivedMessage& message,
        					   const osc::MessageSource& source);

        std::vector<Bitmap*> bitmapList;

        vmml::Vector2i pos;
        bool bAnimate;
        bool bLoop;
        bool bPingPong;
        bool bDrawFromCenter;
        bool bDrawAllLayers;

        int currentFrame;
        unsigned int timestamp;
        bool bForward;  /// advance frames?
};

#endif // SPRITE_H
