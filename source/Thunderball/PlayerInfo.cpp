#include "PlayerInfo.h"

#include "DataSync.h"
#include "ConstEnums.h"

#include <SexyAppFramework/Buffer.h>
#include <SexyAppFramework/SexyApp.h>
#include <set>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00429200
PlayerInfo::PlayerInfo()
{
	Reset(false);
}

// STUB: POPCAPGAME1 0x00462490
PlayerInfo::PlayerInfo(const PlayerInfo& param_1)
{
}

// FUNCTION: POPCAPGAME1 0x461680
PlayerInfo& PlayerInfo::operator=(const PlayerInfo& other)
{
	mName.assign(other.mName, 0, (size_t)-1);
	mUseSeq = other.mUseSeq;
	mId = other.mId;
	mUnk0x28 = other.mUnk0x28;
	mUnk0x2c = other.mUnk0x2c;
	mUnk0x30 = other.mUnk0x30;
	mUnk0x34 = other.mUnk0x34;
	mUnk0x38 = other.mUnk0x38;
	mUnk0x3c = other.mUnk0x3c;
	mUnk0x40 = other.mUnk0x40;
	mUnk0x44 = other.mUnk0x44;
	mUnk0x48 = other.mUnk0x48;
	mUnk0x4c = other.mUnk0x4c;
	mUnk0x50 = other.mUnk0x50;
	mUnk0x54 = other.mUnk0x54;
	mUnk0x58 = other.mUnk0x58;
	mUnk0x5c = other.mUnk0x5c;
	mUnk0x60 = other.mUnk0x60;
	mUnk0x61 = other.mUnk0x61;
	mUnk0x64 = other.mUnk0x64;
	mUnk0x68 = other.mUnk0x68;
	mUnk0x6c = other.mUnk0x6c;
	mUnk0x70 = other.mUnk0x70;
	mUnk0x74 = other.mUnk0x74;
	mUnk0x78 = other.mUnk0x78;
	mUnk0x7c = other.mUnk0x7c;
	mUnk0x80 = other.mUnk0x80;
	mUnk0x84 = other.mUnk0x84;
	mUnk0x88 = other.mUnk0x88;
	mUnk0x8c = other.mUnk0x8c;
	mUnk0x90 = other.mUnk0x90;
	mUnk0x94 = other.mUnk0x94;
	mUnk0x98 = other.mUnk0x98;
	mUnk0xb4 = other.mUnk0xb4;
	mUnk0xd0 = other.mUnk0xd0;
	mUnk0xec = other.mUnk0xec;
	mUnk0xed = other.mUnk0xed;
	mUnk0xee = other.mUnk0xee;
	mUnk0xef = other.mUnk0xef;

	if (&mAdventureScores != &other.mAdventureScores)
		mAdventureScores = other.mAdventureScores;

	if (&mUnk0xfc != &other.mUnk0xfc)
		mUnk0xfc = other.mUnk0xfc;

	if (&mUnk0x108 != &other.mUnk0x108)
		mUnk0x108 = other.mUnk0x108;

	mUnk0x114 = other.mUnk0x114;

	if (&mUnk0x118 != &other.mUnk0x118)
		mUnk0x118 = other.mUnk0x118;

	mUnk0x124 = other.mUnk0x124;
	mUnk0x128 = other.mUnk0x128;

	mUnk0x12c = other.mUnk0x12c;
	mUnk0x198 = other.mUnk0x198;

	mUnk0x204 = other.mUnk0x204;
	mUnk0x208 = other.mUnk0x208;
	mUnk0x20c = other.mUnk0x20c;

	return *this;
}

// SYNTHETIC: POPCAPGAME1 0x00429360
// Sexy::PlayerInfo::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x004267c0
PlayerInfo::~PlayerInfo()
{
}

// STUB: POPCAPGAME1 0x00403840
void PlayerInfo::AddTotalStats(GameStats* theStats)
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
void PlayerInfo::DeleteSavedGame(GameMode theGameMode)
{
	std::string aGameName = GetSavedGameName(theGameMode);

	if (!aGameName.empty()) {
		gSexyApp->EraseFile(aGameName);
	}
}

