/*==============================================================================

	Util.cpp

	visualframework: a simple 2d graphics framework
  
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
#include "Util.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include <windows.h>
#elif defined( __APPLE_CC__)
	#include <mach-o/dyld.h>
#endif
#include <unistd.h>

namespace visual {

bool Util::bUsingDataPath = true;
std::string Util::dataPath = "../../data/";

//
//	data path code from OpenFrameworks: http://openframeworks.cc
//
std::string Util::toDataPath(std::string path, bool makeAbsolute)
{
	if(bUsingDataPath)
	{
		// check if absolute path has been passed or if data path has already been applied
		if(path.length() == 0 ||
		   (!isAbsolutePath(path) && path.substr(0, dataPath.length()) != dataPath))
		{
			path = dataPath + path;
		}

		if(makeAbsolute)
		{
			path = makeAbsolutePath(path);
		}
	}
	return path;	
}

void Util::setDataPath(const std::string& path, bool makeAbsolute)
{
	if(makeAbsolute)
		dataPath = makeAbsolutePath(path);
	else
		dataPath = path;
	
	// add trailing slash
	if(dataPath.length() > 0 && dataPath.substr(dataPath.length()-2, dataPath.length()-1) != "/")
		dataPath += "/";
}

std::string Util::getDataPath()
{
	return dataPath;
}

void Util::useDataPath(bool onoff)
{
	bUsingDataPath = onoff;
}

std::string Util::getCurrentDir()
{
	char currDir[1024];
	getcwd(currDir, 1024);
	return (std::string) currDir;
}

// from http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
std::string Util::getExecutablePath()
{
	char path[1024];
	
	#if defined( __WIN32__ ) || defined( _WIN32 )
		// Will contain exe path
		HMODULE hModule = GetModuleHandle(NULL);
		if(hModule != NULL)
		{
			// When passing NULL to GetModuleHandle, it returns handle of exe itself
			GetModuleFileName(hModule, path, (sizeof(path)));
		}
		else
			return "";
	#elif defined( __APPLE_CC__)
		uint32_t size = sizeof(path);
		if(_NSGetExecutablePath(path, &size) != 0)
			return "";
	#else // LINUX
		readlink("/proc/self/exe", path, sizeof(path));
	#endif
	
	return (std::string) path;
}

bool Util::isAbsolutePath(const std::string& path)
{
	if(path.length() == 0)
		return false;
	
	if(path.substr(0,1) == "/" || path.substr(1,1) == ":")
		return true;
	return false;
}

std::string Util::getDirPath(const std::string& path)
{
	if(path.length() == 0 || path.substr(path.length()-2, path.length()-1) == "/")
		return path;
		
	std::string::size_type loc = path.rfind("/");
	if(loc != std::string::npos)
		return path.substr(0, loc);
	return path;
}
		
std::string Util::getFileName(const std::string& path)
{
	if(path.length() == 0 || path.substr(path.length()-2, path.length()-1) == "/")
		return "";
		
	std::string::size_type loc = path.rfind("/");
	if(loc != std::string::npos)
		return path.substr(loc+1, path.length()-1);
	return "";
}

std::string Util::makeAbsolutePath(std::string path)
{
	if(path.length() == 0 || isAbsolutePath(path))
		return path;
	
	#ifndef _MSC_VER // LINUX, MAC
		char currDir[1024];
		path = "/"+path;
		path = getcwd(currDir, 1024)+path;
	#else 
		char currDir[1024];
		path = "\\"+path;
		path = _getcwd(currDir, 1024)+path;
		std::replace(path.begin(), path.end(), '/', '\\' ); // fix any unixy paths...
	#endif
	
	return path;
}

} // namespace
