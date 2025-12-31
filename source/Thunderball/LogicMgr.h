#ifndef __LOGIC_MGR_H__
#define __LOGIC_MGR_H__

namespace Sexy
{

class Board;
class Graphics;
class Ball;
class PhysObj;
class Hole;
class DataSync;
class KeyCode;
enum PowerupType : int;
enum StyleShot : int;
enum LogicState : int;

class LogicMgr {
public:
	LogicMgr(Board* param_1);
	virtual ~LogicMgr();

	void Update();
	void Draw(Graphics* param_1);
	void DrawBack(Graphics* param_1);
	void MouseEnter();
	void MouseLeave();
	void MouseMove(int param_1, int param_2);
	void MouseDrag(int param_1, int param_2);
	void MouseDown(int param_1, int param_2, int param_3, bool param_4, bool param_5);
	void MouseUp(int param_1, int param_2, int param_3, bool param_4);
	void MouseWheel(int param_1);
	void KeyChar(char param_1);
	void KeyDown(KeyCode param_1);

	void BeginInitLevel();
	void BeginTurn(bool param_1);
	void BeginTurn2();
	void BeginShot(bool param_1);
	void StartInitLevel();
	void InitLevel(bool param_1, bool param_2, bool param_3);
	void ReInitLevel();
	void FinishInitLevel();
	void FinishShot();
	void UpdateShot();
	void UpdatePostShot();
	void UpdatePostPostShot();
	void UpdateZenShot();
	void UpdateShotBalls();
	void UpdateBallBonus(bool param_1);
	void UpdatePreShot();
	void UpdateGun();
	void UpdateFreeBallRadius();
	void UpdateShotExtender();
	void UpdateInitLevel();]
    void UpdateCharacterDialog();
	void IncScore(int param_1, bool param_2);
	void IncNumBalls(int param_1, int param_2, bool param_3);
	void IncShotScore(int param_1);
	int CalcScoreMult(int param_1);
	int CalcMusicIntensity(int param_1);
	void CalcCornerDisplay();
	void SetState(LogicState param_1);
	void SyncClickTimes(DataSync* param_1);
	void WriteClickTimes();
	void SyncState(DataSync* param_1);
	void CheckCollisions();
	void CheckBallStop();
	void CheckPegHitSkillShot(Ball* param_1, PhysObj* param_2);
	void RemoveHitPegs();
	void DoExploder(Ball* param_1, PhysObj* param_2);
	void DoMultiball(Ball* param_1, PhysObj* param_2);
	void DoStyleShot(float param_1, float param_2, StyleShot param_3, PhysObj* param_4);
	void DoStyleShot(Ball* param_1, StyleShot param_2);
	void PegHit(Ball* param_1, PhysObj* param_2, bool param_3);
	void HoleHit(Hole* param_1, Ball* param_2);
	void FreeBallHit(Hole* param_1, Ball* param_2);
	void ActivatePowerup(PowerupType param_1, bool param_2);
	void ActivatePowerups();
	void MakePowerupPeg();
	void MakeScorePeg();
	void MakeGoalPegs();
	void ClearFlipperSpace();
	void SetSlotMachineResult(int param_1);
	int GetSlotMachineResult();
	int GetSlotMachinePowerup();
	void DoSlotMachine(Ball* param_1, PhysObj* param_2);
	void DoSlotMachineResult(int param_1, Ball* param_2);
	void FinishSlotMachine(Ball* param_1, PhysObj* param_2);
	void DoFever();
	void DoFeverSlow();
	void DoFeverTron(Ball* param_1, PhysObj* param_2);
	void DoFeverMissed();
	void AddFeverSparks(Ball* param_1, bool param_2);
	void AddFeverScoreText();
	void UpdateFeverScoreText();
	void AddExtremeFeverEffect(int param_1);
	void DoFeverSlow();
	void SetGunAngle(float param_1);
	void CalcGunAngle(bool param_1);
	void FlipperClick(bool param_1);
	void CheckDoFlippers();
	void DoJimmy();
	void DoTimeBomb();
	void DoPowerup(Ball* param_1, PhysObj* param_2, PowerupType param_3, bool param_4);
	void DoWrapAround(Ball* param_1);
	void UpdateWrapAroundBall();
	void AddStandardText(const std::string& param_1, float param_2, float param_3, int param_4);
	void AddStyleScoreText(int param_1, int param_2);
	void AddFeverScoreText();
	void FinishSlotMachine(Ball* param_1, PhysObj* param_2);
	int GetGoalPegsLeft();
	int GetRemainingGoalPeg();
	bool GetTotalMissIsFreeBall();
	int GetAdventureLevelReplayBonus();
	void KillSlowMoSound();
	void KillSighSound();
	void SpeedTransition();
	void SetCharacters(int param_1, int param_2);
	void SetWearHat(bool param_1);
	void SyncClickTimes(DataSync* param_1);
	void RecordStats();
	void DoLevelDone();
	void BeatLevel();
	void ClearedLevel();
	void NotifySpookyCollision(PhysObj* param_1, PhysObj* param_2);
	void FinishInitLevelText();
	void CheckDoCharacterDialog();
	void CheckDoStealthHelperShot();
	void DoHelperShot(bool param_1);
	void ActivateFreeBall(bool param_1);
	void ActivateFreeBallCover(bool param_1);
	void UpdateLevelDone();
	void UpdateTotalMiss();
	void Clear(bool param_1, bool param_2);
	void DoBeginTurnText();
	void DoBeginTurnTip(int param_1);

private:
	Board* mBoard;
};

} // namespace Sexy

#endif // __LOGIC_MGR_H__
