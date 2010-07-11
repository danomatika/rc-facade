/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef APP_H
#define APP_H

#include "Common.h"

#include "facade.h"

using namespace std;

class App : public visual::Application, public visual::UdpReceiver
{
    public:

        App();

        virtual ~App();

        bool init();

        void setup();

        void update();

        void draw();

        void cleanup();

        void keyPressed(SDLKey key, SDLMod mod);

    private:

        bool bRunning;  // running or paused?

        Facade& facade;

        visual::Image facadeImage;
        visual::Image facadeMask;
        
        visual::UdpReceiver receiver;

        unsigned int reloadTimestamp;
};

#endif // APP_H
