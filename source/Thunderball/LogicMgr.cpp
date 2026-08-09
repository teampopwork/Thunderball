#include "LogicMgr.h"

#include "AIMgr.h"
#include "Ball.h"
#include "Board.h"
#include "CharacterMgr.h"
#include "DebugMgr.h"
#include "Gun.h"
#include "InterfaceMgr.h"
#include "Poly.h"
#include "SoundMgr.h"
#include "ThunderCommon.h"
#include "ThunderButton.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00436f10
static float GetMouseAngleStep()
{
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1053,67", 0.1f);
}

// FUNCTION: POPCAPGAME1 0x004610d0
LogicMgr::LogicMgr(Board* param_1)
{
	mBoard = param_1;
	mUnk0x1cc[1] = POWERUP_0;
	mUnk0x1cc[0] = POWERUP_0;
	mUnk0x54 = 0;
	mUnk0x21 = 0;
	mUnk0xac = 0;
	mUnk0xb0 = 0;
	Clear(true, false);
}

// FUNCTION: POPCAPGAME1 0x0045c990
LogicMgr::~LogicMgr()
{
	KillSlowMoSound();
	KillSighSound();
}

// FUNCTION: POPCAPGAME1 0x004372c0
void LogicMgr::KillSlowMoSound()
{
	if (mUnk0xac != NULL) {
		mUnk0xac->Release();
		mUnk0xac = NULL;
	}
}

// FUNCTION: POPCAPGAME1 0x00458ab0
void LogicMgr::KillSighSound()
{
	if (mUnk0xb0 != NULL) {
		mBoard->mSoundMgr->AddFadeSound(mUnk0xb0);
		mUnk0xb0 = NULL;
	}
}

// STUB: POPCAPGAME1 0x004730d0
void LogicMgr::Update()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00448a30
void LogicMgr::Draw(Graphics* g)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00448820
void LogicMgr::DrawBack(Graphics* g)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00437340
void LogicMgr::MouseEnter()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00437340
void LogicMgr::MouseLeave()
{
}

// FUNCTION: POPCAPGAME1 0x0043d5d0
bool LogicMgr::MouseMove(int param_1, int param_2)
{
	if (mUnk0xe8 == 0 && !mUnk0x244[mUnk0x128])
	{
		mUnk0x70 = GetMouseAngleStep();
		mBoard->mGun->mAngularVelocity = 1000.0f;
		mUnk0x1f = true;
	}
	return true;
}

// FUNCTION: POPCAPGAME1 0x0043d620
bool LogicMgr::MouseDrag(int param_1, int param_2)
{
	if (mUnk0xe8 == 0 && !mUnk0x244[mUnk0x128] &&
		(param_1 != mUnk0x98 || param_2 != mUnk0x9c))
	{
		mUnk0x98 = -10000;
		mUnk0x9c = -10000;
		mUnk0x70 = GetMouseAngleStep();
		mBoard->mGun->mAngularVelocity = 1000.0f;
		mUnk0x1f = true;
	}
	return true;
}

// STUB: POPCAPGAME1 0x00472810
void LogicMgr::MouseDown(int param_1, int param_2, int param_3, bool param_4, bool param_5)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0045ebb0
void LogicMgr::MouseUp(int param_1, int param_2, int param_3, bool param_4)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0043d6a0
void LogicMgr::MouseWheel(int param_1)
{
	// TODO
}

bool LogicMgr::KeyChar(SexyChar param_1)
{
	return false;
}

