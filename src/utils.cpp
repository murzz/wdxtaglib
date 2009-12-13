// WDXTagLib is a content plugin for Total Commander that allows you to show audio
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
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "utils.h"
#include <tchar.h>

namespace utils
{

char* strlcpy( char* p, const char* p2, int maxlen )
{
	if ( ( int ) strlen( p2 ) >= maxlen )
	{
		strncpy( p, p2, maxlen );
		p[ maxlen ] = 0;
	}
	else
	{
		strcpy( p, p2 );
	}
	return p;
}

WCHAR* strlcpyw( WCHAR *str1, const WCHAR *str2, int imaxlen )
{
	if ( ( int ) wcslen( str2 ) >= imaxlen - 1 )
	{
		wcsncpy( str1, str2, imaxlen - 1 );
		str1[ imaxlen - 1 ] = 0;
	}
	else
	{
		wcscpy( str1, str2 );
	}
	return str1;
}

string_t formatSeconds( int seconds )
{
	TCHAR secondsString[ 3 ] = { 0 };
	_stprintf( secondsString, TEXT("%02i"), seconds );
	return secondsString;
}

//string_t Int2Str(const int num)
//{
//	tstringstream os;
//	os << num;
//	return os.str();
//}

std::wstring Int2StrW( const int num )
{
	std::wstringstream os;
	os << num;
	return os.str( );
}

std::string Int2Str( const int num )
{
	std::ostringstream os;
	os << num;
	return os.str( );
}

void ShowError( const string_t& sText, const string_t& sTitle, const HWND hWnd )
{
	MessageBox( hWnd, sText.c_str( ), sTitle.c_str( ), MB_OK | MB_ICONERROR );
}

void ShowInfo( const string_t& sText, const string_t& sTitle, const HWND hWnd )
{
	MessageBox( hWnd, sText.c_str( ), sTitle.c_str( ), MB_OK | MB_ICONINFORMATION );
}

std::wstring toWideString( const std::string& sNarrow )
{
	// figure out how many wide characters we are going to get
	int nChars = MultiByteToWideChar( CP_ACP, 0, sNarrow.c_str( ), -1, NULL, 0 );
	if ( nChars == 0 )
	{
		return L"";
	}

	// convert the narrow string to a wide string
	// slightly naughty to write directly into the string like this
	std::wstring sWide(nChars, '\0');
	//sWide.resize( nChars );
	MultiByteToWideChar( CP_ACP, 0, sNarrow.c_str(), -1,
			const_cast<WCHAR*>(sWide.c_str()), sWide.length() );

	return sWide;
}

std::wstring widen( const std::string& in, std::locale loc )
{
	std::wstring out( in.length(), 0 );
	std::string::const_iterator i = in.begin(), ie = in.end();
	//std::wstring::const_iterator j = out.begin();
	std::wstring::iterator j = out.begin();

	for(; i!=ie; ++i, ++j )
	{
		*j = std::use_facet< std::ctype< wchar_t > > ( loc ).widen( *i );
	}

	return out;
}

} // namespace utils
