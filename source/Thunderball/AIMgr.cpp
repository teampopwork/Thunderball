#include "AIMgr.h"
#include "CollisionMgr.h"
#include "PhysObj.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00454cb0
AIMgr::AIMgr(Board* param_1)
{
	mUnk0x88 = 0.0f;
	mUnk0x8C = 0.0f;
	mBoard = param_1;
	mCollisionMgr = new CollisionMgr();
	mUnk0x4C = false;
	mUnk0x54 = 10;
	mUnk0x60 = 30;
	Clear();
}

// SYNTHETIC: POPCAPGAME1 0x00460350
// Sexy::AIMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0045aa50
AIMgr::~AIMgr()
{
	delete mCollisionMgr;
}

// STUB: POPCAPGAME1 0x004327d0
float AIMgr::KeepAngleInRange(float param_1)
{
	return param_1;
}

// FUNCTION: POPCAPGAME1 0x00432860
bool AIMgr::GetEyePos(SexyVector2* param_1)
{
	if (mUnk0x4D && mUnk0x50 < mUnk0x58)
	{
		*param_1 = mEyePos;
		return true;
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x004328a0
void AIMgr::NotifyCollision(PhysObj* param_1, PhysObj* param_2)
{
	param_1->NotifyCollision(param_2);
}

// STUB: POPCAPGAME1 0x00438520
float AIMgr::GetAngleForPeg(PhysObj* param_1)
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x00440f40
void AIMgr::Draw(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x0043fdc0
void AIMgr::UpdateFreeBallRadius(int param_1)
{
}

// STUB: POPCAPGAME1 0x00460380
void AIMgr::UpdateOneFrame()
{
}

// STUB: POPCAPGAME1 0x0043fc30
float AIMgr::CalcDefAngle()
{
	return 0.0f;
}

// FUNCTION: POPCAPGAME1 0x0044b120
void AIMgr::Clear()
{
	mUnk0x4D = false;
	mUnk0x4E = false;
	mUnk0x58 = 0;
	if (mUnk0x3C != NULL)
		mUnk0x40 = mUnk0x3C;
	mUnk0x3C = NULL;
	mUnk0x44 = NULL;
	mUnk0x48 = NULL;
	mUnk0x30.clear();
	mUnk0xC.clear();
	mUnk0x24.clear();
	mUnk0x18.clear();
	mCollisionMgr->Clear();
}

// STUB: POPCAPGAME1 0x004604c0
void AIMgr::Update()
{
}

// STUB: POPCAPGAME1 0x004637e0
void AIMgr::BeginThinking2(bool param_1, float param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x00465740
void AIMgr::BeginThinking(bool param_1, float param_2, int param_3, int param_4)
{
}
