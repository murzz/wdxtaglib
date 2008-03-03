#include "CUtils.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

CUtils::CUtils()
{
	//ctor
}

char* CUtils::strlcpy(char* p, const char* p2, int maxlen)
{
	if ((int)strlen(p2)>=maxlen) {
			strncpy(p,p2,maxlen);
			p[maxlen]=0;
	} else
			strcpy(p,p2);
	return p;
}

string_t CUtils::formatSeconds(int seconds)
{
  TCHAR secondsString[3] = {0};
  sprintf(secondsString, "%02i", seconds);
  return secondsString;
}

string_t CUtils::Int2Str(const int num)
{
    ostringstream os;
    os << num;
    return (os.str());
}

