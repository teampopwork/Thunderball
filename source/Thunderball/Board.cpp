#include "Board.h"

#include "AIMgr.h"
#include "CollisionMgr.h"
#include "DebugMgr.h"
#include "EffectMgr.h"
#include "FloatingTextMgr.h"
#include "InterfaceMgr.h"
#include "LevelEditor.h"
#include "LogicMgr.h"
#include "SoundMgr.h"
#Include "EndLevelDialog.h"

#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x004238a0
Board::Board(ThunderballApp* theApp)
{
	mApp = theApp;
	mAIMgr = new AIMgr(this);
	mCharacterMgr = theApp->mCharacterMgr;
	mCollisionMgr = new CollisionMgr();
	mDebugMgr = new DebugMgr(this);
	mEffectMgr = new EffectMgr();
	mFloatingTextMgr = new FloatingTextMgr();
	mInterfaceMgr = new InterfaceMgr(this);
	mLevelEditor = new LevelEditor(this);
	mLogicMgr = new LogicMgr(this);
	mSoundMgr = new SoundMgr();
	mEndLevelDialog = new EndLevelDialog(thhis);
}

// STUB: POPCAPGAME1 0x004299a0
Board::~Board()
{
}

// FUNCTION: POPCAPGAME1 0x00402fd0
void Board::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
}

// FUNCTION: POPCAPGAME1 0x00406bf0
void Board::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	NotifyRemoving();
}

// FUNCTION: POPCAPGAME1 0x004025a0
void Board::GotFocus()
{
	Widget::GotFocus();
}

// FUNCTION: POPCAPGAME1 0x004025b0
void Board::LostFocus()
{
	Widget::LostFocus();
}

// STUB: POPCAPGAME1 0x00402790
void Board::MouseMove(int theX, int theY)
{
}

// STUB: POPCAPGAME1 0x004027d0
void Board::MouseDrag(int theX, int theY)
{
}

// STUB: POPCAPGAME1 0x00402810
void Board::MouseDown(int theX, int theY, int theClickCount)
{
}

// STUB: POPCAPGAME1 0x004028a0
void Board::MouseUp(int theX, int theY, int theClickCount)
{
}

// STUB: POPCAPGAME1 0x004028f0
void Board::MouseEnter()
{
}

// STUB: POPCAPGAME1 0x00402910
void Board::MouseLeave()
{
}

// STUB: POPCAPGAME1 0x00402930
void Board::KeyDown(KeyCode theKey)
{
}

// STUB: POPCAPGAME1 0x00406ec0
void Board::MouseWheel(int theDelta)
{
}

