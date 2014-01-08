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
//#include <map>

class PluginFieldList : public ContentPlugin::FieldListBase
{
    public:
        PluginFieldList( );
        virtual ~PluginFieldList( );

    private:
        TagLib::FileRef m_File;
        void OnAddFields( );
        void OpenFile( const std::wstring& sFileName );
        void CloseFile( );
};

class Plugin : public ContentPlugin::PluginBase
{
    public:
        Plugin( );
        virtual ~Plugin( );

    protected:
        std::string OnGetDetectString( ) const;
        void OnEndOfSetValue( );

    private:
        void OnAddFields( );

        ContentPlugin::FieldListBase* OnRegisterFieldList( );
        //TagLib::FileRef& OpenFile( const std::wstring& sFileName );
        //std::wstring GetTagType( TagLib::File* pFile ) const;

        //	typedef std::map < std::wstring, TagLib::FileRef > MapOfFiles;
        //	typedef MapOfFiles::iterator FilesIter;
        //	MapOfFiles m_Files2Write; ///< Cache of opened files, should speed up tag writing.
};
