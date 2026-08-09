#include "Mover.h"

#include "DataSync.h"
#include "PhysObj.h"
#include "ThunderCommon.h"

#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/SmartPtr.h>
#include <math.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0047b430
Mover::Mover()
{
	InitDefaults();
}

// SYNTHETIC: POPCAPGAME1 0x0047a950
// Sexy::Mover::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00478df0
Mover::~Mover()
{
}

// FUNCTION: POPCAPGAME1 0x00476420
void Mover::Translate(float param_1, float param_2)
{
	mUnk0x54 += param_1;
	mUnk0x58 += param_2;
	mUnk0x5c += param_1;
	mUnk0x60 += param_2;
}

// FUNCTION: POPCAPGAME1 0x00478e70
void Mover::SetPos(float param_1, float param_2)
{
	Translate(param_1 - mUnk0x5c, param_2 - mUnk0x60);
}

// FUNCTION: POPCAPGAME1 0x00476460
int Mover::GetTimeTillPhase(int param_1, float param_2)
{
	if (mPause1 > 0) {
		int aTotalTime = mTime + mPause2 + mPause1;
		if (mTime < 1 || aTotalTime < 1)
			return 0;

		int aTargetTime = (int) (mTime * param_2);
		if ((float) mPhase1 < param_2)
			aTargetTime += mPause1;
		if ((float) mPhase2 < param_2)
			aTargetTime += mPause2;
		return MyMod(aTargetTime - (param_1 + mOffset), aTotalTime);
	}

	if (mTime < 1)
		return 0;
	return MyMod((int) (mTime * param_2) - (param_1 + mOffset), mTime);
}

// FUNCTION: POPCAPGAME1 0x004764f0
float Mover::GetMovePos(int param_1)
{
	int local_8;

	if (0 < mPause1) {
		local_8 = mTime + mPause2 + mPause1;
		param_1 += mOffset;
		if (0 < local_8) {
			int aVal1 = (mTime * mPhase1) / 100;
			int aVal2 = ((mPhase2 - mPhase1) * mTime) / 100 + mPause1 + aVal1;
			int aVal3 = ((int) (mPostDelayPhase * local_8) + param_1) % local_8;

			if (aVal1 < aVal3) {
				if (aVal3 <= mPause1 + aVal1) {
					param_1 = aVal1;
				}
				else {
					if (aVal2 < aVal3) {
						if (aVal3 <= mPause2 + aVal2) {
							param_1 = aVal2 - mPause1;
						}
						else {
							aVal3 -= mPause2;
							param_1 = aVal3 - mPause1;
						}
					}
					else {
						param_1 = aVal3 - mPause1;
					}
				}
			}
			else {
				param_1 = aVal3;
			}
		}

		local_8 = mTime;
		param_1 += (int) (mPhase * local_8);
	}
	else {
		param_1 += mOffset;
		local_8 = mTime;
		param_1 += (int) (mPhase * local_8);
	}

	return (float) (param_1 % local_8) / local_8;
}

