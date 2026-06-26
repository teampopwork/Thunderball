#include "Ball.h"
#include "DataSync.h"
#include "ThunderCommon.h"
#include "Board.h"
#include "SoundMgr.h"
#include "ThunderballApp.h"
#include "Res.h"
#include "PegInfo.h"
#include "Poly.h"
#include "BlendedImage.h"

#include <SexyAppFramework/SexyVector.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/SoundInstance.h>

using namespace Sexy;

// GLOBAL: POPCAPGAME1 0x00649d78
float Sexy::Ball::mDefRadius = 6.0f;

// FUNCTION: POPCAPGAME1 0x00480de0
Ball::Ball(bool param_1)
{
    mUnk0xe8 = mCurSortId;
    mUnk0x140 = param_1;
    mUnk0xe4 = 0;
    mUnk0x10 = (param_1 != 0 ? 1 : 0) + 2;
    mUnk0x13c = mDefRadius;
    mUnk0x14c = 0;
    mUnk0x150 = 0;
    mUnk0xf8 = 0;
    mUnk0x154 = 0;
    mUnk0xf4 = 0;
    mUnk0x158 = -1000;
    mUnk0x174 = 0;
    mUnk0x148 = 1000000;
    mUnk0x170 = 0;
    mUnk0x160 = false;
    mUnk0x163 = true;
    mUnk0x161 = false;
    mUnk0x164 = false;
    mUnk0x165 = false;
    mUnk0x142 = false;
    mUnk0x143 = false;
    mUnk0x144 = false;
    mUnk0x145 = false;
    mUnk0x146 = false;
    mUnk0x18c = false;
    mUnk0x18d = false;
    mUnk0x162 = false;
    mUnk0x178 = 0;
    mUnk0x17c = 0;
    mUnk0x180 = 10000;
    mUnk0x184 = 0;
    SetPos(0.0f, 0.0f);
    SetVelocity(0.0f, 0.0f);
}

// SYNTHETIC: POPCAPGAME1 0x0047f130
// Sexy::Ball::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0047dae0
Ball::~Ball()
{
    StopFireballSound();
}

// FUNCTION: POPCAPGAME1 0x00480400
bool Ball::EditGetSetValHook(std::string& param_1, bool param_2)
{
	if (mUnk0x10 == 2) 
    {
        if (EditKeyPrefix(param_1, "mover_")) 
        {
            return false; 
        }
    }

    if (!PhysObj::EditGetSetValHook(param_1, param_2)) 
    {
        return false; 
    }
    {
        if (param_1 == "radius") 
        {
            EditValSyncNum(mUnk0x13c, 2.0, 200.0);
            
            if (param_2) 
            {
                SyncBounds();
                return true;
            }
        }
        return true;
    }

    return true;
}

