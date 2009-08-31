/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef FACADE_APP_H
#define FACADE_APP_H

#include "Common.h"

#include "Config.h"
#include "SceneManager.h"

#include "Pixel.h"
#include "Line.h"
#include "Rect.h"

using namespace std;
using namespace visual;

class FacadeApp : public Application
{
    public:

        FacadeApp();

        virtual ~FacadeApp();

        void init();

        void setup();

        void update();

        void draw();

        void cleanup();

        void keyPressed(SDLKey key, SDLMod mod);

    protected:

    private:

        bool bRunning;  // running or paused?

        Facade& facade;
        OscListener& listener;
        SceneManager sceneManager;
};

#endif // FACADE_APP_H
