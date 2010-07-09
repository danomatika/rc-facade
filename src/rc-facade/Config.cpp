/*==============================================================================
    2009 Dan Wilcox <danomatika@gmail.com>
==============================================================================*/
#include "Config.h"

#include <tclap/tclap.h>

//Facade      Config::_facade;
//OscReceiver Config::_oscReceiver;

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

        // commands to parse
        // name, description, required?, default value, short usage type description
        TCLAP::UnlabeledValueArg<string> fileCmd("xml", "facade xml file to load", false, "", "file");

        // add args to parser (in reverse order)
        
        // add commands
        cmd.add(fileCmd);

        // parse the commandline
        cmd.parse(argc, argv);

        // set variables
        if(fileCmd.getValue() != "")
        {
            file = fileCmd.getValue();
        }
    }
    catch(TCLAP::ArgException &e)  // catch any exceptions
	{
	    LOG_ERROR << "CommandLine: " << e.error() << " for arg " << e.argId() << endl;
        return false;
    }

	return true;
}

/* ***** PROTECTED ***** */

bool Config::readXml(TiXmlElement* e)
{
	return false;
/*
    string name;

    TiXmlElement* child = e->FirstChildElement();
    while(child != NULL)
    {
        if(child->ValueStr() == "setup")
        {
            if((name = Xml::getAttrString(child, "name")) != "")
            {
                LOG_DEBUG << "SceneManager: Loading scene \"" << name << "\"" << std::endl;

                Scene* s = new Scene(name);
                s->loadXml(child);
                addObject(s);
            }
            else
            {

                LOG_WARN << "SceneManager: Cannot load scene without name, line "
                         << child->Row() << endl;
            }
        }

        child = child->NextSiblingElement();
    }

    // try to load the first scene
    if(_currentScene < 0)
    	gotoScene(0);

    return true;
    */
}

/* ***** PRIVATE ***** */

Config::Config() : XmlObject("facade"), file("")
{}
