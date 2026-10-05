#include "LogicMgr.h"

#include "AIMgr.h"
#include "Ball.h"
#include "Board.h"
#include "CharacterMgr.h"
#include "ConstEnums.h"
#include "DebugMgr.h"
#include "EffectMgr.h"
#include "EndLevelDialog.h"
#include "FloatingTextMgr.h"
#include "Gun.h"
#include "InterfaceMgr.h"
#include "Mover.h"
#include "PegInfo.h"
#include "PlayerInfo.h"
#include "Poly.h"
#include "Res.h"
#include "SoundMgr.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

static int KILLBALL_TIME1 = 1500;
static int KILLBALL_TIME3 = 500;

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

// TEMPLATE: POPCAPGAME1 0x0040e2d0
// std::_Tree<std::_Tset_traits<Sexy::SmartPtr<Sexy::PhysObj>,std::less<Sexy::SmartPtr<Sexy::PhysObj> >,std::allocator<Sexy::SmartPtr<Sexy::PhysObj> >,0> >::erase(class std::_Tree<class std::_Tset_traits<class Sexy::SmartPtr<class Sexy::PhysObj>, struct std::less<class Sexy::SmartPtr<class Sexy::PhysObj>>, class std::allocator<class Sexy::SmartPtr<class Sexy::PhysObj>>, 0>>::iterator, class std::_Tree<class std::_Tset_traits<class Sexy::SmartPtr<class Sexy::PhysObj>, struct std::less<class Sexy::SmartPtr<class Sexy::PhysObj>>, class std::allocator<class Sexy::SmartPtr<class Sexy::PhysObj>>, 0>>::iterator)

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

// FUNCTION: POPCAPGAME1 0x004730d0
void LogicMgr::Update()
{
	if (mUnk0xf5 && mUnk0x4 == 2 && !mUnk0xc4.empty()) {
		for (std::list<ClickInfo*>::iterator anItr = mUnk0xc4.begin(); anItr != mUnk0xc4.end(); ++anItr) {
			ClickInfo* aClickInfo = *anItr;
			if (aClickInfo->mUnk0xc) {
				MouseDown(0, 0, (aClickInfo->mUnk0xd == false) * 2 - 1, true, false);
			}
			else {
				MouseUp(0, 0, (aClickInfo->mUnk0xd == false) * 2 - 1, false);
			}
			mUnk0xc4.erase(anItr);
		}
	}

	if (mUnk0xe8 != 0) {
		mUnk0xe8--;
	}

	UpdateGun();
	if (!mBoard->mUnk0xc2) {
		mUnk0x8++;
		if (mUnk0x134 != 0) {
			UpdateFreeBallRadius();
		}

		if (mUnk0xc != 0 && mUnk0xc-- == 0) {
			RemoveHitPegs();
		}

		switch (mUnk0x4) {
		case 1:
			UpdatePreShot();
			break;
		case 2:
			UpdateShot();
			break;
		case 3:
			UpdatePostShot();
			break;
		case 4:
			UpdateTotalMiss();
			break;
		case 5:
			UpdateLevelDone();
			break;
		case 6:
			UpdatePostPostShot();
			break;
		case 7:
			UpdateShotExtender();
			break;
		case 8:
			UpdateInitLevel();
			break;
		case 9:
			UpdateCharacterDialog();
			break;
		case 10:
			UpdateZenShot();
			break;
		}
	}
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
	if (mUnk0xe8 == 0 && !mUnk0x244[mUnk0x128]) {
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
		(param_1 != mUnk0x98 || param_2 != mUnk0x9c)) {
		mUnk0x98 = -10000;
		mUnk0x9c = -10000;
		mUnk0x70 = GetMouseAngleStep();
		mBoard->mGun->mAngularVelocity = 1000.0f;
		mUnk0x1f = true;
	}
	return true;
}

