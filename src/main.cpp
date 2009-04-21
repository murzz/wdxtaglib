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

#include "main.h"
#include "CWDXTagLib.h"
#include "CUtils.h"

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
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // successful
}

// must be ASCII
void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen)
{
	CUtils::strlcpy(DetectString, PLUGIN.GetDetectString().c_str(), maxlen);
}

/// @note ANSI only
void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	if ( sizeof(ContentDefaultParamStruct) != dps->size)
		return;

	PLUGIN.SetIniName(dps->DefaultIniName);
	PLUGIN.SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi,
									dps->PluginInterfaceVersionLow);
}

void DLL_EXPORT __stdcall ContentPluginUnloading(void)
{
	// free plugin instance here
}

int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,
											char* Units,int maxlen)
{
	return PLUGIN.GetSupportedField(FieldIndex, FieldName, Units, maxlen);
}

int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
							int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	return PLUGIN.GetValue(CUtils::toWideString(FileName).c_str(), FieldIndex,
			UnitIndex, FieldValue, maxlen, flags);
}

int DLL_EXPORT __stdcall ContentGetValueW(WCHAR* FileName, int FieldIndex,
							int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	return PLUGIN.GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex)
{
	return PLUGIN.GetSupportedFieldFlags(FieldIndex);
}

int DLL_EXPORT __stdcall ContentSetValue(char* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	return PLUGIN.SetValue(CUtils::toWideString(FileName).c_str(), FieldIndex,
			UnitIndex, FieldType, FieldValue, flags);
}

int DLL_EXPORT __stdcall ContentSetValueW(WCHAR* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	return PLUGIN.SetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
}

void DLL_EXPORT __stdcall ContentStopGetValue(char* FileName)
{
	PLUGIN.StopGetValue(CUtils::toWideString(FileName));
}

void DLL_EXPORT __stdcall ContentStopGetValueW(WCHAR* FileName)
{
	PLUGIN.StopGetValue(FileName);
}
