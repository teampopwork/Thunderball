#include "Mover.h"

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

// STUB: POPCAPGAME1 0x00478df0
Mover::~Mover()
{
	mPhysObj->Release();
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
float Mover::GetTimeTillPhase(int param_1, float param_2)
{
	if (mPause1 < 1) {
		if (0 < mTime) {
			return MyMod((int) ((float) mTime * param_2) - (param_1 + mOffset), mTime);
		}
	}
	else {
		if ((0 < mPause1) && (mTime + mPause2 + mPause1 < 1)) {
			return MyMod((int) (mPause1 - (param_1 + mOffset)), mTime);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004764f0
int Mover::GetMovePos(int param_1)
{
	int local_8;
	int local_c;

	if (0 < mPause1) {
		local_8 = mTime + mPause2 + mPause1;
		param_1 += mType;
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
		local_c = mTime;
		param_1 += mType;
		local_8 = mTime;
		param_1 += (int) (mPhase * local_c);
	}

	param_1 %= local_8;
	return param_1;
}

// STUB: POPCAPGAME1 0x00478ea0
void Mover::CalcPos(int param_1, float param_2)
{
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

	mPhysObj->Release();
}

// STUB: POPCAPGAME1 0x0047a9f0
void Mover::SyncState(DataSync* param_1)
{
}
