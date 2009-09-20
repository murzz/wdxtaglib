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

#include "WDXTagLibFields.h"
#include "utils.h"

// TagLib includes
#include <tag.h>
#include "fileref.h"

FieldTitle::FieldTitle()
: FieldBase()
{
	SetName("Title");
	SetType(WDX_API::ftWideString);
	//m_Unit("");
	//m_MultChoice("");
	SetFlag(contflags_edit);
}

//FieldTitle::~FieldTitle()
//{
//
//}

void FieldTitle::OnGetValue(const std::wstring& sFileName,
		const int iUnitIndex, void* pFieldValue,
		const int iMaxLen, const int iFlags)
{
	///@todo cache opened files here like in OnSetValue() to improve performance.
	///@todo close cache on timer event.
	TagLib::FileRef file( sFileName.c_str(), true, TagLib::AudioProperties::Accurate );

	// no file, no tags or no properties
//	if ( file.isNull() )
//		return WDX_API::ftFileError;
//
//	if ( IsAborted() )
//		return WDX_API::ftFieldEmpty; // return ft_fieldempty here, according to contentplugin help
	TagLib::Tag* pTag = file.tag();

	///@todo throw exception here
	//if (!pTag)
	//	return WDX_API::ftFieldEmpty;
	utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->title().toWString().c_str(), iMaxLen );
}

FieldArtist::FieldArtist()
: FieldBase()
{
	SetName("Artist");
	SetType(WDX_API::ftWideString);
	//m_Unit("");
	//m_MultChoice("");
	SetFlag(contflags_edit);
}

//FieldArtist::~FieldArtist()
//{
//
//}

void FieldArtist::OnGetValue(const std::wstring& sFileName,
		const int iUnitIndex, void* pFieldValue,
		const int iMaxLen, const int iFlags)
{
	///@todo cache opened files here like in OnSetValue() to improve performance.
	///@todo close cache on timer event.
	TagLib::FileRef file( sFileName.c_str(), true, TagLib::AudioProperties::Accurate );

	// no file, no tags or no properties
//	if ( file.isNull() )
//		return WDX_API::ftFileError;
//
//	if ( IsAborted() )
//		return WDX_API::ftFieldEmpty; // return ft_fieldempty here, according to contentplugin help
	TagLib::Tag* pTag = file.tag();

	///@todo throw exception here
	//if (!pTag)
	//	return WDX_API::ftFieldEmpty;
	utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->artist().toWString().c_str(), iMaxLen );
}