// FUNCTION: POPCAPGAME1 0x00478ea0
void Mover::CalcPos(int param_1, float param_2)
{
	if (mPhysObj != NULL) {
		Translate(mPhysObj->mUnk0x54 - mUnk0x4c, mPhysObj->mUnk0x58 - mUnk0x50);
		mUnk0x4c = mPhysObj->mUnk0x54;
		mUnk0x50 = mPhysObj->mUnk0x58;
	}

	if (mType == 0 || mTime < 1) {
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60;
		mUnk0x64 = mRotation;
		return;
	}

	int aMoveType = mType < 0 ? -mType : mType;
	int aDirection = mType < 0 ? -1 : 1;
	float aPhase = GetMovePos(param_1) + param_2 / mTime;
	float anAngle = (float) (aPhase * (SEXY_PI * 2.0) * aDirection);
	float aRadiusX = (float) mRadius;
	float aRadiusY = mRadius2 == 0 ? aRadiusX : (float) mRadius2;

	switch (aMoveType) {
	case 1:
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60 - (float) sin(anAngle) * aRadiusY;
		mUnk0x64 = mRotation;
		break;
	case 2:
		mUnk0x54 = mUnk0x5c + (float) cos(anAngle) * aRadiusX;
		mUnk0x58 = mUnk0x60;
		mUnk0x64 = mRotation;
		break;
	case 3:
		mUnk0x54 = mUnk0x5c + (float) cos(anAngle) * aRadiusX;
		mUnk0x58 = mUnk0x60 - (float) sin(anAngle) * aRadiusY;
		mUnk0x64 = mRotation;
		break;
	case 4:
		mUnk0x54 = mUnk0x5c + (float) cos(anAngle) * aRadiusX;
		mUnk0x58 = mUnk0x60 - (float) sin(anAngle * 2.0f) * aRadiusY * 0.5f;
		mUnk0x64 = mRotation;
		break;
	case 5:
		mUnk0x54 = mUnk0x5c + (float) sin(anAngle * 2.0f) * aRadiusX;
		mUnk0x58 = mUnk0x60 - (float) sin(anAngle) * aRadiusY;
		mUnk0x64 = mRotation;
		break;
	case 6:
	case 7: {
		float aMaxAngle = mMaxAngle == 0.0f ? SEXY_PI : mMaxAngle;
		float aSwingAngle = (float) ((sin(aPhase * (SEXY_PI * 2.0) - SEXY_PI / 2.0) + 1.0) * aMaxAngle * 0.5);
		mUnk0x54 = mUnk0x5c + (float) cos(aSwingAngle) * aRadiusX;
		if (aMoveType == 6)
			mUnk0x58 = mUnk0x60 - (float) sin(aSwingAngle) * aRadiusY;
		else
			mUnk0x58 = mUnk0x60 - (float) cos(aSwingAngle) * aRadiusY;
		mUnk0x64 = mRotation;
		break;
	}
	case 8:
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60;
		mUnk0x64 = mRotation + (mMaxAngle == 0.0f ? anAngle : mMaxAngle * aDirection);
		break;
	case 9: {
		float aMaxAngle = mMaxAngle == 0.0f ? SEXY_PI : mMaxAngle;
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60;
		mUnk0x64 = mRotation + ((float) sin(aPhase * (SEXY_PI * 2.0)) * aMaxAngle + mMoveRotation) * aDirection;
		break;
	}
	case 11: {
		float aFraction = aPhase - (int) aPhase;
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60 - aFraction * aRadiusY * aDirection;
		mUnk0x64 = mRotation;
		break;
	}
	case 12: {
		float aFraction = aPhase - (int) aPhase;
		mUnk0x54 = mUnk0x5c + aFraction * aRadiusX * aDirection;
		mUnk0x58 = mUnk0x60;
		mUnk0x64 = mRotation;
		break;
	}
	case 13:
		mUnk0x54 = mUnk0x5c + (float) cos(anAngle) * aRadiusX;
		mUnk0x58 = mUnk0x60 - (float) sin(anAngle) * aRadiusY;
		if (mRadius == 0 || mRadius2 == 0) {
			mUnk0x64 = mRotation + anAngle;
		}
		else {
			float aTangentAngle = anAngle + SEXY_PI / 2.0f;
			float aTangentX = (float) cos(aTangentAngle) * aRadiusX;
			float aTangentY = -(float) sin(aTangentAngle) * aRadiusY;
			mUnk0x64 = mRotation + (float) atan2(aTangentY, aTangentX);
		}
		break;
	default:
		break;
	}

	if (mMoveRotation != 0.0f)
		RotateXY(&mUnk0x54, &mUnk0x58, mUnk0x5c, mUnk0x60, mMoveRotation);
}

