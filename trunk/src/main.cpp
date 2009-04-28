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

#include <stdexcept>

#include "main.h"
#include "WDXTagLib.h"
#include "CUtils.h"

///@todo move singleton to utils namespace.
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
    inline singleton() {}
    /// private destructor - to prevent direct object destruction
    inline ~singleton() {}
};

typedef singleton<WDXTagLib> GPlugin;
#define PLUGIN (GPlugin::instance())

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
        	CUtils::ODS(__PRETTY_FUNCTION__, " -> DLL_PROCESS_ATTACH" );
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
        	CUtils::ODS(__PRETTY_FUNCTION__, " -> DLL_PROCESS_DETACH" );
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
        	CUtils::ODS(__PRETTY_FUNCTION__, " -> DLL_THREAD_ATTACH" );
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
        	CUtils::ODS(__PRETTY_FUNCTION__, " -> DLL_THREAD_DETACH" );
            break;
    }
    return TRUE; // successful
}

/// Global exception handler.
void ExceptionHandler( const std::string& sWhere )
{
	CUtils::ODS(__PRETTY_FUNCTION__);

	try
	{
		throw;
	}
	catch(const std::runtime_error& e)
	{
		CUtils::ShowError(CUtils::toWideString(e.what()), TEXT("Unhandled error"));
	}
	catch(const std::exception& e)
	{
		CUtils::ShowError(CUtils::toWideString(e.what()), TEXT("Unhandled error"));
	}
	catch(...)
	{
		string_t sText = CUtils::toWideString( std::string("Unknown exception in ") + sWhere );
		CUtils::ShowError(sText, TEXT("Unhandled error"));
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		CUtils::strlcpy(DetectString, PLUGIN.GetDetectString().c_str(), maxlen);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		if ( (int)sizeof(ContentDefaultParamStruct) > dps->size )
		{
			throw std::runtime_error("Unexpected size of ContentDefaultParamStruct struct");
			return;
		}

		PLUGIN.SetIniName(dps->DefaultIniName);
		PLUGIN.SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi,
										dps->PluginInterfaceVersionLow);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
	}
}

/// @note ANSI only.
void DLL_EXPORT __stdcall ContentPluginUnloading(void)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		// free plugin instance here, if needed
		PLUGIN.PluginUnloading();
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
	}
}

/// @note ANSI only.
int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex, char* FieldName,
											char* Units, int maxlen)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.GetSupportedField(FieldIndex, FieldName, Units, maxlen);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_nomorefields;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
							int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.GetValue(CUtils::toWideString(FileName).c_str(), FieldIndex,
			UnitIndex, FieldValue, maxlen, flags);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentGetValueW(WCHAR* FileName, int FieldIndex,
							int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_fileerror;
	}
}

/// @note ANSI only.
int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.GetSupportedFieldFlags(FieldIndex);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_nomorefields;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentSetValue(char* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.SetValue(CUtils::toWideString(FileName).c_str(), FieldIndex,
			UnitIndex, FieldType, FieldValue, flags);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
int DLL_EXPORT __stdcall ContentSetValueW(WCHAR* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		return PLUGIN.SetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
		return ft_fileerror;
	}
}

/// @note ANSI and Unicode.
void DLL_EXPORT __stdcall ContentStopGetValue(char* FileName)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		PLUGIN.StopGetValue(CUtils::toWideString(FileName));
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
	}
}

/// @note ANSI and Unicode.
void DLL_EXPORT __stdcall ContentStopGetValueW(WCHAR* FileName)
{
	try
	{
		CUtils::ODS(__PRETTY_FUNCTION__);

		PLUGIN.StopGetValue(FileName);
	}
	catch(...)
	{
		ExceptionHandler(__PRETTY_FUNCTION__);
	}
}
