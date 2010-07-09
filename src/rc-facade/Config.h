/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"

#include <facade/Facade.h>

/**
    \class  Config
    \brief  global, per-application instance state variable container class

    implemented as a singleton class following:
    http://en.wikipedia.org/wiki/Singleton_pattern

    no initialization is needed, just use equt::Config::instance() to access
    member functions, data
**/
class Config : public xml::XmlObject
{
    public:

		/**
            \brief singleton data access
            \return a reference to itself

            creates a new object on the first call
        **/
        static Config& instance();
        
        /**
        	\brief	parse the commandline options
        */
        bool parseCommandLine(int argc, char **argv);
        
        /* ***** VARIABLES ***** */
        
        std::string file;	///< facade xml file to load

		/* **** OBJECTS ***** */

		/// setup the facade object
        inline void setupFacade(string ip, unsigned int port=8080)
        {
            _facade.setup(ip, port);
        }

		/// setup the osc receiver
        inline void setupReceiver(unsigned int port)
        {
            _oscReceiver.setup(port);
        }

		/// get the facade object
        Facade& getFacade() {return _facade;}
        
        /// get the osc reciever
        OscReceiver& getReceiver() {return _oscReceiver;}

	protected:
    
    	/// xml read callback
        bool readXml(TiXmlElement* e);

    private:

        Facade _facade;				///< the facade object
        OscReceiver _oscReceiver;	///< the osc recviever
        
        // hide all the constructors, copy functions here
        Config();                       // cannot create
        //Config(const Config& from) {}	// not copyable
        virtual ~Config() {}           	// cannot destroy
        void operator =(Config& from) {}// not copyable
};

#endif // CONFIG_H
