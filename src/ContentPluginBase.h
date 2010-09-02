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

#pragma once
#include <windows.h>
#include "contentplug.h"
#include <vector>
#include <string>
#include <stdexcept>

/// Namespace for WDX API classes.
namespace ContentPlugin
{

/// Exception thrown when no such field condition detected.
class NoSuchField : public std::runtime_error
{
    public:
        NoSuchField( const std::string& msg ) :
            std::runtime_error( msg )
        {
        }
};

/// Field type.
typedef enum EFieldType_tag
{
    ftNoMoreFields = ft_nomorefields,
    ftNumeric32 = ft_numeric_32,
    ftNumeric64 = ft_numeric_64,
    ftNumericFloating = ft_numeric_floating,
    ftDate = ft_date,
    ftTime = ft_time,
    ftBoolean = ft_boolean,
    ftMultipleChoice = ft_multiplechoice,
    ftString = ft_string,
    ftFullText = ft_fulltext,
    ftDateTime = ft_datetime,
    ftWideString = ft_stringw,
} EFieldType;

/// Result flag for Get Value functionality.
typedef enum EGetValueResult_tag
{
    ftNoSuchField = ft_nosuchfield, ///< error, invalid field number given
    ftFileError = ft_fileerror, ///< file i/o error
    ftFieldEmpty = ft_fieldempty, ///< field valid, but empty
    ftOnDemand = ft_ondemand, ///< field will be retrieved only when user presses <SPACEBAR>
    ftNotSupported = ft_notsupported, ///< function not supported
    ftSetCancel = ft_setcancel, ///< user clicked cancel in field editor
    /// Field takes a long time to extract -> try again in background.
    ftDelayed = ft_delayed,

} EGetValueResult;

/// Result flag for Set Value functionality.
typedef enum ESetValueResult_tag
{
    // for ContentSetValue
    /// Setting of the attribute succeeded.
    ftSetSuccess = ft_setsuccess,
} SetValueResult;

/// This class represents a field (property) of a file we want to expose.
/// @note Field name and unit must me ANSI, use LNG file to translate it.
class FieldBase
{
    protected:
        /// Name of a field as it would be shown in TC.
        /// The field may not contain the following chars: . (dot) | (vertical line) : (colon).
        /// @note Field name must me ANSI.
        virtual std::string OnGetName( ) const = 0;
        virtual EFieldType OnGetType( ) const = 0;
        virtual std::string OnGetUnit( ) const = 0;
        virtual std::string OnGetMultChoice( ) const = 0;
        virtual int OnGetFlag( ) const = 0;
    public:
        FieldBase( );
        virtual ~FieldBase( );
        std::string GetName( ) const;
        EFieldType GetType( ) const;
        std::string GetUnit( ) const;
        std::string GetMultChoice( ) const;
        int GetFlag( ) const;
        virtual void OnGetValue( const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags ) = 0;

        ///@todo still requires an effort
        //virtual void OnSetValue();
};

/// List of fields.
class FieldListBase
{
    private:
        /// Collection of fields.
        typedef std::vector< FieldBase* > CollectionOfFields;
        CollectionOfFields m_Fields;

    protected:
        /// Reimplement it. Add fields there.
        virtual void OnAddFields( );
        /// Should be used to add field to collection.
        void AddField( FieldBase* pField );

    public:
        FieldListBase( );
        virtual ~FieldListBase( );
        size_t Count( ) const;
        FieldBase& Find( const int nIdx );
        int GetAllFlags( ) const;

        /// Method called by base class to populate list of supported fields.
        void AddFields( );

        virtual void OpenFile( const std::wstring& sFile ) = 0;
        virtual void CloseFile( ) = 0;
};

/// PluginBase class for content plugin.
/// To create plugin inherit this class and reimplement its virtual methods.
class PluginBase
{
    public:
        PluginBase( );
        virtual ~PluginBase( );

        /// @note should be ASCII anyway.
        virtual std::string GetDetectString( ) const;

        void SetIniName( const std::string& sIniName );

        void SetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow );

        EFieldType GetSupportedField( const int iFieldIndex, char* pszFieldName, char* pszUnits, const int iMaxLen );

        EFieldType GetValue( const WCHAR* pszFileName, const int iFieldIndex, const int iUnitIndex, void* pFieldValue,
                const int iMaxLen, const int iFlags );

        int SetValue( const WCHAR* pszFileName, const int iFieldIndex, const int iUnitIndex, const int iFieldType,
                const void* pFieldValue, const int iFlags );

        virtual int GetSupportedFieldFlags( const int iFieldIndex );

        void StopGetValue( const std::wstring& sFileName );

        void PluginUnloading( );

    protected:
        std::string GetIniName( ) const;
        DWORD GetPluginInterfaceVersionHi( ) const;
        DWORD GetPluginInterfaceVersionLow( ) const;

        virtual FieldListBase* OnRegisterFieldList( );

        void AddField( int nIdx, FieldBase* pField );

        virtual std::string OnGetDetectString( ) const;
        virtual void OnEndOfSetValue( ) const;

        /// Method is called before plugin unloading.
        virtual void OnPluginUnloading( );

        /// Check this method on lengthy operations.
        /// TC set this flag to tell a plugin that a directory change
        /// has occurred, and the plugin should stop loading a value.
        bool IsAborted( ) const;

        ///  Get aborted filename.
        /// @return Filename of the processed file in the time when abort flag was up.
        std::wstring GetAbortedFilename( ) const;

        /// That one is called when TC passing its plugin interface version.
        virtual void OnSetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow );

        /// That one is called when TC passing recommended ini file name.
        virtual void OnSetIniName( const std::string& sIniName );

    private:

        /// Field list. It is allowed to inherit own list and implement
        /// file caching there.
        FieldListBase* m_FieldsPtr;

        FieldListBase* GetFields( );

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

        void SetAbortedFilename( const std::wstring& sValue );
        void FreeFieldList( );
};
}
