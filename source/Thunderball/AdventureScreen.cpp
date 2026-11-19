#include "AdventureScreen.h"

#include "HighScoreMgr.h"
#include "PlayerInfo.h"
#include "Res.h"
#include "StageMgr.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/MemoryImage.h>
#include <SexyAppFramework/ResourceManager.h>
#include <set>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00488710
void DrawAdventureFrame(Graphics* g, int param_1, int param_2, int param_3, int param_4, const std::string& param_5)
{
	g->SetColor(Color(0, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp14,142", 0x80)));
	g->FillRect(param_1, param_2, param_3, param_4);

	g->SetColor(Color(0, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp15,144", 0x80)));
	g->FillRect(
		param_1,
		param_2 - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp17,145", 0x14),
		param_3,
		ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp16,145", 0x14)
	);

	g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp18,147", 0xe)));
	g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp19,148", 0xffd305)));
	int aWidth = g->GetFont()->StringWidth(param_5);
	g->DrawString(param_5, (param_3 - aWidth) / 2 + param_1, param_2 - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp20,149", 0x10));
	Rect aRect = Rect(
		param_1 + ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp21,153", 8),
		param_2 - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp22,153", 0x1c),
		param_3 + ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp24,153", 0x24),
		param_4 + ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp23,153", 0x10)
	);

	g->DrawImageBox(aRect, IMAGE_DLG_BLUEFRAME);

	if (ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp25,157", false)) {
		Rect aRect2 = IMAGE_DLG_STAGEBAR->GetCelRect(0);
		aRect = Rect(
			param_1 - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp26,160", 4),
			param_2 - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp27,160", 2),
			param_2 + ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp28,160", 9),
			aRect2.mHeight
		);
		g->DrawImageBox(aRect, IMAGE_DLG_STAGEBAR);
	}
}

// SYNTHETIC: POPCAPGAME1 0x004886e0
// Sexy::AdventureScreen::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00488950
AdventureScreen::AdventureScreen(ThunderballApp* theApp)
{
	mApp = theApp;
	mCurProfile = mApp->mCurProfile;
	mWidth = 800;
	mHeight = 600;
	mContinueButton = MakeButton(0, this, "Continue", IMAGE_DLG_BROWNBUTTON1);
	mRestartButton = MakeButton(1, this, "Restart", IMAGE_DLG_BROWNBUTTON1);
	mMainMenuButton = MakeButton(2, this, "Main Menu", IMAGE_DLG_BROWNBUTTON1);

	if (mCurProfile->JustStartingAdventure()) {
		mContinueButton->mLabel = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp0,45", "Start");
	}

	std::string highscore = "_adventure";
	mHighScores = mApp->mHighScoreMgr->GetScores(&highscore, false);

	AddWidget(mContinueButton);
	AddWidget(mRestartButton);
	AddWidget(mMainMenuButton);

	mUnk0x98 = new MemoryImage();
	mUnk0x98->Create(800, 600);
	Graphics g(mUnk0x98);

	int dVar7 = mCurProfile->mUnk0x30;
	if (dVar7 < 0) {
		dVar7 = 0;
	}
	else if (10 < dVar7) {
		dVar7 = 10;
	}

	int dVar16 = 0;
	if (mCurProfile->mUnk0x34 < 0) {
		dVar16 = 0;
	}
	else {
		dVar16 = 5;
		if (mCurProfile->mUnk0x34 < 6) {
			dVar16 = mCurProfile->mUnk0x34;
		}
	}

	StageInfo* stageInfo = mApp->mStageMgr->GetStageInfo(dVar7);
	if (stageInfo != NULL) {
		LevelInfo* levelInfo = stageInfo->GetLevelInfo(dVar16);
		if (levelInfo != 0) {
			std::string fileName = GetFileName(levelInfo->mUnk0x14);
			Image* image = reinterpret_cast<Image*>(mApp->GetImage("levels/" + fileName, true));
			if (image != NULL) {
				g.SetFastStretch(false);
				Rect aRect1 = Rect(0, 0, image->mWidth, image->mHeight);
				int local_54 = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp1,74", 0x41);
				int local_58 = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp2,75", 0x2d);
				int local_34 = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp3,76", 0x41);
				int iVar10 = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp4,77", 0x5f);
				Rect aRect2 = Rect(local_54, local_34, (mUnk0x98->mWidth - iVar10) - local_34, (mUnk0x98->mHeight - local_58) - local_54);
				if (ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp5,80", false)) {
					g.DrawImage(image, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp6,83", 0) + (mWidth - image->mWidth) / 2, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp7,83", 0) + (mHeight - image->mHeight) / 2);
				}
				else {
					g.DrawImage(image, aRect2, aRect1);
				}
			}
		}
	}

	LoadImageById(mApp->mResourceManager, IMAGE_ADV_ADVENTURE_ID);
	LoadImageById(mApp->mResourceManager, IMAGE_ADV_RESTART_COVER_ID);

	g.DrawImage(IMAGE_ADV_ADVENTURE, 0, 0);
	mUnk0x9c = false;
	if (mCurProfile != NULL) {
		std::string name = mCurProfile->GetSavedGameName(mApp->mGameMode);
		if (!name.empty()) {
			mUnk0x9c = mApp->FileExists(name);
		}
	}

	if (((mCurProfile->mUnk0x30 == 0) && (mCurProfile->mUnk0x34 == 0)) &&
		(mUnk0x9c == 0)) {
		mRestartButton->mVisible = false;
	}

	mApp->ClearUpdateBacklog(false);
}

// FUNCTION: POPCAPGAME1 0x004883f0
AdventureScreen::~AdventureScreen()
{
	RemoveAllWidgets(true);
	if (mUnk0x98 != NULL) {
		delete mUnk0x98;
	}
}

// FUNCTION: POPCAPGAME1 0x004884b0
void AdventureScreen::Update()
{
	Widget::Update();
	mMainMenuButton->Move(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp8,130", 199), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp9,130", 0x227));
	mRestartButton->Move(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp10,131", 0x162), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp11,131", 0x227));
	mContinueButton->Move(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp12,132", 0x1fc), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp13,132", 0x227));

	if (mApp->mHasFocus) {
		MarkDirty();
	}
}

// FUNCTION: POPCAPGAME1 0x00489ac0
void AdventureScreen::Draw(Graphics* g)
{
	g->DrawImage(mUnk0x98, 0, 0);
	int stage = mCurProfile->mUnk0x30 + 1;
	if (stage < 0) {
		stage = 0;
	}
	else if (11 < stage) {
		stage = 11;
	}

	int level = mCurProfile->mUnk0x34 + 1;
	if (level < 0) {
		level = 0;
	}
	else if (5 < level) {
		level = 5;
	}

	std::string adventureStr = StrFormat("Adventure Stage %d-%d", stage, level);
	Color aColor = Color(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp57,348", 0xaaffff));
	g->SetColor(aColor);

	g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp58,349", 0x2f)));
	WriteCenteredLine(g, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp59,350", 0x30), adventureStr);
	DrawHighScores(g, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp60,352", 100), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp61,352", 0x78));
	DrawPersonalHighScores(g, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp62,353", 0x1a4), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp63,353", 0x78));
	DrawStats(g, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp64,355", 100), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp65,355", 0x168), false);
	DrawStats(g, ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp66,356", 0x1a4), ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp67,356", 0x168), true);

	if (mCurProfile->mUnk0x30 == 0 && mCurProfile->mUnk0x34 == 0 && !mUnk0x9c) {
		DeferOverlay();
	}
}

