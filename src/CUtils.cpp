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

#include "CUtils.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <tchar.h>
//#include <assert.h>

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

WCHAR* CUtils::strlcpy(WCHAR *str1,const WCHAR *str2,int imaxlen)
{
	if ((int)wcslen(str2)>=imaxlen-1) {
		wcsncpy(str1,str2,imaxlen-1);
		str1[imaxlen-1]=0;
	} else
		wcscpy(str1,str2);
	return str1;
}

string_t CUtils::formatSeconds(int seconds)
{
  TCHAR secondsString[3] = {0};
  _stprintf(secondsString, TEXT("%02i"), seconds);
  return secondsString;
}

string_t CUtils::Int2Str(const int num)
{
    tstringstream os;
    os << num;
    return (os.str());
}

void CUtils::ShowError( const string_t& sText, const string_t& sTitle, const HWND hWnd)
{
	MessageBox( hWnd, sText.c_str(), sTitle.c_str(), MB_OK | MB_ICONERROR);
}

std::wstring CUtils::toWideString(const std::string& str)
{
	return toWideString(str.c_str(), str.length());
}

std::wstring CUtils::toWideString(const char* pStr, const size_t len)
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

char* walcopy(char* outname,WCHAR* inname,int maxlen)
{
	if (inname) {
		WideCharToMultiByte(CP_ACP,0,inname,-1,outname,maxlen,NULL,NULL);
		outname[maxlen]=0;
		return outname;
	} else
		return NULL;
}

WCHAR* awlcopy(WCHAR* outname,char* inname,int maxlen)
{
	if (inname) {
		MultiByteToWideChar(CP_ACP,0,inname,-1,outname,maxlen);
		outname[maxlen]=0;
		return outname;
	} else
		return NULL;
}

WCHAR* wcslcpy(WCHAR *str1,const WCHAR *str2,int imaxlen)
{
	if ((int)wcslen(str2)>=imaxlen-1) {
		wcsncpy(str1,str2,imaxlen-1);
		str1[imaxlen-1]=0;
	} else
		wcscpy(str1,str2);
	return str1;
}

WCHAR* wcslcat(wchar_t *str1,const WCHAR *str2,int imaxlen)
{
	int l1=(int)wcslen(str1);
	if ((int)wcslen(str2)+l1>=imaxlen-1) {
		wcsncpy(str1+l1,str2,imaxlen-1-l1);
		str1[imaxlen-1]=0;
	} else
		wcscat(str1,str2);
	return str1;
}

// return true if name wasn't cut
BOOL MakeExtraLongNameW(WCHAR* outbuf,const WCHAR* inbuf,int maxlen)
{
	if (wcslen(inbuf)>259) {
		wcslcpy(outbuf,L"\\\\?\\",maxlen);
		wcslcat(outbuf,inbuf,maxlen);
	} else
		wcslcpy(outbuf,inbuf,maxlen);
	return (int)wcslen(inbuf)+4<=maxlen;
}