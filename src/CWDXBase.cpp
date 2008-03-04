#include "CWDXBase.h"
#include "CUtils.h"
namespace WDXTagLib
{
CWDXBase::CWDXBase()
:	m_PluginInterfaceVerionHi(0),
	m_PluginInterfaceVerionLow(0)
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

void CWDXBase::SetIniName(const string_t& sIniName)
{
	if (sIniName == m_IniName)
		return;
	m_IniName = sIniName;
}

string_t CWDXBase::GetIniName() const
{
	return m_IniName;
}

void CWDXBase::SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow)
{
	m_PluginInterfaceVerionHi = dwHi;
	m_PluginInterfaceVerionLow = dwLow;
}

int CWDXBase::GetSupportedField( const int FieldIndex, char* FieldName, char* Units, int maxlen)
{
	if ( FieldIndex < 0 || FieldIndex >= (int)m_Fields.size() )
		return ft_nomorefields;

	const CField& f = m_Fields[FieldIndex];
	CUtils::strlcpy(FieldName, f.m_Name.c_str(), maxlen - 1);
	CUtils::strlcpy(Units, f.m_MultChoice.c_str(), maxlen - 1);
	return f.m_Type;
}

int CWDXBase::GetValue(const char* FileName, const int FieldIndex,
						const int UnitIndex, void* FieldValue, const int maxlen, const int flags)
{
	if ( FieldIndex < 0 || FieldIndex >= (int)m_Fields.size() )
		return ft_nosuchfield;

	return OnGetValue(FileName, /*m_Fields[FieldIndex], */FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

}
