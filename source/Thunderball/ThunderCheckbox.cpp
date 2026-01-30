#include "ThunderCheckbox.h"

#include "Res.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Graphics.h>

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
	mUnk0x104 = 0;
	mUnk0x108 = 15;
	mUnk0xf4 = 0;
	mUnk0x120 = 0;
	mUnk0x124 = 0;
	mUnk0x128 = 0;
	mUnk0x12c = 0;
	mUnk0x130 = 0;
	mUnk0x134 = 0;
	mUnk0x138 = 0;
	mUnk0x13c = 0;
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
