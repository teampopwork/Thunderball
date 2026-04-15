#include "Board.h"

using namespace Sexy;

Board::Board(ThunderballApp* app)
{
	mLogicMgr = NULL;
}
Board::~Board()
{
}

void Board::AddedToManager(WidgetManager* theManager)
{
}

void Board::RemovedFromManager(WidgetManager* theManager)
{
}

void Board::GotFocus()
{
}

void Board::LostFocus()
{
}

void Board::MouseMove(int theX, int theY)
{
}

void Board::MouseDrag(int theX, int theY)
{
}

void Board::MouseDown(int theX, int theY, int theClickCount)
{
}

void Board::MouseUp(int theX, int theY, int theClickCount)
{
}

void Board::MouseEnter()
{
}

void Board::MouseLeave()
{
}

void Board::KeyDown(KeyCode theKey)
{
}

void Board::MouseWheel(int theDelta)
{
}

void Board::DrawOverlay(Graphics* g)
{
}

void Board::Update()
{
}

void Board::ButtonDepress(int theId)
{
}

void Board::KeyChar(SexyChar theChar)
{
}

void Board::Draw(Graphics* g)
{
}

void Board::ShowEndLevelDialog()
{
}

void Board::RemoveSlotMachineDialog()
{
}

void Board::SubmitTotalStats()
{
}

bool Board::Cheated()
{
	return false;
}

bool Board::HasShot()
{
	return false;
}

void Board::PositionReplayDialog()
{
}

void Board::ShowReplayDialog()
{
}

void Board::RecordTrophyResult(bool param_1)
{
}

void Board::ResizeEndLevelDialog()
{
}

void Board::DoCharacterDialog(bool param_1)
{
}

void Board::DoSlotMachineDialog(Ball* param_1, PhysObj* param_2)
{
}

void Board::NotifyRemoving()
{
}

void Board::Pause(bool param_1)
{
}

void Board::DoReplayFileDialog(bool param_1, int param_2, bool param_3)
{
}

void Board::CheckIncTip()
{
}

void Board::SetSlowMo(bool param_1, int param_2)
{
}

void Board::UpdateTwoPlayerStats()
{
}

void Board::BeginShot()
{
}

void Board::ClearZoom()
{
}

void Board::UpdateMgrs()
{
}

void Board::UpdateSlowMo()
{
}

bool Board::IsAltKeyUsed(WPARAM wParam)
{
	return false;
}

void Board::FinishHighScoreEntryDialog(std::string* param_1)
{
}

void Board::DrawShadow(Graphics* g, int param_2, int param_3, bool param_4)
{
}

void Board::MakeShadow(Image* param_1, int param_2, int param_3)
{
}

void Board::SyncColorblind()
{
}

void Board::SetShowBackground(bool param_1)
{
}

void Board::DoZoom(Graphics* g)
{
}

void Board::CheckTrophyAccomplishments()
{
}

void Board::CheckForBackground()
{
}

void Board::CheckExploderForFever(PhysObj* param_1)
{
}

void Board::UpdateZoom()
{
}

void Board::CalcEndLevelDialog()
{
}

void Board::PlayMusic()
{
}

void Board::DeleteReplays(bool param_1)
{
}

void Board::LoadReplayFile(std::string* param_1)
{
}

PhysObj* Board::FindObj(PhysObj* param_1, bool param_2)
{
	return NULL;
}

void Board::Reload()
{
}

void Board::Clear(bool param_1)
{
}

void Board::AddObj(PhysObj* param_1, std::list<Sexy::SmartPtr<PhysObj> >::iterator param_2)
{
}

void Board::AddObj(PhysObj* param_1)
{
}

void Board::RemoveObj(PhysObj* param_1)
{
}

void Board::KillAllBalls()
{
}

void Board::CheckForFever(Ball* param_1)
{
}

void Board::UpdateObjects(bool param_1)
{
}

void Board::CreateLayers()
{
}

void Board::InitEndLevelDialog(int param_1, bool param_2)
{
}

void Board::SyncCharacterOptions(bool param_1)
{
}

void Board::DoStageDialog(bool param_1)
{
}

void Board::LoadLevelBase(std::string* param_1, std::list<Sexy::SmartPtr<PhysObj> > param_2, bool param_3)
{
}

void Board::ChangeHighScore(HighScoreEntry* param_1)
{
}

void Board::SubmitHighScore()
{
}

void Board::CheckClearAccomplishment()
{
}

void Board::DoLevelDone()
{
}

void Board::SyncModeOptions()
{
}

void Board::SyncState(DataSync* theSync)
{
}

void Board::SetSyncPoint(DataWriter* param_1, bool param_2)
{
}

void Board::EndReplay()
{
}

bool Board::NeedSaveGame()
{
	return false;
}

void* Board::GetSyncPoint()
{
	return NULL;
}

void Board::ShowReplay(int param_1, bool param_2)
{
}

void* Board::GetReplayPoint()
{
	return NULL;
}

void Board::LoadGame(Buffer* param_1)
{
}

void Board::SaveGame()
{
}

void Board::MakeThumbnail()
{
}

void Board::SetupLevel()
{
}

void Board::LoadLevel2(std::string* param_1)
{
}

void Board::LoadLevel(std::string* param_1)
{
}

void Board::Reset()
{
}

void Board::LoadEasterEggLevel(std::string* param_1, int param_2)
{
}

void Board::ActivateTypingCheck(int param_1)
{
}

void Board::DrawScreenSaver(Graphics* g)
{
}

