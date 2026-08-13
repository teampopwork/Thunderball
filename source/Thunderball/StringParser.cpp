#include "StringParser.h"

#include "ThunderCommon.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004c0f10
StringParser::StringParser()
{
    mUnk0x0 = "";
    mUnk0x4 = 0;
    mUnk0x8 = 0;
    mThrowExceptions = false;
}

// FUNCTION: POPCAPGAME1 0x004c0f40
StringParser::StringParser(std::string& theString)
{
    mThrowExceptions = false;
    Set(theString);
}

// FUNCTION: POPCAPGAME1 0x004c0f40
void StringParser::Set(std::string& theString)
{
    mUnk0xc = theString;
    mThrowExceptions = false;
}

// FUNCTION: POPCAPGAME1 0x004c0fa0
bool StringParser::Error(std::string& theError, bool param_2)
{
    mUnk0xc = theError;
    if (mThrowExceptions && param_2) {
        throw ParserException(theError);
    }
    return false;
}

// FUNCTION: POPCAPGAME1 0x004c0e40
void StringParser::SkipWhitespace() 
{ 
    if (mUnk0x4 < mUnk0x8) {
        while (mUnk0x4 < mUnk0x8) {
            if (isspace(mUnk0x0[mUnk0x4]) == 0) {
                return;
            }

            mUnk0x4++;
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004c0e80
char StringParser::GetChar(int param_1)
{
    int iVar1 = mUnk0x4 + param_1;
    if (iVar1 < 0 || iVar1 >= mUnk0x8) {
        return '\0';
    }
    return mUnk0x0[iVar1];
}

// FUNCTION: POPCAPGAME1 0x004c0ea0
bool StringParser::CheckNextChar(char param_1)
{
    SkipWhitespace();
    if (mUnk0x0[mUnk0x4] == param_1) {
        mUnk0x4++;
        return true;
    }
    return false;
}

// FUNCTION: POPCAPGAME1 0x004c0ff0
bool StringParser::EnsureNextChar(char param_1)
{
    if (!CheckNextChar(param_1)) {
        Error(StrFormat("Expecting %c", param_1), true);
        return false;
    }

    return true;
}

// FUNCTION: POPCAPGAME1 0x004c1090
int StringParser::ReadIntBase(bool param_1)
{
    SkipWhitespace();
    int aStartingPos = mUnk0x4;
    bool isNegative = false;

    if (mUnk0x0[aStartingPos] == '-') {
        isNegative = true;
        mUnk0x4 = aStartingPos + 1;
    }

    if (mUnk0x0[mUnk0x4] == '0') {
        char c = tolower(GetChar(1));
        if (c == 'x') {
            mUnk0x4 += 2;
            while(isxdigit(mUnk0x0[mUnk0x4])) {
                mUnk0x4++;
            }

            int aResult = 0;
            if (mUnk0x4 > aStartingPos && sscanf(&mUnk0x0[aStartingPos + 2], "%x", &aResult) == 1) {
                return isNegative ? -aResult : aResult;
            }
            Error(std::string("Expecting Integer"), param_1);
        } 
    } else {
        while(isdigit(mUnk0x0[mUnk0x4])) {
            mUnk0x4++;
        }

        if (mUnk0x4 > aStartingPos) {
            return atoi(&mUnk0x0[aStartingPos]);
        }

        Error(std::string("Expecting Integer"), param_1);
    }

    return 0;
}

// FUNCTION: POPCAPGAME1 0x004c1280
int StringParser::ReadInt(int param_1)
{
    if (mUnk0xc.size() == 0) {
        int iVar1 = ReadIntBase(false);
        if (!mUnk0xc.empty()) {
            mUnk0xc.erase();
            return param_1;
        }
        return iVar1;
    }
    return param_1;
}

// FUNCTION: POPCAPGAME1 0x004c1270
int StringParser::ReadInt()
{
    return ReadIntBase(true);
}

// FUNCTION: POPCAPGAME1 0x004c12b0
bool StringParser::ReadString(std::string& theString, bool param_2, bool param_3)
{
    theString.erase();
    SkipWhitespace();

    bool isQuoted = (mUnk0x0[mUnk0x4] == '"');
    if (isQuoted) {
        mUnk0x4++;
    }

    while (mUnk0x4 < mUnk0x8) {
        char currentChar = mUnk0x0[mUnk0x4];

        if (isQuoted) {
            if (currentChar == '"') {
                mUnk0x4++;
                if (mUnk0x0[mUnk0x4] != '+') {
                    return true;
                }

                mUnk0x4++;
                if (!CheckNextChar('"')) {
                    Error(std::string("Missing continued quote"), true);
                    return false;
                }
                continue;
            }

            if (currentChar == '\n') {
                Error(std::string("Missing end quote"), true);
                return false;
            }

            if (currentChar == '\\') {
                mUnk0x4++;
                char escapeChar = mUnk0x0[mUnk0x4];

                switch (escapeChar) {
                    case '"':
                        currentChar = '"';
                        break;
                    case '\\':
                        currentChar = '\\';
                        break;
                    case 'n':
                        currentChar = '\n';
                        break;
                    case 't':
                        currentChar = '\t';
                        break;
                    default:
                        Error(StrFormat("Invalid escape char: \\%c", escapeChar), true);
                        return false;
                }
            }
        } 
        else {
            if (isspace(static_cast<unsigned char>(currentChar))) {
                if (param_2) {
                    return true;
                }
            } 
            else if (currentChar == ',') {
                break;
            }
        }

        theString.append(1, currentChar);
        mUnk0x4++;
    }

    if (!param_2 && param_3) {
        Sexy::inlineTrim(theString, " \t\r\n");
    }

    return true;
}

// FUNCTION: POPCAPGAME1 0x004c1550
std::string StringParser::ReadString(bool param_1, bool param_2)
{
    std::string aString;
    ReadString(aString, param_1, param_2);
    return aString;
}

void StringParser::ReadHTMLString(std::string& theString)
{
    ReadString(theString, false, true);
}

bool StringParser::ReadBool()
{
    SkipWhitespace();
    if (mUnk0x4 < mUnk0x8) {
        char c = tolower(mUnk0x0[mUnk0x4]);
        if (c == 't') {
            mUnk0x4++;
            return true;
        } else if (c == 'f') {
            mUnk0x4++;
            return false;
        }
    }

    Error(std::string("Expecting Boolean"), true);
    return false;
}