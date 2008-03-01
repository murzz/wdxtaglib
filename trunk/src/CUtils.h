#ifndef CUTILS_H
#define CUTILS_H

#include "CustomTypes.h"

class CUtils
{
	public:
		static char* strlcpy( char* p, const char* p2, int maxlen );
		static string_t formatSeconds( int seconds );
	protected:
	private:
		CUtils();
};

#endif // CUTILS_H
