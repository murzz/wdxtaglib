// WDXTagLib is a content plugin for Total Commander which uses TagLib library
// for reading and editing the meta-data of several popular audio formats.
// Copyright (C) 2008-2013 Dmitry Murzaikin (murzzz@gmail.com)
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

#include <map>
#include <string>
#include <windows.h>
#include "contentplug.h"

namespace wdx
{

struct field
{
   std::string m_Name;
   int m_Type;
   std::string m_Unit;
   std::string m_MultChoice;
   int m_Flag;

   field() :
         m_Type(0), m_Flag(0)
   {
   }

   field(const std::string& sName, const int iType, const int iFlag = 0, const std::string& sUnit = std::string(),
         const std::string& sMultChoice = std::string()) :
         m_Name(sName), m_Type(iType), m_Unit(sUnit), m_MultChoice(sMultChoice), m_Flag(iFlag)
   {
   }
};

typedef std::map<int, field> fields_t;

class base
{
public:
   base();
   virtual ~base();
   virtual std::string GetDetectString() const;

   void SetIniName(const std::string& sIniName);
   void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
   int GetSupportedField(const int iFieldIndex, char* pszFieldName,
         char* pszUnits, const int iMaxLen);
   int GetValue(const wchar_t* pszFileName, const int iFieldIndex,
         const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags);
   int SetValue(const wchar_t* pszFileName, const int iFieldIndex,
         const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);
   virtual int GetSupportedFieldFlags(const int iFieldIndex);

protected:
   fields_t fields_;
   const std::string& GetIniName() const;
   const DWORD& GetInterfaceVersionHi() const;
   const DWORD& GetInterfaceVersionLow() const;

   void ExceptionHandler() const;

   virtual int OnGetValue(const std::wstring& sFileName, const int iFieldIndex,
         const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags) = 0;
   virtual int OnSetValue(const std::wstring& sFileName, const int iFieldIndex,
         const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);
   virtual std::string OnGetDetectString() const;
   virtual void OnEndOfSetValue();

private:
   std::string IniName_;
   DWORD InterfaceVerionHi_;
   DWORD InterfaceVerionLow_;
};
}
