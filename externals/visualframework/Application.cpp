/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Application.h"

#include "graphics/Font.h"

#define VISUAL_APP_SLEEP_MS 20

namespace visual {

Application::Application() : bDebug(false),
    _bRun(true), _frameRate(0), _ticks(0), _background(0, 0, 0, 255)
{
    _frameRateMs = 0; // no timing
    
    Font::initTTF();	// start font
}

Application::~Application()
{
	Font::cleanupTTF();	// stop font
}

/* ***** SETUP ***** */

void Application::init() {}

void Application::mainLoop()
{
	// start font

    // program main loop
    while(_bRun)
    {
        update();   // call the user update function
        _events();  // handle events and do framerate idling
        _draw();  // render a frame

        // update ticks
        _ticks = SDL_GetTicks();
    }
}

/* ***** UTIL ***** */

void Application::setFrameRate(float frameRate)
{
    if(frameRate < 0)
        return;

    _frameRate = frameRate;

    // no delay?
    if(frameRate == 0)
    {
        _frameRateMs = 0;
        return;
    }

    _frameRateMs = 1000/_frameRate;   // delay = 1000 ms / fps
}

/* ***** PRIVATE FUNCTIONS ***** */

void Application::_draw()
{
    // clear background
    SDL_FillRect(Graphics::getScreen(), 0,
        SDL_MapRGB(Graphics::getScreen()->format,
            _background.R, _background.G, _background.B));

    // user render function
    draw();

    // swap buffers
    SDL_Flip(Graphics::getScreen());
}

void Application::_events()
{
    // do message processing while waiting for next frame
    while(SDL_GetTicks() - _ticks < _frameRateMs)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch(event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    _bRun = false;
                    break;

                // check for keypresses
                case SDL_KEYDOWN:
                {
                    switch(event.key.state)
                    {
                        case SDL_PRESSED:
                            switch(event.key.keysym.sym)
                            {
                                // exit if ESCAPE is pressed
                                case SDLK_ESCAPE:
                                    _bRun = false;
                                    break;

                                case SDLK_RETURN:
                                    // toggle fullscreen on ALT+ENTER
                                    if(event.key.keysym.mod & KMOD_ALT)
                                        Graphics::toggleFullscreen();
                                    // don't break so SDLK_RETURN goes to keyPressed

                                default:
                                    keyPressed(event.key.keysym.sym, event.key.keysym.mod);
                                    break;
                            }
                            break;

                        case SDL_RELEASED:
                            keyReleased(event.key.keysym.sym, event.key.keysym.mod);
                            break;
                    }
                }

                // check for mouse movement
                case SDL_MOUSEMOTION:
                {
                    mouseMotion(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    switch(event.button.state)
                    {
                        case SDL_PRESSED:
                            mousePressed(event.button.button, event.button.x, event.button.y);
                            break;

                        case SDL_RELEASED:
                            mouseReleased(event.button.button, event.button.x, event.button.y);
                            break;
                    }
                    break;
                }

            } // end switch
        } // end of message processing

        SDL_Delay(VISUAL_APP_SLEEP_MS); // msec for the scheduler
    }
}

} // namespace
