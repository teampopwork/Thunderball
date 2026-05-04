#include "TypingCheck.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0041fc40
TypingCheck::TypingCheck(const std::string& param_1)
{
    SetPhrase(param_1);
}

// FUNCTION: POPCAPGAME1 0x0041d5f0
void TypingCheck::SetPhrase(const std::string& param_1) {
    mPhrase = param_1;
}

// STUB: POPCAPGAME1 0x00409230
bool TypingCheck::Check(char param_1) {
    return false;
}