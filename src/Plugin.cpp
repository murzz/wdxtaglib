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

#include "Plugin.h"
#include "Fields.h"
#include "utils.h"

// TagLib includes
#include <tag.h>
//#include "mpegfile.h"
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

PluginFieldList::PluginFieldList( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
}

PluginFieldList::~PluginFieldList( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
}

void PluginFieldList::OnAddFields( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );

    AddField( new FieldTitle( m_File ) );
    AddField( new FieldArtist( m_File ) );

    //	m_Fields.Add( fiAlbum,			ContentPlugin::Field( "Album",				ContentPlugin::ftWideString, 		"", "", contflags_edit ));
    //	m_Fields.Add( fiYear,			ContentPlugin::Field( "Year",					ContentPlugin::ftNumeric32, 		"", "", contflags_edit ));
    //	m_Fields.Add( fiTracknumber,	ContentPlugin::Field( "Tracknumber",			ContentPlugin::ftNumeric32, 		"", "", contflags_edit ));
    //	m_Fields.Add( fiComment,		ContentPlugin::Field( "Comment",				ContentPlugin::ftWideString, 		"", "", contflags_edit ));
    //	m_Fields.Add( fiGenre,			ContentPlugin::Field( "Genre",				ContentPlugin::ftWideString, 		"", "", contflags_edit ));
    //	m_Fields.Add( fiBitrate,		ContentPlugin::Field( "Bitrate",				ContentPlugin::ftNumeric32, 		"", "", 0 ));
    //	m_Fields.Add( fiSamplerate,		ContentPlugin::Field( "Sample rate",			ContentPlugin::ftNumeric32, 		"", "", 0 ));
    //	m_Fields.Add( fiChannels,		ContentPlugin::Field( "Channels",				ContentPlugin::ftNumeric32, 		"", "", 0 ));
    //	m_Fields.Add( fiLength_s,		ContentPlugin::Field( "Length",				ContentPlugin::ftNumeric32, 		"", "", 0 ));
    //	m_Fields.Add( fiLength_m,		ContentPlugin::Field( "Length (formatted)",	ContentPlugin::ftWideString,		"", "", 0 ));
    //	m_Fields.Add( fiTagType,		ContentPlugin::Field( "Tag type",				ContentPlugin::ftWideString,		"", "", 0 ));

}

void PluginFieldList::OpenFile( const std::wstring& sFileName )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    if ( !m_File.isNull( ) && m_File.file( ) && ( std::wstring( m_File.file( )->name( ) ) == sFileName ) )
    {
        // already have this file opened
        return;
    }
    TagLib::FileRef File( sFileName.c_str( ), true, TagLib::AudioProperties::Accurate );
    m_File = File;
}

void PluginFieldList::CloseFile( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    if ( !m_File.isNull( ) && m_File.file( ) )
    {
        // close file by assigning new empty file
        TagLib::FileRef File;
        m_File = File;
    }
}

Plugin::Plugin( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
}

Plugin::~Plugin( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
}

void Plugin::OnAddFields( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
}

ContentPlugin::FieldListBase* Plugin::OnRegisterFieldList( )
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    return new PluginFieldList( );
}

std::string Plugin::OnGetDetectString( ) const
{
    utils::DbgFuncName( __PRETTY_FUNCTION__ );
    // take supported extensions from FileRef.
    TagLib::String sExtList;
    const TagLib::String sOpen( TEXT("EXT=\"") );
    const TagLib::String sClose( TEXT("\"") );
    const TagLib::String sOr( TEXT(" | ") );

    TagLib::FileRef fTmp;
    TagLib::StringList Exts = fTmp.defaultFileExtensions( );

    for ( TagLib::StringList::Iterator iter = Exts.begin( ); iter != Exts.end( ); ++iter )
    {
        sExtList += sOpen + ( *iter ).upper( ) + sClose + sOr;
    }

    // remove last sOr
    if ( !sExtList.isEmpty( ) )
    {
        sExtList = sExtList.substr( 0, sExtList.size( ) - sOr.size( ) );
    }

    return sExtList.toCString( );
}

