#pragma once

#include <map>
#include <fileref.h>
#include "base.h"

namespace wdx
{
class plugin: public base
{
public:
   plugin();
   virtual ~plugin();

private:
   void OnInitFields();
   int OnGetValue(const std::wstring& sFileName, const int FieldIndex,
         const int UnitIndex, void* FieldValue, const int maxlen, const int flags);
   int OnSetValue(const std::wstring& sFileName, const int FieldIndex,
         const int UnitIndex, const int FieldType, const void* FieldValue, const int flags);

   std::string OnGetDetectString() const;
   void OnEndOfSetValue();

   TagLib::FileRef& OpenFile(const std::wstring& sFileName);
   std::string GetTagType(TagLib::File* pFile) const;

   typedef std::map<std::wstring, TagLib::FileRef> files_t;

   files_t Files2Write_;
};
}
