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

typedef singleton<WDXTagLib::CWDXTagLib> GPlugin;

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
    return TRUE; // succesful
}

extern "C" void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen)
{
	CUtils::strlcpy(DetectString, GPlugin::instance().GetDetectString().c_str(), maxlen);
}

extern "C" void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	if ( sizeof(ContentDefaultParamStruct) != dps->size)
		return;

	GPlugin::instance().SetIniName(dps->DefaultIniName);
	GPlugin::instance().SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi, dps->PluginInterfaceVersionLow);
}

extern "C" void DLL_EXPORT __stdcall ContentPluginUnloading(void)
{
	// free plugin instance here
}

extern "C" int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen)
{
	return GPlugin::instance().GetSupportedField(FieldIndex, FieldName, Units, maxlen);
}

extern "C" int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
																int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	return GPlugin::instance().GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

extern "C" int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex)
{
	return GPlugin::instance().GetSupportedFieldFlags(FieldIndex);
}

extern "C" int DLL_EXPORT __stdcall ContentSetValue(char* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	return GPlugin::instance().SetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
}
