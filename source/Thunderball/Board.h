#ifndef __BOARD_H__
#define __BOARD_H__

#include "ConstEnums.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/SmartPtr.h>

#include <string>
#include <list>
#include <deque>

namespace Sexy
{
class ThunderballApp;
class ThunderButton;
class Ball;
class WidgetManager;
class Graphics;
class Image;
class DataSync;
class DataWriter;
class DataReader;
class Buffer;
class HighScoreEntry;
class AIMgr;
class CharacterMgr;
class CollisionMgr;
class DebugMgr;
class EffectMgr;
class FloatingTextMgr;
class InterfaceMgr;
class LevelEditor;
class LogicMgr;
class SoundMgr;
class ReplayDialog;
class EndLevelDialog;
class SlotMachineDialog;
class Gun;
class PhysObj;	
class TypingCheck;
class TrophyInfo;


// VTABLE: POPCAPGAME1 0x005d76d4 Sexy::ButtonListener
// VTABLE: POPCAPGAME1 0x005d76f4 Sexy::Board
class Board : public Widget, public ButtonListener
{
  public:
	TypingCheck* mTypingCheckList[9]; // +0x8c
	ThunderballApp* mApp; // +0xb0
	GameMode mUnk0xb4; // +0xb4
	int mUnk0xb8; // +0xb8
	SmartPtr<Gun> mGun; // +0xbc
	bool mUnk0xc0; // +0xc0
	bool mUnk0xc1; // +0xc1
	bool mUnk0xc2; // +0xc2
	bool mUnk0xc3; // +0xc3
	bool mUnk0xc4; // +0xc4
	bool mUnk0xc5; // +0xc5
	bool mUnk0xc6; // +0xc6
	bool mUnk0xc7; // +0xc7
	int mUnk0xc8; // +0xc8
	int mUnk0xcc; // +0xcc
	int mUnk0xd0; // +0xd0
	int mUnk0xd4; // +0xd4
	int mUnk0xd8; // +0xd8
	int mUnk0xdc; // +0xdc
	int mUnk0xe0; // +0xe0
	int mUnk0xe4; // +0xe4
	bool mUnk0xe8; // +0xe8
	bool mUnk0xe9; // +0xe9
	bool mUnk0xea; // +0xea
	bool mUnk0xeb; // +0xeb
	int mUnk0xec; // +0xec
	int mUnk0xf0; // +0xf0
	int mUnk0xf4; // +0xf4
	float mUnk0xf8; // +0xf8
	int mUnk0xfc; // +0xfc
	int mUnk0x100; // +0x100
	int mUnk0x104; // +0x104
	int mUnk0x108; // +0x108
	int mUnk0x10c; // +0x10c
	bool mUnk0x110; // +0x110
	int mUnk0x114; // +0x114
	int mUnk0x118; // +0x118
	bool mUnk0x11c; // +0x11c
	bool mUnk0x11d; // +0x11d
	bool mUnk0x11e; // +0x11e
	bool mUnk0x11f; // +0x11f
	bool mUnk0x120; // +0x120
	bool mUnk0x121; // +0x121
	bool mUnk0x122; // +0x122
	bool mUnk0x123; // +0x123
	int mUnk0x124; // +0x124
	SmartPtr<TrophyInfo> mUnk0x128; // +0x128
	bool mUnk0x12c; // +0x12c
	int mUnk0x130; // +0x130
	AIMgr* mAIMgr; // +0x134
	CharacterMgr* mCharacterMgr; // +0x138
	CollisionMgr* mCollisionMgr; // +0x13c
	DebugMgr* mDebugMgr; // +0x140
	EffectMgr* mEffectMgr; // +0x144
	FloatingTextMgr* mFloatingTextMgr; // +0x148
	InterfaceMgr* mInterfaceMgr; // +0x14c
	LevelEditor* mLevelEditor; // +0x150
	LogicMgr* mLogicMgr; // +0x154
	SoundMgr* mSoundMgr; // +0x158
	ReplayDialog* mReplayDialog; // +0x15c
	EndLevelDialog* mEndLevelDialog; // +0x160
	SlotMachineDialog* mSlotMachineDialog; // +0x164
	ThunderButton* mMenuButton; // +0x168
	ThunderButton* mReplayButton; // +0x16c
	int mUnk0x170; // +0x170
	std::deque<DataWriter*> mUnk0x174; // +0x174
	int mUnk0x184; // +0x184
	DataWriter* mUnk0x188; // +0x188
	DataReader* mUnk0x18c; // +0x18c
	std::list<Sexy::SmartPtr<PhysObj>> mUnk0x190; // +0x190
	std::list<Sexy::SmartPtr<Ball>> mUnk0x19c; // +0x1a0
    int mUnk0x1a8; // +0x1a8
	int mUnk0x1ac; // +0x1ac
	int mUnk0x1b0; // +0x1b0
	int mUnk0x1b4; // +0x1b4
	int mUnk0x1b8; // +0x1b8
	int mUnk0x1bc; // +0x1bc
	int mUnk0x1c0; // +0x1c0
    int mUnk0x1c4; // +0x1c4
	int mUnk0x1c8; // +0x1c8
	int mUnk0x1cc; // +0x1cc
	int mUnk0x1d0; // +0x1d0
	std::string mUnk0x1d4; // +0x1d4
	std::string mUnk0x1ec; // +0x1ec
	std::vector<PhysObj*> mUnk0x1f4; // +0x1f4
	std::vector<PhysObj*> mUnk0x204; // +0x204
	std::vector<PhysObj*> mUnk0x214; // +0x214
	std::vector<PhysObj*> mUnk0x224; // +0x224
	std::vector<PhysObj*> mUnk0x234; // +0x234
	std::vector<PhysObj*> mUnk0x244; // +0x244

