#ifndef contentplug_H
#define contentplug_H

#define ft_nomorefields 0
#define ft_numeric_32 1
#define ft_numeric_64 2
#define ft_numeric_floating 3
#define ft_date 4
#define ft_time 5
#define ft_boolean 6
#define ft_multiplechoice 7
#define ft_string 8
#define ft_fulltext 9

// for ContentGetValue
#define ft_delayed 0
#define ft_nosuchfield -1
#define ft_fileerror -2
#define ft_fieldempty -3
#define ft_ondemand -4

#define CONTENT_DELAYIFSLOW 1

typedef struct {
    int size;
    DWORD PluginInterfaceVersionLow;
    DWORD PluginInterfaceVersionHi;
    char DefaultIniName[MAX_PATH];
} ContentDefaultParamStruct;

typedef struct {
	WORD wYear;
	WORD wMonth;
	WORD wDay;
} *pdateformat;

typedef struct {
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
} *ptimeformat;
/*
int __stdcall ContentGetDetectString(char* DetectString,int maxlen);
int __stdcall ContentGetSupportedField(int FieldIndex,char* FieldName,char* Units,char* MultipleChoiceStrings,int maxlen);
int __stdcall ContentGetValue(char* FileName,int FieldIndex,int UnitIndex,void* FieldValue,int maxlen,int flags);
void __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* dps);
void __stdcall ContentStopGetValue(char* FileName);
*/
#endif
