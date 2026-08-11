#ifndef __TEXTREADER_H__
#define __TEXTREADER_H__

#include <string>

namespace Sexy {

class TextReader {
public:
    char* mUnk0x4;
    int mUnk0x8;
    int mUnk0xc;
    int mUnk0x10;
    int mUnk0x14;
    std::string mUnk0x18;
    std::string mUnk0x34;

    TextReader();
    TextReader(TextReader& param_1);
    virtual ~TextReader();

    void Close();
    bool Open(std::string& theFileName);
    bool EndOfFile();
    char NextChar();
    char PeekChar();
    void UngetChar();
    void UngetChars(int theNumChars);
    void Mark();
    void RewindToMark();
    void SkipWhitespace();
    bool GotoChar(char theChar, bool param_2);
    bool GotoString(char* theString, bool param_2);
};

}

#endif //__TEXTREADER_H__