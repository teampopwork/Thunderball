#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include <set>
#include <map>
#include <string>
#include <utility>
#include <SexyAppFramework/SexyAppBase.h>
#include "GameStats.h"

namespace Sexy
{
class DataSync;
class GameStats;

enum GameMode {
	ARCADE = 1,
	STAGE = 2,
	DUEL = 3,
	TROPHY = 4,
};

class PlayerInfo {
public:
	std::string mName;    // +0x04
	unsigned int mUseSeq; // +0x20
	unsigned int mId;     // +0x24
	int mUnk0x28;
	int mUnk0x2c;
	int mUnk0x30;
	int mUnk0x34;
	int mUnk0x38;
	int mUnk0x3c;
	int mUnk0x40;
	int mUnk0x44;
	int mUnk0x48;
	bool mUnk0x4c;
	int mUnk0x50;
	int mUnk0x54;
	int mUnk0x58;
	int mUnk0x5c;
	bool mUnk0x60;
	bool mUnk0x61;
	int mUnk0x64;
	int mUnk0x68;
	int mUnk0x6c;
	int mUnk0x70;
	int mUnk0x74;
	int mUnk0x78;
	int mUnk0x7c;
	int mUnk0x80;
	int mUnk0x84;
	int mUnk0x88;
	int mUnk0x8c;
	int mUnk0x90;
	int mUnk0x94;
	std::string mUnk0x98;
	std::string mUnk0xb4;
	std::string mUnk0xd0;
	bool mUnk0xec;
	bool mUnk0xed;
	unsigned char mUnk0xee;
	bool mUnk0xef;
	std::multiset<int> mAdventureScores; // +0xf0
	std::multiset<int> mUnk0xfc;         // +0xfc
	std::map<int, class MemoryImage*, std::greater<int> > mUnk0x108; // +0x108
	int mUnk0x114;
	std::set<std::string, struct StringLessNoCase> mUnk0x118;        // +0x118
	int mUnk0x124;
	int mUnk0x128;
	GameStats mUnk0x12c;
	GameStats mUnk0x198;
	int mUnk0x204;
	int mUnk0x208;
	int mUnk0x20c;

	PlayerInfo();
	PlayerInfo(const PlayerInfo& param_1);
	virtual ~PlayerInfo();

	PlayerInfo& operator=(const PlayerInfo& thePlayerInfo);

	void SyncSummary(DataSync& theSync);
	int SyncDetails(DataSync& theSync);
	void SaveDetails();
	void SaveIfDirty();
	void LoadDetails();
	void DeleteUserFiles();

	std::string GetSavedGameName(GameMode theGameMode);
	void DeleteSavedGame(GameMode theGameMode);
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
