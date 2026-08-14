#include "CharacterMgr.h"

#include "ConfigParser.h"
#include "ImageMgr.h"
#include "Res.h"

#include <SexyAppFramework/Color.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/MemoryImage.h>


using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0045abd0
CharacterInfo::CharacterInfo()
{
	mName = "Name";
	mUnk0x64 = 0.0f;
	mUnk0x68 = 0.0f;
	mUnk0x24 = NULL;
	mUnk0x28 = NULL;
	mUnk0x20 = 0;
	mUnk0x78 = 1;
	mUnk0x6C = 1;
	mUnk0x70 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp34,64", 6);
	mUnk0x74 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp35,65", 50);
}

CharacterInfo::CharacterInfo(const CharacterInfo& other)
{
	mFrames = other.mFrames;
	mTips = other.mTips;
	mUnk0x20 = other.mUnk0x20;
	mUnk0x24 = other.mUnk0x24;
	mUnk0x28 = other.mUnk0x28;
	mName = other.mName;
	mDescription = other.mDescription;
	mUnk0x64 = other.mUnk0x64;
	mUnk0x68 = other.mUnk0x68;
	mUnk0x6C = other.mUnk0x6C;
	mUnk0x70 = other.mUnk0x70;
	mUnk0x74 = other.mUnk0x74;
	mUnk0x78 = other.mUnk0x78;
}

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

// FUNCTION: POPCAPGAME1 0x00432920
void CharacterMgr::CreateShooterImage(int param_1)
{
	if (mImage2 == NULL) {
		mImage2 = new MemoryImage();
		mImage2->Create(82, 192);
	}
	else {
		mImage2->Clear();
	}

	mImage2->SetImageMode(true, true);
	mImage2->mNumRows = 3;

	Graphics g(mImage2);
	g.DrawImageCel(
		IMAGE_IP_SEAMS,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp36,162", 0),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp37,162", 1),
		param_1
	);

	g.DrawImageCel(
		IMAGE_IP_SEAMS,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp38,163", 0),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp39,163", 65),
		param_1
	);

	g.DrawImageCel(
		IMAGE_IP_SEAMS,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp40,164", 0),
		ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp41,164", 129),
		param_1
	);

	g.DrawImageCel(
		IMAGE_IP_SHOOTER,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp42,165", 10),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp43,165", 3),
		param_1
	);

	g.DrawImageCel(
		IMAGE_IP_SHOOTER,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp44,166", 10),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp45,166", 67),
		param_1
	);

	g.DrawImageCel(
		IMAGE_IP_SHOOTER,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp46,167", 10),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp47,167", 131),
		param_1
	);
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
	if (aCharacter != NULL) {
		return &aCharacter->mDescription;
	}

	// GLOBAL: POPCAPGAME1 0x006509d8
	static std::string anEmptyString;
	return &anEmptyString;
}

// FUNCTION: POPCAPGAME1 0x0043e3b0
int CharacterMgr::GetCharacterIdByName(std::string* param_1)
{
	for (int i = 0; i < (int) mCharacters.size(); i++) {
		if (_stricmp(mCharacters[i].mName.c_str(), param_1->c_str()) == 0) {
			return i;
		}
	}

	return -1;
}

