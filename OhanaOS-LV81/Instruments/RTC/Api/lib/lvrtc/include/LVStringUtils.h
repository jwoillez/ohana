#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <string>
#include <vector>

#include "LVdefinitions.h"

namespace LV
{
	class StringUtils
	{
	public:
		static std::string LStr2String(LStr **mLStrHdl);
		static void String2LStr(std::string mString, LStrHandle mLStrHdl);
		static void Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");
		static void Tokenize(const LStrHandle mLStrHdl, std::vector<std::string>& tokens, const std::string& delimiters = " ");
		static void DbgStringPrintf(std::string message);
	};
};

#endif