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

#include "WDXTagLib.h"
#include "utils.h"
#include <tag.h>

#include "mpegfile.h"

#include "id3v2tag.h"
#include "id3v2header.h"
#include "id3v1tag.h"
#include "apetag.h"
#include "flacfile.h"
#include "oggflacfile.h"
#include "mpcfile.h"
#include "oggfile.h"
#include "trueaudiofile.h"
#include "wavpackfile.h"

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
	fiLength_m,
	fiTagType,
} CFieldIndexes;

WDXTagLib::WDXTagLib()
{
	// fill data for all supported fields here
	m_Fields[ fiTitle		]	= WDX_API::Field( "Title",					WDX_API::ftWideString, 		"", "", contflags_edit );
	m_Fields[ fiArtist		]	= WDX_API::Field( "Artist",					WDX_API::ftWideString, 		"", "", contflags_edit );
	m_Fields[ fiAlbum		]	= WDX_API::Field( "Album",					WDX_API::ftWideString, 		"", "", contflags_edit );
	m_Fields[ fiYear		]	= WDX_API::Field( "Year",					WDX_API::ftNumeric32, 		"", "", contflags_edit );
	m_Fields[ fiTracknumber	]	= WDX_API::Field( "Tracknumber",			WDX_API::ftNumeric32, 		"", "", contflags_edit );
	m_Fields[ fiComment		]	= WDX_API::Field( "Comment",				WDX_API::ftWideString, 		"", "", contflags_edit );
	m_Fields[ fiGenre		]	= WDX_API::Field( "Genre",					WDX_API::ftWideString, 		"", "", contflags_edit );
	m_Fields[ fiBitrate		]	= WDX_API::Field( "Bitrate",				WDX_API::ftNumeric32, 		"", "", 0 );
	m_Fields[ fiSamplerate	]	= WDX_API::Field( "Sample rate",			WDX_API::ftNumeric32, 		"", "", 0 );
	m_Fields[ fiChannels	]	= WDX_API::Field( "Channels",				WDX_API::ftNumeric32, 		"", "", 0 );
	m_Fields[ fiLength_s	]	= WDX_API::Field( "Length",					WDX_API::ftNumeric32, 		"", "", 0 );
	m_Fields[ fiLength_m	]	= WDX_API::Field( "Length (formatted)",		WDX_API::ftWideString,		"", "", 0 );
	m_Fields[ fiTagType		]	= WDX_API::Field( "Tag type",				WDX_API::ftWideString,		"", "", 0 );
}

WDXTagLib::~WDXTagLib()
{
}

std::string WDXTagLib::OnGetDetectString() const
{
	// take supported extensions from FileRef.
	TagLib::String sExtList;
	TagLib::String sOpen(TEXT("EXT=\""));
	TagLib::String sClose(TEXT("\""));
	TagLib::String sOr(TEXT(" | "));

	TagLib::FileRef fTmp;
	TagLib::StringList Exts = fTmp.defaultFileExtensions();

	for(TagLib::StringList::Iterator iter = Exts.begin(); iter != Exts.end(); ++iter)
	{
		sExtList += sOpen + (*iter).upper() + sClose + sOr;
	}

	// remove last sOr
	if (!sExtList.isEmpty())
		sExtList = sExtList.substr(0, sExtList.size() - sOr.size());

	return sExtList.toCString();
}

TagLib::FileRef& WDXTagLib::OpenFile( const string_t& sFileName )
{
	// if there is no such file then insert it
	// otherwise find its reference
	CFilesIter iter = m_Files2Write.find( sFileName );

	if ( m_Files2Write.end() == iter )
	{
		m_Files2Write[sFileName] = TagLib::FileRef( sFileName.c_str() );
		return m_Files2Write[sFileName];
	}
	else
	{
		return (*iter).second;
	}
}

int WDXTagLib::OnGetValue(const string_t& sFileName, const int iFieldIndex,
							const int iUnitIndex, void* pFieldValue,
							const int iMaxLen, const int iFlags)

