#include "MainMenu.h"

#include "PlayerInfo.h"
#include "Res.h"
#include "SimpleButton.h"
#include "StageMgr.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderDialog.h"
#include "TrophyMgr.h"

#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/HyperlinkWidget.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/WidgetManager.h>
#include <string>

// GLOBAL: POPCAPGAME1 0x00649f6c
static int BUBBLE_FADE_TIME = 14;

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004a79e0
MainMenu::MainMenu(ThunderballApp* theApp)
{
	mApp = theApp;

	// STRING: POPCAPGAME1 0x006084ec
	mAdventureButton = MakeEmbeddedButton(
		0,
		this,
		IMAGE_MM_ADVENTURE,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp468,52", true)
	);
	mAdventureButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp469,53", 0);
	mAdventureButton->mUnk0x13c = SOUND_MOUSEOVER;

	mSoloButton = MakeEmbeddedButton(
		1,
		this,
		IMAGE_MM_SOLO,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp470,54", true)
	);
	mSoloButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp471,55", 2);
	mSoloButton->mUnk0x13c = SOUND_MOUSEOVER;

	mDuelButton = MakeEmbeddedButton(
		3,
		this,
		IMAGE_MM_DUEL,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp472,56", true)
	);
	mDuelButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp473,57", 5);
	mDuelButton->mUnk0x13c = SOUND_MOUSEOVER;

	mChallengeButton = MakeEmbeddedButton(
		2,
		this,
		IMAGE_MM_CHALLENGE,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp474,58", true)
	);
	mChallengeButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp475,59", 4);
	mChallengeButton->mUnk0x13c = SOUND_MOUSEOVER;

	mReplayButton = MakeButton(4, this, "Replays", IMAGE_DLG_BROWNBUTTON1);
	mReplayButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp476,62", 7);
	mReplayButton->mUnk0x13c = SOUND_MOUSEOVER;

	mOptionsButton = MakeButton(5, this, "Options", IMAGE_DLG_BROWNBUTTON1);
	mOptionsButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp477,64", 9);
	mOptionsButton->mUnk0x13c = SOUND_MOUSEOVER;

	mDemoButton = MakeButton(6, this, "Demos", IMAGE_DLG_BROWNBUTTON1);
	mDemoButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp478,66", 11);
	mDemoButton->mUnk0x13c = SOUND_MOUSEOVER;

	mQuitButton = MakePurpleButton(7, this, "Quit");
	mQuitButton->mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp479,68", 13);
	mQuitButton->mUnk0x13c = SOUND_MOUSEOVER;

	if (mApp->meth_0x405840() || mApp->IsTrialOver() || !mApp->IsRegistered() || !mApp->IsLevelLockedTrial()) {
		mApp->mShouldShowUpsellButton = true;
		mUpsellButton = MakeSimpleButton(9, this, IMAGE_MM_BUYIT, 0, 0);
		mUpsellButton->mUnk0x124 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp481,71", 15);
		mUpsellButton->mUnk0x128 =
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp481,82", 0xffffff);
		mUpsellButton->mUnk0x12c =
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp482,83", 0xffccaa);
		mUpsellButton->mVisible = false;
	}

	mRegisterLink = new HyperlinkWidget(8, this);
	mRegisterLink->SetFont(
		GetFontById(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp483,90", 0x32))
	);
	mRegisterLink->mColor = Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp484,91", 100));
	mRegisterLink->mOverColor =
		Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp485,92", 0xff));
	mRegisterLink->mDoFinger = true;
	mRegisterLink->mLabel = ModVal(
		0,
		"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp486,94",
		"If this is not you, click here."
	);
	mRegisterLink->mUnderlineSize = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp487,95", 0);
	mRegisterLink->mUnderlineOffset = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp488,96", 1);

	int aStringWidth = mRegisterLink->mFont->StringWidth(mRegisterLink->mLabel);

	mRegisterLink->Resize(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp489,99", 0x122) - aStringWidth / 2,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp490,99", 0x1d),
		aStringWidth,
		mRegisterLink->mFont->GetHeight() +
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp491,99", 8)
	);

	mRegisterLink->SetVisible(false);

	AddWidget(mAdventureButton);
	AddWidget(mSoloButton);
	AddWidget(mChallengeButton);
	AddWidget(mDuelButton);
	AddWidget(mReplayButton);
	AddWidget(mOptionsButton);
	AddWidget(mDemoButton);
	AddWidget(mQuitButton);

	if (mUpsellButton != NULL) {
		AddWidget(mUpsellButton);
	}

	AddWidget(mRegisterLink);
	mApp->PlayMusic(3000, true);

	mUnk0xD4 = 0;
	mUnk0xD8 = 0;
	mUnk0xDC = 0;
	mUnk0xE0 = 0;
	mUnk0xC8 = 0;
	mUnk0xBC = 0;
	mUnk0xB8 = 0;
	mUnk0xCC = 0;
	mUnk0xF0 = 0;
	mUnk0xEC = 0;
	mUnk0xE8 = 0;

	mAdventureButton->Resize(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp495,134", 0x24c),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp496,134", 0x1b),
		mAdventureButton->mWidth,
		mAdventureButton->mHeight
	);

	mSoloButton->Resize(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp497,135", 0x24c),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp498,135", 0xac),
		mSoloButton->mWidth,
		mSoloButton->mHeight
	);

	mDuelButton->Resize(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp499,136", 0x24c),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp500,136", 0x1c8),
		mDuelButton->mWidth,
		mDuelButton->mHeight
	);

	mChallengeButton->Resize(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp501,137", 0x24c),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp502,137", 0x13a),
		mChallengeButton->mWidth,
		mChallengeButton->mHeight
	);

	if (mUpsellButton != NULL) {
		mUpsellButton->Move(
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp503,141", 0x1b),
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp504,141", 0x1b)
		);

		mUpsellButton->mVisible = mApp->mShouldShowUpsellButton;
	}

	mQuitButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp505,145", 7),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp506,145", 0x215)
	);

	mDemoButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp507,146", 0x6c),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp508,146", 0x22a)
	);

	mReplayButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp509,147", 0x108),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp510,147", 0x22a)
	);

	mReplayButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp511,148", 0x1a1),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp512,148", 0x22a)
	);

	mRegisterLink->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp513,149", 0x13b),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp514,149", 0x1d)
	);

	SyncPlayerInfo();
}

