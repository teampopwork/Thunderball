#include "TextReader.h"

#include <PakLib/PakInterface.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004c1a40
TextReader::TextReader()
{
    mUnk0x4 = 0;
    mUnk0x10 = 0;
    mUnk0x8 = 0;
    mUnk0xc = 0;
    mUnk0x14 = 0;
}

// FUNCTION: POPCAPGAME1 0x004be790
TextReader::TextReader(const TextReader& param_1)
{
    mUnk0x4 = param_1.mUnk0x4;
    mUnk0x8 = param_1.mUnk0x8;
    mUnk0xc = param_1.mUnk0xc;
    mUnk0x10 = param_1.mUnk0x10;
    mUnk0x14 = param_1.mUnk0x14;
    mUnk0x18 = param_1.mUnk0x18;
    mUnk0x34 = param_1.mUnk0x34;
}

// FUNCTION: POPCAPGAME1 0x004c1c40
TextReader::~TextReader()
{
    Close();
}

// FUNCTION: POPCAPGAME1 0x004c1a60
void TextReader::Close() {
    delete mUnk0x4;
    mUnk0x4 = NULL;
    mUnk0x10 = 0;
    mUnk0x8 = 0;
    mUnk0xc = 0;
    mUnk0x14 = 1;
}

// FUNCTION: POPCAPGAME1 0x004c1c50
bool TextReader::Open(const std::string& theFileName) {
    PFILE* file = p_fopen(theFileName.c_str(), "rb");
    if (file == NULL) {
        return false;
    }

    p_fseek(file, 0, 2);
    mUnk0x10 = p_ftell(file);
    p_fseek(file, 0, 0);
    mUnk0x4 = new char[mUnk0x10 + 1];
    mUnk0x10 = p_fread(mUnk0x4, 1, mUnk0x10, file);
    mUnk0x4[mUnk0x10] = 0;
    p_fclose(file);
    return true;
}

// FUNCTION: POPCAPGAME1 0x004c1a90
bool TextReader::EndOfFile() {
    return mUnk0x8 >= mUnk0x10;
}

// FUNCTION: POPCAPGAME1 0x004c1aa0
char TextReader::NextChar() {
    if (mUnk0x8 < mUnk0x10) {
        char c = mUnk0x4[mUnk0x8];
        mUnk0x8++;
        if (c == '\n') {
            mUnk0x14++;
        }
        return c;
    }
    return 0;
}

// FUNCTION: POPCAPGAME1 0x004c1ac0
char TextReader::PeekChar() {
    if (mUnk0x8 < mUnk0x10) {
        return mUnk0x4[mUnk0x8];
    }
    return 0;
}

// FUNCTION: POPCAPGAME1 0x004c1ae0
void TextReader::UngetChar() {
    if (0 < mUnk0x8) {
        mUnk0x8--;
        if (mUnk0x4[mUnk0x8] == '\n') {
            mUnk0x14--;
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004c1b00
void TextReader::UngetChars(int theNumChars) {
    for (int i = 0; i < theNumChars; i++) {
        UngetChar();
    }
}

// FUNCTION: POPCAPGAME1 0x004c1b30
void TextReader::Mark() {
    mUnk0xc = mUnk0x8;
}

// FUNCTION: POPCAPGAME1 0x004c1b20
void TextReader::RewindToMark() {
    mUnk0x8 = mUnk0xc;
}

// FUNCTION: POPCAPGAME1 0x004c1b40
void TextReader::SkipWhitespace() {
    while(!EndOfFile() && isspace(mUnk0x4[mUnk0x8])) {
        if (mUnk0x4[mUnk0x8] == '\n') {
            mUnk0x14++;
        }
        mUnk0x8++;
    }
}

// FUNCTION: POPCAPGAME1 0x004c1b90
bool TextReader::GotoChar(char theChar, bool param_2) {
    while (true) {
        if (EndOfFile()) {
            return false;
        }

        if (NextChar() == theChar) {
            break;
        }
    }

    if (!param_2) {
        UngetChar();
    }
    return true;
}

// FUNCTION: POPCAPGAME1 0x004c1bd0
bool TextReader::GotoString(char* theString, bool param_2) {
    int aTargetLength = strlen(theString);

    int anIndex = 0;

    while (!EndOfFile()) {
        char c = NextChar();

        if (c == theString[anIndex]) {
            anIndex++;

            if (anIndex >= aTargetLength) {
                if (!param_2) {
                    UngetChars(aTargetLength);
                }
                return true;
            }
        }
        else if (anIndex > 0) {
            UngetChars(anIndex);
            anIndex = 0;
        }
    }

    return false;
}
