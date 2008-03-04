#ifndef CWDXTAGLIB_H
#define CWDXTAGLIB_H

#include "CWDXBase.h"


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
		private:
	};
};
#endif // CWDXTAGLIB_H
