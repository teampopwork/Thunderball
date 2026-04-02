#ifndef __STAGEMGR_H__
#define __STAGEMGR_H__

#include <string>

namespace Sexy
{
class ThunderballApp;
class PlayerInfo;
class LevelInfo;
class ConfigParser;
class StageInfo;

class StageInfo
{
  public:
	int GetLevelInfo(int);
};

class StageMgr
{
  public:
	StageMgr(ThunderballApp* theApp);
	~StageMgr();

	void       Clear();
	bool       GetLevelInfoByName(std::string* theName);
	int        GetNumStages();
	void       GetRandomLevel(int param_1, int param_2, int* param_3, int* param_4, bool param_5, int param_6, bool param_7);
	void       GetRandomLevel(PlayerInfo* param_1, int* param_2, int* param_3, bool param_4, int param_5, bool param_6);
	StageInfo* GetRandomLevel(PlayerInfo* param_1, bool param_2, int param_3);
	StageInfo* GetStageInfo(int param_1);
	int        GetTip(unsigned long param_1);
	void       Load(char* param_1);
	void       MarkLastUseTime(LevelInfo* param_1);
	void       ReadConfig(std::string* param_1);
	void       ReadKeyBal(ConfigParser* param_1);
	void       ReadStageConfig(ConfigParser* param_1, StageInfo* param_2);
	void       ResetLastUseTimes();
};

} // namespace Sexy

#endif // __STAGEMGR_H__