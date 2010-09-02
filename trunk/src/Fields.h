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
#include "ContentPluginBase.h"
#include <fileref.h>

class PluginField : public ContentPlugin::FieldBase
{
    public:
        PluginField( TagLib::FileRef& File );
        virtual ~PluginField( );

    protected:
        TagLib::FileRef& GetFile( ) const;

    private:
        /// Reference to a file shared between fields.
        TagLib::FileRef& m_File;
};

class FieldTitle : public PluginField
{
    public:
        FieldTitle( TagLib::FileRef& File );

    private:
        std::string OnGetName( ) const;
        ContentPlugin::EFieldType OnGetType( ) const;
        std::string OnGetUnit( ) const;
        std::string OnGetMultChoice( ) const;
        int OnGetFlag( ) const;
        void OnGetValue( const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags );
};

class FieldArtist : public PluginField
{
    public:
        FieldArtist( TagLib::FileRef& File );

    private:
        std::string OnGetName( ) const;
        ContentPlugin::EFieldType OnGetType( ) const;
        std::string OnGetUnit( ) const;
        std::string OnGetMultChoice( ) const;
        int OnGetFlag( ) const;
        void OnGetValue( const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags );
};
