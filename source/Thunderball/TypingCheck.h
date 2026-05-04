#ifndef __TYPINGCHECK_H__
#define __TYPINGCHECK_H__

#include <string>

namespace Sexy
{
class TypingCheck
{
public:
    std::string mPhrase; // +0x0

    TypingCheck(const std::string& param_1);
    void SetPhrase(const std::string& param_1);
    bool Check(char param_1);
};

} // namespace Sexy

#endif  // __TYPINGCHECK_H__