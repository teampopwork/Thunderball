#include "Gun.h"
#include "Ball.h"
#include "Board.h"
#include "DataSync.h"
#include "LogicMgr.h"
#include "ThunderCommon.h"

#include <SexyAppFramework/Common.h>

#include <math.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00475310
static float GetAngleDelta(float param_1, float param_2)
{
	const double aFullTurn = 6.28318530717958647692;
	while (param_2 > aFullTurn)
		param_2 -= aFullTurn;
	while (param_1 > param_2)
		param_1 -= aFullTurn;

	float aDelta = param_2 - param_1;
	if (aDelta > 3.14159265358979323846)
		aDelta = -(aFullTurn - aDelta);
	return aDelta;
}

// FUNCTION: POPCAPGAME1 0x00475390
static int GetFloatSign(float param_1)
{
	if (param_1 > 0.0f)
		return 1;
	if (param_1 < 0.0f)
		return -1;
	return 0;
}

// FUNCTION: POPCAPGAME1 0x004bc3b0
float NormalizeAngle(float param_1)
{
	const float aFullTurn = SEXY_PI * 2.0f;
	if (param_1 >= 0.0f && param_1 < aFullTurn)
		return param_1;
	if (param_1 < 0.0f)
		return aFullTurn - fmodf(-param_1, aFullTurn);
	return fmodf(param_1, aFullTurn);
}

// FUNCTION: POPCAPGAME1 0x00486a90
Gun::Gun(Board* param_1)
	: mUnk0x174(0.0f),
	  mUnk0x178(0.0f),
	  mUnk0x1a4(0.0f),
	  mUnk0x1a8(0.0f)
{
	mUnk0x114 = 0.0f;
	mUnk0x118 = 0.0f;
	mBoard = param_1;
	mUpdateCount = 0;
	mUnk0x160 = 4.0f;
	mUnk0x134 = 1;
	mUnk0x180 = true;
	mLastTrackedAngle = 0.0f;
	mSettledAngle = 0.0f;
	mAngle = 0.0f;
	mUnk0x1b0 = 0.0f;
	mUnk0x198 = -1;
	mUnk0x1b4 = 0.0f;
	mUnk0x19c = -1;
	mUnk0x1b8 = 0.0f;
	mSettledUpdate = 0;
	mUnk0x1bc = 0.0f;
	mAngleStableTicks = 0;
	mUnk0x194 = false;
	mUnk0x164 = 30.0f;
	mUnk0x195 = false;
	mUnk0x1a1 = false;
	mUnk0x168 = 10.0f;
	mUnk0x16c = 60.0f;
	mUnk0x170 = 26.0f;
	mAngularVelocity = 1000.0f;
	mUnk0x1ac = 1000.0f;
	CalcPoints();
}

// SYNTHETIC: POPCAPGAME1 0x00486cd0
// Sexy::Gun::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00486c20
Gun::~Gun()
{
}

// FUNCTION: POPCAPGAME1 0x004752b0
void Gun::UpdateCommon()
{
	if (mAngle == mLastTrackedAngle)
	{
		mAngleStableTicks++;
		if (mAngleStableTicks >= 30)
		{
			mSettledAngle = mAngle;
			mSettledUpdate = mUpdateCount;
		}
	}
	else
	{
		mAngleStableTicks = 0;
		mLastTrackedAngle = mAngle;
	}
}

// FUNCTION: POPCAPGAME1 0x0047df50
void Gun::UpdateSlowMo(float param_1)
{
	Poly::UpdateSlowMo(param_1);
	UpdateCommon();
}

// FUNCTION: POPCAPGAME1 0x00477bf0
bool Gun::CanFire()
{
	return mBall.get() != NULL;
}

// FUNCTION: POPCAPGAME1 0x004754a0
int Gun::GetMaxGuideLength()
{
	return mUnk0x194 ? 80 : 40;
}

// FUNCTION: POPCAPGAME1 0x004754c0
bool Gun::NeedDrawMouseClick()
{
	return (!mUnk0x194 && mUnk0x198 < 0) || mUnk0x198 > GetMaxGuideLength();
}

// FUNCTION: POPCAPGAME1 0x0047f590
void Gun::Draw(Graphics* param_1)
{
	Poly::Draw(param_1);
}

