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

#ifndef CWDXBASE_H
#define CWDXBASE_H

#include "CustomTypes.h"
#include <windows.h>
#include "contentplug.h"
#include <map>
using namespace std;

namespace WDXTagLib
{
	/// Basically this class represents a field (property) of a file we want to expose.
	class CField
	{
		public:
			/// Name of a field as it would be shown in TC.
			/// @note Consult contentplugin help file for name limitation (ContentGetSupportedField).
			string_t m_Name;
			int m_Type;			///< Type of a field: ft_numeric_32, ft_string etc.
			string_t m_Unit;	///< kb, mb, gb etc. Consult contentplugin help for details (ContentGetSupportedField).
			string_t m_MultChoice; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).
			int m_Flag; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).

			CField() : m_Type(0), m_Flag(0){};

			CField(const string_t& sName, const int iType, const string_t& sUnit, const string_t& sMultChoice, const int iFlag)
			:	m_Name(sName),
				m_Type(iType),
				m_Unit(sUnit),
				m_MultChoice(sMultChoice),
				m_Flag(iFlag)
			{
			}
	};

	/// Map of fields.
	typedef map<int, CField> CMapOfFields;

	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString() const;

			void SetIniName(const string_t& sIniName);
			void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
			int GetSupportedField(const int iFieldIndex, char* pszFieldName,
														char* pszUnits, const int iMaxLen) const;

			int GetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, void* pFieldValue,
									const int iMaxLen, const int iFlags);

			int SetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, const int iFieldType,
									const void* pFieldValue, const int iFlags);

			virtual int GetSupportedFieldFlags(const int iFieldIndex) const;

		protected:
			string_t GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;

			/// List of fields supported by plugin. Should be defined in descendants.
			CMapOfFields m_Fields;
			void ExceptionHandler() const;

			virtual int OnGetValue(const string_t& sFileName, const int iFieldIndex,
										const int iUnitIndex, void* pFieldValue,
										const int iMaxLen, const int iFlags) = 0;

			virtual int OnSetValue(const string_t& sFileName, const int iFieldIndex,
								const int iUnitIndex, const int iFieldType,
								const void* pFieldValue, const int iFlags) const;

			virtual string_t OnGetDetectString() const;
			virtual void OnEndOfSetValue() const;

		private:
			string_t m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;
	};


};
#endif // CWDXBASE_H
