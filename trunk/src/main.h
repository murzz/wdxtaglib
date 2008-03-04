#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include "contentplug.h"

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

int DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen);
void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps);
int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen);
int DLL_EXPORT __stdcall ContentGetValue(char* FileName,int FieldIndex,int UnitIndex,void* FieldValue,int maxlen,int flags);
int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex);
int DLL_EXPORT __stdcall ContentSetValue(char* FileName,int FieldIndex,int UnitIndex,int FieldType,void* FieldValue,int flags);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__