//TagLib::FileRef& Plugin::OpenFile( const std::wstring& sFileName )
//{
//	utils::DbgFuncName( __PRETTY_FUNCTION__ );
//	// if there is no such file then insert it
//	// otherwise find its reference
//	FilesIter iter = m_Files2Write.find( sFileName );
//
//	if ( m_Files2Write.end( ) == iter )
//	{
//		m_Files2Write[ sFileName ] = TagLib::FileRef( sFileName.c_str( ) );
//		return m_Files2Write[ sFileName ];
//	}
//	else
//	{
//		return ( *iter ).second;
//	}
//}

//ContentPlugin::EFieldType WDXTagLib::OnGetValue(const std::wstring& sFileName, const int iFieldIndex,
//							const int iUnitIndex, void* pFieldValue,
//							const int iMaxLen, const int iFlags)
//
//{
//	///@todo cache opened files here like in OnSetValue() to improve performance.
//	///@todo close cache on timer event.
//	TagLib::FileRef file( sFileName.c_str(), true, TagLib::AudioProperties::Accurate );
//
//	// no file, no tags or no properties
//	if ( file.isNull() )
//		return ContentPlugin::ftFileError;
//
//	if ( IsAborted() )
//		return ContentPlugin::ftFieldEmpty; // return ft_fieldempty here, according to contentplugin help
//
//	TagLib::Tag* pTag = file.tag();
//	TagLib::AudioProperties* pProp = file.audioProperties();
//
//	switch (iFieldIndex)
//	{
//		case fiTitle:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->title().toWString().c_str(), iMaxLen );
//			break;
//		}
//		case fiArtist:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->artist().toWString().c_str(), iMaxLen );
//			break;
//		}
//		case fiAlbum:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->album().toWString().c_str(), iMaxLen );
//			break;
//		}
//		case fiYear:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			if (!pTag->year())
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pTag->year();
//			break;
//		}
//		case fiTracknumber:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			if (!pTag->track())
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pTag->track();
//			break;
//		}
//		case fiComment:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->comment().toWString().c_str(), iMaxLen );
//			break;
//		}
//		case fiGenre:
//		{
//			if (!pTag)
//				return ContentPlugin::ftFieldEmpty;
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), pTag->genre().toWString().c_str(), iMaxLen );
//			break;
//		}
//		case fiBitrate:
//		{
//			if (!pProp)
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pProp->bitrate();
//			break;
//		}
//		case fiSamplerate:
//		{
//			if (!pProp)
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pProp->sampleRate();
//			break;
//		}
//		case fiChannels:
//		{
//			if (!pProp)
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pProp->channels();
//			break;
//		}
//		case fiLength_s:
//		{
//			if (!pProp)
//				return ContentPlugin::ftFieldEmpty;
//			*(__int32*)pFieldValue = pProp->length();
//			break;
//		}
//		case fiLength_m:
//		{
//			if (!pProp)
//				return ContentPlugin::ftFieldEmpty;
//			int nSeconds = pProp->length() % 60;
//			int nMinutes = (pProp->length() - nSeconds) / 60;
//
//			utils::strlcpyw(reinterpret_cast<wchar_t*>(pFieldValue),
//					std::wstring(utils::Int2Str(nMinutes) + TEXT("m ") +
//									utils::formatSeconds(nSeconds) + TEXT("s")).c_str(),
//							iMaxLen);
//			break;
//		}
//		case fiTagType:
//		{
//			utils::strlcpyw( reinterpret_cast<wchar_t*>(pFieldValue), GetTagType(file.file()).c_str(), iMaxLen );
//			break;
//		}
//		default:
//		{
//			return ContentPlugin::ftNoSuchField;
//			break;
//		}
//	}
//
//	return m_Fields.Find( iFieldIndex ).GetType();
//}

