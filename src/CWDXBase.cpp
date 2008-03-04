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

int CWDXBase::GetSupportedField( const int iFieldIndex, char* pszFieldName, char* pszUnits, int iMaxLen)
{
	if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
		return ft_nomorefields;

	const CField& f = m_Fields[ iFieldIndex ];
	CUtils::strlcpy( pszFieldName, f.m_Name.c_str(), iMaxLen - 1 );
	CUtils::strlcpy( pszUnits, f.m_MultChoice.c_str(), iMaxLen - 1 );
	return f.m_Type;
}

int CWDXBase::GetValue(const char* pszFileName, const int iFieldIndex,
						const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags)
{
	if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
		return ft_nosuchfield;

	return OnGetValue(pszFileName, iFieldIndex, iUnitIndex, pFieldValue, iMaxLen, iFlags);
}

int CWDXBase::SetValue(const char* FileName, const int FieldIndex,
									const int UnitIndex, const int FieldType, const void* FieldValue, const int flags)
{
	if ( FieldIndex < 0 || FieldIndex >= (int)m_Fields.size() )
		return ft_nosuchfield;
	return OnSetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
}

int CWDXBase::OnSetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags)
{
	return ft_nosuchfield;
}

int CWDXBase::GetSupportedFieldFlags(const int iFieldIndex)
{
	if (-1 == iFieldIndex)
	{
		int iTotalFlags = 0;
		for (CFields::iterator iter = m_Fields.begin(); iter != m_Fields.end(); ++iter)
			if (iter->second.m_Flag)
				iTotalFlags |= iter->second.m_Flag;
		return iTotalFlags;
	}

	if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
		return ft_nomorefields;

	return m_Fields[iFieldIndex].m_Flag;
}

}
