#include "LVStringUtils.h"

std::string LV::StringUtils::LStr2String(LStrHandle mLStrHdl)
{
	std::string mString="";
	mString.insert(0,(char *)LStrBuf(*mLStrHdl));
	mString=mString.substr(0,LStrLen(*mLStrHdl));
	return mString;
}

void LV::StringUtils::String2LStr(std::string mString, LStrHandle mLStrHdl)
{
	DSSetHandleSize(mLStrHdl, sizeof(int32)+mString.length()*sizeof(uChar));
	(*mLStrHdl)->cnt=mString.length();
	for(unsigned int i=0;i<mString.length();i++)
		(*mLStrHdl)->str[i]=mString[i];
}

void LV::StringUtils::Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void LV::StringUtils::Tokenize(const LStrHandle mLStrHdl, std::vector<std::string>& tokens, const std::string& delimiters)
{
	Tokenize(LV::StringUtils::LStr2String(mLStrHdl),tokens,delimiters);
}

void LV::StringUtils::DbgStringPrintf(std::string message)
{
		char* buffer=(char *)malloc((message.length()+1)*sizeof(char));
		strcpy(buffer,message.c_str());
		DbgPrintf(buffer);
		free(buffer);
}