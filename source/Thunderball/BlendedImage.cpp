#include "BlendedImage.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/MemoryImage.h>

#include <math.h> 

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00406960
BlendedImage::BlendedImage()
{
    mUnk0x8 = Rect(0, 0, 0, 0);
    mUnk0x4 = NULL;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mUnk0x18[i][j] = NULL;
        }
    }
}

// SYNTHETIC: POPCAPGAME1 0x00408fc0
// Sexy::BlendedImage::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x004069e0
BlendedImage::~BlendedImage()
{
    DeleteImages();
}

// FUNCTION: POPCAPGAME1 0x00401e70
void BlendedImage::DeleteImages()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mUnk0x18[i][j] != NULL) {
                delete mUnk0x18[i][j];
                mUnk0x18[i][j] = NULL;
            }
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004069b0
void BlendedImage::Create(MemoryImage* param_1, Rect& param_2)
{
    DeleteImages();
    mUnk0x4 = param_1;
    mUnk0x8 = param_2;
}

// FUNCTION: POPCAPGAME1 0x00408ff0
void BlendedImage::Create(MemoryImage* param_1)
{
    Rect aRect = Rect(0, 0, param_1->mWidth, param_1->mHeight);
    Create(param_1, aRect);
}

// FUNCTION: POPCAPGAME1 0x00401d30
void BlendedImage::CreateImage(int param_1, int param_2)
{
    MemoryImage* anImage = new MemoryImage(GetThunderballApp());
    anImage->Create(param_1, param_2);
    Graphics g = Graphics((Image*)anImage);
    ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\BlendedImage.cpp0,51",0.1f);
    float fVar2 =  ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\BlendedImage.cpp1,52",-1.0f);
    g.DrawImageF(mUnk0x4, (param_1 + 1) * 0.25f + fVar2, (param_2 + 1) * 0.25f + fVar2, mUnk0x8);
    mUnk0x18[param_1][param_2] = anImage;
}

// FUNCTION: POPCAPGAME1 0x00401eb0
void BlendedImage::Draw(Graphics* g, float param_2, float param_3)
{
    int iVar1 = (param_2 - floorf(param_2) * 4.0f);
    int iVar2 = (param_3 - floorf(param_3) * 4.0f);
    Image* dVar4 = mUnk0x18[iVar1][iVar2];
    if (dVar4 == NULL) {
        CreateImage(iVar1, iVar2);
        dVar4 = mUnk0x18[iVar1][iVar2];
    }
    
    g->DrawImage(dVar4, (int) param_2, (int) param_3);
}
