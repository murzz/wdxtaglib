// WDXTagLib is a content plugin for Total Commander which uses TagLib library
// for reading and editing the meta-data of several popular audio formats.
// Copyright (C) 2008-2013 Dmitry Murzaikin (murzzz@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <windows.h>
#include <string>

namespace utils
{

char* strlcpy(char* p, const char* p2, int maxlen);
std::string formatSeconds( int seconds );
std::string Int2Str( const int num );
void ShowError(const std::string& sText, const std::string& sTitle = TEXT(""), const HWND hWnd = NULL );

template<class T>
class singleton: private T
{
public:
   /// creates global instance of singleton and returns it
   static T& instance()
   {
      static singleton<T> global_instance;
      return global_instance;
   }

private:
   /// private constructor - to prevent direct object creation
   inline singleton()
   {
   }
   /// private destructor - to prevent direct object destruction
   inline ~singleton()
   {
   }
};
}
