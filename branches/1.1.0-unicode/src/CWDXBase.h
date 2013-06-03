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

#include "CustomTypes.h"
#include <windows.h>
#include "contentplug.h"
#include <map>

namespace WDXTagLib
{

	//typedef struct
	class CField
	{
		public:
			string_t m_Name;
			int m_Type;
			string_t m_Unit;
			string_t m_MultChoice;
			int m_Flag;

			CField() : m_Type(0), m_Flag(0){};

			CField(const string_t& sName, const int iType, const string_t& sUnit, const string_t& sMultChoice, const int iFlag)
			:	m_Name(sName),
				m_Type(iType),
				m_Unit(sUnit),
				m_MultChoice(sMultChoice),
				m_Flag(iFlag)
			{
			};
	};// CField, *PField;

	typedef std::map<int, CField> CMapOfFields;


	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString() const;

			void SetIniName(const string_t& sIniName);
			void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
			int GetSupportedField(const int iFieldIndex, char* pszFieldName,
														char* pszUnits, const int iMaxLen);
			int GetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags);
			int SetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);
			virtual int GetSupportedFieldFlags(const int iFieldIndex);

		protected:
			string_t GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;
			CMapOfFields m_Fields;
			void ExceptionHandler() const;

			virtual int OnGetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags) = 0;
			virtual int OnSetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);
			virtual string_t OnGetDetectString() const;
			virtual void OnEndOfSetValue();

		private:
			string_t m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;
	};
};
