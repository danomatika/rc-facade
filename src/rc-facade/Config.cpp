/*==============================================================================

	Config.cpp

	rc-facade: a simple 2d graphics engine for the AEC facade
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

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
        TCLAP::CommandLine cmd("simple aec facade rendering engine", VERSION);
        
        // options to parse
        // short id, long id, description, required?, default value, short usage type description
        TCLAP::ValueArg<string> ipOpt("i", "ip", (string) "IP address to send to; default is '"+sendingIp+"'", false, sendingIp, "string");
		TCLAP::ValueArg<string> mappingOpt("m", "mapping", (string) "facade mapping xml file", false, "", "string");

		stringstream itoa;
        itoa << listeningPort;
		TCLAP::ValueArg<int> 	portOpt("p","port", (string) "Port to listen on; default is '"+itoa.str()+"'", false, listeningPort, "int");
     
        // commands to parse
        // name, description, required?, default value, short usage type description
        TCLAP::UnlabeledValueArg<string> fileCmd("xml", "facade xml file to load", false, "", "file");

        // add args to parser (in reverse order)
		cmd.add(mappingOpt);
        cmd.add(portOpt);
        cmd.add(ipOpt);
        
        // add commands
        cmd.add(fileCmd);

        // parse the commandline
        cmd.parse(argc, argv);

        // load the config file (if one exists)
        if(fileCmd.getValue() != "")
        {
            setXmlFilename(fileCmd.getValue());
            LOG << "Config: loading \"" << getXmlFilename() << "\"" << endl;
    		loadXmlFile();
    		closeXmlFile();
        }
		
		// load the mapping file (if one exists)
		if(mappingOpt.isSet())
		{
			_facade.setXmlFilename(mappingOpt.getValue());
			LOG << "Config: loading mapping \"" << _facade.getXmlFilename() << "\"" << endl;
			_facade.loadXmlFile();
			_facade.closeXmlFile();
		}
        
        // set the variables
        if(ipOpt.isSet())		 sendingIp = ipOpt.getValue();
        if(portOpt.isSet()) 	 listeningPort = portOpt.getValue();
    }
    catch(TCLAP::ArgException &e)  // catch any exceptions
	{
	    LOG_ERROR << "CommandLine: " << e.error() << " for arg " << e.argId() << endl;
        return false;
    }

	return true;
}

void Config::print()
{        
    LOG << "sending ip: " << sendingIp << endl
		<< "listening port:	" << listeningPort << endl
        << "listening address: " << _oscReceiver.getOscRootAddress() << endl;
}

/* ***** PROTECTED ***** */

bool Config::readXml(TiXmlElement* e)
{
	return false;
}

/* ***** PRIVATE ***** */

Config::Config() : XmlObject("facade"), listeningPort(7000), sendingIp("127.0.0.1")
{
	addXmlObject(&_facade);
}
