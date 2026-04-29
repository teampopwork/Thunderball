#ifndef __BOARD_H__
#define __BOARD_H__

#include "PhysObj.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/SmartPtr.h>

#include <string>
#include <list>

namespace Sexy
{
class ThunderballApp;
class Ball;
class WidgetManager;
class Graphics;
class Image;
class DataSync;
class DataWriter;
class Buffer;
class HighScoreEntry;
class AIMgr;
class CollisionMgr;
class DebugMgr;
class EffectMgr;
class FloatingTextMgr;
class InterfaceMgr;
class LevelEditor;
class LogicMgr;
class SoundMgr;

// VTABLE: POPCAPGAME1 0x005d76d4 Sexy::ButtonListener
// VTABLE: POPCAPGAME1 0x005d76f4 Sexy::Board
class Board : public Widget, public ButtonListener
{
  public:
	ThunderballApp* mApp; // +0xb0
	AIMgr* mAIMgr; // +0x134
	CollisionMgr* mCollisionMgr; // +0x13c
	DebugMgr* mDebugMgr; // +0x140
	EffectMgr* mEffectMgr; // +0x144
	FloatingTextMgr* mFloatingTextMgr; // +0x148
	InterfaceMgr* mInterfaceMgr; // +0x14c
	LevelEditor* mLevelEditor; // +0x150
	LogicMgr* mLogicMgr; // +0x154
	SoundMgr* mSoundMgr; // +0x158
	EndLevelDialog* mEndLevelDialog; // +0x160

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
	void     DoZoom(Graphics* g);
	void     CheckTrophyAccomplishments();
	void     CheckForBackground();
	void     CheckExploderForFever(PhysObj* param_1);
	void     UpdateZoom();
	void     CalcEndLevelDialog();
	void     PlayMusic();
	void     DeleteReplays(bool param_1);
	void     LoadReplayFile(std::string* param_1);
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
	void     SyncState(DataSync* theSync);
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