// FUNCTION: POPCAPGAME1 0x004386e0
CharacterInfo* CharacterMgr::GetCharacterInfo(int param_1)
{
	if (param_1 >= 0 && param_1 < (int) mCharacters.size()) {
		return &mCharacters[param_1 % mCharacters.size()];
	}
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x00438760
CharacterInfo* CharacterMgr::GetCharacterInfoSafe(int param_1)
{
	int aCount = mCharacters.size();
	unsigned int anIndex;
	if (param_1 < 0) {
		int aRemainder = -param_1 % aCount;
		anIndex = aRemainder == 0 ? 0 : aCount - aRemainder;
	}
	else {
		anIndex = param_1 % aCount;
	}
	return &mCharacters[anIndex];
}

// FUNCTION: POPCAPGAME1 0x00442c30
std::string* CharacterMgr::GetCharacterName(int param_1)
{
	CharacterInfo* aCharacter = GetCharacterInfo(param_1);
	if (aCharacter != NULL) {
		return &aCharacter->mName;
	}

	// GLOBAL: POPCAPGAME1 0x006509b8
	static std::string anEmptyString;
	return &anEmptyString;
}

// FUNCTION: POPCAPGAME1 0x00442cf0
std::string* CharacterMgr::GetCharacterTip(int param_1, unsigned long param_2)
{
	CharacterInfo* aCharacter = GetCharacterInfo(param_1);
	if (aCharacter != NULL && !aCharacter->mTips.empty()) {
		return &aCharacter->mTips[param_2 % aCharacter->mTips.size()];
	}

	// GLOBAL: POPCAPGAME1 0x006509f8
	static std::string anEmptyString;
	return &anEmptyString;
}

// FUNCTION: POPCAPGAME1 0x00442bd0
int CharacterMgr::GetCurCharFrame(CharacterInfo* param_1)
{
	if (param_1->mFrames.empty()) {
		int iVar1 = param_1->mFrames.size();
		if (iVar1 != 0) {
			if (mUnk0x24 < 1) {
				return param_1->mFrames.back();
			}

			int iVar3 = iVar1 - mUnk0x24;
			if (-1 < iVar3 && iVar3 < iVar1) {
				param_1->mFrames[iVar3];
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004747b0
void CharacterMgr::InitDefault()
{
	Clear(true);
	CharacterInfo aCharacter;
	aCharacter.mUnk0x64 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp48,194", 0x140);
	aCharacter.mUnk0x68 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\CharacterMgr.cpp49,195", 0x28);
	mCharacters.push_back(aCharacter);
}

// FUNCTION: POPCAPGAME1 0x00474cb0
void CharacterMgr::Load()
{
	if (mImage1 == NULL) {
		mImage1 = new MemoryImage();
		mImage1->Create(4, 4);
		Graphics g;
		Color aColor(0);
		g.SetColor(aColor);
		g.FillRect(0, 0, mImage1->GetWidth(), mImage1->GetHeight());
	}

	ReadConfig("characters/characters.cfg");
}

// FUNCTION: POPCAPGAME1 0x00474870
void CharacterMgr::ReadConfig(const std::string& param_1)
{
	Clear(true);

	CharacterInfo aCharacter;
	ConfigParser aConfigParser(true);
	aConfigParser.Open(param_1, true);

	bool foundCharacter = false;
	CharacterInfo* currentCharacter = NULL;

	while (aConfigParser.ReadNext()) {
		if (aConfigParser.mUnk0x9c == 1) {
			if (!aConfigParser.GroupTypeIs("character", 1)) {
				aConfigParser.ErrorUnexpectedGroupType();
				continue;
			}

			if (aConfigParser.mUnk0x58.empty() || aConfigParser.mUnk0x58.back().mUnk0x0.empty()) {
				aConfigParser.Error("Need name for character", false, true);
			}

			mUnk0x24 = -1;
			foundCharacter = true;
			mCharacters.push_back(aCharacter);
			currentCharacter = &mCharacters.back();
			currentCharacter->mName = aConfigParser.mUnk0x58.back().mUnk0x0;
			currentCharacter->mUnk0x64 += (float) mUnk0x78;
			currentCharacter->mUnk0x68 += (float) mUnk0x7C;
		}
		else if (aConfigParser.mUnk0x9c == 2) {
			if (currentCharacter != NULL) {
				ReaderCharacterConfig(&aConfigParser, currentCharacter);
			}
		}
		else if (aConfigParser.mUnk0x9c == 3) {
			currentCharacter = NULL;
		}
	}

	if (!foundCharacter) {
		InitDefault();
	}

	Resync();
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

// FUNCTION: POPCAPGAME1 0x0043e320
int CharacterMgr::SetCurCharacter(int param_1)
{
	if (mCharacters.empty()) {
		return 0;
	}

	int characterCount = (int) mCharacters.size();
	int currentCharacter = mCurCharacter;
	int wraps = 0;
	int newCharacter;

	if (param_1 < 0) {
		int magnitude = -param_1;
		wraps = magnitude / characterCount;
		int remainder = magnitude % characterCount;
		newCharacter = remainder == 0 ? 0 : characterCount - remainder;
	}
	else {
		wraps = param_1 / characterCount;
		newCharacter = param_1 % characterCount;
	}

	mUnk0x40 = 0;
	mCurCharacter = newCharacter;
	if (newCharacter != currentCharacter) {
		CalcEyePos(true);
	}

	return wraps;
}

// FUNCTION: POPCAPGAME1 0x00432b30
void CharacterMgr::SetYinYangEye(bool param_1)
{
	if (mUnk0x45 != param_1) {
		mUnk0x45 = param_1;
	}
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
	if (mUnk0x2C != 0 && --mUnk0x2C == 0) {
		CalcEyePos(false);
	}
}
