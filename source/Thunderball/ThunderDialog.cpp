#include "ThunderDialog.h"

#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "Res.h"

#include <SexyAppFramework/DialogButton.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/SexyApp.h>
#include <SexyAppFramework/Font.h>

using namespace Sexy;

// SYNTHETIC: POPCAPGAME1 0x0049bef0
// Sexy::ThunderDialog::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00497280
ThunderDialog::ThunderDialog(
	int theId,
	bool isModal,
	const SexyString& theDialogHeader,
	const SexyString& theDialogLines,
	const SexyString& theDialogFooter,
	int theButtonMode
)
	: Dialog(
		  IMAGE_DLG_BUTTON3,
		  IMAGE_DLG_DIALOGBOX,
		  theId,
		  isModal,
		  theDialogHeader,
		  theDialogLines,
		  theDialogFooter,
		  theButtonMode
	  )
{
	mContentInsets = Insets(
		ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp832,39",0x23),
		ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp833,39",0x14),
  		ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp834,39",0x23),
		ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp835,39",0x1a)
	);

	SetHeaderFont(GetFontById(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp836,41",0x2f)));
	SetLinesFont(GetFontById(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp837,42",0x31)));

	mButtonHeight = IMAGE_DLG_BUTTON3->mHeight / 3;
	mYesButton = MakeButtonCopy(mYesButton);
	mNoButton = MakeButtonCopy(mNoButton);
	SetupButton(mYesButton, false);
	SetupButton(mNoButton, false);

	SetColor(3, Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp838,52", 0xffffff)));
	SetColor(4, Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp839,53", 0xffffff)));
	SetColor(1, Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp840,54", 0xffffff)));
	SetColor(0, Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp841,55", 0x63f7ff)));

	mUnk0x15C = 0xffffffff;
	mUnk0x150 = 0xfffe7960;
	mUnk0x154 = 0xfffe7960;
	mUnk0x158 = 0;
	mUnk0x160 = false;
	mUnk0x161 = false;
	mUnk0x163 = false;
	mUnk0x162 = true;
	mSpaceAfterHeader = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp842,66",0x20);
	mUnk0x168 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp843,67",0x23);
	mUnk0x16C = 0;
	mUnk0x174 = 0;
	mUnk0x170 = false;
}

// STUB: POPCAPGAME1 0x00497550
ThunderDialog::~ThunderDialog()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00497720
void ThunderDialog::CancelScroll()
{
	mWidgetFlagsMod.mRemoveFlags = 0;
	mMouseVisible = true;
	mUnk0x15C = 0xffffffff;
	mUnk0x150 = 0xfffe7960;
	mUnk0x154 = 0xfffe7960;
	mUnk0x158 = 0;
}

// FUNCTION: POPCAPGAME1 0x00497580
void ThunderDialog::DoScroll(int param_1)
{
	gSexyApp->PlaySample(SOUND_DIALOG_MOVE);

	mUnk0x15C = param_1;
	int iVar1 = mY;
	if (iVar1 < 0) {
		iVar1 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp844,94",100);
	}
	mUnk0x150 = iVar1;

	if (mUnk0x15C < 1) {
		mY = -(mHeight);
	} else {
		mY = 600;
	}

	mUnk0x16C = mY;
	mUnk0x164 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp845,101",0);

	if (param_1 < 1) {
		mUnk0x154 = 0xfffe7960;
	} else if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp846,104", false)) {
		mUnk0x168 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp847,106",0x14);
		mUnk0x154 = mUnk0x150;
		mUnk0x150 -= 0x32;
	}
	
	Resize(mX, mY, mWidth, mHeight);
	mWidgetFlagsMod.mRemoveFlags = 0;
	mMouseVisible = true;
}

// FUNCTION: POPCAPGAME1 0x00497690
void ThunderDialog::DoScrollOff(int param_1)
{
	gSexyApp->PlaySample(SOUND_DIALOG_MOVE);
	mUnk0x161 = param_1;
	mUnk0x15C = 0xffffffff;
	mUnk0x150 = -(mHeight);
	mUnk0x160 = 1;

	gSexyApp->KillDialog(mId, false, false);
	mWidgetFlagsMod.mRemoveFlags |= 0x30;
	mMouseVisible = false;
}

// FUNCTION: POPCAPGAME1 0x00497700
void ThunderDialog::FinishScroll()
{
	if (this->mUnk0x150 != 0xfffe7960) {
    	mY = this->mUnk0x150;
  	}
}

// FUNCTION: POPCAPGAME1 0x00497750
int ThunderDialog::GetLeft()
{
	
	return mX + mContentInsets.mLeft + mBackgroundInsets.mLeft -
	// STRING: POPCPGAME1 0x005fcb70
		   ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp848,166", 0);
}

// FUNCTION: POPCAPGAME1 0x00497780
int ThunderDialog::GetRight()
{
	return mWidth - mContentInsets.mLeft - mBackgroundInsets.mLeft + mX;
}

// FUNCTION: POPCAPGAME1 0x004977a0
int ThunderDialog::GetTop()
{
  return mY + mContentInsets.mTop + mBackgroundInsets.mTop + mHeaderFont->GetHeight() + mSpaceAfterHeader -  ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp849,180",0xc);
}

// FUNCTION: POPCAPGAME1 0x004977e0
int ThunderDialog::GetWidth()
{
  return ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp850,187",0) + mWidth - mContentInsets.mRight - mContentInsets.mLeft - mBackgroundInsets.mRight - mBackgroundInsets.mLeft;
}

// FUNCTION: POPCAPGAME1 0x00497570
bool ThunderDialog::IsScrolling()
{
	return mUnk0x150 != 0xfffe7960;
}

// FUNCTION: POPCAPGAME1 0x00497820
void ThunderDialog::Draw(Graphics* g)
{
	Dialog::Draw(g);

	if (mUnk0x174 != NULL) {
		mUnk0x174(g);
	}

	if (mUnk0x163) {
		int iVar3 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp862,297",6) - (IMAGE_DLG_CONNECTOR->mHeight);
		int iVar4 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp863,300",0x1e);
		int iVar5 = mY + IMAGE_DLG_SEGMENT->mHeight + iVar4;

		while (-1 < iVar5) {
			iVar5 = iVar4;

			g->DrawImage(IMAGE_DLG_SEGMENT, 
				ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp864,303",0) + (mWidth - IMAGE_DLG_SEGMENT->mWidth) / 2,
				iVar5
			);

			iVar4 -= mUnk0x168;
			iVar5 = mY + IMAGE_DLG_SEGMENT->mHeight + iVar4;
		}

		g->DrawImage(IMAGE_DLG_CONNECTOR, 
				ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp864,303",0) + (mWidth - IMAGE_DLG_CONNECTOR->mWidth) / 2,
				iVar3
			);


	}
}

// FUNCTION: POPCAPGAME1 0x00497930
void ThunderDialog::KeyDown(KeyCode theKey)
{
	Widget::KeyDown(theKey);
}

// FUNCTION: POPCAPGAME1 0x00497910
void ThunderDialog::MouseDown(int x, int y, int theClickCount)
{
	if (this->mUnk0x150 == 0xfffe7960) {
    	Widget::MouseDown(x, y, theClickCount);
	}
}

// STUB: POPCAPGAME1 0x0049bf20
void ThunderDialog::Update()
{
	
}
