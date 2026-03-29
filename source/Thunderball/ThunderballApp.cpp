#include "ThunderballApp.h"

#include "LoadTimer.h"
#include "LoadingScreen.h"
#include "MainMenu.h"
#include "NewUserDialog.h"
#include "PlayerInfo.h"
#include "ProfileMgr.h"
#include "Res.h"
#include "StatsMgr.h"
#include "ThunderCommon.h"
#include "ThunderDialog.h"
#include "WidgetMover.h"
#include "OptionsDialog.h"

#include <SexyAppFramework/BassMusicInterface.h>
#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/Debug.h>
#include <SexyAppFramework/ResourceManager.h>
#include <SexyAppFramework/SWTri.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/WidgetManager.h>

// GLOBAL: POPCAPGAME1 0x00650a55
static bool mColorblind;

using namespace Sexy;

// STUB: POPCAPGAME1 0x00426f10
ThunderballApp::ThunderballApp()
{
	mTitle = "Peggle Deluxe " + mProductVersion;
	mRegKey = "PopCap\\Peggle";

	mWidgetMover = new WidgetMover();
	mProfileMgr = new ProfileMgr();
	mCurProfile = NULL;
	mLoadingScreen = NULL;
	mMainMenu = NULL;
	mBoard = NULL;

	mWidth = 800;
	mHeight = 600;
	mAutoEnable3D = true;
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

// STUB: POPCAPGAME1 0x00405f90
void ThunderballApp::ButtonDepress(int param_1)
{
}

// STUB: POPCAPGAME1 0x00405a50
int ThunderballApp::CheckCanExpire()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405aa0
void ThunderballApp::CheckMaxStage()
{
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
	/*if (param_1) {
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
	mLevelScreen = NULL;*/

	CleanupScreen(mLoadingScreen);
	mLoadingScreen = NULL;

	CleanupScreen(mMainMenu);
	mMainMenu = NULL;

	/*CleanupScreen(mTrophyScreen);
	mTrophyScreen = NULL;

	CleanupScreen(mStoryScreen);
	mStoryScreen = NULL;

	CleanupScreen(mAdventureScreen);
	mAdventureScreen = NULL;*/

	KillDialog(1);
	KillDialog(35);
}

// STUB: POPCAPGAME1 0x004081d0
void ThunderballApp::CopyBrickTextures()
{
}

// STUB: POPCAPGAME1 0x0041c610
void ThunderballApp::CopyPegTextures()
{
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
			/*if (mBoard != NULL) {
				mBoard->mUnk0xea = 0;
			}*/
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
			/*if (mBoard != NULL) {
				mBoard->Pause(false);
				mWidgetManager->SetFocus(mBoard);
				if (mBoard->mUnk0xc5 != 0) {
					mBoard->DoReplayFileDialog();2
				}
			}*/
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

// STUB: POPCAPGAME1 0x0041caa0
void ThunderballApp::DoConfirmNewChallengeDialog()
{
}

// STUB: POPCAPGAME1 0x0041c960
void ThunderballApp::DoConfirmQuitDialog()
{
}

// STUB: POPCAPGAME1 0x0041cc40
void ThunderballApp::DoConfirmRestartAdventureDialog()
{
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
	ThunderDialog* aDialog =
		new ThunderDialog(theId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode);
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
	} else {
		theWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderballApp.cpp189,2442", 0x1b8);
	}

	PositionDialog(aDialog, theWidth, false, -1);
	aDialog->DoScroll(true);
	AddDialog(0x13, aDialog);
}

// STUB: POPCAPGAME1 0x0040c4d0
void ThunderballApp::DoRenameUserDialog(std::string& param_1)
{
}

// STUB: POPCAPGAME1 0x0041ce00
bool ThunderballApp::DoReplaysExist()
{
	return false;
}

// STUB: POPCAPGAME1 0x00405f60
void ThunderballApp::DoScrollOff(int param_1)
{
}

// STUB: POPCAPGAME1 0x0041cee0
void ThunderballApp::DoTipDialog(int param_1)
{
}

// STUB: POPCAPGAME1 0x0042d7a0
void ThunderballApp::DoToMenu()
{
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

// STUB: POPCAPGAME1 0x004084a0
void ThunderballApp::FinishConfirmQuitDialog(bool param_1)
{
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

// STUB: POPCAPGAME1 0x00408500
void ThunderballApp::FinishNameErrorDialog(int param_1)
{
}

// STUB: POPCAPGAME1 0x0041c840
void ThunderballApp::FinishOptionsDialog(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00427b90
void ThunderballApp::FinishRenameUserDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004084e0
void ThunderballApp::FinishTipDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00427720
void ThunderballApp::FinishUserDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00405bf0
int ThunderballApp::GetCurLevel()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405ba0
int ThunderballApp::GetCurLevelInfo()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405960
long double ThunderballApp::GetFeverVolume()
{
	return 0.0L;
}

// STUB: POPCAPGAME1 0x00405ae0
DDImage* ThunderballApp::GetImage(const std::string& theFileName, bool commitBits = true)
{
	return SexyApp::GetImage(theFileName, commitBits);
}

// STUB: POPCAPGAME1 0x00405bd0
int ThunderballApp::GetMaxLevel()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405d40
int ThunderballApp::GetMaxLockedLevel()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405cf0
int ThunderballApp::GetMaxLockedStage()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00405e30
int ThunderballApp::GetMaxUnlockedCharacter()
{
	return 0;
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

// STUB: POPCAPGAME1 0x004057f0
bool ThunderballApp::IsExpired()
{
	return false;
}

// STUB: POPCAPGAME1 0x00405c60
bool ThunderballApp::IsLevelDemoLocked(int param_1, int param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x00405860
bool ThunderballApp::IsLevelLockedTrial()
{
	return false;
}

// STUB: POPCAPGAME1 0x004057d0
bool ThunderballApp::IsRegistered()
{
	return false;
}

// STUB: POPCAPGAME1 0x00405d90
bool ThunderballApp::IsTrialOver()
{
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

// STUB: POPCAPGAME1 0x00405c00
bool ThunderballApp::OnMaxLevel()
{
	return false;
}

// STUB: POPCAPGAME1 0x00405c30
void ThunderballApp::PauseBoard(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040bdd0
void ThunderballApp::PlayMusic(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x004294a0
void ThunderballApp::RemoveBoard()
{
}

// STUB: POPCAPGAME1 0x00405b50
void ThunderballApp::ResetTwoPlayerStats()
{
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
	if (mMainMenu == 0) {
		SyncOdeVolume();
	}
}

// STUB: POPCAPGAME1 0x004059c0
void ThunderballApp::SetMusicIntensityIncreasePending(int param_1)
{
}

// STUB: POPCAPGAME1 0x0040d2c0
void ThunderballApp::SetMusicSpeed(float param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00405900
void ThunderballApp::SetMusicVolume(double theVolume)
{
	if (mMainMenu != 0) {
		SexyApp::SetMusicVolume(theVolume);
	}
}

// FUNCTION: POPCAPGAME1 0x00405920
void ThunderballApp::SetSfxVolume(double theVolume)
{
	SexyApp::SetSfxVolume(theVolume);
}

// STUB: POPCAPGAME1 0x00429890
void ThunderballApp::ShowAdventureScreen()
{
}

// STUB: POPCAPGAME1 0x0042f860
void ThunderballApp::ShowBoard(bool param_1, bool param_2)
{
	printf("ThunderballApp::ShowBoard called with %d, %d\n", param_1, param_2);
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
	/*CheckScrollOff(this,this->mLevelScreen,2,1);
	CheckScrollOff(this,this->mTrophyScreen,2,1);
	CheckScrollOff(this,this->mStoryScreen,2,1);
	CheckScrollOff(this,this->mAdventureScreen,2,1);
	CheckScrollOff(this,this->mBoard,2,1);*/

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

// STUB: POPCAPGAME1 0x0042d670
void ThunderballApp::ShowStoryScreen(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00429780
void ThunderballApp::ShowTrophyScreen()
{
}

// STUB: POPCAPGAME1 0x004294f0
void ThunderballApp::ShowUpsellScreen()
{
}

// STUB: POPCAPGAME1 0x0042ff70
void ThunderballApp::StartAdventureGame()
{
}

// STUB: POPCAPGAME1 0x004058b0
void ThunderballApp::SyncOdeVolume()
{
}

// STUB: POPCAPGAME1 0x0042d270
bool ThunderballApp::TryExpire(bool param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0042d320
bool ThunderballApp::TryPlayUpsell()
{
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

// STUB: POPCAPGAME1 0x00430680
void ThunderballApp::GotFocus()
{
	SexyApp::GotFocus();
}

// STUB: POPCAPGAME1 0x00405890
bool ThunderballApp::DebugKeyDown(int theKey)
{
	return SexyApp::DebugKeyDown(theKey);
}

// STUB: POPCAPGAME1 0x
void ThunderballApp::InitHook()
{
}

// STUB: POPCAPGAME1 0x00408430
bool ThunderballApp::IsAltKeyUsed(WPARAM wParam)
{
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

// STUB: POPCAPGAME1 0x00408470
void ThunderballApp::LostFocus()
{
	SexyApp::LostFocus();
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

// STUB: POPCAPGAME1 0x
void ThunderballApp::ShutdownHook()
{
	SexyApp::ShutdownHook();
}

// STUB: POPCAPGAME1 0x00405e70
void ThunderballApp::SwitchScreenMode(bool wantWindowed, bool is3d, bool force)
{
	SexyApp::SwitchScreenMode(wantWindowed, is3d, force);
}

// STUB: POPCAPGAME1 0x00405840
bool ThunderballApp::meth_0x405840()
{
	return false;
}
