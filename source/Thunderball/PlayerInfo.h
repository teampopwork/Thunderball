#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include <string>
#include <set>

namespace Sexy
{
struct DataSync;
struct GameStats;
enum SaveType {
	ARCADE = 1,
	STAGE = 2,
	DUEL = 3,
	TROPHY = 4,
};

class PlayerInfo
{
public:
	std::string mUnk0x4;
	int mUnk0x20;
	int mUnk0x24;
	int mUnk0x28;
	int mUnk0x30;
	int mUnk0x34;
	int mUnk0x40;
	int mUnk0x44;
	int mUnk0x48;
	bool mUnk0x4c;
	int mUnk0x50;
	bool mUnk0x60;
	bool mUnk0x61;
	bool mUnk0xec;
	std::multiset<int> mAdventureScores; // +0xf0
	int mUnk0x204;
	int mUnk0x208;
	int mUnk0x20c;

	PlayerInfo();
	PlayerInfo(PlayerInfo& param_1);
	virtual ~PlayerInfo();

	void SyncSummary(DataSync* theSync);
	int SyncDetails(DataSync* theSync);
	void SaveDetails();
	void SaveIfDirty();
	void LoadDetails();
	void DeleteUserFiles();

	std::string GetSavedGameName(SaveType theSaveType);
	void DeleteSavedGame(SaveType theSaveType);
	void DeleteSavedGames();

	void RestartAdventure();
	int GetMaxLevel();
	int GetAdventureEfficiencyBonus();
	bool JustBeatAdventure();
	bool JustStartingAdventure();

	void AddTotalStats(GameStats* theStats);
	int GetTrophyTopScore(int trophyId);
	bool CheckTrophyTopScore(int trophyId, int theScore);
	void AwardTrophy();
	void SubmitAdventureHighScore(int theScore);

	void SetColorblind(bool isColorblind);
	void SetSelCharacter(int theId);
	void SetSelCharacters(int param_1, int param_2);
	void SetComputerPlayer(bool isComputer);
	void SetComputerSkill(int theSkill);
	void SetLevelSelectStage(int theStage);

	void IncTip(int tipId);
	void DecTip(int tipId);
	void SetTip(int tipId);
	bool IsTipSet(int tipId);
	void IsLevelUnlocked(int param_1, int param_2);

	void Reset(bool param_1);

};

} // namespace Sexy

#endif // __PLAYERINFO_H__
