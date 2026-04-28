#include "PhysObj.h"

#include "AIBall.h"
#include "Ball.h"
#include "Brick.h"
#include "ConstEnums.h"
#include "DataSync.h"
#include "Hole.h"
#include "ImageMgr.h"
#include "Line.h"
#include "Mover.h"
#include "PegInfo.h"
#include "Poly.h"
#include "ThunderCommon.h"

#include <ImageLib/ImageLib.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/SexyVector.h>

using namespace Sexy;

// GLOBAL: POPCAPGAME1 0x00650a68
int Sexy::PhysObj::gCurSortId = 0;
int Sexy::PhysObj::mSyncType = 0;
bool Sexy::PhysObj::mFastLoad = true;

// FUNCTION: POPCAPGAME1 0x00480660
PhysObj::PhysObj()
{
	mUnk0x10 = 0;
	mUnk0x24 = true;
	mUnk0x25 = true;
	mUnk0x26 = true;
	mUnk0x27 = false;
	mUnk0x2a = false;
	mUnk0x2b = false;
	mUnk0xb4 = 0;
	mUnk0xc4 = false;
	mUnk0xd4 = 0;
	mUnk0xd8 = 0;
	mUnk0xe0 = false;
	mUnk0xdc = 0;
	mUnk0xe1 = false;

	gCurSortId++;
	mCurSortId = gCurSortId;

	mUnk0xb0 = 0;
	mUnk0x2f = false;
	mUnk0x30 = false;
	InitDefaults();
}

// SYNTHETIC: POPCAPGAME1 0x0047dfb0
// Sexy::PhysObj::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0047d230
PhysObj::~PhysObj()
{
	DeleteImage();
}

// FUNCTION: POPCAPGAME1 0x00404ca0
PhysObj* PhysObj::ClassFactory(int param_1)
{
	switch (param_1) {
	case 1:
	default:
		return new PhysObj();
	case 2:
		return new Line();
	case 3:
		return new Poly();
	case 4:
		return new Ball(false);
	case 5:
		return new Ball(true);
	case 6:
		return new Brick();
	case 7:
		return new AIBall();
	case 8:
		return new Hole();
	}
}

// FUNCTION: POPCAPGAME1 0x004fa750
int PhysObj::GetClass()
{
	return 1;
}

// FUNCTION: POPCAPGAME1 0x0047d350
float PhysObj::GetXPos()
{
	return (mUnk0x1c + mUnk0x14) * 0.5f;
}