// STUB: POPCAPGAME1 0x00483410
void Ball::SyncState(DataSync& param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004547a0
int Ball::GetClass()
{
	return 7;
}

// FUNCTION: POPCAPGAME1 0x00474e60
void Ball::SetPos(float param_1, float param_2)
{
    mUnk0xec = param_1;
    mUnk0xf0 = param_2;
    mUnk0x14 = param_1 - mUnk0x13c;
    mUnk0x1c = mUnk0x13c + param_1;
    mUnk0x18 = param_2 - mUnk0x13c;
    mUnk0x20 = mUnk0x13c + param_2;
}

// FUNCTION: POPCAPGAME1 0x00474eb0
void Ball::Translate(float param_1, float param_2)
{
    mUnk0xec += param_1;
    mUnk0xf0 += param_2;
    mUnk0x14 += param_1;
    mUnk0x1c += param_1;
    mUnk0x18 += param_2;
    mUnk0x20 += param_2;
}

// FUNCTION: POPCAPGAME1 0x00475600
void Ball::SetVelocity(float param_1, float param_2)
{
    mUnk0xfc = param_1;
    mUnk0x100 = param_2;
}

// STUB: POPCAPGAME1 0x0047a450
void Ball::Update()
{
}

// FUNCTION: POPCAPGAME1 0x0047a8d0
void Ball::UpdateSlowMo(float param_1)
{
    PhysObj::UpdateSlowMo(param_1);
    if (!mUnk0x140) {
        mUnk0x134 = mUnk0xf4 * (1.0f - param_1) + mUnk0xec * param_1;
        mUnk0x138 = mUnk0xf8 * (1.0f - param_1) + mUnk0xf0 * param_1;
    }
}

// FUNCTION: POPCAPGAME1 0x0047b0c0
void Ball::Draw(Graphics* g)
{
    if (mUnk0x10 != 3) {
        if (!mUnk0x18c) {
            float local_c;
            float local_8;
        
            if (!mUnk0x140) {
                local_c = mUnk0x134;
                local_8 = mUnk0x138;
            }
            else {
                local_c = mUnk0xec;
                local_8 = mUnk0xf0;
            }

            if (mUnk0x13c == 6.0f) {
                if (mUnk0x18d) {
                    DrawHat(g);
                }

                local_c -= mUnk0x13c;
                local_8 -= mUnk0x13c;
                g->SetColorizeImages(true);
                g->SetColor(Color(0x60000000));
                g->DrawImageF(IMAGE_BALLSHADOW, local_c - 2.0f, local_8 - 2.0f);
                g->SetColorizeImages(false);
                g->DrawImageF(IMAGE_BALL, local_c, local_8);
                return;
            }

            if (mUnk0x161) {
                if (mUnk0x18d) {
                    DrawHat(g);
                }

                local_c -= mUnk0x13c;
                local_8 -= mUnk0x13c;
                Board* aBoard = GetBoard();
                float fVar3 = 0.0;
                if (aBoard != NULL) {
                    fVar3 = aBoard->mUnk0x1c4 + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp11,1241", 0.05f);
                }

                g->DrawImageRotatedF(IMAGE_FIREBALL, local_c - mUnk0x13c, local_8 - mUnk0x13c, fVar3, NULL);
                return;
            }

            DrawCircle(g, local_c - 2.0f, local_8 - 2.0f, mUnk0x13c, IMAGE_BIGBALLSHADOW, NULL, 0);
            DrawCircle(g, local_c, local_8, mUnk0x13c, IMAGE_BIGBALL, NULL, 0);
        } else {
            if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp10,1200", false)) {
                DrawCircle(g, mUnk0xec, mUnk0xf0, mUnk0x13c, IMAGE_BIGBALL, NULL, 0);
                return;
            }
        }
        return;
    }

    if (mPegInfo != NULL) {
        mPegInfo->DrawBall(this, g);
        return;
    }

    if (mUnk0xb4 != NULL) {
        DrawImage(g, mUnk0xec, mUnk0xf0, 0.0f, g->mIs3D, false);
        return;
    }

    DrawCircle(g, mUnk0xec, mUnk0xf0, mUnk0x13c, IMAGE_DEFINNERPEG, NULL, 0);
    g->SetColorizeImages(true);
    g->SetColor(Color(mUnk0x44));
    DrawCircle(g, mUnk0xec, mUnk0xf0, mUnk0x13c - 1.0f, IMAGE_DEFOUTERPEG, NULL, 0);
    g->SetColorizeImages(false);

}

