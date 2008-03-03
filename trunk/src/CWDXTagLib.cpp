#include "CWDXTagLib.h"
#include "CUtils.h"
#include <fileref.h>
#include <tag.h>

namespace WDXTagLib
{

CWDXTagLib::CWDXTagLib()
{
//	m_FieldsPtr = g_Fields;
	m_Fields[m_Fields.size()] = CField( TEXT("Title"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Artist"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Album"),				ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Year"),					ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Tracknumber"),	ft_string, TEXT(""), TEXT("") );
	m_Fields[m_Fields.size()] = CField( TEXT("Comment"),			ft_string, TEXT(""), TEXT("") );
}

CWDXTagLib::~CWDXTagLib()
{
	//dtor
}

int CWDXTagLib::GetValue(const char* FileName, const int FieldIndex,
												const int UnitIndex, void* FieldValue, const int maxlen, const int flags)
{
	TagLib::FileRef file(FileName);

	if (file.isNull() || !file.tag() )
		return ft_fileerror;

	TagLib::Tag *tag = file.tag();


	CUtils::strlcpy((TCHAR*)FieldValue, tag->artist().toCString(true), maxlen);

	const CField& f = m_Fields[FieldIndex];
//	CUtils::strlcpy(FieldName, f.m_Name.c_str(), maxlen - 1);
//	CUtils::strlcpy(Units, f.m_MultChoice.c_str(), maxlen - 1);
	return f.m_Type;

	//return ft_nosuchfield;
}

}
