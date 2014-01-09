/*==============================================================================

	Util.h

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
#ifndef VISUAL_UTIL_H
#define VISUAL_UTIL_H

#include <string>
#include <sstream>
#include <iomanip>

namespace visual {

/**
	\class	Util
	\brief	a static class of Utility functions
*/
class Util
{
	public:
	
		/// \section String Conversion
		
		template <class T>
		static std::string toString(const T& value)
		{
			std::ostringstream out;
			out << value;
			return out.str();
		}

		template <class T>
		static std::string toString(const T& value, int precision)
		{
			std::ostringstream out;
			out << std::fixed << std::setprecision(precision) << value;
			return out.str();
		}
	
		/// \section Data Path
	
		/// append a the data path to a given path or filename
		static std::string toDataPath(std::string path, bool makeAbsolute=false);
		
		/// set the data path
		static void setDataPath(const std::string& path, bool makeAbsolute=false);
		
		/// get the current data path
		static std::string getDataPath();
		
		/// use the data path? if off, causes toDataPath to return the given string
		static void useDataPath(bool onoff); 
		
		/// \section Path Utils
		
		/// get the current working dir
		static std::string getCurrentDir();

		// returns the path to the executable
		static std::string getExecutablePath();
		
		/// is this an absolute path?
		static bool isAbsolutePath(const std::string& path);

		/// get the dir path minus the filename (if there is one)
		static std::string getDirPath(const std::string& path);
		
		/// get the filename minus the path
		static std::string getFileName(const std::string& path);
		
		/// make a path absolute
		static std::string makeAbsolutePath(std::string path);

	private:
	
		static bool bUsingDataPath;		///< are we using the data path?
		static std::string dataPath;	///< the data path (../../data default)
};

} // namespace

#endif // VISUAL_UTIL_H
