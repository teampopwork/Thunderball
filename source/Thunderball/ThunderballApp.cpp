#include "ThunderballApp.h"

#include "AdventureScreen.h"
#include "Board.h"
#include "CharacterMgr.h"
#include "HelpScreen.h"
#include "HighScoreMgr.h"
#include "ImageMgr.h"
#include "LevelScreen.h"
#include "LoadTimer.h"
#include "LoadingScreen.h"
#include "MainMenu.h"
#include "NewUserDialog.h"
#include "OptionsDialog.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "Res.h"
#include "StageMgr.h"
#include "StatsMgr.h"
#include "StoryScreen.h"
#include "ThunderCheckbox.h"
#include "ThunderCommon.h"
#include "ThunderDialog.h"
#include "TrophyScreen.h"
#include "UpsellScreen.h"
#include "UserDialog.h"
#include "WidgetMover.h"
#include "BlendedImage.h"

#include <SexyAppFramework/BassMusicInterface.h>
#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/DDImage.h>
#include <SexyAppFramework/Debug.h>
#include <SexyAppFramework/DialogButton.h>
#include <SexyAppFramework/EditWidget.h>
#include <SexyAppFramework/ResourceManager.h>
#include <SexyAppFramework/SWTri.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004316f0
int RegistrationControl::GetTrialAge()
{
	if (::IsWindow(mWindow)) {
		return (int) ::SendMessageA(mWindow, mQueryMessage, 0, 0);
	}
	mWindowValid = false;
	return 0;
}

// FUNCTION: POPCAPGAME1 0x004316c0
int RegistrationControl::GetTrialDuration()
{
	if (::IsWindow(mWindow)) {
		return (int) ::SendMessageA(mWindow, mQueryMessage, 2, 0);
	}
	mWindowValid = false;
	return 0;
}

// FUNCTION: POPCAPGAME1 0x00405490
static void MakeGrayscale(MemoryImage* theImage)
{
	ulong* aBits = theImage->GetBits();
	int aPixelCount = theImage->GetWidth() * theImage->GetHeight();
	if (aPixelCount > 0) {
		do {
			ulong aColor = *aBits;
			ulong aGray = (((aColor >> 8) & 0xff) * 0x99) / 0xff
				+ (((aColor >> 16) & 0xff) * 0x4c) / 0xff
				+ ((aColor & 0xff) * 0x1a) / 0xff;
			*aBits = (aColor & 0xff000000) | aGray | (aGray << 8) | (aGray << 16);
			++aBits;
		} while (--aPixelCount != 0);
	}
	theImage->BitsChanged();
}

// FUNCTION: POPCAPGAME1 0x00431760
bool RegistrationControl::IsRegistered()
{
	if (::IsWindow(mWindow)) {
		return ::SendMessageA(mWindow, mQueryMessage, 4, 0) != 0;
	}
	mWindowValid = false;
	return false;
}

// FUNCTION: POPCAPGAME1 0x00431960
bool RegistrationControl::IsWindowValid()
{
	return mWindowValid;
}

// STUB: POPCAPGAME1 0x00426f10
ThunderballApp::ThunderballApp()
{
	mTitle = "Peggle Deluxe " + mProductVersion;
	mRegKey = "PopCap\\Peggle";

	mWidth = 800;
	mHeight = 600;
	mFullscreenBits = 32;

	mBoard = NULL;
	mLevelScreen = NULL;
	mLoadingScreen = NULL;
	mMainMenu = NULL;
	mTrophyScreen = NULL;
	mStoryScreen = NULL;
	mAdventureScreen = NULL;

	mWinCloseButton = NULL;
	mWinMinimizeButton = NULL;
	mWinUnmaxButton = NULL;

	mUpsellScreen = NULL;

	mCurProfile = NULL;

	mCharacterMgr = new CharacterMgr();
	mHighScoreMgr = new HighScoreMgr();
	mImageMgr = new ImageMgr();
	mStageMgr = new StageMgr(this);
	mProfileMgr = new ProfileMgr();
	mStatsMgr = new StatsMgr();
	mEditStatsMgr = new StatsMgr();
	mWidgetMover = new WidgetMover();
}

// STUB: POPCAPGAME1 0x00431340
ThunderballApp::~ThunderballApp()
{
	delete mWidgetMover;
	delete mProfileMgr;
}

// STUB: POPCAPGAME1 0x0042ca30
void ThunderballApp::Init()
{
	SexyApp::Init();

	if (CheckForVista()) {
		WIN32_FIND_DATAA findData;
		memset(&findData, 0, sizeof(findData));

		std::string searchPath = GetAppDataFolder() + "userdata/*.*";

		HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

		if (hFind == INVALID_HANDLE_VALUE) {
			MkDir(GetAppDataFolder());

			AllowAllAccess(GetAppDataFolder());

			std::string destPath = GetAppDataFolder() + "userdata";

			MoveFileA("userdata", destPath.c_str());
		}
		FindClose(hFind);
	}

	SWTri_AddDrawTriFunc(true, true, false, false, 0x8888, true, DrawTriangle_8888_TEX1_TALPHA1_MOD0_GLOB0_BLEND1);
	// FUN_0041bf20(uVar6);

	RegistryWriteInteger("hwnd", (int) mHWnd);

	LoadResourceManifest();

	// STRING: POPCAPGAME1 0x005d7310
	if (!mResourceManager->LoadResources("Init")) {
		ShowResourceError(true);
	}

	if (!ExtractInitResources(mResourceManager)) {
		ShowResourceError(true);
	}

	// STRING: POPCAPGAME1 0x005d72f0
	if (!mResourceManager->LoadResources("Load")) {
		ShowResourceError(true);
	}

	if (!ExtractLoadResources(mResourceManager)) {
		ShowResourceError(true);
	}

	// STRING: POPCAPGAME1 0x005d87dc
	LoadMusic(0, "music\\odetojoy.ogg");
	// STRING: POPCAPGAME1 0x005d87c8
	LoadMusic(2, "music\\opening.ogg");

	mUnk0x779 = true;

	SetCursorImage(0, IMAGE_CURSOR_POINTER);
	SetCursorImage(1, IMAGE_CURSOR_HAND);
	SetCursorImage(2, IMAGE_CURSOR_DRAGGING);
	SetCursorImage(3, IMAGE_CURSOR_TEXT);

	// mCharacterMgr->Load();
	// mHighScoreMgr->Load();
	mProfileMgr->Load();
	// mStageMgr->Load();
	// mStatsMgr->Load();
	// mEditStatsMgr->Load();
	// mTrophyMgr->Load();

	std::string aCurUserName;
	bool registryReadSuccess = false;

	if (mCurProfile == NULL) {
		registryReadSuccess = RegistryReadString("CurUser", &aCurUserName);
	}

	if (registryReadSuccess) {
		mCurProfile = mProfileMgr->GetProfile(aCurUserName);
	}

	if (mCurProfile == NULL) {
		mCurProfile = mProfileMgr->GetAnyProfile();
	}

	if (!IsScreenSaver() || mCurProfile != NULL) {
		/*if (mStatsMgr->mWelcomeLabel.empty() && mCurProfile != NULL) {
			mStatsMgr->mWelcomeLabel = mCurProfile->mName;
		}*/

		mWinCloseButton = MakeWinButton(IMAGE_WIN_CLOSE, 1);
		mWinMinimizeButton = MakeWinButton(IMAGE_WIN_MINIMIZE, 2);
		mWinUnmaxButton = MakeWinButton(IMAGE_WIN_UNMAX, 3);

		mWinCloseButton->Move(mWidth - mWinCloseButton->mWidth, 0);

		mWinUnmaxButton->Layout(0x4800, mWinCloseButton, 0, 0, 0, 0);
		mWinMinimizeButton->Layout(0x4800, mWinUnmaxButton, 0, 0, 0, 0);

		// virt_meth_0x52a680
		CheckMaxStage();
		ShowLoadingScreen();
	}
	else {
		// DoDialog("No User Profile");
		mLoadingFailed = true;
	}
}

