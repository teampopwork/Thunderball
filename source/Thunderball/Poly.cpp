#include "Poly.h"

#include "Board.h"
#include "EffectMgr.h"
#include "Line.h"
#include "Mover.h"
#include "Res.h"
#include "SoundMgr.h"
#include "ThunderCommon.h"

#include <SexyAppFramework/SexyVector.h>
#include <vector>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00481670
Poly::Poly()
{
	InitDefaults();
	mUnk0x118 = 0.0f;
	mUnk0x12d = true;
	mUnk0x114 = 0.0f;
	mUnk0x12e = true;
	mUnk0x10 = 5;
	mUnk0x12c = false;
}

/*// STUB: POPCAPGAME1 0x00487c00
Poly::Poly()
{
}*/

// SYNTHETIC: POPCAPGAME1 0x00483300
// Sexy::Poly::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00481770
Poly::~Poly()
{
}

// FUNCTION: POPCAPGAME1 0x00487270
bool Poly::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	bool isMover = false;
	if (!EditKeyPrefix(param_1, "mover_") || mMover == NULL) {
		bool isMover = false;
	}
	else {
		bool isMover = true;
	}

	if (PhysObj::EditGetSetValHook(param_1, param_2)) {
		if (isMover && mMover != NULL) {
			mMover->mRotation = mUnk0x11c;
		}
		return true;
	}

	if (param_1 == "poly_convex") {
		EditValSyncBool(mUnk0x12d);
		return true;
	}
	else if (param_1 == "poly_imagetile") {
		EditValSyncBool(mUnk0x12f);
		return true;
	}
	else if (param_1 == "poly_imagemirror") {
		EditValSyncBool(mUnk0x130);
		return true;
	}
	else if (param_1 == "poly_growtype") {
		EditValSyncNum(mUnk0x13c);
		return true;
	}
	else if (param_1 == "poly_width" || param_1 == "poly_height") {
		if (mUnk0x12c) {
			if (mUnk0xe8.size() == 5) {
				SexyVector2* aPoint0 = mUnk0xe8[0];
				SexyVector2* aPoint2 = mUnk0xe8[2];
				float width = abs(aPoint0->x - aPoint2->x) + 1.0f;
				float height = abs(aPoint0->y - aPoint2->y) + 1.0f;
				if (param_1 == "poly_width") {
					EditValSyncNum(width, 1.0f, 100000.0f);
				}
				else {
					EditValSyncNum(height, 1.0f, 100000.0f);
				}

				if (param_2) {
					InitFromRect(mUnk0x114 + (width - 1.0f) * -0.5, mUnk0x118 + (height - 1.0f) * -0.5, width, height);
				}

				return true;
			}
		}
		else {
			return false;
		}
	}
	else if (param_1 == "poly_normaldir") {
		if (!param_2) {
			SetEditValNum(mUnk0x134);
			return true;
		}
		else {
			int aNormalDir = GetEditValNum();
			if (aNormalDir < -1) {
				SetNormalDir(aNormalDir | -1);
				return true;
			}
			else if (1 < aNormalDir) {
				SetNormalDir(aNormalDir);
				return true;
			}
		}
	}
	else if (param_1 == "poly_rotation") {
		if (!param_2) {
			SetEditValNum(mUnk0x11c * 180.0f / SEXY_PI);
			return true;
		}
		else {
			float aRotation = GetEditValNum();
			SetRotation(aRotation * SEXY_PI / 180.0f);
			return true;
		}
	}
	else if (param_1 == "poly_scale") {
		if (!param_2) {
			SetEditValNum(mUnk0x124);
			return true;
		}
		else {
			float aScale = GetEditValNum();
			SetScale(aScale);
			return true;
		}
	}

	return PhysObj::EditGetSetValHook(param_1, param_2);
}

// FUNCTION: POPCAPGAME1 0x00488010
void Poly::SyncState(DataSync* theSync)
{
	SyncCommon(theSync, true);
}

