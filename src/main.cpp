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

#include "main.h"
#include "Plugin.h"
#include "utils.h"
#include <stdexcept>

typedef utils::singleton < Plugin > PluginSingleton;
inline Plugin& PluginInst( )
{
	return PluginSingleton::instance( );
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
			// attach to process
			// return FALSE to fail DLL load
			utils::DbgStr( __PRETTY_FUNCTION__, " -> DLL_PROCESS_ATTACH" );
			break;

		case DLL_PROCESS_DETACH:
			// detach from process
			utils::DbgStr( __PRETTY_FUNCTION__, " -> DLL_PROCESS_DETACH" );
			break;

		case DLL_THREAD_ATTACH:
			// attach to thread
			utils::DbgStr( __PRETTY_FUNCTION__, " -> DLL_THREAD_ATTACH" );
			break;

		case DLL_THREAD_DETACH:
			// detach from thread
			utils::DbgStr( __PRETTY_FUNCTION__, " -> DLL_THREAD_DETACH" );
			break;
	}
	return TRUE; // successful
}

/// Global exception handler.
void ExceptionHandler( const std::string& sWhere )
{
	utils::DbgStr( __PRETTY_FUNCTION__ );

	try
	{
		throw ;
	}
	catch(const std::runtime_error& e)
	{
		utils::ShowError(utils::toWideString(e.what()), TEXT("Runtime error"));
	}
	catch(const std::exception& e)
	{
		utils::ShowError(utils::toWideString(e.what()), TEXT("Exception"));
	}
	catch(...)
	{
		std::wstring sText = utils::toWideString( std::string("Unknown exception in ") + sWhere );
		utils::ShowError(sText, TEXT("Unknown exception"));
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentGetDetectString( char* DetectString, int maxlen )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		utils::strlcpy( DetectString, PluginInst( ).GetDetectString( ).c_str( ), maxlen );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentSetDefaultParams( ContentDefaultParamStruct* dps )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		if ( ( int ) sizeof(ContentDefaultParamStruct) > dps->size )
		{
			throw std::runtime_error( "Unexpected size of ContentDefaultParamStruct struct" );
			return;
		}

		PluginInst( ).SetIniName( dps->DefaultIniName );
		PluginInst( ).SetPluginInterfaceVersion( dps->PluginInterfaceVersionHi, dps->PluginInterfaceVersionLow );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentPluginUnloading( void )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		PluginInst( ).PluginUnloading( );

		///@todo free plugin instance here, if needed
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
	}
}

/// @note ANSI only.
int DLL_EXPORT __stdcall ContentGetSupportedField( int FieldIndex, char* FieldName, char* Units, int maxlen )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).GetSupportedField( FieldIndex, FieldName, Units, maxlen );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_nomorefields;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentGetValue( char* FileName, int FieldIndex, int UnitIndex, void* FieldValue, int maxlen,
		int flags )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).GetValue( utils::toWideString( FileName ).c_str( ), FieldIndex, UnitIndex, FieldValue,
				maxlen, flags );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentGetValueW( WCHAR* FileName, int FieldIndex, int UnitIndex, void* FieldValue,
		int maxlen, int flags )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).GetValue( FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_fileerror;
	}
}

/// @note ANSI only.
int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags( int FieldIndex )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).GetSupportedFieldFlags( FieldIndex );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_nomorefields;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentSetValue( char* FileName, int FieldIndex, int UnitIndex, int FieldType,
		void* FieldValue, int flags )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).SetValue( utils::toWideString( FileName ).c_str( ), FieldIndex, UnitIndex, FieldType,
				FieldValue, flags );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentSetValueW( WCHAR* FileName, int FieldIndex, int UnitIndex, int FieldType,
		void* FieldValue, int flags )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		return PluginInst( ).SetValue( FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
void DLL_EXPORT __stdcall ContentStopGetValue( char* FileName )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		PluginInst( ).StopGetValue( utils::toWideString( FileName ) );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
	}
}

/// @note ANSI and Unicode.
void DLL_EXPORT __stdcall ContentStopGetValueW( WCHAR* FileName )
{
	try
	{
		utils::DbgStr( __PRETTY_FUNCTION__ );

		PluginInst( ).StopGetValue( FileName );
	}
	catch ( ... )
	{
		ExceptionHandler( __PRETTY_FUNCTION__ );
	}
}