// FUNCTION: POPCAPGAME1 0x004129c0
void PlayerInfo::DeleteSavedGames()
{
	DeleteSavedGame(GameMode::ADVENTURE);
	DeleteSavedGame(GameMode::QUICK_PLAY);
	DeleteSavedGame(GameMode::CHALLENGE);
	DeleteSavedGame(GameMode::DUEL);
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
std::string PlayerInfo::GetSavedGameName(GameMode theGameMode)
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
	if ((0 < mUnk0x48) && (mUnk0x30 == 11) && (mUnk0x34 == 0) && (mUnk0x208 == 0)) {
		return true;
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x004038a0
bool PlayerInfo::JustStartingAdventure()
{
	if ((mUnk0x30 <= 0) && (mUnk0x34 == 0) && (mUnk0x208 == 0)) {
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
		if (gSexyApp->ReadBufferFromFile(GetAppDataFolder() + StrFormat("userdata/user%d.dat", mId), &aBuffer)) {
			DataReader aReader;
			aReader.OpenMemory(aBuffer.GetDataPtr(), aBuffer.GetDataLen(), false);
			DataSync aSync(aReader);
			SyncDetails(aSync);
		}
	}
	catch (...) {
		Reset(false);
	}
}

// FUNCTION: POPCAPGAME1 0x00421850
void PlayerInfo::Reset(bool param_1)
{
	mUnk0xec = true;
	mUnk0xed = true;
	mUnk0xee = true;
	mUnk0x4c = true;
	mUnk0x54 = 0;
	mUnk0x60 = false;
	mUnk0x61 = true;
	mUnk0xef = false;
	mUnk0x64 = 0;
	mUnk0x68 = 0;
	mUnk0x6c = 0;
	mUnk0x50 = -1;
	mUnk0x70 = 0;
	mUnk0x74 = 0;
	mUnk0x78 = 0;
	mUnk0x7c = 0;
	mUnk0x80 = 0;
	mUnk0x84 = 0;
	mUnk0x88 = 0;
	mUnk0x8c = 0;
	mUnk0x90 = 0;
	mUnk0x94 = 0;
	mUnk0x30 = -1;
	mUnk0x28 = 0;
	mUnk0x2c = 0;
	mUnk0x34 = 0;
	mUnk0x40 = 0;
	mUnk0x44 = 1;
	mUnk0x98 = "";
	mUnk0xb4 = "";
	mUnk0x38 = 0;
	mUnk0x124 = 0;
	mUnk0x128 = 0;
	mUnk0x48 = 0;
	mUnk0x58 = 0;
	mUnk0x3c = 0;
	mUnk0x20c = 0;
	mUnk0x12c.Reset();
	mUnk0x204 = 0;
	mUnk0x208 = 0;

	if (!param_1) {
		mUnk0xfc.clear();
		mUnk0x108.clear();
		mUnk0x118.clear();
		mAdventureScores.clear();
		mUnk0x198.Reset();
	}

	mUnk0x114 = 0;
}

// FUNCTION: POPCAPGAME1 0x0041f820
void PlayerInfo::RestartAdventure()
{
	mUnk0x204 = 0;
	mUnk0x208 = 0;
	mUnk0x20c = 0;
	mUnk0x30 = 0;
	mUnk0x34 = 0;
	mUnk0x61 = true;
	DeleteSavedGame(GameMode::ADVENTURE);
	mUnk0xec = true;
}

// TEMPLATE: POPCAPGAME1 0x0040f340
// std::operator+<char,std::char_traits<char>,std::allocator<char> >(class std::basic_string<char, struct
// std::char_traits<char>, class std::allocator<char>> const &, class std::basic_string<char, struct
// std::char_traits<char>, class std::allocator<char>> const &)

// FUNCTION: POPCAPGAME1 0x00426d60
void PlayerInfo::SaveDetails()
{
	mUnk0xec = false;
	DataWriter aWriter;
	aWriter.OpenMemory(32);
	DataSync aSync(aWriter);
	SyncDetails(aSync);

	// STRING: POPCAPGAME1 0x005d7c78
	std::string aUserData = GetAppDataFolder() + "userdata";
	MkDir(aUserData);

	gSexyApp->WriteBytesToFile(
		GetAppDataFolder() + StrFormat("userdata/user%d.dat", mId),
		aWriter.mMemoryHandle,
		aWriter.mMemoryLength
	);
}

// FUNCTION: POPCAPGAME1 0x00426f00
void PlayerInfo::SaveIfDirty()
{
	if (mUnk0xec) {
		SaveDetails();
	}
}

// FUNCTION: POPCAPGAME1 0x004036e0
void PlayerInfo::SetColorblind(bool isColorblind)
{
	if (isColorblind != mUnk0x60) {
		mUnk0x60 = isColorblind;
		mUnk0xec = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00403750
void PlayerInfo::SetComputerPlayer(bool isComputer)
{
	if (mUnk0x4c != isComputer) {
		mUnk0x4c = isComputer;
		mUnk0xec = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00403770
void PlayerInfo::SetComputerSkill(int theSkill)
{
	if (mUnk0x50 != theSkill) {
		mUnk0x50 = theSkill;
		mUnk0xec = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00403700
void PlayerInfo::SetSelCharacter(int theId)
{
	if (mUnk0x40 != theId) {
		mUnk0x40 = theId;
		mUnk0xec = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00403720
void PlayerInfo::SetSelCharacters(int param_1, int param_2)
{
	if (mUnk0x40 != param_1) {
		mUnk0x40 = param_1;
		mUnk0xec = true;
	}
	if (mUnk0x44 != param_2) {
		mUnk0x44 = param_2;
		mUnk0xec = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00421a00
void PlayerInfo::SubmitAdventureHighScore(int theScore)
{
	mAdventureScores.insert(theScore);

	if (mAdventureScores.size() > 10) {
		std::multiset<int>::iterator anIt;

		anIt = mAdventureScores.begin();
		if (*anIt != theScore) {
			mUnk0xec = true;
		}
		mAdventureScores.erase(anIt);
		return;
	}
	mUnk0xec = true;
}

// STUB: POPCAPGAME1 0x00426980
int PlayerInfo::SyncDetails(DataSync& theSync)
{
	if (theSync.mReader != NULL) {
		Reset(false);
	}

	return 0;
}

// FUNCTION: POPCAPGAME1 0x00403670
void PlayerInfo::SyncSummary(DataSync& theSync)
{
	theSync.SyncString(mName);
	theSync.SyncLong(mUseSeq);
	theSync.SyncLong(mId);
}
