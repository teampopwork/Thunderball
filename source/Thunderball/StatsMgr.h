#ifndef __STATSMGR_H__
#define __STATSMGR_H__

#include <string>

namespace Sexy
{
class LevelStats;
class TrophyStats;
class DataSync;

class StatsMgr
{
  public:

	StatsMgr();

	LevelStats*  GetStageStatsForLevel(std::string* param_1);
	LevelStats*  GetStatsForLevel(std::string* param_1);
	TrophyStats* GetStatsForTrophy(std::string* param_1);

	void IncCharacterCount(int param_1);
	void IncCharacterLossCount(int param_1);
	void IncCharacterWinCount(int param_1);
	void IncStageCharacterLossCount(int param_1);
	void IncStageCharacterWinCount(int param_1);
	void IncTrophyCharacterCount(int param_1);

	void Clear();
	bool Load(char* path);
	bool Save(char* path);
	void SyncState(DataSync* sync);
};
} // namespace Sexy

#endif // __STATSMGR_H__