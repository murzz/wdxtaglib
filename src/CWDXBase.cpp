#include "CWDXBase.h"

namespace WDXTagLib
{

CWDXBase::CWDXBase()
{
	//ctor
}

CWDXBase::~CWDXBase()
{
	//dtor
}

string_t CWDXBase::GetDetectString() const
{
	return "";
}

void CWDXBase::SetIniName(const string_t sIniName)
{
	if (sIniName == FIniName)
		return;
	FIniName = sIniName;
}

string_t CWDXBase::GetIniName() const
{
	return FIniName;
}

}
