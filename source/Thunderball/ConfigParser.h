#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include "StringParser.h"
#include "TextReader.h"

#include <vector>
#include <string>

namespace Sexy
{

// FUNCTION: POPCAPGAME1 0x0063dc2c
// __TI2?AUConfigParserException@Sexy@@

struct ConfigParserException : public std::exception
{
	std::string what;
    // FUNCTION: POPCAPGAME1 0x004be8c0
	ConfigParserException(const std::string &theWhat) : what(theWhat) { }
};

class StringParser;

// VTABLE: POPCAPGAME1 0x0060db9c
class ConfigParser {
public:
	class GroupInfo {
	public:
		std::string mUnk0x0;
		std::string mUnk0x1c;
	};

	std::vector<TextReader> mUnk0x4;
	TextReader* mUnk0x14;
	std::string mUnk0x18;
	std::string mUnk0x38;
	int mUnk0x50;
	std::vector<GroupInfo> mUnk0x58;
	std::string mUnk0x64;
	std::string mUnk0x80;
	int mUnk0x9c;
	bool mThrowExceptions; // +0xa0
	StringParser mStringParser; // +0xa4

	ConfigParser(bool throwExceptions);
	virtual ~ConfigParser();

	void SetThrowExceptions(bool on);
	StringParser* GetValParser();

	void GetCode(std::string& theCode);
	void GetToken(std::string& theToken, bool allowSpaces);
	bool DoReadNext();
	bool ReadNext();
	bool Open(std::string& param_1, bool param_2);
	bool IncludeFile(std::string& param_1);

	bool Error(const std::string& param_1, bool param_2, bool param_3);
	void ErrorNoException(const std::string& param_1, bool param_2);
	std::string GetError();
	bool ErrorUnexpectedKey();
	bool ErrorUnexpectedGroupType();
	bool GroupTypeIs(const char* str, int val);
};

} // namespace Sexy

#endif // __CONFIG_PARSER_H__
