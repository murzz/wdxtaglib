#include "main.h"
#include "CWDXTagLib.h"
#include "CUtils.h"

using namespace WDXTagLib;

CWDXTagLib wdx;

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
	CUtils::strlcpy(DetectString, wdx.GetDetectString().c_str(), maxlen);
	return 0;
}

void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	if ( sizeof(ContentDefaultParamStruct) != dps->size)
		return;

	wdx.SetIniName(dps->DefaultIniName);
	wdx.SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi, dps->PluginInterfaceVersionLow);
}

int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen)
{
	return wdx.GetSupportedField(FieldIndex, FieldName, Units, maxlen);
}

int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
																int UnitIndex, void* FieldValue, int maxlen, int flags)
{
	return wdx.GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

