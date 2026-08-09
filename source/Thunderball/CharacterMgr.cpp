#include "CharacterMgr.h"
#include "ImageMgr.h"
#include "../SexyAppFramework/Image.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00473c30
CharacterMgr::CharacterMgr()
{
	mUnk0x4C = 0.0f;
	mUnk0x50 = 0.0f;
	mUnk0x54 = 0.0f;
	mUnk0x58 = 0.0f;
	mUnk0x5C = 0.0f;
	mUnk0x60 = 0.0f;
	mUnk0x64 = 0.0f;
	mUnk0x68 = 0.0f;
	mUnk0x6C = 0.0f;
	mUnk0x70 = 0.0f;
	mUnk0x80 = 0.0f;
	mUnk0x84 = 0.0f;
	mImageMgr = new ImageMgr();
	mUnk0x48 = 0.0f;
	mImage2 = NULL;
	mCurCharacter = 0;
	mUnk0x78 = 400;
	mUnk0x7C = 70;
	mUnk0x2C = 0;
	mImage1 = NULL;
	mUnk0x90 = 0;
	mUnk0x34 = 0;
	mUnk0x30 = 0;
	mUnk0x40 = 0;
	mUnk0x74 = true;
	mUnk0x45 = false;
}

// SYNTHETIC: POPCAPGAME1 0x004746d0
// Sexy::CharacterMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00473d10
CharacterMgr::~CharacterMgr()
{
	delete mImageMgr;
	delete mImage1;
	delete mImage2;
}

// STUB: POPCAPGAME1 0x00438a10
void CharacterMgr::CalcEyePos(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004410c0
void CharacterMgr::CalcLookPos(Board* theBoard, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00438cf0
void CharacterMgr::CalcPowerupActive(Board* theBoard)
{
}

// STUB: POPCAPGAME1 0x004388a0
void CharacterMgr::CheckCrossEyeFix()
{
}

// FUNCTION: POPCAPGAME1 0x00473d90
void CharacterMgr::Clear(bool param_1)
{
	mUnk0x48 = 0.0f;
	mUnk0x34 = 0;
	mUnk0x30 = 0;
	mUnk0x3C = -2;
	mUnk0x38 = -2;
	mUnk0x45 = false;
	if (param_1) {
		mImageMgr->Clear();
		mCharacters.clear();
	}
}

// STUB: POPCAPGAME1 0x00432920
void CharacterMgr::CreateShooterImage(int param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0054b790
void CharacterMgr::DoCharMove(int param_1, int param_2, bool param_3)
{
}

// FUNCTION: POPCAPGAME1 0x00432d70
void CharacterMgr::DoPowerupBlink(int param_1)
{
	mUnk0x34 = param_1 * 40 - 1;
}

// STUB: POPCAPGAME1 0x00438cf0
void CharacterMgr::DoPowerupCountBlink()
{
}

// STUB: POPCAPGAME1 0x00439350
void CharacterMgr::Draw(Graphics* g, Board* theBoard)
{
}

// STUB: POPCAPGAME1 0x00438e30
void CharacterMgr::DrawBack(Graphics* g1, Graphics* g2, Board* theBoard)
{
}

// STUB: POPCAPGAME1 0x00441230
void CharacterMgr::DrawFront(Graphics* g1, Graphics* g2, Board* theBoard)
{
}

// FUNCTION: POPCAPGAME1 0x00442c90
std::string* CharacterMgr::GetCharacterDesc(int param_1)
{
	CharacterInfo* aCharacter = GetCharacterInfo(param_1);
	if (aCharacter != NULL)
		return &aCharacter->mDescription;

	// GLOBAL: POPCAPGAME1 0x006509d8
	static std::string anEmptyString;
	return &anEmptyString;
}

// FUNCTION: POPCAPGAME1 0x0043e3b0
int CharacterMgr::GetCharacterIdByName(std::string* param_1)
{
	for (int i = 0; i < (int)mCharacters.size(); i++) {
		if (_stricmp(mCharacters[i].mName.c_str(), param_1->c_str()) == 0)
			return i;
	}

	return -1;
}

// FUNCTION: POPCAPGAME1 0x004386e0
CharacterInfo* CharacterMgr::GetCharacterInfo(int param_1)
{
	if (param_1 >= 0 && param_1 < (int)mCharacters.size())
		return &mCharacters[param_1 % mCharacters.size()];
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x00438760
CharacterInfo* CharacterMgr::GetCharacterInfoSafe(int param_1)
{
	int aCount = mCharacters.size();
	unsigned int anIndex;
	if (param_1 < 0)
	{
		int aRemainder = -param_1 % aCount;
		anIndex = aRemainder == 0 ? 0 : aCount - aRemainder;
	}
	else
		anIndex = param_1 % aCount;
	return &mCharacters[anIndex];
}

// FUNCTION: POPCAPGAME1 0x00442c30
std::string* CharacterMgr::GetCharacterName(int param_1)
{
	CharacterInfo* aCharacter = GetCharacterInfo(param_1);
	if (aCharacter != NULL)
		return &aCharacter->mName;

	// GLOBAL: POPCAPGAME1 0x006509b8
	static std::string anEmptyString;
	return &anEmptyString;
}

// FUNCTION: POPCAPGAME1 0x00442cf0
std::string* CharacterMgr::GetCharacterTip(int param_1, unsigned long param_2)
{
	CharacterInfo* aCharacter = GetCharacterInfo(param_1);
	if (aCharacter != NULL && !aCharacter->mTips.empty())
		return &aCharacter->mTips[param_2 % aCharacter->mTips.size()];

	// GLOBAL: POPCAPGAME1 0x006509f8
	static std::string anEmptyString;
	return &anEmptyString;
}

// STUB: POPCAPGAME1 0x00442bd0
int CharacterMgr::GetCurCharFrame(CharacterInfo* param_1)
{
	return 0;
}

// STUB: POPCAPGAME1 0x004747b0
void CharacterMgr::InitDefault()
{
}

// STUB: POPCAPGAME1 0x00474cb0
void CharacterMgr::Load()
{
}

// STUB: POPCAPGAME1 0x00474870
void CharacterMgr::ReadConfig(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x004657c0
void CharacterMgr::ReaderCharacterConfig(ConfigParser* param_1, CharacterInfo* param_2)
{
}

// STUB: POPCAPGAME1 0x00446490
int CharacterMgr::ReadPowerupType(ConfigParser* param_1, std::string* param_2)
{
	return 0;
}

// FUNCTION: POPCAPGAME1 0x0043e460
void CharacterMgr::Resync()
{
	CalcEyePos(true);
}

// STUB: POPCAPGAME1 0x0043e320
int CharacterMgr::SetCurCharacter(int param_1)
{
    return 0;
}

// FUNCTION: POPCAPGAME1 0x00432b30
void CharacterMgr::SetYinYangEye(bool param_1)
{
	if (mUnk0x45 != param_1)
		mUnk0x45 = param_1;
}

// STUB: POPCAPGAME1 0x0043ff10
void CharacterMgr::SyncState(DataSync& theState)
{
}

// STUB: POPCAPGAME1 0x00439830
void CharacterMgr::Update()
{
}

// STUB: POPCAPGAME1 0x00439990
void CharacterMgr::UpdatePaused()
{
}

// FUNCTION: POPCAPGAME1 0x00439a60
void CharacterMgr::UpdateSlowMo()
{
	if (mUnk0x2C != 0 && --mUnk0x2C == 0)
		CalcEyePos(false);
}
