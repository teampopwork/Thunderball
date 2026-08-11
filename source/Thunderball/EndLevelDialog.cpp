#include "EndLevelDialog.h"

#include "Board.h"
#include "Res.h"

#include <SexyAppFramework/DialogButton.h>
#include <SexyAppFramework/SexyApp.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x004a1a10
EndLevelDialog::EndLevelDialog(Board* param_1) : ThunderDialog(0, false, "", "", "", 0)
{
}

// SYNTHETIC: POPCAPGAME1 0x0049ec50
// Sexy::EndLevelDialog::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0049db50
EndLevelDialog::~EndLevelDialog()
{
	RemoveAllWidgets(true, false);
}

// STUB: POPCAPGAME1 0x00492c90
void EndLevelDialog::Resize(int param_1, int param_2, int param_3, int param_4)
{
}

// FUNCTION: POPCAPGAME1 0x00492e30
void EndLevelDialog::SetVisible(bool param_1)
{
	if (mVisible != param_1) {
		Widget::SetVisible(param_1);
		if (!param_1 || mShowYesButton) {
			mYesButton->SetVisible(param_1);
		}
		if (!param_1 || mShowNoButton) {
			mNoButton->SetVisible(param_1);
		}
	}
}

// STUB: POPCAPGAME1 0x00492ea0
void EndLevelDialog::UpdateStats()
{
}

// STUB: POPCAPGAME1 0x0049cab0
void EndLevelDialog::Update()
{
}

// STUB: POPCAPGAME1 0x00499290
void EndLevelDialog::DrawAdventureWin(Graphics* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004931a0
void EndLevelDialog::MouseMove(int, int theY)
{
	if (mHighScoreEntry != NULL && theY >= mUnk0x198 - 15 && theY < mUnk0x198 + 15) {
		gSexyApp->SetCursor(CURSOR_HAND);
		return;
	}

	gSexyApp->SetCursor(CURSOR_POINTER);
}

// FUNCTION: POPCAPGAME1 0x00499760
void EndLevelDialog::MouseDown(int theX, int theY, int theClickCount)
{
	if (mHighScoreEntry != NULL &&
		theY >= mUnk0x198 - 15 && theY < mUnk0x198 + 15 && theClickCount == 1) {
		gSexyApp->PlaySample(SOUND_BUTTON1);
		mBoard->ChangeHighScore(mHighScoreEntry);
		return;
	}

	ThunderDialog::MouseDown(theX, theY, theClickCount);
}

// FUNCTION: POPCAPGAME1 0x004931f0
void EndLevelDialog::MouseLeave()
{
	gSexyApp->SetCursor(CURSOR_POINTER);
	Widget::MouseLeave();
}

// STUB: POPCAPGAME1 0x00499520
void EndLevelDialog::DrawChallengeResult(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00499610
void EndLevelDialog::DrawTip(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x0049dc20
void EndLevelDialog::ButtonDepress(int param_1)
{
}

// STUB: POPCAPGAME1 0x0049c850
int EndLevelDialog::GetPreferredHeight(int param_1)
{
	return 0;
}

// STUB: POPCAPGAME1 0x00499010
void EndLevelDialog::ComputeStats()
{
}

// STUB: POPCAPGAME1 0x004a1d60
void EndLevelDialog::FinishHighScoreEntryDialog(std::string& param_1)
{
}

// STUB: POPCAPGAME1 0x004a1c30
void EndLevelDialog::InitTip()
{
}

// STUB: POPCAPGAME1 0x004ae8e0
void EndLevelDialog::Init(EndLevelMode param_1, std::list<int>* param_2)
{
}

// STUB: POPCAPGAME1 0x004a1df0
void EndLevelDialog::DrawHighScores(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004a2870
void EndLevelDialog::DrawAdventureComplete(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004a2e00
void EndLevelDialog::DrawTwoPlayerResult(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004a2260
void EndLevelDialog::DrawStats(Graphics* param_1)
{
}

// STRING: POPCAPGAME1 0x004a3660
void EndLevelDialog::Draw(Graphics* param_1)
{
}
