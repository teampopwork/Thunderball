#include "Hole.h"

#include "Ball.h"
#include "DataSync.h"
#include "Mover.h"

#include <SexyAppFramework/Graphics.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004810e0
Hole::Hole()
{
    mUnk0xf4 = 0.0f;
    mUnk0xf8 = 0.0f;
    mUnk0xfc = 0.0f;
    mUnk0x100 = 0.0f;
    mUnk0x10 = 1;
    mUnk0xec = 0;
    mUnk0x10c = false;
    mUnk0xf0 = 0;
    mUnk0xe8 = 0;
    SetSize(100, 0x14);
}

// SYNTHETIC: POPCAPGAME1 0x004811e0
// Sexy::Hole::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00481160
Hole::~Hole()
{
}

// FUNCTION: POPCAPGAME1 0x00480530
bool Hole::EditGetSetValHook(const std::string& theKey, bool isSet)
{
	if (PhysObj::EditGetSetValHook(theKey, isSet)) {
		return true;
	}

	if (theKey != "poly_width" && theKey != "poly_height") {
		if (theKey == "hole_circular") {
			return EditValSyncBool(mUnk0x10c);
		}
		if (theKey == "hole_score") {
			return EditValSyncNum(mUnk0xf0);
		}
		if (theKey == "hole_outdelay") {
			return EditValSyncNum(mUnk0xe8);
		}
		return false;
	}

	int& aDimension = theKey == "poly_width" ? mUnk0x104 : mUnk0x108;
	EditValSyncNum(aDimension, 1, 100000);
	if (isSet) {
		SetSize(mUnk0x104, mUnk0x108);
	}
	return true;
}

// FUNCTION: POPCAPGAME1 0x00481210
void Hole::SyncState(DataSync& theSync)
{
	PhysObj::SyncState(theSync);

	if (theSync.mReader != NULL) {
		mUnk0xec = 0;
		mUnk0xf0 = 0;
		mUnk0xe8 = 0;
		mUnk0xe4 = NULL;
	}

	bool hasMover = mMover != NULL;
	bool hasFlash = mUnk0xec != 0;
	bool syncPosition = !hasMover;
	bool hasScore = mUnk0xf0 != 0;
	bool hasConnectedHole = mUnk0xe4 != NULL;
	bool hasOutDelay = mUnk0xe8 != 0;
	bool hasVelocity = mUnk0xfc != 0.0f || mUnk0x100 != 0.0f;

	theSync.SyncBoolBit(mUnk0x10c);
	theSync.SyncBoolBit(hasFlash);
	theSync.SyncBoolBit(syncPosition);
	theSync.SyncBoolBit(hasScore);
	theSync.SyncBoolBit(hasConnectedHole);
	theSync.SyncBoolBit(hasOutDelay);
	theSync.SyncBoolBit(hasVelocity);
	theSync.EndBit();

	theSync.SyncLong(mUnk0x104);
	theSync.SyncLong(mUnk0x108);
	if (hasFlash) {
		theSync.SyncShort(mUnk0xec);
	}
	if (hasScore) {
		theSync.SyncLong(mUnk0xf0);
	}
	if (hasOutDelay) {
		theSync.SyncLong(mUnk0xe8);
	}
	if (hasConnectedHole) {
		DataSync_SyncSmartPtrFactory<PhysObj>(theSync, mUnk0xe4, NULL);
	}
	if (syncPosition) {
		theSync.SyncFloat(mUnk0xf4);
		theSync.SyncFloat(mUnk0xf8);
	} else if (theSync.mReader != NULL && hasMover) {
		mUnk0xf4 = mMover->mUnk0x54;
		mUnk0xf8 = mMover->mUnk0x58;
	}
	if (hasVelocity) {
		theSync.SyncFloat(mUnk0xfc);
		theSync.SyncFloat(mUnk0x100);
	} else {
		mUnk0xfc = 0.0f;
		mUnk0x100 = 0.0f;
	}

	SetSize(mUnk0x104, mUnk0x108);
}

// FUNCTION: POPCAPGAME1 0x00481140
int Hole::GetClass()
{
	return 8;
}

