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

using namespace WDXTagLib;
CWDXTagLib* pWdx;

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

int DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen)
{
	CUtils::strlcpy(DetectString, pWdx->GetDetectString().c_str(), maxlen);
	return 0;
}

void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	pWdx = new CWDXTagLib; // deleted in ContentPluginUnloading()

	if ( sizeof(ContentDefaultParamStruct) != dps->size)
		return;

	pWdx->SetIniName(dps->DefaultIniName);
	pWdx->SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi, dps->PluginInterfaceVersionLow);
}

void DLL_EXPORT __stdcall ContentPluginUnloading(void)
{
	delete pWdx; // created in ContentSetDefaultParams();
	pWdx = NULL;
}

int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen)
{
	return pWdx->GetSupportedField(FieldIndex, FieldName, Units, maxlen);
}

int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
																int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	return pWdx->GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex)
{
	return pWdx->GetSupportedFieldFlags(FieldIndex);
}

int DLL_EXPORT __stdcall ContentSetValue(char* FileName, int FieldIndex,
										int UnitIndex, int FieldType, void* FieldValue, int flags)
{
	return pWdx->SetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
}
