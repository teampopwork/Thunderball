#include "PegInfo.h"

#include "DataSync.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00476fd0
__declspec(noinline) void DataSync_SyncPegType(DataSync& param_1, PegType& param_2, PegType)
{
	int value = param_2;
	param_1.SyncByte(value);
	param_2 = (PegType)value;
}

// FUNCTION: POPCAPGAME1 0x004765f0
PegInfo::PegInfo()
{
	mUnk0x14 = false;
	mUnk0x16 = false;
	mUnk0x17 = false;
	mUnk0x18 = 0;
	mUnk0x20 = 0;
	mUnk0x24 = 0;
	mUnk0x1c = 0;
	mPegType = NORMAL;
	mUnk0x15 = true;
}

PegInfo::~PegInfo()
{
}

void PegInfo::Reset()
{
}

void PegInfo::SetHit(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00479560
void PegInfo::SyncState(DataSync& param_1)
{
	if (param_1.mReader != NULL) {
		mUnk0x18 = 0;
		mUnk0x24 = 0;
		mUnk0x20 = 0;
		mUnk0x1c = 0;
	}

	bool hasUnk0x18 = mUnk0x18 != 0;
	bool hasUnk0x20 = mUnk0x20 != 0;
	bool hasUnk0x24 = mUnk0x24 != 0;
	bool hasUnk0x1c = mUnk0x1c != 0;
	DataSync_SyncPegType(param_1, mPegType, NONE);
	param_1.SyncBoolBit(mUnk0x14);
	param_1.SyncBoolBit(mUnk0x15);
	param_1.SyncBoolBit(hasUnk0x18);
	param_1.SyncBoolBit(mUnk0x16);
	param_1.SyncBoolBit(hasUnk0x20);
	param_1.SyncBoolBit(hasUnk0x24);
	param_1.SyncBoolBit(mUnk0x17);
	param_1.SyncBoolBit(hasUnk0x1c);
	param_1.EndBit();

	if (hasUnk0x18) {
		param_1.SyncLong(mUnk0x18);
	}
	if (hasUnk0x20) {
		param_1.SyncLong(mUnk0x20);
	}
	if (hasUnk0x24) {
		param_1.SyncByte(mUnk0x24);
	}
	if (hasUnk0x1c) {
		param_1.SyncByte(mUnk0x1c);
	}
}

void PegInfo::DoFlash(int param_1)
{
}

void PegInfo::DoFlashBlink(int param_1)
{
}

void PegInfo::DrawBigPulse(Graphics* param_1, int param_2, float param_3, float param_4, int param_5, int param_6)
{
}

void PegInfo::DrawBrick(Brick* param_1, Graphics* param_2)
{
}

void PegInfo::DrawGlow(PhysObj* param_1, Graphics* param_2)
{
}

void PegInfo::DrawLight(PhysObj* param_1, Graphics* param_2)
{
}

void PegInfo::IncCrumble()
{
}

void PegInfo::Update(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0047ad10
void PegInfo::DrawBall(Ball* param_1, Graphics* param_2)
{
}

// FUNCTION: POPCAPGAME1 0x0047b800
bool PegInfo::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	if (param_1 == "peg_type") {
		if (param_2) {
			mPegType = (PegType)(int)GetEditValNum();
		}
		else {
			SetEditValNum(mPegType);
		}
		return true;
	}
	if (param_1 == "peg_variable") {
		return EditValSyncBool(mUnk0x15);
	}
	if (param_1 == "peg_crumble") {
		return EditValSyncBool(mUnk0x16);
	}
	return false;
}

void PegInfo::DrawColorblind(Graphics* param_1, PhysObj* param_2)
{
}
