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

#include "CWDXTagLib.h"
#include "CUtils.h"
#include <tag.h>

namespace WDXTagLib
{
typedef enum FieldIndexes
{
	fiTitle = 0,
	fiArtist,
	fiAlbum,
	fiYear,
	fiTracknumber,
	fiComment,
	fiGenre,
	fiBitrate,
	fiSamplerate,
	fiChannels,
	fiLength_s,
	fiLength_m
} CFieldIndexes;

CWDXTagLib::CWDXTagLib()
:	m_FilePtr(NULL)
{
	m_Fields[ fiTitle				]	=	CField( TEXT("Title"),				ft_string, 				TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiArtist			]	=	CField( TEXT("Artist"),				ft_string, 				TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiAlbum				]	=	CField( TEXT("Album"),				ft_string, 				TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiYear				]	= CField( TEXT("Year"),					ft_numeric_32, 		TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiTracknumber	]	= CField( TEXT("Tracknumber"),	ft_numeric_32, 		TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiComment			]	= CField( TEXT("Comment"),			ft_string, 				TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiGenre				]	= CField( TEXT("Genre"),				ft_string, 				TEXT(""), TEXT(""), contflags_edit );
	m_Fields[ fiBitrate			]	= CField( TEXT("Bitrate"),			ft_numeric_32, 		TEXT(""), TEXT(""), 0 );
	m_Fields[ fiSamplerate	]	= CField( TEXT("Sample rate"),	ft_numeric_32, 		TEXT(""), TEXT(""), 0 );
	m_Fields[ fiChannels		]	= CField( TEXT("Channels"),			ft_numeric_32, 		TEXT(""), TEXT(""), 0 );
	m_Fields[ fiLength_s		]	= CField( TEXT("Length"),				ft_numeric_32, 		TEXT(""), TEXT(""), 0 );
	m_Fields[ fiLength_m		]	= CField( TEXT("Length (formatted)"),		ft_string,				TEXT(""), TEXT(""), 0 );
}

CWDXTagLib::~CWDXTagLib()
{
	delete m_FilePtr;
	m_FilePtr = NULL;
}

int CWDXTagLib::OnGetValue(const string_t& sFileName, const int iFieldIndex,
												const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags)
{
	//TagLib::FileRef file( sFileName.c_str() );
	if ( sFileName != m_sFileName )
	{
		m_sFileName = sFileName;
		delete m_FilePtr;
		m_FilePtr = NULL;
		m_FilePtr = new TagLib::FileRef(sFileName.c_str());
	}

	if ( !m_FilePtr || m_FilePtr->isNull() || !m_FilePtr->tag() || !m_FilePtr->audioProperties() )
		return ft_fileerror;

	TagLib::Tag *tag = m_FilePtr->tag();
	TagLib::AudioProperties *prop = m_FilePtr->audioProperties();

	switch (iFieldIndex)
	{
		case fiTitle:				CUtils::strlcpy( (TCHAR*)pFieldValue, tag->title().toCString(true), iMaxLen );	break;
		case fiArtist:			CUtils::strlcpy( (TCHAR*)pFieldValue, tag->artist().toCString(true), iMaxLen );	break;
		case fiAlbum:				CUtils::strlcpy( (TCHAR*)pFieldValue, tag->album().toCString(true), iMaxLen );	break;
		case fiYear:
		{
			if (!tag->year())
				return ft_fieldempty;
			*(__int32*)pFieldValue = tag->year();
			break;
		}
		case fiTracknumber:
		{
			if (!tag->track())
				return ft_fieldempty;
			*(__int32*)pFieldValue = tag->track();
			break;
		}
		case fiComment:			CUtils::strlcpy( (TCHAR*)pFieldValue, tag->comment().toCString(true), iMaxLen );	break;
		case fiGenre:				CUtils::strlcpy( (TCHAR*)pFieldValue, tag->genre().toCString(true), iMaxLen );		break;
		case fiBitrate:			*(__int32*)pFieldValue = prop->bitrate();		break;
		case fiSamplerate:	*(__int32*)pFieldValue = prop->sampleRate();	break;
		case fiChannels:		*(__int32*)pFieldValue = prop->channels();		break;
		case fiLength_s:		*(__int32*)pFieldValue = prop->length();			break;
		case fiLength_m:
		{
			int seconds = prop->length() % 60;
			int minutes = (prop->length() - seconds) / 60;

			CUtils::strlcpy((TCHAR*)pFieldValue,
										string_t(CUtils::Int2Str(minutes) + TEXT("m ") +
													CUtils::formatSeconds(seconds) + TEXT("s")).c_str(), iMaxLen);
			break;
		}
		default: return ft_nosuchfield;
			break;
	}
	return m_Fields[iFieldIndex].m_Type;
}

int CWDXTagLib::OnSetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags)
{
	/// @todo Optimization: use std::list for all unique sFileName (list of TagLib::FileRef instances).
	/// When iFlags indicates end of operations then save every file.
	/// Quotation from wdxhelp: FileName is set to NULL and FieldIndex to -1
	/// to signal to the plugin that the change attributes operation has ended.
	/// This can be used to flush unsaved data to disk, e.g. when setting comments for multiple files.

	TagLib::FileRef file( sFileName.c_str() );

	if ( file.isNull() || !file.tag() )
		return ft_fileerror;

	TagLib::Tag *tag = file.tag();

	switch (iFieldIndex)
	{
		case fiTitle:				tag->setTitle((PCHAR)pFieldValue);			break;
		case fiArtist:			tag->setArtist((PCHAR)pFieldValue);			break;
		case fiAlbum:				tag->setAlbum((PCHAR)pFieldValue);			break;
		case fiYear:				tag->setYear(*(__int32*)pFieldValue);		break;
		case fiTracknumber:	tag->setTrack(*(__int32*)pFieldValue);	break;
		case fiComment:			tag->setComment((PCHAR)pFieldValue);		break;
		case fiGenre:				tag->setGenre((PCHAR)pFieldValue);			break;
		default: return ft_nosuchfield;															break;
	}
	file.save();
	return ft_setsuccess;
}

}
