#include "cmdConverter.h"
#define MD5_CONVERTER
//#define TIME_MD5_CONVERTER
//#define NULL_CONVERTER

#ifdef MD5_CONVERTER
#include "md5Converter.h"
#endif // MD5_CONVERTER

#ifdef TIME_MD5_CONVERTER
#include "timeSynMd5Converter.h"
#endif // TIME_MD5_CONVERTER

#ifdef NULL_CONVERTER
#include "nullConverter.h"
#endif // NULL_CONVERTER


cmdConverter::cmdConverter()
{
}


cmdConverter::~cmdConverter()
{
}

string cmdConverter::getEncryCmd(string _srcCmd)
{
#ifdef MD5_CONVERTER
	static md5Converter * ptrConverter = md5Converter::getInstance();
#endif // MD5_CONVERTER

#ifdef TIME_MD5_CONVERTER
	static md5Converter * ptrConverter = timeSynMd5Converter::getInstance();
#endif // TIME_MD5_CONVERTER

#ifdef NULL_CONVERTER
	static md5Converter * ptrConverter = nullConverter::getInstance();
#endif // NULL_CONVERTER


	return ptrConverter->getCmd(_srcCmd);
}