// FUNCTION: POPCAPGAME1 0x00478110
void Hole::EditDrawOutline(Graphics* g)
{
	g->DrawRect(
		(int)(mUnk0x14 - 3.0),
		(int)(mUnk0x18 - 3.0),
		(int)(mUnk0x1c - mUnk0x14 + 6.0),
		(int)(mUnk0x20 - mUnk0x18 + 6.0));
	if (mUnk0xe4 != NULL) {
		g->DrawLine(
			(int)mUnk0xf4,
			(int)mUnk0xf8,
			(int)mUnk0xe4->GetXPos(),
			(int)mUnk0xe4->GetYPos());
	}
}

// FUNCTION: POPCAPGAME1 0x00475540
void Hole::SetPos(float theX, float theY)
{
	Translate(theX - mUnk0xf4, theY - mUnk0xf8);
}

// FUNCTION: POPCAPGAME1 0x004754f0
void Hole::Translate(float theDx, float theDy)
{
	mUnk0xf4 += theDx;
	mUnk0xf8 += theDy;
	mUnk0x14 += theDx;
	mUnk0x1c += theDx;
	mUnk0x18 += theDy;
	mUnk0x20 += theDy;
}

// FUNCTION: POPCAPGAME1 0x00475600
void Hole::SetVelocity(float theVx, float theVy)
{
	mUnk0xfc = theVx;
	mUnk0x100 = theVy;
}

// FUNCTION: POPCAPGAME1 0x0047a930
void Hole::Update()
{
	PhysObj::Update();
	if (mUnk0xec != 0) {
		mUnk0xec--;
	}
}

// STUB: POPCAPGAME1 0x0047ce60
void Hole::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x0047a230
void Hole::DrawLight(Graphics* g)
{
    PhysObj::DrawLight(g);
}

// FUNCTION: POPCAPGAME1 0x0047dfa0
float Hole::GetXPos()
{
	return mUnk0xf4;
}

// FUNCTION: POPCAPGAME1 0x00481150
float Hole::GetYPos()
{
	return mUnk0xf8;
}

// FUNCTION: POPCAPGAME1 0x00475580
void Hole::SetSize(int theWidth, int theHeight)
{
	float aHalfWidth = (float)theWidth * 0.5;
	float aHalfHeight = (float)theHeight * 0.5;
	mUnk0x104 = theWidth;
	mUnk0x108 = theHeight;
	mUnk0x14 = mUnk0xf4 - aHalfWidth;
	mUnk0x1c = aHalfWidth + mUnk0xf4;
	mUnk0x18 = mUnk0xf8 - aHalfHeight;
	mUnk0x20 = aHalfHeight + mUnk0xf8;
}

// FUNCTION: POPCAPGAME1 0x004755f0
void Hole::SetFlashCount(int theCount)
{
	mUnk0xec = theCount;
}

// FUNCTION: POPCAPGAME1 0x004781c0
bool Hole::CheckCollision(Ball* theBall)
{
	float aCenterX = mUnk0xf4;
	float aCenterY = mUnk0xf8;
	float aHalfWidth = (float)mUnk0x104 * 0.5f;
	float aHalfHeight = (float)mUnk0x108 * 0.5f;
	float aBallX = theBall->mUnk0xec;
	float aBallY = theBall->mUnk0xf0;

	if (aBallX < aCenterX - aHalfWidth ||
		aBallX > aCenterX + aHalfWidth ||
		aBallY < aCenterY - aHalfHeight ||
		aBallY > aCenterY + aHalfHeight) {
		return false;
	}

	if (mUnk0x10c) {
		float aDeltaX = aBallX - aCenterX;
		float aDeltaY = aBallY - aCenterY;
		if (aDeltaX * aDeltaX / (aHalfWidth * aHalfWidth) +
			aDeltaY * aDeltaY / (aHalfHeight * aHalfHeight) > 1.0f) {
			return false;
		}
	}

	if (mNotifyCollisionFunc != NULL) {
		mNotifyCollisionFunc(theBall, this);
		SetFlashCount(100);
	}
	return true;
}

// STUB: POPCAPGAME1 0x0047cac0
void Hole::DrawHole(Graphics* g, int param_2, int param_3)
{
}
