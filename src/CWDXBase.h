#ifndef CWDXBASE_H
#define CWDXBASE_H

#include "CustomTypes.h"
#include <windows.h>
#include "contentplug.h"
//#include <map>
//using namespace std;

namespace WDXTagLib
{

	typedef struct
	{
		string_t m_Name;
		int m_Type;
		string_t m_Unit;
		string_t m_MultChoice;
	} CField;

	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString() const;

			void SetIniName(const string_t sIniName);
			void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
			int GetSupportedField(const int FieldIndex, char* FieldName,
														char* Units, const int maxlen) const;

			virtual int GetValue(const char* FileName, const int FieldIndex,
													const int UnitIndex, void* FieldValue, const int maxlen, const int flags) = 0;

		protected:
			string_t GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;
			int GetFieldsCount() const;

		private:
			string_t m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;
			const CField m_Fields[];

	};


};
#endif // CWDXBASE_H
