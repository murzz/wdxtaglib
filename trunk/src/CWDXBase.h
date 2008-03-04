#ifndef CWDXBASE_H
#define CWDXBASE_H

#include "CustomTypes.h"
#include <windows.h>
#include "contentplug.h"
#include <map>
using namespace std;

namespace WDXTagLib
{

	//typedef struct
	class CField
	{
		public:
			string_t m_Name;
			int m_Type;
			string_t m_Unit;
			string_t m_MultChoice;

			CField() : m_Type(0){};

			CField(string_t sName, int iType, string_t sUnit, string_t sMultChoice)
			:	m_Name(sName),
				m_Type(iType),
				m_Unit(sUnit),
				m_MultChoice(sMultChoice)
			{
			};
	};// CField, *PField;

	typedef map<int, CField> CFields;


	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString() const;

			void SetIniName(const string_t& sIniName);
			void SetPluginInterfaceVersion(const DWORD dwHi, const DWORD dwLow);
			int GetSupportedField(const int FieldIndex, char* FieldName,
														char* Units, const int maxlen);
			int GetValue(const char* FileName, const int FieldIndex,
									const int UnitIndex, void* FieldValue, const int maxlen, const int flags);

		protected:
			string_t GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;
			CFields m_Fields;
			virtual int OnGetValue(const string_t& sFileName, /*const CField& Field, */const int FieldIndex,
													const int UnitIndex, void* FieldValue, const int maxlen, const int flags) = 0;

		private:
			string_t m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;
	};


};
#endif // CWDXBASE_H