// FUNCTION: POPCAPGAME1 0x004838f0
void Ball::DrawShadow(Graphics* g)
{
    if (mUnk0x10 == 3) {
        Rect aRect;
        aRect.mHeight = IMAGE_PEGSHADOW->mHeight;
        aRect.mWidth = IMAGE_PEGSHADOW->mWidth;
        float local_c = (mUnk0xec - 3.0f) - mUnk0x13c;
        float local_8 = (mUnk0xf0 - 3.0f) - mUnk0x13c;
        bool bVar1 = mMover == NULL;
        if (bVar1) {
            aRect.mWidth -= 2;
            aRect.mHeight -= 2;
        }
        else {
            local_c -= 1.0f;
            local_8 -= 1.0f;
        }

        aRect.mY = (int)bVar1;
        aRect.mX = (int)bVar1;
        
        g->SetColorizeImages(true);
        g->SetColor(Color(ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp7,1127",0x90)));
        if (!g->mIs3D) {
            if (mUnk0x13c != 10.0f) {
                DrawCircle(g, mUnk0xec - 3.0f, mUnk0xf0 + 3.0f, mUnk0x13c, IMAGE_BIGBALLSHADOW, NULL, 0);
            } else if (mMover == NULL) {
                g->DrawImage(IMAGE_PEGSHADOW, (int)local_c, (int)local_8, aRect);
            } else {
                gBallPegImage[8]->Draw(g, local_c, local_8);
            }
        } else {
            if (mUnk0x13c != 10.0f) {
                DrawCircle(g, mUnk0xec - 3.0f, mUnk0xf0 + 3.0f, mUnk0x13c, IMAGE_BIGBALLSHADOW, NULL, 0);
            } else {
                g->DrawImageF(IMAGE_PEGSHADOW, local_c, local_8, aRect);
            }
        }

        g->SetColorizeImages(false);
        if (mPegInfo != NULL) {
            mPegInfo->DrawGlow(this, g);
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00477070
void Ball::AddedToGame()
{
    mUnk0xf4 = mUnk0xec;
    mUnk0xf8 = mUnk0xf0;
    mUnk0x134 = mUnk0xec;
    mUnk0x138 = mUnk0xf0;
}

// FUNCTION: POPCAPGAME1 0x00474e40
SexyVector2 Ball::GetCenter()
{
	return SexyVector2(mUnk0xec, mUnk0xf0);
}

// FUNCTION: POPCAPGAME1 0x0047df90
float Ball::GetXPos()
{
	return mUnk0xec;
}

// FUNCTION: POPCAPGAME1 0x004547b0
float Ball::GetYPos()
{
	return mUnk0xf0;
}

// FUNCTION: POPCAPGAME1 0x00477a00
bool Ball::IsCollidableWith(PhysObj* param_1)
{
	if (!mUnk0x18c) {
        if (!mUnk0x140 || param_1->mUnk0x10 != 2) {
            if (mUnk0x24 && param_1->mUnk0x24) {
                return true;
            }
        }
    }
    else if (mUnk0x4c < 11) {
        if (param_1->mPegInfo != NULL && param_1->mUnk0x14 != 0 && param_1->mUnk0x24) {
            return true;
        }
    }    

    return false;
}

// FUNCTION: POPCAPGAME1 0x00474dd0
void Ball::SetAbsPos(float param_1, float param_2)
{
    SetPos(param_1, param_2);
    mUnk0xf4 = mUnk0xec;
    mUnk0xf8 = mUnk0xf0;
    mUnk0x134 = mUnk0xec;
    mUnk0x138 = mUnk0xf0;
    mUnk0x104 = mUnk0xec;
    mUnk0x108 = mUnk0xf0;
}

// FUNCTION: POPCAPGAME1 0x00474fc0
void Ball::SyncBounds()
{
    mUnk0x14 = mUnk0xec - mUnk0x13c;
    mUnk0x1c = mUnk0x13c + mUnk0xec;
    mUnk0x18 = mUnk0xf0 - mUnk0x13c;
    mUnk0x20 = mUnk0x13c + mUnk0xf0;
}

// FUNCTION: POPCAPGAME1 0x004770b0
void Ball::SetRadius(float param_1)
{
    mUnk0x13c = param_1;
    SyncBounds();
}

// FUNCTION: POPCAPGAME1 0x00474f00
void Ball::StartFireballSound()
{
    Board* aBoard = GetBoard();
    if ((mUnk0x184 == 0) && (mUnk0x163)) {
        mUnk0x184 = aBoard->mApp->mSoundManager->GetSoundInstance(SOUND_FIREBALLLOOP);
    }

    if (mUnk0x184 != 0) {
        if (!mUnk0x184->IsPlaying()) {
            mUnk0x184->Play(true, true);
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00474f70
void Ball::StopFireballSound()
{
    if (mUnk0x184 != 0) {
        Board* aBoard = GetBoard();
        if (aBoard != NULL) {
            aBoard->mSoundMgr->AddFadeSound(mUnk0x184);
            mUnk0x184 = 0;
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00474fb0
void Ball::SetFireballRadius()
{
    mUnk0x13c = 10.0f;
}

// FUNCTION: POPCAPGAME1 0x004770d0
void Ball::SetFireball(bool param_1)
{
    mUnk0x161 = param_1;
    if (param_1) {
        SetFireballRadius();
        StartFireballSound();
    } else {
        StopFireballSound();
        mUnk0x13c = mDefRadius;
    }
}

// FUNCTION: POPCAPGAME1 0x00475200
void Ball::DoNonCollideUpdate()
{
    Translate(mUnk0xfc, mUnk0x100);
}

// FUNCTION: POPCAPGAME1 0x00477a60
void Ball::DrawHat(Graphics* g)
{
    float fVar2 = mUnk0xfc / ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp8,1164",3.0f);
    if ((-1.0f <= fVar2)) {
        if (fVar2 <= 1.0f) {
            fVar2 *= SEXY_PI / 4;
        } else {
            fVar2 = SEXY_PI / 4;
        }
    } else {
        fVar2 = -SEXY_PI / 4;
    }

    Image* aHatImage = IMAGE_HAT;
    if (mUnk0x140) {
        aHatImage = IMAGE_MAGICHAT;
    }

    g->DrawImageRotatedF(aHatImage, (mUnk0x104 + mUnk0x138 - mUnk0xec) - (aHatImage->mWidth / 2), 
    (mUnk0x108 + mUnk0xfc - mUnk0xf0 - (aHatImage->mHeight / 2)) - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp9,1168", 0x14), fVar2, NULL);
}

// FUNCTION: POPCAPGAME1 0x00475000
bool Ball::CheckCollision(SexyVector2* param_1, SexyVector2* param_2, float param_3, float* param_4, SexyVector2* param_5)
{
    float fVar3 = (mUnk0x13c - 0.01f) + param_3;
    fVar3 = fVar3 * fVar3;

    float fVar1 = mUnk0xec;
    float fVar2 = mUnk0xf0;
    float fVar4 = param_1->x - fVar1;
    float fVar5 = param_1->y - fVar2;

    if (fVar5 * fVar5 + fVar4 * fVar4 < fVar3) {
        *param_4 = 0.0f;
        param_5->x = param_1->x;
        param_5->y = param_1->y;
        return 1;
    }

    float fVar6 = param_2->x * param_2->x + param_2->y * param_2->y;
    fVar5 = fVar5 * param_2->y + param_2->x * fVar4;
    fVar5 = fVar5 + fVar5;

    float fVar4_dup = param_1->x * fVar1 + param_1->y * fVar2;

    if (0.0f <= fVar5 * fVar5 - fVar6 * 4.0f * (((param_1->y * param_1->y + param_1->x * param_1->x + fVar2 * fVar2 + fVar1 * fVar1) - (fVar4_dup + fVar4_dup)) - fVar3)) {
        double fVar7 = param_2->Magnitude();
        float fVar1_res = (-fVar5 - (float)fVar7) / (fVar6 + fVar6);

        if (fVar1_res < 0.0f) {
            fVar1_res = ((float)fVar7 - fVar5) / (fVar6 + fVar6);
        }

        if ((0.0f < fVar1_res) && (fVar1_res < *param_4)) {
            *param_4 = fVar1_res;
            fVar2 = param_2->y;
            fVar3 = param_1->y;
            param_5->x = param_1->x + param_2->x * fVar1_res;
            param_5->y = fVar3 + fVar1_res * fVar2;
            return 1;
        }
    }

    return 0;
}

// FUNCTION: POPCAPGAME1 0x0047f4c0
bool Ball::CheckCollision(PhysObj* param_1, float param_2, float param_3)
{
	SexyVector2 local_1c = SexyVector2(mUnk0xec, mUnk0xf0);
    SexyVector2 local_14 = SexyVector2(mUnk0xfc, mUnk0x100);
    SexyVector2 local_c = SexyVector2(0.0f, 0.0f);
    SexyVector2 local_20 = SexyVector2(0.0f, 0.0f);
    SexyVector2 local_2c = SexyVector2(0.0f, 0.0f);
    SexyVector2 local_34 = SexyVector2(0.0f, 0.0f);
    param_3 += mUnk0x13c;
    if (param_1->mUnk0x10 == 5) {
        if (((Poly*)param_1)->CheckCollision(&local_1c, &local_14, param_3, &param_2, &local_c, &local_20, &local_34, &local_2c)) {
            return true;
        }
    } else if (param_1->mUnk0x10 == 3) {
        if (((Ball*)param_1)->CheckCollision(&local_1c, &local_14, param_3, &param_2, &local_c)) {
            return true;
        }
    }
    return false;
}

// FUNCTION: POPCAPGAME1 0x0047a350
void Ball::SetHoleOut(PhysObj* param_1, int param_2)
{
    if (0 < param_2) {
        SetActive(false);
        mUnk0x14c = param_2;
        mUnk0x15c = param_1;
    } else {
        SetAbsPos(GetXPos(), GetYPos());
    }
}

// FUNCTION: POPCAPGAME1 0x00480f50
void Ball::SetHat(bool param_1, bool param_2)
{
    mUnk0x18d = param_1;
    if (!param_2) {
        if (!param_1) {
            if (mUnk0x188 != NULL) {
                Board* aBoard = GetBoard();
                if (aBoard != NULL) {
                    aBoard->RemoveObj(mUnk0x188.get());
                    mUnk0x188->Release();
                }
            }
        }

        Ball* aBall = mUnk0x188.get();
        if (mUnk0x188 == NULL) {
            mUnk0x188 = new Ball(false);
        }
        aBall->mUnk0x18c = true;
        aBall->mUnk0x161 = true;
        aBall->mUnk0x24 = false;
        aBall->mUnk0x13c = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Ball.cpp0,369", 0x14);
        Board* aBoard = GetBoard();
        if (aBoard != NULL) {
            aBoard->AddObj(aBall);
        }
    } else if (param_1) {
        float fVar3;
        if (mUnk0xec <= 325.0f) {
            fVar3 = mUnk0xec + 200.0f;
        } else {
            fVar3 = mUnk0xec - 200.0f;
        }
        mUnk0x104 = fVar3;
        mUnk0x108 = mUnk0xf0 - 200.0f;
    } else {
        if (mUnk0x188 != NULL) {
            Board* aBoard = GetBoard();
            if (aBoard != NULL) {
                aBoard->RemoveObj(mUnk0x188.get());
                mUnk0x188->Release();
            }
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00477110
void Ball::DoBallBallCollision(Ball* param_1)
{
    SexyVector2 local_2c(param_1->mUnk0xec - mUnk0xec, param_1->mUnk0xf0 - mUnk0xf0);
    SexyVector2 local_24 = local_2c.Normalize();
    float fVar5 = (local_24.y * (mUnk0x100 - param_1->mUnk0x100) + local_24.x * (mUnk0xfc - param_1->mUnk0xfc)) * 0.95f;
    fVar5 += fVar5;

    float fVar4 = fabsf(fVar5);
    param_1->mUnk0x170 = fVar4;
    mUnk0x170 = fVar4;

    fVar5 = fVar5 * 0.5f;

    param_1->mUnk0xfc += fVar5 * local_24.x;
    param_1->mUnk0x100 += fVar5 * local_24.y;
    mUnk0xfc = local_24.x * -fVar5;
    mUnk0x100 = local_24.y * -fVar5;

    float fVar1 = (mUnk0x13c - param_1->mUnk0x13c) - SexyVector2(mUnk0xec - param_1->mUnk0xec, mUnk0xf0 - param_1->mUnk0xf0).Magnitude();
    if (0.0f < fVar1) {
        local_24 *= fVar1;
        param_1->Translate(local_24.x, local_24.y);
        Translate(-local_24.x, -local_24.y);
    }

    if (mNotifyCollisionFunc != NULL) {
        mNotifyCollisionFunc(this, param_1);
    }
}

// STUB: POPCAPGAME1 0x00477340
void Ball::DoBallPegCollision(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x004775b0
void Ball::DoBallCollision(Ball* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0047a3b0
void Ball::CheckBallCollision(Ball* param_1)
{
    SexyVector2 aDelta(param_1->mUnk0xec - mUnk0xec, param_1->mUnk0xf0 - mUnk0xf0);
    aDelta = aDelta.Normalize();

    float aThisVX = mUnk0xfc;
    float aThisVY = mUnk0x100;
    float aOtherVX = param_1->mUnk0xfc;
    float aOtherVY = param_1->mUnk0x100;

    float aImpulse = (aDelta.y * (aThisVY - aOtherVY) + aDelta.x * (aThisVX - aOtherVX)) * 0.95f;
    aImpulse += aImpulse;

    float aCollisionSpeed = fabsf(aImpulse);
    param_1->mUnk0x170 = aCollisionSpeed;
    mUnk0x170 = aCollisionSpeed;

    aImpulse *= 0.5f;
    param_1->mUnk0xfc = aOtherVX + aImpulse * aDelta.x;
    param_1->mUnk0x100 = aDelta.y * aImpulse + aOtherVY;
    mUnk0xfc = aThisVX - aDelta.x * aImpulse;
    mUnk0x100 = aThisVY - aDelta.y * aImpulse;

    float aDx = mUnk0xec - param_1->mUnk0xec;
    float aDy = mUnk0xf0 - param_1->mUnk0xf0;
    float aDistance = SexyVector2(aDx, aDy).Magnitude();
    float aRadiusSum = mUnk0x13c + param_1->mUnk0x13c;

    (void)aDistance;
    (void)aRadiusSum;
}

// STUB: POPCAPGAME1 0x004775f0
void Ball::DoLineCollision(
	SexyVector2* param_1,
	PhysObj* param_2,
	SexyVector2* param_3,
	SexyVector2* param_4,
	SexyVector2* param_5,
	SexyVector2* param_6
)
{
}

// STUB: POPCAPGAME1 0x0047f160
void Ball::DoCollideUpdate(std::vector<PhysObj*>* param_1, SexyVector2* param_2)
{
}
