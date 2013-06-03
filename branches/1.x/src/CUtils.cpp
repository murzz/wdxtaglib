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

#include "CUtils.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

CUtils::CUtils()
{
	//ctor
}

char* CUtils::strlcpy(char* p, const char* p2, int maxlen)
{
	if ((int)strlen(p2)>=maxlen) {
			strncpy(p,p2,maxlen);
			p[maxlen]=0;
	} else
			strcpy(p,p2);
	return p;
}

string_t CUtils::formatSeconds(int seconds)
{
  TCHAR secondsString[3] = {0};
  sprintf(secondsString, "%02i", seconds);
  return secondsString;
}

string_t CUtils::Int2Str(const int num)
{
    std::ostringstream os;
    os << num;
    return (os.str());
}

void CUtils::ShowError( const string_t& sText, const string_t& sTitle, const HWND hWnd)
{
	MessageBox( hWnd, sText.c_str(), sTitle.c_str(), MB_OK | MB_ICONERROR);
}

