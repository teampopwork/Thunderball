#include "ConfigParser.h"

#include "StringParser.h"
#include "TextReader.h"

#include <SexyAppFramework/Common.h>

using namespace Sexy;

// SYNTHETIC: POPCAPGAME1 0x004c0100
// Sexy::ConfigParser::`scalar deleting destructor'

// TEMPLATE: POPCAPGAME1 0x004bfcc0
// std::vector<Sexy::TextReader,std::allocator<Sexy::TextReader> >::reserve

// TEMPLATE: POPCAPGAME1 0x004c0130
// std::vector<Sexy::TextReader,std::allocator<Sexy::TextReader> >::resize

// FUNCTION: POPCAPGAME1 0x004c03f0
ConfigParser::ConfigParser(bool throwExceptions)
{
	mUnk0x9c = 0;
    mUnk0x4.reserve(0x64);
    mUnk0x4.resize(1);
    mUnk0x14 = &mUnk0x4[0];

    SetThrowExceptions(throwExceptions);
}

// FUNCTION: POPCAPGAME1 0x004bf860
ConfigParser::~ConfigParser()
{
}

// FUNCTION: POPCAPGAME1 0x004be580
void ConfigParser::SetThrowExceptions(bool on)
{
	mStringParser.mThrowExceptions = on;
	mThrowExceptions = on;
}

// FUNCTION: POPCAPGAME1 0x004be5a0
StringParser* ConfigParser::GetValParser()
{
	mStringParser.Set(mUnk0x70);
	return &mStringParser;
}

// STUB: POPCAPGAME1 0x004be930
std::string ConfigParser::GetCode(const std::string& param_1)
{
	// TODO
	return 0;
}

// STUB: POPCAPGAME1 0x004bf990
bool ConfigParser::GetToken(std::string& out, bool param_1)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x004c0a20
bool ConfigParser::DoReadNext()
{
	// TODO
	return false;
}

// FUNCTION: POPCAPGAME1 0x004c0db0
bool ConfigParser::ReadNext()
{
	if (!mUnk0x18.empty() || mStringParser.mUnk0xc.empty()) {
		if (mUnk0x9c == 3 && !mUnk0x58.empty()) {
			mUnk0x58.pop_back();
		}

		if (DoReadNext() || mUnk0x58.empty()) {
			return true;
		}
	}

	return false;
}

// STUB: POPCAPGAME1 0x004c0510
bool ConfigParser::Open(const std::string& param_1, bool param_2)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x004c0740
bool ConfigParser::IncludeFile(const std::string& param_1)
{
	// TODO
	return false;
}

// FUNCTION: POPCAPGAME1 0x004bf020
void ConfigParser::Error(const std::string& param_1, bool param_2, bool param_3)
{
	if (mUnk0x18.empty()) {
		mUnk0x18 = param_1 + " ";

		for (int i = 0; i < (int)mUnk0x4.size(); i++) {
			int dVar6 = mUnk0x4[i].mUnk0x14;
			if (param_2) {
				if (i == mUnk0x4.size() - 1) {
					dVar6 = mUnk0x38.size();
				}
			}
			// STRING: POPCAPGAME1 0x0060db64
			mUnk0x18 += StrFormat("(%s:%d)", mUnk0x4[i].mUnk0x18.c_str(), dVar6);
		}

		if (mThrowExceptions && param_3) {
			throw ConfigParserException(mUnk0x18);
		}
	}
}

// STUB: POPCAPGAME1 0x004bf250
void ConfigParser::ErrorNoException(const std::string& param_1, bool param_2)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x004bf350
bool ConfigParser::ErrorUnexpectedKey()
{
	// STRING: POPCAPGAME1 0x0060db84
	Error("Unexpected Key - " + mUnk0x70, true, true);
	return false;
}

// TEMPLATE: POPCAPGAME1 0x004421e0
// std::vector<Sexy::ConfigParser::GroupInfo,std::allocator<Sexy::ConfigParser::GroupInfo> >::back

// FUNCTION: POPCAPGAME1 0x004bf2a0
bool ConfigParser::ErrorUnexpectedGroupType()
{
    std::string& aGroupName = mUnk0x58.empty() ? mUnk0x38 : mUnk0x58.back().mUnk0x0;

	// STRING: POPCAPGAME1 0x0060db70
    Error("Unexpected Group - " + aGroupName, false, true);
    return false;
}

// FUNCTION: POPCAPGAME1 0x004bf3d0
bool ConfigParser::GroupTypeIs(const char* str, int val)
{
	if (0 <= val) {
		if (val != mUnk0x58.size()) {
			return ErrorUnexpectedGroupType();
		}
	}

	std::string& aGroupName = mUnk0x58.empty() ? mUnk0x38 : mUnk0x58.back().mUnk0x0;
	return stricmp(aGroupName.c_str(), str) == 0;
}

// STUB: POPCAPGAME1 0x004bf270
std::string ConfigParser::GetError()
{
}

bool ConfigParser::HadError()
{
	// TODO
	return false;
}

std::string ConfigParser::GetKey()
{
	// TODO
	return 0;
}

int ConfigParser::GetStackLevel()
{
	// TODO
	return 0;
}

int ConfigParser::GetGroupType()
{
	// TODO
	return 0;
}
