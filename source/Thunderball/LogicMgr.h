#ifndef __LOGIC_MGR_H__
#define __LOGIC_MGR_H__

#include "GameStats.h"
#include "PhysObj.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>
#include <set>
#include <string>

namespace Sexy
{

class Board;
class Graphics;
class Ball;
class Hole;
class DataSync;
class FloatingText;
class LevelStats;
enum KeyCode;
enum LogicState;
enum StyleShot;
enum PowerupType;

class LogicMgr {
	class ClickInfo {};

	class PegHitInfo {
	public:
		void SyncState(DataSync* theSync);
	};

	class BallPosInfo {};

public:
	int mUnk0x4;                            // +0x4
	int mUnk0x8;                            // +0x8
	int mUnk0xc;                            // +0xc
	int mUnk0x10;                           // +0x10
	int mUnk0x14;                           // +0x14
	bool mUnk0x18;                          // +0x18
	bool mUnk0x19;                          // +0x19
	bool mUnk0x1a;                          // +0x1a
	bool mUnk0x1b;                          // +0x1b
	bool mUnk0x1c;                          // +0x1c
	bool mUnk0x1d;                          // +0x1d
	bool mUnk0x1e;                          // +0x1e
	bool mUnk0x1f;                          // +0x1f
	bool mUnk0x20;                          // +0x20
	bool mUnk0x21;                          // +0x21
	int mUnk0x24;                           // +0x24
	int mUnk0x28;                           // +0x28
	int mUnk0x2c;                           // +0x2c
	int mUnk0x30;                           // +0x30
	int mUnk0x34;                           // +0x34
	int mUnk0x38;                           // +0x38
	int mUnk0x3c;                           // +0x3c
	int mUnk0x40;                           // +0x40
	int mUnk0x44;                           // +0x44
	int mUnk0x48;                           // +0x48
	int mUnk0x4c;                           // +0x4c
	int mUnk0x50;                           // +0x50
	int mUnk0x54;                           // +0x54
	bool mUnk0x68;                          // +0x68
	bool mUnk0x69;                          // +0x69
	float mUnk0x70;                         // +0x70
	int mUnk0x74;                           // +0x74
	int mUnk0x78;                           // +0x78
	std::string mUnk0x80;                   // +0x80
	int mUnk0xa0;                           // +0xa0
	int mUnk0xa4;                           // +0xa4
	bool mUnk0xa8;                          // +0xa8
	bool mUnk0xa9;                          // +0xa9
	bool mUnk0xaa;                          // +0xaa
	int mUnk0xac;                           // +0xac
	int mUnk0xb0;                           // +0xb0
	std::vector<PegHitInfo> mUnk0xb4;       // +0xb4
	std::list<ClickInfo> mUnk0xc4;          // +0xc4
	std::vector<BallPosInfo> mUnk0xd0;      // +0xd0
	int mUnk0xe0;                           // +0xe0
	float mUnk0xe4;                         // +0xe4
	int mUnk0xe8;                           // +0xe8
	bool mUnk0xed;                          // +0xed
	int mUnk0xf0;                           // +0xf0
	bool mUnk0xf4;                          // +0xf4
	bool mUnk0xf5;                          // +0xf5
	bool mUnk0xf6;                          // +0xf6
	bool mUnk0xf7;                          // +0xf7
	bool mUnk0xf8;                          // +0xf8
	bool mUnk0xf9;                          // +0xf9
	bool mUnk0xfa;                          // +0xfa
	bool mUnk0xfb;                          // +0xfb
	bool mUnk0xfc;                          // +0xfc
	bool mUnk0xfd;                          // +0xfd
	bool mUnk0xfe;                          // +0xfe
	bool mUnk0xff;                          // +0xff
	bool mUnk0x100;                         // +0x100
	bool mUnk0x101;                         // +0x101
	Board* mBoard;                          // +0x104
	int mUnk0x108;                          // +0x108
	int mUnk0x10c;                          // +0x10c
	int mUnk0x110;                          // +0x110
	int mUnk0x114;                          // +0x114
	int mUnk0x118;                          // +0x118
	int mUnk0x11c;                          // +0x11c
	int mUnk0x120;                          // +0x120
	bool mUnk0x124;                         // +0x124
	int mUnk0x128;                          // +0x128
	int mUnk0x12c;                          // +0x12c
	int mUnk0x130;                          // +0x130
	int mUnk0x134;                          // +0x134
	int mUnk0x138;                          // +0x138
	int mUnk0x13c;                          // +0x13c
	int mUnk0x140;                          // +0x140
	int mUnk0x144;                          // +0x144
	int mUnk0x148;                          // +0x148
	int mUnk0x14c;                          // +0x14c
	int mUnk0x150;                          // +0x150
	int mUnk0x154;                          // +0x154
	int mUnk0x158;                          // +0x158
	int mUnk0x15c;                          // +0x15c
	int mUnk0x160;                          // +0x160
	int mUnk0x164;                          // +0x164
	int mUnk0x168;                          // +0x168
	int mUnk0x16c;                          // +0x16c
	int mUnk0x174;                          // +0x174
	int mUnk0x178;                          // +0x178
	int mUnk0x17c;                          // +0x17c
	int mUnk0x180;                          // +0x180
	int mUnk0x184;                          // +0x184
	int mUnk0x188;                          // +0x188
	std::string mUnk0x18c;                  // +0x18c
	std::string mUnk0x1a8;                  // +0x1a8
	int mUnk0x1c4;                          // +0x1c4
	int mUnk0x1c8;                          // +0x1c8
	int mUnk0x1cc[4];                       // +0x1cc
	int mUnk0x1d0;                          // +0x1d0
	int mUnk0x1d4;                          // +0x1d4
	int mUnk0x1d8;                          // +0x1d8
	int mUnk0x1dc;                          // +0x1dc
	int mUnk0x1e4[4];                       // +0x1e4
	bool mUnk0x244;                         // +0x244
	bool mUnk0x245;                         // +0x245
	GameStats* mUnk0x248[2];                // +0x248
	int mUnk0x320;                          // +0x320
	int mUnk0x324;                          // +0x324
	int mUnk0x328;                          // +0x328
	int mUnk0x32c;                          // +0x32c
	float mUnk0x330;                        // +0x330
	float mUnk0x334;                        // +0x334
	float mUnk0x338;                        // +0x338
	float mUnk0x33c;                        // +0x33c
	std::list<SmartPtr<PhysObj>> mUnk0x340; // +0x340
	std::list<SmartPtr<PhysObj>> mUnk0x34c; // +0x34c
	std::set<SmartPtr<PhysObj>> mUnk0x358;  // +0x358
	std::set<SmartPtr<PhysObj>> mUnk0x364;  // +0x364
	LevelStats* mLevelStats;                // +0x370

