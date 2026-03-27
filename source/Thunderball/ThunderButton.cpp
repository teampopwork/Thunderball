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
	mClickSound = 0xffffffff;
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
	if (!mUnk0x148) {
		return;
	}

	int colorIndex = mUnk0x15c;
	if (colorIndex != 0x11) {
		if (mIsDown && mIsOver) {
			colorIndex += 2;
		}
		else if (mIsOver || mIsDown) {
			colorIndex += 1;
		}

		SetButtonFontColor(colorIndex);
	}

	if (mUnk0x14c != 0) {
		bool doPulse = true;
		if (!mUnk0x151) {
			if ((mUnk0x14c / (mUnk0x154 / 2)) % 2 == 0) {
				doPulse = false;
			}
		}

		if (doPulse && !mIsDown && !mIsOver) {
			double oldAlpha = mOverAlpha;

			if (mUnk0x151) {
				int pulseTime =
					ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp817,146", 0x1e);
				int totalCycle = pulseTime + mUnk0x154;
				int halfCycle = mUnk0x154 / 2;
				int timeInCycle = mUnk0x14c % totalCycle;

				if (timeInCycle < halfCycle) {
					mOverAlpha = (double) timeInCycle / (double) halfCycle;
				}
				else if (timeInCycle < halfCycle + pulseTime) {
					mOverAlpha = 1.0;
				}
				else {
					mOverAlpha = (double) (totalCycle - timeInCycle) / (double) halfCycle;
				}

				mOverAlpha = mOverAlpha * mOverAlpha;
				mOverAlpha *= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp818,159", 0.7f);

				mIsOver = false;
				SwapRect(mDownRect, mOverRect);
				DialogButton::Draw(g);
				SwapRect(mDownRect, mOverRect);

				mOverAlpha = oldAlpha;
				mIsOver = false;
				return;
			}
			else {
				mOverAlpha = 0.0;
				mIsOver = true;
				DialogButton::Draw(g);
				mOverAlpha = oldAlpha;
				mIsOver = false;
				return;
			}
		}
	}

	DialogButton::Draw(g);

	if (mUnk0x159 && mIsDown && mIsOver) {
		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		g->SetColorizeImages(true);

		Color aColor(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp819,182", 0x404040));
		g->SetColor(aColor);

		DialogButton::Draw(g);
		g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		g->SetColorizeImages(false);
	}
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
