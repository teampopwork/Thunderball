#include "TypingCheck.h"

#include <ctype.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0041fc40
TypingCheck::TypingCheck(const std::string& param_1)
{
    SetPhrase(param_1);
}

// FUNCTION: POPCAPGAME1 0x0041d5f0
void TypingCheck::SetPhrase(const std::string& param_1) {
    mPhrase = param_1;
	mProgress = 0;
}

// FUNCTION: POPCAPGAME1 0x00409230
bool TypingCheck::Check(char param_1) {
	if (!mPhrase.empty()) {
		if (tolower((unsigned char)mPhrase[mProgress]) == tolower((unsigned char)param_1)) {
			++mProgress;
			if (mProgress == mPhrase.size()) {
				mProgress = 0;
				return true;
			}
		} else {
			mProgress = 0;
		}
	}
    return false;
}
