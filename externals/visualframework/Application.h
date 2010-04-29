/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_APPLICATION_H
/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#define VISUAL_APPLICATION_H

#include "Common.h"

namespace visual {

class Application
{
    public:

        Application();
        virtual ~Application();

        /* ***** SETUP ***** */

        /// initialization, call before creating sdl window
        virtual void init();

        /// sdl resource setup, call after creating sdl window
        virtual void setup() = 0;

        /// start the main run loop
        void mainLoop();

        /* ***** MAIN CALLBACKS ***** */

        virtual void update() = 0;

        virtual void draw() = 0;

        virtual void cleanup() = 0;

        /* ***** INPUT CALLBACKS ***** */

        virtual void keyPressed(SDLKey key, SDLMod mod) {}

        virtual void keyReleased(SDLKey key, SDLMod mod) {}

        virtual void mousePressed(int button, int x, int y) {}

        virtual void mouseReleased(int button, int x, int y) {}

        virtual void mouseMotion(int x, int y, int xRel, int yRel) {}

        /* ***** UTIL ***** */

        /// set the target framerate
        void setFrameRate(float frameRate);

        Color& getBackground() {return _background;}
        void setBackground(Color color) {_background = color;}
        void setBackground(unsigned int color) {_background.set(color);}

        inline bool getDebug() {return bDebug;}
        inline void setDebug(bool yesno) {bDebug = yesno;}

        /// tell mainLoop to exit
        inline void stop() {_bRun = false;}

    protected:

        bool bDebug;    /// is debug mode on?

    private:

        // processes sdl events to input callbacks
        void _events();

        // main sdl loop, calls draw, update, etc
        void _draw();

        bool _bRun;          /// is the main loop running?
        float _frameRate;    /// frame rate target in FPS
        float _frameRateMs;  /// frame rate delay in ms
        Uint32 _ticks;       /// SDL ticks for frame rate timer
        Color _background;   /// back ground color
};

} // namespace

#endif // VISUAL_APPLICATION_H
