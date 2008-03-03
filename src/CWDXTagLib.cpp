#include "CWDXTagLib.h"
#include <fileref.h>
#include <tag.h>

namespace WDXTagLib
{

//	CWDXBase::m_Fields = {0};
	/*
	{
		TEXT("Artist"),
		ft_string,
		TEXT(""),
		TEXT(""),
	},*/

CWDXTagLib::CWDXTagLib()
{
	//ctor
}

CWDXTagLib::~CWDXTagLib()
{
	//dtor
}

int CWDXTagLib::GetValue(const char* FileName, const int FieldIndex,
													const int UnitIndex, void* FieldValue, const int maxlen, const int flags)
{
	return ft_nosuchfield;
}

}
