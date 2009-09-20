// WDXTagLib is a content plugin for Total Commander that allows you to show audio
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
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef WDXTAGLIBFIELDS_H_
#define WDXTAGLIBFIELDS_H_

#include "WDXBase.h"

typedef enum EFieldIndexes_tag
{
	fiTitle = 0,
	fiArtist,
//	fiAlbum,
//	fiYear,
//	fiTracknumber,
//	fiComment,
//	fiGenre,
//	fiBitrate,
//	fiSamplerate,
//	fiChannels,
//	fiLength_s,
//	fiLength_m,
//	fiTagType,
} EFieldIndexes;

class FieldTitle : public WDX_API::FieldBase
{
public:
	FieldTitle();
	virtual ~FieldTitle();

	void OnGetValue(const std::wstring& sFileName,
			const int iUnitIndex, void* pFieldValue,
			const int iMaxLen, const int iFlags);
};

class FieldArtist : public WDX_API::FieldBase
{
public:
	FieldArtist();
	virtual ~FieldArtist();

	void OnGetValue(const std::wstring& sFileName,
			const int iUnitIndex, void* pFieldValue,
			const int iMaxLen, const int iFlags);
};

#endif /* WDXTAGLIBFIELDS_H_ */
