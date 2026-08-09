#include "InterfaceMgr.h"

#include "Board.h"
#include "LogicMgr.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/MemoryImage.h>

using namespace Sexy;

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

// STUB: POPCAPGAME1 0x00436890
void InterfaceMgr::DrawScore(Graphics* param_1, std::string* param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00436950
void InterfaceMgr::DrawSmallMode(Graphics* param_1, std::string* param_2, bool param_3)
{
}

// FUNCTION: POPCAPGAME1 0x0043ca00
void InterfaceMgr::DrawMode(Graphics* param_1, std::string* param_2, bool param_3)
{
    DrawSmallMode(param_1, param_2, param_3);
}

// STUB: POPCAPGAME1 0x00436a10
void InterfaceMgr::DrawDetail(Graphics* param_1, std::string* param_2, bool param_3, int param_4)
{
}

// STUB: POPCAPGAME1 0x00436ae0
void InterfaceMgr::DrawScoreBlink(Graphics* param_1)
{
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

// STUB: POPCAPGAME1 0x00436c90
void InterfaceMgr::UpdateShotMeter()
{
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

// STUB: POPCAPGAME1 0x00448190
void InterfaceMgr::CheckHighScoreSync()
{
}

// STUB: POPCAPGAME1 0x004482d0
void InterfaceMgr::SettleDown()
{
}

// STUB: POPCAPGAME1 0x004481d0
void InterfaceMgr::UpdateScoreDisp()
{
}

// STUB: POPCAPGAME1 0x0043cfd0
void InterfaceMgr::DrawShotMeter(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x0043c7b0
void InterfaceMgr::DrawImageToInterface(Image* param_1, int param_2, int param_3, int param_4)
{
}

// STUB: POPCAPGAME1 0x0043c990
void InterfaceMgr::DrawImageCelToInterface(Image* param_1, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x0043c9b0
void InterfaceMgr::LoadGun()
{
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

// STUB: POPCAPGAME1 0x004724e0
void InterfaceMgr::UpdateHighScore(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004725f0
void InterfaceMgr::InitLevel()
{
}

// STUB: POPCAPGAME1 0x00442db0
int InterfaceMgr::GetTopBallY()
{
	return 0;
}

// STUB: POPCAPGAME1 0x0043c770
int InterfaceMgr::GetNumVisibleBalls()
{
	return 0;
}

// STUB: POPCAPGAME1 0x0043d310
void InterfaceMgr::DrawBalls(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00443cf0
void InterfaceMgr::UpdateBalls()
{
}

// STUB: POPCAPGAME1 0x00457870
void InterfaceMgr::SetNumBalls(int param_1)
{
}

// STUB: POPCAPGAME1 0x00447260
void InterfaceMgr::Clear()
{
}

// STUB: POPCAPGAME1 0x004517c0
void InterfaceMgr::AddBottomBall(int param_1)
{
}

// STUB: POPCAPGAME1 0x004518b0
void InterfaceMgr::Update()
{
}

// STUB: POPCAPGAME1 0x0045c860
void InterfaceMgr::AddTopBalls(int param_1)
{
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
