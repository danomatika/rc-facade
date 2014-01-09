/*==============================================================================

	Font.h

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
#ifndef VISUAL_FONT_H
#define VISUAL_FONT_H

#include "Common.h"

#include <SDL/SDL_ttf.h>

#include <string>

namespace visual {

class Font
{
	public:
	
		Font();
		Font(std::string filename, unsigned int size);
		virtual ~Font();
		
		bool load(std::string filename, unsigned int size);
		
		void clear();
		
		bool isLoaded() const;
		
		/// draw characters
		void draw(const int x, const int y, const char c);
		
		/// draw strings
		void draw(const int x, const int y, const std::string& text);
		
		/// render the text to a surface
		SDL_Surface* render(const char c);
		SDL_Surface* render(const std::string& text);
		
		//const int width();
		//const int height();
		
		inline std::string getFilename() {return _filename;}
		
		/// print this texture's info via ostream
		friend std::ostream& operator<<(std::ostream& os, const Font& from)
		{
			os << "loaded: " << from.isLoaded() << " filename: " << from._filename;
			return os;
		}
		
		// bitmap string stream helper
		class Stream
		{
			public:

				Stream(Font& font, const int x, const int y) : _font(font), _pos(x, y) {}
				Stream(Font& font, const Point& p) : _font(font), _pos(p) {}

				/// does the actual printing on exit
				~Stream()
				{
					_font.draw(_pos.x, _pos.y, _line.str());
				}

				/// catch << with a template class to read any type of data
				template <class T> Stream& operator<<(const T& value)
				{
					_line << value;
					return *this;
				}

				/// catch << ostream function pointers such as std::endl and std::hex
				Stream& operator<<(std::ostream& (*func)(std::ostream&))
				{
					func(_line);
					return *this;
				}

			private:

				Stream(Stream const&);                // not defined, not copyable
				Stream& operator = (Stream const&);   // not defined, not assignable
				
				Font& _font;
				Point _pos;
				std::ostringstream _line;   ///< temp buffer
		};
		
		// global SDL_ttf functions
		static void initTTF();
		static void cleanupTTF();

	protected:
		
		TTF_Font*	_font;
		std::string	_filename;
};

} // namespace

#endif // VISUAL_FONT_H
