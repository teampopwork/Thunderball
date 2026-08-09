#ifndef __THUNDERBALLAPP_H__
#define __THUNDERBALLAPP_H__

#include "ConstEnums.h"
#include "GameStats.h"

#include <SexyAppFramework/SexyApp.h>
#include <SexyAppFramework/Image.h>

// GLOBAL: POPCAPGAME1 0x00650a55
extern bool mColorblind;


namespace Sexy
{
class WidgetMover;
class PlayerInfo;
class ButtonWidget;
class LoadingScreen;
class TrophyScreen;
class StoryScreen;
class AdventureScreen;
class LevelScreen;
class HelpScreen;
class UpsellScreen;
class MainMenu;
class ThunderDialog;
class ProfileMgr;
class StatsMgr;
class StageMgr;
class LevelInfo;
class CharacterMgr;
class TrophyMgr;
class HighScoreMgr;
class ImageMgr;
class Board;
class BlendedImage;

class RegistrationControl {
public:
	int mUnk0x0;             // +0x0
	HWND mWindow;            // +0x4
	char mPadding0x8[8];     // +0x8
	bool mWindowValid;       // +0x10
	char mPadding0x11[0x1b]; // +0x11
	UINT mQueryMessage;      // +0x2c

	int GetTrialAge();
	int GetTrialDuration();
	bool IsRegistered();
	bool IsWindowValid();
};

// GLOBAL: POPCAPGAME1 0x0065057c
extern BlendedImage* gBallPegImage[9];

// VTABLE: POPCAPGAME1 0x005d7cb8
class ThunderballApp : public SexyApp {
public:
	char mPadding0x728[0x28];           // +0x728
	int mUnk0x750;                     // +0x750 // part of SexyApp?
	char mPadding0x754[0xc];            // +0x754
	GameMode mGameMode;                // +0x760
	int mUnk0x764;                     // +0x764
	int mUnk0x768;                     // +0x768
	char mPadding0x76c[0x4];            // +0x76c
	int mMaxStage;                     // +0x770
	int mMaxLevel;                     // +0x774
	char mPadding0x778;                 // +0x778
	bool mUnk0x779;                    // +0x779
	char mPadding0x77a[0x2];            // +0x77a
    int mUnk0x77c;                     // +0x77C
	int mUnk0x780;                     // +0x780
	int mUnk0x784;                     // +0x784
	int mPendingMusicOrder;             // +0x788
	bool mMusicIntensityIncreasePending; // +0x78c
	char mPadding0x78d[0x3];            // +0x78d
	double mFeverVolume;               // +0x790
	bool mShouldShowUpsellButton;      // +0x798
	bool mUnk0x799;                     // +0x799
	char mPadding0x79a[0x16];           // +0x79a
	int mUnk0x7b0;                     // +0x7B0
	int mUnk0x7b8;                     // +0x7B4
	Board* mBoard;                     // +0x7B8
	UpsellScreen* mUpsellScreen;       // +0x7BC
	HelpScreen* mHelpScreen;           // +0x7C0
	LevelScreen* mLevelScreen;         // +0x7C4
	LoadingScreen* mLoadingScreen;     // +0x7C8
	MainMenu* mMainMenu;               // +0x7CC
	TrophyScreen* mTrophyScreen;       // +0x7D0
	StoryScreen* mStoryScreen;         // +0x7D4
	AdventureScreen* mAdventureScreen; // +0x7D8
	char mPadding0x7dc[0x54];           // +0x7DC
	RegistrationControl* mRegistrationControl; // +0x830
	int mUnk0x834;                     // +0x834
	bool mExpirationDisabled;           // +0x838
	bool mUnk0x839;                    // +0x839
	bool mUnk0x83A;                    // +0x83A
	bool mUnk0x83b;                     // +0x83b
	bool mUnk0x83C;                    // +0x83C
	char mPadding0x83d[0x7];            // +0x83d
	CharacterMgr* mCharacterMgr;       // +0x844
	HighScoreMgr* mHighScoreMgr;       // +0x848
	ImageMgr* mImageMgr;               // +0x84C
	ProfileMgr* mProfileMgr;           // +0x850
	char mPadding0x854[0x4];            // +0x854
	StageMgr* mStageMgr;               // +0x858
	StatsMgr* mStatsMgr;               // +0x85C
	StatsMgr* mEditStatsMgr;           // +0x860
	TrophyMgr* mTrophyMgr;             // +0x864
	WidgetMover* mWidgetMover;         // +0x868
	ButtonWidget* mWinCloseButton;     // +0x86C
	ButtonWidget* mWinMinimizeButton;  // +0x870
	ButtonWidget* mWinUnmaxButton;     // +0x874
	PlayerInfo* mCurProfile;           // +0x878
	int mUnk0x87c;                     // +0x87c
	int mUnk0x880;                     // +0x880
	int mUnk0x884;                     // +0x884
	int mUnk0x888;                     // +0x888
	int mUnk0x88c;                     // +0x88c
	int mUnk0x890;                     // +0x890
	int mUnk0x894;                     // +0x894
	int mUnk0x898;                     // +0x898
	GameStats mTwoPlayerStats[2];       // +0x89c

