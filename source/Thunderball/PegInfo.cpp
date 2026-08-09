#include "PegInfo.h"

#include "Ball.h"
#include "BlendedImage.h"
#include "DataSync.h"
#include "Res.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Color.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00476fd0
__declspec(noinline) void DataSync_SyncPegType(DataSync& param_1, PegType& param_2, PegType)
{
	int value = param_2;
	param_1.SyncByte(value);
	param_2 = (PegType)value;
}

// FUNCTION: POPCAPGAME1 0x004bc420
__declspec(noinline) float GetPulsePercent(int param_1, int param_2, int param_3)
{
	param_1 %= param_2 * 2 + param_3;
	if (param_1 < param_3) {
		return 0.0f;
	}

	param_1 -= param_3;
	if (param_1 > param_2) {
		param_1 = param_2 * 2 - param_1;
	}
	return (float)param_1 / (float)param_2;
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

// FUNCTION: POPCAPGAME1 0x00476640
void PegInfo::Reset()
{
	mUnk0x18 = 0;
	mUnk0x20 = 0;
	mUnk0x24 = 0;
	mUnk0x1c = 0;
}

// FUNCTION: POPCAPGAME1 0x00476650
void PegInfo::SetHit(bool param_1)
{
	mUnk0x14 = param_1;
	mUnk0x18 = param_1 != false;
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

// FUNCTION: POPCAPGAME1 0x00476670
void PegInfo::DoFlash(int param_1)
{
	mUnk0x20 = 1;
	mUnk0x24 = param_1;
}

// FUNCTION: POPCAPGAME1 0x00476690
void PegInfo::DoFlashBlink(int param_1)
{
	mUnk0x20 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\PegInfo.cpp61,152", 50) * param_1 - 1;
	mUnk0x24 = 10;
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

// FUNCTION: POPCAPGAME1 0x004769b0
void PegInfo::IncCrumble()
{
	if (mUnk0x1c < 3) {
		mUnk0x1c++;
	}
}

// FUNCTION: POPCAPGAME1 0x00479680
void PegInfo::Update(PhysObj* param_1)
{
	if (mUnk0x18 != 0) {
		mUnk0x18++;
		if (mUnk0x16 && mUnk0x1c >= 3 && mUnk0x1c < 100 && ++mUnk0x1c == 100) {
			param_1->SetActive(false);
		}
	}

	if (mUnk0x20 != 0) {
		if (mUnk0x24 == 10) {
			if (--mUnk0x20 <= 0) {
				mUnk0x24 = 0;
				mUnk0x20 = 0;
			}
		}
		else {
			mUnk0x20++;
			if (mUnk0x20 > 100) {
				mUnk0x20 = 0;
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0047ad10
void PegInfo::DrawBall(Ball* param_1, Graphics* param_2)
{
	Image* image = mColorblind ? IMAGE_BALLPEGCB : IMAGE_BALLPEG;
	int cel = mPegType - 1;
	if (mUnk0x14) {
		cel += 4;
	}

	float x = param_1->mUnk0xec - param_1->mUnk0x13c;
	float y = param_1->mUnk0xf0 - param_1->mUnk0x13c;

	if (!param_2->mIs3D) {
		if (param_1->mMover != NULL) {
			gBallPegImage[cel]->Draw(param_2, x - 1.0f, y - 1.0f);
		}
		else {
			Rect srcRect = image->GetCelRect(0, cel);
			srcRect.mWidth -= 2;
			srcRect.mHeight -= 2;
			srcRect.mX++;
			srcRect.mY++;
			param_2->DrawImage(image, (int)x, (int)y, srcRect);
		}
	}
	else {
		Rect srcRect = image->GetCelRect(0, cel);
		if (param_1->mMover != NULL) {
			param_2->DrawImageF(image, x - 1.0f, y - 1.0f, srcRect);
		}
		else {
			srcRect.mWidth -= 2;
			srcRect.mHeight -= 2;
			srcRect.mX++;
			srcRect.mY++;
			param_2->DrawImage(image, (int)x, (int)y, srcRect);
		}
	}

	if (mUnk0x24 == 10 && mUnk0x20 != 0 && !mUnk0x14) {
		mUnk0x14 = true;
		param_2->SetColorizeImages(true);
		float pulse = GetPulsePercent(
			mUnk0x20,
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\PegInfo.cpp66,258", 20),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\PegInfo.cpp67,258", 10)
		);
		int alpha = (int)(
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\PegInfo.cpp68,259", 0) +
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\PegInfo.cpp69,259", 200) * pulse
		);
		param_2->SetColor(Color(0xffffff, alpha));
		param_2->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		param_2->SetColorizeImages(true);
		DrawBall(param_1, param_2);
		param_2->SetColorizeImages(false);
		param_2->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		mUnk0x14 = false;
	}
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
