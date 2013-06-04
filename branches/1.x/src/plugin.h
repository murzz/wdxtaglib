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

#pragma once

#include "base.h"
#include <fileref.h>
#include <map>

namespace wdx
{
class plugin: public base
{
public:
   plugin();
   virtual ~plugin();

private:
   int OnGetValue(const std::wstring& sFileName, const int FieldIndex,
         const int UnitIndex, void* FieldValue, const int maxlen, const int flags);
   int OnSetValue(const std::wstring& sFileName, const int FieldIndex,
         const int UnitIndex, const int FieldType, const void* FieldValue, const int flags);

   std::string OnGetDetectString() const;
   void OnEndOfSetValue();

   TagLib::FileRef& OpenFile(const std::wstring& sFileName);
   std::string GetTagType(TagLib::File* pFile) const;

   typedef std::map<std::wstring, TagLib::FileRef> files_t;

   files_t m_Files2Write;
   std::wstring m_sFileName;
};
}
