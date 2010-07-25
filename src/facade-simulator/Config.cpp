/*==============================================================================

	Config.cpp

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
#include "Config.h"

#include <tclap/tclap.h>

using namespace xml;
using namespace facade;

Config& Config::instance()
{
    static Config * pointerToTheSingletonInstance = new Config;
    return *pointerToTheSingletonInstance;
}

bool Config::parseCommandLine(int argc, char **argv)
{
	try
    {
        // the commandline parser
        TCLAP::CommandLine cmd("2d aec facade simulator", VERSION);
        
        
        // options to parse
        // short id, long id, description, required?, default value, short usage type description

        // commands to parse
        // name, description, required?, default value, short usage type description
        TCLAP::UnlabeledValueArg<string> fileCmd("xml", "facade mapping xml file to load", false, "", "file");

        // add args to parser (in reverse order)
        
        // add commands
        cmd.add(fileCmd);

        // parse the commandline
        cmd.parse(argc, argv);
		
		// load the mapping file (if one exists)
        if(fileCmd.getValue() != "")
        {
            _facade.setXmlFilename(fileCmd.getValue());
            LOG << "Config: loading \"" << _facade.getXmlFilename() << "\"" << endl;
    		_facade.loadXmlFile();
    		_facade.closeXmlFile();
        }
    }
    catch(TCLAP::ArgException &e)  // catch any exceptions
	{
	    LOG_ERROR << "CommandLine: " << e.error() << " for arg " << e.argId() << endl;
        return false;
    }

	return true;
}

/* ***** PRIVATE ***** */

Config::Config()
{}
