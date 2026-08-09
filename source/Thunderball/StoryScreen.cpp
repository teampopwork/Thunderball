#include "StoryScreen.h"

#include "ThunderballApp.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "PlayerInfo.h"
#include "Res.h"
#include "StageMgr.h"
#include "TrophyMgr.h"

#include <SexyAppFramework/HyperlinkWidget.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/ResourceManager.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/SoundInstance.h>

#include <cmath>
#include <string>

using namespace Sexy;

namespace Sexy
{
class StoryParticle {
public:
	float mX;
	float mY;
	float mVX;
	float mVY;
	int mAge;
	int mDuration;
	int mType;
	int mUnk0x1c;

	__declspec(noinline) StoryParticle();
	__declspec(noinline) void Update();
};
}

// FUNCTION: POPCAPGAME1 0x00489ce0
StoryParticle::StoryParticle()
{
	mX = 0.0f;
	mY = 0.0f;
	mVX = 0.0f;
	mVY = 0.0f;
	mAge = 0;
	mDuration = 0;
	mType = 0;
	mUnk0x1c = 0;
}

// FUNCTION: POPCAPGAME1 0x00489d00
void StoryParticle::Update()
{
	++mAge;
	mX += mVX;
	mY += mVY;
	mVY += ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp0,44", 0.01f);
}

// FUNCTION: POPCAPGAME1 0x004e90e0
__declspec(noinline) void StoryParticleList::PushBack(StoryParticle* const& theParticle)
{
	if (mBegin != NULL && mEnd < mCapacity) {
		*mEnd++ = theParticle;
		return;
	}

	int anOldSize = mBegin == NULL ? 0 : (int) (mEnd - mBegin);
	int anOldCapacity = mBegin == NULL ? 0 : (int) (mCapacity - mBegin);
	int aNewCapacity = anOldCapacity == 0 ? 1 : anOldCapacity * 2;
	StoryParticle** aNewBuffer = (StoryParticle**) operator new(aNewCapacity * sizeof(StoryParticle*));
	for (int i = 0; i < anOldSize; ++i)
		aNewBuffer[i] = mBegin[i];
	operator delete(mBegin);
	mBegin = aNewBuffer;
	mEnd = aNewBuffer + anOldSize;
	mCapacity = aNewBuffer + aNewCapacity;
	*mEnd++ = theParticle;
}

