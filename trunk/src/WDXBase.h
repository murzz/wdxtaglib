// WDXTagLib is a content plugin for Total Commander that allows you to show audio
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
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef WDXBASE_H
#define WDXBASE_H

#include <windows.h>
#include "contentplug.h"
#include <map>
#include <string>

/// Namespace where WDX API classes are defined.
namespace WDX_API
{
	/// Field type.
	typedef enum EFieldType_tag
	{
		ftNoMoreFields 			= ft_nomorefields,
		ftNumeric32 			= ft_numeric_32,
		ftNumeric64 			= ft_numeric_64,
		ftNumericFloating 		= ft_numeric_floating,
		ftDate 					= ft_date,
		ftTime 					= ft_time,
		ftBoolean 				= ft_boolean,
		ftMultipleChoice 		= ft_multiplechoice,
		ftString 				= ft_string,
		ftFullText 				= ft_fulltext,
		ftDateTime 				= ft_datetime,
		ftWideString 			= ft_stringw,

		// for ContentGetValue
		ftNoSuchField 			= ft_nosuchfield,	///< error, invalid field number given
		ftFileError				= ft_fileerror,		///< file i/o error
		ftFieldEmpty			= ft_fieldempty,	///< field valid, but empty
		ftOnDemand				= ft_ondemand,		///< field will be retrieved only when user presses <SPACEBAR>
		ftNotSupported			= ft_notsupported,	///< function not supported
		ftSetCancel				= ft_setcancel,		///< user clicked cancel in field editor
		ftDelayed				= ft_delayed,		///< Field takes a long time to extract -> try again in background.

		// for ContentSetValue
		ftSetSuccess			= ft_setsuccess,	///< Setting of the attribute succeeded.
	} EFieldType;

	/// This class represents a field (property) of a file we want to expose.
	/// @note Field name and unit must me ANSI, use LNG file to translate it.
	class FieldBase
	{
	private:
			/// Name of a field as it would be shown in TC.
			/// The field may not contain the following chars: . (dot) | (vertical line) : (colon).
			/// @note Field name must me ANSI.
			std::string m_Name;
			EFieldType m_Type;			///< Type of a field, @sa EFieldType.
			std::string m_Unit;	///< kb, mb, gb etc. Consult contentplugin help for details (ContentGetSupportedField).
			std::string m_MultChoice; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).

			///@todo use enum
			int m_Flag; ///< Consult contentplugin help for details (ContentGetSupportedFieldFlags).

	protected:
			void SetName( const std::string& sName);
			void SetType( const EFieldType& ftType );
			void SetUnit( const std::string& sUnit );
			void SetMultChoice( const std::string& sMultChoice );
			void SetFlag( const int& nFlag );

	public:
			FieldBase();
			virtual ~FieldBase();

			std::string GetName() const;
			EFieldType GetType() const;
			std::string GetUnit() const;
			std::string GetMultChoice() const;
			int GetFlag() const;

			/// Implement it in every custom field.
			virtual void OnGetValue(const std::wstring& sFileName,
					const int iUnitIndex, void* pFieldValue,
					const int iMaxLen, const int iFlags) = 0;

			///@todo still requires an effort
			virtual void OnSetValue();
	};

	/// List of fields.
	class FieldList
	{
	private:
		/// Map of fields.
		typedef std::map<int, FieldBase*> MapOfFields;
		MapOfFields m_Fields;

	public:
		FieldList();
		virtual ~FieldList();

		size_t Count() const;
		void Add(int nIdx, FieldBase* pField);
		FieldBase& Find(const int nIdx);
		int GetAllFlags();
	};

	/// Base class for content plugin.
	/// To create plugin inherit this class and reimplement its virtual methods.
	class WDXBase
	{
		public:
			WDXBase();
			virtual ~WDXBase();

			/// @note should be ASCII anyway.
			virtual std::string GetDetectString() const;

			void SetIniName( const std::string& sIniName );

			void SetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow );

			EFieldType GetSupportedField( const int iFieldIndex, char* pszFieldName,
												char* pszUnits, const int iMaxLen );

			EFieldType GetValue( const WCHAR* pszFileName, const int iFieldIndex,
										const int iUnitIndex, void* pFieldValue,
										const int iMaxLen, const int iFlags );

			EFieldType SetValue( const WCHAR* pszFileName, const int iFieldIndex,
									const int iUnitIndex, const int iFieldType,
									const void* pFieldValue, const int iFlags );

			virtual int GetSupportedFieldFlags(const int iFieldIndex);

			void StopGetValue(const std::wstring& sFileName);

			void PluginUnloading();

		protected:
			std::string GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;

			/// Fields supported by plugin. Add supported fields in descendant.
			FieldList m_Fields;

//			virtual EFieldType OnGetValue( const std::wstring& sFileName, const int iFieldIndex,
//										const int iUnitIndex, void* pFieldValue,
//										const int iMaxLen, const int iFlags ) = 0;

//			virtual EFieldType OnSetValue( const std::wstring& sFileName, const int iFieldIndex,
//								const int iUnitIndex, const int iFieldType,
//								const void* pFieldValue, const int iFlags ) const;

			virtual std::string OnGetDetectString() const;
			virtual void OnEndOfSetValue() const;

			/// Method is called before plugin unloading.
			virtual void OnPluginUnloading();

			/// Check this method on lengthy operations.
			/// TC set this flag to tell a plugin that a directory change
			/// has occurred, and the plugin should stop loading a value.
			bool IsAborted() const;

			///  Get aborted filename.
			/// @return Filename of the processed file in the time when abort flag was up.
			std::wstring GetAbortedFilename() const;

			/// That one is called when TC passing its plugin interface version.
			virtual void OnSetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow );

			/// That one is called when TC passing recommended ini file name.
			virtual void OnSetIniName( const std::string& sIniName );

		private:
			std::string m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;

			/// File should be aborted
			std::wstring m_sAbortedFilename;

			/// 'time to stop' flag
			bool m_bIsAborted;

			/// Raise m_bIsAborted flag.
			void SetAbortedFlag( );

			/// Clear m_bIsAborted flag.
			void ClearAbortedFlag( );

			void SetAbortedFilename(const std::wstring& sValue);
	};
};
#endif // CWDXBASE_H
