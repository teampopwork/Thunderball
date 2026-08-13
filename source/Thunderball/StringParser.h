#ifndef __STRINGPARSER_H__
#define __STRINGPARSER_H__

#include <string>

namespace Sexy {

struct ParserException : public std::exception
{
	std::string what;
	ParserException(const std::string &theWhat) : what(theWhat) { }
};

class StringParser {
public:
    char* mUnk0x0;
    int mUnk0x4;
    int mUnk0x8;
    std::string mUnk0xc;
    bool mThrowExceptions; // +0x28

    StringParser();
    StringParser(std::string& theString);

    void Set(std::string& theString);
    bool Error(std::string& theError, bool param_2);
    void SkipWhitespace();
    char GetChar(int param_1);
    bool CheckNextChar(char param_1);
    bool EnsureNextChar(char param_1);
    int ReadIntBase(bool param_1);
    int ReadInt(int param_1);
    int ReadInt();
    bool ReadString(std::string& theString, bool param_2, bool param_3);
    std::string ReadString(bool param_1, bool param_2);
    bool ReadHTMLString(std::string& theString);
    bool ReadBool();
};

} // namespace Sexy

#endif //__STRINGPARSER_H__