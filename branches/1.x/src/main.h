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

#include <windows.h>
#include "contentplug.h"

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


extern "C"
{
void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString,int maxlen);
void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps);
int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen);
int DLL_EXPORT __stdcall ContentGetValue(char* FileName,int FieldIndex,int UnitIndex,void* FieldValue,int maxlen,int flags);
int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex);
int DLL_EXPORT __stdcall ContentSetValue(char* FileName,int FieldIndex,int UnitIndex,int FieldType,void* FieldValue,int flags);
void DLL_EXPORT __stdcall ContentPluginUnloading(void);
}
