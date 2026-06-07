#include "ReplayDialog.h"

#include "Board.h"
#include "Res.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/WidgetManager.h>
#include <string>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004a9960
ReplayDialog::ReplayDialog(Board* param_1) : ThunderDialog(0x16, true, "", "", "", 0)
{
	mPriority = 0;
	mBoard = param_1;
	const char* options[5] = {"Replay", "Next", "Prev", "Save", "Done"};
	mReplayButton = MakeEmbeddedButton(0, this, IMAGE_DLG_INSTANTREPLAY, false);
	AddWidget(mReplayButton);
	for (int i = 1; i < 5; i++) {
		mOptionButtons[i] = MakePurpleButton(i, this, options[i]);
		AddWidget(mOptionButtons[i]);
		if (5 <= i) {
			mUnk0x194 = false;
			mUnk0x190 = -1;
			mUnk0x162 = false;
			mUnk0x196 = false;
			SetMode(false, false, true);
		}
	}
}

// SYNTHETIC: POPCAPGAME1 0x0049cc00
// Sexy::ReplayDialog::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0049ac50
ReplayDialog::~ReplayDialog()
{
	RemoveAllWidgets(true);
}

// FUNCTION: POPCAPGAME1 0x00495b60
void ReplayDialog::RemovedFromManager(WidgetManager* param_1)
{
	ThunderDialog::RemovedFromManager(param_1);
}

// FUNCTION: POPCAPGAME1 0x00495b70
void ReplayDialog::SetMouseVisibility(bool param_1)
{
	mReplayButton->mMouseVisible = param_1;
	mOptionButtons[0]->mMouseVisible = param_1;
	mOptionButtons[1]->mMouseVisible = param_1;
	mOptionButtons[2]->mMouseVisible = param_1;
	mOptionButtons[3]->mMouseVisible = param_1;
}

