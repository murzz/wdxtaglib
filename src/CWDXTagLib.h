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
			int OnGetValue(const string_t& sFileName, const CField& Field, const int FieldIndex,
										const int UnitIndex, void* FieldValue, const int maxlen, const int flags);

		protected:
		private:
	};
};
#endif // CWDXTAGLIB_H
