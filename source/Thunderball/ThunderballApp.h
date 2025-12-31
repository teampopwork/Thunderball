#ifndef __THUNDERBALLAPP_H__
#define __THUNDERBALLAPP_H__

#include <SexyAppFramework/SexyApp.h>

namespace Sexy
{
class WidgetMover;
class ProfileInfo;
class ButtonWidget;
class LoadingScreen;

// VTABLE: POPCAPGAME1 0x005d7cb8
class ThunderballApp : public SexyApp {
public:
	int m_unk0x750;                   // +0x750 // part of SexyApp
	int m_unk0x760;                   // +0x760 // part of SexyApp
	int mMaxStage;                    // +0x770
	int mMaxLevel;                    // +0x774
	bool m_unk0x779;                  // +0x779
	int m_unk0x77c;                   // +0x77C
	int m_unk0x780;                   // +0x780
	int m_unk0x784;                   // +0x784
	double mFeverVolume;              // +0x790
	bool mShouldShowUpsellButton;     // +0x798
	bool m_unk0x7b0;                  // +0x7B0
	bool m_unk0x7b1;                  // +0x7B1
	int m_unk0x7b8;                   // +0x7B4
	LoadingScreen* mLoadingScreen;    // +0x7C8
	bool mColorblind;                 // +0x7CC
	bool m_unk0x839;                  // +0x839
									  // CharacterMgr* mCharacterMgr; // +0x844
									  // HighScoreMgr* mHighScoreMgr; // +0x848
									  // ProfileMgr*   mProfileMgr;   // +0x850
									  // StageMgr*     mStageMgr;     // +0x858
									  // StatsMgr*	 mStatsMgr;     // +0x85C
									  // StatsMgr*	 mEditStatsMgr;    // +0x860
									  // TrophyMgr*    mTrophyMgr;    // +0x864
	WidgetMover* mWidgetMover;        // +0x868
	ButtonWidget* mWinCloseButton;    // +0x86C
	ButtonWidget* mWinMinimizeButton; // +0x870
	ButtonWidget* mWinUnmaxButton;    // +0x874
	// ProfileInfo*   mCurProfile;        // +0x878
	int mCurProfile;                // +0x878

	ThunderballApp();
	virtual ~ThunderballApp();

	void BringDialogsToFront();
	void ButtonDepress(int);
	int CheckCanExpire();
	void CheckMaxStage();
	void CheckPlayMusic(bool);
	int CheckSaveGame(bool);
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
	// ThunderDialog* DoDialogScroll(int, bool, const std::string&, const std::string&, const std::string&, int);
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
	int GetCurLevelInfo();
	long double GetFeverVolume();
	DDImage* GetImage(const std::string&, bool);
	int GetMaxLevel();
	int GetMaxLockedLevel();
	int GetMaxLockedStage();
	int GetMaxUnlockedCharacter();
	int GetMusicOrder(int theId);
	void IncLevel(int);
	bool IsExpired();
	bool IsLevelDemoLocked(int, int);
	bool IsLevelLockedTrial();
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
	void ShowUpsellScreen();
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
};

inline ThunderballApp* GetThunderballApp()
{
	return (ThunderballApp*) gSexyApp;
}

} // namespace Sexy

#endif // _THUNDERBALLAPP_H_
