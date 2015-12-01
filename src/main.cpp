#include "main.h"
#include "plugin.h"
#include "utils.h"
#include "cunicode.h"

wdx::plugin& plugin_inst = utils::singleton<wdx::plugin>::instance();

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
   switch (fdwReason)
   {
      case DLL_PROCESS_ATTACH:
         // attach to process
         // return FALSE to fail DLL load
         break;

      case DLL_PROCESS_DETACH:
         // detach from process
         break;

      case DLL_THREAD_ATTACH:
         // attach to thread
         break;

      case DLL_THREAD_DETACH:
         // detach from thread
         break;
   }
   return TRUE; // succesful
}

extern "C" void DLL_EXPORT __stdcall ContentGetDetectString(char* DetectString, int maxlen)
{
   utils::strlcpy(DetectString, plugin_inst.GetDetectString().c_str(), maxlen);
}

extern "C" void DLL_EXPORT __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps)
{
   if (sizeof(ContentDefaultParamStruct) != dps->size)
      return;

   plugin_inst.SetIniName(dps->DefaultIniName);
   plugin_inst.SetPluginInterfaceVersion(dps->PluginInterfaceVersionHi, dps->PluginInterfaceVersionLow);
}

extern "C" void DLL_EXPORT __stdcall ContentPluginUnloading(void)
{
   // free plugin instance here
}

extern "C" int DLL_EXPORT __stdcall ContentGetSupportedField(int FieldIndex, char* FieldName, char* Units, int maxlen)
{
   return plugin_inst.GetSupportedField(FieldIndex, FieldName, Units, maxlen);
}

extern "C" int DLL_EXPORT __stdcall ContentGetValueW(WCHAR* FileName, int FieldIndex,
      int UnitIndex, void* FieldValue, int maxlen, int flags)
{
   return plugin_inst.GetValue(FileName, FieldIndex, UnitIndex, FieldValue, maxlen, flags);
}

extern "C" int DLL_EXPORT __stdcall ContentGetValue(char* FileName, int FieldIndex,
      int UnitIndex, void* FieldValue, int maxlen, int flags)
{
   WCHAR FileNameW[MAX_PATH];
   return ContentGetValueW(awfilenamecopy(FileNameW,FileName), FieldIndex,
         UnitIndex, FieldValue, maxlen, flags);
}

extern "C" int DLL_EXPORT __stdcall ContentGetSupportedFieldFlags(int FieldIndex)
{
   return plugin_inst.GetSupportedFieldFlags(FieldIndex);
}

extern "C" int DLL_EXPORT __stdcall ContentSetValueW(WCHAR* FileName, int FieldIndex,
      int UnitIndex, int FieldType, void* FieldValue, int flags)
{
   return plugin_inst.SetValue(FileName, FieldIndex, UnitIndex, FieldType, FieldValue, flags);
}

extern "C" int DLL_EXPORT __stdcall ContentSetValue(char* FileName, int FieldIndex,
      int UnitIndex, int FieldType, void* FieldValue, int flags)
{
   WCHAR FileNameW[MAX_PATH];
   return ContentSetValueW(awfilenamecopy(FileNameW,FileName), FieldIndex,
         UnitIndex, FieldType, FieldValue, flags);
}