{
	TagLib::FileRef file( sFileName.c_str(), true, TagLib::AudioProperties::Accurate );

	// no file, no tags or no properties
	if ( file.isNull() )
		return ft_fileerror;

	if ( IsAborted() )
		return ft_fieldempty; // return ft_fieldempty here, according to contentplugin help

	TagLib::Tag* pTag = file.tag();
	TagLib::AudioProperties* pProp = file.audioProperties();

	switch (iFieldIndex)
	{
		case fiTitle:
		{
			if (!pTag)
				return ft_fieldempty;
			utils::strlcpy( (PTCHAR)pFieldValue, pTag->title().toWString().c_str(), iMaxLen );
			break;
		}
		case fiArtist:
		{
			if (!pTag)
				return ft_fieldempty;
			utils::strlcpy( (PTCHAR)pFieldValue, pTag->artist().toWString().c_str(), iMaxLen );
			break;
		}
		case fiAlbum:
		{
			if (!pTag)
				return ft_fieldempty;
			utils::strlcpy( (PTCHAR)pFieldValue, pTag->album().toWString().c_str(), iMaxLen );
			break;
		}
		case fiYear:
		{
			if (!pTag)
				return ft_fieldempty;
			if (!pTag->year())
				return ft_fieldempty;
			*(__int32*)pFieldValue = pTag->year();
			break;
		}
		case fiTracknumber:
		{
			if (!pTag)
				return ft_fieldempty;
			if (!pTag->track())
				return ft_fieldempty;
			*(__int32*)pFieldValue = pTag->track();
			break;
		}
		case fiComment:
		{
			if (!pTag)
				return ft_fieldempty;
			utils::strlcpy( (PTCHAR)pFieldValue, pTag->comment().toWString().c_str(), iMaxLen );
			break;
		}
		case fiGenre:
		{
			if (!pTag)
				return ft_fieldempty;
			utils::strlcpy( (PTCHAR)pFieldValue, pTag->genre().toWString().c_str(), iMaxLen );
			break;
		}
		case fiBitrate:
		{
			if (!pProp)
				return ft_fieldempty;
			*(__int32*)pFieldValue = pProp->bitrate();
			break;
		}
		case fiSamplerate:
		{
			if (!pProp)
				return ft_fieldempty;
			*(__int32*)pFieldValue = pProp->sampleRate();
			break;
		}
		case fiChannels:
		{
			if (!pProp)
				return ft_fieldempty;
			*(__int32*)pFieldValue = pProp->channels();
			break;
		}
		case fiLength_s:
		{
			if (!pProp)
				return ft_fieldempty;
			*(__int32*)pFieldValue = pProp->length();
			break;
		}
		case fiLength_m:
		{
			if (!pProp)
				return ft_fieldempty;
			int nSeconds = pProp->length() % 60;
			int nMinutes = (pProp->length() - nSeconds) / 60;

			utils::strlcpy((PTCHAR)pFieldValue,
							string_t(utils::Int2Str(nMinutes) + TEXT("m ") +
									utils::formatSeconds(nSeconds) + TEXT("s")).c_str(),
							iMaxLen);
			break;
		}
		case fiTagType:
		{
			utils::strlcpy( (PTCHAR)pFieldValue, GetTagType(file.file()).c_str(), iMaxLen );
			break;
		}
		default:
		{
			return ft_nosuchfield;
			break;
		}
	}

	//return m_Fields.at(iFieldIndex).m_Type;
	return m_Fields[iFieldIndex].m_Type;
}

