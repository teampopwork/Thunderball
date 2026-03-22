#include "StatsMgr.h"

using namespace Sexy;

StatsMgr::StatsMgr()
{
}

LevelStats* StatsMgr::GetStageStatsForLevel(std::string* param_1)
{
    return NULL;
}

LevelStats* StatsMgr::GetStatsForLevel(std::string* param_1)
{
    return NULL;
}

TrophyStats* StatsMgr::GetStatsForTrophy(std::string* param_1)
{
    return NULL;
}

void StatsMgr::IncCharacterCount(int param_1)
{
}

void StatsMgr::IncCharacterLossCount(int param_1)
{
}

void StatsMgr::IncCharacterWinCount(int param_1)
{
}

void StatsMgr::IncStageCharacterLossCount(int param_1)
{
}

void StatsMgr::IncStageCharacterWinCount(int param_1)
{
}

void StatsMgr::IncTrophyCharacterCount(int param_1)
{
}

void StatsMgr::Clear()
{
}

bool StatsMgr::Load(char* path)
{
    return false;
}

bool StatsMgr::Save(char* path)
{
    return false;
}

void StatsMgr::SyncState(DataSync* sync)
{
}