// FUNCTION: POPCAPGAME1 0x0048d150
StoryScreen::StoryScreen(ThunderballApp* theApp, bool param_2, bool param_3)
{
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

// FUNCTION: POPCAPGAME1 0x0048b500
StoryScreen::~StoryScreen()
{
	RemoveAllWidgets(true, false);
}

// FUNCTION: POPCAPGAME1 0x00489ec0
void StoryScreen::ButtonDepress(int theId)
{
	if (mUnk0xa8 != 0)
		mApp->ShowMainMenu();
	else
		mApp->ShowBoard(true, true);
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

// FUNCTION: POPCAPGAME1 0x0048bfa0
void StoryScreen::Draw(Graphics* g)
{
    if (mUnk0xa8 != 0) {
        DrawWin(g);
        return;
    }

    g->SetColor(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp200,1068", 0x80));
    g->FillRect(0, 0, mWidth, 20);
    g->FillRect(0, mHeight - 20, mWidth, 20);
    g->FillRect(0, 0, 20, mHeight);
    g->FillRect(mWidth - 20, 0, 20, mHeight);

    int iVar5 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp201,1073",2);
    int iVar6 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp202,1074",4);
    Rect aDialogRect = aDialogRect.Inflate(iVar5, iVar6);
    g->DrawImageBox(aDialogRect, IMAGE_DLG_DIALOGBOX);
    g->DrawImage(IMAGE_DLG_PLAYWIDGET1, mX - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp203,1079", 32), mY - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp204,1079", 20));

    if (mUnk0x98 == 0) {
        return;
    }

    g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp205,1086", 0xddddff)));
    g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp206,1087", 0x2e)));

    char* aList[11] = { 
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
        "Ten",
        "Eleven"
    };

    if (mUnk0x9c < 0 || 10 < mUnk0x9c) {
        WriteCenteredLine(g, ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp208,1092", 0x2d), StrFormat("Stage %d", mUnk0x9c + 1));
    } else {
        WriteCenteredLine(g, ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp207,1090", 0x2d), StrFormat("Stage %s", aList[mUnk0x9c]));
    }

    int aX = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp209,1094", 0x35);
    int aY;
    if (mUnk0x9c == 0 || mApp->mCurProfile == NULL || mApp->mCurProfile->mUnk0x48 != 0) {
        aY = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp210,1095", 200);
    } else {
         aY = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp211,1095", 0x87);
    }

    int aOldX = aX;
    aX = (mWidth - IMAGE_CHR_CHARACTER1->mWidth) - aX;

    int local_48 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp212,1098",0x14);
    Rect aRect1 = Rect(
        ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp213,1100", 0x14) + IMAGE_CHR_CHARACTER1->mWidth + aOldX,
        ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp214,1100", 20) + aY,
        (mWidth - aY) -  ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp215,1101", 0x32),
        0
    );

    Rect aRect2 = Rect(
        ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp216,1103", 0x50),
        aY,
        0,
        mWidth - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp218,1104", 0xa0)
    );

    int iVar7 = mUnk0x9c;
    int local_44 = iVar5 + 1;

    if (!mUnk0x98->mUnk0x8[0].empty() && mUnk0x98->mUnk0x8[0][0].mUnk0x1c >= 0) {
        iVar5 = mUnk0x98->mUnk0x8[0][0].mUnk0x1c;
        
    }

    if (!mUnk0x98->mUnk0x8[1].empty() && mUnk0x98->mUnk0x8[1][0].mUnk0x1c >= 0) {
        local_44 = mUnk0x98->mUnk0x8[1][0].mUnk0x1c;  
    }

    int iVar8 = mUnk0x9c % 10;
    int iVar9 = mUnk0x9c % 10;

    for (int i = 0; i < 1; i++) {
        if (mUnk0x10c <= i) break;

        int local_6c = 0xff;
        if (0 < mUnk0x108 && i == mUnk0x10c - 1) {
            local_6c = mUnk0x108 * 0xff / 20;
        }

        g->SetColorizeImages(true);
        g->SetColor(Color(0, ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp219,1128", 0.5f) * local_6c));

        Rect local_94 = aRect1;
        if (iVar5 != 0) {
            local_94 = aRect2;
        }

        local_94.Inflate(
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp220,1131",10), 
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp221,1131",10)
        );

        local_94.mWidth = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp222,1132", 0xbe);
        g->DrawImageBox(local_94, IMAGE_DLG_TEXTRECT);
        g->SetColor(Color(0xffffff));

        if (i == 0) {
            DrawCharacterPlusFrame(g, aOldX, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp223,1138",4) + aY, iVar8);
        } else {
            DrawCharacterPlusFrame(g, aX, local_48, iVar9);
            g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp224,1142", 0xbbbbbb)));
            
            int aNewX = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp225,1143",0x14);
            
            g->FillRect(
                aNewX + aOldX,
                local_48 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp226,1146",0x14),
                (IMAGE_CHR_CHARACTER1->mWidth - aNewX) + aX - (aNewX + aOldX),
                ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp227,1146",1)
            );
        }

        g->SetColorizeImages(false);
    }

    g->SetFont(FONT_STAGE);
    mUnk0xf8 = 0;
    g->SetColor(Color(GetColorForCharacter(iVar8)));
    DoDrawText(g, aRect1, mUnk0x98->mUnk0x8[0], ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp228,1156",-1));
    g->SetFont(FONT_OVERLOAD24OUTLINE);

    if (mUnk0xac != 1) {
        aRect2.mY += ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp229,1162", 0x28);
    }

    std::string local_30;
    if (mUnk0xac == 1) {
        local_30 = mUnk0x98->mUnk0x8[1][0].mUnk0x0;
    }
    else {
        local_30 = "A few choice words of\nPeggle Wisdom";
    }

    g->WriteWordWrapped(aRect2, local_30, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp231,1163",0x1e), ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp232,1163",0));

    if (mUnk0x9c != 0 && mApp->mCurProfile != NULL && mApp->mCurProfile->mUnk0x48 == 0) {
        int local_68 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp233,1172",0x35) + mX;
        int iVar10 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp234,1173",0x16f);
        int local_6c = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp235,1174",0x1d1);
        int local_70 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp236,1176",0x40);
        int local_84 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp237,1177",0x2f);
        int local_7c = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp238,1178",0x28);
        int local_74 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp239,1179", 0);
        local_44 = local_68;

        int local_50 = IMAGE_CHR_CHARACTERS->GetCelWidth();
        int local_54 = IMAGE_CHR_CHARACTERS->GetCelHeight();

        g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp240,1185",0x32)));
        g->SetColorizeImages(true);


        g->DrawImageBox(Rect(
            local_68 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp241,1187", 8),
            iVar10 - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp242,1187", 25),
            (local_70 * 11) + ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp243,1187",0xe),
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp244,1187",0x5f)
        ), IMAGE_DLG_TEXTRECT);

        g->DrawImageBox(Rect(
            local_68 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp245,1189",8),
            local_6c - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp246,1189",0x19),
            (local_70 * 11) + ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp247,1189",0xe),
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp248,1189",0x4b)
        ), IMAGE_DLG_TEXTRECT);

        g->SetColorizeImages(false);

        local_30 = StrFormat("Adventure: ^00FF00^%d of 55^oldclr^ Complete", mApp->GetMaxLevel());
        g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp249,1195",0xffffff)));
        g->SetFont(FONT_OVERLOAD16OUTLINE);
        int aStringWidth = (mWidth - g->GetFont()->StringWidth(local_30)) / 2;
        g->DrawStringColor(
            local_30, 
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp250,1197",0x50) + aStringWidth,
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp251,1197",0) + iVar10,
            -1
        );

        local_30 = StrFormat("Challenge: ^00FF00^%d of 75^oldclr^ Complete", 0);
        g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp252,1201",0xffffff)));
        g->SetFont(FONT_OVERLOAD16OUTLINE);
        aStringWidth = (mWidth - g->GetFont()->StringWidth(local_30)) / 2;
        g->DrawStringColor(
            local_30, 
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp253,1203",0x50) + aStringWidth,
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp254,1203",0) + local_6c,
            -1
        );

        for (int i = 0; i < 10; i++) {
            if (mUnk0x9c < i) {
                g->DrawImageCel(IMAGE_CHR_CHARACTERSHADOWS, local_44, iVar10, i);
                g->SetColor(Color(0xffffff, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp255,1214",0x78)));
                g->SetColorizeImages(true);
                g->DrawImage(IMAGE_LS_LOCK_SMALL, local_44, iVar10);
                g->SetColorizeImages(false);
                g->SetColor(Color(0, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp256,1218",0x6e)));
                g->FillRect(local_44, iVar10, local_50, local_54);
            } else {
                g->DrawImageCel(IMAGE_CHR_CHARACTERS, local_44, iVar10, i);
            }

            int iVar11 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp257,1222",5) + local_54;
            ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp258,1223",-1);

            g->DrawImageBox(Rect(
                local_44 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp259,1226",5), 
                iVar10 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp260,1226",8),
                ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp262,1226",0xb) + iVar11,
                ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp261,1226",10) + local_50),
                local_48 == mUnk0x9c ? IMAGE_DLG_SELECTORFRAME : IMAGE_DLG_BLUEFRAME
            );

            local_44 += local_70;
        }

        g->DrawImage(IMAGE_DLG_QUESTIONMARK, local_44, iVar10);
        if (ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp263,1242", true) && mUnk0x9c < 10) {
            g->SetColor(Color(0xffffff, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp264,1244",0x78)));
            g->SetColorizeImages(true);
            g->DrawImage(IMAGE_LS_LOCK_SMALL, local_44, iVar10);
            g->SetColorizeImages(false);
        }

        int iVar12 = ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp265,1249",5) + local_54;

        g->DrawImageBox(Rect(
            local_44 -  ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp267,1253",5),
            iVar10 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp268,1253",7),
            iVar12 + ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp270,1253",10),
            iVar12),
            mUnk0x9c == 10 ? IMAGE_DLG_SELECTORFRAME : IMAGE_DLG_BLUEFRAME
        );

        for (int i = 0; i < 15; i++) {
            Color aColor;
            switch(i) {
            case 0:
            case 1:
            case 2:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp272,1264",0x2a80)));
                break;
            case 3:
            case 4:
            case 5:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp273,1266",0x7a8c)));
                break;
            case 6:
            case 7:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp274,1268",0x4b7807)));
                break;
            case 8:
            case 9:
            case 10:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp275,1270",0x7b8001)));
                break;
            case 0xb:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp276,1272",0x805b00)));
                break;
            case 0xc:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp277,1274",0x801d01)));
                break;
            case 0xd:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp278,1276",0x800a66)));
                break;
            case 0xe:
                g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp279,1278",0x805375)));
                break;
            default:
                break;
            }

            g->FillRect(
                ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp280,1281",0) + iVar10, 
                ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp281,1281",0) + local_6c,
                local_7c,
                local_7c
            );

            g->SetColorizeImages(true);
            g->SetColor(Color(0, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp282,1285",0x32)));
            g->DrawImage(IMAGE_DLG_STARBADGEICON, iVar10, local_6c);
            g->SetColor(Color(0, ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp283,1289",0x50)));
            g->DrawImage(IMAGE_DLG_TINYLOCKED, iVar10, local_6c);
            g->SetColorizeImages(false);

            g->DrawImageBox(Rect(
                    iVar10 - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp284,1294",9),
                    local_6c - ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp285,1294",8),
                    ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp286,1294",0xf) + local_7c,
                    ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp287,1294",0xf) + local_7c),
                IMAGE_DLG_BLUEFRAME
            );
            iVar8 += local_84;
        }
    } 
}

// FUNCTION: POPCAPGAME1 0x0048b860
void StoryScreen::DrawOverlay(Graphics* g)
{
	g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp122,812", 0)));
	if (mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp123,816", 500)) {
		g->FillRect(0, 0, mWidth, mHeight);
		DrawStars(g);

		int anAlpha = 255;
		if (mUnk0xb4 > 450) {
			float aFade = (float) (500 - mUnk0xb4);
			anAlpha = (int) (aFade / 50.0 * 255.0);
		}

		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		g->SetColor(Color(0xffffff, anAlpha));
		Transform aTransform;
		aTransform.RotateRad(
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp124,830", 9.28f) *
			(float) std::sin(
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp125,830", 0.007f) *
				mUnk0xb4));
		g->DrawImageTransform(
			IMAGE_UPSELL_ZEN,
			aTransform,
			(float) ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp126,831", 400),
			(float) ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp127,831", 300));
		g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
	} else if (mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp128,835", 850)) {
		int aCellSize = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp129,837", 40);
		int aColumnDelay = 0;
		int aStartDelay = 21;
		for (int aColumn = 0, aCellX = 0; aCellX < 800;
			++aColumn, aCellX = aColumn * aCellSize, aColumnDelay += 18, aStartDelay += 7) {
			int aCellDelay = aStartDelay;
			int aCellPhase = 0;
			for (int aRow = 0, aCellY = 0; aCellY < 600;
				++aRow, aCellY = aRow * aCellSize, aCellPhase += 23,
				aCellDelay += aColumn + 3) {
				int aTrigger = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp130,844", 500) +
					((aColumnDelay + aCellDelay + aCellPhase) % 8) * 40;
				int anOffsetX = 0;
				int anOffsetY = 0;
				float aScale = 1.0f;
				if (mUnk0xb4 < aTrigger) {
					g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp131,849", 0)));
				} else {
					int aDelta = aTrigger - mUnk0xb4;
					anOffsetY = (int) (
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp133,852", 0.1) *
							aDelta * aDelta +
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp132,852", 6.5) *
							aDelta);
					int aWobble =
						(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp135,853", 117) * aColumn +
							ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp136,853", 37) * aRow) %
							50 - 25;
					anOffsetX = (int) (
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp134,853", 0.2) *
							aDelta * aWobble);
					aScale = 1.0f -
						(float) (mUnk0xb4 - aTrigger) /
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp137,854", 80.0f);
					if (aScale < 0.0f)
						aScale = 0.0f;
					int aBrightness = (int) ((1.0f - aScale) * 255.0);
					g->SetColor(Color(aBrightness, aBrightness, aBrightness));
				}

				int aDrawSize = (int) ((float) aCellSize * aScale);
				g->FillRect(aCellX + anOffsetX, aCellY + anOffsetY, aDrawSize, aDrawSize);
			}
		}
	}

	int anOffset = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp138,867", -600);
	if (mUnk0xb4 >= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp139,868", 50)) {
		if (mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp140,873", 100)) {
			anOffset += ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp141,874", 12) *
				(mUnk0xb4 - 50);
		} else if (mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp142,875", 400)) {
			anOffset = 0;
		} else if (mUnk0xb4 >= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp143,877", 400)) {
			anOffset = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp144,878", 12) *
				(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp145,878", 400) - mUnk0xb4);
		}

		g->DrawImage(
			IMAGE_MM_BJORN,
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp146,881", 0) + anOffset,
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp147,881", 200));
		if (mUnk0xb4 > ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp148,883", 160) &&
			mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp149,883", 340)) {
			g->DrawImage(
				IMAGE_MM_SPEECHBUBBLE,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp150,885", 280) + anOffset,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp151,885", 180));
			g->SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp152,887", 50)));
			g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp153,888", 100)));
			Rect aTextRect(
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp154,890", 280) +
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp155,890", 12) + anOffset,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp156,890", 180) +
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp157,890", 15),
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp158,890", 235),
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp159,890", 80));
			std::string aText = ModVal(
				0,
				"SEXY_SEXYMODVAL.\\StoryScreen.cpp160,891",
				"HANG ON FOLKS!!");
			aTextRect.mY +=
				(aTextRect.mHeight - GetWordWrappedHeight(g, aTextRect.mWidth, aText, 20)) / 2;
			WriteWordWrapped(g, aTextRect, aText, 20, 0);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0048f0e0
void StoryScreen::Update()
{
    Widget::Update();
    if (mUnk0x90->mVisible != false) {
        if (mUnk0x90->mY != mUnk0xa4) {
            mUnk0x90->mY -= ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp81,656",0xf);
            if (mUnk0x90->mY < mUnk0xa4) {
                mUnk0x90->mY = mUnk0xa4;
            }
        }

        if (mUnk0x90->mX != mUnk0xa0) {
            mUnk0x90->mX += ModVal(0,"SEXY_SEXYMODVAL.\\StoryScreen.cpp82,662",0x1e);
            if (mUnk0x90->mX > mUnk0xa0) {
                mUnk0x90->mX = mUnk0xa0;
            }
        }

        MarkDirty();
    }
    DoUpdate();
}

// FUNCTION: POPCAPGAME1 0x0048b5f0
void StoryScreen::InitText()
{
	int aStage = mUnk0x9c;
	if (mUnk0xf1 || aStage > 10)
		aStage = 10;
	else if (aStage < 0)
		aStage = 0;

	mUnk0x98 = mApp->mStageMgr->GetStageInfo(aStage);
	mUnk0xa8 = mUnk0x9c == 11 || mUnk0xf1;
	if (mUnk0xa8) {
		if (!mApp->mResourceManager->LoadResources("Story"))
			mApp->ShowResourceError(true);
		if (!ExtractStoryResources(mApp->mResourceManager))
			mApp->ShowResourceError(true);
		if (mApp->mCurProfile != NULL && !mUnk0xf1)
			mApp->mCurProfile->RestartAdventure();
		if (mUnk0xb0 == 0)
			mApp->PlayMusic(2000, true);
	}
	else {
		mApp->PlayMusic(49, true);
	}

	mUnk0xf0 = false;
	mUnk0xf4 = 0;
	mUnk0x108 = 0;
	mUnk0x10c = 0;
	mUnk0xfc = 0;
	mUnk0x100 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp11,144", 20);
	mUnk0x90->SetVisible(false);
	mUnk0x90->mX = -(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp12,146", 100) + mUnk0x90->mWidth);
	mUnk0x104 = 0.0f;
	mUnk0xac = 0;
	if (!mUnk0xa8) {
		mUnk0xac = 1;
		if (mApp->mCurProfile != NULL) {
			if (mApp->mCurProfile->mUnk0x48 < 4)
				mUnk0xac = mApp->mCurProfile->mUnk0x48 + 1;
			else
				mUnk0xac += rand() % 3 + 1;
		}
		if (mUnk0x98->mUnk0x8[mUnk0xac].empty())
			mUnk0xac = 1;
	}
	mUnk0x94->SetVisible(mUnk0xa8);
}

// FUNCTION: POPCAPGAME1 0x00489d40
void StoryScreen::PlayOdeNote(int noteId)
{
    // GLOBAL: POPCAPGAME1 0x00649e8c
    static const int sNotesList[16] = { 
        4, 4, 5, 7, 7, 5, 4, 2, 0, 0, 2, 4
    };

    SoundInstance* anInstance = mApp->mSoundManager->GetSoundInstance(SOUND_MOUSEOVER);
    if (anInstance != NULL) {
        anInstance->AdjustPitch(sNotesList[noteId]);
        anInstance->Play(false, true);
    }
}

// FUNCTION: POPCAPGAME1 0x0048a090
void StoryScreen::DrawFireworks(Graphics* g)
{
	g->SetColorizeImages(true);
	for (unsigned int i = 0; i < mParticles.Size(); ++i) {
		if (mParticles[i]->mType == 1) {
			int aCel = (int) (((double) mParticles[i]->mAge / mParticles[i]->mDuration) * 30.0);
			g->SetColor(Color(
				0,
				0,
				0,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp161,908", 40) -
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp162,908", 1) * aCel));
			g->DrawImageCel(
				IMAGE_FIREBALLFIRE,
				Rect(
					(int) (mParticles[i]->mX - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp163,909", 4)),
					(int) (mParticles[i]->mY - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp164,909", 4)),
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp165,909", 9),
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp166,909", 9)),
				aCel);
		} else if (mParticles[i]->mType == 0) {
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			g->SetColor(Color(
				mParticles[i]->mUnk0x1c,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp167,914", 120)));
			int aCel = (int) (((double) mParticles[i]->mAge / mParticles[i]->mDuration) * 14.0);
			g->DrawImageCel(
				IMAGE_STORY_BIGSPARKLE,
				Rect(
					(int) (mParticles[i]->mX - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp168,916", 15)),
					(int) (mParticles[i]->mY - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp169,916", 15)),
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp170,916", 30),
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp171,916", 30)),
				aCel);
			g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		} else if (mParticles[i]->mType == 2 || mParticles[i]->mType == 4) {
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			int anAlpha = (int) (255.0 -
				((double) mParticles[i]->mAge / mParticles[i]->mDuration) * 255.0);
			g->SetColor(Color(mParticles[i]->mUnk0x1c, anAlpha));
			const bool isNukeStreak = mParticles[i]->mType == 4;
			g->DrawImage(
				IMAGE_NUKESTREAK,
				(int) (mParticles[i]->mX - ModVal(
					0,
					isNukeStreak ? "SEXY_SEXYMODVAL.\\StoryScreen.cpp177,947" : "SEXY_SEXYMODVAL.\\StoryScreen.cpp172,925",
					6)),
				(int) (mParticles[i]->mY - ModVal(
					0,
					isNukeStreak ? "SEXY_SEXYMODVAL.\\StoryScreen.cpp178,947" : "SEXY_SEXYMODVAL.\\StoryScreen.cpp173,925",
					6)),
				ModVal(
					0,
					isNukeStreak ? "SEXY_SEXYMODVAL.\\StoryScreen.cpp179,947" : "SEXY_SEXYMODVAL.\\StoryScreen.cpp174,925",
					13),
				ModVal(
					0,
					isNukeStreak ? "SEXY_SEXYMODVAL.\\StoryScreen.cpp180,947" : "SEXY_SEXYMODVAL.\\StoryScreen.cpp175,925",
					13));
			g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		} else if (mParticles[i]->mType == 3) {
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
			int anAlpha = (int) (255.0 -
				((double) mParticles[i]->mAge / mParticles[i]->mDuration) * 255.0);
			g->SetColor(Color(mParticles[i]->mUnk0x1c, anAlpha));
			Transform aTransform;
			aTransform.Scale(
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp176,935", 0.75f),
				1.0f);
			aTransform.RotateRad((float) std::atan2(mParticles[i]->mVY, mParticles[i]->mVX) + 3.1415f);
			g->DrawImageTransform(
				IMAGE_STREAK,
				aTransform,
				mParticles[i]->mX,
				mParticles[i]->mY);
			g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		}
	}

	if (mUnk0xcc >= 0) {
		g->SetColor(Color(0xffffff));
		Transform aTransform;
		aTransform.Scale(
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp181,958", 0.75f),
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp182,958", 0.5f));
		aTransform.RotateRad((float) std::atan2(mParticleVY, mParticleVX) + 3.1415f);
		g->DrawImageTransform(IMAGE_STORY_ROCKET, aTransform, mParticleX, mParticleY);
	}
	g->SetColorizeImages(false);
}

// FUNCTION: POPCAPGAME1 0x0048ab40
void StoryScreen::DrawStars(Graphics* g)
{
	g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
	g->SetColorizeImages(true);
	g->SetColor(Color(0xffffff));

	for (unsigned int i = 0; i < mStars.Size(); ++i) {
		if (mStars[i]->mType == 0) {
			Rect aDestRect(
				(int) (mStars[i]->mX - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp183,975", 4)),
				(int) (mStars[i]->mY - ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp184,975", 4)),
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp185,975", 9),
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp186,975", 9));
			g->DrawImageCel(
				IMAGE_STORY_BIGSPARKLE,
				aDestRect,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp187,975", 7));
			continue;
		}

		g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		g->SetColorizeImages(false);
		Image* anImage = IMAGE_FLOWER;
		if (mStars[i]->mType < 5) {
			anImage = GetImageById(mStars[i]->mType + 0x1a0);
		} else {
			switch (mStars[i]->mType) {
			case 6:
				anImage = IMAGE_MAGICHAT;
				break;
			case 7:
				anImage = IMAGE_FEVERSTAR_RED;
				break;
			case 8:
				anImage = IMAGE_FEVERSTAR_GREEN;
				break;
			case 9:
				anImage = IMAGE_FEVERSTAR_BLUE;
				break;
			}
		}

		Transform aTransform;
		if (mStars[i]->mType != 1 && mStars[i]->mType != 6) {
			aTransform.RotateRad((float) (ModVal(
				0,
				"SEXY_SEXYMODVAL.\\StoryScreen.cpp188,1009",
				-0.05) * mStars[i]->mAge));
		}
		g->DrawImageTransform(anImage, aTransform, mStars[i]->mX, mStars[i]->mY);
		g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
		g->SetColorizeImages(true);
	}

	g->SetColorizeImages(false);
	g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
}

// FUNCTION: POPCAPGAME1 0x0048af20
void StoryScreen::DrawWin(Graphics* g)
{
	g->SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp88,722", 0)));
	g->FillRect(0, 0, mWidth, mHeight);
	g->DrawImage(
		IMAGE_STORY_WIN,
		(mWidth - IMAGE_STORY_WIN->mWidth) / 2,
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp89,725", 0));
	g->SetColor(Color(
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp90,727", 107),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp91,727", 49),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp92,727", 173)));
	g->FillRect(
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp93,728", 283),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp94,728", 118),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp95,728", 262),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp96,728", 294));
	g->FillRect(
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp97,729", 313),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp98,729", 232),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp99,729", 412),
		ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp100,729", 20));

	if (mUnk0x98 != NULL) {
		if (mUnk0xf2)
			DeferOverlay(0);

		Graphics aGraphics(*g);
		Rect aClipRect(
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp101,738", 280),
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp102,738", 117),
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp103,738", 266),
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp104,738", 316));
		aGraphics.ClipRect(aClipRect);

		int aStoryTier = 0;
		if (mApp->mCurProfile != NULL &&
			mApp->mTrophyMgr->mTrophyInfos.size() <= mApp->mCurProfile->mUnk0xfc.size()) {
			aStoryTier = 1;
			if (mApp->mStageMgr->mUnk0x1c.size() <= mApp->mCurProfile->mUnk0x118.size())
				aStoryTier = 2;
		}
		if (mUnk0xf2)
			aStoryTier = 3;
		if (mUnk0x98->mUnk0x8[aStoryTier].empty())
			aStoryTier = 0;

		std::vector<StoryData>& aStory = mUnk0x98->mUnk0x8[aStoryTier];
		int aTextY = (int) (ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp105,759", 455) - mUnk0x104);
		int aTextX = aClipRect.mX + aClipRect.mWidth / 2;
		if (aStoryTier < 3) {
			int aTrophyOffset = 0;
			if (aStoryTier == 1)
				aTrophyOffset = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp108,765", 60);
			else if (aStoryTier == 2)
				aTrophyOffset = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp109,765", 125);

			aGraphics.DrawImageCel(
				IMAGE_MM_TROPHIES,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp106,764", 305),
				aTextY + ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp107,765", 160) + aTrophyOffset,
				aStoryTier);
		}

		for (unsigned int i = 1; i < aStory.size(); ++i) {
			StoryData& aStoryData = aStory[i];
			int aSpacing = 0;
			switch (aStoryData.mUnk0x1c) {
			case 0:
				aGraphics.SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp110,774", 14)));
				aGraphics.SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp111,775", 0xffff88)));
				aSpacing = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp112,776", 0);
				break;
			case 1:
				aGraphics.SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp113,780", 48)));
				aGraphics.SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp114,781", 0xffff00)));
				aSpacing = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp115,782", 0);
				break;
			case 2:
				aTextY += ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp116,786", 20);
				continue;
			default:
				aGraphics.SetFont(GetFontById(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp117,790", 51)));
				aGraphics.SetColor(Color(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp118,791", 0xffffaa)));
				aSpacing = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp119,792", 0);
				break;
			}

			aTextY += aGraphics.GetFont()->GetHeight() + aSpacing;
			aGraphics.DrawString(
				aStoryData.mUnk0x0,
				aTextX - aGraphics.GetFont()->StringWidth(aStoryData.mUnk0x0) / 2,
				aTextY);
		}

		g->DrawImage(
			IMAGE_STORY_CLAWS,
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp120,802", 522),
			ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp121,802", 386));
		bool colorizeImages = g->mColorizeImages;
		mUnk0xb8 = colorizeImages;
		if (colorizeImages)
			DrawFireworks(g);
	}
}

// FUNCTION: POPCAPGAME1 0x00489fd0
void StoryScreen::DoDrawText(Graphics* g, Rect& param_2, std::vector<StoryData>& param_3, int param_4)
{
	Rect aRect = param_2;
	StoryData& aStory = param_3[0];
	int aMaxChars = mUnk0xf4 - mUnk0xf8;
	if (aMaxChars > 0) {
		if (!aStory.mUnk0x0.empty()) {
			aRect.mY += g->WriteWordWrapped(
				aRect,
				aStory.mUnk0x0,
				ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp87,708", -1),
				param_4,
				NULL,
				aMaxChars,
				NULL
			);
			mUnk0xf8 += aStory.mUnk0x0.length();
			return;
		}
		aRect.mY += g->GetFont()->GetLineSpacing();
		mUnk0xf8 += aStory.mUnk0x0.length();
	}
}

// FUNCTION: POPCAPGAME1 0x0048ee20
void StoryScreen::DoUpdate()
{
	if (mUnk0xa8) {
		UpdateWin();
		return;
	}
	if (mUnk0xf0)
		return;

	if (mUnk0x100 != 0) {
		if (--mUnk0x100 == 0) {
			++mUnk0x10c;
			mUnk0x108 = 1;
			mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp70,554", 20);
			MarkDirty();
		}
		return;
	}

	if (mUnk0x108 != 0) {
		MarkDirty();
		if (++mUnk0x108 == 20)
			mUnk0x108 = 0;
	}
	if (mUnk0xfc != 0) {
		--mUnk0xfc;
		return;
	}

	if (mUnk0xf4 < 1000000) {
		++mUnk0xf4;
		MarkDirty();
		mApp->PlaySample(SOUND_TYPING);
	}
	if (mUnk0x98 == NULL) {
		mUnk0xf0 = true;
		return;
	}

	std::vector<StoryData>& aStory = mUnk0x98->mUnk0x8[mUnk0xac];
	if (!aStory.empty()) {
		std::string& aText = aStory[0].mUnk0x0;
		int anOffset = mUnk0xf4 - 1;
		if (anOffset >= 0 && anOffset < (int) aText.length()) {
			switch (aText[anOffset]) {
			case '!':
				mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp71,607", 20);
				break;
			case '.':
				mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp72,608", 10);
				break;
			case '?':
				mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp73,609", 20);
				break;
			case ',':
				mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp74,610", 10);
				break;
			default:
				mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp75,613", 2);
				break;
			}

			if (anOffset == aText.length() - 1) {
				if (aStory.size() - 1 == 0)
					mUnk0x100 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp76,620", 50);
				else
					mUnk0xfc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp77,622", 20);
			}
		}

		if (mUnk0xfc == 0) {
			mUnk0xf0 = true;
			mUnk0x90->SetVisible(true);
			mUnk0x90->mUnk0x154 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp78,638", 120);
			mUnk0x90->mUnk0x151 = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp79,639", 1) != 0;
			mUnk0x90->Blink(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp80,640", 1000), true);
			mApp->PlaySample(SOUND_TEXT_WOOSH);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0048d520
void StoryScreen::UpdateParticles()
{
	for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp53,426", 3); ++i) {
		StoryParticle* aParticle = new StoryParticle();
		aParticle->mX = mParticleX + rand() % 3;
		aParticle->mY = mParticleY + rand() % 3 - 1.0f;
		aParticle->mDuration = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp54,433", 30);
		aParticle->mType = 1;

		float anAngle = (float) ((rand() % 100) * 6.283 / 100.0);
		float aSpeed = (float) ((rand() % 10) * (double) ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp55,437", 0.03f));
		aParticle->mVX = (float) sin(anAngle) * aSpeed;
		aParticle->mVY = (float) cos(anAngle) * aSpeed;
		mParticles.PushBackInline(aParticle);
	}

	for (int i = 0; i < mParticles.mEnd - mParticles.mBegin; ++i) {
		StoryParticle* aParticle = mParticles.mBegin[i];
		if (aParticle->mAge >= aParticle->mDuration) {
			delete aParticle;
			mParticles.mBegin[i] = mParticles.mEnd[-1];
			--mParticles.mEnd;
			--i;
		}
		else {
			aParticle->Update();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0048d830
void StoryScreen::UpdateStars()
{
	if (mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp56,468", 400)) {
		for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp57,470", 6); ++i) {
			StoryParticle* aStar = new StoryParticle();
			aStar->mX = (float) (ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp58,474", 400) - 5 + rand() % 10);
			aStar->mY = (float) (ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp59,475", 300) - 5 + rand() % 10);

			float anAngle = (float) ((rand() % 100) * 6.283 / 100.0);
			float aSpeed = (float) ((rand() % 8 + 2) * (double) ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp60,478", 4.2f));
			aStar->mVX = (float) sin(anAngle) * aSpeed;
			aStar->mVY = (float) cos(anAngle) * aSpeed;
			aStar->mType = 0;
			aStar->mDuration = rand() % 30 + 70;

			if (rand() % ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp61,486", 30) == 0 &&
				mUnk0xb4 < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp62,486", 360)) {
				aStar->mType = rand() % ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp63,488", 9) + 1;
				float aLength = (float) sqrt(aStar->mVX * aStar->mVX + aStar->mVY * aStar->mVY);
				if (aLength > 0.0f) {
					aStar->mVX *= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp64,492", 5.0f) / aLength;
					aStar->mVY *= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp65,493", 5.0f) / aLength;
				}
				aStar->mDuration *= 2;
			}

			mStars.PushBack(aStar);
		}
	}

	for (int i = 0; i < mStars.mEnd - mStars.mBegin; ++i) {
		StoryParticle* aStar = mStars.mBegin[i];
		if (aStar->mAge >= aStar->mDuration) {
			delete aStar;
			mStars.mBegin[i] = mStars.mEnd[-1];
			--mStars.mEnd;
			--i;
			continue;
		}

		if (aStar->mType != 0) {
			aStar->mVX += (rand() % 100 - 50) * ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp66,519", 0.005f);
			aStar->mVY += (rand() % 100 - 50) * ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp67,520", 0.005f);
			float aLength = (float) sqrt(aStar->mVX * aStar->mVX + aStar->mVY * aStar->mVY);
			if (aLength > 0.0f) {
				aStar->mVX *= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp68,525", 5.0f) / aLength;
				aStar->mVY *= ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp69,526", 5.0f) / aLength;
			}
		}

		aStar->Update();
	}
}

// FUNCTION: POPCAPGAME1 0x0048dea0
void StoryScreen::UpdateWin()
{
	if (!mApp->mLoaded)
		return;

	if (mUnk0xb0 > 0) {
		++mUnk0xb4;
		--mUnk0xb0;
		UpdateStars();
		if (mUnk0xb4 == ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp13,199", 50))
			mApp->PlaySample(SOUND_POWERUP_ZEN);
		if (mUnk0xb4 >= 500 && mUnk0xb4 < 820 && (mUnk0xb4 - 500) % 40 == 0)
			PlayOdeNote((mUnk0xb4 - 500) / 40);
		if (mUnk0xb0 == 0)
			mApp->PlayMusic(2000, true);
		MarkDirty();
		return;
	}

	if (mUnk0xcc > 0) {
		--mUnk0xcc;
		mParticleX += mParticleVX;
		mParticleY += mParticleVY;
	}
	if (mUnk0xcc < 1) {
		if (mParticleY < 500.0f) {
			int aColor = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp14,227", 0xff5511);
			int aColorChoice = rand();
			if (aColorChoice % 3 == 0)
				aColor = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp15,231", 0x55ff22);
			else if (aColorChoice % 3 == 1)
				aColor = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp16,234", 0x3355ff);

			for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp17,240", 60); ++i) {
				StoryParticle* aParticle = new StoryParticle();
				aParticle->mX = mParticleX + rand() % 10 - 5.0f;
				aParticle->mY = mParticleY + rand() % 10 - 5.0f;
				float anAngle = (float) ((rand() % 100) * 6.283 / 100.0);
				float aSpeed = (rand() % 8 + 2) *
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp18,248", 0.2f);
				aParticle->mVX = (float) sin(anAngle) * aSpeed;
				aParticle->mVY = (float) cos(anAngle) * aSpeed;
				aParticle->mType = 0;
				aParticle->mUnk0x1c = aColor;
				aParticle->mDuration = rand() % 30 + 70;
				mParticles.PushBack(aParticle);
			}

			for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp19,259", 120); ++i) {
				StoryParticle* aParticle = new StoryParticle();
				aParticle->mX = mParticleX + rand() % 10 - 5.0f;
				aParticle->mY = mParticleY + rand() % 10 - 5.0f;
				float anAngle = (float) ((rand() % 100) * 6.283 / 100.0);
				float aSpeed = (rand() % 8 + 2) *
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp20,267", 0.2f);
				aParticle->mVX = (float) sin(anAngle) * aSpeed;
				aParticle->mVY = (float) cos(anAngle) * aSpeed;
				aParticle->mType = 2;
				aParticle->mUnk0x1c = aColor;
				aParticle->mDuration = rand() % 30 + 70;
				mParticles.PushBack(aParticle);
			}

			for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp21,278", 60); ++i) {
				StoryParticle* aParticle = new StoryParticle();
				aParticle->mX = mParticleX + rand() % 8 - 4.0f;
				aParticle->mY = mParticleY + rand() % 8 - 4.0f;
				float anAngle = (float) ((rand() % 100) * 6.283 / 100.0);
				float aSpeed =
					(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp23,286", 10) + rand() % 10) *
					ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp22,286", 0.1f);
				aParticle->mVX = (float) sin(anAngle) * aSpeed;
				aParticle->mVY = (float) cos(anAngle) * aSpeed;
				aParticle->mType = 3;
				aParticle->mUnk0x1c = aColor;
				aParticle->mDuration = rand() % 30 + 70;
				mParticles.PushBackInline(aParticle);
			}

			if (rand() % 2 == 0) {
				for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp24,303", 30); ++i) {
					StoryParticle* aParticle = new StoryParticle();
					aParticle->mX = mParticleX + rand() % 8 - 4.0f;
					aParticle->mY = mParticleY + rand() % 8 - 4.0f;
					float anAngle = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp25,310", 2.2f) +
						(rand() % 100) *
							ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp26,310", 0.4f) / 100.0f;
					float aSpeed =
						(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp28,311", 4) +
							rand() % ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp29,311", 2)) *
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp27,311", 0.2f);
					aParticle->mVX = (float) sin(anAngle) * aSpeed;
					aParticle->mVY = (float) cos(anAngle) * aSpeed;
					aParticle->mType = 4;
					aParticle->mUnk0x1c = aColor;
					aParticle->mDuration = rand() % 30 + 70;
					mParticles.PushBackInline(aParticle);
				}

				for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp30,323", 60); ++i) {
					StoryParticle* aParticle = new StoryParticle();
					aParticle->mX = mParticleX + rand() % 8 - 4.0f;
					aParticle->mY = mParticleY + rand() % 8 - 4.0f;
					float anAngle = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp31,330", -2.2f) -
						(rand() % 100) *
							ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp32,330", 0.4f) / 100.0f;
					float aSpeed =
						(ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp34,331", 4) +
							rand() % ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp35,331", 2)) *
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp33,331", 0.2f);
					aParticle->mVX = (float) sin(anAngle) * aSpeed;
					aParticle->mVY = (float) cos(anAngle) * aSpeed;
					aParticle->mType = 4;
					aParticle->mUnk0x1c = aColor;
					aParticle->mDuration = rand() % 30 + 70;
					mParticles.PushBackInline(aParticle);
				}

				for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp36,346", 90); ++i) {
					StoryParticle* aParticle = new StoryParticle();
					aParticle->mX = mParticleX + rand() % 10 - 5.0f;
					aParticle->mY = mParticleY + rand() % 10 - 5.0f;
					float anAngle = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp37,353", -1.0f) +
						(rand() % 100) *
							ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp38,353", 2.0f) / 100.0f;
					(void) rand();
					float aSpeed = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp40,354", 5) *
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp39,354", 0.2f);
					aParticle->mVX = (float) sin(anAngle) * aSpeed;
					aParticle->mVY = (float) cos(anAngle) * aSpeed;
					aParticle->mType = 4;
					aParticle->mUnk0x1c = aColor;
					aParticle->mDuration = rand() % 30 + 70;
					mParticles.PushBackInline(aParticle);
				}
			} else {
				for (int i = 0; i < ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp41,371", 190); ++i) {
					StoryParticle* aParticle = new StoryParticle();
					aParticle->mX = mParticleX + rand() % 6 - 3.0f;
					aParticle->mY = mParticleY + rand() % 6 - 3.0f;
					float anAngle = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp42,378", 0.0f) +
						(rand() % 100) *
							ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp43,378", 6.283f) / 100.0f;
					float aCosine = (float) cos(anAngle);
					float aSpeed = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp44,379", 0.95f) *
						(aCosine + ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp45,379", 1.0f));
					aParticle->mVX = (float) sin(anAngle) * aSpeed;
					aParticle->mVY = aCosine * aSpeed;
					if (aParticle->mVY > 0.0f)
						aParticle->mVX = (1.0f - aCosine) * aParticle->mVX;
					aParticle->mVY -=
						ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp46,386", 0.75f);
					aParticle->mType = 4;
					aParticle->mUnk0x1c = aColor;
					aParticle->mDuration = rand() % 30 + 70;
					mParticles.PushBackInline(aParticle);
				}
			}

			if (mUpdateCnt > 20 && mUnk0xb8)
				mApp->PlaySample(SOUND_FIREWORKPOP);
		}

		mParticleY = (float) mApp->mHeight;
		float aLaunchSide = rand() % 2 == 0 ? 0.5f : 1.0f;
		mParticleX = (float) (
			((double) (rand() % 500) / 1000.0 + aLaunchSide) *
			mApp->mWidth * 0.5);
		mParticleVX = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp47,404", 0.12f) *
			(10 - rand() % 20);
		mParticleVY = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp48,405", -4.0f);
		mUnk0xcc = ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp49,407", 40) +
			rand() % ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp50,407", 80);
	}
	UpdateParticles();

	mUnk0x104 += ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp51,413", 0.25f);
	if (mUnk0x104 > ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp52,415", 4100.0f))
		mUnk0x104 = 0.0f;

	MarkDirty();
}