// FUNCTION: POPCAPGAME1 0x00481720
int Poly::GetClass()
{
	return 3;
}

// FUNCTION: POPCAPGAME1 0x00476e60
void PolyLineHelper(Graphics* g, SexyVector2 param_1, SexyVector2 param_2)
{
	SexyVector2 dir = (param_2 - param_1).Normalize();

	float off_x = dir.y * 3.0;
	float off_y = -dir.x * 3.0;

	int x1 = param_1.x - off_x;
	int y1 = param_1.y - off_y;
	int x2 = param_2.x - off_x;
	int y2 = param_2.y - off_y;

	g->DrawLine(x1, y1, x2, y2);
}

// FUNCTION: POPCAPGAME1 0x0047ea90
void Poly::EditDrawOutline(Graphics* g)
{
	EnsureLines();
	Rect aRect;
	if (GetStandardRect(&aRect)) {
		aRect.mX += -3;
		aRect.mY += -3;
		aRect.mWidth += 6;
		aRect.mHeight += 6;
		g->DrawRect(aRect);
	}
	else {
		for (int i = 0; i < mUnk0x108.size(); i++) {
			Line* aLine = mUnk0x108[i];
			SexyVector2 aPoint0 = SexyVector2(aLine->mUnk0xec, aLine->mUnk0xf4);
			SexyVector2 aPoint1 = SexyVector2(aLine->mUnk0xf0, aLine->mUnk0xf8);
			PolyLineHelper(g, aPoint0, aPoint1);
		}
	}
}

