#ifndef __STAGEMGR_H__
#define __STAGEMGR_H__

#include <SexyAppFramework/SmartPtr.h>
#include <set>
#include <string>
#include <vector>

namespace Sexy
{
class ThunderballApp;
class PlayerInfo;
class ConfigParser;

class StoryData : public RefCount {};

class LevelInfo : public RefCount {
public:
	LevelInfo();
	virtual ~LevelInfo();

	int mUnk0x8;
	int mUnk0xc;
	int mUnk0x10;
	std::string mUnk0x14;
	std::string mUnk0x34;
	std::string mUnk0x50;
	std::string mUnk0x6c;
};

class StageInfo : public RefCount {
public:
	StoryData mUnk0x8[5];
	std::vector<SmartPtr<LevelInfo>> mUnk0x5c;

	StageInfo();
	virtual ~StageInfo();
	LevelInfo* GetLevelInfo(int param_1);
};

class StageMgr {
public:
	ThunderballApp* mApp; // +0x4
	int mUnk0x8;
	std::vector<SmartPtr<StageInfo>> mUnk0xc;
	std::multimap<std::string, SmartPtr<LevelInfo>> mUnk0x1c;
	std::vector<std::string> mUnk0x2c;

	StageMgr(ThunderballApp* theApp);
	virtual ~StageMgr();

	void Clear();
	LevelInfo* GetLevelInfoByName(const std::string& theName);
	int GetNumStages();
	void GetRandomLevel(int param_1, int param_2, int* param_3, int* param_4, bool param_5, int param_6, bool param_7);
	void GetRandomLevel(PlayerInfo* param_1, int* param_2, int* param_3, bool param_4, int param_5, bool param_6);
	LevelInfo* GetRandomLevel(PlayerInfo* param_1, bool param_2, int param_3);
	StageInfo* GetStageInfo(int param_1);
	int GetTip(unsigned long param_1);
	void Load(char* param_1);
	void MarkLastUseTime(LevelInfo* param_1);
	void ReadConfig(const std::string& param_1);
	void ReadKeyVal(ConfigParser* param_1);
	void ReadStageConfig(ConfigParser* param_1, StageInfo* param_2);
	void ResetLastUseTimes();
};

} // namespace Sexy

#endif // __STAGEMGR_H__