//std::wstring WDXTagLib::GetTagType( TagLib::File* pFile ) const
//{
//	TagLib::ID3v2::Tag *pId3v2 = NULL;
//	TagLib::ID3v1::Tag *pId3v1 = NULL;
//	TagLib::APE::Tag *pApe = NULL;
//	TagLib::Ogg::XiphComment *pXiph = NULL;
//
//	// get pointers to tags
//	TagLib::MPEG::File* pMpegFile = dynamic_cast<TagLib::MPEG::File*>(pFile);
//	if (pMpegFile && pMpegFile->isValid())
//	{
//		pId3v2 = pMpegFile->ID3v2Tag();
//		pId3v1 = pMpegFile->ID3v1Tag();
//		pApe = pMpegFile->APETag();
//	}
//
//	TagLib::FLAC::File* pFlacFile = dynamic_cast<TagLib::FLAC::File*>(pFile);
//	if (pFlacFile && pFlacFile->isValid())
//	{
//		pId3v2 = pFlacFile->ID3v2Tag();
//		pId3v1 = pFlacFile->ID3v1Tag();
//		pXiph = pFlacFile->xiphComment();
//	}
//
//	TagLib::MPC::File* pMpcFile =  dynamic_cast<TagLib::MPC::File*>(pFile);
//	if (pMpcFile && pMpcFile->isValid())
//	{
//		pId3v1 = pMpcFile->ID3v1Tag();
//		pApe = pMpcFile->APETag();
//	}
//
//	TagLib::Ogg::File* pOggFile =  dynamic_cast<TagLib::Ogg::File*>(pFile);
//	bool bJustSayXiph = pOggFile && pOggFile->isValid(); // ogg files could have only xiph comments
//
//	TagLib::TrueAudio::File* pTAFile = dynamic_cast<TagLib::TrueAudio::File*>(pFile);
//	if (pTAFile && pTAFile->isValid())
//	{
//		pId3v2 = pTAFile->ID3v2Tag();
//		pId3v1 = pTAFile->ID3v1Tag();
//	}
//
//	TagLib::WavPack::File* pWPFile =  dynamic_cast<TagLib::WavPack::File*>(pFile);
//	if (pWPFile && pWPFile->isValid())
//	{
//		pId3v1 = pWPFile->ID3v1Tag();
//		pApe = pWPFile->APETag();
//	}
//
//	// format text
//	tstringstream sResult;
//	bool bUseSeparator = false;
//	if ( pId3v2 && !pId3v2->isEmpty())
//	{
//		sResult << TEXT("ID3v2.")
//			<< pId3v2->header()->majorVersion()
//			<< TEXT(".")
//			<< pId3v2->header()->revisionNumber();
//		bUseSeparator = true;
//	}
//
//	if ( pId3v1 && !pId3v1->isEmpty() )
//	{
//		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("ID3v1");
//		bUseSeparator = true;
//	}
//
//	if ( pApe && !pApe->isEmpty() )
//	{
//		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("APE");
//		bUseSeparator = true;
//	}
//
//	if ( (pXiph && !pXiph->isEmpty()) || bJustSayXiph )
//		sResult << (bUseSeparator ? TEXT(", ") : TEXT("")) << TEXT("XiphComment");
//
//	return sResult.str();
//}

//ContentPlugin::EFieldType WDXTagLib::OnSetValue( const std::wstring& sFileName, const int iFieldIndex,
//								const int iUnitIndex, const int iFieldType,
//								const void* pFieldValue, const int iFlags )
//{
//	TagLib::FileRef file = OpenFile( sFileName );
//
//	if ( file.isNull() || !file.tag() )
//		return ContentPlugin::ftFileError;
//
//	TagLib::Tag* pTag = file.tag();
//
//	switch (iFieldIndex)
//	{
//		case fiTitle:			pTag->setTitle((PTCHAR)pFieldValue);		break;
//		case fiArtist:			pTag->setArtist((PTCHAR)pFieldValue);		break;
//		case fiAlbum:			pTag->setAlbum((PTCHAR)pFieldValue);		break;
//		case fiYear:			pTag->setYear(*(__int32*)pFieldValue);		break;
//		case fiTracknumber:		pTag->setTrack(*(__int32*)pFieldValue);		break;
//		case fiComment:			pTag->setComment((PTCHAR)pFieldValue);		break;
//		case fiGenre:			pTag->setGenre((PTCHAR)pFieldValue);		break;
//		default: 				return ContentPlugin::ftNoSuchField;				break;
//	}
//
//	return ContentPlugin::ftSetSuccess;
//}

//void Plugin::OnEndOfSetValue( )
//{
//	utils::DbgFuncName( __PRETTY_FUNCTION__ );
//	// commit unsaved changes
//	for ( FilesIter iter = m_Files2Write.begin( ); iter != m_Files2Write.end( ); ++iter )
//	{
//		( *iter ).second.save( );
//	}
//
//	m_Files2Write.clear( );
//}
