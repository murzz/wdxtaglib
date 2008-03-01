#ifndef CUSTOMTYPES_H_INCLUDED
#define CUSTOMTYPES_H_INCLUDED

#include <string>
using namespace std;

#ifdef _UNICODE
	#define string_t wstring
#else
	#define string_t string
#endif

#endif // CUSTOMTYPES_H_INCLUDED
