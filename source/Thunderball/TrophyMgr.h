
#ifndef __TROPHY_MGR_H__
#define __TROPHY_MGR_H__

#include <string>
#include <vector>

#include <SexyAppFramework/SmartPtr.h>

namespace Sexy
{
class ThunderballApp;
class ConfigParser;
class OpponentInfo {};

class TrophyInfo : public RefCount {
public:
    int mId; // +0x8
    bool mUnk0x60; // +0x60
    int mUnk0x6c; // +0x6c
    int mUnk0x70; // +0x70
    bool mUnk0x74; // +0x74
    std::vector<std::string>* mUnk0x78; // +0x78
    int mUnk0x7c; // +0x7c
    int mUnk0x80; // +0x80
    std::vector<OpponentInfo> mUnk0x88; // +0x88
};

struct TrophyPage;

class TrophyMgr {
public:
	char padding[0x1c];
	int mUnk0x20;

	TrophyMgr(ThunderballApp* theApp);
	virtual ~TrophyMgr();

	void Clear();

	bool Load(char* theFile);
	bool ReadConfig(const std::string& thePath);
	bool ReadTrophyPage(ConfigParser* theParser);
	bool ReadTrophyConfig(ConfigParser* theParser, TrophyInfo* theInfo);

	TrophyInfo* GetTrophyInfoById(int theId);
	TrophyPage* GetTrophyPage(int theId);
};

} // namespace Sexy

#endif // __TROPHY_MGR_H__