// FUNCTION: POPCAPGAME1 0x0047d370
float PhysObj::GetYPos()
{
	return (mUnk0x20 + mUnk0x18) * 0.5f;
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::SetPos(float theX, float theY)
{
}

// FUNCTION: POPCAPGAME1 0x00476b00
void PhysObj::Translate(float theDx, float theDy)
{
	mUnk0x14 += theDx;
	mUnk0x18 += theDx;
	mUnk0x1c += theDy;
	mUnk0x20 += theDy;
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::SetVelocity(float theVx, float theVy)
{
}

void PhysObj::AdjustRect(float theX, float theY, float theWidth, float theHeight)
{
}

// FUNCTION: POPCAPGAME1 0x00479700
float PhysObj::GetOrigX()
{
	if (mMover != NULL) {
		return mMover->mUnk0x5c;
	}

	return GetXPos();
}

// FUNCTION: POPCAPGAME1 0x00479720
float PhysObj::GetOrigY()
{
	if (mMover != NULL) {
		return mMover->mUnk0x60;
	}

	return GetYPos();
}

// FUNCTION: POPCAPGAME1 0x004769f0
void PhysObj::SetActive(bool param_1)
{
	mUnk0x24 = param_1;
	mUnk0x25 = param_1;
}

// FUNCTION: POPCAPGAME1 0x00454790
void PhysObj::SetActiveWithGrowAnim(bool param_1)
{
	SetActive(param_1);
}

// FUNCTION: POPCAPGAME1 0x0047af50
void PhysObj::SetIsPeg(bool isPeg)
{
	if (!isPeg) {
		if (mPegInfo != NULL) {
			mPegInfo->CreateRef();
		}
		PegChangedHook(true);
	}
	else if (mPegInfo != NULL) {
		mPegInfo = new PegInfo();
		PegChangedHook(false);
	}
}

// FUNCTION: POPCAPGAME1 0x00479870
void PhysObj::SetPegType(PegType theType)
{
	if (mPegInfo != NULL) {
		mPegInfo->mPegType = theType;
		PegChangedHook(true);
	}
}

// FUNCTION: POPCAPGAME1 0x00479980
void PhysObj::SetMoveUpdateCnt(int param_1)
{
	mUnk0x4c = param_1;
	SyncPosWithMover();
}

// FUNCTION: POPCAPGAME1 0x004799a0
void PhysObj::SetMovingPercent(float param_1, bool param_2)
{
	if (mMover != NULL) {
		bool bVar2 = param_1 < 0.0f;
		if (bVar2) {
			param_1 * -1.0f;
		}
		float dVar3 = mMover->GetTimeTillPhase(mUnk0x4c, param_1);
		if ((int) dVar3 < 1) {
			if (bVar2) {
				dVar3 += mMover->mPause2 + mMover->mPause1 + mMover->mTime;
			}
			if (dVar3 < 1) {
				return;
			}
		}

		if (param_2) {
			SetMoveUpdateCnt(dVar3);
		}
		mUnk0x26 = true;
		mUnk0x50 = dVar3;
	}
}

// FUNCTION: POPCAPGAME1 0x00479940
void PhysObj::SyncPosWithMover()
{
	if (mMover != NULL) {
		mMover->CalcPos(mUnk0x4c, 0.0f);
		SetPos(mMover->mOffset, mMover->mRadius);
	}
}

// FUNCTION: POPCAPGAME1 0x00479890
uint PhysObj::GetTypeFlags()
{
	uint uVar3 = 0;
	if (mPegInfo == NULL || (uVar3 = 1, mPegInfo->mPegType == 0)) {
		uVar3 = 0x1000;
	}

	if (mUnk0x10 == 2 || mUnk0x10 == 3) {
		uVar3 |= 2;
	}
	else {
		uVar3 |= 0x2000;
	}

	if (GetClass() == 6) {
		uVar3 |= 4;
	}
	else {
		uVar3 |= 0x4000;
	}

	if (!mUnk0x24) {
		uVar3 |= 8;
	}
	else {
		uVar3 |= 0x8000;
	}

	if (mUnk0x2a) {
		uVar3 |= 0x10;
	}
	else {
		uVar3 |= 0x10000;
	}

	if (!mUnk0xe1) {
		uVar3 |= 0x20000;
	}

	if (mPegInfo != NULL && !mPegInfo->mUnk0x15) {
		uVar3 |= 0x20;
	}

	if (mPegInfo != NULL && mPegInfo->mUnk0x16) {
		uVar3 |= 0x40;
	}

	if (mUnk0x54 != 0) {
		uVar3 |= 0x80;
	}

	return uVar3;
}

// FUNCTION: POPCAPGAME1 0x00476b30
bool PhysObj::HasTypeFlags(int param_1)
{
	return (param_1 & GetTypeFlags()) != 0;
}

// FUNCTION: POPCAPGAME1 0x0047d390
bool PhysObj::IsCollidableWith(PhysObj* param_1)
{
	return param_1->mUnk0x24;
}

// FUNCTION: POPCAPGAME1 0x0047f740
void PhysObj::InitDefaults()
{
	mUnk0x5c = "";
	mUnk0x78 = "";
	mUnk0x34 = 0;
	mUnk0x4c = 0;
	mUnk0x38 = 0;
	mUnk0x40 = 0;
	mUnk0x3c = 0;
	mUnk0xc8 = 0;
	mUnk0x50 = 0.0f;
	mUnk0x54 = 0;
	mUnk0xcc = 0;
	mUnk0x44 = 0xffffff;
	if (mPegInfo != NULL) {
		mPegInfo->Release();
		mPegInfo = NULL;
	}

	if (mMover != NULL) {
		mMover->Release();
		mMover = NULL;
	}

	DeleteImage();

	mUnk0xb4 = 0;
	mUnk0x94 = "";
	mUnk0xb8 = 0;
	mUnk0xbc = 0;
	mUnk0xc4 = false;
	mUnk0x28 = false;
	mUnk0xc0 = 0;
	mUnk0x29 = false;
	mUnk0x2c = false;
	mUnk0x2d = false;
	mUnk0x2e = false;
}

// FUNCTION: POPCAPGAME1 0x0047f830
bool PhysObj::LoadImage()
{
	if (!mUnk0x94.empty()) {
		DeleteImage();
		uint uVar1 = ImageLib::gAlphaComposeColor;

		// STRING: POPCAPGAME1 0x005f1c0c
		if (StrFindNoCase(mUnk0x94.c_str(), "shadow")) {
			ImageLib::gAlphaComposeColor = 0;
		}

		ImageMgr* theImageMgr = GetImageMgr();

		if (mUnk0x94.find('/') != -1) {
			mUnk0xb4 = (Image*) theImageMgr->GetImage(&mUnk0x94, &mUnk0x2f, true);
		}
		else {
			// STRING: POPCAPGAME1 0x005f1bfc
			std::string path = "images/levels/" + mUnk0x94;
			mUnk0xb4 = (Image*) theImageMgr->GetImage(&path, &mUnk0x2f, true);
		}

		ImageLib::gAlphaComposeColor = uVar1;
		return mUnk0xb4 != NULL;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x0047f960
void PhysObj::EditReloadImage()
{
	LoadImage();
}

// FUNCTION: POPCAPGAME1 0x004769c0
void PhysObj::DeleteImage()
{
	if (mUnk0xc4 != 0 && mUnk0xb4 != NULL) {
		mUnk0xb4->~Image();
	}
	mUnk0xb4 = NULL;
}

// FUNCTION: POPCAPGAME1 0x0052a680
void PhysObj::AddedToGame()
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::DrawShadow(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00479b70
void PhysObj::DrawLight(Graphics* g)
{
	if (mPegInfo != NULL) {
		mPegInfo->DrawLight(this, g);
	}
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::EditDrawPoints(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00479ff0
void PhysObj::EditDrawMovement(Graphics* g)
{
	if (mMover != NULL) {
		mMover->DrawMovement(g);
	}
}

// FUNCTION: POPCAPGAME1 0x00476b50
void PhysObj::EditDrawOutline(Graphics* g)
{
	g->DrawRect((int) mUnk0x14, (int) mUnk0x18, (int) (mUnk0x1c - mUnk0x14), (int) (mUnk0x20 - mUnk0x18));
}

// FUNCTION: POPCAPGAME1 0x004797c0
void PhysObj::EditTranslate(float param_1, float param_2)
{
	if (mMover != NULL) {
		mMover->Translate(param_1, param_2);
	}

	Translate(param_1, param_2);
}

// FUNCTION: POPCAPGAME1 0x00479800
void PhysObj::EditSetPos(float param_1, float param_2)
{
	if (mMover != NULL) {
		float fVar2 = param_1 - mMover->mUnk0x5c;
		float fVar1 = param_2 - mMover->mUnk0x60;
		mMover->Translate(fVar2, fVar1);
		Translate(fVar2, fVar1);
	}
	else {
		SetPos(param_1, param_2);
	}
}

// FUNCTION: POPCAPGAME1 0x00479a30
void PhysObj::Update()
{
	if ((mUnk0xc8 != 0) && (mUnk0xc8-- == 0)) {
		SetActive(false);
	}

	if (mPegInfo != NULL) {
		mPegInfo->Update(this);
	}

	if (mMover != NULL) {
		float fVar1 = mMover->mUnk0x54;
		float fVar2 = mMover->mUnk0x58;

		if (mUnk0x26) {
			if (mMover->mPhysObj != NULL) {
				mMover->CalcPos(mUnk0x4c, 0.0f);
			}
		}
		else {
			mUnk0x4c++;
			mMover->CalcPos(mUnk0x4c, 0.0f);
		}

		SetPos(mMover->mUnk0x54, mMover->mUnk0x58);
		SetVelocity(mMover->mUnk0x54 - fVar1, mMover->mUnk0x58 - fVar2);
	}

	if ((mUnk0x50 != 0.0f) && (mUnk0x50-- == 0.0f)) {
		mUnk0x26 = false;
	}
}

// FUNCTION: POPCAPGAME1 0x00479b00
void PhysObj::UpdateSlowMo(float param_1)
{
	if ((mMover != NULL) && (mUnk0x26)) {
		float fVar1 = mMover->mUnk0x54;
		float fVar2 = mMover->mUnk0x58;
		mMover->CalcPos(mUnk0x4c - 1, param_1);
		SetPos(mMover->mUnk0x54, mMover->mUnk0x58);
		mMover->mUnk0x54 = fVar1;
		mMover->mUnk0x58 = fVar2;
	}
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::NotifyCollision(PhysObj* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::PegChangedHook(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0052a680
void PhysObj::EditFinishDrag()
{
}

// FUNCTION: POPCAPGAME1 0x00476a80
void PhysObj::EditGetDragMode(float param_1, float param_2)
{
	mUnk0xd8 = 0;
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::EditDoPointDrag(float param_1, float param_2)
{
}

// FUNCTION: POPCAPGAME1 0x00476a30
bool PhysObj::EditContains(float param_1, float param_2, bool param_3)
{
	if ((((param_1 < mUnk0x14) || (mUnk0x1c < param_1)) || (param_2 < mUnk0x18)) || (mUnk0x20 < param_2)) {
		return false;
	}
	else {
		return true;
	}
}

// FUNCTION: POPCAPGAME1 0x00479740
bool PhysObj::EditIntersects(Rect param_1)
{
	int var1 = (int) mUnk0x14;
	int var2 = (int) mUnk0x18;
	int var3 = (int) (mUnk0x1c - mUnk0x14);
	int var4 = (int) (mUnk0x20 - mUnk0x18);

	if (param_1.mX > var1 + var3 &&
		param_1.mY > var2 + var4 &&
		var1 < param_1.mWidth + param_1.mX &&
		var2 < param_1.mHeight + param_1.mY) {
		return true;
	}
	return false;
}

// FUNCTION: POPCAPGAME1 0x00476a90
void PhysObj::EditReflect(float param_1, float param_2, bool param_3)
{
	float xPos = GetXPos();
	float yPos = GetYPos();
	if (param_3) {
		xPos = 0;
		yPos = (yPos - param_2) + (yPos - param_2);
	} else {
		yPos = 0;
		xPos = (xPos - param_1) + (xPos - param_1);
	}

	EditTranslate(xPos, yPos);
}

// FUNCTION: POPCAPGAME1 0x00479b90
void PhysObj::DrawImage(
	Graphics* g,
	Image* param_2,
	float param_3,
	float param_4,
	float param_5,
	bool param_6,
	bool param_7
)
{
	Rect local_1c;
	local_1c.mWidth = param_2->mWidth;
	local_1c.mHeight = param_2->mHeight;
	local_1c.mX = 0;
	local_1c.mY = 0;

	float fVar1 = local_1c.mWidth * 0.5f;
	float fVar2 = local_1c.mHeight * 0.5f;

	float fVar3 = mUnk0xb8 + param_3 - fVar1;
	float fVar4 = mUnk0xbc + param_4 - fVar2;

	if (param_7) {
		if ((param_6) && g->mIs3D) {
			Transform aTransform;
			aTransform.Scale(-1.0f, 1.0f);
			g->DrawImageTransformF(param_2, aTransform, local_1c, fVar3 + fVar1, fVar4 + fVar2);
		}
		else {
			g->DrawImageMirror(param_2, fVar3, fVar4, true);
		}
	}
	else {
		float fVar5 = mUnk0xc0 + param_5;
		if (fVar5 != 0.0f) {
			g->DrawImageRotatedF(param_2, fVar3, fVar4, fVar5, (fVar1 - mUnk0xb8), (fVar2 - mUnk0xbc), &local_1c);
		}
		else if (param_6) {
			g->DrawImageF(param_2, fVar3, fVar4, local_1c);
		}
		else {
			g->DrawImage(param_2, fVar3, fVar4, local_1c);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00479d50
void PhysObj::DrawImage(
	Graphics* g,
	float param_2,
	float param_3,
	float param_4,
	bool param_5,
	int param_6,
	float param_7
)
{
	Rect local_2c;

	local_2c.mHeight = mUnk0xb4->mHeight;
	float fVar1 = mUnk0xb4->mWidth * 0.5f;
	float fVar2 = mUnk0xb4->mHeight * 0.5f;
	float fVar3 = (param_2 + mUnk0xb8) - fVar1;
	float fVar4 = (param_3 + mUnk0xbc) - fVar2;

	float fVar5;
	if (0.0 <= param_7) {
		fVar5 = 1.0f;
		if (param_7 <= 1.0f) {
			fVar5 = param_7;
		}
	}
	else {
		fVar3 = 0.0f;
	}

	if ((param_6 & 0x100U) == 0) {
		fVar3 = 1.0f - fVar3;
	}

	local_2c.mWidth = fVar5 * mUnk0xb4->mWidth;
	local_2c.mX = 0;
	local_2c.mY = 0;

	switch (param_6 & 0xff) {
	case 2:
		local_2c.mX = mUnk0xb4->mWidth - local_2c.mWidth;
		fVar3 += local_2c.mX;
		break;
	case 3:
		local_2c.mX = mUnk0xb4->mWidth - local_2c.mWidth;
		break;
	case 4:
		fVar3 += mUnk0xb4->mWidth - local_2c.mWidth;
		break;
	case 5:
		local_2c.mX = (mUnk0xb4->mWidth - local_2c.mWidth) / 2;
		fVar3 += local_2c.mX;
		break;
	case 6:
		local_2c.mHeight = mUnk0xb4->mHeight * fVar5;
		local_2c.mWidth = mUnk0xb4->mWidth;
		local_2c.mY = (mUnk0xb4->mHeight - local_2c.mHeight) / 2;
		fVar4 += local_2c.mY;
		break;
	case 7:
		local_2c.mHeight = mUnk0xb4->mHeight * fVar5;
		local_2c.mWidth = mUnk0xb4->mWidth;
		local_2c.mY = mUnk0xb4->mHeight - local_2c.mHeight;
		break;
	case 8:
		local_2c.mWidth = mUnk0xb4->mWidth;
		break;
	}

	float fVar6 = mUnk0xc0 + param_7;
	if (fVar6 == 0.0f) {
		if (param_5) {
			g->DrawImageF(mUnk0xb4, fVar3, fVar4, local_2c);
		}
		else {
			g->DrawImage(mUnk0xb4, fVar3, fVar4, local_2c);
		}
	}
	else {
		g->DrawImageRotatedF(mUnk0xb4, fVar3, fVar4, fVar6, fVar1 - mUnk0xb8, fVar2 - mUnk0xbc, &local_2c);
	}
}

// FUNCTION: POPCAPGAME1 0x00479fb0
void PhysObj::DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6)
{
	DrawImage(g, mUnk0xb4, param_2, param_3, param_4, param_5, param_6);
}

// FUNCTION: POPCAPGAME1 0x0047f970
bool PhysObj::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	if (param_1 == "physobj_xpos" && param_1 == "physobj_ypos") {
		float fVar1 = GetOrigX();
		float fVar2 = GetOrigY();

		if (param_2) {
			if (param_1 == "physobj_xpos") {
				fVar1 = (float) GetEditValNum();
			}
			else {
				fVar2 = (float) GetEditValNum();
			}

			EditSetPos(fVar1, fVar2);
		}
		else {
			if (param_1 == "physobj_xpos") {
				SetEditValNum((double) fVar1);
			}
			else {
				SetEditValNum((double) fVar2);
			}
		}
	}

	else if (param_1 == "physobj_align") {
		float fVar1 = GetOrigX();
		float fVar2 = GetOrigY();
		float fVar3 = fVar1 - mUnk0x14;
		float fVar4 = 640.0f - (mUnk0x1c - fVar1);
		float fVar5 = fVar2 - mUnk0x18;
		float fVar6 = 480.0f - (mUnk0x20 - fVar2);

		if (param_2) {
			uint uVar1 = (int) mEditVal->ToNum() & 3;
			if (uVar1 == 2) {
				fVar4 = 320.0f;
			}
			else if (uVar1 != 3 && (fVar4 = fVar1, uVar1 == 1)) {
				fVar4 = fVar3;
			}

			if (uVar1 == 3) {
				fVar6 = 240.0f;
			}
			else if (uVar1 != 3 && (fVar6 = fVar2, uVar1 == 1)) {
				fVar6 = fVar5;
			}

			EditSetPos(fVar4, fVar6);
			return true;
		}
		else {
			SetEditValNum(0.0);
			return true;
		}
	}

	else if (param_1 == "physobj_collideable") {
		return EditValSyncBool(mUnk0x24);
	}

	else if (param_1 == "physobj_visible") {
		return EditValSyncBool(mUnk0x25);
	}

	else if (param_1 == "physobj_moving") {
		return EditValSyncBool(mUnk0x26);
	}

	else if (param_1 == "physobj_background") {
		return EditValSyncBool(mUnk0x27);
	}

	else if (param_1 == "physobj_ballstopreset") {
		return EditValSyncBool(mUnk0x2b);
	}

	else if (param_1 == "physobj_bouncy") {
		return EditValSyncNum(mUnk0x34);
	}

	else if (param_1 == "physobj_maxbouncevel") {
		return EditValSyncNum(mUnk0x3c);
	}

	else if (param_1 == "physobj_rolly") {
		return EditValSyncNum(mUnk0x38);
	}

	else if (param_1 == "physobj_solidcolor") {
		return EditValSyncNum(mUnk0x40);
	}

	else if (param_1 == "physobj_outlinecolor") {
		return EditValSyncNum(mUnk0x44);
	}

	else if (param_1 == "physobj_id") {
		return EditValSyncString(mUnk0x5c);
	}

	else if (param_1 == "physobj_logic") {
		return EditValSyncString(mUnk0x78);
	}

	else if (param_1 == "physobj_sound") {
		return EditValSyncNum(mUnk0x54);
	}

	else if (param_1 == "physobj_subid") {
		return EditValSyncNum(mUnk0xb0);
	}

	else if (param_1 == "physobj_flipperflags") {
		return EditValSyncNum(mUnk0xcc);
	}

	else if (param_1 == "physobj_image") {
		return EditValSyncString(mUnk0x94);
	}

	else if (param_1 == "physobj_imagedx") {
		return EditValSyncNum(mUnk0xb8);
	}

	else if (param_1 == "physobj_imagedy") {
		return EditValSyncNum(mUnk0xbc);
	}

	else if (param_1 == "physobj_foreground") {
		return EditValSyncBool(mUnk0x28);
	}

	else if (param_1 == "physobj_foreground2") {
		return EditValSyncBool(mUnk0x29);
	}

	else if (param_1 == "physobj_drawsort") {
		return EditValSyncBool(mUnk0x2c);
	}

	else if (param_1 == "physobj_drawfloat") {
		return EditValSyncBool(mUnk0x2d);
	}

	else if (param_1 == "physobj_baseobj") {
		return EditValSyncBool(mUnk0x2a);
	}

	else if (param_1 == "physobj_imagerot") {
		if (param_2) {
			mUnk0xc0 = (float) GetEditValNum() * SEXY_PI / 180.0f;
			return true;
		}
		else {
			SetEditValNum((double) (mUnk0xc0 * 180.0f / SEXY_PI));
			return true;
		}
	}

	else {
		if (EditKeyPrefix(param_1, "peg_")) {
			if (param_2 && mPegInfo == NULL) {
				mPegInfo = new PegInfo();
			}

			PegType oldPegType;
			if (mPegInfo != NULL) {
				oldPegType = NONE;
			}
			else {
				oldPegType = mPegInfo->mPegType;
			}

			bool delegate = EditGetSetValDelegate(mPegInfo, param_1);
			if (delegate && param_2 && mPegInfo != NULL && mPegInfo->mPegType == 0 && mUnk0xd == false) {
				SetIsPeg(true);
			}

			PegType newPegType;
			if (mPegInfo != NULL) {
				newPegType = NONE;
			}
			else {
				newPegType = mPegInfo->mPegType;
			}

			if (oldPegType != newPegType) {
				PegChangedHook(true);
			}

			return delegate;
		}

		if (EditKeyPrefix(param_1, "mover_")) {
			if (param_2 && mMover == NULL) {
				float fVar1 = GetXPos();
				float fVar2 = GetYPos();

				mMover = new Mover();
				mMover->SetPos(fVar1, fVar2);
			}

			bool delegate = EditGetSetValDelegate(mMover, param_1);
			if (delegate && param_2 && mMover != NULL && mMover->mType == 0 && mMover->mPhysObj == NULL && mUnk0xd == false && mMover->GetRefCount() == 0) {
				mMover->Release();
				mMover = NULL;
			}

			return delegate;
		}

		return false;
	}
}

// TEMPLATE: POPCAPGAME1 0x00476f70
// Sexy::ConstSmartPtr<Sexy::PegInfo>::operator=

// TEMPLATE: POPCAPGAME1 0x00408e30
// Sexy::DataSync_SyncSmartPointer<Sexy::Mover>

// TEMPLATE: POPCAPGAME1 0x00476f70
// Sexy::ConstSmartPtr<Sexy::Mover>::operator=

// TEMPLATE: POPCAPGAME1 0x00406860
// Sexy::DataSync_SyncRefCount<Sexy::Mover>

// FUNCTION: POPCAPGAME1 0x00480750
void PhysObj::SyncState(DataSync* theSync)
{
	DataReader* theReader = theSync->mReader;
	if (theReader != NULL) {
		InitDefaults();
	}

	bool bVar1 = mUnk0x38 != 0;
	bool bVar2 = (mUnk0x34 != 0.0f);
	bool bVar3 = (mPegInfo != NULL);
	bool bVar4 = (mUnk0xb8 != 0.0f);
	bool bVar5 = (mMover != NULL);
	bool bVar6 = (mUnk0x4c != 0);
	bool bVar7 = (mUnk0x40 != 0);
	bool bVar8 = (mUnk0x44 != 0x00ffffff);
	bool bVar9 = !mUnk0x94.empty();
	bool bVar10 = (mUnk0xbc != 0.0f);
	bool bVar11 = (mUnk0xc0 != 0.0f);
	bool bVar12 = (mUnk0xc8 != 0);
	bool bVar13 = (mUnk0x3c != 0.0f);
	bool bVar14 = !mUnk0x5c.empty();
	bool bVar15 = (mUnk0x50 != 0);
	bool bVar16 = (mUnk0x54 != 0);
	bool bVar17 = !mUnk0x78.empty();
	bool bVar18 = (mUnk0xb0 != 0);
	bool bVar19 = (mUnk0xcc != 0);

	theSync->SyncBoolBit(bVar1);
	theSync->SyncBoolBit(bVar2);
	theSync->SyncBoolBit(bVar3);
	theSync->SyncBoolBit(bVar5);
	theSync->SyncBoolBit(bVar6);
	theSync->SyncBoolBit(mUnk0x24);
	theSync->SyncBoolBit(mUnk0x25);
	theSync->SyncBoolBit(mUnk0x26);
	theSync->EndBit();

	theSync->SyncBoolBit(bVar7);
	theSync->SyncBoolBit(bVar8);
	theSync->SyncBoolBit(bVar9);
	theSync->SyncBoolBit(bVar4);
	theSync->SyncBoolBit(bVar10);
	theSync->SyncBoolBit(bVar11);
	theSync->SyncBoolBit(mUnk0x27);
	theSync->SyncBoolBit(mUnk0x2a);
	theSync->EndBit();

	theSync->SyncBoolBit(bVar12);
	theSync->SyncBoolBit(bVar14);
	theSync->SyncBoolBit(bVar15);
	theSync->SyncBoolBit(bVar16);
	theSync->SyncBoolBit(mUnk0x2b);
	theSync->SyncBoolBit(bVar17);
	theSync->SyncBoolBit(mUnk0x28);
	theSync->SyncBoolBit(bVar13);
	theSync->EndBit();

	if (theSync->mVersion >= 0xF) {
		theSync->SyncBoolBit(mUnk0x2c);
		theSync->SyncBoolBit(mUnk0x29);
		theSync->SyncBoolBit(bVar18);
		theSync->SyncBoolBit(bVar19);
		theSync->SyncBoolBit(mUnk0x2d);
		theSync->SyncBoolBit(mUnk0x30);
		theSync->EndBit();
	}

	if (bVar1) {
		theSync->SyncFloat(mUnk0x38);
	}

	if (bVar2) {
		theSync->SyncFloat(mUnk0x34);
	}

	if (bVar6) {
		theSync->SyncLong(mUnk0x4c);
	}

	if (bVar7) {
		theSync->SyncLong(mUnk0x40);
	}

	if (bVar8) {
		theSync->SyncLong(mUnk0x44);
	}

	if (bVar9) {
		theSync->SyncString(mUnk0x94);
	}

	if (bVar4) {
		theSync->SyncFloat(mUnk0xb8);
	}

	if (bVar10) {
		theSync->SyncFloat(mUnk0xbc);
	}

	if (bVar11) {
		theSync->SyncFloat(mUnk0xc0);
	}

	if (bVar12) {
		theSync->SyncLong(mUnk0xc8);
	}

	if (bVar14) {
		theSync->SyncString(mUnk0x5c);
	}

	if (bVar15) {
		theSync->SyncLong(mUnk0x50);
	}

	if (bVar16) {
		theSync->SyncByte(mUnk0x54);
	}

	if (bVar17) {
		theSync->SyncString(mUnk0x78);
	}

	if (bVar13) {
		theSync->SyncFloat(mUnk0x3c);
	}

	if (bVar18) {
		theSync->SyncLong(mUnk0xb0);
	}

	if (bVar19) {
		theSync->SyncByte(mUnk0xcc);
	}

	if (bVar3) {
		if (theReader != NULL) {
			mPegInfo = new PegInfo();
		}
		mPegInfo->SyncState(theSync);
	}

	if (bVar5) {
		DataSync_SyncSmartPointer<Mover>(*theSync, mMover);
	}

	if (mSyncType == 2) {
		bool bVar20 = mUnk0xdc != 0;
		theSync->SyncBoolBit(mUnk0xe0);
		theSync->SyncBoolBit(bVar20);
		theSync->EndBit();

		if (bVar20) {
			theSync->SyncLong(mUnk0xdc);
		}
	}

	if (theReader != NULL) {
		mUnk0x2e = mUnk0x2d;
		if (mMover != NULL) {
			float iVar1 = mMover->mType;
			if ((int) fabs((float) mMover->mType) < 8 || (int) iVar1 == 8 || (int) iVar1 == 9 || iVar1 == 13) {
				mUnk0x2e = true;
			}
		}

		if (mFastLoad) {
			LoadImage();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00476a00
SexyVector2 PhysObj::GetCenter()
{
	return SexyVector2((mUnk0x1c + mUnk0x14) * 0.5, (mUnk0x20 + mUnk0x18) * 0.5);
}
