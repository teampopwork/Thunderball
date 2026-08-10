#include "TrophyScreen.h"

#include "PlayerInfo.h"
#include "ThunderballApp.h"
#include "TrophyMgr.h"
#include "WidgetMover.h"

#include <SexyAppFramework/ModVal.h>

#include <string.h>

using namespace Sexy;

// SYNTHETIC: POPCAPGAME1 0x0049c200
// Sexy::TrophyScreen::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x004b08e0
TrophyScreen::TrophyScreen(ThunderballApp* theApp)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497940
TrophyScreen::~TrophyScreen()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497a90
void TrophyScreen::Update()
{
	// TODO
}

// STUB: POPCAPGAME1 0x004ac440
void TrophyScreen::Draw(Graphics* g)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497d50
void TrophyScreen::DrawOverlay(Graphics* g)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0049ee00
void TrophyScreen::ButtonPress(int theId, int theClickCount)
{
	if (!mApp->mWidgetMover->IsMoving() && (unsigned int)theId <= 4) {
		DoPlay();
	}
}

// STUB: POPCAPGAME1 0x004ac8f0
void TrophyScreen::ButtonDepress(int theId)
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00497b60
void TrophyScreen::ButtonMouseEnter(int theId)
{
	if ((unsigned int)theId <= 4) {
		mHoverId = theId;
		mHoverTicks = 0;
	}
}

// FUNCTION: POPCAPGAME1 0x00497b80
void TrophyScreen::ButtonMouseLeave(int theId)
{
	if ((unsigned int)theId <= 4) {
		mHoverId = theId;
		// STRING: POPCAPGAME1 0x005fcf38
		mHoverTicks = ModVal(
			0,
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\TrophyScreen.cpp901,346",
			10);
	}
}

// FUNCTION: POPCAPGAME1 0x004979c0
void TrophyScreen::SyncPlayerInfo()
{
	if (mPlayerInfo != NULL && mPlayerInfo->mUnk0x38 != mPlayerInfoValue) {
		mPlayerInfo->mUnk0x38 = mPlayerInfoValue;
		mPlayerInfo->mUnk0xec = true;
	}
}

// STUB: POPCAPGAME1 0x004ab780
void TrophyScreen::SyncPageNum()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x0049c230
bool TrophyScreen::CanSelectTrophy()
{
	return true;
}

// FUNCTION: POPCAPGAME1 0x0049ed10
void TrophyScreen::DoPlay()
{
	TrophyInfo** aTrophyInfoPtr = &mEntries[0].mTrophyInfo;
	int aRemaining = 5;
	do {
		Widget* aButton = *(Widget**)((char*)aTrophyInfoPtr - 8);
		if (aButton->mIsOver) {
			TrophyInfo* aTrophyInfo = *aTrophyInfoPtr;
			if (aTrophyInfo != NULL) {
				*(int*)((char*)mApp + 0x76c) = aTrophyInfo->mId;
				std::vector<std::string>& aCommands =
					*(std::vector<std::string>*)((char*)aTrophyInfo + 0x78);
				// STRING: POPCAPGAME1 0x005d5fd4
				if (aCommands.size() == 1 &&
					_stricmp(aCommands.front().c_str(), "pick") == 0) {
					mApp->ShowLevelScreen(false);
				}
				else {
					mApp->ShowBoard(true, true);
				}
			}
		}

		aTrophyInfoPtr = (TrophyInfo**)((char*)aTrophyInfoPtr + 0x14);
		aRemaining--;
	} while (aRemaining != 0);
}

// STUB: POPCAPGAME1 0x00497bb0
void TrophyScreen::DrawBadge(Graphics* g, int theId)
{
	// TODO
}

// STUB: POPCAPGAME1 0x004abf50
void TrophyScreen::DrawTrophyInfo(Graphics* g, int theId)
{
	// TODO
}

// STUB: POPCAPGAME1 0x004ab600
DDImage* TrophyScreen::GetLevelImage(const std::string& theLevel)
{
	// TODO
	return NULL;
}

// STUB: POPCAPGAME1 0x004979f0
void TrophyScreen::DrawImageAndRect(Graphics *g,Image *param_2,int param_3,int param_4,int param_5,int param_6)
{
	// TODO
}
