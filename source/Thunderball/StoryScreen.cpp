#include "StoryScreen.h"

#include "ThunderballApp.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "PlayerInfo.h"
#include "Res.h"

#include <SexyAppFramework/HyperlinkWidget.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/Font.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0048d150
StoryScreen::StoryScreen(ThunderballApp* theApp, bool param_2, bool param_3)
{
	mUnk0xd4 = 0;
	mUnk0xd8 = 0;
	mUnk0xdc = 0;
	mUnk0xe4 = 0;
	mUnk0xe8 = 0;
	mUnk0xec = 0;
	mUnk0xf1 = param_2;
	mApp = theApp;
	mUnk0xf2 = param_3;
	mUnk0xcc = -1;
	mUnk0xb8 = 1;

	mUnk0x90 = MakeBottomButton(0, this, "Continue");
	mUnk0x94 = new HyperlinkWidget(0, this);

	mUnk0x94->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp1,62", 0x2e)));
	mUnk0x94->mColor = Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp2,63", 0xffff88));
	mUnk0x94->mOverColor = Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp3,64", 0x88ff88));
	mUnk0x94->mDoFinger = true;
	mUnk0x94->mLabel = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp4,66", "Continue");
	mUnk0x94->mUnderlineSize = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp5,67", 0);
	mUnk0x94->mUnderlineOffset = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp6,68", -10);
	int aStringWidth = mUnk0x94->mFont->StringWidth(mUnk0x94->mLabel);

	mUnk0x94->Resize(
		400 - aStringWidth / 2,
		600 - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp7,70", 0x23),
		aStringWidth,
		mUnk0x94->mFont->GetHeight() + ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp8,70", 0x12)
	);

	mUnk0x94->SetVisible(false);

	mUnk0xa0 = 400 - mWidth / 2;
	mUnk0xa4 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp9,74", 0x21e);
	mUnk0x90->Move(mUnk0xa0, mUnk0xa4);

	AddWidget(mUnk0x90);
	AddWidget(mUnk0x94);

	mUnk0x98 = NULL;
	mUnk0x9c = NULL;

	if (mApp->mCurProfile != NULL) {
		mUnk0x9c = mApp->mCurProfile->mUnk0x30;
	}
	if (mUnk0x9c == -1) {
		mUnk0x9c = 0;
	}
	mUnk0xb4 = 0;
	if (!mUnk0xf2) {
		mUnk0xb0 = 0;
	}
	else {
		mUnk0xb0 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp10,100", 900);
	}

	InitText();
}

// SYNTHETIC: POPCAPGAME1 0x0048b5c0
// Sexy::StoryScreen::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x0048b500
StoryScreen::~StoryScreen()
{
}

// STUB: POPCAPGAME1 0x00489ec0
void StoryScreen::ButtonDepress(int theId)
{
}

// FUNCTION: POPCAPGAME1 0x00489ee0
void StoryScreen::MouseDown(int theX, int theY, int theButton)
{
    if (0 < theButton) {
        mUnk0x100 = 0;
        mUnk0xfc = 0;
        mUnk0x108 = 0;
        mUnk0xf4 = 1000000;
        mUnk0x10c = 2;
        MarkDirty();
        
    }
}

// STUB: POPCAPGAME1 0x0048bfa0
void StoryScreen::Draw(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x0048b860
void StoryScreen::DrawOverlay(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x0048f0e0
void StoryScreen::Update()
{
}

// STUB: POPCAPGAME1 0x0048b5f0
void StoryScreen::InitText()
{
}

// STUB: POPCAPGAME1 0x00489d40
void StoryScreen::PlayOdeNote(int noteId)
{
}

// STUB: POPCAPGAME1 0x0048a090
void StoryScreen::DrawFireworks(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x0048ab40
void StoryScreen::DrawStars(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x0048af20
void StoryScreen::DrawWin(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00489fd0
void StoryScreen::DoDrawText(Graphics* g, Rect& param_2, std::vector<StoryData> param_3, int param_4)
{
}

// STUB: POPCAPGAME1 0x0048ee20
void StoryScreen::DoUpdate()
{
}

// STUB: POPCAPGAME1 0x0048d520
void StoryScreen::UpdateParticles()
{
}

// STUB: POPCAPGAME1 0x0048d830
void StoryScreen::UpdateStars()
{
}

// STUB: POPCAPGAME1 0x0048dea0
void StoryScreen::UpdateWin()
{
}
