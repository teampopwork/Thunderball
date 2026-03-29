#include "ThunderCheckbox.h"

#include "Res.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Rect.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0049e7c0
ThunderCheckbox::ThunderCheckbox(
	Image* theUncheckedImage,
	Image* theCheckedImage,
	int theId,
	CheckboxListener* theCheckboxListener
)
	: Checkbox(theUncheckedImage, theCheckedImage, theId, theCheckboxListener)
{
	mUncheckedHilightRect = Rect(0, 0, 0, 0);
	mCheckedHilightRect = Rect(0, 0, 0, 0);
	mUnk0x110 = 0;
	mUnk0x10c = 0xffffffff;
	Font* dVar1 = FONT_BUTTON;
	mUnk0x140 = 0;
	mUnk0x118 = 0;
	mUnk0x148 = (double) 0x3fb47ae147ae147b;
	mUnk0x114 = 0;
	mUnk0x11c = 0;
	mUnk0x150 = (double) 0x3fc999999999999a;
	mUnk0xec = dVar1;
}

// FUNCTION: POPCAPGAME1 0x0049ecb0
ThunderCheckbox::~ThunderCheckbox()
{
}

// FUNCTION: POPCAPGAME1 0x0049bb10
void ThunderCheckbox::Draw(Graphics* g)
{
	Rect aDestRect(0, 0, mWidth, mHeight);

	int aFontColorIndex;
	if (mUnk0x11c == 1) {
		if (mChecked) {
			aFontColorIndex = 0x10;
		}
		else {
			if (mIsDown) {
				if (mIsOver) {
					aFontColorIndex = 0x10;
				}
				else {
					aFontColorIndex = 0xf;
				}
			}
			else {
				if (mIsOver) {
					aFontColorIndex = 0xf;
				}
				else {
					aFontColorIndex = 0xd;
				}
			}
		}
	}
	else {
		if (mIsOver) {
			aFontColorIndex = 0xe;
		}
		else {
			aFontColorIndex = 0xd;
		}
	}

	SetButtonFontColor(aFontColorIndex);

	Rect pSrcRect;
	Rect pHilightRect;
	if (!mChecked) {
		pSrcRect = mUncheckedRect;
		pHilightRect = mUncheckedHilightRect;
	}
	else {
		pSrcRect = mCheckedRect;
		pHilightRect = mCheckedHilightRect;
	}

	if (mUnk0x140 <= 0.0 || pHilightRect.mWidth < 1) {
		Rect aFinalSrcRect = pSrcRect;
		if (mIsOver && pHilightRect.mWidth >= 1) {
			aFinalSrcRect = pHilightRect;
		}

		g->DrawImageBox(aFinalSrcRect, aDestRect, mUncheckedImage);
	}
	else {
		if (mUnk0x140 < 1.0) {
			g->DrawImageBox(pSrcRect, aDestRect, mUncheckedImage);
		}

		g->SetColorizeImages(true);
		int anAlpha = (int) (mUnk0x140 * 255.0);
		g->SetColor(Color(255, 255, 255, anAlpha));
		g->DrawImageBox(pHilightRect, aDestRect, mUncheckedImage);
		g->SetColorizeImages(false);
	}

	g->SetFont(mUnk0xec);
	int aLabelWidth = mUnk0xec->StringWidth(mLabel);
	int aLabelX;
	if (mUnk0x11c == 1) {
		aLabelX = (mWidth - aLabelWidth) / 2 + mUnk0x114;
	}
	else {
		aLabelX = mUnk0x114;
	}

	int aFontHeight = mUnk0xec->GetHeight();
	int aAscent = mUnk0xec->GetAscent();
	int aLabelY = aAscent + mUnk0x118 + (mHeight - aFontHeight) / 2;

	Color aLabelColor;
	if (!mIsDown) {
		if (!mIsOver) {
			aLabelColor =
				Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp825,362", 0xffffff));
		}
		else {
			aLabelColor =
				Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp824,360", 0xffffff));
		}
	}
	else {
		aLabelColor =
			Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp823,355", 0xffffff));
	}

	g->SetColor(aLabelColor);
	g->DrawString(mLabel, aLabelX, aLabelY);
}

// FUNCTION: POPCAPGAME1 0x004970b0
void ThunderCheckbox::MouseDown(int x, int y, int theClickCount)
{
	if (!mUnk0x110 || !mChecked) {
		Checkbox::MouseDown(x, y, theClickCount);
	}

	if (0 <= mUnk0x10c) {
		GetThunderballApp()->PlaySample(mUnk0x10c);
	}
}

// FUNCTION: POPCAPGAME1 0x00497010
void ThunderCheckbox::MouseEnter()
{
	Checkbox::MouseEnter();
	if (mUnk0x150 == 0.0 && mUnk0x140 > 0.0) {
		mUnk0x140 = 0.0;
	}
	MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00497130
void ThunderCheckbox::MouseLeave()
{
	Checkbox::MouseLeave();
	if (!mIsDown) {
		if (mIsOver) {
			goto LAB_00497195;
		}
		if (0.0 < mUnk0x140) {
			if ((mUnk0x118 <= 0.0) || (mUnk0x140 = mUnk0x148 - mUnk0x140, mUnk0x140 < 0.0)) {
				mUnk0x140 = 0;
			}
			MarkDirty();
			return;
		}
	}
	if (mIsOver) {
		return;
	}

LAB_00497195:
	if ((0.0 < mUnk0x150) && (mUnk0x140 < 1.0)) {
		mUnk0x140 = mUnk0x150 + mUnk0x140;
		if (1.0 < mUnk0x140) {
			mUnk0x140 = 0;
			MarkDirty();
			return;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00497100
void ThunderCheckbox::MouseUp(int x, int y, int theClickCount)
{
	Checkbox::MouseUp(x, y, theClickCount);
	MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00497050
void ThunderCheckbox::Update()
{
	Checkbox::Update();

	double dVar1 = 0.0;
	if ((mUnk0x148 != 0.0) && (mUnk0x140 > 0.0)) {
		if ((mUnk0x148 <= 0.0) || (mUnk0x140 != 0.0)) {
			MarkDirty();
			return;
		}
		dVar1 = 1.0;
	}
	mUnk0x140 = dVar1;
}
