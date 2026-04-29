#include "OptionsDialog.h"

#include "Board.h"
#include "ConstEnums.h"
#include "LogicMgr.h"
#include "PlayerInfo.h"
#include "Res.h"
#include "ThunderButton.h"
#include "ThunderCheckbox.h"
#include "ThunderCommon.h"
#include "ThunderSlider.h"
#include "ThunderballApp.h"
#include "EndLevelDialog.h"

#include <SexyAppFramework/DialogButton.h>
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/WidgetManager.h>
#include <SexyAppFramework/Rect.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004affd0
OptionsDialog::OptionsDialog(bool isFromGame)
	: ThunderDialog(0x13, true, isFromGame ? "MENU" : "OPTIONS", "", isFromGame ? "Back To Game" : "Done", 3)
{
	mUnk0x163 = true;
	mFromGame = isFromGame;

	mMusicVolumeSlider = new ThunderSlider("Music Volume", 0, this);
	mMusicVolumeSlider->SetValue(GetThunderballApp()->GetMusicVolume());
	mSfxVolumeSlider = new ThunderSlider("Sound Effects", 1, this);
	mSfxVolumeSlider->SetValue(GetThunderballApp()->GetSfxVolume());
	mFeverVolumeSlider = new ThunderSlider("Fever Volume", 2, this);
	mFeverVolumeSlider->SetValue(GetThunderballApp()->GetFeverVolume());

	mFullscreenCheckbox = MakeCheckbox2(3, this, "Fullscreen", 0);
	mCustomCursorsCheckbox = MakeCheckbox2(4, this, "CustomCursors", 0);
	m3DAccelerationCheckbox = MakeCheckbox2(5, this, "3D Acceleration", 0);
	mColorblindModeCheckbox = MakeCheckbox2(6, this, "Colorblind Mode", 0);

	mHelpButton = MakeButton(7, this, "Help", NULL);
	mUnk0x1A0 = NULL;
	mUnk0x1A4 = NULL;
	mMainMenuButton = MakeButton(8, this, "Main Menu", NULL);
	mNewLevelButton = MakeButton(9, this, "New Level", NULL);
	mNewChallengeButton = MakeButton(10, this, "New Challenge", NULL);

	mYesButton->mComponentImage = IMAGE_DLG_PLAYBUTTON1;
	mYesButton->mWidth = IMAGE_DLG_PLAYBUTTON1->mWidth;
	mYesButton->mHeight = IMAGE_DLG_PLAYBUTTON1->mHeight / 2;
	mYesButton->mNormalRect.mWidth = 1;
	mYesButton->mNormalRect.mHeight = 0;
	mYesButton->mOverRect = Rect(0, 0, IMAGE_DLG_PLAYBUTTON1->mWidth, IMAGE_DLG_PLAYBUTTON1->mHeight / 2);
	mYesButton->mDownRect =
		Rect(0, IMAGE_DLG_PLAYBUTTON1->mHeight / 2, IMAGE_DLG_PLAYBUTTON1->mWidth, IMAGE_DLG_PLAYBUTTON1->mHeight / 2);

	if (isFromGame && (GetThunderballApp()->mGameMode == GameMode::CHALLENGE)) {
		mNewLevelButton->mLabel = "Restart Challenge";
	}
	else if (GetThunderballApp()->mGameMode == GameMode::ADVENTURE) {
		mNewLevelButton->mLabel = "Restart Level";
		if (GetThunderballApp()->mBoard != NULL && GetThunderballApp()->mBoard->mLogicMgr->mUnk0x4 == 5) {
			if (GetThunderballApp()->mBoard->mLogicMgr->BeatLevel()) {
				mNewLevelButton->mLabel = "Next Level";
			}
		}
	}

	mFullscreenCheckbox->mChecked = !GetThunderballApp()->mIsPhysWindowed;
	mCustomCursorsCheckbox->mChecked = GetThunderballApp()->mCustomCursorsEnabled;
	m3DAccelerationCheckbox->mChecked = GetThunderballApp()->Is3DAccelerated();

	if (GetThunderballApp()->mCurProfile != NULL) {
		mColorblindModeCheckbox->mChecked = GetThunderballApp()->mCurProfile->mUnk0x60;
	}

	mMainMenuButton->SetVisible(isFromGame);
	mNewLevelButton->SetVisible(isFromGame);

	if ((isFromGame) || GetThunderballApp()->mGameMode != GameMode::CHALLENGE) {
		mNewChallengeButton->SetVisible(false);
	}
	else {
		mNewChallengeButton->SetVisible(true);
	}

	mHelpButton->SetVisible(true);

	if (isFromGame &&
		(GetThunderballApp()->mGameMode == GameMode::UNKNOWN_5 || GetThunderballApp()->mGameMode == GameMode::DEMO)) {
		mNewLevelButton->SetVisible(false);
		mHelpButton->SetVisible(false);
	}

	mUnk0x1B8 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp684,98", 0xdc);
	if (mMainMenuButton->mVisible) {
		mUnk0x1B8 += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp685,100", 0x20);
	}
	if (mHelpButton->mVisible) {
		mUnk0x1B8 += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp686,102", 0x20);
	}
	if ((isFromGame != 0) && (GetThunderballApp()->mGameMode == GameMode::CHALLENGE)) {
		mUnk0x1B8 += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp687,104", 0x20);
	}
}

