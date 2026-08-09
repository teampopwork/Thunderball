#include "Line.h"
#include "DataSync.h"

#include <SexyAppFramework/SexyVector.h>

#include <math.h>

using namespace Sexy;

// GLOBAL: POPCAPGAME1 0x00650a54
bool Sexy::gCheckLineCollision = false;

// FUNCTION: POPCAPGAME1 0x00475e10
static int GetRectOutCode(Rect* param_1, float param_2, float param_3)
{
	int aCode = param_2 < param_1->mX;
	if (param_3 < param_1->mY)
		aCode |= 2;
	if (param_1->mX + param_1->mWidth < param_2)
		aCode |= 4;
	if (param_1->mY + param_1->mHeight < param_3)
		aCode |= 8;
	return aCode;
}

// FUNCTION: POPCAPGAME1 0x00475e90
static void GetProjectionRange(
	SexyVector2* param_1,
	int param_2,
	SexyVector2* param_3,
	float* param_4,
	float* param_5)
{
	*param_4 = 1.0e10f;
	*param_5 = -1.0e10f;
	for (int i = 0; i < param_2; i++)
	{
		float aProjection = param_1[i].x * param_3->x + param_1[i].y * param_3->y;
		if (aProjection < *param_4)
			*param_4 = aProjection;
		if (*param_5 < aProjection)
			*param_5 = aProjection;
	}
}

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

// FUNCTION: POPCAPGAME1 0x00476010
bool Line::IsPartlyInsideRect(Rect* theRect)
{
	SexyVector2 aLinePoints[2] = {
		SexyVector2(mUnk0xec, mUnk0xf4),
		SexyVector2(mUnk0xf0, mUnk0xf8)
	};

	int aStartCode = GetRectOutCode(theRect, aLinePoints[0].x, aLinePoints[0].y);
	int anEndCode = GetRectOutCode(theRect, aLinePoints[1].x, aLinePoints[1].y);
	if (aStartCode != 0 && anEndCode != 0)
	{
		if ((aStartCode & anEndCode) != 0)
			return false;

		SexyVector2 aRectPoints[4] = {
			SexyVector2((float) theRect->mX, (float) theRect->mY),
			SexyVector2((float) (theRect->mX + theRect->mWidth), (float) theRect->mY),
			SexyVector2((float) theRect->mX, (float) (theRect->mY + theRect->mHeight)),
			SexyVector2((float) (theRect->mX + theRect->mWidth), (float) (theRect->mY + theRect->mHeight))
		};
		SexyVector2 anAxes[3] = {
			SexyVector2(1.0f, 0.0f),
			SexyVector2(0.0f, 1.0f),
			SexyVector2(aLinePoints[0].y - aLinePoints[1].y, aLinePoints[1].x - aLinePoints[0].x)
		};

		for (int i = 0; i < 3; i++)
		{
			float aRectMin;
			float aRectMax;
			float aLineMin;
			float aLineMax;
			GetProjectionRange(aRectPoints, 4, &anAxes[i], &aRectMin, &aRectMax);
			GetProjectionRange(aLinePoints, 2, &anAxes[i], &aLineMin, &aLineMax);
			if (aLineMax < aRectMin || aRectMax < aLineMin)
				return false;
		}
	}
	return true;
}

// FUNCTION: POPCAPGAME1 0x00476380
bool Line::EditIntersects(Rect* theRect)
{
	return IsPartlyInsideRect(theRect);
}

// FUNCTION: POPCAPGAME1 0x00475660
void Line::CalcEdgeHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
	SexyVector2 aVelocity(mUnk0xfc, mUnk0x100);
	*param_2 = *param_1 * param_1->Dot(aVelocity);
}

void Line::CalcVertexHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
}