string_t WDXTagLib::GetTagType( TagLib::File* pFile ) const
{
	TagLib::ID3v2::Tag *pId3v2 = NULL;
	TagLib::ID3v1::Tag *pId3v1 = NULL;
	TagLib::APE::Tag *pApe = NULL;
	TagLib::Ogg::XiphComment *pXiph = NULL;

	// get pointers to tags
	TagLib::MPEG::File* pMpegFile = dynamic_cast<TagLib::MPEG::File*>(pFile);
	if (pMpegFile && pMpegFile->isValid())
	{
		pId3v2 = pMpegFile->ID3v2Tag();
		pId3v1 = pMpegFile->ID3v1Tag();
		pApe = pMpegFile->APETag();
	}

	TagLib::FLAC::File* pFlacFile = dynamic_cast<TagLib::FLAC::File*>(pFile);
	if (pFlacFile && pFlacFile->isValid())
	{
		pId3v2 = pFlacFile->ID3v2Tag();
		pId3v1 = pFlacFile->ID3v1Tag();
		pXiph = pFlacFile->xiphComment();
	}

	TagLib::MPC::File* pMpcFile =  dynamic_cast<TagLib::MPC::File*>(pFile);
	if (pMpcFile && pMpcFile->isValid())
	{
		pId3v1 = pMpcFile->ID3v1Tag();
		pApe = pMpcFile->APETag();
	}

	TagLib::Ogg::File* pOggFile =  dynamic_cast<TagLib::Ogg::File*>(pFile);
	bool bJustSayXiph = pOggFile && pOggFile->isValid(); // ogg files could have only xiph comments

	TagLib::TrueAudio::File* pTAFile = dynamic_cast<TagLib::TrueAudio::File*>(pFile);
	if (pTAFile && pTAFile->isValid())
	{
		pId3v2 = pTAFile->ID3v2Tag();
		pId3v1 = pTAFile->ID3v1Tag();
	}

	TagLib::WavPack::File* pWPFile =  dynamic_cast<TagLib::WavPack::File*>(pFile);
	if (pWPFile && pWPFile->isValid())
	{
		pId3v1 = pWPFile->ID3v1Tag();
		pApe = pWPFile->APETag();
	}

	// format text
	tstringstream sResult;
	bool bUseSeparator = false;
	if ( pId3v2 && !pId3v2->isEmpty())
	{
		sResult << TEXT("ID3v2.")
			<< pId3v2->header()->majorVersion()
			<< TEXT(".")
			<< pId3v2->header()->revisionNumber();
		bUseSeparator = true;
	}

	if ( pId3v1 && !pId3v1->isEmpty() )
	{
		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("ID3v1");
		bUseSeparator = true;
	}

	if ( pApe && !pApe->isEmpty() )
	{
		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("APE");
		bUseSeparator = true;
	}

	if ( (pXiph && !pXiph->isEmpty()) || bJustSayXiph )
		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("XiphComment");

	return sResult.str();
}

int WDXTagLib::OnSetValue(const string_t& sFileName, const int iFieldIndex,
								const int iUnitIndex, const int iFieldType,
								const void* pFieldValue, const int iFlags)
{
	///@todo use unicode here
	//if ( !TagLib::File::isWritable(sFileName.c_str()) )
		//return ft_fileerror;

	TagLib::FileRef file = OpenFile( sFileName );

	if ( file.isNull() || !file.tag() )
		return ft_fileerror;

	TagLib::Tag* pTag = file.tag();

	switch (iFieldIndex)
	{
		case fiTitle:			pTag->setTitle((PTCHAR)pFieldValue);		break;
		case fiArtist:			pTag->setArtist((PTCHAR)pFieldValue);		break;
		case fiAlbum:			pTag->setAlbum((PTCHAR)pFieldValue);		break;
		case fiYear:			pTag->setYear(*(__int32*)pFieldValue);		break;
		case fiTracknumber:		pTag->setTrack(*(__int32*)pFieldValue);		break;
		case fiComment:			pTag->setComment((PTCHAR)pFieldValue);		break;
		case fiGenre:			pTag->setGenre((PTCHAR)pFieldValue);		break;
		default: 				return ft_nosuchfield;						break;
	}

	return ft_setsuccess;
}

void WDXTagLib::OnEndOfSetValue()
{
	for (CFilesIter iter = m_Files2Write.begin(); iter != m_Files2Write.end(); ++iter)
		(*iter).second.save();

	m_Files2Write.clear();
}
