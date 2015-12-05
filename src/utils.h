#pragma once

#include <string>
#include <windows.h>
#include <memory>

namespace utils
{

char* strlcpy(char* p, const char* p2, int maxlen);
std::string formatSeconds(int seconds);
std::string Int2Str(const int num);
void ShowError(const std::string& sText, const std::string& sTitle = std::string(), const HWND hWnd = NULL);

#if 1
template<class T>
class singleton: private T
{
public:
   /// creates global instance of singleton and returns it
   static T& instance()
   {
      static singleton<T> global_instance;
      return global_instance;
   }

private:
   /// private constructor - to prevent direct object creation
   inline singleton()
   {
   }
   /// private destructor - to prevent direct object destruction
   inline ~singleton()
   {
   }
};
#else
template <typename T>
struct singleton
{
   using inst = std::shared_ptr<T>;
   inst inst_;
   inst get()
   {
      if (!inst_)
      {
         inst_ = std::make_shared<T>();
      }
      return inst_;
   }

   void release()
   {
      inst_.reset();
   }

   inst operator()()
   {
      return get();
   }
};
#endif
}
