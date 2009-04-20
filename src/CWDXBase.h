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

namespace WDX_API
{
	/// Basically this class represents a field (property) of a file we want to expose.
	/// @note Field name and unit must me ANSI, use LNG file to translate it.
	/// @todo Make use of CFieldList.
	/// @todo Rename CField to Field.
	class CField
	{
		public:
			/// Name of a field as it would be shown in TC.
			/// @note Consult contentplugin help file for name limitation (ContentGetSupportedField).
			/// @note Field name must me ANSI.
			std::string m_Name;
			int m_Type;			///< Type of a field: ft_numeric_32, ft_string etc.
			std::string m_Unit;	///< kb, mb, gb etc. Consult contentplugin help for details (ContentGetSupportedField).
			std::string m_MultChoice; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).
			int m_Flag; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).

			CField() : m_Type(0), m_Flag(0){};

			CField(const std::string& sName, const int iType, const std::string& sUnit, const std::string& sMultChoice, const int iFlag)
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

			/// @note should be ASCII anyway
			virtual std::string GetDetectString() const;

			void SetIniName(const std::string& sIniName);
			void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
			int GetSupportedField(const int iFieldIndex, char* pszFieldName,
														char* pszUnits, const int iMaxLen) ;

			int GetValue(const WCHAR* pszFileName, const int iFieldIndex,
									const int iUnitIndex, void* pFieldValue,
									const int iMaxLen, const int iFlags);

			int SetValue(const WCHAR* pszFileName, const int iFieldIndex,
									const int iUnitIndex, const int iFieldType,
									const void* pFieldValue, const int iFlags);

			virtual int GetSupportedFieldFlags(const int iFieldIndex) ;

			void StopGetValue(const string_t& sFileName);

		protected:
			std::string GetIniName() const;
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

			virtual std::string OnGetDetectString() const;
			virtual void OnEndOfSetValue() const;

			/// Check this method on lengthy operations.
			/// TC set this flag to tell a plugin that a directory change
			/// has occurred, and the plugin should stop loading a value.
			bool IsAborted() const;

			///  Get aborted filename.
			/// @return Filename of the processed file in the time when abort flag was up.
			string_t GetAbortedFilename() const;

		private:
			std::string m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;

			/// File should be aborted
			string_t m_sAbortedFilename;

			/// 'time to stop' flag
			bool m_bIsAborted;

			/// Setter for m_bIsAborted.
			void SetAborted( const bool bValue );

			void SetAbortedFilename(const string_t& sValue);
	};


};
#endif // CWDXBASE_H
