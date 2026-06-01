#include "StageMgr.h"

#include "PlayerInfo.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0045f810
// Sexy::StoryData::~StoryData

// FUNCTION: POPCAPGAME1 0x00441fd0
LevelInfo::LevelInfo()
{
}

// SYNTHETIC: POPCAPGAME1 0x00442f00
// Sexy::LevelInfo::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00442020
LevelInfo::~LevelInfo()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x00461a00
StageInfo::StageInfo()
{
}

// SYNTHETIC: POPCAPGAME1 0x00464d90
// Sexy::StageInfo::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00461a70
StageInfo::~StageInfo()
{
}

// FUNCTION: POPCAPGAME1 0x0043d7d0
LevelInfo* StageInfo::GetLevelInfo(int param_1)
{
	if (param_1 < 0 || param_1 >= (int) mUnk0x5c.size()) {
		return NULL;
	}
	else {
		return mUnk0x5c[param_1].get();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x00461940
StageMgr::StageMgr(ThunderballApp* theApp)
{
	mApp = theApp;
}

// SYNTHETIC: POPCAPGAME1 0x004619d0
// Sexy::StageMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0045f380
StageMgr::~StageMgr()
{
}

// FUNCTION: POPCAPGAME1 0x0045f460
void StageMgr::Clear()
{
	mUnk0x8 = 0;
	mUnk0xc.clear();
	mUnk0x1c.clear();
	mUnk0x2c.clear();
}

// FUNCTION: POPCAPGAME1 0x00442ff0
LevelInfo* StageMgr::GetLevelInfoByName(const std::string& theName)
{
	std::multimap<std::string, SmartPtr<LevelInfo>>::iterator it = mUnk0x1c.find(theName);
	if (it == mUnk0x1c.end()) {
		return NULL;
	}
	else {
		return it->second.get();
	}
}

// FUNCTION: POPCAPGAME1 0x0043d870
int StageMgr::GetNumStages()
{
	return (int) mUnk0xc.size();
}

// STUB: POPCAPGAME1 0x00459060
void StageMgr::GetRandomLevel(
	int param_1,
	int param_2,
	int* param_3,
	int* param_4,
	bool param_5,
	int param_6,
	bool param_7
)
{
	printf("StageMgr::GetRandomLevel stub called\n");
}

// FUNCTION: POPCAPGAME1 0x004592b0
void StageMgr::GetRandomLevel(PlayerInfo* param_1, int* param_2, int* param_3, bool param_4, int param_5, bool param_6)
{
	GetRandomLevel(param_1->mUnk0x28, param_1->mUnk0x2c, param_2, param_3, param_4, param_5, true);
}

// FUNCTION: POPCAPGAME1 0x004592e0
LevelInfo* StageMgr::GetRandomLevel(PlayerInfo* param_1, bool param_2, int param_3)
{
	int stageNum = -1;
	int levelNum = -1;
	GetRandomLevel(param_1, &stageNum, &levelNum, param_2, param_3, true);
	StageInfo* stage = GetStageInfo(stageNum);
	if (stage == NULL) {
		return NULL;
	}
	else {
		return stage->GetLevelInfo(levelNum);
	}
}

// FUNCTION: POPCAPGAME1 0x0043d820
StageInfo* StageMgr::GetStageInfo(int param_1)
{
	if (-1 <= param_1 && param_1 < (int) mUnk0xc.size()) {
		return mUnk0xc[param_1].get();
	}
	else {
		return NULL;
	}
}

// STUB: POPCAPGAME1 0x00442f30
int StageMgr::GetTip(unsigned long param_1)
{
	return 0;
}

// FUNCTION: POPCAPGAME1 0x00468830
void StageMgr::Load(char* param_1)
{
	if (param_1 != NULL) {
		std::string path = param_1;
		ReadConfig(path);
	}
	else {
		std::string path = "levels/stages.cfg";
		ReadConfig(path);
	}
}

// STUB: POPCAPGAME1 0x00437620
void StageMgr::MarkLastUseTime(LevelInfo* param_1)
{
}

// STUB: POPCAPGAME1 0x004685f0
void StageMgr::ReadConfig(const std::string& param_1)
{
}

// STUB: POPCAPGAME1 0x00468300
void StageMgr::ReadKeyVal(ConfigParser* param_1)
{
}

// STUB: POPCAPGAME1 0x00467d50
void StageMgr::ReadStageConfig(ConfigParser* param_1, StageInfo* param_2)
{
}

// STUB: POPCAPGAME1 0x0043d890
void StageMgr::ResetLastUseTimes()
{
}
