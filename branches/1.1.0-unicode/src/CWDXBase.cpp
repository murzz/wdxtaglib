// WDXTagLib is a content plugin for Total Commander which uses TagLib library
// for reading and editing the meta-data of several popular audio formats.
// Copyright (C) 2008-2013 Dmitry Murzaikin (murzzz@gmail.com)
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

#include "CWDXBase.h"
#include "CUtils.h"
#include <exception>

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
	return OnGetDetectString();
}

string_t CWDXBase::OnGetDetectString() const
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
	try
	{
		if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
			return ft_nomorefields;

		const CField& f = m_Fields[ iFieldIndex ];
		utils::strlcpy( pszFieldName, f.m_Name.c_str(), iMaxLen - 1 );
		utils::strlcpy( pszUnits, f.m_MultChoice.c_str(), iMaxLen - 1 );
		return f.m_Type;
	}
	catch(...)
	{
		ExceptionHandler();
		return ft_nomorefields;
	}
}

int CWDXBase::GetValue(const char* pszFileName, const int iFieldIndex,
						const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags)
{
	try
	{
		if (iUnitIndex < 0)
			utils::ShowError(utils::Int2Str(iUnitIndex));

		if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
			return ft_nosuchfield;

		return OnGetValue(pszFileName, iFieldIndex, iUnitIndex, pFieldValue, iMaxLen, iFlags);
	}
	catch(...)
	{
		ExceptionHandler();
		return ft_fileerror;
	}
}

int CWDXBase::SetValue(const char* FileName, const int FieldIndex,
									const int UnitIndex, const int FieldType, const void* FieldValue, const int flags)
{
	try
	{
		if ( !FileName || (-1 == FieldIndex) ) // this indicates end of changing attributes
		{
			OnEndOfSetValue();
			return ft_setsuccess;
		}

		if ( FieldIndex < 0 || FieldIndex >= (int)m_Fields.size() )
			return ft_nosuchfield;

		return OnSetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
	}
	catch(...)
	{
		ExceptionHandler();
		return ft_fileerror;
	}
}

int CWDXBase::OnSetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags)
{
	return ft_nosuchfield;
}

int CWDXBase::GetSupportedFieldFlags(const int iFieldIndex)
{
	try
	{
		if (-1 == iFieldIndex) // we should return a combination of all supported flags here
		{
			int iTotalFlags = 0;
			for (CMapOfFields::iterator iter = m_Fields.begin(); iter != m_Fields.end(); ++iter)
				if ((*iter).second.m_Flag)
					iTotalFlags |= (*iter).second.m_Flag;
			return iTotalFlags;
		}

		if ( iFieldIndex < 0 || iFieldIndex >= (int)m_Fields.size() )
			return ft_nomorefields;

		return m_Fields[iFieldIndex].m_Flag;
	}
	catch(...)
	{
		ExceptionHandler();
		return 0; // not sure what to return here
	}
}

void CWDXBase::OnEndOfSetValue()
{
}

void CWDXBase::ExceptionHandler() const
{
	try
	{
		throw;
	}
	catch(const std::exception& e)
	{
		utils::ShowError(e.what());
	}
	catch(...)
	{
		utils::ShowError(TEXT("Unknown exception"));
	}
}

}
