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

void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen)
{
	CUtils::strlcpy(DetectString, wdx.GetDetectString().c_str(), maxlen);
}

void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
	if ( sizeof(ContentDefaultParamStruct) != dps->size)
		return;


	MessageBoxA(0, dps->DefaultIniName, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen)
{
//	if (FieldIndex<0 || FieldIndex>=fieldcount)
		return ft_nomorefields;
//	strlcpy(FieldName,fieldnames[FieldIndex],maxlen-1);
//	strlcpy(Units,fieldunits_and_multiplechoicestrings[FieldIndex],maxlen-1);
//	return fieldtypes[FieldIndex];
}

int DLL_EXPORT __stdcall ContentGetValue(char* FileName,int FieldIndex,int UnitIndex,void* FieldValue,int maxlen,int flags)
{
	/*TagLib::FileRef f(FileName);

	if (f.isNull() || !f.tag() )
		return ft_fileerror;

	TagLib::Tag *tag = f.tag();
	//tag->*/

	return ft_nosuchfield	;
}

