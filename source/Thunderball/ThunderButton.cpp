#include "ThunderButton.h"

#include "ThunderCommon.h"
#include "ThunderballApp.h"
#include "WidgetMover.h"

#include <SexyAppFramework/DialogButton.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/SoundManager.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0049ba30
ThunderButton::ThunderButton(Image* theComponentImage, int theId, ButtonListener* theListener)
	: DialogButton(theComponentImage, theId, theListener)
{
	mOverAlphaSpeed = (double) 0x3fb47ae147ae147b;
	mOverAlphaFadeInSpeed = (double) 0x3fc999999999999a;

	mUnk0x144 = 0xfffffc18;
	mUnk0x138 = 0xffffffff;
	mUnk0x13c = 0xffffffff;
	mUnk0x148 = 1;
	mUnk0x15c = 0x11;
	mUnk0x150 = 0;
	mUnk0x14c = 0;
	mUnk0x151 = 0;
	// STRING: POPCAPGAME1 0x006004f8
	mUnk0x154 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp815,28", 60);
	mUnk0x158 = 0;
	mUnk0x159 = 0;

	mTranslateY = 0;
	mTranslateX = 0;
}

// FUNCTION: POPCAPGAME1 0x0049d440
void ThunderButton::Draw(Graphics* g)
{

	if (mUnk0x148 == 0) {
		return;
	}

	int dVar8 = mUnk0x15c;
	if (dVar8 != 0x11) {
		if (mIsDown && mIsOver) {
			dVar8 += 2;
		}
		else if (mIsOver || mIsDown) {
			dVar8 += 1;
		}
		SetButtonFontColor(dVar8);
	}
	if (mUnk0x14c == 0) {
	LABEL_3:
		DialogButton::Draw(g);
		if ((mUnk0x159) && (mIsDown) && (mIsOver)) {
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			g->SetColorizeImages(true);

			// STRING: POPCAPGAME1 0x00601230
			Color aColor(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp819,182", 0x404040));
			g->SetColor(aColor);

			DialogButton::Draw(g);
			g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
			g->SetColorizeImages(false);
		}
		return;
	}

	if (!mUnk0x151) {
		int iVar5 = (mUnk0x14c / (mUnk0x154 / 2)) % 2;
		if (iVar5 == 0) {
			goto LABEL_3;
		}
	}

	if (mIsDown || mIsOver) {
		goto LABEL_3;
	}

	// --- Smooth Pulse Logic ---
	// Defined HERE so it can reuse the memory slot of 'Color aColor' above.
	double local_14 = mOverAlpha;

	// Hard Blink "Off" Logic
	if (!mUnk0x151) {
		goto LABEL_BLINK_OFF;
	}

	// STRING: POPCAPGAME1 0x006012c0
	int iVar6 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp817,146", 0x1e);
	int iVar7 = iVar6 + mUnk0x154;
	int local_8 = mUnk0x154 / 2;
	int local_c = mUnk0x14c % iVar7;

	double dVar3;

	if (local_c > local_8) {
		if (local_c < (local_8 + iVar6)) {
			dVar3 = 1.0;
			goto LABEL_4;
		}
		else {
			local_8 = iVar7 - local_c;
		}
	}
	dVar3 = (double) local_c / (double) local_8;

LABEL_4:
	mOverAlpha = dVar3;
	mOverAlpha *= dVar3;

	// STRING: POPCAPGAME1 0x00601278
	mOverAlpha *= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp818,159", 0.7f);
	mIsOver = false;
	SwapRect(mDownRect, mOverRect);
	DialogButton::Draw(g);
	SwapRect(mDownRect, mOverRect);

	mOverAlpha = local_14;
	mIsOver = false;
	return;

LABEL_BLINK_OFF:
	mOverAlpha = 0.0;
	mIsOver = true;
	DialogButton::Draw(g);
	mOverAlpha = local_14;
	mIsOver = false;
}

// FUNCTION: POPCAPGAME1 0x00496d30
void ThunderButton::MouseDown(int x, int y, int theClickCount)
{
	if (-1 < mUnk0x13c) {
		GetThunderballApp()->PlaySample(mUnk0x13c);
	}
	DialogButton::MouseDown(x, y, theClickCount);
}

// FUNCTION: POPCAPGAME1 0x00496c50
void ThunderButton::MouseEnter()
{
	DialogButton::MouseEnter();

	if (mUnk0x158 != 0) {
		mUnk0x14c = 0;
	}

	if ((GetThunderballApp() != NULL) && (-1 < mUnk0x13c)) {
		// STRING: POPCAPGAME1 0x005fc230
		int iVar3 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp816,79", 30);
		if (iVar3 < GetThunderballApp()->mUpdateCount - mUnk0x144) {
			if (!GetThunderballApp()->mWidgetMover->IsMoving()) {
				SoundInstance* hoverSound = GetThunderballApp()->mSoundManager->GetSoundInstance(mUnk0x13c);
				if (hoverSound == NULL) {
					GetThunderballApp()->PlaySample(mUnk0x13c);
				}
				else {
					hoverSound->AdjustPitch(mUnk0x140);
					hoverSound->Play(0, 1);
				}
				mUnk0x144 = GetThunderballApp()->mUpdateCount;
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00496d70
void ThunderButton::MouseUp(int x, int y, int theClickCount)
{
	mUnk0x150 = theClickCount < 0;
	DialogButton::MouseUp(x, y, theClickCount);
}

// FUNCTION: POPCAPGAME1 0x00496da0
void ThunderButton::Update()
{
	DialogButton::Update();
	if (mUnk0x14c != 0 && GetThunderballApp()->mHasFocus) {
		mUnk0x14c--;
		MarkDirty();
	}
}

// FUNCTION: POPCAPGAME1 0x00496c40
void ThunderButton::StopBlink()
{
	mUnk0x14c = 0;
}

// FUNCTION: POPCAPGAME1 0x00496c00
void ThunderButton::Blink(int param_1, bool param_2)
{
	int dVar1 = mUnk0x154 * param_1 - 1;
	mUnk0x14c = dVar1;
	if (param_2 == 0) {
		mUnk0x14c = mUnk0x154 / 2 + dVar1;
	}
}

/*  if (local_8 <= local_c) {
	if (local_c < local_8 + iVar6) {
	  dVar3 = 1.0;
	  goto LAB_0049d53c;
	}
	local_c = iVar7 - local_c;
  }
  dVar3 = (double)local_c / (double)local_8;

  if (local_c <= local_8) {
	if (local_8 < local_c + iVar4) {
	  dVar2 = 1.0;
	  goto LAB_0040139f;
	}
	local_8 = iVar5 - local_8;
  }
  dVar2 = (double)local_c / (double)local_8;*/
