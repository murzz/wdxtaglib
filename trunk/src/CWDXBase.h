#ifndef CWDXBASE_H
#define CWDXBASE_H

#include <string>

#ifdef _UNICODE
	#define string_t wstring
#else
	#define string_t string
#endif

using namespace std;
namespace WDXTagLib
{

	class CWDXBase
	{
		public:
			CWDXBase();
			virtual ~CWDXBase();
			virtual string_t GetDetectString();


			int ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,int maxlen);
		protected:
		private:
	};


};
#endif // CWDXBASE_H