	ThunderballApp();
	virtual ~ThunderballApp();

	void BringDialogsToFront();
	void ButtonDepress(int);
	bool CanExpire();
	bool CheckCanExpire();
	void CheckMaxStage();
	void CheckPlayMusic(bool);
	bool CheckSaveGame(bool);
	void CheckScrollOff(Widget*, int, bool);
	void CleanupScreen(Widget*);
	void CleanupScreens(bool);
	void CopyBrickTextures();
	void CopyPegTextures();
	void DialogButtonDepress(int, int);
	void DoConfirmDeleteUserDialog(const std::string&);
	void DoConfirmMainMenuDialog();
	void DoConfirmNewChallengeDialog();
	void DoConfirmQuitDialog();
	void DoConfirmRestartAdventureDialog();
	void DoConfirmRestartLevelDialog(int);
	void DoCreateUserDialog();
	ThunderDialog* DoDialogScroll(
		int theId,
		bool isModal,
		const SexyString& theDialogHeader,
		const SexyString& theDialogLines,
		const SexyString& theDialogFooter,
		int theButtonMode
	);
	void DoOptionsDialog();
	void DoRenameUserDialog(std::string&);
	bool DoReplaysExist();
	void DoScrollOff(int);
	void DoTipDialog(int);
	void DoToMenu();
	void DoUserDialog();
	void EndHelpScreen();
	void EndUpsellScreen();
	void FinishConfirmDeleteUserDialog(bool);
	void FinishConfirmMainMenuDialog(bool);
	void FinishConfirmNewChallengeDialog(bool);
	void FinishConfirmQuitDialog(bool);
	void FinishConfirmRestartAdventureDialog(bool);
	void FinishConfirmRestartLevelDialog(bool);
	void FinishContinueDialog(bool);
	void FinishCreateUserDialog(bool);
	void FinishHighScoreEntryDialog(bool);
	void FinishNameErrorDialog(int);
	void FinishOptionsDialog(bool, bool);
	void FinishRenameUserDialog(bool);
	void FinishTipDialog(bool);
	void FinishUserDialog(bool);
	int GetCurLevel();
	LevelInfo* GetCurLevelInfo();
	long double GetFeverVolume();
	DDImage* GetImage(const std::string&, bool);
	int GetMaxLevel();
	int GetMaxLockedLevel();
	int GetMaxLockedStage();
	int GetMaxUnlockedCharacter();
	int GetMusicOrder(int theId);
	void IncLevel(int);
	int IsExpired();
	bool IsLevelDemoLocked(int, int);
	int IsLevelLockedTrial();
	bool IsRegistered();
	bool IsTrialOver();
	void LoadLevelMusic();
	void LoadMusic(int, const std::string&);
	bool OnMaxLevel();
	void PauseBoard(bool);
	void PlayMusic(int, bool);
	void RemoveBoard();
	void ResetTwoPlayerStats();
	void ScrollOn(Widget*);
	bool SetColorblind(bool);
	void SetExpired();
	void SetFeverVolume(double);
	void SetMusicIntensityIncreasePending(int);
	void SetMusicSpeed(float);
	void SetMusicVolume(double);
	void SetSfxVolume(double);
	void ShowAdventureScreen();
	void ShowBoard(bool, bool);
	void ShowHelpScreen(bool, bool);
	void ShowLevelScreen(bool);
	void ShowLoadingScreen();
	void ShowMainMenu();
	void ShowReplay(bool);
	void ShowStoryScreen(bool, bool);
	void ShowTrophyScreen();
	bool ShowUpsellScreen(bool param_1 = false, bool param_2 = false);
	void StartAdventureGame();
	void SyncOdeVolume();
	bool TryExpire(bool);
	bool TryPlayUpsell();
	int TryShowNewTrophy();
	void UpdateMusic();
	void ViewReplays();

	virtual void GotFocus();
	virtual bool DebugKeyDown(int);
	virtual void Init();
	virtual void InitHook();
	virtual bool IsAltKeyUsed(WPARAM wParam);
	virtual void LoadingThreadCompleted();
	virtual void LoadingThreadProc();
	virtual void LostFocus();
	virtual void MakeWindow();
	virtual Dialog* NewDialog(
		int theDialogId,
		bool isModal,
		const SexyString& theDialogHeader,
		const SexyString& theDialogLines,
		const SexyString& theDialogFooter,
		int theButtonMode
	);
	virtual void ReadFromRegistry();
	virtual void UpdateFrames();
	virtual void WriteToRegistry();
	virtual void Shutdown();
	virtual void ShutdownHook();
	virtual void SwitchScreenMode(bool wantWindowed, bool is3d, bool force);

	bool meth_0x405840();
};

inline ThunderballApp* GetThunderballApp()
{
	return (ThunderballApp*) gSexyApp;
}

} // namespace Sexy

#endif // _THUNDERBALLAPP_H_