// FUNCTION: POPCAPGAME1 0x00472810
bool LogicMgr::MouseDown(int param_1, int param_2, int param_3, bool param_4, bool param_5)
{
	mUnk0x98 = param_1;
	mUnk0x9c = param_2;

	if (param_3 < 0 && mUnk0x4 != 8) {
		CalcCornerDisplay();
		return false;
	}

	if (mUnk0xf5) {
		if (!param_4) {
			return true;
		}

		if (mUnk0xf5) {
			param_5 = true;
		}
	}

	if (mUnk0x4 == 5 && mUnk0xfd && mUnk0x8 < 100) {
		mUnk0x8 = 100;
		mBoard->mFloatingTextMgr->EraseText(mUnk0x34);
		mUnk0x34 = 0;
		if (mBoard->mApp->TryShowNewTrophy()) {
			return true;
		}

		Effect* anEffect1 = mBoard->mEffectMgr->GetEffectByType(EffectType::EFFECT_7);
		if (anEffect1 != NULL) {
			anEffect1 = mBoard->mEffectMgr->SetPriority(anEffect1, 2);
			anEffect1->mUnk0x10 = anEffect1->mUnk0xc + 20;
		}

		Effect* anEffect2 = mBoard->mEffectMgr->GetEffectByType(EffectType::EFFECT_33);
		if (anEffect2 != NULL) {
			return true;
		}

		anEffect2->mUnk0x10 = anEffect2->mUnk0xc + 20;
		mBoard->mApp->ShowTrophyScreen();
		return true;
	}

	bool bVar4 = false;
	if (!mUnk0xf5 && mUnk0x4 == 2) {
		ClickInfo aClickInfo;
		aClickInfo.mUnk0x8 = mUnk0x8;
		if (param_5) {
			aClickInfo.mUnk0x8--;
		}
		aClickInfo.mUnk0xc = param_3 < 0;
		aClickInfo.mUnk0xd = false;
		mUnk0xc4.push_back(&aClickInfo);
		bVar4 = true;
	}

	int killTime = KILLBALL_TIME1;
	if (0 < param_3) {
		if (mUnk0x4 == 1 && mUnk0x244[mUnk0x128] == 0) {
			if (mUnk0x138 != 0) {
				return true;
			}

			mUnk0xed = true;
			return true;
		}

		if (mUnk0x4 != 2) {
			if (mUnk0xc4.size() != 0 && bVar4) {
				mUnk0xc4.pop_front();
			}

			SpeedTransition();
			return true;
		}

		if (mUnk0x1d) {
			mUnk0xf7 = true;
			mUnk0x1d = killTime < mUnk0x38;
			return true;
		}

		if (!mBoard->mUnk0xc1) {
			if (mUnk0x244[mUnk0x128] != 0 && !param_5) {
				if (mUnk0xc4.size() == 0) {
					return true;
				}
				if (!bVar4) {
					return true;
				}
				mUnk0xc4.pop_front();
				return true;
			}
		}
		else if (mUnk0xf5 == 0 && (mUnk0xf9 = false, mBoard->mUnk0xc8 != 0)) {
			mBoard->mUnk0xc8 = 1;
		}
		if (mUnk0x20 != 0) {
			mUnk0x20 = 0;
			PlayerInfo* aPlayerInfo = mBoard->mApp->mCurProfile;
			if (mUnk0xf5 == 0 && aPlayerInfo != NULL && aPlayerInfo->mUnk0x54 < 100) {
				aPlayerInfo->mUnk0x54++;
				aPlayerInfo->mUnk0xec = true;
			}
		}

		mUnk0x1e++;
	}

	if (mUnk0x1e4[mUnk0x128] < 1) {
		if (mUnk0x4 == 2) {
			if (mUnk0x22c[mUnk0x128] < 1) {
				int aMaxLevel = mBoard->mApp->GetMaxLevel();
				if (aMaxLevel == 0 && 0 < param_3 && !mUnk0xf6 && !mBoard->mUnk0xc1) {
					FloatingText* aFloatingText = mBoard->mFloatingTextMgr->GetTextById(mUnk0x34);
					if (aFloatingText == NULL) {
						float fVar1 = mBoard->mGun->mUnk0x114;
						int Mod1 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1251,4077", 0x6e);
						float fVar2 = mBoard->mGun->mUnk0x118;
						std::string aText = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1252,4079", "You can only fire ^00FF00^one ball^oldclr^ at a time!^oldclr^");
						aFloatingText = AddStandardText(aText, fVar1, Mod1 + fVar2, 14);
						int Mod2 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1253,4080", 0xffffff);
						aFloatingText->mUnk0x8c = 0;
						aFloatingText->mUnk0x60 = Mod2;
						aFloatingText->mUnk0x68 = 200;
						aFloatingText->mUnk0x74 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1254,4083", 10);
						aFloatingText->mUnk0x78 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1255,4084", 0x1e);
						aFloatingText->mUnk0x9c = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1256,4085", true);
						mUnk0x34 = aFloatingText->mId;
					}
					mBoard->mSoundMgr->AddSound(SOUND_COINSPIN_NO, 0.0f, 0, 0, 5, -1.0f);
				}
			}
			else {
				DoTimeBomb();
			}
		}
	}
	else {
		FlipperClick(true);
	}

	return true;
}

