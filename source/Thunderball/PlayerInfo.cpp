#include "PlayerInfo.h"
#include "DataSync.h"

#include <SexyAppFramework/SexyApp.h>
#include <SexyAppFramework/Buffer.h>

#include <set>

using namespace Sexy;

// STUB: POPCAPGAME1 0x00429200
PlayerInfo::PlayerInfo()
{
}

// STUB: POPCAPGAME1 0x00462490
PlayerInfo::PlayerInfo(PlayerInfo& param_1)
{
}

// SYNTHETIC: POPCAPGAME1 0x00429360
// Sexy::PlayerInfo::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x004267c0
PlayerInfo::~PlayerInfo()
{
}

// STUB: POPCAPGAME1 0x00403840
void PlayerInfo::AddTotalStats(GameStats *theStats)
{
}

// STUB: POPCAPGAME1 0x004fc300
void PlayerInfo::AwardTrophy() 
{
}

// STUB: POPCAPGAME1 0x0049d670
bool PlayerInfo::CheckTrophyTopScore(int trophyId, int theScore) 
{
    return false;
}

// FUNCTION: POPCAPGAME1 0x00412940
void PlayerInfo::DeleteSavedGame(SaveType theSaveType) 
{
    std::string aGameName = GetSavedGameName(theSaveType);

    if (!aGameName.empty())
    {
        gSexyApp->EraseFile(aGameName);
    }
}

// FUNCTION: POPCAPGAME1 0x004129c0
void PlayerInfo::DeleteSavedGames()
{
    DeleteSavedGame(SaveType::ARCADE);
    DeleteSavedGame(SaveType::STAGE);  
    DeleteSavedGame(SaveType::TROPHY);
    DeleteSavedGame(SaveType::DUEL);
}

// STUB: POPCAPGAME1 0x0041f860
void PlayerInfo::DeleteUserFiles()
{
}

// STUB: POPCAPGAME1 0x004037f0
int PlayerInfo::GetAdventureEfficiencyBonus() 
{
    return 0;
}

// STUB: POPCAPGAME1 0x004037e0
int PlayerInfo::GetMaxLevel() 
{
    return 0;
}

// STUB: POPCAPGAME1 0x00412680
std::string PlayerInfo::GetSavedGameName(SaveType theSaveType)
{
    return "";
}

// STUB: POPCAPGAME1 0x0040d110
int PlayerInfo::GetTrophyTopScore(int trophyId) 
{
    return 0;
}

// STUB: POPCAPGAME1 0x004037b0
void PlayerInfo::IncTip(int tipId)
{
}