	Board(ThunderballApp* app);
	virtual ~Board();

	virtual void AddedToManager(WidgetManager* theWidgetManager);
	virtual void RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void GotFocus();
	virtual void LostFocus();
	virtual void MouseMove(int theX, int theY);
	virtual void MouseDrag(int theX, int theY);
	virtual void MouseDown(int theX, int theY, int theClickCount);
	virtual void MouseUp(int theX, int theY, int theClickCount);
	virtual void MouseEnter();
	virtual void MouseLeave();
	virtual void KeyDown(KeyCode theKey);
	virtual void MouseWheel(int theDelta);
	virtual void DrawOverlay(Graphics* g);
	virtual void Update();
	virtual void ButtonDepress(int theId);
	virtual void KeyChar(SexyChar theChar);
	virtual void Draw(Graphics* g);

	void     ShowEndLevelDialog();
	void     RemoveSlotMachineDialog();
	void     SubmitTotalStats();
	bool     Cheated();
	bool     HasShot();
	void     PositionReplayDialog();
	void     ShowReplayDialog();
	void     RecordTrophyResult(bool param_1);
	void     ResizeEndLevelDialog();
	void     DoCharacterDialog(bool param_1);
	void     DoSlotMachineDialog(Ball* param_1, PhysObj* param_2);
	void     NotifyRemoving();
	void     Pause(bool param_1);
	void     DoReplayFileDialog(bool param_1, int param_2, bool param_3);
	void     CheckIncTip();
	void     SetSlowMo(bool param_1, int param_2);
	void     UpdateTwoPlayerStats();
	void     BeginShot();
	void     ClearZoom();
	void     UpdateMgrs();
	void     UpdateSlowMo();
	bool     IsAltKeyUsed(WPARAM wParam);
	void     FinishHighScoreEntryDialog(std::string* param_1);
	void     DrawShadow(Graphics* g, int param_2, int param_3, bool param_4);
	void     MakeShadow(Image* param_1, int param_2, int param_3);
	void     SyncColorblind();
	void     SetShowBackground(bool param_1);
	bool     DoZoom(Graphics* g);
	void     CheckTrophyAccomplishments();
	void     CheckForBackground();
	void     CheckExploderForFever(PhysObj* param_1);
	void     UpdateZoom();
	void     CalcEndLevelDialog();
	void     PlayMusic();
	void     DeleteReplays(bool param_1);
	bool     LoadReplayFile(std::string& param_1);
	PhysObj* FindObj(PhysObj* param_1, bool param_2);
	void     Reload();
	void     Clear(bool param_1);
	void     AddObj(PhysObj* param_1, std::list<Sexy::SmartPtr<PhysObj> >::iterator param_2);
	void     AddObj(PhysObj* param_1);
	void     RemoveObj(PhysObj* param_1);
	void     KillAllBalls();
	void     CheckForFever(Ball* param_1);
	void     UpdateObjects(bool param_1);
	void     CreateLayers();
	void     InitEndLevelDialog(int param_1, bool param_2);
	void     SyncCharacterOptions(bool param_1);
	void     DoStageDialog(bool param_1);
	void     LoadLevelBase(std::string* param_1, std::list<Sexy::SmartPtr<PhysObj> > param_2, bool param_3);
	void     ChangeHighScore(HighScoreEntry* param_1);
	void     SubmitHighScore();
	void     CheckClearAccomplishment();
	void     DoLevelDone();
	void     SyncModeOptions();
	void     SyncState(DataSync& theSync);
	void     SetSyncPoint(DataWriter* param_1, bool param_2);
	void     EndReplay();
	bool     NeedSaveGame();
	void*    GetSyncPoint();
	void     ShowReplay(int param_1, bool param_2);
	void*    GetReplayPoint();
	void     LoadGame(Buffer* param_1);
	void     SaveGame();
	void     MakeThumbnail();
	void     SetupLevel();
	void     LoadLevel2(std::string* param_1);
	void     LoadLevel(std::string* param_1);
	void     Reset();
	void     LoadEasterEggLevel(std::string* param_1, int param_2);
	void     ActivateTypingCheck(int param_1);
	void     DrawScreenSaver(Graphics* g);
	bool     EditingLevel();
};
} // namespace Sexy

#endif