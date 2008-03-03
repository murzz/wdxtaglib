#include "CWDXTagLib.h"
#include "CUtils.h"
#include <fileref.h>
#include <tag.h>

namespace WDXTagLib
{
typedef enum
{
} CFieldIndexes;
CWDXTagLib::CWDXTagLib()
{
	m_Fields[m_Fields.size()] = CField( TEXT("Title"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Artist"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Album"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Year"),					ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Tracknumber"),	ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Comment"),			ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Genre"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Bitrate"),			ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Sample rate"),	ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Channels"),			ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Length (s)"),				ft_numeric_32, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Length (m:s)"),				ft_string, TEXT(""), TEXT("") );
}

CWDXTagLib::~CWDXTagLib()
{
	//dtor
}

int CWDXTagLib::OnGetValue(const string_t& sFileName, const CField& Field, const int FieldIndex,
												const int UnitIndex, void* FieldValue, const int maxlen, const int flags)
{
	TagLib::FileRef file(sFileName.c_str());

	if (file.isNull() || !file.tag() || !file.audioProperties())
		return ft_fileerror;

	TagLib::Tag *tag = file.tag();
	TagLib::AudioProperties *prop = file.audioProperties();

	switch (FieldIndex)
	{
		case 0:	CUtils::strlcpy((TCHAR*)FieldValue, tag->title().toCString(true), maxlen);	break;
		case 1:	CUtils::strlcpy((TCHAR*)FieldValue, tag->artist().toCString(true), maxlen);	break;
		case 2:	CUtils::strlcpy((TCHAR*)FieldValue, tag->album().toCString(true), maxlen);	break;
		case 3:	*(__int32*)FieldValue = tag->year();	break;
		case 4:	*(__int32*)FieldValue = tag->track();	break;
		case 5:	CUtils::strlcpy((TCHAR*)FieldValue, tag->comment().toCString(true), maxlen);	break;
		case 6:	CUtils::strlcpy((TCHAR*)FieldValue, tag->genre().toCString(true), maxlen);	break;
		case 7:	*(__int32*)FieldValue = prop->bitrate();	break;
		case 8:	*(__int32*)FieldValue = prop->sampleRate();	break;
		case 9:	*(__int32*)FieldValue = prop->channels();	break;
		case 10:	*(__int32*)FieldValue = prop->length();	break;
		case 11:
		{
			int seconds = prop->length() % 60;
      int minutes = (prop->length() - seconds) / 60;

      CUtils::strlcpy((TCHAR*)FieldValue,
					string_t(CUtils::Int2Str(minutes) + string_t(TEXT(":")) + CUtils::formatSeconds(seconds)).c_str(), maxlen);
		}
		break;
		default: return ft_nosuchfield;
			break;
	}


	return Field.m_Type;
}

}
