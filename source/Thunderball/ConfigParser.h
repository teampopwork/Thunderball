#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <string>

namespace Sexy
{
class ConfigParser {
public:
	ConfigParser(bool throwExceptions);
	virtual ~ConfigParser();

	void SetThrowExceptions(bool on);
	void* GetValParser();

	std::string GetCode(const std::string& param_1);
	bool GetToken(std::string& out, bool param_1);
	bool DoReadNext();
	bool ReadNext();
	bool Open(const std::string& param_1, bool param_2);
	bool IncludeFile(const std::string& param_1);

	void Error(const std::string& param_1);
	void ErrorNoException(const std::string& param_1);
	std::string GetError();
	bool HadError();

	std::string GetKey();
	int GetStackLevel();
	int GetGroupType();
	void ErrorUnexpectedKey();
	void ErrorUnexpectedGroupType();
	bool GroupTypeIs(const char* str, int val);
};

} // namespace Sexy

#endif // __CONFIG_PARSER_H__