// FUNCTION: POPCAPGAME1 0x00488640
void AdventureScreen::DrawOverlay(Graphics* g)
{
	g->DrawImage(
		IMAGE_ADV_RESTART_COVER,
		// STRING: POPCAPGAME1 0x005f2c9c
		ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp68,366", 0x131),
		// STRING: POPCAPGAME1 0x005f2cc8
		ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp69,366", 0x21b),
		// STRING: POPCAPGAME1 0x005f2cf4
		ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp70,366", 0xaa),
		IMAGE_ADV_RESTART_COVER->mHeight
	);
}

// FUNCTION: POPCAPGAME1 0x004886a0
void AdventureScreen::ButtonDepress(int theId)
{
	if (theId == 0) {
		StartGame();
	}
	else if (theId == 1) {
		mApp->DoConfirmRestartAdventureDialog();
	}
	else if (theId == 2) {
		mApp->ShowMainMenu();
	}
}

// FUNCTION: POPCAPGAME1 0x00488470
void AdventureScreen::StartGame()
{
	if (!mApp->IsTrialOver()) {
		if (!mApp->CheckSaveGame(false)) {
			mApp->StartAdventureGame();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00488ec0
void AdventureScreen::DrawHighScores(Graphics* g, int theX, int theY)
{

	// STRING: POPCAPGAME1 0x005f3298
	int frameW = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp29,169", 0x118);
	// STRING: POPCAPGAME1 0x005f326c
	int frameH = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp30,170", 0xbe);
	// STRING: POPCAPGAME1 0x005f3260
	DrawAdventureFrame(g, theX, theY, frameW, frameH, "High Scores");

	g->SetFont(FONT_OVERLOAD12OUTLINE);
	g->SetColor(0xffffff);

	// STRING: POPCAPGAME1 0x005f3234
	int aY = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp31,177", 0x19) + theY;
	int aRank = 1;
	// STRING: POPCAPGAME1 0x005f3208
	int aX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp32,180", 10) + theX;
	// STRING: POPCAPGAME1 0x005f31dc
	int nameX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp33,181", 0x28) + aX;
	// STRING: POPCAPGAME1 0x005f31b0
	int scoreRightX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp34,182", 0xdc) + nameX;
	// STRING: POPCAPGAME1 0x005f3184
	int rowHeight = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp35,183", 0) + g->GetFont()->GetHeight();

	for (std::list<HighScoreEntry>::iterator it = mHighScores->begin(); it != mHighScores->end() && aRank <= 10; ++it, ++aRank) {
		HighScoreEntry& aEntry = *it;
		// STRING: POPCAPGAME1 0x005f312c
		uint hue = (ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp36,190", 0x46) +
					// STRING: POPCAPGAME1 0x005f3158
					aRank * ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp37,190", 0xf5)) &
				   0x800000ff;
		if ((int) hue < 0) {
			hue = (hue - 1 | 0xffffff00) + 1;
		}
		g->SetColor(Color(GetThunderballApp()->HSLToRGB(hue, 0xff, 0x80)));

		g->SetFont(FONT_OVERLOAD12OUTLINE);
		// STRING: POPCAPGAME1 0x005f3128
		g->DrawString(StrFormat("%d.", aRank), aX, aY);
		g->DrawString(aEntry.mName, nameX, aY);

		std::string scoreStr = CommaSeperate(aEntry.mScore);
		g->SetFont(FONT_OVERLOADMONO12);
		g->DrawString(scoreStr, scoreRightX - g->GetFont()->StringWidth(scoreStr), aY);

		aY += rowHeight;
	}

	for (; aRank <= 0xa; ++aRank) {
		g->SetColor(Color(0xffffff));
		g->DrawString(StrFormat("%d.", aRank), aX, aY);
		aY += rowHeight;
	}
}

// FUNCTION: POPCAPGAME1 0x00489290
void AdventureScreen::DrawPersonalHighScores(Graphics* g, int theX, int theY)
{
	int frameW = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp38,217", 0x118);
	int frameH = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp39,218", 0xbe);
	DrawAdventureFrame(g, theX, theY, frameW, frameH, "Your Best Scores");

	g->SetFont(FONT_OVERLOAD12OUTLINE);
	g->SetColor(Color(0xffffff));

	int aRank = 1;
	int aY = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp40,225", 0x19) + theY;
	int aX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp41,228", 10) + theX;
	int nameX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp42,229", 0x28) + aX;
	int scoreRightX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp43,230", 0xdc) + nameX;
	int rowHeight = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp44,231", 0) + g->GetFont()->GetHeight();

	std::multiset<int> scores = mCurProfile->mAdventureScores;
	for (std::multiset<int>::iterator it = scores.begin(); it != scores.end() && aRank <= 10; ++it, ++aRank) {
		int score = *it;

		uint hue = (ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp36,190", 0x46) +
					aRank * ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp37,190", 0xf5)) &
				   0x800000ff;
		if ((int) hue < 0) {
			hue = (hue - 1 | 0xffffff00) + 1;
		}
		g->SetColor(Color(GetThunderballApp()->HSLToRGB(hue, 0xff, 0x80)));

		g->SetFont(FONT_OVERLOAD12OUTLINE);
		g->DrawString(StrFormat("%d.", aRank), aX, aY);

		std::string scoreStr = CommaSeperate(score);
		if (-1 < score) {
			score =  ModVal(0,"SEXY_SEXYMODVAL.\\AdventureScreen.cpp48,259",1);
			if (score != 0) {
				g->DrawString(mCurProfile->mName, nameX, aY);
			}
		}

		g->SetFont(FONT_OVERLOADMONO12);
		g->DrawString(scoreStr, scoreRightX - g->GetFont()->StringWidth(scoreStr), aY);
	}
}

// FUNCTION: POPCAPGAME1 0x004897c0
void AdventureScreen::DrawStats(Graphics* g, int theX, int theY, bool is_current)
{
	int width1 = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp51,295", 0x118);
	int titleX = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp52,296", 0x8c);
	char* title = "Your Current Stats";
	if (!is_current) {
		title = "Your All-Time Stats";
	}
	DrawAdventureFrame(g, theX, theY, width1, titleX, title);
	int yOffset = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp53,301", 0x19);
	g->SetFont(FONT_OVERLOAD12OUTLINE);

	GameStats* stats;
	if (is_current) {
		stats = &this->mCurProfile->mUnk0x12c;
	}
	else {
		stats = &this->mCurProfile->mUnk0x198;
	}
	int rowHeight = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp54,305", 0) + g->GetFont()->GetHeight();
	int x = ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp55,307", 10) + theX;
	int width = (width1 + theX) - ModVal(0, "SEXY_SEXYMODVAL.\\AdventureScreen.cpp56,308", 10);
	g->DoDrawStat(stats->mUnk0x0, x, width, theY + yOffset);
	int y = theY + yOffset + rowHeight;
	g->DoDrawStat(stats->GetTotalFreeBalls(), x, width, y);
	y += rowHeight;
	g->DoDrawStat(stats->GetTotalStyleShots(), x, width, y);
	y += rowHeight;
	g->DoDrawStat(stats->mUnk0x4, x, width, y);
	y += rowHeight;
	g->DoDrawStat(stats->mUnk0x8, x, width, y);
	y += rowHeight;
	int theLastStat;
	if (is_current) {
		g->DoDrawStat(this->mCurProfile->mUnk0x204, x, width, y);
		theLastStat = this->mCurProfile->mUnk0x20c;
	}
	else {
		g->DoDrawStat(this->mCurProfile->mUnk0x104, x, width, y);
		theLastStat = this->mCurProfile->mUnk0x120;
	}
	g->DoDrawStat(theLastStat, x, width, rowHeight + y);
	return;
}
