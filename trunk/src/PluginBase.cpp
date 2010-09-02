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

#include "PluginBase.h"
#include "utils.h"
#include <stdexcept>

namespace WDX_API
{
PluginBase::PluginBase( ) :
    m_FieldsPtr( NULL ), m_PluginInterfaceVerionHi( 0 ), m_PluginInterfaceVerionLow( 0 )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    ClearAbortedFlag( );
}

PluginBase::~PluginBase( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    FreeFieldList( );
}

FieldListBase* PluginBase::OnRegisterFieldList( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return NULL;
}

void PluginBase::FreeFieldList( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    if ( m_FieldsPtr )
    {
        delete m_FieldsPtr;
        m_FieldsPtr = NULL;
    }
}

std::string PluginBase::GetDetectString( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return OnGetDetectString( );
}

std::string PluginBase::OnGetDetectString( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return "";
}

void PluginBase::SetIniName( const std::string& sIniName )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    if ( sIniName == m_IniName )
    {
        return;
    }

    m_IniName = sIniName;
    OnSetIniName( m_IniName );
}

void PluginBase::OnSetIniName( const std::string& sIniName )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

std::string PluginBase::GetIniName( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return m_IniName;
}

void PluginBase::SetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    m_PluginInterfaceVerionHi = dwHi;
    m_PluginInterfaceVerionLow = dwLow;

    OnSetPluginInterfaceVersion( m_PluginInterfaceVerionHi, m_PluginInterfaceVerionLow );
}

void PluginBase::OnSetPluginInterfaceVersion( const DWORD dwHi, const DWORD dwLow )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

EFieldType PluginBase::GetSupportedField( const int iFieldIndex, char* pszFieldName, char* pszUnits, int iMaxLen )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    const FieldBase& fld = GetFields( )->Find( iFieldIndex );
    utils::strlcpy( pszFieldName, fld.GetName( ).c_str( ), iMaxLen - 1 );
    utils::strlcpy( pszUnits, fld.GetMultChoice( ).c_str( ), iMaxLen - 1 );
    return fld.GetType( );
}

EFieldType PluginBase::GetValue( const WCHAR* pszFileName, const int iFieldIndex, const int iUnitIndex,
        void* pFieldValue, const int iMaxLen, const int iFlags )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // parameter checking

    if ( !pszFileName )
    {
        throw std::runtime_error( "pszFileName is NULL" );
    }

    if ( iUnitIndex < 0 )
    {
        throw std::runtime_error( "iUnitIndex is negative" );
    }

    if ( !pFieldValue )
    {
        throw std::runtime_error( "pFieldValue is NULL" );
    }

    if ( iMaxLen < 0 )
    {
        throw std::runtime_error( "iMaxLen is negative" );
    }

    if ( iFlags < 0 )
    {
        throw std::runtime_error( "iFlags is negative" );
    }

    // abort flag down
    ClearAbortedFlag( );

    ///@todo open file only once
    GetFields( )->OpenFile( pszFileName );
    FieldBase& Field = GetFields( )->Find( iFieldIndex );

    Field.OnGetValue( iUnitIndex, pFieldValue, iMaxLen, iFlags );
    return Field.GetType( );
}

FieldListBase* PluginBase::GetFields( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    if ( !m_FieldsPtr )
    {
        m_FieldsPtr = OnRegisterFieldList( );
        if ( !m_FieldsPtr )
        {
            throw std::runtime_error( "Failed to register field list" );
        }
        m_FieldsPtr->AddFields( );
    }
    return m_FieldsPtr;
}

int PluginBase::SetValue( const WCHAR* pszFileName, const int iFieldIndex, const int iUnitIndex, const int iFieldType,
        const void* pFieldValue, const int iFlags )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // according to specs here should be &&, not ||, but leave it to be error proof
    if ( !pszFileName || ( -1 == iFieldIndex ) ) // this indicates end of changing attributes
    {
        OnEndOfSetValue( );
        return ftSetSuccess;
    }

    FieldBase& fld = GetFields( )->Find( iFieldIndex );
    return fld.GetType( );
}

int PluginBase::GetSupportedFieldFlags( const int iFieldIndex )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // we should return a combination of all supported flags here
    if ( -1 == iFieldIndex )
    {
        return GetFields( )->GetAllFlags( );
    }

    return GetFields( )->Find( iFieldIndex ).GetFlag( );
}

void PluginBase::OnEndOfSetValue( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

void PluginBase::StopGetValue( const std::wstring& sFileName )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // abort flag up

    SetAbortedFilename( sFileName );
    SetAbortedFlag( );
}

void PluginBase::SetAbortedFlag( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // aborted!
    m_bIsAborted = true;
}

void PluginBase::ClearAbortedFlag( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    // clear filename if previous state was ABORTED
    if ( m_bIsAborted )
    {
        SetAbortedFilename( TEXT("") );
    }

    // clear flag itself
    m_bIsAborted = false;
}

bool PluginBase::IsAborted( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return m_bIsAborted;
}

void PluginBase::SetAbortedFilename( const std::wstring& sValue )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    m_sAbortedFilename = sValue;
}

std::wstring PluginBase::GetAbortedFilename( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return m_sAbortedFilename;
}

void PluginBase::PluginUnloading( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    OnPluginUnloading( );
}

void PluginBase::OnPluginUnloading( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

FieldListBase::FieldListBase( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

FieldListBase::~FieldListBase( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    ///@todo destroy all fields here
}
void FieldListBase::OnAddFields( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

size_t FieldListBase::Count( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    return m_Fields.size( );
}

void FieldListBase::AddFields( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    OnAddFields( );
}

void FieldListBase::AddField( FieldBase* pField )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    if ( !pField )
    {
        throw std::runtime_error( "Failed to add field: pointer is empty" );
    }
    m_Fields.push_back( pField );
}

FieldBase& FieldListBase::Find( const int Idx )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    try
    {
        return * ( m_Fields.at( Idx ) );
    }
    catch ( std::out_of_range& e )
    {
        throw NoSuchField( e.what( ) );
    }
}

int FieldListBase::GetAllFlags( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );

    int iTotalFlags = 0;
    for ( CollectionOfFields::const_iterator iter = m_Fields.begin( ); iter != m_Fields.end( ); ++iter )
    {
        const FieldBase& f = **iter;
        if ( f.GetFlag( ) )
        {
            iTotalFlags |= f.GetFlag( );
        }
    }
    return iTotalFlags;
}

FieldBase::FieldBase( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}

FieldBase::~FieldBase( )
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
}
std::string FieldBase::GetName( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return OnGetName( );
}

EFieldType FieldBase::GetType( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return OnGetType( );
}

std::string FieldBase::GetUnit( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return OnGetUnit( );
}

std::string FieldBase::GetMultChoice( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return OnGetMultChoice( );
}

int FieldBase::GetFlag( ) const
{
    utils::DbfFuncName( __PRETTY_FUNCTION__ );
    return OnGetFlag( );
}

} // namespace
