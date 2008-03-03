#ifndef CUTILS_H
#define CUTILS_H

#include "CustomTypes.h"

class CUtils
{
	public:
		static char* strlcpy( char* p, const char* p2, int maxlen );
		static string_t formatSeconds( int seconds );
		static string_t CUtils::Int2Str(const int num);
	protected:
	private:
		CUtils();
};

#endif // CUTILS_H