// FUNCTION: POPCAPGAME1 0x0045ebb0
bool LogicMgr::MouseUp(int param_1, int param_2, int param_3, bool param_4)
{
	if (mUnk0xf5) {
		param_4 = true;
	}

	bool bVar3 = false;
	if (!mUnk0xf5 && mUnk0x4 == 2) {
		ClickInfo aClickInfo;
		aClickInfo.mUnk0x8 = mUnk0x8;
		aClickInfo.mUnk0xc = false;
		mUnk0xc4.push_back(&aClickInfo);
		bVar3 = true;
	}

	bool bVar1 = mUnk0x1e;
	if (0 < param_3) {
		mUnk0x1e = false;
	}

	if (mUnk0x244[mUnk0x128] == 0 || param_4) {
		if (0 < mUnk0x1e4[mUnk0x128] && (0 < param_3 && bVar1)) {
			FlipperClick(false);
		}
		CalcCornerDisplay();
	}
	else if (bVar3 && mUnk0xc4.size() != 0) {
		mUnk0xc4.pop_front();
	}

	return true;
}

// FUNCTION: POPCAPGAME1 0x0043d6a0
bool LogicMgr::MouseWheel(int param_1)
{
	if (!mUnk0x244[mUnk0x128] && mUnk0x4 == 1) {
		float anAngleStep = GetMouseAngleStep();
		Gun* aGun = mBoard->mGun.get();
		if (aGun->mUnk0x194 && aGun->mAngularVelocity <= 1.0f && abs(param_1) <= 1) {
			float aSpeedScale = ModVal(
									0,
									"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1257,4148",
									0.02f
								) /
								aGun->mAngularVelocity;
			anAngleStep = Clamp(
				mUnk0x70 * aSpeedScale,
				ModVal(
					0,
					"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1258,4149",
					0.01f
				),
				ModVal(
					0,
					"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1259,4149",
					0.1f
				)
			);
		}

		mUnk0x70 = anAngleStep;
		float anAngleDelta = (float) (anAngleStep * (M_PI / 180.0));
		SetGunAngle(mUnk0xe0 + anAngleDelta * param_1);
		mUnk0xe8 = ModVal(
			0,
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1260,4155",
			30
		);
		aGun->mUnk0x180 = true;
	}
	return true;
}

bool LogicMgr::KeyChar(SexyChar param_1)
{
	return false;
}

bool LogicMgr::KeyDown(KeyCode param_1)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00440500
void LogicMgr::BeginInitLevel()
{
	if (!mUnk0x340.empty()) {
		SetState((LogicState) 8);
		for (std::list<SmartPtr<PhysObj>>::iterator anItr = mUnk0x340.begin();
			 anItr != mUnk0x340.end();
			 ++anItr) {
			anItr->get()->mUnk0x25 = false;
		}

		mUnk0x40 = 0;
		mUnk0x44 = 0;
		mUnk0x3c = 0;
		mUnk0x34 = 0;
	}
}

