/*==============================================================================

	Config.h

	facade-simulator: a simple 2d simulator for the AEC facade
  
	Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"

#include "../common/Facade.h"

/**
    \class  Config
    \brief  global, per-application instance state variable container class

    implemented as a singleton class following:
    http://en.wikipedia.org/wiki/Singleton_pattern

    no initialization is needed, just use equt::Config::instance() to access
    member functions, data
**/
class Config
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

		/* **** OBJECTS ***** */

		/// get the facade object
        Facade& getFacade() {return _facade;}

    private:

        Facade _facade;				///< the facade object
        
        // hide all the constructors, copy functions here
        Config();                       // cannot create
        //Config(const Config& from) {}	// not copyable
        virtual ~Config() {}           	// cannot destroy
        void operator =(Config& from) {}// not copyable
};

#endif // CONFIG_H
