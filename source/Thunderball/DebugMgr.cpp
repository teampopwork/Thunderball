#include "DebugMgr.h"

#include "Ball.h"
#include "ThunderCommon.h"
#include "../SexyAppFramework/SexyApp.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0043ffa0
DebugMgr::DebugMgr(Board* param_1) : mBoard(param_1)
{
	mUnk0x4 = false;
	mUnk0x5 = false;
	mUnk0x6 = false;
	Clear();
	mUnk0x18 = -1;
	mUnk0x14 = -1;
}

// SYNTHETIC: POPCAPGAME1 0x0043e470
// Sexy::DebugMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00439a80
DebugMgr::~DebugMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00432db0
void DebugMgr::MarkCheat()
{
	mUnk0x20 = true;
}

// STUB: POPCAPGAME1 0x004648e0
void DebugMgr::SyncFlipperState()
{
}

// FUNCTION: POPCAPGAME1 0x0054b760
bool DebugMgr::MouseMove(int theX, int theY)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x0054b760
bool DebugMgr::MouseDrag(int theX, int theY)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00432dc0
bool DebugMgr::MouseEnter()
{
	if (mUnk0x4)
		gSexyApp->SetCursor(1);
	return false;
}

// FUNCTION: POPCAPGAME1 0x00432de0
bool DebugMgr::MouseLeave()
{
	if (mUnk0x4)
		gSexyApp->SetCursor(0);
	return false;
}

// FUNCTION: POPCAPGAME1 0x00437350
bool DebugMgr::KeyChar(SexyChar theKey)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00437350
bool DebugMgr::MouseWheel(int theDelta)
{
	return false;
}

// STUB: POPCAPGAME1 0x00439ab0
void DebugMgr::UpdateMouseBall()
{
}

// STUB: POPCAPGAME1 0x004414e0
void DebugMgr::SyncFeverState()
{
}

// STUB: POPCAPGAME1 0x00440010
Ball* DebugMgr::GetBallAt(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00446670
void DebugMgr::SyncNumDebugPegs()
{
}

// STUB: POPCAPGAME1 0x00464930
void DebugMgr::InitLevel()
{
}

// FUNCTION: POPCAPGAME1 0x0043e4a0
void DebugMgr::Clear()
{
	mMouseBall = NULL;
	mUnk0x1C = 0;
	mUnk0x20 = false;
	mUnk0x21 = false;
}

// FUNCTION: POPCAPGAME1 0x0043e4e0
void DebugMgr::SetMouseBall(Ball* param_1)
{
	if (mMouseBall != NULL)
		mMouseBall->mUnk0x140 = false;
	mMouseBall = param_1;
	if (mMouseBall != NULL)
		mMouseBall->mUnk0x140 = true;
}

// FUNCTION: POPCAPGAME1 0x0043e520
bool DebugMgr::MouseUp(int theX, int theY, int theClickCount)
{
	if (mUnk0x4)
	{
		SetMouseBall(NULL);
		return true;
	}
	return false;
}

// STUB: POPCAPGAME1 0x00044b4a0
bool DebugMgr::MouseDown(int theX, int theY, int theClickCount)
{
	return false;
}

// STUB: POPCAPGAME1 0x0044db10
void DebugMgr::DeleteBalls(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0044dcd0
void DebugMgr::Update()
{
}