// SYNTHETIC: POPCAPGAME1 0x00499bf0
// Sexy::MainMenu::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00494990
MainMenu::~MainMenu()
{
	RemoveAllWidgets(true);
}

// FUNCTION: POPCAPGAME1 0x00437350
bool MainMenu::HandleControlClick(int param_1)
{
	return true;
}

// FUNCTION: POPCAPGAME1 0x004afd20
void MainMenu::ButtonDepress(int theId)
{
	if (!HandleControlClick(0)) {
		return;
	}

	mWidth = 0; // ????
	switch (theId) {
	case 0:
		if (mApp->IsTrialOver()) {
			mApp->ViewReplays();
			return;
		}

		mApp->mGameMode = GameMode::ADVENTURE;
		mApp->mUnk0x764 = mX;
		mApp->mUnk0x768 = mY;

		if (mApp->mCurProfile == NULL || (0 < mApp->mCurProfile->mUnk0x48) || !mApp->CheckSaveGame(true)) {
			StartGame();
			return;
		}
		break;
	case 1:
		mApp->mGameMode = GameMode::QUICK_PLAY;
		if (mApp->CheckSaveGame(true)) {
			StartGame();
			return;
		}
		break;
	case 2:
		mApp->mGameMode = GameMode::DUEL;
		if (mApp->CheckSaveGame(true)) {
			StartGame();
			return;
		}
		break;
	case 3:
		mApp->mGameMode = GameMode::CHALLENGE;
		if (mApp->CheckSaveGame(true)) {
			StartGame();
			return;
		}
		break;
	case 4:
		mApp->ViewReplays();
		return;
		break;
	case 5:
		mApp->DoOptionsDialog();
		break;
	case 6:
		if (mApp->mUnk0x83A) {
			mApp->mUnk0x839 = true;
			return;
		}

		if (mApp->mCurProfile != NULL && mApp->mCurProfile->mUnk0x28 < 2) {
			DoNotYet(
				std::string(
					"^FFFF00^DEMO MODE LOCKED!^oldclr^\nThis mode shows how the Masters play.\n\n^FFFF00^To "
					"Unlock:^oldclr^\nFinish Stage 2 of Adventure Mode!"
				)
			);
			return;
		}

		mApp->mGameMode = GameMode::DEMO;
		mApp->ShowBoard(true, true);
		break;
	case 7:
		mApp->DoConfirmQuitDialog();
		break;
	case 8:
		mApp->PlaySample(SOUND_BUTTON1);
		mApp->DoUserDialog();
		break;
	case 9:
		mApp->ShowUpsellScreen();
		break;
	}
}

