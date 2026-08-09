#include "Gun.h"
#include "Ball.h"

using namespace Sexy;

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

// STUB: POPCAPGAME1 0x0047f590
void Gun::Draw(Graphics* param_1)
{
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

// STUB: POPCAPGAME1 0x0047bf30
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
	if (anElapsed < 1)
		anElapsed = 1;

	return aTotal / anElapsed;
}

// STUB: POPCAPGAME1 0x00483da0
void Gun::CalcPoints()
{
}

// STUB: POPCAPGAME1 0x00484500
void Gun::SetFireball(bool param_1)
{
	if (mBall.get() != NULL)
	{
		mBall->SetFireball(param_1);
		mUnk0x1a1 = param_1;
		CalcPoints();
	}
}

// STUB: POPCAPGAME1 0x004844c0
void Gun::Reload(Ball* param_1)
{
	mBall = param_1;
	mBall->mUnk0x140 = true;
	mUnk0x1a1 = false;
	CalcPoints();
}

// STUB: POPCAPGAME1 0x004843a0
void Gun::SetAngle(float param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x004882c0
void Gun::SyncState(DataSync& param_1)
{
}

// STUB: POPCAPGAME1 0x00482910
void Gun::UpdateBouncyGuide()
{
}

// STUB: POPCAPGAME1 0x00484530
void Gun::Fire(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00484120
void Gun::Update()
{
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