	LogicMgr(Board* param_1);
	virtual ~LogicMgr();

	void Update();
	void Draw(Graphics* g);
	void DrawBack(Graphics* g);
	void MouseEnter();
	void MouseLeave();
	void MouseMove(int param_1, int param_2);
	void MouseDrag(int param_1, int param_2);
	void MouseDown(int param_1, int param_2, int param_3, bool param_4, bool param_5);
	void MouseUp(int param_1, int param_2, int param_3, bool param_4);
	void MouseWheel(int param_1);
	bool KeyChar(SexyChar param_1);
	bool KeyDown(KeyCode param_1);

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
	void UpdateInitLevel();
	void UpdateCharacterDialog();
	void IncScore(int param_1, bool param_2);
	void IncNumBalls(int param_1, int param_2, bool param_3);
	void IncShotScore(int param_1);
	int CalcScoreMult(int param_1);
	int CalcMusicIntensity(int param_1);
	void CalcCornerDisplay();
	void SetState(LogicState param_1);
	void SyncClickTimes(DataSync* theSync);
	void WriteClickTimes();
	void SyncState(DataSync* theSync);
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
	void SetGunAngle(float param_1);
	void CalcGunAngle(bool param_1);
	void FlipperClick(bool param_1);
	void CheckDoFlippers();
	void DoJimmy();
	void DoTimeBomb();
	void DoPowerup(Ball* param_1, PhysObj* param_2, PowerupType param_3, bool param_4);
	void DoWrapAround(Ball* param_1);
	void UpdateWrapAroundBall();
	FloatingText* AddStandardText(const std::string& param_1, float param_2, float param_3, int param_4);
	void AddStyleScoreText(int param_1, int param_2);
	int GetGoalPegsLeft();
	int GetRemainingGoalPeg();
	bool GetTotalMissIsFreeBall();
	int GetAdventureLevelReplayBonus();
	void KillSlowMoSound();
	void KillSighSound();
	void SpeedTransition();
	void SetCharacters(int param_1, int param_2);
	void SetWearHat(bool param_1);
	void RecordStats();
	void DoLevelDone();
	bool BeatLevel();
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
};

} // namespace Sexy

#endif // __LOGIC_MGR_H__