// FUNCTION: POPCAPGAME1 0x00479450
void Mover::DrawMovement(Graphics* g)
{
	int local_8 = mType;
	if (local_8 <= 0 || mTime <= 0) {
		return;
	}

	float oldUnk0x54 = mUnk0x54;
	float oldUnk0x58 = mUnk0x58;
	int oldUnk0x2c = mPause1;
	int pointsX[10];
	int pointsY[10];

	mPause1 = 0;

	for (int i = 0; i < 10; ++i) {
		CalcPos((mTime * i) / 10, 0.0f);
		pointsX[i] = (int) mUnk0x54;
		pointsY[i] = (int) mUnk0x58;
	}

	for (int i = 0; i < 9; ++i) {
		g->DrawLine(pointsX[i], pointsY[i], pointsX[i + 1], pointsY[i + 1]);
	}

	mUnk0x54 = oldUnk0x54;
	mUnk0x58 = oldUnk0x58;
	mPause1 = oldUnk0x2c;
}

// FUNCTION: POPCAPGAME1 0x0047b490
bool Mover::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	if (param_1.compare("mover_type") == 0) {
		EditValSyncNum(mType);
		return true;
	}
	if (param_1.compare("mover_radius") == 0) {
		EditValSyncNum(mRadius);
		return true;
	}
	if (param_1.compare("mover_time") == 0) {
		EditValSyncNum(mTime);
		return true;
	}
	if (param_1.compare("mover_radius2") == 0) {
		EditValSyncNum(mRadius2);
		return true;
	}
	if (param_1.compare("mover_offset") == 0) {
		EditValSyncNum(mOffset);
		return true;
	}
	if (param_1.compare("mover_pause1") == 0) {
		EditValSyncNum(mPause1);
		return true;
	}
	if (param_1.compare("mover_phase1") == 0) {
		EditValSyncNum(mPhase1);
		return true;
	}
	if (param_1.compare("mover_pause2") == 0) {
		EditValSyncNum(mPause2);
		return true;
	}
	if (param_1.compare("mover_phase2") == 0) {
		EditValSyncNum(mPhase2);
		return true;
	}
	if (param_1.compare("mover_phase") == 0) {
		if (param_2) {
			float aValue = (float) GetEditValNum();
			aValue = fmodf(aValue, 100.0f);
			mPhase = aValue / 100.0f;
		}
		else {
			SetEditValNum((double) (mPhase * 100.0f));
		}
		return true;
	}
	if (param_1.compare("mover_postdelayphase") == 0) {
		if (param_2) {
			float aValue = (float) GetEditValNum() / 100.0f;
			if (aValue < -1.0f) {
				aValue = -1.0f;
			}
			else if (1.0f < aValue) {
				aValue = 1.0f;
			}
			mPostDelayPhase = aValue;
		}
		else {
			SetEditValNum((double) (mPostDelayPhase * 100.0f));
		}
		return true;
	}
	if (param_1.compare("mover_moverotation") == 0) {
		if (param_2) {
			mMoveRotation = (float) ((float) GetEditValNum() * 3.1415927 / 180.0);
		}
		else {
			SetEditValNum((double) (mMoveRotation * 180.0 / 3.1415927));
		}
		return true;
	}
	if (param_1.compare("mover_maxangle") == 0) {
		if (param_2) {
			mMaxAngle = (float) ((float) GetEditValNum() * 3.1415927 / 180.0);
		}
		else {
			SetEditValNum((double) (mMaxAngle * 180.0 / 3.1415927));
		}
		return true;
	}
	if (param_1.compare("mover_rotation") == 0) {
		if (param_2) {
			mRotation = (float) ((float) GetEditValNum() * 3.1415927 / 180.0);
		}
		else {
			SetEditValNum((double) (mRotation * 180.0 / 3.1415927));
		}
		return true;
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x0047a980
void Mover::InitDefaults()
{
	mPhase = 0;
	mRotation = 0;
	mPostDelayPhase = 0;
	mType = 0;
	mMaxAngle = 0;
	mOffset = 0;
	mUnk0x64 = 0;
	mRadius = 0;
	mMoveRotation = 0;
	mTime = 200;
	mUnk0x58 = 0.0;
	mRadius2 = 0;
	mUnk0x54 = 0.0;
	mPause1 = 0;
	mUnk0x60 = 0.0;
	mPhase1 = 0;
	mUnk0x5c = 0.0;
	mPause2 = 0;
	mPhase2 = 0;

	mPhysObj = NULL;
}

// FUNCTION: POPCAPGAME1 0x0047a9f0
void Mover::SyncState(DataSync& theSync)
{
	if (theSync.mReader != NULL)
		InitDefaults();

	theSync.SyncSByte(mType);
	theSync.SyncFloat(mUnk0x5c);
	theSync.SyncFloat(mUnk0x60);
	theSync.SyncShort(mTime);

	bool hasOffset = mOffset != 0;
	bool hasRadius = mRadius != 0;
	bool hasPhase = mPhase != 0.0f;
	bool hasMoveRotation = mMoveRotation != 0.0f;
	bool hasRadius2 = mRadius2 != 0;
	bool hasPause1 = mPause1 != 0;
	bool hasPause2 = mPause2 != 0;
	bool hasPhase1 = mPhase1 != 0;
	bool hasPhase2 = mPhase2 != 0;
	bool hasPostDelayPhase = mPostDelayPhase != 0.0f;
	bool hasMaxAngle = mMaxAngle != 0.0f;
	bool hasCurrentRotation = mUnk0x64 != 0.0f;
	bool hasParent = mPhysObj != NULL;
	bool hasCurrentPos = mUnk0x54 != mUnk0x5c || mUnk0x58 != mUnk0x60;
	bool hasRotation = mRotation != 0.0f;

	theSync.SyncBoolBit(hasOffset);
	theSync.SyncBoolBit(hasRadius);
	theSync.SyncBoolBit(hasPhase);
	theSync.SyncBoolBit(hasMoveRotation);
	theSync.SyncBoolBit(hasRadius2);
	theSync.SyncBoolBit(hasPause1);
	theSync.SyncBoolBit(hasPause2);
	theSync.SyncBoolBit(hasPhase1);
	theSync.EndBit();

	theSync.SyncBoolBit(hasPhase2);
	theSync.SyncBoolBit(hasPostDelayPhase);
	theSync.SyncBoolBit(hasMaxAngle);
	theSync.SyncBoolBit(hasCurrentRotation);
	theSync.SyncBoolBit(hasParent);
	theSync.SyncBoolBit(hasCurrentPos);
	theSync.SyncBoolBit(hasRotation);
	theSync.EndBit();

	if (hasOffset)
		theSync.SyncSShort(mOffset);
	if (hasRadius)
		theSync.SyncSShort(mRadius);
	if (hasPhase)
		theSync.SyncFloat(mPhase);
	if (hasMoveRotation)
		theSync.SyncFloat(mMoveRotation);
	if (hasRadius2)
		theSync.SyncSShort(mRadius2);
	if (hasPause1)
		theSync.SyncShort(mPause1);
	if (hasPause2)
		theSync.SyncShort(mPause2);
	if (hasPhase1)
		theSync.SyncSByte(mPhase1);
	if (hasPhase2)
		theSync.SyncSByte(mPhase2);
	if (hasPostDelayPhase)
		theSync.SyncFloat(mPostDelayPhase);
	if (hasMaxAngle)
		theSync.SyncFloat(mMaxAngle);
	if (hasCurrentRotation)
		theSync.SyncFloat(mUnk0x64);
	if (hasRotation)
		theSync.SyncFloat(mRotation);
	if (hasParent) {
		theSync.SyncFloat(mUnk0x4c);
		theSync.SyncFloat(mUnk0x50);
		DataSync_SyncSmartPtr<Mover>(theSync, mPhysObj);
	}
	if (hasCurrentPos) {
		theSync.SyncFloat(mUnk0x54);
		theSync.SyncFloat(mUnk0x58);
	}
	else {
		mUnk0x54 = mUnk0x5c;
		mUnk0x58 = mUnk0x60;
	}
}
