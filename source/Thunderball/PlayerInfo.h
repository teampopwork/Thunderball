#ifndef __PLAYERINFO_H__
#define __PLAYERINFO_H__

#include <string>

namespace Sexy
{
struct DataSync;
struct GameStats;
enum class GameMode : int;

class PlayerInfo
{
public:
	PlayerInfo();
	PlayerInfo(PlayerInfo& param_1);
	virtual ~PlayerInfo();

	int SyncSummary(DataSync* theSync);
	int SyncDetails(DataSync* theSync);
	void SaveDetails();
	void SaveIfDirty();
	void LoadDetails();
	void DeleteUserFiles();

	std::string GetSavedGameName(GameMode theMode);
	void DeleteSavedGame(GameMode theMode);
	void DeleteSavedGames();

	// Adventure / level state
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

	void Reset(bool param_1);

};

} // namespace Sexy

#endif // __PLAYERINFO_H__
