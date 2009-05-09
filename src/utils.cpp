// 	WDXTagLib is a content plugin for Total Commander that allows you to show audio
// file tags in columns, edit tags and search in tags.
// Copyright (C) 2008 Dmitrie Murzaikin (murzzz@gmail.com)
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

#include "utils.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <tchar.h>
//#include <assert.h>

namespace utils
{

char* strlcpy(char* p, const char* p2, int maxlen)
{
	if ((int)strlen(p2)>=maxlen) {
			strncpy(p,p2,maxlen);
			p[maxlen]=0;
	} else
			strcpy(p,p2);
	return p;
}

WCHAR* strlcpy(WCHAR *str1,const WCHAR *str2,int imaxlen)
{
	if ((int)wcslen(str2)>=imaxlen-1) {
		wcsncpy(str1,str2,imaxlen-1);
		str1[imaxlen-1]=0;
	} else
		wcscpy(str1,str2);
	return str1;
}

string_t formatSeconds(int seconds)
{
  TCHAR secondsString[3] = {0};
  _stprintf(secondsString, TEXT("%02i"), seconds);
  return secondsString;
}

string_t Int2Str(const int num)
{
    tstringstream os;
    os << num;
    return os.str();
}

void ShowError( const string_t& sText, const string_t& sTitle, const HWND hWnd)
{
	MessageBox( hWnd, sText.c_str(), sTitle.c_str(), MB_OK | MB_ICONERROR);
}

std::wstring toWideString(const std::string& str)
{
	return toWideString(str.c_str(), str.length());
}

///@todo Polish it.
std::wstring toWideString(const char* pStr, const size_t len)
{
	//ASSERT_PTR( pStr );
	//ASSERT( len >= 0 || len == -1 , _T("Invalid string length: ") << len );

	// figure out how many wide characters we are going to get
	int nChars = MultiByteToWideChar(CP_ACP, 0, pStr, len, NULL, 0);
	if (len == -1)
		--nChars;
	if (nChars == 0)
		return L"" ;

	// convert the narrow string to a wide string
	// nb: slightly naughty to write directly into the string like this
	std::wstring buf;
	buf.resize( nChars );
	MultiByteToWideChar( CP_ACP , 0 , pStr , len ,
			const_cast<wchar_t*>(buf.c_str()) , nChars );

	return buf;
}

} // namespace utils
