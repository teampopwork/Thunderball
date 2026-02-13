#include "SimpleButton.h"

#include "Res.h"

#include <SexyAppFramework/SexyApp.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00496de0
SimpleButton::SimpleButton(Image* theImage, int theId, ButtonListener* theListener)
    : ButtonWidget(theId, theListener)
{
    mDoFinger = true;
    mImage = theImage;
    // STRING: POPCAPGAME1 0x005fc430
    mUnk0x128 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp820,198",0x88ff88);
    // STRING: POPCAPGAME1 0x005fc2c0
    mUnk0x12c = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp821,199",0x88ff88);
    // STRING: POPCAPGAME1 0x005fc278
    mUnk0x124 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp822,200",0xffff00);
}

// FUNCTION: POPCAPGAME1 0x00496e90
void SimpleButton::Draw(Graphics* g)
{
    int imageX = (mWidth - mImage->mWidth) / 2;
    int imageY = (mHeight - mImage->mHeight) / 2;

    if (mIsDown || mIsOver) {
        if (mIsOver) {
            g->SetColor(Color(mUnk0x124));
        } else {
            g->SetColor(Color(mUnk0x128));
        }
    } else {
        g->SetColor(Color(mUnk0x12c));
    }

    g->SetColorizeImages(true);
    g->DrawImage(mImage, imageX, imageY);
    g->SetColorizeImages(false);
}

// FUNCTION: POPCAPGAME1 0x00496fd0
void SimpleButton::MouseEnter()
{
    ButtonWidget::MouseEnter();
    MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00496ff0
void SimpleButton::MouseLeave()
{
    ButtonWidget::MouseLeave();
    MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00496f60
void SimpleButton::MouseDown(int theX, int theY, int theClickCount) {
    ButtonWidget::MouseDown(theX, theY, theClickCount);
    gSexyApp->PlaySample(SOUND_BUTTON1);
    MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x003c968
void SimpleButton::MouseUp(int theX, int theY) {
    ButtonWidget::MouseUp(theX, theY);
    MarkDirty();
}