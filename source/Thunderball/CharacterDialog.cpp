#include "CharacterDialog.h"

#include "Res.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/Checkbox.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/Widget.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x004b2990
CharacterDialog::CharacterDialog(Board* param_1)
    : ThunderDialog(0, false, "", "", "", 0)
{
}

// SYNTHETIC: POPCAPGAME1 0x004adcd0
// Sexy::CharacterDialog::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x004a0090
CharacterDialog::~CharacterDialog()
{
}

// FUNCTION: POPCAPGAME1 0x00496b40
void CharacterDialog::AddedToManager(WidgetManager* param_1)
{
    ThunderDialog::AddedToManager(param_1);
}

// FUNCTION: POPCAPGAME1 0x00495b60
void CharacterDialog::RemovedFromManager(WidgetManager* param_1)
{
    ThunderDialog::RemovedFromManager(param_1);
}

// FUNCTION: POPCAPGAME1 0x004926a0
void CharacterDialog::SyncDifficultyVisibility()
{
	if (mUnk0x219) {
		Checkbox* aCheckbox = mPlayCheckboxes[1];
		bool aVisible = aCheckbox->mChecked;
		mDifficultyCheckboxes[0]->mVisible = aVisible;
		mDifficultyCheckboxes[1]->mVisible = aVisible;
		mDifficultyCheckboxes[2]->mVisible = aVisible;
		mDifficultyCheckboxes[3]->mVisible = aVisible;
	}
}

// FUNCTION: POPCAPGAME1 0x00492590
int CharacterDialog::CanSelectCharacter(int param_1)
{
	if (param_1 != 10) {
		if (param_1 < 0 ||
			param_1 > mApp->GetMaxUnlockedCharacter() ||
			param_1 > 10) {
			return 0;
		}
	}

	return 1;
}
    
// FUNCTION: POPCAPGAME1 0x004925d0
void CharacterDialog::SyncNamePos()
{
	Font* aFont = FONT_OVERLOAD16OUTLINE;
	for (int i = 0; i < 2; i++) {
		int aCenter;
		if (i == 0) {
			// STRING: POPCAPGAME1 0x005f9520
			aCenter = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp29,351", 0x5a);
		} else {
			// STRING: POPCAPGAME1 0x005f94d8
			aCenter = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp30,351", 0x1a9);
		}

		std::string& aName = mNames[i];
		int aWidth = aFont->StringWidth(aName);
		mNameX[i] = aCenter - aWidth / 2;

		// STRING: POPCAPGAME1 0x005f9490
		int aRight = aCenter + aWidth / 2 + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp31,355", 0);
		// STRING: POPCAPGAME1 0x005f9448
		int aLimit = mWidth - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp32,356", 0x32);
		if (aRight > aLimit)
			aRight = aLimit;
		ButtonWidget* aButton = mNameButtons[i];
		*(int*)((char*)aButton + 0x30) = aRight;
	}
}

// STUB: POPCAPGAME1 0x00498670
void CharacterDialog::Resize(int param_1, int param_2, int param_3, int param_4)
{
}

// FUNCTION: POPCAPGAME1 0x00492550
int CharacterDialog::GetPreferredHeight(int param_1)
{
	if (mUnk0x219) {
		// STRING: POPCAPGAME1 0x005f9400
		return ModVal(
			0,
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp27,320",
			0x20d);
	}

	// STRING: POPCAPGAME1 0x005f93b8
	return ModVal(
		0,
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterDialog.cpp28,320",
		0x1e0);
}

// FUNCTION: POPCAPGAME1 0x004926e0
void CharacterDialog::CheckboxChecked(int param_1, bool param_2)
{
	if ((unsigned int)param_1 <= 1) {
		mPlayCheckboxes[1 - param_1]->mChecked = false;
		SyncDifficultyVisibility();
		return;
	}

	if ((unsigned int)(param_1 - 2) <= 3) {
		for (int i = 2; i < 6; i++) {
			if (param_1 != i)
				mDifficultyCheckboxes[i - 2]->mChecked = false;
		}
	}
}

// STUB: POPCAPGAME1 0x00498900
void CharacterDialog::SelectCharacter(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x00498a60
void CharacterDialog::ButtonPress(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x0049c490
void CharacterDialog::Update()
{
}

// STUB: POPCAPGAME1 0x004a0190
void CharacterDialog::DrawCharacterInfo(Graphics* param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x004a0590
void CharacterDialog::Draw(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004a0f90
void CharacterDialog::SaveDetails()
{
}

// STUB: POPCAPGAME1 0x004a1270
void CharacterDialog::DialogButtonDepress(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x004add00
void CharacterDialog::ButtonDepress(int param_1)
{
}