// FUNCTION: POPCAPGAME1 0x0046e880
void LogicMgr::BeginTurn(bool param_1)
{
	mBoard->mCharacterMgr->SetYinYangEye(false);
	if (mUnk0xf5) {
		SetState(LOGICSTATE_5);
		return;
	}

	if (!mUnk0x124) {
		if (mUnk0x17c[0] < 1) {
			DoLevelDone();
			return;
		}
	}
	else if (mUnk0x17c[0] <= 0 && mUnk0x17c[1] < 1) {
		DoLevelDone();
		return;
	}

	if (mUnk0x1e) {
		if (0 < mUnk0x1e4[mUnk0x128]) {
			FlipperClick(false);
		}
		mUnk0x1e = false;
	}

	if (mUnk0x124) {
		bool bVar1 = mUnk0x244[mUnk0x128];
		if (param_1) {
			mUnk0x128 = 1 - mUnk0x128;
			if (mUnk0x17c[mUnk0x128] < 1) {
				mUnk0x128 = 1 - mUnk0x128;
			}
		}

		if (bVar1 && mUnk0x244[mUnk0x128] == 0) {
			CalcGunAngle(true);
		}
		mBoard->mInterfaceMgr->SetNumBalls(mUnk0x17c[mUnk0x128]);
	}

	mBoard->mCharacterMgr->SetCurCharacter(mUnk0x184[mUnk0x128]);
	DoBeginTurnText();
	DoBeginTurnTip(-1);
	if (!mUnk0x124 && -1 < mUnk0x320) {
		mUnk0x320 = -mUnk0x320;
	}
	else {
		mUnk0x320 = 0;
	}

	mUnk0x138 = 0;
	mUnk0x108 = 0;
	mUnk0x10c = 0;
	mUnk0x110 = 0;
	mUnk0x11c = 0;
	mUnk0xc = 0;
	mUnk0x10 = 0;
	mUnk0x14 = 0;
	mUnk0x50 = 0;
	mUnk0x18 = false;
	mUnk0x19 = false;
	mUnk0x1a = false;
	mUnk0xf8 = false;
	mUnk0x20 = false;
	mUnk0x68 = false;
	mUnk0x69 = false;
	mUnk0xfa = false;
	mUnk0x55 = false;
	mBoard->mGun->mUnk0x1a2 = false;
	mUnk0x330 = 320.0f;
	mUnk0x338 = 320.0f;
	mUnk0x334 = 240.0f;
	mUnk0x33c = 240.0f;

	ActivatePowerups();

	if (0 < mUnk0x12c) {
		mUnk0x12c = 0;
		MakeScorePeg();
	}

	if (mUnk0x1c != 0) {
		mUnk0x1c = 0;
		if (0 < mUnk0x24) {
			mUnk0x24--;
			MakePowerupPeg();
		}
	}

	if (0 < mZenBallCount[mUnk0x128]) {
		mUnk0x55 = true;
	}

	CalcCornerDisplay();
	BeginTurn2();
}

