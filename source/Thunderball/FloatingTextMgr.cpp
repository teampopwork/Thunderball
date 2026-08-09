#include "FloatingTextMgr.h"

#include <SexyAppFramework/Image.h>

#include "ThunderCommon.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00460f70
FloatingText::FloatingText()
{
	mImage = NULL;
	Reset();
}

// FUNCTION: POPCAPGAME1 0x0045c060
FloatingText::~FloatingText()
{
	delete mImage;
}

// FUNCTION: POPCAPGAME1 0x0045c160
void FloatingText::Reset()
{
	delete mImage;
	mImage = NULL;
	mStrings.clear();
	mUnk0x18.clear();
	mUnk0x28.clear();
	mUnk0x38.clear();
	mUnk0x80 = 0;
	mId = 0;
	mUnk0x84 = 0;
	mUnk0x48 = 0;
	mUnk0x88 = 0;
	mUnk0x4c = 0;
	mUnk0x8c = 0;
	mUnk0x50 = 0;
	mUnk0x54 = 0;
	mUnk0x90 = 1.0f;
	mUnk0x5c = 0;
	mUnk0x60 = 0;
	mUnk0x64 = 0;
	mUnk0x68 = 0;
	mUnk0x94 = 0;
	mUnk0x6c = 0;
	mUnk0x98 = 0;
	mUnk0x70 = 0;
	mUnk0x74 = 0;
	mUnk0x78 = 0;
	mUnk0xa4 = 0;
	mUnk0x7c = 0;
	mUnk0xa0 = 0;
	mUnk0x9c = false;
	mUnk0x9d = false;
	mUnk0xb4 = NULL;
	mUnk0xb8 = 0;
	mUnk0xa8 = 0;
	mUnk0xbc = 0;
	mUnk0xac = 0;
	mUnk0xb0 = 0;
}

// FUNCTION: POPCAPGAME1 0x0046e6e0
FloatingTextMgr::FloatingTextMgr()
{
	mNextId = 0;
}

// SYNTHETIC: POPCAPGAME1 0x00471e10
// Sexy::FloatingTextMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0046e710
FloatingTextMgr::~FloatingTextMgr()
{
}

// FUNCTION: POPCAPGAME1 0x004416d0
FloatingText* FloatingTextMgr::GetTextById(int param_1)
{
	for (std::list<FloatingText>::iterator it = mTexts.begin(); it != mTexts.end(); ++it) {
		if (it->mId == param_1) {
			return &*it;
		}
	}
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x00469de0
void FloatingTextMgr::EraseText(int param_1)
{
	for (std::list<FloatingText>::iterator it = mTexts.begin(); it != mTexts.end(); ++it) {
		if (it->mId == param_1) {
			mTexts.erase(it);
			return;
		}
	}
}

// STUB: POPCAPGAME1 0x00441730
void FloatingTextMgr::Draw(Graphics* param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x00469e40
void FloatingTextMgr::Update()
{
}

// FUNCTION: POPCAPGAME1 0x00469d10
void FloatingTextMgr::Clear()
{
	mTexts.clear();
}

// FUNCTION: POPCAPGAME1 0x00469d20
void FloatingTextMgr::AddText()
{
	FloatingText aText;
	mTexts.push_back(aText);
	++mNextId;
	if (mNextId == 0) {
		mNextId = 1;
	}
	mTexts.back().mId = mNextId;
}

// STUB: POPCAPGAME1 0x00471e40
void FloatingTextMgr::SyncState(DataSync& param_1)
{
}
