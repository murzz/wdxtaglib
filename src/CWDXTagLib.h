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
			int GetValue(const char* FileName, const int FieldIndex,
										const int UnitIndex, void* FieldValue, const int maxlen, const int flags);

		protected:
		private:
	};
};
#endif // CWDXTAGLIB_H
