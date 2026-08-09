#include "LevelScreen.h"

#include "PlayerInfo.h"
#include "StageMgr.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"
#include "WidgetMover.h"

using namespace Sexy;

// STUB: POPCAPGAME1 0x004af150
LevelScreen::LevelScreen(ThunderballApp* theApp)
{
}

// SYNTHETIC: POPCAPGAME1 0x00499890
// Sexy::LevelScreen::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00493410
LevelScreen::~LevelScreen()
{
}

// FUNCTION: POPCAPGAME1 0x00493490
void LevelScreen::SyncPlayerInfo()
{
	if (mPlayerInfo != NULL)
		mPlayerInfo->SetLevelSelectStage(mStage);
}

// FUNCTION: POPCAPGAME1 0x004934b0
void LevelScreen::Update()
{
	Widget::Update();
	if (mHoverTicks != 0 && --mHoverTicks == 0)
		mHoveredLevel = -1;
}

// FUNCTION: POPCAPGAME1 0x004934e0
void LevelScreen::ButtonMouseEnter(int theId)
{
	if ((unsigned int) theId < 5)
	{
		mHoveredLevel = theId;
		mHoverTicks = 0;
	}
}

// FUNCTION: POPCAPGAME1 0x00493500
void LevelScreen::ButtonMouseLeave(int theId)
{
	if ((unsigned int) theId < 5)
	{
		mHoveredLevel = theId;
		mHoverTicks = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LevelScreen.cpp366,347", 10);
	}
}

// FUNCTION: POPCAPGAME1 0x00493530
void LevelScreen::DoPlay(int theId)
{
	int aLevel = theId;
	if ((unsigned int) theId >= 5)
	{
		if (mPlayerInfo == NULL)
			return;

		int aStage = -1;
		aLevel = -1;
		mApp->mStageMgr->GetRandomLevel(
			mApp->mCurProfile, &aStage, &aLevel, mApp->mGameMode == DUEL, 0, true);
		if (aStage < 0 || aLevel < 0)
			return;

		mStage = aStage;
		SyncPlayerInfo();
	}

	mApp->mUnk0x768 = aLevel;
	mApp->mUnk0x764 = mStage;
	mApp->ShowBoard(false, true);
	mApp->mStageMgr->MarkLastUseTime(mLevels[aLevel].mLevelInfo);
}

// FUNCTION: POPCAPGAME1 0x00493600
bool LevelScreen::CanSelectLevel(int theId)
{
	if ((unsigned int) theId < 5)
	{
		if (mApp->mCurProfile == NULL)
			return true;
		if (!mApp->IsLevelDemoLocked(mStage, theId))
			return mApp->mCurProfile->IsLevelUnlocked(mStage, theId);
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x00493660
void LevelScreen::ButtonPress(int theId, int theMouseButton)
{
	if (!mApp->mWidgetMover->IsMoving() && (unsigned int) theId < 5)
	{
		MarkDirty();
		DoPlay(theId);
	}
}

// STUB: POPCAPGAME1 0x004a5fa0
void LevelScreen::DrawLevelInfo(Graphics* g, int theX, int theY)
{
}

// STUB: POPCAPGAME1 0x004a6820
void LevelScreen::Draw(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x004a5c40
void LevelScreen::SyncStageNum()
{
}

// STUB: POPCAPGAME1 0x004a6dd0
void LevelScreen::ButtonDepress(int theId)
{
}

