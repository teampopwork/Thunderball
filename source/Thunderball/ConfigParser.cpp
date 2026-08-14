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
	mStringParser.Set(mUnk0x64);
	return &mStringParser;
}

// FUNCTION: POPCAPGAME1 0x004be930
void ConfigParser::GetCode(std::string& theCode)
{
	while (!mUnk0x14->EndOfFile()) {
		char c = mUnk0x14->NextChar();
		if (c == '/') {
			if (mUnk0x14->PeekChar() == '/') {
				mUnk0x14->GotoChar('\n', false);
			}
			else if (mUnk0x14->PeekChar() == '*') {
				// STRING: POPCAPGAME1 0x0060db60
				mUnk0x14->GotoString("*/", true);
			}
		}
		else if (c == ']') {
			mUnk0x14->RewindToMark();
			while (!mUnk0x14->EndOfFile()) {
				char c2 = mUnk0x14->NextChar();
				if (c2 == '\n') {
					return;
				}
				if (!isspace(c2)) {
					mUnk0x14->Mark();
					break;
				}
			}
		}
		theCode += c;
	}
}

// FUNCTION: POPCAPGAME1 0x004bf990
void ConfigParser::GetToken(std::string& theToken, bool allowSpaces)
{
	mUnk0x14->SkipWhitespace();
	theToken.erase();

	while (!mUnk0x14->EndOfFile()) {
		char c = mUnk0x14->NextChar();

		if (c == '/' && mUnk0x14->PeekChar() == '/') {
			mUnk0x14->GotoChar('\n', false);
		}
		else if (c == '/' && mUnk0x14->PeekChar() == '*') {
			int startLine = mUnk0x14->mUnk0x14;
			mUnk0x14->GotoString("*/", true);

			if (mUnk0x14->mUnk0x14 != startLine && allowSpaces) {
				break;
			}
		}
		else if (c == '"') {
			theToken += '"';
			while (!mUnk0x14->EndOfFile()) {
				char quoteChar = mUnk0x14->NextChar();
				if (quoteChar == '\n') {
					Error("Carriage return found in quote", false, true);
					return;
				}
				theToken += quoteChar;
				if (quoteChar == '"') {
					break;
				}
			}
		}

		else {
			if (!isspace(c)) {
				if (c == ';') {
					if (allowSpaces) {
						break;
					}
					theToken += c;
				}
				else if (c == '{' || c == '}') {
					if (theToken.empty()) {
						theToken = c;
						return;
					}
					mUnk0x14->UngetChar();
					return;
				}
				else if (c == '[') {
					GetCode(theToken);
				}
				else if (c == '\\' && mUnk0x14->PeekChar() == '\n') {
					mUnk0x14->NextChar();
				}
				else {
					theToken += c;
					if (c == ':' && !allowSpaces) {
						break;
					}
				}
			}
			else if (allowSpaces) {
				if (c == '\n') {
					break;
				}
				theToken += c;
			}
			else if (!theToken.empty()) {
				return;
			}
		}
	}

	if (allowSpaces) {
		inlineTrim(theToken, " \t\r\n");
	}

	if (theToken.empty() && mUnk0x14->EndOfFile()) {
		if (mUnk0x4.size() > 1) {
			mUnk0x4.pop_back();
			mUnk0x14 = &mUnk0x4.back();
			GetToken(theToken, allowSpaces);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004c0a20
bool ConfigParser::DoReadNext()
{
	std::string aToken;
	GetToken(aToken, false);
	if (aToken.empty()) {
		return false;
	}

	if (aToken[aToken.size() - 1] == ':') {
		mUnk0x64 = aToken.substr(0, aToken.size() - 1);
		mUnk0x50 = mUnk0x14->mUnk0x14;
		GetToken(mUnk0x80, false);
		mUnk0x9c = 2;
		if (stricmp(mUnk0x80.c_str(), "IncludeFile") == 0) {
			IncludeFile(mUnk0x64);
			return false;
		}
		else {
			return DoReadNext();
		}
	}
	else {
		if (aToken == "}") {
			if (!mUnk0x58.empty()) {
				mUnk0x9c = 3;
				return false;
			}
			else {
				return Error("Unexpected }", false, true);
			}
		}
		else {
			GroupInfo aGroupInfo;
			aGroupInfo.mUnk0x1c = aToken;
			GetToken(aToken, true);
			if (aToken == "[") {
				mUnk0x64 = aGroupInfo.mUnk0x1c;
				mUnk0x50 = mUnk0x14->mUnk0x14;
				mUnk0x80.erase();
				GetCode(mUnk0x80);
				mUnk0x9c = 2;
			}
			else if (aToken != "{") {
				if (aToken.empty() && aToken[0] != '\"') {
					aGroupInfo.mUnk0x1c = aToken;
				}
				else {
					StringParser aStringParser(aToken);
					aGroupInfo.mUnk0x1c = aStringParser.ReadString(false, false);
				}
				GetToken(aToken, false);
				if (aToken != "{") {
					return Error("Expecting {", false, true);
				}
			}
			mUnk0x58.push_back(aGroupInfo);
			mUnk0x9c = 1;
		}
	}

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

// FUNCTION: POPCAPGAME1 0x004c0510
bool ConfigParser::Open(const std::string& param_1, bool param_2)
{
	mUnk0x4.resize(1);

	mUnk0x4[0].mUnk0x18 = GetFileName(param_1);
	mUnk0x4[0].mUnk0x34 = GetFileDir(param_1, true);
	mUnk0x14 = &mUnk0x4[0];
	mUnk0x18 = "";
	mUnk0x58.clear();
	mUnk0x64 = "";
	mUnk0x80 = "";
	mUnk0x9c = 0;
	if (!mUnk0x14->Open(param_1) && param_2) {
		return Error("Unable to open file: " + param_1, false, true);
	}

}

// STUB: POPCAPGAME1 0x004c0740
bool ConfigParser::IncludeFile(std::string& param_1)
{
	// TODO
	return false;
}

// FUNCTION: POPCAPGAME1 0x004bf020
bool ConfigParser::Error(const std::string& param_1, bool param_2, bool param_3)
{
	if (mUnk0x18.empty()) {
		mUnk0x18 = param_1 + " ";

		for (int i = 0; i < (int) mUnk0x4.size(); i++) {
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

	return false;
}

// FUNCTION: POPCAPGAME1 0x004bf250
void ConfigParser::ErrorNoException(const std::string& param_1, bool param_2)
{
	Error(param_1, param_2, false);
}

// FUNCTION: POPCAPGAME1 0x004bf350
bool ConfigParser::ErrorUnexpectedKey()
{
	// STRING: POPCAPGAME1 0x0060db84
	Error("Unexpected Key - " + mUnk0x64, true, true);
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

// FUNCTION: POPCAPGAME1 0x004bf270
std::string ConfigParser::GetError()
{
	if (mUnk0x18.empty() && mStringParser.mUnk0xc.empty()) {
		ErrorNoException(mStringParser.mUnk0xc, false);
	}
	return mUnk0x18;
}