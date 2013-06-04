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

#include <cstring>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include "utils.h"

namespace utils
{

char* strlcpy(char* p, const char* p2, int maxlen)
{
   if ((int) strlen(p2) >= maxlen)
   {
      std::strncpy(p, p2, maxlen);
      p[maxlen] = 0;
   }
   else
      std::strcpy(p, p2);
   return p;
}

std::string formatSeconds(int seconds)
{
   char secondsString[3] = { 0 };
   std::sprintf(secondsString, "%02i", seconds);
   return secondsString;
}

std::string Int2Str(const int num)
{
   std::ostringstream os;
   os << num;
   return (os.str());
}

void ShowError(const std::string& sText, const std::string& sTitle, const HWND hWnd)
{
   MessageBox(hWnd, sText.c_str(), sTitle.c_str(), MB_OK | MB_ICONERROR);
}

}