// FUNCTION: POPCAPGAME1 0x00475bd0
int Line::CircleIntersect(float param_1, float param_2, float param_3, SexyVector2* param_4, SexyVector2* param_5)
{
	SexyVector2 aStart(mUnk0xec - param_1, mUnk0xf4 - param_2);
	SexyVector2 aDelta(mUnk0xf0 - mUnk0xec, mUnk0xf8 - mUnk0xf4);
	float a = aDelta.Dot(aDelta);
	float b = 2.0f * aStart.Dot(aDelta);
	float c = aStart.Dot(aStart) - param_3 * param_3;
	param_3 = b * b - 4.0f * a * c;
	if (param_3 < 0.0f)
		return 0;

	param_3 = sqrtf(param_3);
	float aFirstTime = (-b + param_3) / (2.0f * a);
	float aSecondTime = (-b - param_3) / (2.0f * a);
	aStart += SexyVector2(param_1, param_2);

	int aResult = 0;
	if (aFirstTime >= 0.0f)
	{
		if (aFirstTime <= 1.0f)
		{
			if (param_4 != NULL)
				*param_4 = aStart + aDelta * aFirstTime;
			aResult++;
		}
	}

	if (aSecondTime >= 0.0f)
	{
		if (aSecondTime <= 1.0f)
		{
			if (aResult == 0)
			{
				if (param_4 != NULL)
					*param_4 = aStart + aDelta * aSecondTime;
			}
			else if (param_5 != NULL)
			{
				*param_5 = aStart + aDelta * aSecondTime;
			}
			aResult++;
		}
	}

	return aResult;
}

// FUNCTION: POPCAPGAME1 0x00475890
bool Line::CheckEdgeTimeCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	SexyVector2* hitPoint,
	SexyVector2* hitNormal,
	SexyVector2* hitVelocity,
	float* hitTime
)
{
	SexyVector2 aNormal(mUnk0x104, mUnk0x108);
	float anOffset = mUnk0x10c;
	if (!mUnk0x111 && aNormal.Dot(*param_1 - SexyVector2(mUnk0xec, mUnk0xf4)) < 0.0f)
	{
		aNormal *= -1.0f;
		anOffset *= -1.0f;
	}

	float aSpeed = aNormal.Dot(*param_2);
	if (aSpeed > 0.2f)
		return false;

	if (aSpeed == 0.0f)
	{
		if (!gCheckLineCollision || aNormal.y != 0.0f)
			return false;

		SexyVector2 anEdgePoint = *param_1 - aNormal * param_3;
		bool isOnEdge;
		if (!mUnk0x110)
			isOnEdge = mUnk0x14 <= anEdgePoint.x && anEdgePoint.x <= mUnk0x1c;
		else
			isOnEdge = mUnk0x18 <= anEdgePoint.y && anEdgePoint.y <= mUnk0x20;

		if (!isOnEdge || param_3 < fabs(param_1->Dot(aNormal) + anOffset))
			return false;

		*hitTime = 0.0f;
		*hitPoint = *param_1;
		*hitNormal = aNormal;
		hitVelocity->x = 0.0f;
		hitVelocity->y = 0.0f;
		gCheckLineCollision = false;
		return true;
	}

	float aTime = ((param_3 - 0.01f) - anOffset - param_1->Dot(aNormal)) / aSpeed;
	if (aTime < 0.0f || *hitTime <= aTime)
		return false;

	SexyVector2 aCenter = *param_1 + *param_2 * aTime;
	SexyVector2 anEdgePoint = aCenter - aNormal * param_3;
	bool isOnEdge;
	if (!mUnk0x110)
		isOnEdge = mUnk0x14 <= anEdgePoint.x && anEdgePoint.x <= mUnk0x1c;
	else
		isOnEdge = mUnk0x18 <= anEdgePoint.y && anEdgePoint.y <= mUnk0x20;
	if (!isOnEdge)
		return false;

	*hitTime = aTime;
	*hitPoint = aCenter + aNormal * 0.01f;
	*hitNormal = aNormal;
	CalcEdgeHitVelocity(hitNormal, hitVelocity);
	return true;
}

