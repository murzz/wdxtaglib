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

#include "base.h"
#include "utils.h"

namespace wdx
{
base::base() :
      InterfaceVerionHi_(0),
            InterfaceVerionLow_(0)
{
}

base::~base()
{
}

std::string base::GetDetectString() const
{
   return OnGetDetectString();
}

std::string base::OnGetDetectString() const
{
   return "";
}

void base::SetIniName(const std::string& sIniName)
{
   if (sIniName == IniName_)
      return;
   IniName_ = sIniName;
}

const std::string& base::GetIniName() const
{
   return IniName_;
}

void base::SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow)
{
   InterfaceVerionHi_ = dwHi;
   InterfaceVerionLow_ = dwLow;
}

int base::GetSupportedField(const int iFieldIndex, char* pszFieldName, char* pszUnits, int iMaxLen)
{
   try
   {
      if(!fields_.size())
      {
         OnInitFields();
      }
      if (iFieldIndex < 0 || iFieldIndex >= (int) fields_.size())
      {
         return ft_nomorefields;
      }

      const field& field = fields_[iFieldIndex];
      utils::strlcpy(pszFieldName, field.m_Name.c_str(), iMaxLen - 1);
      utils::strlcpy(pszUnits, field.m_MultChoice.c_str(), iMaxLen - 1);
      // must not return ft_stringw in this function, see wdx plugin specs
      return field.m_Type == ft_stringw ? ft_string : field.m_Type;
   }
   catch (...)
   {
      ExceptionHandler();
      return ft_nomorefields;
   }
}

int base::GetValue(const wchar_t* pszFileName, const int iFieldIndex,
      const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags)
{
   try
   {
      if (iUnitIndex < 0)
         utils::ShowError(utils::Int2Str(iUnitIndex));

      if (iFieldIndex < 0 || iFieldIndex >= (int) fields_.size())
         return ft_nosuchfield;

      return OnGetValue(pszFileName, iFieldIndex, iUnitIndex, pFieldValue, iMaxLen, iFlags);
   }
   catch (...)
   {
      ExceptionHandler();
      return ft_fileerror;
   }
}

int base::SetValue(const wchar_t* FileName, const int FieldIndex,
      const int UnitIndex, const int FieldType, const void* FieldValue, const int flags)
{
   try
   {
      if (!FileName || (-1 == FieldIndex)) // this indicates end of changing attributes
      {
         OnEndOfSetValue();
         return ft_setsuccess;
      }

      if (FieldIndex < 0 || FieldIndex >= (int) fields_.size())
         return ft_nosuchfield;

      return OnSetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
   }
   catch (...)
   {
      ExceptionHandler();
      return ft_fileerror;
   }
}

int base::OnSetValue(const std::wstring& sFileName, const int iFieldIndex,
      const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags)
{
   return ft_nosuchfield;
}

int base::GetSupportedFieldFlags(const int iFieldIndex)
{
   try
   {
      if (-1 == iFieldIndex) // we should return a combination of all supported flags here
      {
         int iTotalFlags = 0;
         for (const fields_t::value_type& pair : fields_)
         {
            if (pair.second.m_Flag)
            {
               iTotalFlags |= pair.second.m_Flag;
            }
         }
         return iTotalFlags;
      }

      if (iFieldIndex < 0 || iFieldIndex >= (int) fields_.size())
         return ft_nomorefields;

      return fields_[iFieldIndex].m_Flag;
   }
   catch (...)
   {
      ExceptionHandler();
      return 0; // not sure what to return here
   }
}

void base::OnEndOfSetValue()
{
}

void base::ExceptionHandler() const
{
   try
   {
      throw;
   }
   catch (const std::exception& e)
   {
      utils::ShowError(e.what());
   }
   catch (...)
   {
      utils::ShowError("Unknown exception");
   }
}

}