bool LogicMgr::KeyDown(KeyCode param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x00440500
void LogicMgr::BeginInitLevel()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046e880
void LogicMgr::BeginTurn(bool param_1)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0044b5b0
void LogicMgr::BeginTurn2()
{
	if (mUnk0xf5)
	{
		SetState((LogicState) 0);
		return;
	}

	mBoard->mAIMgr->Clear();
	SetState((LogicState) 1);
	if (!mBoard->mDebugMgr->mUnk0x5)
		ActivateFreeBall(true);

	mUnk0x158 = 0;
	mUnk0x154 = 0;
	mUnk0x3c = 0;
	mUnk0x40 = 0;
	mUnk0x38 = 0;
	mUnk0x44 = 0;
	mUnk0x48 = 0;
	mUnk0x4c = 0;
	mUnk0x138 = 1;
	mUnk0x144 = -1;
	mUnk0xf7 = false;
	mUnk0x1d = false;
	mUnk0x1e = false;
	mUnk0xf9 = true;
	mBoard->Reload();
	mBoard->mInterfaceMgr->LoadGun();

	if (mFireballCount[mUnk0x128] > 0)
		mBoard->mGun->SetFireball(true);
	if (mUnk0x54)
		SetWearHat(true);
}

void LogicMgr::BeginShot(bool param_1)
{
	// TODO
}

void LogicMgr::StartInitLevel()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0045dda0
void LogicMgr::InitLevel(bool param_1, bool param_2, bool param_3)
{
	// TODO
}

void LogicMgr::ReInitLevel()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00470990
void LogicMgr::FinishInitLevel()
{
	// TODO
}

void LogicMgr::FinishShot()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00472f60
void LogicMgr::UpdateShot()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00471030
void LogicMgr::UpdatePostShot()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00471600
void LogicMgr::UpdatePostPostShot()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046d0c0
void LogicMgr::UpdateZenShot()
{
	// TODO
}

void LogicMgr::UpdateShotBalls()
{
	// TODO
}

void LogicMgr::UpdateBallBonus(bool param_1)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00466f10
void LogicMgr::UpdatePreShot()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046d630
void LogicMgr::UpdateGun()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00440830
void LogicMgr::UpdateFreeBallRadius()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0044b690
void LogicMgr::UpdateShotExtender()
{
	if (mBoard->mInterfaceMgr->mUnk0x160)
		BeginTurn2();
}

void LogicMgr::IncScore(int param_1, bool param_2)
{
	// TODO
}

void LogicMgr::IncNumBalls(int param_1, int param_2, bool param_3)
{
	// TODO
}

void LogicMgr::IncShotScore(int param_1)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x004370b0
int LogicMgr::CalcScoreMult(int param_1)
{
	if (param_1 <= 0 && !mUnk0xfb)
		return 100;
	if (param_1 <= 3)
		return 10;
	if (param_1 <= 6)
		return 5;
	if (param_1 <= 10)
		return 3;
	return param_1 <= 15 ? 2 : 1;
}

// FUNCTION: POPCAPGAME1 0x00437110
int LogicMgr::CalcMusicIntensity(int param_1)
{
	if (param_1 <= 3)
		return 6;
	if (param_1 <= 6)
		return 5;
	if (param_1 <= 10)
		return 4;
	if (param_1 <= 15)
		return 3;
	return param_1 <= 20 ? 2 : 1;
}

// FUNCTION: POPCAPGAME1 0x00436fb0
void LogicMgr::SetState(LogicState param_1)
{
	mUnk0x4 = param_1;
	mUnk0x8 = 0;
}

void LogicMgr::SyncClickTimes(DataSync* theSync)
{
	// TODO
}

void LogicMgr::WriteClickTimes()
{
	// TODO
}


void LogicMgr::SyncState(DataSync& theSync)
{
	// TODO
}

void LogicMgr::CheckCollisions()
{
	// TODO
}

void LogicMgr::CheckBallStop()
{
	// TODO
}

void LogicMgr::CheckPegHitSkillShot(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00466a0
void LogicMgr::RemoveHitPegs()
{
	// TODO
}

void LogicMgr::DoExploder(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

void LogicMgr::DoMultiball(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

void LogicMgr::DoStyleShot(float param_1, float param_2, StyleShot param_3, PhysObj* param_4)
{
	// TODO
}

void LogicMgr::DoStyleShot(Ball* param_1, StyleShot param_2)
{
	// TODO
}

void LogicMgr::PegHit(Ball* param_1, PhysObj* param_2, bool param_3)
{
	// TODO
}

void LogicMgr::HoleHit(Hole* param_1, Ball* param_2)
{
	// TODO
}

void LogicMgr::FreeBallHit(Hole* param_1, Ball* param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x004612e0
void LogicMgr::ActivatePowerup(PowerupType param_1, bool param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00461560
void LogicMgr::ActivatePowerups()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00457dc0
void LogicMgr::MakePowerupPeg()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00458110
void LogicMgr::MakeScorePeg()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00457960
void LogicMgr::MakeGoalPegs()
{
	// TODO
}

void LogicMgr::ClearFlipperSpace()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00437290
void LogicMgr::SetSlotMachineResult(int param_1)
{
	if (mUnk0x50 == 1)
		mUnk0x14c = param_1;
	else
		mUnk0x150 = param_1;
}

// FUNCTION: POPCAPGAME1 0x00437270
int LogicMgr::GetSlotMachineResult()
{
	if (mUnk0x50 == 1)
		return mUnk0x14c;
	return mUnk0x150;
}

// FUNCTION: POPCAPGAME1 0x00451ac0
int LogicMgr::GetSlotMachinePowerup()
{
	std::vector<int> aPowerups;
	for (int i = 0; i <= mUnk0x15c; ++i)
	{
		CharacterInfo* aCharacter = mBoard->mCharacterMgr->GetCharacterInfo(i);
		if (aCharacter != NULL && aCharacter->mUnk0x6C != 13)
			aPowerups.push_back(aCharacter->mUnk0x6C);
	}
	if (aPowerups.empty())
		aPowerups.push_back(1);

	int aSelector = mUnk0x50 == 1 ? mUnk0x30 : mUnk0x2c;
	return aPowerups[aSelector % aPowerups.size()];
}

// TODO: address unknown
void LogicMgr::DoSlotMachine(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0045e830
void LogicMgr::DoSlotMachineResult(int param_1, Ball* param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046ae60
void LogicMgr::FinishSlotMachine(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

void LogicMgr::DoFever()
{
	// TODO
}

void LogicMgr::DoFeverSlow()
{
	// TODO
}

void LogicMgr::DoFeverTron(Ball* param_1, PhysObj* param_2)
{
	// TODO
}

void LogicMgr::DoFeverMissed()
{
	// TODO
}

void LogicMgr::AddFeverSparks(Ball* param_1, bool param_2)
{
	// TODO
}

void LogicMgr::AddFeverScoreText()
{
	// TODO
}

void LogicMgr::UpdateFeverScoreText()
{
	// TODO
}

void LogicMgr::AddExtremeFeverEffect(int param_1)
{
	// TODO
}

void LogicMgr::SetGunAngle(float param_1)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0043ece0
void LogicMgr::CalcGunAngle(bool param_1)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00448370
void LogicMgr::CalcCornerDisplay()
{
	if (mBoard->mWidgetManager->IsMiddleButtonDown() &&
		!mBoard->mReplayButton->mIsOver && mUnk0x4 != 2)
	{
		mUnk0x80.assign("Fast Forward", 12);
		return;
	}
	if (mUnk0x68)
	{
		#pragma inline_depth(0)
		mUnk0x80.assign("Triple Score", 12);
		#pragma inline_depth(16)
		return;
	}
	if (mZenBallCount[mUnk0x128] > 0)
	{
		mUnk0x80.assign("ZenBall", 7);
		return;
	}
	if (mFireballCount[mUnk0x128] > 0)
	{
		mUnk0x80.assign("Fireball", 8);
		return;
	}
	if (mUnk0x69)
	{
		mUnk0x80 = "Magic Hat";
		return;
	}
	mUnk0x80 = "";
}

// STUB: POPCAPGAME1 0x0045ea70
void LogicMgr::FlipperClick(bool param_1)
{
	// TODO
}

void LogicMgr::CheckDoFlippers()
{
	// TODO
}

void LogicMgr::DoJimmy()
{
	// TODO
}

void LogicMgr::DoTimeBomb()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046edf0
void LogicMgr::DoPowerup(Ball* param_1, PhysObj* param_2, PowerupType param_3, bool param_4)
{
	// TODO
}

void LogicMgr::DoWrapAround(Ball* param_1)
{
	// TODO
}

void LogicMgr::UpdateWrapAroundBall()
{
	// TODO
}

FloatingText* LogicMgr::AddStandardText(const std::string& param_1, float param_2, float param_3, int param_4)
{
	return NULL;
}

void LogicMgr::AddStyleScoreText(int param_1, int param_2)
{
	// TODO
}

int LogicMgr::GetGoalPegsLeft()
{
	// TODO
	return 0;
}

int LogicMgr::GetRemainingGoalPeg()
{
	// TODO
	return 0;
}

bool LogicMgr::GetTotalMissIsFreeBall()
{
	// TODO
	return false;
}

int LogicMgr::GetAdventureLevelReplayBonus()
{
	// TODO
	return 0;
}

void LogicMgr::SpeedTransition()
{
	// TODO
}

void LogicMgr::SetCharacters(int param_1, int param_2)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0043d4d0
void LogicMgr::SetWearHat(bool param_1)
{
	mUnk0x54 = param_1;
	Ball* aBall = mBoard->mGun->mBall.get();
	if (aBall != NULL)
	{
		aBall->SetHat(param_1, false);
		if (param_1)
			aBall->SetAbsPos(aBall->mUnk0xec, aBall->mUnk0xf0);
	}
}

void LogicMgr::RecordStats()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046a9c0
void LogicMgr::DoLevelDone()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0043d580
bool LogicMgr::BeatLevel()
{
	if (mUnk0xfb)
		return mUnk0x358.empty() && mUnk0x364.empty();
	return mUnk0x358.empty();
}

void LogicMgr::ClearedLevel()
{
	// TODO
}

void LogicMgr::NotifySpookyCollision(PhysObj* param_1, PhysObj* param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046c220
void LogicMgr::FinishInitLevelText()
{
	// TODO
}

void LogicMgr::CheckDoCharacterDialog()
{
	// TODO
}

void LogicMgr::CheckDoStealthHelperShot()
{
	// TODO
}

void LogicMgr::DoHelperShot(bool param_1)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00440580
void LogicMgr::ActivateFreeBall(bool param_1)
{
	if (!mUnk0xf6 || !param_1)
	{
		std::list<SmartPtr<PhysObj> >& anObjList = mBoard->mUnk0x190;
		bool anActive = param_1 && mFreeBallCount[mUnk0x128] > 0;
		for (std::list<SmartPtr<PhysObj> >::iterator anItr = anObjList.begin();
			anItr != anObjList.end(); ++anItr)
		{
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x5c == "bumperhole")
			{
				anObj->SetActiveWithGrowAnim(anActive);
				if (anObj->mUnk0x10 == 5 && anObj->mUnk0xb0 == 1 && mUnk0x4 == 2)
				{
					static_cast<Poly*>(anObj)->mUnk0x140 = ModVal(
						0,
						"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1078,1463",
						300
					);
				}

				if (anObj->mUnk0xb0 == 1)
					anObj->mUnk0x24 = false;
				else
					anObj->mUnk0x25 = false;
			}
			else if (anObj->mUnk0x5c == "freeball")
			{
				anObj->SetActive(param_1);
				if (anObj->mUnk0x10 != 1)
				{
					if (anObj->mUnk0x28)
						anObj->mUnk0x24 = false;
					else
						anObj->mUnk0x25 = false;
				}
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00440700
void LogicMgr::ActivateFreeBallCover(bool param_1)
{
	if (!mUnk0xf6 || !param_1)
	{
		for (std::list<SmartPtr<PhysObj> >::iterator anItr = mBoard->mUnk0x190.begin();
			anItr != mBoard->mUnk0x190.end(); ++anItr)
		{
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x5c == "freeballcover")
				anObj->SetActiveWithGrowAnim(param_1);
		}
	}
}

// STUB: POPCAPGAME1 0x0046ce00
void LogicMgr::UpdateLevelDone()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00471500
void LogicMgr::UpdateTotalMiss()
{
	// TODO
}

void LogicMgr::Clear(bool param_1, bool param_2)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00469f30
void LogicMgr::DoBeginTurnText()
{
	// TODO
}

// STUB: POPCAPGAME1 0x0046a370
void LogicMgr::DoBeginTurnTip(int param_1)
{
	// TODO
}

// STUB: POPCAPGAME1 0x004484a0
void LogicMgr::UpdateInitLevel()
{
	// TODO
}

// STUB: POPCAPGAME1 0x004709f0
void LogicMgr::UpdateCharacterDialog()
{
	// TODO
}