// STUB: POPCAPGAME1 0x004036b0
void PlayerInfo::IsLevelUnlocked(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x004038f0
bool PlayerInfo::IsTipSet(int tipId) 
{
    return false;
}

// FUNCTION: POPCAPGAME1 0x00403870
bool PlayerInfo::JustBeatAdventure()
{
    if ((0 < m_unk0x48) && (m_unk0x30 == 11) && (m_unk0x34 == 0) && (m_unk0x208 == 0)) {
        return true;
    }
    return false;
}

// FUNCTION: POPCAPGAME1 0x004038a0
bool PlayerInfo::JustStartingAdventure()
{
    if ((m_unk0x30 <= 0) && (m_unk0x34 == 0) && (m_unk0x208 == 0)) {
        return true;
    }
    return false;
}

// FUNCTION: POPCAPGAME1 0x00426bd0
void PlayerInfo::LoadDetails()
{
    Buffer aBuffer;
    try {
        // STRING: POPCAPGAME1 0x005d72b0
        if (gSexyApp->ReadBufferFromFile(GetAppDataFolder() + StrFormat("userdata/user%d.dat", m_unk0x24), &aBuffer)) 
        {
            DataReader aReader;
            aReader.OpenMemory(aBuffer.GetDataPtr(), aBuffer.GetDataLen(), false);
            DataSync aSync(aReader);
            SyncDetails(&aSync);
        }
    } catch (...) {
        Reset(false);
    }
}

// STUB: POPCAPGAME1 0x00421850
void PlayerInfo::Reset(bool param_1) 
{
}

// FUNCTION: POPCAPGAME1 0x0041f820
void PlayerInfo::RestartAdventure()
{
    m_unk0x204 = 0;
    m_unk0x208 = 0;
    m_unk0x20c = 0;
    m_unk0x30 = 0;
    m_unk0x34 = 0;
    m_unk0x61 = true;
    DeleteSavedGame(SaveType::ARCADE);
    m_unk0xec = true;
}

// TEMPLATE: POPCAPGAME1 0x0040f340
// std::operator+<char,std::char_traits<char>,std::allocator<char> >(class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const &, class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const &)

// FUNCTION: POPCAPGAME1 0x00426d60
void PlayerInfo::SaveDetails()
{
    m_unk0xec = false;
    DataWriter aWriter;
    aWriter.OpenMemory(32);
    DataSync aSync(aWriter);
    SyncDetails(&aSync);

    // STRING: POPCAPGAME1 0x005d7c78
    std::string aUserData = GetAppDataFolder() + "userdata";
    MkDir(aUserData);

    gSexyApp->WriteBytesToFile(GetAppDataFolder() + StrFormat("userdata/user%d.dat", m_unk0x24), aWriter.mMemoryHandle, aWriter.mMemoryLength);
}

// FUNCTION: POPCAPGAME1 0x00426f00
void PlayerInfo::SaveIfDirty()
{
    if (m_unk0xec) {
        SaveDetails();
    }
}

// FUNCTION: POPCAPGAME1 0x004036e0
void PlayerInfo::SetColorblind(bool isColorblind)
{
    if (isColorblind != m_unk0x60) {
        m_unk0x60 = isColorblind;
        m_unk0xec = true;
    }
}

// FUNCTION: POPCAPGAME1 0x00403750
void PlayerInfo::SetComputerPlayer(bool isComputer)
{
    if (m_unk0x4c != isComputer) {
        m_unk0x4c = isComputer;
        m_unk0xec = true;
    }
}

// FUNCTION: POPCAPGAME1 0x00403770
void PlayerInfo::SetComputerSkill(int theSkill) 
{
    if (m_unk0x50 != theSkill) {
        m_unk0x50 = theSkill;
        m_unk0xec = true;
    }
}

// FUNCTION: POPCAPGAME1 0x00403700
void PlayerInfo::SetSelCharacter(int theId)
{
    if (m_unk0x40 != theId) {
        m_unk0x40 = theId;
        m_unk0xec = true;
    }
}

// FUNCTION: POPCAPGAME1 0x00403720
void PlayerInfo::SetSelCharacters(int param_1, int param_2)
{
    if (m_unk0x40 != param_1) {
        m_unk0x40 = param_1;
        m_unk0xec = true;
    }
    if (m_unk0x44 != param_2) {
        m_unk0x44 = param_2;
        m_unk0xec = true;
    }
}

// FUNCTION: POPCAPGAME1 0x00421a00
void PlayerInfo::SubmitAdventureHighScore(int theScore)
{
    mAdventureScores.insert(theScore);

    if (mAdventureScores.size() > 10) {
        std::multiset<int>::iterator anIt;
    
        anIt = mAdventureScores.begin();
        if (*anIt != theScore) 
        {
            m_unk0xec = true;
        }
        mAdventureScores.erase(anIt);
        return;
    }
    m_unk0xec = true;
}

// STUB: POPCAPGAME1 0x00426980
int PlayerInfo::SyncDetails(DataSync* theSync) 
{
    if (theSync->mReader != NULL) {
        Reset(false);
    }

    return 0;
}

// FUNCTION: POPCAPGAME1 0x00403670
void PlayerInfo::SyncSummary(DataSync* theSync)
{
    theSync->SyncString(m_unk0x4);
    theSync->SyncLong(m_unk0x20);
    theSync->SyncLong(m_unk0x24);
}