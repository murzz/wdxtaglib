// 	WDXTagLib is a content plugin for Total Commander that allows you to show audio
// file tags in columns, edit tags and search in tags.
// Copyright (C) 2008 Dmitrie Murzaikin (murzzz@gmail.com)
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

#include "CWDXBase.h"
#include <fileref.h>
#include <map>

namespace WDXTagLib
{
	class CWDXTagLib : public CWDXBase
	{
		public:
			CWDXTagLib();
			virtual ~CWDXTagLib();
			int OnGetValue(const string_t& sFileName, const int FieldIndex,
										const int UnitIndex, void* FieldValue, const int maxlen, const int flags);
			int OnSetValue(const string_t& sFileName, const int FieldIndex,
										const int UnitIndex, const int FieldType, const void* FieldValue, const int flags);

		protected:
			string_t OnGetDetectString() const;
			void OnEndOfSetValue();

		private:
			string_t m_sFileName;

			TagLib::FileRef& OpenFile( const string_t& sFileName );
			string_t GetTagType( TagLib::File* pFile ) const;

			typedef std::map<string_t, TagLib::FileRef> CMapOfFiles;
			typedef CMapOfFiles::iterator CFilesIter;
			CMapOfFiles m_Files2Write;
	};
};