// STUB: POPCAPGAME1 0x0047c030
void Gun::DrawBouncyGuide(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00477c00
void Gun::DoDrawGuide(Graphics* param_1, float param_2, float param_3, float param_4, float param_5, int param_6, int param_7, int param_8, bool param_9)
{
}

// STUB: POPCAPGAME1 0x0047c940
void Gun::DrawGuide(Graphics* param_1, bool param_2)
{
}

// FUNCTION: POPCAPGAME1 0x0047bf30
float Gun::CalcAngularVelocity()
{
	if (mAngleHistory.empty())
		return 0.0f;

	while (!mAngleHistory.empty() && mUpdateCount - mAngleHistory.front().second > 20)
		mAngleHistory.pop_front();

	if (mAngleHistory.empty())
		return 0.0f;

	float aTotal = 0.0f;
	for (std::list<std::pair<float, int> >::iterator anItr = mAngleHistory.begin(); anItr != mAngleHistory.end(); ++anItr)
		aTotal += anItr->first;

	int anElapsed = mUpdateCount - mAngleHistory.front().second;
	if (anElapsed <= 0)
		anElapsed = 1;

	return aTotal / anElapsed;
}

// FUNCTION: POPCAPGAME1 0x00483da0
void Gun::CalcPoints()
{
	mUnk0x12d = true;
	mUnk0x12e = true;

	if (mUnk0x108.size() != 3)
	{
		mUnk0x108.clear();
		SexyVector2 aPoint(0.0f, 0.0f);
		for (int i = 0; i < 3; i++)
		{
			mUnk0x108.push_back(new Line(0.0f, 0.0f, 0.0f, 0.0f));
			mUnk0x108.back()->mUnk0x111 = true;
			mUnk0xf8.push_back(aPoint);
		}
	}

	float aRadius = Ball::mDefRadius;
	if (mBall.get() != NULL)
		aRadius = mBall->mUnk0x13c;

	SexyVector2 aPoints[4];
	aPoints[0] = SexyVector2(mUnk0x114 + mUnk0x164, mUnk0x118);
	aPoints[1] = SexyVector2(mUnk0x114, mUnk0x118 - mUnk0x168);
	aPoints[2] = SexyVector2(mUnk0x114, mUnk0x118 + mUnk0x168);
	aPoints[3] = SexyVector2(
		mUnk0x114 + mUnk0x170 + aRadius,
		mUnk0x118 + (float) ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Gun.cpp17,151", 1));

	for (int i = 0; i < 4; i++)
	{
		aPoints[i].x += mUnk0x16c;
		RotateXY(&aPoints[i].x, &aPoints[i].y, mUnk0x114, mUnk0x118, mAngle);
	}

	for (int i = 0; i < 3; i++)
	{
		Line* aLine = mUnk0x108[i];
		const SexyVector2& aStart = aPoints[i];
		const SexyVector2& anEnd = aPoints[(i + 1) % 3];
		aLine->Init(aStart.x, aStart.y, anEnd.x, anEnd.y);
		mUnk0xf8[i] = SexyVector2(aLine->mUnk0xec - mUnk0x114, aLine->mUnk0xf4 - mUnk0x118);
	}

	if (mBall.get() != NULL)
		mBall->SetAbsPos(aPoints[3].x, aPoints[3].y);

	mUnk0x158 = aPoints[3].x;
	mUnk0x15c = aPoints[3].y;
	CalcBoundingBox();
}

// FUNCTION: POPCAPGAME1 0x00484500
void Gun::SetFireball(bool param_1)
{
	if (mBall.get() != NULL)
	{
		mBall->SetFireball(param_1);
		mUnk0x1a1 = param_1;
		CalcPoints();
	}
}

// FUNCTION: POPCAPGAME1 0x004844c0
void Gun::Reload(Ball* param_1)
{
	mBall = param_1;
	mBall->mUnk0x140 = true;
	mUnk0x1a1 = false;
	CalcPoints();
}

// FUNCTION: POPCAPGAME1 0x004843a0
bool Gun::SetAngle(float param_1, bool param_2)
{
	if (param_1 == mAngle)
		return false;

	if (param_2)
	{
		mAngleHistory.clear();
		mAngle = param_1;
		mTargetAngle = param_1;
		mSettledUpdate = mUpdateCount - 1000;
		CalcPoints();
		return true;
	}

	if (param_1 == mTargetAngle)
		return true;

	float anAngleDelta = GetAngleDelta(mAngle, param_1);
	if (!mAngleHistory.empty() && GetFloatSign(mAngleHistory.back().first) == GetFloatSign(anAngleDelta))
		mAngleHistory.clear();

	mAngleHistory.push_back(std::make_pair(anAngleDelta, mUpdateCount));
	mTargetAngle = param_1;

	return true;
}

// FUNCTION: POPCAPGAME1 0x004882c0
void Gun::SyncState(DataSync& param_1)
{
	SyncCommon(param_1, false);

	if (param_1.mReader != NULL)
		mUpdateCount = 0;

	bool hasUpdateCount = mUpdateCount != 0;
	bool hasBouncyGuide = mUnk0x1bc != 0.0f;
	param_1.SyncBoolBit(hasUpdateCount);
	param_1.SyncBoolBit(mUnk0x194);
	param_1.SyncBoolBit(hasBouncyGuide);
	param_1.SyncBoolBit(mUnk0x195);
	param_1.SyncBoolBit(mUnk0x1a1);
	param_1.SyncBoolBit(mUnk0x1a2);
	param_1.EndBit();

	if (hasUpdateCount)
		param_1.SyncLong(mUpdateCount);
	if (hasBouncyGuide)
	{
		param_1.SyncFloat(mUnk0x1b0);
		param_1.SyncFloat(mUnk0x1b4);
		param_1.SyncFloat(mUnk0x1b8);
		param_1.SyncFloat(mUnk0x1bc);
	}

	param_1.SyncFloat(mAngle);
	DataSync_SyncSmartPtr<Ball>(param_1, mBall);

	if (param_1.mReader != NULL)
	{
		CalcPoints();
		mTargetAngle = mAngle;
	}
}

// STUB: POPCAPGAME1 0x00482910
void Gun::UpdateBouncyGuide()
{
}

// STUB: POPCAPGAME1 0x00484530
SmartPtr<Ball> Gun::Fire(bool param_1)
{
	if (mBall.get() == NULL)
		return NULL;

	float anOldAngle = mAngle;
	if (param_1 && mUpdateCount - mSettledUpdate < 10)
	{
		mAngle = mSettledAngle;
		CalcPoints();
		if (mUnk0x194)
			UpdateBouncyGuide();
	}

	SmartPtr<Ball> aBall = mBall;
	mBall = NULL;
	mUnk0x1b0 = mAngle;
	mUnk0x1b4 = mUnk0x158;
	mUnk0x1b8 = mUnk0x15c;
	mUnk0x1bc = mUnk0x160;

	aBall->mUnk0x140 = false;
	aBall->SetVelocity(
		mUnk0x160 * (float) cos(mAngle),
		-mUnk0x160 * (float) sin(mAngle));

	if (anOldAngle != mAngle)
	{
		mAngle = anOldAngle;
		CalcPoints();
	}

	return aBall;
}

// FUNCTION: POPCAPGAME1 0x00484120
void Gun::Update()
{
	Poly::Update();
	mUpdateCount++;

	float anX = 0.0f;
	float aY = 0.0f;
	if (!mUnk0x108.empty())
	{
		anX = mUnk0x108.front()->mUnk0xfc;
		aY = mUnk0x108.front()->mUnk0x100;
	}

	float anAngularVelocity = CalcAngularVelocity();
	if (mBall.get() != NULL)
	{
		float anOffset = anAngularVelocity * 10.0f;
		float anAngle = mAngle + SEXY_PI / 2.0f;
		mBall->SetPos(
			anX + (float) cos(anAngle) * anOffset,
			aY - (float) sin(anAngle) * anOffset);
	}
	mUnk0x120 = anAngularVelocity;

	UpdateCommon();

	if (mTargetAngle != mAngle)
	{
		float aTargetAngle = mTargetAngle;
		float aCurrentAngle = mAngle;
		if (aTargetAngle < SEXY_PI / 2.0f)
			aTargetAngle += SEXY_PI * 2.0f;
		if (aCurrentAngle < SEXY_PI / 2.0f)
			aCurrentAngle += SEXY_PI * 2.0f;

		float anAngleStep = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Gun.cpp24,385", 0.2f);
		if (aTargetAngle <= aCurrentAngle)
		{
			mAngle -= anAngleStep;
			if (aCurrentAngle - anAngleStep <= aTargetAngle)
				mAngle = mTargetAngle = NormalizeAngle(mTargetAngle);
		}
		else
		{
			mAngle += anAngleStep;
			if (aTargetAngle <= aCurrentAngle + anAngleStep)
				mAngle = mTargetAngle = NormalizeAngle(mTargetAngle);
		}
		CalcPoints();
	}

	if (mBoard->mLogicMgr->mUnk0x4 == 1)
		UpdateBouncyGuide();

	if (mUnk0x1bc != 0.0f &&
		(mBoard->mLogicMgr->mUnk0x4 != 2 || mBoard->mLogicMgr->mUnk0x8 > 150))
		mUnk0x1bc = 0.0f;
}

// FUNCTION: POPCAPGAME1 0x00486c10
int Gun::GetClass()
{
	return 7;
}

// FUNCTION: POPCAPGAME1 0x0047f5f0
void Gun::Clear()
{
	mBall = NULL;
	mGuidePoints.clear();
	mAngleHistory.clear();
	mUpdateCount = 0;
	mAngularVelocity = 1000.0f;
	mUnk0x194 = false;
	mUnk0x1a1 = false;
	mUnk0x1a2 = false;
	mUnk0x180 = true;
}

// STUB: POPCAPGAME1 0x0047f6e0
void Gun::SetDoBouncyGuide(bool param_1)
{
	mUnk0x194 = param_1;
	mGuidePoints.clear();
}
