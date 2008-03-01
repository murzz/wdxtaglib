#ifndef CWDXBASE_H
#define CWDXBASE_H

#include "CustomTypes.h"


namespace WDXTagLib
{

	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString() const;

			void SetIniName(const string_t sIniName);



//			virtual int ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen) = 0;
		protected:
			string_t GetIniName() const;

		private:
			string_t FIniName;
	};


};
#endif // CWDXBASE_H