// STUB: POPCAPGAME1 0x0047eb70
void Poly::EditDrawPoints(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x0047edb0
bool Poly::EditContains(float param_1, float param_2, bool param_3)
{
	EnsureLines();
	int local_30 = param_3 ? 20 : 5;

	Rect aRect;
	if (mUnk0x134 == -1 && GetStandardRect(&aRect) && !param_3) {
		aRect.mY -= 5;
		aRect.mX -= 5;
		aRect.mWidth = 10;
		aRect.mHeight = 10;
		return aRect.Contains((int) param_1, (int) param_2);
	}

	int iVar1 = (int) (mUnk0x114 - 5.0f);
	int iVar2 = (int) (mUnk0x118 - 5.0f);
	int iVar4 = (int) param_2;
	int iVar3 = (int) param_1;
	if (iVar3 < iVar1 || iVar1 + 10 <= iVar3 || iVar4 < iVar2 || iVar2 + 10 <= iVar4) {
		if (param_1 < mUnk0x14 - local_30) {
			return false;
		}
		if (local_30 < mUnk0x1c - param_1) {
			return false;
		}
		if (param_2 < mUnk0x18 - local_30) {
			return false;
		}
		if (local_30 + mUnk0x20 < param_2) {
			return false;
		}

		for (int i = 0; i < (int) mUnk0x108.size(); i++) {
			if (mUnk0x108.size() <= i) {
				if (!mUnk0x12e) {
					return false;
				}

				return PointInside(param_1, param_2);
			}

			float distance = mUnk0x108[i]->GetDistanceFromPoint(param_1, param_2);
			if (distance <= local_30) {
				return true;
			}
		}
	}
}

// STUB: POPCAPGAME1 0x00484ed0
void Poly::EditGetDragMode(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00486fe0
void Poly::EditDoPointDrag(float param_1, float param_2)
{
}

// FUNCTION: POPCAPGAME1 0x0052a680
void Poly::EditFinishDrag()
{
}

// STUB: POPCAPGAME1 0x00485540
void Poly::EditReflect(float param_1, float param_2, bool param_3)
{
}

// FUNCTION: POPCAPGAME1 0x00476d70
void Poly::SetPos(float param_1, float param_2)
{
	mUnk0x146 = true;
	float fVar1 = param_1 - mUnk0x114;
	float fVar2 = param_2 - mUnk0x118;
	mUnk0x114 = param_1;
	mUnk0x118 = param_2;
	mUnk0x14 += fVar1;
	mUnk0x1c += fVar1;
	mUnk0x18 += fVar2;
	mUnk0x20 += fVar2;
}

// FUNCTION: POPCAPGAME1 0x00476d30
void Poly::Translate(float param_1, float param_2)
{
	SetPos(param_1 + mUnk0x114, param_2 + mUnk0x118);
}

// FUNCTION: POPCAPGAME1 0x0047bcd0
void Poly::SetVelocity(float param_1, float param_2)
{
	for (std::vector<SmartPtr<Line>>::iterator it = mUnk0x108.begin(); it != mUnk0x108.end(); ++it) {
		(*it)->SetVelocity(param_1, param_2);
	}
}

// FUNCTION: POPCAPGAME1 0x0047bd50
void Poly::Update()
{
	PhysObj::Update();
	if (mMover != NULL) {
		if (mUnk0x11c == mMover->mUnk0x64) {
			mUnk0x120 = 0.0f;
		}
		else {
			mUnk0x120 = mMover->mUnk0x64 - mUnk0x11c;
			while (SEXY_PI < mUnk0x120) {
				mUnk0x120 -= 2 * SEXY_PI;
			}

			while (mUnk0x120 < -SEXY_PI) {
				mUnk0x120 += 2 * SEXY_PI;
			}

			mUnk0x128 = mMover->mUnk0x64;
			mUnk0x11c = mMover->mUnk0x64;
			DelayedInitRotatedFromPoints(mMover->mUnk0x64);
		}
	}

	if (!mUnk0x78.empty() && mUnk0x78 != "movetoggle" && mUnk0x50 == ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp101,952", 0x28)) {
		mUnk0x130 = !mUnk0x130;
		mUnk0xb8 = -mUnk0xb8;
		AddBubbles(SOUND_FLIP);
	}

	if (0 < mUnk0x138) {
		mUnk0x138--;
		if ((mUnk0x13c & 0x100) == 0) {
			if ((mUnk0x13c & 0x1000) == 0 && mUnk0x144 != 0) {
				mUnk0x140 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp102,973", 100);
			}
		}
		else {
			mUnk0x25 = mUnk0x138 != 0;
		}
	}

	if (0 < mUnk0x140) {
		mUnk0x140--;
	}
}

// FUNCTION: POPCAPGAME1 0x0047d8c0
void Poly::UpdateSlowMo(float param_1)
{
	if (mMover != NULL) {
		float fVar1 = mMover->mUnk0x64;
		PhysObj::UpdateSlowMo(param_1);
		float fVar2 = mMover->mUnk0x64;
		mMover->mUnk0x64 = fVar1;
		mUnk0x128 = fVar2;
		if (mUnk0x11c != fVar2) {
			InitRotatedFromPoints(fVar2);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0047a160
void Poly::DrawShadow(Graphics* g)
{
	if (mPegInfo != NULL && mUnk0xb4 != NULL && mOutlineMode != 2 && g->mIs3D) {
		g->SetColorizeImages(true);
		g->SetColor(Color(0, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp97,856", 0xff)));
		DrawImage(g, mUnk0x114 - 3.0f, mUnk0x118 + 3.0f, mUnk0x128, true, mUnk0x130);
		g->SetColorizeImages(false);
	}
}

// STUB: POPCAPGAME1 0x0047e7e0
void Poly::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x0047a230
void Poly::DrawLight(Graphics* g)
{
	PhysObj::DrawLight(g);
}

// FUNCTION: POPCAPGAME1 0x0047b9d0
void Poly::NotifyCollision(PhysObj* param_1)
{
	if (mUnk0x78 == "movetoggle" && !mUnk0x26 && mMover != NULL && 0 < mMover->mTime) {
		if (mUnk0x4c % mMover->mTime < 10) {
			if (mUnk0x130) {
				float fVar1 = mUnk0xb8;
				mUnk0x130 = false;
				mUnk0xb8 = fVar1 * -1.0f;
			}
			SetMovingPercent(0.5f, false);
			AddBubbles(SOUND_FLIP);
		}
		else {
			if (!mUnk0x130) {
				float fVar1 = mUnk0xb8;
				mUnk0x130 = true;
				mUnk0xb8 = fVar1 * -1.0f;
			}
			SetMovingPercent(0.0f, false);
			AddBubbles(SOUND_FLIP);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0052a680
void Poly::AddedToGame()
{
}

// FUNCTION: POPCAPGAME1 0x00481750
SexyVector2 Poly::GetCenter()
{
	return SexyVector2(mUnk0x114, mUnk0x118);
}

// FUNCTION: POPCAPGAME1 0x00481730
float Poly::GetXPos()
{
	return mUnk0x114;
}

// FUNCTION: POPCAPGAME1 0x00481740
float Poly::GetYPos()
{
	return mUnk0x118;
}

// FUNCTION: POPCAPGAME1 0x00476de0
void Poly::SetActiveWithGrowAnim(bool param_1)
{
	bool aBool = false;
	if (!mUnk0x25 || (mUnk0x138 != 0 && mUnk0x13c)) {
		aBool = false;
	}
	else {
		aBool = true;
	}

	SetActive(param_1);
	if (aBool != mUnk0x25) {
		if (!param_1) {
			mUnk0x13c |= 0x100;
			mUnk0x25 = true;
		}
		else {
			mUnk0x13c &= 0xfffffeff;
		}
		mUnk0x138 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp95,791", 0x14);
	}
}

// FUNCTION: POPCAPGAME1 0x00476b90
void Poly::InitDefaults()
{
	mUnk0x11c = 0.0f;
	mUnk0x120 = 0.0f;
	mUnk0x134 = 1;
	mUnk0x128 = 0.0f;
	mUnk0x138 = 0;
	mUnk0x13c = 0;
	mUnk0x124 = 0.0f;
	mUnk0x140 = 0;
	mUnk0x12f = false;
	mUnk0x130 = false;
	mUnk0x144 = true;
	mUnk0x145 = false;
	mUnk0x146 = false;
}

// FUNCTION: POPCAPGAME1 0x00476bf0
void Poly::AddBubbles(int param_1)
{
	if (!mUnk0x30) {
		Board* aBoard = GetBoard();
		if (aBoard) {
			if (-1 < param_1) {
				aBoard->mSoundMgr->AddSound(param_1, 0.0, 0.0, 0.0, 0x1e, -1.0f);
			}

			int xPos = 0.0f;
			if (!mUnk0x130) {
				xPos = mUnk0x14;
			}
			else {
				xPos = mUnk0x1c;
			}
			int yPos = mUnk0x118;

			int aNumBubbles = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp92,207", 2) + Rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp93,207", 3);
			for (int i = 0; i < aNumBubbles; i++) {
				Effect* aBubble = aBoard->mEffectMgr->AddBubble(Rand() % 21 - 10 * xPos, Rand() % 21 - 10 * yPos);
				aBubble->mUnk0xc = -Rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Poly.cpp94,213", 0x14);
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0047bb90
void Poly::ActualSetPos(float param_1, float param_2)
{
	float fVar3 = param_1 - mUnk0x114;
	mUnk0x146 = false;
	float fVar4 = param_2 - mUnk0x118;
	mUnk0x114 = param_1;
	mUnk0x118 = param_2;
	mUnk0x14 = mUnk0x14 + fVar3;
	mUnk0x1c = mUnk0x1c + fVar3;
	mUnk0x18 = mUnk0x18 + fVar4;
	mUnk0x20 = mUnk0x20 + fVar4;

	int i = 0;
	for (std::vector<SmartPtr<Line>>::iterator it = mUnk0x108.begin(); it != mUnk0x108.end(); ++it, i++) {
		Line* aLine = *it;
		SexyVector2* aLineStart = mUnk0xf8[i];
		aLine->SetPos(mUnk0x114 + aLineStart->x, mUnk0x118 + aLineStart->y);
	}
}

// STUB: POPCAPGAME1 0x0047bab0
void Poly::CalcBoundingBox()
{
}

// STUB: POPCAPGAME1 0x0047d3a0
void Poly::CheckConvex()
{
}

// FUNCTION: POPCAPGAME1 0x0047d5b0
void Poly::InitRotatedFromPoints(float param_1)
{
	if (1 < mUnk0xe8.size()) {
		mUnk0x145 = false;
		mUnk0x146 = false;
		float fVar1 = cos(param_1);
		float fVar2 = sin(param_1);

		SexyVector2* aPoint0 = mUnk0xe8[0];
		float fVar3 = fVar2 * aPoint0->y - fVar1 * aPoint0->x;
		float fVar4 = fVar1 * aPoint0->y + fVar2 * aPoint0->x;

		int i = 0;
		for (std::vector<SexyVector2*>::iterator it = mUnk0xe8.begin(); it != mUnk0xe8.end(); ++it, i++) {
			SexyVector2* aPoint = *it;
			float fVar5 = aPoint->x;
			float fVar6 = aPoint->y;
			float fVar7 = fVar1 * fVar5 + fVar2 * fVar6;
			float fVar8 = fVar6 * fVar1 - fVar2 * fVar5;
			Line* aLine = mUnk0x108[i];
			aLine->Init(
				fVar3 + mUnk0x114,
				mUnk0x118 + fVar4,
				fVar7 + mUnk0x114,
				mUnk0x118 + fVar8
			);

			SexyVector2* aLineStart = mUnk0xf8[i];
			aLineStart->x = aLine->mUnk0xec - mUnk0x114;
			aLineStart->y = aLine->mUnk0xf4 - mUnk0x118;
		}

		CalcBoundingBox();
	}
}

// FUNCTION: POPCAPGAME1 0x0047a010
void Poly::DelayedInitRotatedFromPoints(float param_1)
{
	mUnk0x18 = 1000000000000;
	mUnk0x14 = 1000000000000;
	mUnk0x20 = -1000000000000;
	mUnk0x1c = -1000000000000;

	float fVar1 = cos(param_1);
	float fVar2 = sin(param_1);

	for (int i = 0; i < mUnk0xe8.size(); i++) {
		float x = mUnk0xe8[i]->x;
		float y = mUnk0xe8[i]->y;
		float fVar3 = fVar2 * y + fVar1 * x + mUnk0x114;
		float fVar4 = (y * fVar1 - fVar2 * x) + mUnk0x118;

		if (fVar3 < mUnk0x14) {
			mUnk0x14 = fVar3;
		}
		if (mUnk0x1c < fVar3 && fVar3 != mUnk0x1c) {
			mUnk0x1c = fVar3;
		}
		if (fVar4 < mUnk0x18) {
			mUnk0x18 = fVar4;
		}
		if (mUnk0x20 <= fVar4 && fVar4 != mUnk0x20) {
			mUnk0x20 = fVar4;
		}
	}

	mUnk0x145 = true;
}

// FUNCTION: POPCAPGAME1 0x0047d880
void Poly::EnsureLines()
{
	if (mUnk0x145) {
		InitRotatedFromPoints(mUnk0x11c);
	}
	else if (mUnk0x146) {
		ActualSetPos(mUnk0x114, mUnk0x118);
	}
}

// FUNCTION: POPCAPGAME1 0x0047d930
bool Poly::PointInside(float param_1, float param_2)
{
	EnsureLines();
	uint uVar1 = 0;
	for (int i = 0; i < mUnk0x108.size(); i++) {
		Line* aLine = mUnk0x108[i];
		float fVar1 = aLine->mUnk0xf4;
		float fVar2 = aLine->mUnk0xf8;
		if ((fVar1 != fVar2 && fVar1 <= param_2 && param_2 < fVar2) ||
			(fVar2 <= param_2 && param_2 < fVar1) && (fVar1 == fVar2) || (fVar1 < param_1) && (param_1 < ((param_2 - fVar1) * aLine->mUnk0xf0 - aLine->mUnk0xec)) / (fVar2 - fVar1) + aLine->mUnk0xec) {
			uVar1++;
		}
	}
	return uVar1 & 1;
}

// STUB: POPCAPGAME1 0x0047e4b0
bool Poly::GetStandardRectF(FRect* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047e390
bool Poly::GetStandardRect(Rect* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x00w
bool Poly::EditIntersects(Rect* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047e5b0
void Poly::DrawPoly(Graphics* g, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x0047dfe0
bool Poly::CheckCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	float* param_4,
	SexyVector2* param_5,
	SexyVector2* param_6,
	SexyVector2* param_7,
	SexyVector2* param_8
)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047d810
void Poly::SetRotation(float param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00483330
void Poly::AddPoint(float param_1, float param_2)
{
	mUnk0xe8.push_back(new SexyVector2(param_1, param_2));
}

// STUB: POPCAPGAME1 0x00484730
void Poly::InitFromPoints()
{
}

// STUB: POPCAPGAME1 0x00484e80
void Poly::ReverseLines()
{
}

// STUB: POPCAPGAME1 0x00486e20
void Poly::SetNormalDir(int param_1)
{
}

// STUB: POPCAPGAME1 0x00484dc0
void Poly::Close()
{
}

// FUNCTION: POPCAPGAME1 0x00484b30
void Poly::MoveCenterTo(float param_1, float param_2)
{
	float fVar1 = param_1 - mUnk0x114;
	float fVar2 = param_2 - mUnk0x118;
	for (int i = 0; i < (int)mUnk0xe8.size(); i++) {
		SexyVector2* aPoint = mUnk0xe8[i];
		aPoint->x -= fVar1;
		aPoint->y -= fVar2;
	}

	mUnk0x114 += fVar1;
	mUnk0x118 += fVar2;
	mUnk0xb8 -= fVar1;
	mUnk0xbc -= fVar2;

	if (mMover != NULL) {
		mMover->Translate(fVar1, fVar2);
		InitFromPoints();
	} else {
		InitFromPoints();
	}
}

// FUNCTION: POPCAPGAME1 0x00484a80
void Poly::SetScale(float param_1)
{
	if (param_1 > 0) {
		float aScale = param_1 / mUnk0x124;
		for (int i = 0; i < (int)mUnk0xe8.size(); i++) {
			SexyVector2* aPoint = mUnk0xe8[i];
			aPoint->x *= aScale;
			aPoint->y *= aScale;
		}

		mUnk0x124 = param_1;
		InitFromPoints();
	}
}

// FUNCTION: POPCAPGAME1 0x00486d00
void Poly::InitFromRect(float param_1, float param_2, float param_3, float param_4)
{
	mUnk0xe8.clear();
	float fVar2 = (param_4 - 1.0) * 0.5;
	float fVar3 = (param_3 - 1.0) * 0.5;
	float fVar4 = -fVar3;
	float fVar5 = -fVar2;
	AddPoint(fVar5, fVar4);
	AddPoint(fVar5, fVar3);
	AddPoint(fVar2, fVar3);
	AddPoint(fVar2, fVar4);
	AddPoint(fVar5, fVar4);
	mUnk0x12c = true;
	mUnk0x114 = fVar2 + param_1;
	mUnk0x118 = fVar3 + param_2;
	InitFromPoints();
}

// STUB: POPCAPGAME1 0x00487d00
void Poly::SyncCommon(DataSync* theSync, bool param_2)
{
}