// SYNTHETIC: POPCAPGAME1 0x0049cbd0
// Sexy::OptionsDialog::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00499f40
OptionsDialog::~OptionsDialog()
{
	if (mMusicVolumeSlider != NULL) {
		delete mMusicVolumeSlider;
	}
	if (mSfxVolumeSlider != NULL) {
		delete mSfxVolumeSlider;
	}
	if (mFeverVolumeSlider != NULL) {
		delete mFeverVolumeSlider;
	}
	if (mFullscreenCheckbox != NULL) {
		delete mFullscreenCheckbox;
	}
	if (mCustomCursorsCheckbox != NULL) {
		delete mCustomCursorsCheckbox;
	}
	if (m3DAccelerationCheckbox != NULL) {
		delete m3DAccelerationCheckbox;
	}
	if (mColorblindModeCheckbox != NULL) {
		delete mColorblindModeCheckbox;
	}
	if (mHelpButton != NULL) {
		delete mHelpButton;
	}
	if (mMainMenuButton != NULL) {
		delete mMainMenuButton;
	}
	if (mNewLevelButton != NULL) {
		delete mNewLevelButton;
	}
	if (mNewChallengeButton != NULL) {
		delete mNewChallengeButton;
	}
}

// FUNCTION: POPCAPGAME1 0x004956e0
void OptionsDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	Dialog::AddedToManager(theWidgetManager);
	theWidgetManager->AddWidget(mMusicVolumeSlider);
	theWidgetManager->AddWidget(mSfxVolumeSlider);
	theWidgetManager->AddWidget(mFeverVolumeSlider);
	theWidgetManager->AddWidget(mFullscreenCheckbox);
	theWidgetManager->AddWidget(mCustomCursorsCheckbox);
	theWidgetManager->AddWidget(m3DAccelerationCheckbox);
	theWidgetManager->AddWidget(mColorblindModeCheckbox);
	theWidgetManager->AddWidget(mHelpButton);
	theWidgetManager->AddWidget(mMainMenuButton);
	theWidgetManager->AddWidget(mNewLevelButton);
	theWidgetManager->AddWidget(mNewChallengeButton);
}