// FUNCTION: POPCAPGAME1 0x0044b5b0
void LogicMgr::BeginTurn2()
{
	if (mUnk0xf5) {
		SetState((LogicState) 0);
		return;
	}

	mBoard->mAIMgr->Clear();
	SetState((LogicState) 1);
	if (!mBoard->mDebugMgr->mUnk0x5) {
		ActivateFreeBall(true);
	}

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

	if (mFireballCount[mUnk0x128] > 0) {
		mBoard->mGun->SetFireball(true);
	}
	if (mUnk0x54) {
		SetWearHat(true);
	}
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

// FUNCTION: POPCAPGAME1 0x00440830
void LogicMgr::UpdateFreeBallRadius()
{
	int anUpdateRate = ModVal(
		0,
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1261,4256",
		2
	);
	if (mBoard->mUnk0x1c4 % anUpdateRate != 0) {
		bool aRadiusChanged = false;
		for (std::list<SmartPtr<PhysObj>>::iterator anItr = mBoard->mUnk0x190.begin();
			 anItr != mBoard->mUnk0x190.end();
			 ++anItr) {
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x5c == "freeballcover" ||
				anObj->mUnk0x5c == "freeball" ||
				anObj->mUnk0x5c == "bumperhole") {
				Mover* aMover = anObj->mMover.get();
				if (aMover != NULL && (float) mUnk0x134 != (float) aMover->mRadius &&
					aMover->mTime > 0) {
					aRadiusChanged = true;
					if (aMover->mRadius > mUnk0x134) {
						int aRadius = aMover->mRadius - 1;
						aMover->mRadius = aRadius < mUnk0x134 ? mUnk0x134 : aRadius;
					}
					else {
						int aRadius = aMover->mRadius + 1;
						aMover->mRadius = aRadius > mUnk0x134 ? mUnk0x134 : aRadius;
					}
				}
			}
		}

		if (!aRadiusChanged) {
			mUnk0x134 = 0;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0044b690
void LogicMgr::UpdateShotExtender()
{
	if (mBoard->mInterfaceMgr->mUnk0x160) {
		BeginTurn2();
	}
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
	if (param_1 <= 0 && !mUnk0xfb) {
		return 100;
	}
	if (param_1 <= 3) {
		return 10;
	}
	if (param_1 <= 6) {
		return 5;
	}
	if (param_1 <= 10) {
		return 3;
	}
	return param_1 <= 15 ? 2 : 1;
}

// FUNCTION: POPCAPGAME1 0x00437110
int LogicMgr::CalcMusicIntensity(int param_1)
{
	if (param_1 <= 3) {
		return 6;
	}
	if (param_1 <= 6) {
		return 5;
	}
	if (param_1 <= 10) {
		return 4;
	}
	if (param_1 <= 15) {
		return 3;
	}
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

// FUNCTION: POPCAPGAME1 0x00466a00
void LogicMgr::RemoveHitPegs()
{
	int listSize = mUnk0x34c.size();

	if (listSize == 0 && mUnk0x10 < 1) {
		return;
	}

	if (mUnk0x10 < 1) {
		SmartPtr<PhysObj> aPhysObj = mUnk0x34c.front();

		mUnk0x330 = aPhysObj->GetXPos();
		mUnk0x334 = aPhysObj->GetYPos();

		if (aPhysObj->mUnk0x25) {
			aPhysObj->mPegInfo->DoFlash(1);
			aPhysObj->mUnk0x25 = false;
		}

		mUnk0x34c.pop_front();
		listSize--;
	}
	else {
		mUnk0x10--;
	}

	if (listSize > 0) {
		int delay = 8 - (listSize / 10);

		if (delay < 1) {
			delay = 1;
		}
		else if (delay > 5) {
			delay = 5;
		}

		mUnk0xc = delay;

		if (mUnk0x4 == 3) {
			int pegIndex = mUnk0x12c - listSize;
			int modOffset;
			if (pegIndex == 1) {
				mUnk0xc += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1246,3806", 0);
			}
			else if (pegIndex == 2) {
				mUnk0xc += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1247,3807", 0);
			}
			else if (pegIndex == 3) {
				mUnk0xc += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1248,3808", 0);
			}
		}

		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1249,3813", -6);
		mBoard->mSoundMgr->AddSound(SOUND_PEGPOP, 0, 0, 0, 10, 1.0f);

		mUnk0x14++;

		if (mUnk0x3c != 0) {
			FloatingText* mainText = mBoard->mFloatingTextMgr->GetTextById(mUnk0x3c);
			FloatingText* multiText = mBoard->mFloatingTextMgr->GetTextById(mUnk0x11c);
			FloatingText* bonusText = mBoard->mFloatingTextMgr->GetTextById(mUnk0x40);

			if (mainText != NULL) {
				int totalHit = mUnk0x12c;

				int pegsToScore = (totalHit - mUnk0x34c.size()) - mUnk0x10;

				if (mUnk0x18 != false) {
					pegsToScore = mUnk0x14;
					if (totalHit < mUnk0x14) {
						pegsToScore = totalHit;
					}
				}

				if (pegsToScore < 1) {
					pegsToScore = 1;
				}

				if (mUnk0x18 == false && mUnk0x124 != false) {
					mainText->mUnk0x6c = -1000;
					if (multiText != NULL) {
						multiText->mUnk0x6c = -1000;
					}
					if (bonusText != NULL) {
						bonusText->mUnk0x6c = -1000;
					}
				}
				else {
					int bonusPoints = mUnk0x108 - (mUnk0x10c * totalHit);
					if (bonusPoints < 0) {
						bonusPoints = 0;
					}

					if (mUnk0xf6 == false) {
						int finalScore = (mUnk0x10c * pegsToScore) + bonusPoints;

						mainText->SetText(CommaSeperate(finalScore));

						if (multiText != NULL) {
							std::string baseScoreStr = CommaSeperate(mUnk0x10c);

							if (pegsToScore == 1) {
								multiText->SetText(StrFormat("%s x %d Peg", baseScoreStr.c_str(), 1));
							}
							else {
								multiText->SetText(StrFormat("%s x %d Pegs", baseScoreStr.c_str(), pegsToScore));
							}
						}
					}
				}
			}
		}

		if (KILLBALL_TIME3 < mUnk0x38) {
			mUnk0x38 = KILLBALL_TIME3;
		}

		for (std::list<SmartPtr<Ball>>::iterator it = mBoard->mUnk0x19c.begin(); it != mBoard->mUnk0x19c.end(); ++it) {
			(*it)->mUnk0xe4 = 0;
		}
	}
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

// FUNCTION: POPCAPGAME1 0x004612e0
void LogicMgr::ActivatePowerup(PowerupType param_1, bool param_2)
{
	switch (param_1) {
	case POWERUP_1:
		if (mUnk0x4 != 2) {
			mBoard->mGun->SetDoBouncyGuide(param_2);
		}
		break;
	case POWERUP_2:
		if (param_2) {
			ClearFlipperSpace();
			if (mUnk0x244[mUnk0x128] == 0 && !mUnk0xf5 && mBoard->mApp->mCurProfile != NULL && mBoard->mApp->mCurProfile->mUnk0x54 < 2) {
				mUnk0x20 = true;
			}
		}
		else {
			FlipperClick(false);
		}

		for (std::list<SmartPtr<PhysObj>>::iterator anItr = mBoard->mUnk0x190.begin(); anItr != mBoard->mUnk0x190.end(); ++anItr) {
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x78 == "flipper") {
				anObj->AddedToGame();
				if (param_2 && mUnk0x4 == 2 && anObj->mUnk0x10 == 5) {
					static_cast<Ball*>(anObj)->mUnk0x148 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1079,1559", 180);
				}

				if (anObj->mUnk0x50 == 0) {
					anObj->mUnk0x30 = false;
				}
			}
			else {
				if (!(anObj->mUnk0x78 == "freeball")) {
					anObj->mUnk0x78 == "bumperhole"; // ???
				}
			}
		}
		break;
	case POWERUP_4:
		if (param_2) {
			if (mUnk0x4 == 2) {
				ActivateFreeBall(true);
			}
		}
		else {
			mBoard->mEffectMgr->EraseAllOfType(EFFECT_22);
		}
		break;
	case POWERUP_7:
		if (param_2 && mUnk0x4 != 2) {
			mBoard->mCharacterMgr->SetYinYangEye(true);
		}
		break;
	case POWERUP_10:
		mUnk0x148 = -(uint) param_2 & 100;
		break;
	case 12:
		if (mUnk0x4 != 2) {
			ActivateFreeBallCover(param_2);
		}
		break;
	}

	if (param_1 == 2 || param_1 == 4) {
		if (mUnk0x1e4[mUnk0x128] != 0) {
			mUnk0x134 = 130;
		} else {
			mUnk0x134 = (-(uint)mFreeBallCount[mUnk0x128] == 0) & 60 + 200;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00461560
void LogicMgr::ActivatePowerups()
{
	if (mUnk0x1cc[mUnk0x128] != 0) {
		mUnk0x1d4[mUnk0x128 + mUnk0x1cc[mUnk0x128] * 2] = 1;
	}

	for (int i = 0; i < 14; ++i) {
		int iVar1 = mUnk0x128 + i * 2;
		if (0 < mUnk0x1d4[iVar1]) {
			mUnk0x1d4[iVar1]--;
		}
		ActivatePowerup((PowerupType) i, mUnk0x1d4[iVar1] != 0);
	}

	if (mUnk0x58[mUnk0x128] != 0) {
		mUnk0x68 = true;
		mUnk0x58[mUnk0x128]--;
	}

	if (mUnk0x60[mUnk0x128] != 0) {
		mUnk0x69 = true;
		mUnk0x60[mUnk0x128]--;
	}
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
	if (mUnk0x50 == 1) {
		mUnk0x14c = param_1;
	}
	else {
		mUnk0x150 = param_1;
	}
}

// FUNCTION: POPCAPGAME1 0x00437270
int LogicMgr::GetSlotMachineResult()
{
	if (mUnk0x50 == 1) {
		return mUnk0x14c;
	}
	return mUnk0x150;
}

// FUNCTION: POPCAPGAME1 0x00451ac0
int LogicMgr::GetSlotMachinePowerup()
{
	std::vector<int> aPowerups;
	for (int i = 0; i <= mUnk0x15c; ++i) {
		CharacterInfo* aCharacter = mBoard->mCharacterMgr->GetCharacterInfo(i);
		if (aCharacter != NULL && aCharacter->mUnk0x6C != 13) {
			aPowerups.push_back(aCharacter->mUnk0x6C);
		}
	}
	if (aPowerups.empty()) {
		aPowerups.push_back(1);
	}

	int aSelector = mUnk0x50 == 1 ? mUnk0x30 : mUnk0x2c;
	return aPowerups[aSelector % aPowerups.size()];
}

// STUB: POPCAPGAME1 0x0046ecb0
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

// FUNCTION: POPCAPGAME1 0x00436fd0
void LogicMgr::SetGunAngle(float param_1)
{
	mUnk0xe0 = NormalizeAngle(param_1);
	float aMaxGunAngle = GetMaxGunAngle();
	float aMinAngle = (float) (90.0 - aMaxGunAngle);
	aMinAngle = (float) (aMinAngle * M_PI / 180.0);
	float aMaxAngle = (float) (aMaxGunAngle + 90.0);
	aMaxAngle = (float) (aMaxAngle * M_PI / 180.0);
	if (mUnk0xe0 > aMinAngle && mUnk0xe0 < aMaxAngle) {
		float aMiddleAngle = (float) ((aMaxAngle + aMinAngle) * 0.5);
		if (mUnk0xe0 > aMiddleAngle) {
			mUnk0xe0 = aMaxAngle;
		}
		else {
			mUnk0xe0 = aMinAngle;
		}
	}
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
		!mBoard->mReplayButton->mIsOver && mUnk0x4 != 2) {
		mUnk0x80.assign("Fast Forward", 12);
		return;
	}
	if (mUnk0x68) {
#pragma inline_depth(0)
		mUnk0x80.assign("Triple Score", 12);
#pragma inline_depth(16)
		return;
	}
	if (mZenBallCount[mUnk0x128] > 0) {
		mUnk0x80.assign("ZenBall", 7);
		return;
	}
	if (mFireballCount[mUnk0x128] > 0) {
		mUnk0x80.assign("Fireball", 8);
		return;
	}
	if (mUnk0x69) {
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

// FUNCTION: POPCAPGAME1 0x0046c2d0
void LogicMgr::SpeedTransition()
{
	if (mUnk0x4 == 8) {
		mUnk0x100 = true;

		for (std::list<SmartPtr<PhysObj>>::iterator anItr = mUnk0x340.begin(); anItr != mUnk0x340.end(); ++anItr) {
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x24) {
				anObj->mUnk0x25 = true;
				anObj->mPegInfo->mUnk0x20 = 0;
			}
		}

		if (mUnk0x34 != 0) {
			mBoard->mFloatingTextMgr->EraseText(mUnk0x34);
			mUnk0x34 = 0;
		}

		if (mUnk0x3c != 0) {
			mBoard->mFloatingTextMgr->EraseText(mUnk0x3c);
			mUnk0x3c = 0;
		}

		if (mUnk0x40 != 0) {
			mBoard->mFloatingTextMgr->EraseText(mUnk0x40);
			mUnk0x40 = 0;
		}

		if (mUnk0x11c != 0) {
			mBoard->mFloatingTextMgr->EraseText(mUnk0x11c);
			mUnk0x11c = 0;
		}

		mBoard->mInterfaceMgr->SettleDown();
		mBoard->mInterfaceMgr->SetNumBalls(mUnk0x17c[mUnk0x128]);
	}
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
	if (aBall != NULL) {
		aBall->SetHat(param_1, false);
		if (param_1) {
			aBall->SetAbsPos(aBall->mUnk0xec, aBall->mUnk0xf0);
		}
	}
}

void LogicMgr::RecordStats()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0046a9c0
void LogicMgr::DoLevelDone()
{
	SetState(LOGICSTATE_6);
	if (!mUnk0xf5) {
		RecordStats();
		mBoard->DoLevelDone();
	}

	int iVar1 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1128,2162", 0x82);
	if (mBoard->mEndLevelDialog->mUnk0x180 == 6) {
		mUnk0xfd = true;
		mBoard->mEffectMgr->AddMasterBadge(
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1129,2166", 325),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1130,2166", 275),
			iVar1
		);
	}
	else if (mUnk0xfc && mBoard->mUnk0xb4 != DEMO) {
		mUnk0xfd = true;
		mBoard->mEffectMgr->AddRibbon(
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1131,2171", 325),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1132,2171", 320),
			iVar1
		);
	}

	if (mUnk0xfd && mUnk0xf5) {
		FloatingText* aText = AddStandardText(
			"Click to Continue",
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1133,2176", 325),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1134,2176", 440),
			iVar1
		);

		aText->mUnk0x7c = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1135,2177", 2);
		aText->mUnk0x74 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1136,2178", 30);
		int iVar2 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1137,2179", -300);
		aText->mUnk0x8c = 0;
		aText->mUnk0x88 = 0;
		aText->mUnk0x6c = iVar2;
		aText->mUnk0x68 = 0;
		mUnk0x34 = aText->mId;
		mBoard->mSoundMgr->AddSound(SOUND_TING, 0.0f, 0, iVar1, 1, -1.0f);
		mBoard->mSoundMgr->AddSound(SOUND_APPLAUSE, 0.0f, 0, iVar1 + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1138,2184", 0x1e), 1, -1.0f);
	}
}

// FUNCTION: POPCAPGAME1 0x0043d580
bool LogicMgr::BeatLevel()
{
	if (mUnk0xfb) {
		return mUnk0x358.empty() && mUnk0x364.empty();
	}
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
	if (!mUnk0xf6 || !param_1) {
		std::list<SmartPtr<PhysObj>>& anObjList = mBoard->mUnk0x190;
		bool anActive = param_1 && mFreeBallCount[mUnk0x128] > 0;
		for (std::list<SmartPtr<PhysObj>>::iterator anItr = anObjList.begin();
			 anItr != anObjList.end();
			 ++anItr) {
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x5c == "bumperhole") {
				anObj->SetActiveWithGrowAnim(anActive);
				if (anObj->mUnk0x10 == 5 && anObj->mUnk0xb0 == 1 && mUnk0x4 == 2) {
					static_cast<Poly*>(anObj)->mUnk0x140 = ModVal(
						0,
						"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LogicMgr.cpp1078,1463",
						300
					);
				}

				if (anObj->mUnk0xb0 == 1) {
					anObj->mUnk0x24 = false;
				}
				else {
					anObj->mUnk0x25 = false;
				}
			}
			else if (anObj->mUnk0x5c == "freeball") {
				anObj->SetActive(param_1);
				if (anObj->mUnk0x10 != 1) {
					if (anObj->mUnk0x28) {
						anObj->mUnk0x24 = false;
					}
					else {
						anObj->mUnk0x25 = false;
					}
				}
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00440700
void LogicMgr::ActivateFreeBallCover(bool param_1)
{
	if (!mUnk0xf6 || !param_1) {
		for (std::list<SmartPtr<PhysObj>>::iterator anItr = mBoard->mUnk0x190.begin();
			 anItr != mBoard->mUnk0x190.end();
			 ++anItr) {
			PhysObj* anObj = anItr->get();
			if (anObj->mUnk0x5c == "freeballcover") {
				anObj->SetActiveWithGrowAnim(param_1);
			}
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