// FUNCTION: POPCAPGAME1 0x00495bb0
void ReplayDialog::Resize(int param_1, int param_2, int param_3, int param_4)
{
	ThunderDialog::Resize(param_1, param_2, param_3, param_4);
	mReplayButton->Move(
		// STRING: POPCAPGAME1 0x005fb648
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp711,117", 10),
		// STRING: POPCAPGAME1 0x005fb690
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp712,117", 10)
	);

	// STRING: POPCAPGAME1 0x005fb600
	int iVar3 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp713,118", 10);
	// STRING: POPCAPGAME1 0x005fb5b8
	int iVar1 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp714,119", 0x53);

	for (int i = 0; i < 4; i++) {
		if (mOptionButtons[i]->mVisible) {
			mOptionButtons[i]->Move(iVar1, iVar3);
			// STRING: POPCAPGAME1 0x005fb570
			iVar3 += IMAGE_DLG_REPLAYSEGMENT->mHeight + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp715,125", -2);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0049acc0
void ReplayDialog::MouseDown(int param_1, int param_2, int param_3)
{
	if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp716,135", 0)) {
		ThunderDialog::MouseDown(param_1, param_2, param_3);
	}
}

// FUNCTION: POPCAPGAME1 0x00495c90
int ReplayDialog::GetPreferredHeight(int param_1)
{
	int height = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp717,145", -2) + IMAGE_DLG_REPLAYTOP->mHeight;
	for (int i = 0; i < 4; i++) {
		if (mOptionButtons[i]->mVisible) {
			height += IMAGE_DLG_REPLAYSEGMENT->mHeight + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp718,149", -2);
		}
	}

	if (mUnk0x195) {
		height += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp719,153", 0);
	}

	return height;
}

// FUNCTION: POPCAPGAME1 0x00495d20
bool ReplayDialog::IsFast()
{
	if (mBoard->mIsOver) {
		if (GetThunderballApp()->mWidgetManager->IsRightButtonDown()) {
			return true;
		}
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x0049ad00
void ReplayDialog::BlinkDoneButton()
{
	mOptionButtons[3]->Blink(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp720,185", 10), true);
}

// FUNCTION: POPCAPGAME1 0x00495d50
void ReplayDialog::StopBlinkingButtons()
{
	mOptionButtons[3]->mUnk0x14c = 0;
}

// FUNCTION: POPCAPGAME1 0x0049ad30
void ReplayDialog::ButtonPress(int theId)
{
	if (theId == 2) {
		mUnk0x194 = true;
		mBoard->SetSlowMo(true, 0xfa);
	}
}

// FUNCTION: POPCAPGAME1 0x00495d70
void ReplayDialog::Draw(Graphics* g)
{
	g->DrawImage(IMAGE_DLG_REPLAYTOP, 0, 0);
	int height = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp721,269", -2) + IMAGE_DLG_REPLAYTOP->mHeight;

	for (int i = 0; i < 4; i++) {
		ThunderButton* button = mOptionButtons[i];
		if (button->mVisible) {
			g->DrawImage(IMAGE_DLG_REPLAYSEGMENT, 0, height);
			height += IMAGE_DLG_REPLAYSEGMENT->mHeight + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp722,275", -2);
		}
	}

	if (mUnk0x195) {
		DeferOverlay(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp723,280", 0));
	}
}

// FUNCTION: POPCAPGAME1 0x0049cc30
void ReplayDialog::Update()
{
	ThunderDialog::Update();
	if (!IsScrolling() && mWidgetManager != NULL) {
		if (mBoard->mIsOver && mWidgetManager->IsLeftButtonDown()) {
			if (!mUnk0x194) {
				mUnk0x194 = true;
				mBoard->SetSlowMo(true, 0xfa);
			}
		}
		else if (mUnk0x194) {
			mUnk0x194 = false;
			mBoard->SetSlowMo(false, 0xfa);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0049e5d0
void ReplayDialog::DrawOverlay(Graphics* g)
{
	if (mUnk0x195 && !mBoard->mUnk0x1b8) {
		std::string str = StrFormat("%d", mUnk0x190 + 1);
		int strWidth = mHeaderFont->StringWidth(str);
		int aX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp724,292", 0x22);
		int aY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp725,293", 200);

		g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp726,295", 0xff00ff)));

		if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp727,296", false)) {
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		}

		g->SetFont(FONT_OVERLOAD12OUTLINE);
		g->DrawString(str, (aX - strWidth) / 2, aY);
		g->DrawString(str, (aX - strWidth) / 2 + 1, aY - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ReplayDialog.cpp728,300", 0x46));
	}
}

// FUNCTION: POPCAPGAME1 0x0049ab70
void ReplayDialog::SetMode(bool param_1, bool param_2, bool param_3)
{
	mUnk0x196 = param_1;
	mUnk0x194 = false;
	if ((param_3) || (mUnk0x190 < 0) || mUnk0x190 >= mBoard->mUnk0x184) {
		mUnk0x190 = -1;
	}

	mUnk0x195 = param_2;
	if (param_2) {
		int iVar1 = mBoard->mUnk0x184;
		if (iVar1 > 2) {
			mUnk0x195 = false;
		}
		else if ((mUnk0x190 < 0) || (mUnk0x190 >= iVar1)) {
			mUnk0x190 = iVar1 - 1;
		}
	}

	if (param_1 && !mBoard->mUnk0xc6 && !mUnk0x195) {
		mOptionButtons[2]->SetVisible(false);
	}
	else {
		mOptionButtons[2]->SetVisible(true);
	}

	mOptionButtons[0]->SetVisible(mUnk0x195);
	mOptionButtons[1]->SetVisible(mUnk0x195);
}

// FUNCTION: POPCAPGAME1 0x0049ad60
void ReplayDialog::ButtonDepress(int param_1)
{
	if (!IsScrolling()) {
		switch (param_1) {
		case 0:
			if (!mReplayButton->mUnk0x150) {
				mBoard->ShowReplay(mUnk0x190, false);
			}
			else {
				SetMode(mUnk0x196, !mUnk0x195, false);
				mBoard->PositionReplayDialog();
			}
			break;
		case 1:
		case 2:
			mUnk0x190 += (uint) (param_1 == 1) * 2 - 1;
			if (mUnk0x190 < 0) {
				mUnk0x190 = mBoard->mUnk0x184 - 1;
			}

			if (mBoard->mUnk0x184 <= mUnk0x190) {
				mUnk0x190 = 0;
			}

			MarkDirty();
			break;
		case 3:
			mBoard->DoReplayFileDialog(true, mUnk0x190, mUnk0x195);
			break;
		case 4:
			if (!mBoard->mUnk0xc5) {
				mBoard->EndReplay();
				mBoard->mUnk0x12c = false;
				mBoard->mReplayButton->SetDisabled(false);
			}
			else {
				mBoard->DoReplayFileDialog(false, -1, false);
			}
			break;
		}
	}
}
