#include "InterfaceMgr.h"

#include "Board.h"
#include "HighScoreMgr.h"
#include "LogicMgr.h"
#include "PlayerInfo.h"
#include "Res.h"
#include "SoundMgr.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/MemoryImage.h>

#include <algorithm>
#include <cstring>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00436700
static Image* GetBallImage()
{
	// STRING: POPCAPGAME1 0x005dc4d8
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp934,47", 0) ? IMAGE_BALL : IMAGE_INT_BALL;
}

// FUNCTION: POPCAPGAME1 0x00436720
static int GetBallSpacing()
{
	Image* aBallImage = GetBallImage();
	// STRING: POPCAPGAME1 0x005dc520
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp935,58", 0) + aBallImage->mHeight;
}

// FUNCTION: POPCAPGAME1 0x00436740
static int GetMaxVisibleBalls()
{
	// STRING: POPCAPGAME1 0x005dc568
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp936,65", 25);
}

// TEMPLATE: POPCAPGAME1 0x00442320
// std::vector<Sexy::SexyVector2,std::allocator<Sexy::SexyVector2> >::back

// TEMPLATE: POPCAPGAME1 0x0041ff50
// std::vector<Sexy::SexyVector2,std::allocator<Sexy::SexyVector2> >::insert

// FUNCTION: POPCAPGAME1 0x004515a0
InterfaceMgr::InterfaceMgr(Board* theBoard)
{
	mApp = theBoard->mApp;
	mBoard = theBoard;
	mUnk0xf0 = 10;

	for (int i = 0; i < 9; ++i) {
		mImages[i] = new MemoryImage();
	}

	mImages[0]->Create(88, 600);
	mImages[2]->Create(624, 74);
	mImages[3]->Create(110, 70);
	mImages[1]->Create(88, 600);
	mImages[4]->Create(624, 14);

	for (int i = 5; i < 9; ++i) {
		mImages[i]->SetImageMode(true, true);
	}

	mUnk0xf4 = -1;
	Clear();
}

// SYNTHETIC: POPCAPGAME1 0x00447230
// Sexy::InterfaceMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00443880
InterfaceMgr::~InterfaceMgr()
{
	for (int i = 0; i < 9; ++i) {
		delete mImages[i];
	}
}

// FUNCTION: POPCAPGAME1 0x004366a0
int InterfaceMgr::GetBallBottom()
{
	// STRING: POPCAPGAME1 0x005dc490
	int aBallSpacing = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp933,28", 3);
	int aSpacingOffset = aBallSpacing * mUnk0xec;
	// STRING: POPCAPGAME1 0x005dc448
	int aBallBottom = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp932,28", 410) + mUnk0x5c + aSpacingOffset;

	if (mUnk0x58 != 0) {
		if (mUnk0x58 <= 20) {
			return aBallBottom + mUnk0x58 * 2;
		}

		if (mUnk0x58 < 30) {
			int aBounceOffset = 30 - mUnk0x58;
			aBallBottom += aBounceOffset * 2;
		}
	}

	return aBallBottom;
}

// FUNCTION: POPCAPGAME1 0x00436870
void InterfaceMgr::AddScoreUpdateDelay(int theDelay)
{
	if (mUnk0x9c < theDelay) {
		mUnk0x9c = theDelay;
	}
}