// GLOBAL: POPCAPGAME1 0x0064a044
static int sNotesList[] = {2, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 2, 1, 1};

// FUNCTION: POPCAPGAME1 0x00494ad0
void MainMenu::ButtonMouseEnter(int theId)
{
	if (theId == sNotesList[mUnk0xD0]) {
		mUnk0xD0++;
	}
	else {
		mUnk0xD0 = 0;
	}

	if (15U <= mUnk0xD0) {
		mApp->ShowStoryScreen(true, true);
	}
}

// FUNCTION: POPCAPGAME1 0x004a90a0
void MainMenu::DoNotYet(std::string& param_1)
{
	ThunderDialog* aDialog = static_cast<ThunderDialog*>(mApp->DoDialog(
		38,
		true,
		// STRING: POPCAPGAME1 0x00609724
		"Locked",
		param_1,
		// STRING: POPCAPGAME1 0x005d6fa8
		"OK",
		3
	));

	aDialog->mUnk0x163 = true;
	aDialog->DoScroll(true);
}

// FUNCTION: POPCAPGAME1 0x004a8c00
void MainMenu::Draw(Graphics* g)
{
	if (0 < mUnk0xF0) {
		int aAlpha = (BUBBLE_FADE_TIME * 2 - mUnk0xF0) * 0x7f / BUBBLE_FADE_TIME;
		g->SetColor(Color(aAlpha, aAlpha, aAlpha));
		g->SetColorizeImages(true);
	}

	g->DrawImage(
		IMAGE_MM_BACKGROUND,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp556,425", 0xf),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp557,425", 0xb)
	);

	g->SetColorizeImages(false);

	// STRING: POPCAPGAME1 0x006095e4
	int SunX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp558,426", -170);
	// STRING: POPCAPGAME1 0x006095a4
	int SunY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp559,427", -190);

	if (g->mIs3D) {
		g->DrawImageRotated(
			IMAGE_SUNGLOW,
			SunX,
			SunY,
			(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp560,432", 0.05) * mUnk0xE4 * 180 / SEXY_PI),
			// STRING: POPCAPGAME1 0x006094e4
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp561,432", 0x18a),
			// STRING: POPCAPGAME1 0x00609524
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp562,432", 0x17f),
			0
		);
	}
	else {
		g->DrawImage(IMAGE_SUNGLOW, SunX, SunY);
	}

	g->DrawImage(
		IMAGE_MM_BLANKSUN,
		// STRING: POPCAPGAME1 0x00609464
		SunX + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp564,437", 0x13f),
		// STRING: POPCAPGAME1 0x006094a4
		SunY + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp563,437", 0x133)
	);

	g->DrawImage(
		IMAGE_MM_FOREGROUND,
		// STRING: POPCAPGAME1 0x006093e4
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp565,438", 0),
		mHeight - IMAGE_MM_FOREGROUND->mHeight -
			// STRING: POPCAPGAME1 0x00609424
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp566,438", 0x3c)
	);

	g->DrawImage(
		IMAGE_MM_BJORN,
		// STRING: POPCAPGAME1 0x00609364
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp567,439", 0xf),
		// STRING: POPCAPGAME1 0x006093a4
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp568,439", 0x82)
	);

	if (0 < mUnk0xD8) {
		DrawSpeechBubble(g, mUnk0xD4, 0xff - (mUnk0xCC * 0xff / BUBBLE_FADE_TIME), true);
	}
	DrawSpeechBubble(g, mUnk0xD4, 0xff, false);

	int aCels = 0;
	if (0 < mUnk0xC8) {
		aCels = mUnk0xC8 - 1;
		if (aCels < 0) {
			aCels = 0;
		}
		else if (2 < aCels) {
			aCels = 2;
		}

		if (mUnk0xEC > mUnk0xE8) {
			int height = IMAGE_MM_TROPHIES->mHeight *
						 ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp571,459", 0.75);
			Graphics aG(*g);
			aG.ClipRect(
				Rect(0x138, height + 0xb5, IMAGE_MM_TROPHIES->mWidth / 3, IMAGE_MM_TROPHIES->mHeight - height)
			);

			aG.DrawImageCel(
				IMAGE_MM_TROPHIES,
				// STRING: POPCAPGAME1 0x006092e4
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp572,462", 0x138),
				// STRING: POPCAPGAME1 0x00609324
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp573,462", 0xb5),
				aCels
			);
		}
		else {
			g->DrawImageCel(
				IMAGE_MM_TROPHIES,
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp572,462", 0x138),
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp573,462", 0xb5),
				aCels
			);
		}
	}

	g->DrawImage(IMAGE_MM_LEFT, 0, 0);

	g->DrawImage(
		IMAGE_MM_TOP,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp574,467", 0x2e),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp575,467", 0)
	);

	g->DrawImage(IMAGE_MM_RIGHT, mWidth - IMAGE_MM_RIGHT->mWidth, 0);

	g->DrawImage(
		IMAGE_MM_BOTTOM,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp576,469", 0x40),
		mHeight - IMAGE_MM_BOTTOM->mHeight
	);

	if (mApp->mCurProfile != NULL) {
		DrawTrophyEffect(g);
		Widget::DeferOverlay(0);
	}
}