// FUNCTION: POPCAPGAME1 0x004756c0
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
	SexyVector2 aDelta = *param_1 - SexyVector2(param_6, param_7);
	param_3 -= 0.01;
	float a = param_2->Dot(*param_2);
	float b = 2.0f * aDelta.Dot(*param_2);
	float c = aDelta.Dot(aDelta) - param_3 * param_3;
	param_3 = b * b - 4.0f * a * c;
	if (param_3 < 0.0f)
		return false;

	param_3 = sqrtf(param_3);
	param_3 = (-b - param_3) / (2.0f * a);
	if (0.0f <= param_3)
	{
		if (param_3 < *param_4)
		{
			param_3 -= 0.01 / param_2->Magnitude();
			SexyVector2 aHit = *param_1 + *param_2 * param_3;
			*param_5 = aHit;
			if (param_3 <= 0.0f)
				param_3 = 0.0f;
			*param_4 = param_3;
			aDelta = *param_5 - SexyVector2(param_6, param_7);
			*param_8 = aDelta.Normalize();
			CalcEdgeHitVelocity(param_8, param_9);
			return true;
		}
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x00478500
bool Line::CheckPenetration(
	SexyVector2* param_1,
	float param_2,
	SexyVector2* param_3,
	SexyVector2* param_4,
	SexyVector2* param_5
)
{
	float anAdjustedRadius = param_2 - 0.01;
	float aPlaneDistance = param_1->Dot(SexyVector2(mUnk0x104, mUnk0x108)) + mUnk0x10c;
	float anAbsDistance = fabs(aPlaneDistance);
	if (anAdjustedRadius < anAbsDistance)
		return false;

	SexyVector2 anIntersection(0.0f, 0.0f);
	if (!mUnk0x110)
	{
		if (param_1->x + param_2 < mUnk0x14)
			return false;
		if (mUnk0x1c < param_1->x - param_2)
			return false;
	}
	else
	{
		if (param_2 + param_1->y < mUnk0x18)
			return false;
		if (mUnk0x20 < param_1->y - param_2)
			return false;
	}

	int anIntersectionCount = CircleIntersect(
		param_1->x, param_1->y, anAdjustedRadius, &anIntersection, NULL);
	if (anIntersectionCount == 0)
		return false;

	if (anIntersectionCount == 1)
	{
		float aStartDx = mUnk0xec - param_1->x;
		float aStartDy = mUnk0xf4 - param_1->y;
		float anEndDx = mUnk0xf0 - param_1->x;
		float anEndDy = mUnk0xf8 - param_1->y;
		SexyVector2 aVertex;
		SexyVector2 aPush;
		if (anEndDx * anEndDx + anEndDy * anEndDy <=
			aStartDx * aStartDx + aStartDy * aStartDy)
		{
			aVertex = SexyVector2(mUnk0xf0, mUnk0xf8);
			aPush = aVertex - anIntersection;
			if (aPush.x == 0.0f && aPush.y == 0.0f)
				aPush = SexyVector2(mUnk0xf0 - mUnk0xec, mUnk0xf8 - mUnk0xf4).Normalize() * 0.01f;
		}
		else
		{
			aVertex = SexyVector2(mUnk0xec, mUnk0xf4);
			aPush = aVertex - anIntersection;
			if (aPush.x == 0.0f && aPush.y == 0.0f)
				aPush = SexyVector2(mUnk0xec - mUnk0xf0, mUnk0xf4 - mUnk0xf8).Normalize() * 0.01f;
		}

		*param_3 = *param_1 + aPush;
		*param_4 = (*param_3 - aVertex).Normalize();
		*param_3 += *param_4 * 0.01f;
		CalcEdgeHitVelocity(param_4, param_5);
		return true;
	}

	*param_4 = SexyVector2(mUnk0x104, mUnk0x108);
	if (!mUnk0x111 && aPlaneDistance < 0.0f)
	{
		*param_4 *= -1.0f;
		aPlaneDistance *= -1.0f;
	}
	*param_3 = *param_1 + *param_4 * (param_2 - aPlaneDistance);
	CalcEdgeHitVelocity(param_4, param_5);
	return true;
}

// FUNCTION: POPCAPGAME1 0x00478940
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
	if (mUnk0x14 - 20.0f <= param_1->x + param_3 &&
		param_1->x - param_3 <= mUnk0x1c + 20.0f &&
		mUnk0x18 - 20.0f <= param_1->y + param_3 &&
		param_1->y - param_3 <= mUnk0x20 + 20.0f)
	{
		if (CheckPenetration(param_1, param_3, param_5, param_6, param_7))
		{
			*param_4 = 0.0f;
			return true;
		}

		bool aResult = CheckEdgeTimeCollision(
			param_1, param_2, param_3, param_5, param_6, param_7, param_4);
		if (CheckVertexTimeCollision(
			param_1, param_2, param_3, param_4, param_5,
			mUnk0xec, mUnk0xf4, param_6, param_7))
		{
			aResult = true;
		}
		if (param_8 && CheckVertexTimeCollision(
			param_1, param_2, param_3, param_4, param_5,
			mUnk0xf0, mUnk0xf8, param_6, param_7))
		{
			aResult = true;
		}
		return aResult;
	}
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

