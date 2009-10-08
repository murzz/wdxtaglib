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

//void FieldTitle::Configure()
//{
//	utils::DbgStr(__PRETTY_FUNCTION__);
//	SetName("Title");
//	SetType(WDX_API::ftWideString);
//	//m_Unit("");
//	//m_MultChoice("");
//	SetFlag(contflags_edit);
//}

std::string FieldTitle::OnGetName() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "Title";
}

WDX_API::EFieldType FieldTitle::OnGetType() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return WDX_API::ftWideString;
}

std::string FieldTitle::OnGetUnit() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "";
}

std::string FieldTitle::OnGetMultChoice() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "";
}

int FieldTitle::OnGetFlag() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return contflags_edit; // this field is editable
}

//FieldTitle::~FieldTitle()
//{
//
//}

void FieldTitle::OnGetValue(/*const std::wstring& sFileName,*/
		const int iUnitIndex, void* pFieldValue,
		const int iMaxLen, const int iFlags)
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	TagLib::FileRef& file = GetFile();

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

//void FieldArtist::Configure()
//{
//	utils::DbgStr(__PRETTY_FUNCTION__);
//	SetName("Artist");
//	SetType(WDX_API::ftWideString);
//	//m_Unit("");
//	//m_MultChoice("");
//	SetFlag(contflags_edit);
//}
std::string FieldArtist::OnGetName() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "Artist";
}

WDX_API::EFieldType FieldArtist::OnGetType() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return WDX_API::ftWideString;
}

std::string FieldArtist::OnGetUnit() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "";
}

std::string FieldArtist::OnGetMultChoice() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return "";
}

int FieldArtist::OnGetFlag() const
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	return contflags_edit; // this field is editable
}
//FieldArtist::~FieldArtist()
//{
//
//}

void FieldArtist::OnGetValue(/*const std::wstring& sFileName,*/
		const int iUnitIndex, void* pFieldValue,
		const int iMaxLen, const int iFlags)
{
	utils::DbgStr(__PRETTY_FUNCTION__);
	TagLib::FileRef& file = GetFile();
	//( sFileName.c_str(), true, TagLib::AudioProperties::Accurate );

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