// FUNCTION: POPCAPGAME1 0x004a8470
void MainMenu::DrawSpeechBubble(Graphics* g, int param_2, int param_3, bool param_4)
{
	PlayerInfo* aPlayerInfo = mApp->mCurProfile;
	std::string aName;
	int aUnk0x30 = 0;
	int aUnk0x34 = 0;
	bool aUnk0x48 = false;

	if (aPlayerInfo != NULL) {
		aName = aPlayerInfo->mName;
		aUnk0x30 = aPlayerInfo->mUnk0x30;
		aUnk0x34 = aPlayerInfo->mUnk0x34;
		aUnk0x48 = aPlayerInfo->mUnk0x48 > 0;
	}

	int aBubbleX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp518,266", 0x113);
	int aBubbleY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp519,267", 0x38);

	if (param_4 && (aName.length() != 0 || param_2 > 0)) {
		Transform aTransform;
		float aScale = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp520,272", 1.0f);
		if (mUnk0xD8 > 0) {
			float aDiff = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp522,275", 10.0f) - fabs(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp523,275", 10.0f) - mUnk0xD8);
			aScale -= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp521,275", 0.0025f) * aDiff;
		}

		aTransform.Scale(aScale, aScale);
		g->DrawImageTransform(
			IMAGE_MM_SPEECHBUBBLE,
			aTransform,
			IMAGE_MM_SPEECHBUBBLE->mWidth / 2 + aBubbleX,
			IMAGE_MM_SPEECHBUBBLE->mHeight / 2 + 10 + aBubbleY
		);
	}

	int aTextHeight = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp527,282", 0x50);
	int aTextWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp526,282", 0xeb);
	int aTextY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp525,282", 0x14) + aBubbleY;
	int aTextX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp524,282", 0xa) + aBubbleX;

	mUnk0xCC = false;

	if (param_2 > 0) {
		g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp528,287", 0x32)));
		g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp529,288", 100), param_3));

		std::string aString;
		switch (param_2) {
		case 1:
			if (aUnk0x48 && aUnk0x34 > 0 && !mApp->IsTrialOver()) {
				aString = StrFormat(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp532,303", "Continue your adventure on\nStage %d-%d!"), aUnk0x30 + 1, aUnk0x34 + 1);
			}
			else if (aUnk0x30 == -1 && !aUnk0x48) {
				aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp530,296", "New to Peggle?\nClick here to start your adventure!");
			}
			else {
				aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp531,301", "Start a new Adventure!\nCan you get a high score?");
			}
			break;
		case 2:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp533,308", "Play individual levels that you have unlocked in Adventure!");
			break;
		case 3:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp534,312", "Play against a friend or the computer in this two player mode!");
			break;
		case 4:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp535,316", "Complete all of these extra\ndifficult challenges to become a\nPeggle Grand Master!");
			break;
		case 5:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp536,320", "Watch the Peggle Masters play and see if you can learn their tricks!");
			break;
		case 6:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp537,324", "View instant replays\nthat you've saved!");
			break;
		case 7:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp538,328", "Set options like sound volume\nand colorblind mode.\nHelp is also available here.");
			break;
		case 8:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp539,332", "See you again soon!");
			mUnk0xCC = true;
			break;
		case 9:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp540,337", "This trophy is awarded for completing Adventure Mode!");
			break;
		case 10:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp541,341", "This trophy is awarded for beating all of the challenges!");
			break;
		case 11:
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp542,345", "This trophy is awarded for beating all of the challenges and clearing all of the levels!");
			break;
		}

		aTextY += (aTextHeight - GetWordWrappedHeight(g, aTextWidth, aString, 20)) / 2;
		WriteWordWrapped(g, Rect(aTextX, aTextY, aTextWidth, aTextHeight), aString, 20, 0);
	}
	else if (aName.length() != 0) {
		std::string aString;
		if (aUnk0x30 < 0) {
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp543,361", "Welcome to Peggle,");
		}
		else {
			aString = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp544,363", "Welcome Back,");
		}

		g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp545,365", 0x1e)));
		int aTextWidth2 = g->GetFont()->StringWidth(aString);
		int aTextX2 = aBubbleX + (aTextWidth - aTextWidth2) / 2;
		int aTextY2 = aTextY + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp546,367", -10) + g->GetFont()->GetHeight();

		g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp547,369", 0x86065d), param_3));
		g->DrawString(aString, aTextX2, aTextY2);

		aString = aName + "!";
		g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp548,374", 0x1e)));
		aTextY2 += g->GetFont()->GetHeight() + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp549,375", -10);
		aTextWidth2 = g->GetFont()->StringWidth(aString);
		aTextX2 = aBubbleX + (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp550,376", 0xfa) - aTextWidth2) / 2;

		g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp551,379", 0x86065d), param_3));
		g->DrawString(aString, aTextX2, aTextY2);
	}

	if (mUnk0xCC && param_2 == 8) {
		int aAlpha = 0xff;
		if (mUnk0xD8 != 0 && mUnk0xD4 == 8) {
			aAlpha = 0xff - (mUnk0xD8 * 0xff / BUBBLE_FADE_TIME);
		}

		g->SetColorizeImages(true);
		g->SetColor(Color(0xffffff, aAlpha));
		g->DrawImage(IMAGE_MM_CRY, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp552,406", 0xc2), ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp553,406", 0xb2));
		g->SetColorizeImages(false);
	}
}

