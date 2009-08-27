#ifndef FACADE_APP_H
#define FACADE_APP_H

#include "Common.h"

#include "facade/Facade.h"

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

        Facade facade;
};

#endif // FACADE_APP_H
