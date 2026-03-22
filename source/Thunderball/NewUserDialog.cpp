#include "NewUserDialog.h"

#include "ThunderballApp.h"
#include "LoadingScreen.h"
#include "MainMenu.h"
#include "ThunderCommon.h"
#include "ThunderButton.h"
#include "Res.h"

#include <SexyAppFramework/EditWidget.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/WidgetManager.h>
#include <time.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004a9380
NewUserDialog::NewUserDialog(ThunderballApp* theApp, bool param_2, bool param_3, bool param_4) : ThunderDialog(28, true, param_2 ? "New User" : "Rename User", "Please enter your name.", "", 1)
{
    mApp = theApp;
    mUnk0x188 = param_3;

    if (param_2) {
        mWidth = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp654,25", 400);
    }
    else {
        mWidth = IMAGE_MM_CERTIFICATE->mWidth;
    }

    mUnk0x184 = 0;
    mUnk0x1A8 = 0;
    mUnk0x180 = CreateEditWidget(0, this);
    if (mUnk0x188) {
        __time64_t time;
        _time64(&time);
        tm* aTime = _localtime64(&time);
        int aDay = aTime->tm_mday;
        int aYear = aTime->tm_year + 1900;
        int aMonth = aTime->tm_mon + 1;
        mUnk0x18C = StrFormat(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp655,37", "%d / %d / %d"), aMonth, aDay, aYear);
        
        mUnk0x180->SetFont(GetFontById(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp656,39",0x1e)));
        if (!param_4) {
            mNoButton->SetVisible(false);
        }
        mYesButton->SetVisible(false);

        mUnk0x184 = MakeEmbeddedButton(1000, this, IMAGE_MM_CERTIFICATEOK,  true);
        AddWidget(mUnk0x184);

        Color aColor2 = Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp657,48",0x60));
        mUnk0x180->SetColor(2, aColor2);

        Color aColor3 = Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp658,49",0x80));
        mUnk0x180->SetColor(3, aColor3);

        Color aColor4 = Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp659,50",0xffffff));
        mUnk0x180->SetColor(4, aColor4);
    }

    DoNameWidthEnforce(mUnk0x180);
}

// FUNCTION: POPCAPGAME1 0x0049e510
NewUserDialog::~NewUserDialog()
{
    RemoveAllWidgets(true);

    if (mUnk0x180 != 0) {
        delete mUnk0x180;
    }
}

// FUNCTION: POPCAPGAME1 0x00499d70
void NewUserDialog::Draw(Graphics* g)
{
    if (!mUnk0x188) {
        ThunderDialog::Draw(g);
        DrawEditBox(g, mUnk0x180);
    } else {
        g->DrawImage(IMAGE_MM_CERTIFICATE, 0, 0);

        if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp674,147", false)) {
            DrawEditBox(g, mUnk0x180);
        }

        Color aColor = Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp675,150",0x80));
        g->SetColor(aColor);

        g->SetFont(GetFontById(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp676,151",0x1d)));
        Font* aFont = g->GetFont();
        int aWidth = aFont->StringWidth(mUnk0x18C);
        
        g->DrawString(mUnk0x18C, 
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp677,152",0x87) - aWidth / 2,
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp678,152",0x186)
        );

        if (mVisible) {
            g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp679,157", 0xd6cfc0)));
            g->FillRect(0x133,0x164,0x88,0x32);
        }

        if (0 < mUnk0x1A8) {
            DeferOverlay(0);
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00495530
void NewUserDialog::DrawOverlay(Graphics* g)
{
    if (0 < mUnk0x1A8) {
        float fVar1 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp680,177", 0x14);
        Transform aTransform;
        if (mUnk0x1A8 > fVar1) {
            float aScale = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp681,181",2.0f) * (1.0 - (mUnk0x1A8 / fVar1) + 1.0);
            aTransform.Scale(aScale, aScale);
        }

        g->DrawImageTransform(IMAGE_MM_APPROVEDSTAMP, aTransform,
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp682,188",0xfa),
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp683,188",0x131)
        );
    }
}

// FUNCTION: POPCAPGAME1 0x0049cb00
void NewUserDialog::Update()
{
    ThunderDialog::Update();

    if (mUnk0x1A8 != 0) {
        mUnk0x1A8++;
        if (mUnk0x1A8 == ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp672,120",0x4b)) {
            if (mApp->mCurProfile == NULL) {
                mUnk0x1A8 = 0;
                return;
            }

            mApp->KillDialog(24);
            if (mApp->mLoadingScreen != NULL) {
                mApp->mLoadingScreen->mAdventureStartDelay = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp673,129", 0x14);
            }

            mApp->DoScrollOff(mId);
            if (mApp->mMainMenu != NULL) {
                mWidgetManager->SetFocus(mApp->mMainMenu);
            }
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004952e0
int NewUserDialog::GetPreferredHeight(int theWidth)
{
    if (mUnk0x188) {
        return IMAGE_MM_CERTIFICATE->mHeight;
    }
    else {
        return ThunderDialog::GetPreferredHeight(theWidth) + ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp660,72",0x28);
    }
}

// FUNCTION: POPCAPGAME1 0x00495330
void NewUserDialog::AddedToManager(WidgetManager* theWidgetManager)
{
    ThunderDialog::AddedToManager(theWidgetManager);
    AddWidget(mUnk0x180);
    theWidgetManager->SetFocus(mUnk0x180);
}

// FUNCTION: POPCAPGAME1 0x00
void NewUserDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
    ThunderDialog::RemovedFromManager(theWidgetManager);
    RemoveWidget(mUnk0x180);
}

// FUNCTION: POPCAPGAME1 0x004953a0
void NewUserDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
    ThunderDialog::Resize(theX, theY, theWidth, theHeight);

    if (mUnk0x188) {
        mUnk0x184->Move(
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp661,101",0xd2),
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp662,101",0x107)
        );

        mUnk0x180->Resize(
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp663,102",0x91),
            mY + ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp664,102",300),
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp665,102",0xb4),
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp666,102",0x20)
        );

        int iVar5 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp667,104",0x96);

        mNoButton->Resize(
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp668,105",0x136) + mX,
            ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp669,105",0x16d),
            iVar5,
            mNoButton->mHeight
        );

        return;
    }

    mUnk0x180->Resize(mX + 0x30, 
        ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp670,108",0x69) + mY, 
        mWidth - 96,
        ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\NewUserDialog.cpp671,108",0x18)
    );
}

// FUNCTION: POPCAPGAME1 0x00495610
void NewUserDialog::EditWidgetText(int theId, const SexyString& theString)
{
    mApp->DialogButtonDepress(mId, 1000);
}

// FUNCTION: POPCAPGAME1 0x00495630
bool NewUserDialog::AllowChar(int theId, SexyChar theChar)
{
    if ((!isalnum(theChar) && (theChar -= ' '))) {
        return false;
    }
    
    return true;
}