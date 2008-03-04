#include "CWDXTagLib.h"
#include "CUtils.h"
#include <fileref.h>
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
{
	m_Fields[ fiTitle ] 					=	CField( TEXT("Title"),				ft_string, 				TEXT(""), TEXT("") );
	m_Fields[ fiArtist ] 					=	CField( TEXT("Artist"),				ft_string, 				TEXT(""), TEXT("") );
	m_Fields[ fiAlbum ] 					=	CField( TEXT("Album"),				ft_string, 				TEXT(""), TEXT("") );
	m_Fields[ fiYear ] 						= CField( TEXT("Year"),					ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiTracknumber ] 		= CField( TEXT("Tracknumber"),	ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiComment ] 				= CField( TEXT("Comment"),			ft_string, 				TEXT(""), TEXT("") );
	m_Fields[ fiGenre ] 					= CField( TEXT("Genre"),				ft_string, 				TEXT(""), TEXT("") );
	m_Fields[ fiBitrate ] 				= CField( TEXT("Bitrate"),			ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiSamplerate ] 			= CField( TEXT("Sample rate"),	ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiChannels ] 				= CField( TEXT("Channels"),			ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiLength_s ] 				= CField( TEXT("Length"),		ft_numeric_32, 		TEXT(""), TEXT("") );
	m_Fields[ fiLength_m ]				= CField( TEXT("Length (formatted)"),		ft_string,				TEXT(""), TEXT("") );
}

CWDXTagLib::~CWDXTagLib()
{
	//dtor
}

int CWDXTagLib::OnGetValue(const string_t& sFileName, /*const CField& Field,*/ const int FieldIndex,
												const int UnitIndex, void* FieldValue, const int maxlen, const int flags)
{
	TagLib::FileRef file( sFileName.c_str() );

	if ( file.isNull() || !file.tag() || !file.audioProperties() )
		return ft_fileerror;

	TagLib::Tag *tag = file.tag();
	TagLib::AudioProperties *prop = file.audioProperties();

	switch (FieldIndex)
	{
		case fiTitle:				CUtils::strlcpy( (TCHAR*)FieldValue, tag->title().toCString(true), maxlen );	break;
		case fiArtist:			CUtils::strlcpy( (TCHAR*)FieldValue, tag->artist().toCString(true), maxlen );	break;
		case fiAlbum:				CUtils::strlcpy( (TCHAR*)FieldValue, tag->album().toCString(true), maxlen );	break;
		case fiYear:
		{
			if (!tag->year())
				return ft_fieldempty;
			*(__int32*)FieldValue = tag->year();
			break;
		}
		case fiTracknumber:
		{
			if (!tag->track())
				return ft_fieldempty;
			*(__int32*)FieldValue = tag->track();
			break;
		}
		case fiComment:			CUtils::strlcpy( (TCHAR*)FieldValue, tag->comment().toCString(true), maxlen );	break;
		case fiGenre:				CUtils::strlcpy( (TCHAR*)FieldValue, tag->genre().toCString(true), maxlen );		break;
		case fiBitrate:			*(__int32*)FieldValue = prop->bitrate();		break;
		case fiSamplerate:	*(__int32*)FieldValue = prop->sampleRate();	break;
		case fiChannels:		*(__int32*)FieldValue = prop->channels();		break;
		case fiLength_s:		*(__int32*)FieldValue = prop->length();			break;
		case fiLength_m:
		{
			int seconds = prop->length() % 60;
      int minutes = (prop->length() - seconds) / 60;

      CUtils::strlcpy((TCHAR*)FieldValue,
					string_t(CUtils::Int2Str(minutes) + TEXT("m ") +
									CUtils::formatSeconds(seconds) + TEXT("s")).c_str(), maxlen);
			break;
		}
		default: return ft_nosuchfield;
			break;
	}


	return m_Fields[FieldIndex]/*Field*/.m_Type;
}

}
