#include <cstring>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include "utils.h"

namespace utils
{

char* strlcpy(char* p, const char* p2, int maxlen)
{
   if ((int) strlen(p2) >= maxlen)
   {
      std::strncpy(p, p2, maxlen);
      p[maxlen] = 0;
   }
   else
      std::strcpy(p, p2);
   return p;
}

std::string formatSeconds(int seconds)
{
   char secondsString[3] = { 0 };
   std::sprintf(secondsString, "%02i", seconds);
   return secondsString;
}

std::string Int2Str(const int num)
{
   std::ostringstream os;
   os << num;
   return (os.str());
}

void ShowError(const std::string& sText, const std::string& sTitle, const HWND hWnd)
{
   MessageBox(hWnd, sText.c_str(), sTitle.c_str(), MB_OK | MB_ICONERROR);
}

}
