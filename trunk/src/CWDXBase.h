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
			int m_Flag;

			CField() : m_Type(0), m_Flag(0){};

			CField(const string_t& sName, const int iType, const string_t& sUnit, const string_t& sMultChoice, const int iFlag)
			:	m_Name(sName),
				m_Type(iType),
				m_Unit(sUnit),
				m_MultChoice(sMultChoice),
				m_Flag(iFlag)
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
			int GetSupportedField(const int iFieldIndex, char* pszFieldName,
														char* pszUnits, const int iMaxLen);
			int GetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags);
			int SetValue(const char* pszFileName, const int iFieldIndex,
									const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);
			virtual int GetSupportedFieldFlags(const int iFieldIndex);

		protected:
			string_t GetIniName() const;
			DWORD GetPluginInterfaceVersionHi() const;
			DWORD GetPluginInterfaceVersionLow() const;
			CFields m_Fields;
			virtual int OnGetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, void* pFieldValue, const int iMaxLen, const int iFlags) = 0;
			virtual int OnSetValue(const string_t& sFileName, const int iFieldIndex,
													const int iUnitIndex, const int iFieldType, const void* pFieldValue, const int iFlags);

		private:
			string_t m_IniName;
			DWORD m_PluginInterfaceVerionHi;
			DWORD m_PluginInterfaceVerionLow;
	};


};
#endif // CWDXBASE_H
