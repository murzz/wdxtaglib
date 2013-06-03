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

#pragma once

#include "CustomTypes.h"
#include <windows.h>

class CUtils
{
	public:
		static char* strlcpy( char* p, const char* p2, int maxlen );
		static string_t formatSeconds( int seconds );
		static string_t Int2Str( const int num );
		static void ShowError( const string_t& sText, const string_t& sTitle = TEXT(""), const HWND hWnd = NULL );
	protected:
	private:
		CUtils();
};
