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

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>

#ifdef _UNICODE
	#define string_t std::wstring
	#define tstringstream std::wstringstream
#else
	#define string_t std::string
	#define tstringstream std::ostringstream
#endif

namespace utils
{
	std::wstring widen( const std::string& in, std::locale loc  = std::locale() );
	std::wstring toWideString(const std::string& sNarrow);
	char* strlcpy( char* p, const char* p2, int maxlen );
	WCHAR* strlcpy(WCHAR *str1,const WCHAR *str2,int imaxlen);
	string_t formatSeconds( int seconds );
	string_t Int2Str( const int num );
	void ShowError( const string_t& sText, const string_t& sTitle = TEXT(""), const HWND hWnd = NULL );

	/// OutputDebugString() wrapper.
	inline void ODS (const std::string& Str)
	{
		// do not throw any exceptions here
		OutputDebugStringA(Str.c_str());
	}

	/// OutputDebugString() wrapper. Str1 and Str2 gets concatenated.
	inline void ODS (const std::string& Str1, const std::string& Str2)
	{
		// do not throw any exceptions here
		OutputDebugStringA((Str1 + Str2).c_str());
	}

	/// Singleton.
	template <class T>
	class singleton : private T
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
	    singleton() {}
	    /// private destructor - to prevent direct object destruction
	    ~singleton() {}
	};
} // namespace utils

#endif // UTILS_H