// STUB: POPCAPGAME1 0x00406f70
void Board::DrawOverlay(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00410e10
void Board::Update()
{
}

// STUB: POPCAPGAME1 0x00425f00
void Board::ButtonDepress(int theId)
{
}

// STUB: POPCAPGAME1 0x0042df70
void Board::KeyChar(SexyChar theChar)
{
}

// STUB: POPCAPGAME1 0x00425290
void Board::Draw(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00402280
void Board::ShowEndLevelDialog()
{
}

// STUB: POPCAPGAME1 0x00402480
void Board::RemoveSlotMachineDialog()
{
}

// STUB: POPCAPGAME1 0x00406a20
void Board::SubmitTotalStats()
{
}

// STUB: POPCAPGAME1 0x00402000
bool Board::Cheated()
{
	return false;
}

// STUB: POPCAPGAME1 0x00402010
bool Board::HasShot()
{
	return false;
}

// STUB: POPCAPGAME1 0x00402030
void Board::PositionReplayDialog()
{
}

// STUB: POPCAPGAME1 0x00402130
void Board::ShowReplayDialog()
{
}

// STUB: POPCAPGAME1 0x004021b0
void Board::RecordTrophyResult(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00402210
void Board::ResizeEndLevelDialog()
{
}

// STUB: POPCAPGAME1 0x004022f0
void Board::DoCharacterDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004023f0
void Board::DoSlotMachineDialog(Ball* param_1, PhysObj* param_2)
{
}

// STUB: POPCAPGAME1 0x00402500
void Board::NotifyRemoving()
{
}

// STUB: POPCAPGAME1 0x004025c0
void Board::Pause(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040d000
void Board::DoReplayFileDialog(bool param_1, int param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00406c10
void Board::CheckIncTip()
{
}

// STUB: POPCAPGAME1 0x004026f0
void Board::SetSlowMo(bool param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x00406da0
void Board::UpdateTwoPlayerStats()
{
}

// STUB: POPCAPGAME1 0x00402760
void Board::BeginShot()
{
}

// STUB: POPCAPGAME1 0x00402ab0
void Board::ClearZoom()
{
}

// STUB: POPCAPGAME1 0x00402ad0
void Board::UpdateMgrs()
{
}

// STUB: POPCAPGAME1 0x00402ba0
void Board::UpdateSlowMo()
{
}

// STUB: POPCAPGAME1 0x004073a0
bool Board::IsAltKeyUsed(WPARAM wParam)
{
	return false;
}

// STUB: POPCAPGAME1 0x00402cf0
void Board::FinishHighScoreEntryDialog(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x00406c50
void Board::DrawShadow(Graphics* g, int param_2, int param_3, bool param_4)
{
}

// STUB: POPCAPGAME1 0x00409020
void Board::MakeShadow(Image* param_1, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x004098b0
void Board::SyncColorblind()
{
}

// STUB: POPCAPGAME1 0x00409aa0
void Board::SetShowBackground(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004029c0
void Board::DoZoom(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00420dd0
void Board::CheckTrophyAccomplishments()
{
}

// STUB: POPCAPGAME1 0x00409920
void Board::CheckForBackground()
{
}

// STUB: POPCAPGAME1 0x00409b40
void Board::CheckExploderForFever(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0040ad10
void Board::UpdateZoom()
{
}

// STUB: POPCAPGAME1 0x00406a80
void Board::CalcEndLevelDialog()
{
}

// STUB: POPCAPGAME1 0x00422640
void Board::PlayMusic()
{
}

// STUB: POPCAPGAME1 0x0040cf70
void Board::DeleteReplays(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00420920
void Board::LoadReplayFile(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x0040d8e0
PhysObj* Board::FindObj(PhysObj* param_1, bool param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x004090d0
void Board::Reload()
{
}

// STUB: POPCAPGAME1 0x0040d7d0
void Board::Clear(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00421070
void Board::AddObj(PhysObj* param_1, std::list<Sexy::SmartPtr<PhysObj> >::iterator param_2)
{
}

// STUB: POPCAPGAME1 0x00422a90
void Board::AddObj(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0040fed0
void Board::RemoveObj(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x00410120
void Board::KillAllBalls()
{
}

// STUB: POPCAPGAME1 0x00409d50
void Board::CheckForFever(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x00410ae0
void Board::UpdateObjects(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00424fd0
void Board::CreateLayers()
{
}

// STUB: POPCAPGAME1 0x0040ac40
void Board::InitEndLevelDialog(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0040f400
void Board::SyncCharacterOptions(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0041e910
void Board::DoStageDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004227c0
void Board::LoadLevelBase(std::string* param_1, std::list<Sexy::SmartPtr<PhysObj> > param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x0040fd90
void Board::ChangeHighScore(HighScoreEntry* param_1)
{
}

// STUB: POPCAPGAME1 0x00420b50
void Board::SubmitHighScore()
{
}

// STUB: POPCAPGAME1 0x00420e80
void Board::CheckClearAccomplishment()
{
}

// STUB: POPCAPGAME1 0x00427f20
void Board::DoLevelDone()
{
}

// STUB: POPCAPGAME1 0x0040f980
void Board::SyncModeOptions()
{
}

// STUB: POPCAPGAME1 0x00424090
void Board::SyncState(DataSync* theSync)
{
}

// STUB: POPCAPGAME1 0x00424a70
void Board::SetSyncPoint(DataWriter* param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00424c50
void Board::EndReplay()
{
}

// STUB: POPCAPGAME1 0x00427e50
bool Board::NeedSaveGame()
{
	return false;
}

// STUB: POPCAPGAME1 0x004249c0
void* Board::GetSyncPoint()
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00424d40
void Board::ShowReplay(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00424be0
void* Board::GetReplayPoint()
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00424860
void Board::LoadGame(Buffer* param_1)
{
}

// STUB: POPCAPGAME1 0x00427d60
void Board::SaveGame()
{
}

// STUB: POPCAPGAME1 0x004101a0
void Board::MakeThumbnail()
{
}

// STUB: POPCAPGAME1 0x0041ea50
void Board::SetupLevel()
{
}

// STUB: POPCAPGAME1 0x00429d10
void Board::LoadLevel2(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x0042aae0
void Board::LoadLevel(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x0042da00
void Board::Reset()
{
}

// STUB: POPCAPGAME1 0x0042db70
void Board::LoadEasterEggLevel(std::string* param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x0042dc60
void Board::ActivateTypingCheck(int param_1)
{
}

// STUB: POPCAPGAME1 0x00410940
void Board::DrawScreenSaver(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x004024e0
bool Board::EditingLevel() 
{
	return false;
}

