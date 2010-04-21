/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"

#include <facade/Facade.h>

class Config
{
    public:

        static void setupFacade(string ip, unsigned int port=8080)
        {
            _facade.setup(ip, port);
        }

        static void setupReceiver(unsigned int port)
        {
            _oscReceiver.setup(port);
        }

        static Facade& getFacade() {return _facade;}
        static OscReceiver& getReceiver() {return _oscReceiver;}

    private:

        Config() {}                       // cannot create
        Config(const Config& from) {}     // not copyable
        virtual ~Config() {}              // cannot destroy
        void operator =(Config& from) {}   // not copyable

        static Facade _facade;
        static OscReceiver _oscReceiver;
};

#endif // CONFIG_H