// STUB: POPCAPGAME1 0x0040c140
void ThunderballApp::BringDialogsToFront()
{
}

// FUNCTION: POPCAPGAME1 0x00405f90
void ThunderballApp::ButtonDepress(int param_1)
{
	switch (param_1) {
	case 1:
		Shutdown();
		break;
	case 2:
		::CloseWindow(mHWnd);
		break;
	case 3:
		SwitchScreenMode(true, Is3DAccelerated(), false);
		break;
	}
}

// FUNCTION: POPCAPGAME1 0x00405a20
bool ThunderballApp::CanExpire()
{
	if ((!mLoadingFailed || mCursorThreadRunning) && !mProcessInTimer && !mExpirationDisabled) {
		return true;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00405a50
bool ThunderballApp::CheckCanExpire()
{
	if (!IsRegistered() && mUnk0x834 == 0) {
		int trialAge = mRegistrationControl->GetTrialAge();
		int trialDuration = mRegistrationControl->GetTrialDuration();
		if (trialAge >= trialDuration && CanExpire()) {
			return true;
		}
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00405aa0
void ThunderballApp::CheckMaxStage()
{
	if (mCurProfile != NULL) {
		if (mCurProfile->mUnk0x28 > mMaxStage) {
			mMaxStage = mCurProfile->mUnk0x28;
			mMaxLevel = mCurProfile->mUnk0x2c;
		}
		else if (mCurProfile->mUnk0x28 == mMaxStage && mCurProfile->mUnk0x2c > mMaxLevel) {
			mMaxLevel = mCurProfile->mUnk0x2c;
		}
	}
}

// STUB: POPCAPGAME1 0x0040d180
void ThunderballApp::CheckPlayMusic(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004306e0
bool ThunderballApp::CheckSaveGame(bool param_1)
{
	return 0;
}

// FUNCTION: POPCAPGAME1 0x00423480
void ThunderballApp::CheckScrollOff(Widget* param_1, int param_2, bool param_3)
{
	if (param_1 != NULL) {
		mWidgetMover->ScrollOff(param_1, param_2, param_3);
		if (param_3) {
			mUnk0x750 = param_2;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004234f0
void ThunderballApp::CleanupScreen(Widget* param_1)
{
	if (param_1 != NULL) {
		if (mWidgetMover->WillRemove(param_1)) {
			mWidgetMover->RemoveWidget(param_1);
			mWidgetManager->RemoveWidget(param_1);
			SafeDeleteWidget(param_1);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00429390
void ThunderballApp::CleanupScreens(bool param_1)
{
	if (param_1) {
		if (mBoard != NULL) {
			if (mBoard->NeedSaveGame()) {
				mBoard->SaveGame();
			}
			mBoard->NotifyRemoving();
		}

		CleanupScreen(mBoard);
		mBoard = NULL;

		CleanupScreen(mUpsellScreen);
		mUpsellScreen = NULL;
	}

	CleanupScreen(mHelpScreen);
	mHelpScreen = NULL;

	CleanupScreen(mLevelScreen);
	mLevelScreen = NULL;

	CleanupScreen(mLoadingScreen);
	mLoadingScreen = NULL;

	CleanupScreen(mMainMenu);
	mMainMenu = NULL;

	CleanupScreen(mTrophyScreen);
	mTrophyScreen = NULL;

	CleanupScreen(mStoryScreen);
	mStoryScreen = NULL;

	CleanupScreen(mAdventureScreen);
	mAdventureScreen = NULL;

	KillDialog(1);
	KillDialog(35);
}

// STUB: POPCAPGAME1 0x004081d0
void ThunderballApp::CopyBrickTextures()
{
}

// FUNCTION: POPCAPGAME1 0x0041c610
void ThunderballApp::CopyPegTextures()
{
    MemoryImage* aPegImage = (MemoryImage*)IMAGE_BALLPEG;

    if (mColorblind) {
        aPegImage = (MemoryImage*)IMAGE_BALLPEGCB;
    }

    if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp161,1225", true) && aPegImage->mWidth == 0x14) {
        MemoryImage* aPegImage2 = new MemoryImage();
        aPegImage2->Create(22, 176);
        aPegImage2->CopyAttributes(aPegImage);
        aPegImage2->mFilePath = aPegImage->mFilePath;
        Graphics g = Graphics((Image*)aPegImage2);
        int iVar2 = 1;
        int local_14 = 0;
        while (iVar2 < 0xb1) {
            Rect aRect = Rect(0, local_14, 0x14, 0x14);
            g.DrawImage(aPegImage, 1, iVar2, aRect);
            local_14 += 0x14;
            iVar2 += 0x16;
        }

        ReplaceImageById(mResourceManager, (mColorblind ? 1 : 0) + IMAGE_BALLPEG_ID, aPegImage2);
        aPegImage = aPegImage2;
    }

    Rect aRect = Rect((aPegImage->mWidth + (aPegImage->mWidth >> 0x1f & 7U) >> 3), aPegImage->mHeight, 0, 0);
    
    
    for (int i = 0; i < 9; i++) {
        if (gBallPegImage[i] != NULL) {
            delete gBallPegImage[i];
        }

        gBallPegImage[i] = new BlendedImage();
        gBallPegImage[i]->Create(aPegImage, aRect);
        aRect.mY += 1;
    }

    if (gBallPegImage[8] != NULL) {
        delete gBallPegImage[8];
    }
    
    gBallPegImage[8] = new BlendedImage();
    gBallPegImage[8]->Create((MemoryImage*)IMAGE_PEGSHADOW);

}

// FUNCTION: POPCAPGAME1 0x004302a0
void ThunderballApp::DialogButtonDepress(int theDialogId, int theButtonId)
{
	bool bVar1 = theButtonId == 1000;
	switch (theDialogId) {
	default:
		DoScrollOff(theDialogId);
		break;
	case 2:
		FinishConfirmDeleteUserDialog(bVar1);
		break;
	case 4:
		FinishConfirmMainMenuDialog(bVar1);
		break;
	case 5:
		FinishConfirmQuitDialog(bVar1);
		break;
	case 6:
		FinishConfirmRestartAdventureDialog(bVar1);
		break;
	case 7:
		FinishConfirmNewChallengeDialog(bVar1);
		break;
	case 8:
		FinishConfirmRestartLevelDialog(bVar1);
		break;
	case 10:
		FinishCreateUserDialog(bVar1);
		break;
	case 0xb:
		FinishNameErrorDialog(0xb);
		break;
	case 0x15:
		FinishNameErrorDialog(0x15);
	case 0xd:
		DoScrollOff(0xd);
		if (mBoard != NULL) {
			mBoard->mUnk0xea = false;
		}
		break;
	case 0xe:
		FinishTipDialog(bVar1);
		break;
	case 0x10:
		FinishHighScoreEntryDialog(bVar1);
		break;
	case 0x13:
		FinishOptionsDialog(bVar1, true);
		break;
	case 0x14:
		FinishRenameUserDialog(bVar1);
		break;
	case 0x18:
		FinishUserDialog(bVar1);
		break;
	case 0x1b:
	case 0x22:
		KillDialog(theDialogId);
		if (mBoard != NULL) {
			mBoard->Pause(false);
			mWidgetManager->SetFocus(mBoard);
			if (mBoard->mUnk0xc5 != 0) {
				mBoard->DoReplayFileDialog(false, -1, false);
			}
		}
		break;
	}
}

// STUB: POPCAPGAME1 0x0041d260
void ThunderballApp::DoConfirmDeleteUserDialog(const std::string& param_1)
{
}

// STUB: POPCAPGAME1 0x0042d7c0
void ThunderballApp::DoConfirmMainMenuDialog()
{
}

// FUNCTION: POPCAPGAME1 0x0041caa0
void ThunderballApp::DoConfirmNewChallengeDialog()
{
	// STRING: POPCAPGAME1 0x005d6b94
	SexyString aHeader = "New Challenge?";
	SexyString aLines = ModVal(
		0,
		// STRING: POPCAPGAME1 0x005d6ae8
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp193,2860",
		// STRING: POPCAPGAME1 0x005d6b30
		"Are you sure that you want to choose a new challenge? Your progress on this challenge will be lost."
	);
	ThunderDialog* aDialog = static_cast<ThunderDialog*>(DoDialog(
		7,
		true,
		aHeader,
		aLines,
		"",
		2
	));
	aDialog->mYesButton->mLabel = ModVal(
		0,
		// STRING: POPCAPGAME1 0x005d6a90
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp194,2864",
		// STRING: POPCAPGAME1 0x005d6ad8
		"New Challenge"
	);
	PositionDialog(
		aDialog,
		ModVal(
			0,
			// STRING: POPCAPGAME1 0x005d6a48
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp195,2865",
			400
		),
		false,
		-1
	);
	aDialog->DoScroll(true);
}

// FUNCTION: POPCAPGAME1 0x0041c960
void ThunderballApp::DoConfirmQuitDialog()
{
	ThunderDialog* aDialog = DoDialogScroll(
		5,
		true,
		// STRING: POPCAPGAME1 0x005d6a10
		"Quit Peggle?",
		// STRING: POPCAPGAME1 0x005d6a20
		"Are you sure you want to\nquit the game?",
		"",
		1
	);
	// STRING: POPCAPGAME1 0x005d69c8
	aDialog->mWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp191,2516", 0xeb);
	// STRING: POPCAPGAME1 0x005d6980
	aDialog->mHeight = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp192,2517", 0x118);
	aDialog->DoScroll(-1);
	aDialog->mUnk0x163 = false;
}

// FUNCTION: POPCAPGAME1 0x0041cc40
void ThunderballApp::DoConfirmRestartAdventureDialog()
{
	// STRING: POPCAPGAME1 0x005d6d78
	SexyString aHeader = "Restart Adventure?";
	SexyString aLines = ModVal(
		0,
		// STRING: POPCAPGAME1 0x005d6c98
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp196,2886",
		// STRING: POPCAPGAME1 0x005d6ce0
		"Are you sure that you want to ^00FF00^RESTART ADVENTURE?^oldclr^\n\nThis will put you all the way back to the first level and reset your score to zero."
	);
	ThunderDialog* aDialog = static_cast<ThunderDialog*>(DoDialog(
		8,
		true,
		aHeader,
		aLines,
		"",
		2
	));
	aDialog->mTextAlign = ModVal(
		0,
		// STRING: POPCAPGAME1 0x005d6c50
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp197,2889",
		-1
	);
	aDialog->mYesButton->mLabel = ModVal(
		0,
		// STRING: POPCAPGAME1 0x005d6bf0
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp198,2890",
		// STRING: POPCAPGAME1 0x005d6c38
		"Restart Adventure"
	);
	PositionDialog(
		aDialog,
		ModVal(
			0,
			// STRING: POPCAPGAME1 0x005d6ba8
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp199,2891",
			0x1cc
		),
		false,
		-1
	);
	aDialog->DoScroll(true);
}

// STUB: POPCAPGAME1 0x004310e0
void ThunderballApp::DoConfirmRestartLevelDialog(int param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0040c3b0
void ThunderballApp::DoCreateUserDialog()
{
	KillDialog(10);
	NewUserDialog* aDialog = new NewUserDialog(this, false, true, mCurProfile != NULL);
	int aPreferredHeight = aDialog->GetPreferredHeight(aDialog->mWidth);
	if (mPrimaryThreadId == 0) {
		aDialog->Resize(
			(mWidth - aDialog->mWidth) / 2,
			(mHeight - aPreferredHeight) / 2,
			aDialog->mWidth,
			aPreferredHeight
		);
	}
	else {
		PositionDialog(aDialog, aDialog->mWidth, false, -1);
	}

	if (mMainMenu != NULL) {
		aDialog->mX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp202,3030", 0x1e);
		aDialog->mY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp203,3031", 0x1e);
	}

	aDialog->DoScroll(true);
	AddDialog(10, aDialog);
}

// FUNCTION: POPCAPGAME1 0x00405f20
ThunderDialog* ThunderballApp::DoDialogScroll(
	int theId,
	bool isModal,
	const SexyString& theDialogHeader,
	const SexyString& theDialogLines,
	const SexyString& theDialogFooter,
	int theButtonMode
)
{
	ThunderDialog* aDialog = static_cast<ThunderDialog*>(SexyApp::DoDialog(
		theId,
		isModal,
		theDialogHeader,
		theDialogLines,
		theDialogFooter,
		theButtonMode
	));
	aDialog->DoScroll(true);
	return aDialog;
}

// FUNCTION: POPCAPGAME1 0x0040c210
void ThunderballApp::DoOptionsDialog()
{
	PauseBoard(true);
	OptionsDialog* aDialog = new OptionsDialog(mBoard != NULL);
	int theWidth;
	if (mBoard == NULL) {
		theWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp190,2442", 0x1b8);
	}
	else {
		theWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp189,2442", 0x1b8);
	}

	PositionDialog(aDialog, theWidth, false, -1);
	aDialog->DoScroll(true);
	AddDialog(0x13, aDialog);
}

// FUNCTION: POPCAPGAME1 0x0040c4d0
void ThunderballApp::DoRenameUserDialog(std::string& param_1)
{
	KillDialog(20);
	NewUserDialog* aDialog = new NewUserDialog(this, true, false, true);
	aDialog->GetPreferredHeight(aDialog->mWidth);
	PositionDialog(aDialog, aDialog->mWidth, false, -1);
	aDialog->SetName(param_1);
	aDialog->DoScroll(true);
	AddDialog(20, aDialog);
}

// STUB: POPCAPGAME1 0x0041ce00
bool ThunderballApp::DoReplaysExist()
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00405f60
void ThunderballApp::DoScrollOff(int param_1)
{
	ThunderDialog* dialog = static_cast<ThunderDialog*>(GetDialog(param_1));
	if (dialog != NULL) {
		dialog->DoScrollOff(true);
	}
}

// STUB: POPCAPGAME1 0x0041cee0
void ThunderballApp::DoTipDialog(int param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0042d7a0
void ThunderballApp::DoToMenu()
{
	KillDialog(13);
	ShowMainMenu();
}

// STUB: POPCAPGAME1 0x0040c2e0
void ThunderballApp::DoUserDialog()
{
}

// STUB: POPCAPGAME1 0x0042fe30
void ThunderballApp::EndHelpScreen()
{
}

// STUB: POPCAPGAME1 0x0042ff40
void ThunderballApp::EndUpsellScreen()
{
}

// STUB: POPCAPGAME1 0x0041d3d0
void ThunderballApp::FinishConfirmDeleteUserDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0042d980
void ThunderballApp::FinishConfirmMainMenuDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00429970
void ThunderballApp::FinishConfirmNewChallengeDialog(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004084a0
void ThunderballApp::FinishConfirmQuitDialog(bool param_1)
{
	if (param_1) {
		KillDialog(5);
		Shutdown();
	}
	else {
		DoScrollOff(5);
	}
}

// STUB: POPCAPGAME1 0x0041fc00
void ThunderballApp::FinishConfirmRestartAdventureDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004301c0
void ThunderballApp::FinishConfirmRestartLevelDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00430020
void ThunderballApp::FinishContinueDialog(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00427830
void ThunderballApp::FinishCreateUserDialog(bool param_1)
{
	NewUserDialog* aDialog = (NewUserDialog*) GetDialog(10);
	if (aDialog == NULL) {
		return;
	}

	std::string aName = aDialog->GetName();
	if (!param_1 || !aName.empty()) {
		if (mCurProfile == NULL && (!param_1 || aName.empty())) {
			DoDialogScroll(
				11,
				true,
				"Enter Your Name",
				"Please enter your name to create a new user profile for storing high score data and game progress.",
				"OK",
				3
			);
			return;
		}
		else if (!param_1) {
			DoScrollOff(10);
			return;
		}

		PlayerInfo* pProfile = mProfileMgr->AddProfile(aName);
		if (pProfile == NULL) {
			DoDialogScroll(
				11,
				true,
				"Name Conflict",
				"The name you entered is already being used.  Please enter a unique player name.",
				"OK",
				3
			);
		}
		else {
			mProfileMgr->Save();
			if (mCurProfile != NULL) {
				mCurProfile->SaveIfDirty();
			}

			mCurProfile = pProfile;

			if (mStatsMgr->mWelcomeLabel.empty()) {
				mStatsMgr->mWelcomeLabel = pProfile->mName;
			}

			mWidgetManager->MarkAllDirty();
			if (!aDialog->mUnk0x188) {
				DoScrollOff(24);
				DoScrollOff(10);
			}
			else {
				aDialog->DoApproved();
			}

			if (mMainMenu != NULL) {
				mMainMenu->SyncPlayerInfo();
				mWidgetManager->SetFocus(mMainMenu);
			}
		}
	}
	else {
		DoDialogScroll(
			11,
			true,
			"Enter Your Name",
			"Please enter your name to create a new user profile for storing high score data and game progress.",
			"OK",
			3
		);
	}
}

// STUB: POPCAPGAME1 0x0040c590
void ThunderballApp::FinishHighScoreEntryDialog(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00408500
void ThunderballApp::FinishNameErrorDialog(int param_1)
{
	DoScrollOff(param_1);
	NewUserDialog* aDialog = static_cast<NewUserDialog*>(GetDialog(param_1 != 11 ? 20 : 10));
	if (aDialog != NULL) {
		mWidgetManager->SetFocus(aDialog->mUnk0x180);
	}
}

// FUNCTION: POPCAPGAME1 0x0041c840
void ThunderballApp::FinishOptionsDialog(bool param_1, bool param_2)
{
	OptionsDialog* aDialog = static_cast<OptionsDialog*>(GetDialog(0x13));
	if (aDialog != NULL) {
		if (param_1) {
			SwitchScreenMode(!aDialog->mFullscreenCheckbox->mChecked, true, false);
			EnableCustomCursors(aDialog->mCustomCursorsCheckbox->mChecked);
			mCurProfile->SetColorblind(aDialog->mColorblindModeCheckbox->mChecked);

			if (SetColorblind(aDialog->mColorblindModeCheckbox->mChecked) && mBoard != NULL) {
				mBoard->SyncColorblind();
			}

			ClearUpdateBacklog(false);
		}

		if (param_2) {
			aDialog->DoScrollOff(true);
		}
		else {
			KillDialog(0x13);
		}
		PauseBoard(false);
	}
}

// FUNCTION: POPCAPGAME1 0x00427b90
void ThunderballApp::FinishRenameUserDialog(bool param_1)
{
	if (!param_1) {
		DoScrollOff(20);
		return;
	}

	UserDialog* aUserDialog = static_cast<UserDialog*>(GetDialog(24));
	NewUserDialog* aRenameDialog = static_cast<NewUserDialog*>(GetDialog(20));
	if (aUserDialog == NULL || aRenameDialog == NULL) {
		return;
	}

	std::string anOldName = aUserDialog->GetSelName();
	std::string aNewName = aRenameDialog->GetName();
	if (!aNewName.empty()) {
		mCurProfile->SaveIfDirty();
		bool isCurProfile = mProfileMgr->GetProfile(anOldName) == mCurProfile;
		if (!mProfileMgr->RenameProfile(anOldName, aNewName)) {
			DoDialogScroll(
				21,
				true,
				// STRING: POPCAPGAME1 0x005d7e70
				"Name Conflict",
				// STRING: POPCAPGAME1 0x005d7e80
				"The name you entered is already being used.  Please enter a unique player name.",
				// STRING: POPCAPGAME1 0x005d7f44
				"OK",
				3
			);
		}
		else {
			mProfileMgr->Save();
			if (isCurProfile) {
				mCurProfile = mProfileMgr->GetProfile(aNewName);
			}

			aUserDialog->FinishRenameUser(&aNewName);
			mWidgetManager->MarkAllDirty();
			DoScrollOff(20);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004084e0
void ThunderballApp::FinishTipDialog(bool param_1)
{
	if (GetDialog(14) != NULL) {
		DoScrollOff(14);
	}
}

// STUB: POPCAPGAME1 0x00427720
void ThunderballApp::FinishUserDialog(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00405bf0
int ThunderballApp::GetCurLevel()
{
	return mUnk0x764 * 5 + mUnk0x768;
}

// FUNCTION: POPCAPGAME1 0x00405ba0
LevelInfo* ThunderballApp::GetCurLevelInfo()
{
	StageInfo* aStageInfo = mStageMgr->GetStageInfo(mUnk0x764);
	if (aStageInfo == NULL) {
		return NULL;
	}

	return aStageInfo->GetLevelInfo(mUnk0x768);
}

// FUNCTION: POPCAPGAME1 0x00405960
long double ThunderballApp::GetFeverVolume()
{
	return mFeverVolume;
}

// FUNCTION: POPCAPGAME1 0x00405ae0
DDImage* ThunderballApp::GetImage(const std::string& theFileName, bool commitBits = true)
{
	if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp160,1205", 0) != 0) {
		DDImage* anImage = SexyApp::GetImage(theFileName, false);
		if (anImage != NULL) {
			MakeGrayscale(anImage);
			if (commitBits) {
				anImage->CommitBits();
			}
		}
		return anImage;
	}
	return SexyApp::GetImage(theFileName, commitBits);
}

// FUNCTION: POPCAPGAME1 0x00405bd0
int ThunderballApp::GetMaxLevel()
{
	if (mCurProfile == NULL) {
		return 0;
	}

	return mCurProfile->GetMaxLevel();
}

// FUNCTION: POPCAPGAME1 0x00405d40
int ThunderballApp::GetMaxLockedLevel()
{
	if (!IsRegistered()) {
		if (mUnk0x834 == 1) {
			return 3;
		}
		if (mUnk0x834 == 3 || mUnk0x834 == 5) {
			return 4;
		}
		if (mUnk0x834 == 4 || mUnk0x834 == 2) {
			return 0;
		}
	}

	return 1000;
}

// FUNCTION: POPCAPGAME1 0x00405cf0
int ThunderballApp::GetMaxLockedStage()
{
	if (!IsRegistered()) {
		if (mUnk0x834 == 1) {
			return 0;
		}
		if (mUnk0x834 == 2) {
			return 1;
		}
		if (mUnk0x834 == 3) {
			return 2;
		}
		if (mUnk0x834 == 4 || mUnk0x834 == 5) {
			return 3;
		}
	}

	return 1000;
}

// FUNCTION: POPCAPGAME1 0x00405e30
int ThunderballApp::GetMaxUnlockedCharacter()
{
	if (IsRegistered()) {
		return 20;
	}
	if (mUnk0x834 == 3) {
		return 2;
	}
	if (mUnk0x834 == 5) {
		return 3;
	}

	return 20;
}

// FUNCTION: POPCAPGAME1 0x00405970
int ThunderballApp::GetMusicOrder(int param_1)
{
	BassMusicInterface* aMusicInterface = dynamic_cast<BassMusicInterface*>(mMusicInterface);
	if (aMusicInterface == NULL) {
		return -1;
	}
	int aMusicOrder = aMusicInterface->GetMusicOrder(param_1);
	if (aMusicOrder != -1) {
		return aMusicOrder >> 0x10;
	}
	return -1;
}

// STUB: POPCAPGAME1 0x00427570
void ThunderballApp::IncLevel(int param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004057f0
int ThunderballApp::IsExpired()
{
	if (mUnk0x834 == 0 && mRegistrationControl != NULL) {
		int trialAge = mRegistrationControl->GetTrialAge();
		int trialDuration = mRegistrationControl->GetTrialDuration();
		if (trialAge >= trialDuration && !mRegistrationControl->IsRegistered()) {
			return true;
		}
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00405c60
bool ThunderballApp::IsLevelDemoLocked(int param_1, int param_2)
{
	if (IsRegistered()) {
		return false;
	}

	int trialType = mUnk0x834;
	if (mCurProfile == NULL ||
		(trialType == 1 && param_1 == 0 && param_2 >= 4) ||
		(trialType == 2 && param_1 == 1 && param_2 >= 1) ||
		(trialType == 1 && param_1 >= 1) ||
		(trialType == 2 && param_1 >= 2) ||
		(trialType == 3 && param_1 >= 3) ||
		(trialType == 5 && param_1 >= 4) ||
		(trialType == 4 && param_1 == 3 && param_2 >= 1) ||
		(trialType == 4 && param_1 >= 4)) {
		return true;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00405860
int ThunderballApp::IsLevelLockedTrial()
{
	if (mUnk0x834 == 1 || mUnk0x834 == 2 || mUnk0x834 == 3 || mUnk0x834 == 4 || mUnk0x834 == 5) {
		return true;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x004057d0
bool ThunderballApp::IsRegistered()
{
	if (mRegistrationControl != NULL) {
		return mRegistrationControl->IsRegistered();
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x00405d90
bool ThunderballApp::IsTrialOver()
{
	if (IsRegistered()) {
		return false;
	}
	if ((unsigned char) IsExpired()) {
		return true;
	}

	if (mCurProfile == NULL ||
		(mUnk0x834 == 1 && mCurProfile->mUnk0x30 == 0 && mCurProfile->mUnk0x34 >= 4) ||
		(mUnk0x834 == 2 && mCurProfile->mUnk0x30 == 1 && mCurProfile->mUnk0x34 >= 1) ||
		(mUnk0x834 == 1 && mCurProfile->mUnk0x30 >= 1) ||
		(mUnk0x834 == 2 && mCurProfile->mUnk0x30 >= 2) ||
		(mUnk0x834 == 3 && mCurProfile->mUnk0x30 >= 3) ||
		(mUnk0x834 == 5 && mCurProfile->mUnk0x30 >= 4) ||
		(mUnk0x834 == 4 && mCurProfile->mUnk0x30 == 3 && mCurProfile->mUnk0x34 >= 1) ||
		(mUnk0x834 == 4 && mCurProfile->mUnk0x30 >= 4)) {
		return true;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00405740
void ThunderballApp::LoadLevelMusic()
{
	mUnk0x779 = false;
	mUnk0x780 = 1;
	mUnk0x784 = 9;
}

// STUB: POPCAPGAME1 0x004233b0
void ThunderballApp::LoadMusic(int param_1, const std::string& param_2)
{
}

// FUNCTION: POPCAPGAME1 0x00405c00
bool ThunderballApp::OnMaxLevel()
{
	if (mCurProfile == NULL) {
		return false;
	}

	return mCurProfile->GetMaxLevel() == GetCurLevel();
}

// FUNCTION: POPCAPGAME1 0x00405c30
void ThunderballApp::PauseBoard(bool param_1)
{
	if (mBoard != NULL) {
		mBoard->Pause(param_1);
	}
	if (mUpsellScreen != NULL) {
		mUpsellScreen->Pause(param_1);
	}
}

// STUB: POPCAPGAME1 0x0040bdd0
void ThunderballApp::PlayMusic(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x004294a0
void ThunderballApp::RemoveBoard()
{
}

// FUNCTION: POPCAPGAME1 0x00405b50
void ThunderballApp::ResetTwoPlayerStats()
{
	mUnk0x880 = 0;
	mUnk0x87c = 0;
	mUnk0x888 = 0;
	mUnk0x884 = 0;
	mUnk0x890 = 0;
	mUnk0x88c = 0;
	mUnk0x894 = -1;
	mUnk0x898 = 0;
	mTwoPlayerStats[0].Reset();
	mTwoPlayerStats[1].Reset();
}

// FUNCTION: POPCAPGAME1 0x004234c0
void ThunderballApp::ScrollOn(Widget* theWidget)
{
	if (mWidgetMover != NULL) {
		mWidgetMover->ScrollOn(theWidget, mRegCode.size());
		ClearUpdateBacklog(false);
	}
}

// FUNCTION: POPCAPGAME1 0x0041c810
bool ThunderballApp::SetColorblind(bool param_1)
{
	if (param_1 == mColorblind) {
		return false;
	}

	mColorblind = param_1;
	CopyBrickTextures();
	CopyPegTextures();
	return true;
}

// might not exist?
// STUB: POPCAPGAME1 0x
void ThunderballApp::SetExpired()
{
}

// FUNCTION: POPCAPGAME1 0x00405940
void ThunderballApp::SetFeverVolume(double param_1)
{
	mFeverVolume = param_1;
	if (mUnk0x77c == 0) {
		SyncOdeVolume();
	}
}

// FUNCTION: POPCAPGAME1 0x004059c0
void ThunderballApp::SetMusicIntensityIncreasePending(int param_1)
{
	if (param_1 <= 6) {
		int currentOffset = mUnk0x77c - 1;
		mUnk0x77c += (currentOffset / 6) * 6 - currentOffset - 2 + param_1;

		int musicOrder = GetMusicOrder(1);
		if (musicOrder != -1) {
			mMusicIntensityIncreasePending = true;
			mPendingMusicOrder = musicOrder;
		}
	}
}

// STUB: POPCAPGAME1 0x0040d2c0
void ThunderballApp::SetMusicSpeed(float param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00405900
void ThunderballApp::SetMusicVolume(double theVolume)
{
	if (mUnk0x77c != 0) {
		SexyApp::SetMusicVolume(theVolume);
	}
}

// FUNCTION: POPCAPGAME1 0x00405920
void ThunderballApp::SetSfxVolume(double theVolume)
{
	SexyApp::SetSfxVolume(theVolume);
}

// FUNCTION: POPCAPGAME1 0x00429890
void ThunderballApp::ShowAdventureScreen()
{
	CheckPlayMusic(false);
	CheckScrollOff(mMainMenu, 1, true);
	CleanupScreens(true);

	mAdventureScreen = new AdventureScreen(this);

	mAdventureScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mAdventureScreen);
	mWidgetManager->SetFocus(mAdventureScreen);
	ScrollOn(mAdventureScreen);
}

// FUNCTION: POPCAPGAME1 0x0042f860
void ThunderballApp::ShowBoard(bool param_1, bool param_2)
{
	CheckScrollOff(mLoadingScreen, 1, true);
	CheckScrollOff(mMainMenu, 1, true);
	CheckScrollOff(mLevelScreen, 1, true);
	CheckScrollOff(mTrophyScreen, 1, true);
	CheckScrollOff(mHelpScreen, 1, true);
	CheckScrollOff(mStoryScreen, 1, true);
	CheckScrollOff(mAdventureScreen, 1, true);
	CleanupScreens(true);

	if (mCurProfile != NULL) {
		SetColorblind(mCurProfile->mUnk0x60);
	}

	mBoard = new Board(this);

	mBoard->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mBoard);
	mWidgetManager->SetFocus(mBoard);
	ScrollOn(mBoard);

	if (param_2) {
		mBoard->Reset();
	}
}

// STUB: POPCAPGAME1 0x00423540
void ThunderballApp::ShowHelpScreen(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042d350
void ThunderballApp::ShowLevelScreen(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004296c0
void ThunderballApp::ShowLoadingScreen()
{
	CheckPlayMusic(false);
	CleanupScreens(true);

	mLoadingScreen = new LoadingScreen(this);
	mLoadingScreen->Resize(0, 0, mWidth, mHeight);

	mWidgetManager->AddWidget(mLoadingScreen);
	mWidgetManager->SetFocus(mLoadingScreen);
}

// STUB: POPCAPGAME1 0x0042d480
void ThunderballApp::ShowMainMenu()
{
	mSoundManager->StopAllSounds();
	CheckPlayMusic(false);
	ResetTwoPlayerStats();

	MainMenu* aMainMenu = mMainMenu;
	if (aMainMenu != 0) {
		mMainMenu = NULL;
		CleanupScreens(true);
		mWidgetManager->SetFocus(mMainMenu);
		return;
	}

	mUnk0x750 = 3;
	CheckScrollOff(this->mLoadingScreen, 1, 1);
	CheckScrollOff(this->mLevelScreen, 2, 1);
	CheckScrollOff(this->mTrophyScreen, 2, 1);
	CheckScrollOff(this->mStoryScreen, 2, 1);
	CheckScrollOff(this->mAdventureScreen, 2, 1);
	CheckScrollOff(this->mBoard, 2, 1);

	ThunderDialog* aDialog = static_cast<ThunderDialog*>(GetDialog(0x13));
	if (aDialog != NULL) {
		aDialog->mUnk0x158 = 0x28;
	}

	CleanupScreens(true);
	FinishOptionsDialog(true, true);
	if (!TryExpire(false)) {
		mMainMenu = new MainMenu(this);
		mMainMenu->Resize(0, 0, mWidth, mHeight);
		mWidgetManager->AddWidget(mMainMenu);
		mWidgetManager->SetFocus(mMainMenu);
		ScrollOn(mMainMenu);
		BringDialogsToFront();
		if (mCurProfile == NULL) {
			DoCreateUserDialog();
		}
	}
}

// STUB: POPCAPGAME1 0x0042fb00
void ThunderballApp::ShowReplay(bool param_1)
{
	printf("ThunderballApp::ShowReplay called with %d\n", param_1);
}

// FUNCTION: POPCAPGAME1 0x0042d670
void ThunderballApp::ShowStoryScreen(bool param_1, bool param_2)
{
	if (!TryExpire(false)) {
		CheckPlayMusic(false);
		if (mCurProfile != NULL) {
			mCurProfile->mUnk0x61 = false;
			mCurProfile->mUnk0xec = true;
		}

		CheckScrollOff(mBoard, 2, true);
		CheckScrollOff(mMainMenu, 1, true);
		CleanupScreens(true);

		mStoryScreen = new StoryScreen(this, param_1, param_2);

		mStoryScreen->Resize(0, 0, mWidth, mHeight);
		mWidgetManager->AddWidget(mStoryScreen);
		mWidgetManager->SetFocus(mStoryScreen);

		ScrollOn(mStoryScreen);
	}
}

// STUB: POPCAPGAME1 0x00429780
void ThunderballApp::ShowTrophyScreen()
{
}

// STUB: POPCAPGAME1 0x004294f0
bool ThunderballApp::ShowUpsellScreen(bool param_1, bool param_2)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x0042ff70
void ThunderballApp::StartAdventureGame()
{
	if (mCurProfile != NULL) {
		if (mCurProfile->JustBeatAdventure()) {
			mCurProfile->RestartAdventure();
		}
	}

	PlayerInfo* aProfile = mCurProfile;
	mGameMode = GameMode::ADVENTURE;
	if (aProfile == NULL) {
		mUnk0x764 = 0;
		mUnk0x768 = 0;
	}
	else {
		int stage = aProfile->mUnk0x30;
		if (stage < 0) {
			stage = 0;
		} else if (10 < stage) {
			stage = 10;
		}
		mUnk0x764 = stage;

		int level = aProfile->mUnk0x34;
		if (level < 0) {
			level = 0;
		} else if (5 < level) {
			level = 5;
		}
		mUnk0x768 = level;
	}

	if (aProfile != NULL && aProfile->mUnk0x61 && mUnk0x768 == 0) {
		ShowStoryScreen(false, false);
	} else {
        ShowBoard(true, false);
    }
}

// FUNCTION: POPCAPGAME1 0x004058b0
void ThunderballApp::SyncOdeVolume()
{
	if (mMusicInterface != NULL) {
		mMusicInterface->SetVolume(mMuteCount > 0 ? 0.0 : mFeverVolume);
	}
}

// FUNCTION: POPCAPGAME1 0x0042d270
bool ThunderballApp::TryExpire(bool param_1)
{
	if (CheckCanExpire()) {
		mUnk0x83A = true;
		if (GetDialog(14) != NULL) {
			FinishTipDialog(true);
			return false;
		}

		return ShowUpsellScreen(param_1, false);
	}
	else {
		mUnk0x83A = false;
		return false;
	}
}

// FUNCTION: POPCAPGAME1 0x0042d320
bool ThunderballApp::TryPlayUpsell()
{
	if (!IsRegistered() && IsTrialOver()) {
		ShowUpsellScreen(false, false);
		return true;
	}

	return false;
}

// STUB: POPCAPGAME1 0x0042feb0
int ThunderballApp::TryShowNewTrophy()
{
	return 0;
}

// STUB: POPCAPGAME1 0x0040bdd0
void ThunderballApp::UpdateMusic()
{
}

// STUB: POPCAPGAME1 0x0042f9d0
void ThunderballApp::ViewReplays()
{
}

// STUB: POPCAPGAME1 0x
void ThunderballApp::GotFocus()
{
	SexyApp::GotFocus();
}

// FUNCTION: POPCAPGAME1 0x00405890
bool ThunderballApp::DebugKeyDown(int theKey)
{
	if (SexyApp::DebugKeyDown(theKey)) {
		return true;
	}

	return false;
}

// STUB: POPCAPGAME1 0x
void ThunderballApp::InitHook()
{
}

// FUNCTION: POPCAPGAME1 0x00408430
bool ThunderballApp::IsAltKeyUsed(WPARAM wParam)
{
	if (SexyApp::IsAltKeyUsed(wParam)) {
		return true;
	}
	if (mBoard != NULL) {
		return mBoard->IsAltKeyUsed(wParam);
	}

	return false;
}

// STUB: POPCAPGAME1 0x
void ThunderballApp::LoadingThreadCompleted()
{
	SexyApp::LoadingThreadCompleted();
}

// FUNCTION: POPCAPGAME1 0x00421a70
void ThunderballApp::LoadingThreadProc()
{
	OutputDebugStringA("LoadingThreadProc started\n");
	const char* aGroups[] = {
		"LoadingThread",
		"Game",
		"MainMenu",
		"LevelSelect",
		"Help",
		"Interface",
		"IP",
		"Dialog",
		"Character",
		"LuckySpin",
		"Upsell"
	};

	mNumLoadingThreadTasks = 0;
	for (int i = 0; i < 11; i++) {
		mNumLoadingThreadTasks += mResourceManager->GetNumResources(aGroups[i]);
	}

	LoadTimer aLoadTimer;
	if (mLoadingScreen->mBallBounced) {
		aLoadTimer.Begin();
	}

	for (int i = 0; i < 11; i++) {
		mResourceManager->StartLoadResources(aGroups[i]);

		while (mResourceManager->LoadNextResource()) {
			mCompletedLoadingThreadTasks++;
			if (mShutdown) {
				return;
			}
		}

		if (mResourceManager->HadError()) {
			ShowResourceError(false);
			mLoadingFailed = true;
			return;
		}

		if (!ExtractResourcesByName(mResourceManager, aGroups[i])) {
			ShowResourceError(false);
			mLoadingFailed = true;
			return;
		}
	}

	CopyBrickTextures();
	CopyPegTextures();
	// MakeFeverStars();
}

// FUNCTION: POPCAPGAME1 0x00408470
void ThunderballApp::LostFocus()
{
	SexyApp::LostFocus();
	if (mBoard != NULL && mBoard->mUnk0x130 == 0) {
		PauseBoard(true);
	}
}

// STUB: POPCAPGAME1 0x004057c0
void ThunderballApp::MakeWindow()
{
	SexyApp::MakeWindow();
}

// FUNCTION: POPCAPGAME1 0x0040c0a0
Dialog* ThunderballApp::NewDialog(
	int theDialogId,
	bool isModal,
	const SexyString& theDialogHeader,
	const SexyString& theDialogLines,
	const SexyString& theDialogFooter,
	int theButtonMode
)
{
	ThunderDialog* aDialog =
		new ThunderDialog(theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode);
	PositionDialog(aDialog, 0x15e, false, -1);
	return static_cast<Dialog*>(aDialog);
}

// STUB: POPCAPGAME1 0x0041c400
void ThunderballApp::ReadFromRegistry()
{
	SexyApp::ReadFromRegistry();
}

// FUNCTION: POPCAPGAME1 0x0042d2d0
void ThunderballApp::UpdateFrames()
{
	SexyApp::UpdateFrames();

	if ((mUpdateCount % 100 == 0) && (mUnk0x839 != false)) {
		TryExpire(mUnk0x839 == false);
	}

	mWidgetMover->Update();
	UpdateMusic();
}

// STUB: POPCAPGAME1 0x00427380
void ThunderballApp::WriteToRegistry()
{
	if (!IsScreenSaver()) {
		SexyApp::WriteToRegistry();

		// STRING: POPCAPGAME1 0x005d692c
		RegistryWriteInteger("FeverVolume", mFeverVolume * 100.0);

		// STRING: POPCPAGAME1 0x005d692c
		RegistryWriteBoolean("ShouldShowUpsellButton", mShouldShowUpsellButton);

		// STRING: POPCAPGAME1 0x005d6908
		RegistryWriteInteger("MaxStage", mMaxStage);
		// STRING: POPCAPGAME1 0x005d7e64
		RegistryWriteInteger("MaxLevel", mMaxLevel);

		/*if (mCurUser != NULL) {
			// STRING: POPCAPGAME1 0x005d7e5c
			RegistryWriteString("CurUser", mCurUser);
		}*/
	}
}

// STUB: POPCAPGAME1 0x0042d180
void ThunderballApp::Shutdown()
{
	SexyApp::Shutdown();

	CleanupScreens(true);
	mWidgetMover->Clear();

	if (mWinCloseButton != NULL) {
		mWidgetManager->RemoveWidget(mWinCloseButton);
	}

	if (mWinMinimizeButton != NULL) {
		mWidgetManager->RemoveWidget(mWinMinimizeButton);
	}

	if (mWinUnmaxButton != NULL) {
		mWidgetManager->RemoveWidget(mWinUnmaxButton);
	}
}

// FUNCTION: POPCAPGAME1 0x00430680
void ThunderballApp::ShutdownHook()
{
	SexyApp::ShutdownHook();
	if (mUpsellScreen != NULL && IsRegistered()) {
		if (mUnk0x83b) {
			mUnk0x83b = false;
			StartAdventureGame();
		}
		else {
			ShowMainMenu();
		}
		return;
	}

	mUnk0x799 = true;
	if (mBoard != NULL && mBoard->mUnk0x130 == 0) {
		PauseBoard(false);
	}
}

// STUB: POPCAPGAME1 0x00405e70
void ThunderballApp::SwitchScreenMode(bool wantWindowed, bool is3d, bool force)
{
	SexyApp::SwitchScreenMode(wantWindowed, is3d, force);
}

// FUNCTION: POPCAPGAME1 0x00405840
bool ThunderballApp::meth_0x405840()
{
	if (mRegistrationControl != NULL) {
		return mRegistrationControl->IsWindowValid();
	}
	return false;
}
