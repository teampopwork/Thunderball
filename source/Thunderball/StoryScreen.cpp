#include "StoryScreen.h"

#include "ThunderballApp.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "PlayerInfo.h"
#include "Res.h"
#include "StageMgr.h"

#include <SexyAppFramework/HyperlinkWidget.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/SoundInstance.h>

#include <string>

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

// STUB: POPCAPGAME1 0x0048b860
void StoryScreen::DrawOverlay(Graphics* g)
{
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

// STUB: POPCAPGAME1 0x0048b5f0
void StoryScreen::InitText()
{
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