// FUNCTION: POPCAPGAME1 0x00494b50
void MainMenu::DrawTrophyEffect(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00494aa0
void MainMenu::MouseMove(int x, int y)
{
	Widget::MouseMove(x, y);
	if (mUnk0xC4 == 0) {
		mUnk0xC1 = true;
	}
}

// FUNCTION: POPCAPGAME1 0x00494a00
void MainMenu::Resize(int theX, int theY, int theWidth, int theHeight)
{
	Widget::Resize(theX, theY, theWidth, theHeight);
	// STRING: POPCAPGAME1 0x005fa614
	mUnk0xC4 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp515,166", 10);
	mUnk0xC1 = false;
}

// FUNCTION: POPCAPGAME1 0x00494a40
void MainMenu::SetCurBubble(int param_1, int param_2)
{
	if (mUnk0xD4 != param_1) {
		int Unk0xE0 = mUnk0xE0;
		mUnk0xE0++;

		if (Unk0xE0 >= param_2) {
			mUnk0xD8 = BUBBLE_FADE_TIME;
			mUnk0xDC = mUnk0xD4;
			mUnk0xD4 = param_1;
			mUnk0xE0 = 0;

			MarkDirty();
		}
	}
}

// TEMPLATE: POPCAPGAME1 0x0052db40
// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >
// const,double>::~pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const,double>

// FUNCTION: POPCAPGAME1 0x004a9190
void MainMenu::StartGame()
{
	switch (mApp->mGameMode) {
	case GameMode::ADVENTURE:
		if (mApp->mCurProfile != NULL && (0 < mApp->mCurProfile->mUnk0x48)) {
			if (mApp->mCurProfile->JustBeatAdventure()) {
				mApp->mCurProfile->RestartAdventure();
			}

			mApp->ShowAdventureScreen();
			return;
		}

		mApp->StartAdventureGame();
		return;
	case GameMode::QUICK_PLAY:
	case GameMode::DUEL:
		if (mApp->mGameMode == GameMode::DUEL && mApp->mCurProfile != NULL && (mApp->mCurProfile->mUnk0x28 < 1)) {
			DoNotYet(
				std::string(
					// STRING: POPCAPGAME1 0x006097c8
					"^FFFF00^DUEL MODE LOCKED!^oldclr^\nThis mode lets you compete against a friend or the computer.\n\n^FFFF00^To Unlock:^oldclr^\nFinish Stage 1 of Adventure Mode!"
				)
			);
			return;
		}

		if (mUnk0xC0 && (mApp->mCurProfile != NULL)) {
			mApp->mStageMgr->GetRandomLevel(mApp->mCurProfile, &mApp->mUnk0x764, &mApp->mUnk0x768, false, false, true);
			mApp->ShowBoard(false, true);
			return;
		}

		mApp->ShowLevelScreen(false);
		return;
	case GameMode::CHALLENGE:
		if ((mApp->mCurProfile != NULL && (mApp->mCurProfile->mUnk0x48 <= 0)) ||
			(mApp->IsLevelLockedTrial() && !mApp->IsRegistered())) {
			DoNotYet(
				std::string(
					// STRING: POPCAPGAME1 0x00609730
					"^FFFF00^CHALLENGE MODE LOCKED!^oldclr^\nThis mode presents 75 challenges for advanced players.\n\n^FFFF00^To Unlock:^oldclr^\nComplete Adventure Mode!"
				)
			);
			return;
		}

		mApp->ShowTrophyScreen();
	}
}

// FUNCTION: POPCAPGAME1 0x00494b10
void MainMenu::StartTrophyEffect()
{
	if (1 <= mUnk0xC8 && mUnk0xC8 <= 3) {
		mUnk0xE8 = 0;
		// STRING: POPCAPGAME1 0x005fa654
		mUnk0xEC = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp606,909", 400);
	}
}

// FUNCTION: POPCAPGAME1 0x00499c20
void MainMenu::SyncPlayerInfo()
{
	mUnk0xBC = 0;
	mUnk0xB8 = 0;
	mUnk0xC8 = 0;

	PlayerInfo* aPlayerInfo = mApp->mCurProfile;
	if (aPlayerInfo != NULL) {
		int unk0x114 = aPlayerInfo->mUnk0x114;
		mUnk0xB8 = aPlayerInfo->mUnk0x30;

		mUnk0xBC = aPlayerInfo->mUnk0x34;

		if (mUnk0xB8 < 0) {
			mUnk0xB8 = 0;
		}

		if (mUnk0xBC < 0) {
			mUnk0xBC = 0;
		}

		if (aPlayerInfo->mUnk0x48 > 0) {
			mUnk0xC8 = 1;

			if ((int) aPlayerInfo->mUnk0xfc.size() >= mApp->mTrophyMgr->mUnk0x20) {
				mUnk0xC8 = 2;

				if ((int) aPlayerInfo->mUnk0x118.size() >= mApp->mStageMgr->mUnk0x24) {
					mUnk0xC8 = 3;
				}
			}
		}

		if (unk0x114 < mUnk0xC8) {
			aPlayerInfo->mUnk0x114 = mUnk0xC8;
			StartTrophyEffect();
			aPlayerInfo->SaveDetails();
		}
	}

	// STRING: POPCAPGAME1 0x005fe8ac
	if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp516,208", 0)) {
		bool doBlink;

		if (aPlayerInfo != NULL && aPlayerInfo->GetMaxLevel() == 0) {
			doBlink = true;
		}
		else {
			doBlink = false;
		}

		// how to do this naturally?
		if (doBlink != (bool) (0 < mAdventureButton->mUnk0x14c)) {
			if (doBlink) {
				mAdventureButton->mUnk0x151 = true;
				// STRING: POPCAPGAME1 0x005fe86c
				mAdventureButton->mUnk0x154 =
					ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp517,216", 0x78);
				mAdventureButton->Blink(1000, true);
			}
			else {
				mAdventureButton->StopBlink();
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004af680
void MainMenu::Update()
{
	Widget::Update();
	if (mUnk0xCC == 0) {
		if (0 < mUnk0xF0) {
			mUnk0xF0--;
		}
	}
	else {
		// STRING: POPCAPGAME1 0x0060bf80
		if (mUnk0xF0 < ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp577,527", 0xf)) {
			mUnk0xF0++;
		}
	}

	mAdventureButton->Resize(
		// STRING: POPCAPGAME1 0x0060be40
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp581,538", 0x24c),
		// STRING: POPCAPGAME1 0x0060be80
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp582,538", 0x1b),
		mAdventureButton->mWidth,
		mAdventureButton->mHeight
	);

	mSoloButton->Resize(
		// STRING: POPCAPGAME1 0x0060bdc0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp583,539", 0x241),
		// STRING: POPCAPGAME1 0x0060be00
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp584,539", 0xac),
		mSoloButton->mWidth,
		mSoloButton->mHeight
	);

	mDuelButton->Resize(
		// STRING: POPCAPGAME1 0x0060bd40
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp585,540", 0x24c),
		// STRING: POPCAPGAME1 0x0060bd80
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp586,540", 0x1c8),
		mDuelButton->mWidth,
		mDuelButton->mHeight
	);

	mChallengeButton->Resize(
		// STRING: POPCAPGAME1 0x0060bcc0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp587,541", 0x241),
		// STRING: POPCAPGAME1 0x0060bd00
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp588,541", 0x13a),
		mChallengeButton->mWidth,
		mChallengeButton->mHeight
	);

	if (mUpsellButton != NULL) {
		mUpsellButton->Move(
			// STRING: POPCAPGAME1 0x0060bc40
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp589,545", 0x1b),
			// STRING: POPCAPGAME1 0x0060bc80
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp590,545", 0x1b)
		);

		mUpsellButton->mVisible = mApp->mShouldShowUpsellButton;
	}

	mQuitButton->Move(
		// STRING: POPCAPGAME1 0x0060bbc0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp591,549", 7),
		// STRING: POPCAPGAME1 0x0060bc00
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp592,549", 0x21e)
	);

	mDemoButton->Move(
		// STRING: POPCAPGAME1 0x0060bb40
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp593,550", 0x6c),
		// STRING: POPCAPGAME1 0x0060bb80
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp594,550", 0x22a)
	);

	mOptionsButton->Move(
		// STRING: POPCAPGAME1 0x0060bac0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp595,551", 0x108),
		// STRING: POPCAPGAME1 0x0060bb00
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp596,551", 0x22a)
	);

	mReplayButton->Move(
		// STRING: POPCAPGAME1 0x0060ba40
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp597,552", 0x1a1),
		// STRING: POPCAPGAME1 0x0060ba80
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp598,552", 0x22a)
	);

	mRegisterLink->Move(
		// STRING: POPCAPGAME1 0x0060b9c0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp599,553", 0x13b),
		// STRING: POPCAPGAME1 0x0060ba00
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp600,553", 0x88)
	);

	if (mApp->mDialogMap.size() == 0 && mUnk0xC1) {
		if ((mAdventureButton->mIsOver == 0) && (mAdventureButton->mIsDown == 0)) {
			if ((mSoloButton->mIsOver == 0) && (mSoloButton->mIsDown == 0)) {
				if ((mChallengeButton->mIsOver == 0) && (mChallengeButton->mIsDown == 0)) {
					if ((mDuelButton->mIsOver == 0) && (mDuelButton->mIsDown == 0)) {
						if ((mDemoButton->mIsOver == 0) && (mDemoButton->mIsDown == 0)) {
							if ((mReplayButton->mIsOver == 0) && (mReplayButton->mIsDown == 0)) {
								if ((mOptionsButton->mIsOver == 0) && (mOptionsButton->mIsDown == 0)) {
									if ((mQuitButton->mIsOver == 0) && (mQuitButton->mIsDown == 0)) {
										// STRING: POPCAPGAME1 0x0060b980
										if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp601,573", true) && (0 < mUnk0xC8)) {
											if (Rect(330, 200, 160, 225).Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY)) {
												SetCurBubble(
													mUnk0xC8 + 8,
													// STRING: POPCAPGAME1 0x0060b940
													ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp602,575", 0x32)
												);
											}
											else {
												SetCurBubble(0, 0xf);
											}
										}
									}
									else {
										SetCurBubble(8, 0xf);
									}
								}
								else {
									SetCurBubble(7, 0xf);
								}
							}
							else {
								SetCurBubble(6, 0xf);
							}
						}
						else {
							SetCurBubble(5, 0xf);
						}
					}
					else {
						SetCurBubble(4, 0xf);
					}
				}
				else {
					SetCurBubble(3, 0xf);
				}
			}
			else {
				SetCurBubble(2, 0xf);
			}
		}
		else {
			SetCurBubble(1, 0xf);
		}
	}

	if (mUnk0xC4 != 0) {
		mUnk0xC4--;
	}

	if (0 < mUnk0xD8) {
		mUnk0xD8--;
		MarkDirty();
	}

	if (mRegisterLink->mVisible) {
		if (mApp->mCurProfile == NULL || mUnk0xD4 != 0) {
			mRegisterLink->SetVisible(false);
			MarkDirty();
		}
	}
	else if (mApp->mCurProfile == NULL && mUnk0xD4 == 0) {
		mRegisterLink->SetVisible(true);
		MarkDirty();
	}

	if (mApp->Is3DAccelerated() && mApp->mHasFocus) {
		mUnk0xE4++;
		MarkDirty();
	}

	if (mUnk0xE8 < mUnk0xEC) {
		mUnk0xE8++;
		MarkDirty();

		// STRING: POPCAPGAME1 0x0060b900
		if (mUnk0xE8 == ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp603,612", 0xa0)) {
			mApp->PlaySample(SOUND_AWARD);
		}

		// STRING: POPCAPGAME1 0x0060b8c0
		else if (mUnk0xE8 == ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp604,616", 10)) {
			mApp->PlaySample(SOUND_APPLAUSE);
		}
	}

	// STRING: POPCAPGAME1 0x0060b880
	if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\MainMenu.cpp605,621", false) ||
		mApp->mUnk0x83C && mApp->IsRegistered()) {
		mApp->mUnk0x83C = false;
		mApp->mGameMode = GameMode::ADVENTURE;
		mApp->mUnk0x764 = mApp->mCurProfile->mUnk0x30;
		mApp->mUnk0x768 = mApp->mCurProfile->mUnk0x34;
		StartGame();
		mApp->CheckSaveGame(false);
	}
}
