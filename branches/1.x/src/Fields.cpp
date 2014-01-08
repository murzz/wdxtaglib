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

#include "Fields.h"
#include "utils.h"

// TagLib includes
#include <tag.h>
#include "fileref.h"

PluginField::~PluginField( )
{

}

PluginField::PluginField( TagLib::FileRef& File ) :
    FieldBase( ), m_File( File )
{

}

TagLib::FileRef& PluginField::GetFile( ) const
{
    return m_File;
}

FieldTitle::FieldTitle( TagLib::FileRef& File ) :
    PluginField( File )
{

}

std::string FieldTitle::OnGetName( ) const
{
    return "Title";
}

ContentPlugin::EFieldType FieldTitle::OnGetType( ) const
{
    return ContentPlugin::ftWideString;
}

std::string FieldTitle::OnGetUnit( ) const
{
    return "";
}

std::string FieldTitle::OnGetMultChoice( ) const
{
    return "";
}

int FieldTitle::OnGetFlag( ) const
{
    return contflags_edit; // this field is editable
}

void FieldTitle::OnGetValue( const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    TagLib::FileRef& file = GetFile( );

    // no file, no tags or no properties
    //	if ( file.isNull() )
    //		return ContentPlugin::ftFileError;
    //
    //	if ( IsAborted() )
    //		return ContentPlugin::ftFieldEmpty; // return ft_fieldempty here, according to contentplugin help
    TagLib::Tag* pTag = file.tag( );

    ///@todo throw exception here
    //if (!pTag)
    //	return ContentPlugin::ftFieldEmpty;
    utils::strlcpyw( reinterpret_cast< wchar_t* > ( pFieldValue ), pTag->title( ).toWString( ).c_str( ), iMaxLen );
}

FieldArtist::FieldArtist( TagLib::FileRef& File ) :
    PluginField( File )
{

}

std::string FieldArtist::OnGetName( ) const
{
    return "Artist";
}

ContentPlugin::EFieldType FieldArtist::OnGetType( ) const
{
    return ContentPlugin::ftWideString;
}

std::string FieldArtist::OnGetUnit( ) const
{
    return "";
}

std::string FieldArtist::OnGetMultChoice( ) const
{
    return "";
}

int FieldArtist::OnGetFlag( ) const
{
    return contflags_edit; // this field is editable
}

void FieldArtist::OnGetValue( const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    TagLib::FileRef& file = GetFile( );

    // no file, no tags or no properties
    //	if ( file.isNull() )
    //		return ContentPlugin::ftFileError;
    //
    //	if ( IsAborted() )
    //		return ContentPlugin::ftFieldEmpty; // return ft_fieldempty here, according to contentplugin help
    TagLib::Tag* pTag = file.tag( );

    ///@todo throw exception here
    //if (!pTag)
    //	return ContentPlugin::ftFieldEmpty;
    utils::strlcpyw( reinterpret_cast< wchar_t* > ( pFieldValue ), pTag->artist( ).toWString( ).c_str( ), iMaxLen );
}
