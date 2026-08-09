#include "Line.h"
#include "DataSync.h"

#include <SexyAppFramework/SexyVector.h>

#include <math.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00481440
Line::Line()
{
	mUnk0x104 = 0.0f;
	mUnk0x108 = 0.0f;
	mUnk0xfc = 0.0f;
	mUnk0x100 = 0.0f;
	mUnk0x10 = 4;
	mUnk0x111 = false;
}

// FUNCTION: POPCAPGAME1 0x00481480
Line::Line(float param_1, float param_2, float param_3, float param_4)
{
	mUnk0x104 = 0.0f;
	mUnk0x108 = 0.0f;
	mUnk0xfc = 0.0f;
	mUnk0x100 = 0.0f;
	mUnk0x10 = 4;
	mUnk0x111 = false;
	Init(param_1, param_2, param_3, param_4);
}

// SYNTHETIC: POPCAPGAME1 0x0047f5a0
// Sexy::Line::`scalar destroying destructor'

// FUNCTION: POPCAPGAME1 0x0047df70
Line::~Line()
{
}

// FUNCTION: POPCAPGAME1 0x004814f0
void Line::SyncState(DataSync& sync)
{
	PhysObj::SyncState(sync);
	bool syncVx = mUnk0xfc != 0.0f;
	bool syncVy = mUnk0x100 != 0.0f;
	sync.SyncBoolBit(syncVx);
	sync.SyncBoolBit(syncVy);
	sync.SyncBoolBit(mUnk0x111);
	sync.EndBit();
	sync.SyncFloat(mUnk0xec);
	sync.SyncFloat(mUnk0xf4);
	sync.SyncFloat(mUnk0xf0);
	sync.SyncFloat(mUnk0xf8);
	if (syncVx) {
		sync.SyncFloat(mUnk0xfc);
	}
	if (syncVy) {
		sync.SyncFloat(mUnk0x100);
	}
	if (mSyncType == 3) {
		sync.SyncFloat(mUnk0xe4);
		sync.SyncFloat(mUnk0xe8);
		sync.SyncFloat(mUnk0x104);
		sync.SyncFloat(mUnk0x108);
		sync.SyncBoolBit(mUnk0x110);
		sync.EndBit();
		SetPos(mUnk0xec, mUnk0xf4);
	} else if (sync.mReader != NULL) {
		Init(mUnk0xec, mUnk0xf4, mUnk0xf0, mUnk0xf8);
	}
}

// FUNCTION: POPCAPGAME1 0x0047df80
int Line::GetClass()
{
	return 2;
}