// FUNCTION: POPCAPGAME1 0x00436890
void InterfaceMgr::DrawScore(Graphics* theGraphics, std::string* theText, bool isLeftSide)
{
	theGraphics->SetFont(FONT_SCORE_DISP);
	theGraphics->SetColor(Color(0xffffff));
	int aTextWidth = theGraphics->GetFont()->StringWidth(*theText);
	// STRING: POPCAPGAME1 0x005dc7a8
	// STRING: POPCAPGAME1 0x005dc760
	int aRight = isLeftSide
		? ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp953,542", 295)
		: ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp954,542", 670);
	// STRING: POPCAPGAME1 0x005dc718
	if (aTextWidth > ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp955,543", 100)) {
		// STRING: POPCAPGAME1 0x005dc6d0
		aRight += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp956,544", 5);
	}
	// STRING: POPCAPGAME1 0x005dc688
	theGraphics->DrawString(*theText, aRight - aTextWidth, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp957,545", 28));
}

// FUNCTION: POPCAPGAME1 0x00436950
void InterfaceMgr::DrawSmallMode(Graphics* theGraphics, std::string* theText, bool isLeftSide)
{
	theGraphics->SetFont(FONT_SMALL_DISP);
	theGraphics->SetColor(Color(0xffffff));
	// STRING: POPCAPGAME1 0x005dc910
	// STRING: POPCAPGAME1 0x005dc8c8
	int anX = isLeftSide
		? ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp958,568", 128)
		: ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp959,568", 508);
	int aTextWidth = theGraphics->GetFont()->StringWidth(*theText);
	// STRING: POPCAPGAME1 0x005dc880
	if (aTextWidth > ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp960,569", 75)) {
		// STRING: POPCAPGAME1 0x005dc838
		anX -= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp961,570", 6);
	}
	// STRING: POPCAPGAME1 0x005dc7f0
	theGraphics->DrawString(*theText, anX, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp962,571", 20));
}

// FUNCTION: POPCAPGAME1 0x0043ca00
void InterfaceMgr::DrawMode(Graphics* param_1, std::string* param_2, bool param_3)
{
    DrawSmallMode(param_1, param_2, param_3);
}

// FUNCTION: POPCAPGAME1 0x00436a10
void InterfaceMgr::DrawDetail(Graphics* theGraphics, std::string* theText, bool isLeftSide, int theOffset)
{
	theGraphics->SetFont(FONT_SMALL_DISP);
	theGraphics->SetColor(Color(0xffffff));
	// STRING: POPCAPGAME1 0x005dca78
	// STRING: POPCAPGAME1 0x005dca30
	int anX = isLeftSide
		? ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp963,581", 128)
		: ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp964,581", 508);
	int aTextWidth = theGraphics->GetFont()->StringWidth(*theText);
	// STRING: POPCAPGAME1 0x005dc9e8
	if (aTextWidth > ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp965,582", 75)) {
		// STRING: POPCAPGAME1 0x005dc9a0
		anX -= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp966,583", 6);
	}
	// STRING: POPCAPGAME1 0x005dc958
	theGraphics->DrawString(*theText, anX + theOffset, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp967,584", 35));
}

// FUNCTION: POPCAPGAME1 0x00436ae0
void InterfaceMgr::DrawScoreBlink(Graphics* theGraphics)
{
	// STRING: POPCAPGAME1 0x005dcbe0
	int aBlinkRate = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp968,613", 15);
	if (mUnk0xe0 > 0 && (mUnk0xe0 / aBlinkRate) % 2 == 0) {
		// STRING: POPCAPGAME1 0x005dcb98
		// STRING: POPCAPGAME1 0x005dcb50
		theGraphics->DrawImage(
			IMAGE_INT_SCOREHILIGHT,
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp969,615", 113),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp970,615", 2));
	}
	if (mUnk0xe4 > 0 && (mUnk0xe4 / aBlinkRate) % 2 == 0) {
		// STRING: POPCAPGAME1 0x005dcb08
		// STRING: POPCAPGAME1 0x005dcac0
		theGraphics->DrawImage(
			IMAGE_INT_SCOREHILIGHT,
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp971,618", 492),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp972,618", 2));
	}
}

// FUNCTION: POPCAPGAME1 0x00436bb0
int InterfaceMgr::GetBallX()
{
	// STRING: POPCAPGAME1 0x005dcc28
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1017,1093", 30);
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void InterfaceMgr::DrawSuperFront(Graphics* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00436c40
void InterfaceMgr::EndShot()
{
	mUnk0x30 = -1;
	mUnk0x38 = -1;
	mUnk0x4c = 0;
}

// FUNCTION: POPCAPGAME1 0x00436c60
void InterfaceMgr::DoShotMeterBlink()
{
	mUnk0x54 = 1;
}

// FUNCTION: POPCAPGAME1 0x00436c70
void InterfaceMgr::DoFeverBlink()
{
	if (mUnk0x30 != -1) {
		mUnk0x34 = 1;
		mUnk0x40 = mUnk0x30;
	}
}

// FUNCTION: POPCAPGAME1 0x00436c90
void InterfaceMgr::UpdateShotMeter()
{
	LogicMgr* aLogicMgr = mBoard->mLogicMgr;
	if (aLogicMgr->mUnk0x4 == 2 && !aLogicMgr->mUnk0xf6) {
		if (aLogicMgr->mUnk0x108 >= 125000 && mUnk0x48 < 125000) {
			mUnk0x48 = 125000;
			mUnk0x4c = 125000;
			mUnk0x161 = true;
		} else if (aLogicMgr->mUnk0x108 >= 75000 && mUnk0x48 < 75000) {
			mUnk0x48 = 75000;
			mUnk0x4c = 75000;
			mUnk0x161 = true;
		} else if (aLogicMgr->mUnk0x108 >= 25000 && mUnk0x48 < 25000) {
			mUnk0x48 = 25000;
			mUnk0x4c = 25000;
			mUnk0x161 = true;
		} else {
			mUnk0x4c = aLogicMgr->mUnk0x108;
		}

		if (aLogicMgr->mUnk0x108 > mUnk0x50) {
			mUnk0x50 = aLogicMgr->mUnk0x108;
		}
	}

	if (mUnk0x54 != 0) {
		mUnk0x54++;
		// STRING: POPCAPGAME1 0x005dcc70
		if (mUnk0x54 >= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1046,1497", 400)) {
			if (mUnk0x48 == 0) {
				mUnk0x50 = 0;
			}
			mUnk0x54 = 0;
		}
	}

	if (mUnk0x48 == mUnk0x4c) {
		return;
	}

	int aMeterValue = mUnk0x48;
	if (aMeterValue < mUnk0x4c) {
		int aDifference = mUnk0x4c - aMeterValue;
		if (aDifference > 100000) {
			aMeterValue += 5000;
		} else if (aDifference > 25000) {
			aMeterValue += 1000;
		} else if (aDifference > 1000) {
			aMeterValue += 200;
		} else if (aDifference > 100) {
			aMeterValue += 100;
		} else {
			aMeterValue += 10;
		}
		mUnk0x48 = aMeterValue;
		if (mUnk0x48 > mUnk0x4c) {
			mUnk0x48 = mUnk0x4c;
		}
	} else if (aMeterValue > mUnk0x4c) {
		int aDifference = aMeterValue - mUnk0x4c;
		if (aDifference > 100000) {
			aMeterValue -= 5000;
			mUnk0x48 = aMeterValue;
		}
		if (aDifference > 25000) {
			mUnk0x48 -= 1000;
		} else {
			mUnk0x48 -= 200;
		}
		if (mUnk0x48 < mUnk0x4c) {
			mUnk0x48 = mUnk0x4c;
		}
	}

	if (mUnk0x48 == 0) {
		if (mUnk0x54 == 0) {
			mUnk0x50 = 0;
		}
		mUnk0x161 = false;
	} else if (mUnk0x48 >= 25000) {
		mUnk0x161 = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00436e20
bool InterfaceMgr::IsScoreAccurate()
{
	for (int i = 0; i < 2; ++i) {
		if ((&mUnk0x94)[i] != (&mBoard->mLogicMgr->mUnk0x174)[i]) {
			return false;
		}
	}

	return true;
}

// FUNCTION: POPCAPGAME1 0x00436e60
void InterfaceMgr::DoFeverMultBlink()
{
	mUnk0xf8 = 1;
}

// FUNCTION: POPCAPGAME1 0x00436e70
void InterfaceMgr::DoFever()
{
	mUnk0x44 = 1;
	mUnk0xfc[0] = 0;
	mUnk0xfc[1] = 0;
	mUnk0xfc[2] = 0;
	mUnk0xfc[3] = 0;
	mUnk0xfc[4] = 0;
	mUnk0xfc[5] = 0;
	mUnk0xfc[6] = 0;
	mUnk0xfc[7] = 0;
	mUnk0xfc[8] = 0;
	mUnk0xfc[9] = 0;
	mUnk0xfc[10] = 0;
	mUnk0xfc[11] = 0;
	mUnk0xfc[12] = 0;
	mUnk0xfc[13] = 0;
	mUnk0xfc[14] = 0;
	mUnk0xfc[15] = 0;
	mUnk0xfc[16] = 0;
	mUnk0xfc[17] = 0;
	mUnk0xfc[18] = 0;
	mUnk0xfc[19] = 0;
	mUnk0xfc[20] = 0;
	mUnk0xfc[21] = 0;
	mUnk0xfc[22] = 0;
	mUnk0xfc[23] = 0;
	mUnk0xfc[24] = 0;
}

// FUNCTION: POPCAPGAME1 0x0043ca00
void InterfaceMgr::UpdatePaused()
{
}

// FUNCTION: POPCAPGAME1 0x00448190
void InterfaceMgr::CheckHighScoreSync()
{
	if (mUnk0x64 > 0 && mUnk0x64 < mUnk0x94 && mBoard->mUnk0xb4 != DEMO) {
		mUnk0x64 = mUnk0x94;
		if (mApp->mCurProfile != NULL) {
			mUnk0x70.assign(mApp->mCurProfile->mName, 0, (size_t) -1);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004482d0
void InterfaceMgr::SettleDown()
{
	LogicMgr* aLogicMgr = mBoard->mLogicMgr;
	mUnk0x94 = aLogicMgr->mUnk0x174;
	mUnk0x98 = aLogicMgr->mUnk0x178;
	CheckHighScoreSync();
}

// FUNCTION: POPCAPGAME1 0x004481d0
void InterfaceMgr::UpdateScoreDisp()
{
	if (mUnk0x9c != 0) {
		--mUnk0x9c;
		return;
	}

	for (int i = 0; i < 2; ++i) {
		LogicMgr* aLogicMgr = mBoard->mLogicMgr;
		int aDisplayedScore = (&mUnk0x94)[i];
		int aScore = (&aLogicMgr->mUnk0x174)[i];
		if (aDisplayedScore == aScore) {
			continue;
		}

		if (aDisplayedScore < aScore) {
			if (aLogicMgr->mUnk0x4 == 5) {
				aDisplayedScore += 5000;
			} else {
				int aDifference = aScore - aDisplayedScore;
				if (aDifference > 100000) {
					aDisplayedScore += 5000;
				} else if (aDifference > 10000) {
					aDisplayedScore += 1000;
				} else if (aDifference > 1000) {
					aDisplayedScore += 200;
				} else if (aDifference > 100) {
					aDisplayedScore += 100;
				} else {
					aDisplayedScore += 10;
				}
			}

			if (aDisplayedScore > aScore) {
				aDisplayedScore = aScore;
			}
		} else if (aDisplayedScore > aScore) {
			int aDifference = aDisplayedScore - aScore;
			if (aDifference > 100000) {
				aDisplayedScore -= 5000;
			}
			if (aDifference > 10000) {
				aDisplayedScore -= 1000;
			} else if (aDifference > 1000) {
				aDisplayedScore -= 200;
			} else if (aDifference > 100) {
				aDisplayedScore -= 100;
			} else {
				aDisplayedScore -= 10;
			}

			if (aDisplayedScore < aScore) {
				aDisplayedScore = aScore;
			}
		}

		(&mUnk0x94)[i] = aDisplayedScore;
		if (i == 0) {
			CheckHighScoreSync();
		}
	}
}

// STUB: POPCAPGAME1 0x0043cfd0
void InterfaceMgr::DrawShotMeter(Graphics* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0043c7b0
void InterfaceMgr::DrawImageToInterface(Image* theImage, int theX, int theY, int theCel)
{
	Graphics aLeftGraphics(mImages[0]);
	Graphics aRightGraphics(mImages[1]);
	Graphics aTopGraphics(mImages[2]);
	Graphics aBottomGraphics(mImages[3]);
	Graphics aCenterGraphics(mImages[4]);

	Rect aSrcRect;
	if (theCel >= 0) {
		aSrcRect = theImage->GetCelRect(theCel);
	} else {
		aSrcRect = Rect(0, 0, theImage->mWidth, theImage->mHeight);
	}

	aLeftGraphics.DrawImage(theImage, theX, theY, aSrcRect);
	aRightGraphics.DrawImage(theImage, mImages[1]->mWidth - 800 + theX, theY, aSrcRect);
	aTopGraphics.DrawImage(theImage, theX - mImages[0]->mWidth, theY, aSrcRect);
	aBottomGraphics.DrawImage(theImage, theX - 345, theY - mImages[2]->mHeight, aSrcRect);
	aCenterGraphics.DrawImage(theImage, theX - mImages[0]->mWidth, mImages[4]->mHeight - 600 + theY, aSrcRect);
}

// FUNCTION: POPCAPGAME1 0x0043c990
void InterfaceMgr::DrawImageCelToInterface(Image* theImage, int theX, int theY)
{
	DrawImageToInterface(theImage, theX, theY, mUnk0xf4);
}

// FUNCTION: POPCAPGAME1 0x0043c9b0
void InterfaceMgr::LoadGun()
{
	if (mUnk0x164.size() == 0) {
		mBoard->mLogicMgr->mUnk0x138 = 2;
		return;
	}

	mUnk0x160 = false;
	mUnk0x58 = 1;
}

// STUB: POPCAPGAME1 0x0043ca10
void InterfaceMgr::DrawFeverLights(Graphics* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0043d400
void InterfaceMgr::BeginShot()
{
	mUnk0x38 = -1;
	mUnk0x30 = 25 - (int) mBoard->mLogicMgr->mUnk0x358.size();
	mUnk0x54 = 0;
	mUnk0x161 = false;
}

// FUNCTION: POPCAPGAME1 0x004724e0
void InterfaceMgr::UpdateHighScore(bool param_1)
{
	PlayerInfo* aProfile = mBoard->mApp->mCurProfile;
	if (aProfile != NULL) {
		mUnk0x68 = aProfile->mUnk0x204;
	} else {
		mUnk0x68 = 0;
	}
	mUnk0x64 = 0;
	mUnk0x70 = "";

	std::string aLevelName = GetFileName(mBoard->mUnk0x1d4, true);
	if (aLevelName.empty()) {
		return;
	}
	std::list<HighScoreEntry>* aScores = mBoard->mApp->mHighScoreMgr->GetScores(&aLevelName, false);
	if (aScores != NULL) {
		mUnk0x64 = aScores->front().mScore;
		mUnk0x70.assign(aScores->front().mName, 0, (size_t) -1);
	}
}

// STUB: POPCAPGAME1 0x004725f0
void InterfaceMgr::InitLevel()
{
}

// FUNCTION: POPCAPGAME1 0x00442db0
int InterfaceMgr::GetTopBallY()
{
	if (mUnk0x164.size() != 0 && (int) mUnk0x164.size() <= GetMaxVisibleBalls()) {
		return (int) mUnk0x164.back().x;
	}

	return -1;
}

// FUNCTION: POPCAPGAME1 0x0043c770
int InterfaceMgr::GetNumVisibleBalls()
{
	int aMaxVisibleBalls = GetMaxVisibleBalls();
	int aNumBalls = (int) mUnk0x164.size();
	return (std::min)(aMaxVisibleBalls, aNumBalls);
}

// FUNCTION: POPCAPGAME1 0x0043d310
void InterfaceMgr::DrawBalls(Graphics* theGraphics)
{
	Image* aBallImage = GetBallImage();
	int aBallX = GetBallX();
	// STRING: POPCAPGAME1 0x005df9d8
	// STRING: POPCAPGAME1 0x005df990
	theGraphics->DrawImage(
		IMAGE_INT_BALLBACK,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1018,1103", -2) + aBallX,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1019,1103", 17) + GetBallBottom());

	int aNumVisibleBalls = GetNumVisibleBalls();
	for (int i = 0; i < aNumVisibleBalls; ++i) {
		theGraphics->DrawImage(aBallImage, aBallX, (int) mUnk0x164[i].x);
	}

	// STRING: POPCAPGAME1 0x005df948
	// STRING: POPCAPGAME1 0x005df900
	theGraphics->DrawImage(
		IMAGE_INT_BALLGLASS,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1020,1110", 3),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp1021,1110", 92));
}

// STUB: POPCAPGAME1 0x00443cf0
void InterfaceMgr::UpdateBalls()
{
}

// FUNCTION: POPCAPGAME1 0x00457870
void InterfaceMgr::SetNumBalls(int theNumBalls)
{
	mUnk0x164.resize(theNumBalls, SexyVector2(0, 0));
	int aDisplayedNumBalls = theNumBalls;
	if (theNumBalls > 15) {
		aDisplayedNumBalls = 15;
	}
	mUnk0xec = aDisplayedNumBalls;
	mUnk0xe8 = aDisplayedNumBalls;
	mUnk0x5c = 0;

	int aBallY = GetBallBottom();
	int aBallSpacing = GetBallSpacing();
	for (int i = 0; i < (int) mUnk0x164.size(); ++i) {
		SexyVector2& aBallPos = mUnk0x164[i];
		aBallPos.x = (float) aBallY;
		aBallY -= aBallSpacing;
		aBallPos.y = 0.0f;
	}

	mUnk0x160 = true;
}

// FUNCTION: POPCAPGAME1 0x00447260
void InterfaceMgr::Clear()
{
	mUnk0x30 = -1;
	mUnk0x34 = 0;
	mUnk0x38 = -1;
	mUnk0x3c = 0;
	mUnk0x40 = -1;
	mUnk0x48 = 0;
	mUnk0x4c = 0;
	mUnk0x50 = 0;
	mUnk0x54 = 0;
	mUnk0x58 = 0;
	mUnk0x5c = 0;
	mUnk0x60 = 0;
	mUnk0x64 = 0;
	// STRING: POPCAPGAME1 0x005d2b00
	mUnk0x70 = "";
	mUnk0x160 = true;
	mUnk0x161 = false;
	mUnk0x98 = 0;
	mUnk0x94 = 0;
	mUnk0x9c = 0;
	mUnk0xa0 = mUnk0xbc = "";
	mUnk0xdc = 0;
	mUnk0xd8 = 0;
	mUnk0xec = 0;
	mUnk0xe8 = 0;
	mUnk0x6c = 0;
	mUnk0x44 = 0;
	mUnk0x68 = 0;
	mUnk0xf8 = 0;
	mUnk0xe4 = 0;
	mUnk0xe0 = 0;
	mUnk0x164.clear();
}

// FUNCTION: POPCAPGAME1 0x004517c0
void InterfaceMgr::AddBottomBall(int theDelay)
{
	mUnk0x160 = false;
	if (mUnk0x60 != 0) {
		mUnk0x60 = 0;
		AddBottomBall(0);
	}

	if (theDelay != 0) {
		mUnk0x60 = theDelay;
		return;
	}

	int aBallSpacing = GetBallSpacing();
	SexyVector2 aNewBall;
	memset(&aNewBall, 0, sizeof(aNewBall));
	mUnk0x164.insert(mUnk0x164.begin(), aNewBall);
	SexyVector2& aBottomBall = mUnk0x164.front();
	aBottomBall.y = 0.0f;
	mUnk0x5c += aBallSpacing;
	aBottomBall.x = (float) GetBallBottom();

	int aNumVisibleBalls = GetNumVisibleBalls();
	for (int i = 0; i < aNumVisibleBalls; ++i) {
		mUnk0x164[i].y = -1.0f;
	}
}

// STUB: POPCAPGAME1 0x004518b0
void InterfaceMgr::Update()
{
}

// FUNCTION: POPCAPGAME1 0x0045c860
void InterfaceMgr::AddTopBalls(int theNumBalls)
{
	mUnk0x160 = false;
	int aCurrentNumBalls = (int) mUnk0x164.size();
	// STRING: POPCAPGAME1 0x005eaec0
	// STRING: POPCAPGAME1 0x005eae78
	// STRING: POPCAPGAME1 0x005eae30
	int aSoundOffset =
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp951,449", 20) +
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp950,449", 4) *
		(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp949,449", 9) + theNumBalls - aCurrentNumBalls);
	if (aSoundOffset >= 0 && theNumBalls <= 2) {
		mBoard->mSoundMgr->AddSound(SOUND_ADD_BALL, 0.0f, 0, aSoundOffset, 1, -1.0f);
	}

	int aBallSpacing = GetBallSpacing();
	// STRING: POPCAPGAME1 0x005eade8
	int aBallY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\InterfaceMgr.cpp952,454", 100);
	for (int i = 0; i < theNumBalls; ++i) {
		SexyVector2 aNewBall;
		mUnk0x164.push_back(aNewBall);
		SexyVector2& aBall = mUnk0x164.back();
		aBall.x = (float) aBallY;
		aBallY -= aBallSpacing;
		aBall.y = 0.0f;
	}
}

// STUB: POPCAPGAME1 0x0045c5a0
void InterfaceMgr::SyncState(DataSync& param_1)
{
}

// STUB: POPCAPGAME1 0x004439b0
void InterfaceMgr::SyncStageNum()
{
}

// STUB: POPCAPGAME1 0x00447360
void InterfaceMgr::DrawBallsLeftDetail(Graphics* param_1, int param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x004474b0
void InterfaceMgr::DrawOnePlayer(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004476f0
void InterfaceMgr::DrawStageMode(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00447920
void InterfaceMgr::DrawTrophyMode(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00447b90
void InterfaceMgr::DrawTwoPlayer(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00447f60
void InterfaceMgr::DrawBack(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004417b0
void InterfaceMgr::DrawFront(Graphics* param_1)
{
}
