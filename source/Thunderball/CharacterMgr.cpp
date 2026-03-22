#include "CharacterMgr.h"

using namespace Sexy;

CharacterMgr::CharacterMgr()
{
}
CharacterMgr::~CharacterMgr()
{
}

void CharacterMgr::CalcEyePos(bool param_1)
{
}
void CharacterMgr::CalcLookPos(Board* theBoard, bool param_2)
{
}
void CharacterMgr::CalcPowerupActive(Board* theBoard)
{
}
void CharacterMgr::CheckCrossEyeFix()
{
}
void CharacterMgr::Clear(bool param_1)
{
}
void CharacterMgr::CreateShooterImage(int param_1)
{
}
void CharacterMgr::DoCharMove(int param_1, int param_2, bool param_3)
{
}
void CharacterMgr::DoPowerupBlink(int param_1)
{
}
void CharacterMgr::DoPowerupCountBlink()
{
}
void CharacterMgr::Draw(Graphics* g, Board* theBoard)
{
}
void CharacterMgr::DrawBack(Graphics* g1, Graphics* g2, Board* theBoard)
{
}
void CharacterMgr::DrawFront(Graphics* g1, Graphics* g2, Board* theBoard)
{
}
std::string* CharacterMgr::GetCharacterDesc(int param_1)
{
	return NULL;
}

int CharacterMgr::GetCharacterIdByName(std::string* param_1)
{
	return 0;
}

int CharacterMgr::GetCharacterInfo(int param_1)
{
	return 0;
}

int CharacterMgr::GetCharacterInfoSafe(int param_1)
{
	return 0;
}

int CharacterMgr::GetCharacterName(int param_1)
{
	return 0;
}

int CharacterMgr::GetCharacterTip(int param_1, unsigned long param_2)
{
	return 0;
}

int CharacterMgr::GetCurCharFrame(CharacterInfo* param_1)
{
	return 0;
}
void CharacterMgr::InitDefault()
{
}
void CharacterMgr::Load()
{
}
void CharacterMgr::ReadConfig(std::string* param_1)
{
}
void CharacterMgr::ReaderCharacterConfig(ConfigParser* param_1, CharacterInfo* param_2)
{
}
int CharacterMgr::ReadPowerupType(ConfigParser* param_1, std::string* param_2)
{
	return 0;
}
void CharacterMgr::Resync()
{
}
int CharacterMgr::SetCurCharacter(int param_1)
{
    return 0;
}
void CharacterMgr::SetYinYangEye(bool param_1)
{
}
void CharacterMgr::SyncState(DataSync& theState)
{
}
void CharacterMgr::Update()
{
}
void CharacterMgr::UpdatePaused()
{
}
void CharacterMgr::UpdateSlowMo()
{
}
