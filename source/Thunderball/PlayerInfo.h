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
	std::string m_unk0x4;
	int m_unk0x20;
	int m_unk0x24;
	int m_unk0x28;
	int m_unk0x30;
	int m_unk0x34;
	int m_unk0x40;
	int m_unk0x44;
	int m_unk0x48;
	bool m_unk0x4c;
	int m_unk0x50;
	bool m_unk0x60;
	bool m_unk0x61;
	bool m_unk0xec;
	std::multiset<int> mAdventureScores; // +0xf0
	int m_unk0x204;
	int m_unk0x208;
	int m_unk0x20c;

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
