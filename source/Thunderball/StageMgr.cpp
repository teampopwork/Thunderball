#include "StageMgr.h"

using namespace Sexy;

StageMgr::StageMgr(ThunderballApp* theApp)
{
}

StageMgr::~StageMgr()
{
}

void StageMgr::Clear()
{
}

bool StageMgr::GetLevelInfoByName(std::string* theName)
{
	return false;
}

int StageMgr::GetNumStages()
{
	return 0;
}

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
}

void StageMgr::GetRandomLevel(PlayerInfo* param_1, int* param_2, int* param_3, bool param_4, int param_5, bool param_6)
{
}

StageInfo* StageMgr::GetRandomLevel(PlayerInfo* param_1, bool param_2, int param_3)
{
	return NULL;
}

StageInfo* StageMgr::GetStageInfo(int param_1)
{
	return NULL;
}

int StageMgr::GetTip(unsigned long param_1)
{
	return 0;
}

void StageMgr::Load(char* param_1)
{
}

void StageMgr::MarkLastUseTime(LevelInfo* param_1)
{
}

void StageMgr::ReadConfig(std::string* param_1)
{
}

void StageMgr::ReadKeyBal(ConfigParser* param_1)
{
}

void StageMgr::ReadStageConfig(ConfigParser* param_1, StageInfo* param_2)
{
}

void StageMgr::ResetLastUseTimes()
{
}