// FUNCTION: POPCAPGAME1 0x0049a5c0
void OptionsDialog::ButtonDepress(int theId)
{
	if (!IsScrolling()) {
		Dialog::ButtonDepress(theId);
		ThunderballApp* aApp = GetThunderballApp();
		if ((aApp->mGameMode == GameMode::CHALLENGE || aApp->mUnk0x834 == 0) && aApp->IsTrialOver() && theId != 7 && theId != mYesButton->mId) {
			aApp->ShowUpsellScreen();
			return;
		}
		
		switch (theId) {
			case 7:
				aApp->ShowHelpScreen(false, aApp->mBoard == NULL);
				if (aApp->mBoard == NULL) {
					aApp->FinishOptionsDialog(true, true);
				}
			break;

			case 8:
				aApp->DoConfirmMainMenuDialog();
			break;
				
			case 9:
				if ((aApp->mBoard != NULL && aApp->mBoard->mEndLevelDialog->mWidgetManager == NULL) && (aApp->mBoard->mLogicMgr->mUnk0x4 == 5 || aApp->mBoard->mLogicMgr->BeatLevel())) {
					aApp->DoConfirmRestartLevelDialog(-1);
				}
			break;

			case 10:
				aApp->DoConfirmNewChallengeDialog();
				if (aApp->mBoard != NULL && aApp->mBoard->mEndLevelDialog->mWidgetManager != NULL) {
					aApp->FinishConfirmNewChallengeDialog(true);
				}
			break;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004a9700
void OptionsDialog::CheckboxChecked(int theId, bool checked)
{
	if (!IsScrolling()) {
		if (theId == 3) {
			if (GetThunderballApp()->mForceFullscreen && !checked) {
				GetThunderballApp()->DoDialogScroll(
					3,
					true,
					"No Windowed Mode",
					"Windowed mode is only available if your desktop is running in either 16 bit or 32 bit color mode, which it is not.",
					"OK",
					3
				);

				mFullscreenCheckbox->SetChecked(true);
			}
		}
		else if (theId == 5 && checked) {
			if (!GetThunderballApp()->Is3DAccelerationSupported()) {
				GetThunderballApp()->DoDialogScroll(
					0,
					true,
					"Not Supported",
					"Hardware Acceleration cannot be enabled on this computer.\nYour video card does not meet the minimum requirements for this game.",
					"OK",
					3
				);

				m3DAccelerationCheckbox->SetChecked(false);
			} 
			if (!GetThunderballApp()->Is3DAccelerationRecommended()) {
				GetThunderballApp()->DoDialogScroll(
					0,
					true,
					"Warning",
					"Your video card may not fully support this feature.\nIf you experience slower performance, please disable Hardware Acceleration.",
					"OK",
					3
				);
			}
		} 
	}
}

// FUNCTION: POPCAPGAME1 0x0049a480
void OptionsDialog::Draw(Graphics* g)
{
	ThunderDialog::Draw(g);
	g->DrawImageBox(
		Rect(
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp706,252", 0x24),
			(mHeight - IMAGE_DLG_PLAYWIDGET1->mHeight) -
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp707,252", 6),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp708,252", 0x172),
			IMAGE_DLG_PLAYWIDGET1->mHeight
		),
		IMAGE_DLG_PLAYWIDGET1
	);
}

// FUNCTION: POPCAPGAME1 0x004956c0
int OptionsDialog::GetPreferredHeight(int theWidth)
{
	return Dialog::GetPreferredHeight(theWidth) + mUnk0x1B8;
}

// FUNCTION: POPCAPGAME1 0x00495880
void OptionsDialog::OrderInManagerChanged()
{
	mWidgetManager->BringToFront(mMusicVolumeSlider);
	mWidgetManager->BringToFront(mSfxVolumeSlider);
	mWidgetManager->BringToFront(mFeverVolumeSlider);
	mWidgetManager->BringToFront(mFullscreenCheckbox);
	mWidgetManager->BringToFront(mCustomCursorsCheckbox);
	mWidgetManager->BringToFront(m3DAccelerationCheckbox);
	mWidgetManager->BringToFront(mColorblindModeCheckbox);
	mWidgetManager->BringToFront(mHelpButton);
	mWidgetManager->BringToFront(mMainMenuButton);
	mWidgetManager->BringToFront(mNewLevelButton);
	mWidgetManager->BringToFront(mNewChallengeButton);
}

// FUNCTION: POPCAPGAME1 0x004957b0
void OptionsDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Dialog::RemovedFromManager(theWidgetManager);
	theWidgetManager->RemoveWidget(mMusicVolumeSlider);
	theWidgetManager->RemoveWidget(mSfxVolumeSlider);
	theWidgetManager->RemoveWidget(mFeverVolumeSlider);
	theWidgetManager->RemoveWidget(mFullscreenCheckbox);
	theWidgetManager->RemoveWidget(mCustomCursorsCheckbox);
	theWidgetManager->RemoveWidget(m3DAccelerationCheckbox);
	theWidgetManager->RemoveWidget(mColorblindModeCheckbox);
	theWidgetManager->RemoveWidget(mHelpButton);
	theWidgetManager->RemoveWidget(mMainMenuButton);
	theWidgetManager->RemoveWidget(mNewLevelButton);
	theWidgetManager->RemoveWidget(mNewChallengeButton);
}

// FUNCTION: POPCAPGAME1 0x0049a080
void OptionsDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
	ThunderDialog::Resize(theX, theY, theWidth, theHeight);

	int iVar5 = GetLeft();
	theY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp688,133", -10);
	theY += GetTop();
	int iVar6 = GetWidth();
	int iVar7 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp689,135", 5);
	int iVar10 = iVar6 / 2 - iVar7 / 2;
	iVar6 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp690,137", 0xb6);
	int iVar8 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp691,138", 0);

	mMusicVolumeSlider->Resize(
		iVar5 + iVar10,
		theY + iVar8,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp692,141", 0xbe),
		0x24
	);
	mMusicVolumeSlider->MarkAllDirty();

	mFeverVolumeSlider->Layout(
		LAY_SameLeft | LAY_Below | LAY_SameSize,
		mMusicVolumeSlider,
		0,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp694,142", 0),
		0,
		0
	);
	mSfxVolumeSlider->Layout(
		LAY_SameLeft | LAY_Below | LAY_SameSize,
		mFeverVolumeSlider,
		0,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp695,143", 0),
		0,
		0
	);
	mFullscreenCheckbox->Layout(
		LAY_Below | LAY_SetLeft | LAY_SetWidth,
		mSfxVolumeSlider,
		iVar8 + iVar5,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp696,144", 8),
		iVar6,
		0
	);

	mCustomCursorsCheckbox->Layout(
		LAY_SameLeft | LAY_Below | LAY_SameWidth,
		mFullscreenCheckbox,
		0,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp697,145", 0),
		0,
		0
	);
	m3DAccelerationCheckbox->Layout(
		LAY_SameTop | LAY_Right | LAY_SameWidth,
		mFullscreenCheckbox,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp698,146", 5),
		0,
		0,
		0
	);
	mColorblindModeCheckbox->Layout(
		LAY_SameLeft | LAY_Below | LAY_SameWidth,
		m3DAccelerationCheckbox,
		0,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp699,147", 0),
		0,
		0
	);

	if (!mFromGame) {
		if (mHelpButton->mVisible) {
			mHelpButton->Layout(
				LAY_SameLeft | LAY_Above | LAY_SameSize,
				mYesButton,
				0,
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp704,176", -0x1e),
				0,
				0
			);
		}
	}
	else {
		mMainMenuButton->Layout(
			LAY_SameLeft | LAY_Below | LAY_SameWidth,
			mYesButton,
			0,
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp700,151", -0x1e),
			0,
			0
		);
		if (GetThunderballApp()->mGameMode == GameMode::CHALLENGE) {
			mNewLevelButton->Layout(LAY_SameLeft | LAY_Below | LAY_SameSize, mMainMenuButton, 0, 0, 0, 0);
			mHelpButton->Layout(
				LAY_SameLeft | LAY_Below | LAY_SetWidth | LAY_SetHeight,
				mNewLevelButton,
				0,
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp701,156", 0),
				iVar10,
				0
			);
			mNewChallengeButton->Layout(LAY_SameTop | LAY_Right | LAY_SameSize, mHelpButton, 0, 0, 0, 0);
		}
		else {
			Board* aBoard = GetThunderballApp()->mBoard;
			if ((aBoard == NULL) /*|| (aBoard->mUnk0x160->mUnk0x10 != 0)*/) {
				mHelpButton->Layout(
					LAY_SameLeft | LAY_Below | LAY_SameWidth,
					mMainMenuButton,
					0,
					ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp702,165", 0),
					0,
					0
				);
				mNewLevelButton->SetVisible(false);
			}
			else {
				if ((aBoard->mLogicMgr->mUnk0x4 == 5) && (aBoard->mLogicMgr->BeatLevel())) {
					mHelpButton->Layout(
						LAY_SameLeft | LAY_Below | LAY_SameWidth,
						mMainMenuButton,
						0,
						ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp702,165", 0),
						0,
						0
					);
					mNewLevelButton->SetVisible(false);
				}
				else {
					mHelpButton->Layout(
						LAY_SameLeft | LAY_Below | LAY_SetWidth | LAY_SetHeight,
						mMainMenuButton,
						0,
						ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp703,170", 0),
						iVar10,
						0
					);
					mNewLevelButton->Layout(LAY_SameTop | LAY_Right | LAY_SameSize, mHelpButton, 0, 0, 0, 0);
				}
			}
		}
	}

	ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\OptionsDialog.cpp705,179", 0x20);
	mYesButton->MarkAllDirty();
}

// FUNCTION: POPCAPGAME1 0x0049a510
void OptionsDialog::SliderVal(int theId, double theVal)
{
	if (!IsScrolling()) {
		if (theId == 0) {
			GetThunderballApp()->SetMusicVolume(theVal);
		}
		else if (theId == 1) {
			GetThunderballApp()->SetSfxVolume(theVal);
			GetThunderballApp()->PlaySample(SOUND_BUTTON1);
		}
		else if (theId == 2) {
			GetThunderballApp()->SetFeverVolume(theVal);
		}
	}
}
