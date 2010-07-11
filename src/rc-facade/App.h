/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef APP_H
#define APP_H

#include "Common.h"

#include "SceneManager.h"

using namespace std;

class App : public visual::Application, public OscObject
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

    protected:

        /// osc callback
        bool processOscMessage(const osc::ReceivedMessage& message,
								  const osc::MessageSource& source);

    private:

        bool bRunning;  // running or paused?

        Facade& facade;
        OscReceiver& receiver;
        SceneManager sceneManager;
        
        visual::Image facadeImage;
        visual::Image facadeMask;

        unsigned int reloadTimestamp;
};

#endif // APP_H