// STUB: POPCAPGAME1 0x00476190
void Line::EditDrawOutline(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x000476310
void Line::EditDrawPoints(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00478db0
bool Line::EditContains(float param_1, float param_2, bool param_3)
{
	return GetDistanceFromPoint(param_1, param_2) < (param_3 ? 20.0f : 5.0f);
}

// FUNCTION: POPCAPGAME1 0x00478be0
void Line::EditGetDragMode(float param_1, float param_2)
{
	float aDx1 = mUnk0xec - param_1;
	float aDy1 = mUnk0xf4 - param_2;
	float aDx2 = mUnk0xf0 - param_1;
	float aDy2 = mUnk0xf8 - param_2;
	if (aDx1 * aDx1 + aDy1 * aDy1 < aDx2 * aDx2 + aDy2 * aDy2) {
		mUnk0xd8 = 1;
	} else {
		mUnk0xd8 = 2;
	}
}

// FUNCTION: POPCAPGAME1 0x00478ca0
void Line::EditDoPointDrag(float param_1, float param_2)
{
	if (mUnk0xd8 == 1) {
		mUnk0xec = param_1;
		mUnk0xf4 = param_2;
	} else {
		mUnk0xf0 = param_1;
		mUnk0xf8 = param_2;
	}
	Init(mUnk0xec, mUnk0xf4, mUnk0xf0, mUnk0xf8);
}

// FUNCTION: POPCAPGAME1 0x00478d10
void Line::EditReflect(float param_1, float param_2, bool param_3, bool param_4)
{
	PhysObj::EditReflect(param_1, param_2, param_3, param_4);
	if (param_4) {
		if (param_3) {
			Init(mUnk0xf0, mUnk0xf4, mUnk0xec, mUnk0xf8);
		} else {
			Init(mUnk0xec, mUnk0xf8, mUnk0xf0, mUnk0xf4);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00478440
void Line::SetPos(float theX, float theY)
{
	mUnk0xec = theX;
	mUnk0xf4 = theY;
	mUnk0xf0 = mUnk0xe4 + theX;
	mUnk0xf8 = mUnk0xe8 + theY;
	mUnk0x10c = -(mUnk0x104 * theX + mUnk0x108 * theY);
	mUnk0x14 = theX;
	mUnk0x1c = mUnk0xf0;
	mUnk0x18 = theY;
	mUnk0x20 = mUnk0xf8;
	if (mUnk0xf0 < theX) {
		float aTemp = mUnk0x14;
		mUnk0x14 = mUnk0x1c;
		mUnk0x1c = aTemp;
	}
	if (mUnk0x20 < mUnk0x18) {
		float aTemp = mUnk0x18;
		mUnk0x18 = mUnk0x20;
		mUnk0x20 = aTemp;
	}
}

// FUNCTION: POPCAPGAME1 0x00475620
void Line::Translate(float theDx, float theDy)
{
	SetPos(mUnk0xec + theDx, mUnk0xf4 + theDy);
}

// FUNCTION: POPCAPGAME1 0x00475600
void Line::SetVelocity(float theVx, float theVy)
{
	mUnk0xfc = theVx;
	mUnk0x100 = theVy;
}

// STUB: POPCAPGAME1 0x00476390
void Line::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x0047df90
float Line::GetXPos()
{
	return mUnk0xec;
}

// FUNCTION: POPCAPGAME1 0x0047dfa0
float Line::GetYPos()
{
	return mUnk0xf4;
}

// FUNCTION: POPCAPGAME1 0x004782f0
void Line::Init(float param_1, float param_2, float param_3, float param_4)
{
	mUnk0xec = param_1;
	mUnk0xf0 = param_3;
	mUnk0xf4 = param_2;
	mUnk0xf8 = param_4;
	mUnk0xe4 = mUnk0xf0 - mUnk0xec;
	mUnk0xe8 = mUnk0xf8 - mUnk0xf4;
	mUnk0x14 = mUnk0xec;
	mUnk0x1c = mUnk0xf0;
	mUnk0x18 = mUnk0xf4;
	mUnk0x20 = mUnk0xf8;
	if (mUnk0xf0 < mUnk0xec) {
		float aTemp = mUnk0x14;
		mUnk0x14 = mUnk0x1c;
		mUnk0x1c = aTemp;
	}
	if (mUnk0x20 < mUnk0x18) {
		float aTemp = mUnk0x18;
		mUnk0x18 = mUnk0x20;
		mUnk0x20 = aTemp;
	}
	if (fabs(mUnk0xf4 - mUnk0xf8) > fabs(mUnk0xec - mUnk0xf0)) {
		mUnk0x110 = true;
	} else {
		mUnk0x110 = false;
	}
	SexyVector2 aNormal = SexyVector2(mUnk0xf4 - mUnk0xf8, mUnk0xf0 - mUnk0xec).Normalize();
	mUnk0x104 = aNormal.x;
	mUnk0x108 = aNormal.y;
	mUnk0x10c = -(mUnk0x104 * mUnk0xec + mUnk0x108 * mUnk0xf4);
}

// STUB: POPCAPGAME1 0x00476010
bool Line::IsPartlyInsideRect(Rect* theRect)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00476380
bool Line::EditIntersects(Rect* theRect)
{
	return IsPartlyInsideRect(theRect);
}

// STUB: POPCAPGAME1 0x00475660
void Line::CalcEdgeHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
}

// STUB: POPCAPGAME1 0x00475660
void Line::CalcVertexHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
}

// STUB: POPCAPGAME1 0x00475bd0
bool Line::CircleIntersect(float param_1, float param_2, float param_3, SexyVector2* param_4, SexyVector2* param_5)
{
	return false;
}

// STUB: POPCAPGAME1 0x00475890
bool Line::CheckEdgeTimeCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	SexyVector2* param_4,
	SexyVector2* param_5,
	SexyVector2* hitNormal,
	float* hitTime
)
{
	return false;
}

// STUB: POPCAPGAME1 0x004756c0
bool Line::CheckVertexTimeCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	float* param_4,
	SexyVector2* param_5,
	float param_6,
	float param_7,
	SexyVector2* param_8,
	SexyVector2* param_9
)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478500
bool Line::CheckPenetration(
	SexyVector2* param_1,
	float param_2,
	SexyVector2* param_3,
	SexyVector2* param_4,
	SexyVector2* param_5
)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478940
bool Line::CheckCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	float* param_4,
	SexyVector2* param_5,
	SexyVector2* param_6,
	SexyVector2* param_7,
	bool param_8
)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00478ac0
float Line::GetDistanceFromPoint(float param_1, float param_2)
{
	if ((mUnk0x110 && mUnk0x18 <= param_2 && param_2 <= mUnk0x20) ||
		(!mUnk0x110 && mUnk0x14 <= param_1 && param_1 <= mUnk0x1c)) {
		return fabs(param_2 * mUnk0x108 + mUnk0x104 * param_1 + mUnk0x10c);
	}

	float aDx1 = mUnk0xec - param_1;
	float aDy1 = mUnk0xf4 - param_2;
	float aDist1 = aDx1 * aDx1 + aDy1 * aDy1;
	float aDx2 = mUnk0xf0 - param_1;
	float aDy2 = mUnk0xf8 - param_2;
	float aDist2 = aDx2 * aDx2 + aDy2 * aDy2;
	if (aDist1 < aDist2) {
		return sqrtf(aDist1);
	}
	return sqrtf(aDist2);
}

