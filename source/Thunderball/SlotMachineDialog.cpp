#include "SlotMachineDialog.h"

#include "Ball.h"
#include "Board.h"
#include "DataSync.h"
#include "LogicMgr.h"
#include "PhysObj.h"
#include "Res.h"
#include "SoundMgr.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/ModVal.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004ab260
SlotMachineDialog::SlotMachineDialog(Board* param_1) : ThunderDialog(0x17, false, "Lucky Spin!", "", "", 0)
{
	mBoard = param_1;
	mApp = param_1->mApp;
}

// SYNTHETIC: POPCAPGAME1 0x0049cd10
// Sexy::SlotMachineDialog::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0049b310
SlotMachineDialog::~SlotMachineDialog()
{
	RemoveAllWidgets(true, false);
}

// FUNCTION: POPCAPGAME1 0x00496120
void SlotMachineDialog::Resize(int param_1, int param_2, int param_3, int param_4)
{
	Dialog::Resize(param_1, param_2, param_3, param_4);
}

// FUNCTION: POPCAPGAME1 0x00496130
int SlotMachineDialog::GetPreferredHeight(int param_1)
{
	return ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp752,120", 300);
}

// STUB: POPCAPGAME1 0x00496150
void SlotMachineDialog::Draw(Graphics* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00496730
void SlotMachineDialog::CalcCurLight()
{
	float anAngles[4];
	anAngles[0] = (float)(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp768,230", 45) * 3.14159274101257 / 180.0);
	anAngles[1] = (float)(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp769,231", 135) * 3.14159274101257 / 180.0);
	anAngles[2] = (float)(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp770,232", 225) * 3.14159274101257 / 180.0);
	anAngles[3] = (float)(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp771,233", 315) * 3.14159274101257 / 180.0);

	int aLight = 0;
	for (; aLight < 4; aLight++) {
		if (mUnk0x190 < anAngles[aLight]) {
			break;
		}
	}
	mUnk0x180 = aLight % 4;

	int aBrightness = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp772,244", 30);
	if (mUnk0x184 != 0) {
		for (int i = 0; i < 40; i++) {
			mUnk0x19c[i] = 0;
		}

		if ((mUnk0x184 / 20) % 2 != 1) {
			return;
		}
		if (mUnk0x180 > 0) {
			int aStart = mUnk0x180 * 10 - 5;
			int anEnd = aStart + 10;
			for (int i = aStart; i <= anEnd; i++) {
				mUnk0x19c[i] = aBrightness;
			}
		}
		else {
			for (int i = 0; i <= 5; i++) {
				mUnk0x19c[i] = aBrightness;
			}
			for (int i = 35; i < 40; i++) {
				mUnk0x19c[i] = aBrightness;
			}
		}
		return;
	}

	float anOffsetAngle = (float)ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp773,272", -5);
	anOffsetAngle = (float)(anOffsetAngle * 3.14159274101257 / 180.0);
	int anOffset = (int)((mUnk0x190 - anOffsetAngle) * 20.0 / 3.14159274101257);
	if (anOffset < 0) {
		int aRemainder = -anOffset % 40;
		mUnk0x198 = aRemainder == 0 ? 0 : 40 - aRemainder;
	}
	else {
		mUnk0x198 = anOffset % 40;
	}
	mUnk0x19c[mUnk0x198] = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp774,273", 30);
}

// FUNCTION: POPCAPGAME1 0x0049b3d0
void SlotMachineDialog::UpdatePointer(bool param_1)
{
	bool aStopping = false;
	int anOldLight = mUnk0x198;
	if (mUnk0x248 > 0) {
		double anAngle = mUnk0x190;
		mUnk0x248--;
		aStopping = true;
		mUnk0x190 = (float)(anAngle - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp777,315", 0.0f));
	}
	else {
		mUnk0x190 -= mUnk0x194;
	}

	CalcCurLight();
	if (mUnk0x190 > 6.2831854820251465) {
		mUnk0x190 = (float)(mUnk0x190 - 6.2831854820251465);
	}
	else if (mUnk0x190 < 0.0f) {
		mUnk0x190 = (float)(mUnk0x190 + 6.2831854820251465);
	}

	if (aStopping) {
		return;
	}
	if (mUnk0x244 > 0) {
		mUnk0x244--;
	}

	if ((mUnk0x198 - 5) % 10 != 0) {
		if ((mUnk0x198 + 4) % 10 == 0 && anOldLight != mUnk0x198) {
			mBoard->mSoundMgr->AddSound(SOUND_DING, 0.0f, 1);
			mUnk0x23c = (mUnk0x23c + 1) % 4;
			if (mUnk0x244 == 0) {
				mUnk0x194 = (float)((double)mUnk0x194 - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp778,346", 0.0016f));
			}
		}
		else if (mUnk0x244 == 0) {
			mUnk0x194 = (float)((double)mUnk0x194 - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp779,349", 0.0008f));
		}
	}

	if (mUnk0x194 <= 0.0f) {
		int aResults[4] = {2, 1, 0, 3};
		mBoard->mLogicMgr->DoSlotMachineResult(aResults[mUnk0x180], mBall.get());
		mUnk0x194 = 0.0f;
		mUnk0x184 = 1;
	}
}

// STUB: POPCAPGAME1 0x0049d2c0
void SlotMachineDialog::Update()
{
}

// STUB: POPCAPGAME1 0x0049d100
void SlotMachineDialog::MouseDown(int param_1, int param_2, int param_3)
{
}

// FUNCTION: POPCAPGAME1 0x0049cd40
void SlotMachineDialog::Init(Ball* param_1, PhysObj* param_2)
{
	mClip = true;
	mBall = param_1;
	mPhysObj = param_2;
	mUnk0x184 = 0;
	mWidth = gSexyApp->mWidth;
	mHeight = gSexyApp->mHeight;
	mUnk0x198 = 0;
	mUnk0x180 = 0;
	mUnk0x240 = 0;

	switch (mBoard->mLogicMgr->GetSlotMachinePowerup())
	{
	case 1: mUnk0x240 = 0; break;
	case 2: mUnk0x240 = 4; break;
	case 3: mUnk0x240 = 1; break;
	case 4: mUnk0x240 = 2; break;
	case 5: mUnk0x240 = 3; break;
	case 6: mUnk0x240 = 5; break;
	case 7: mUnk0x240 = 8; break;
	case 9: mUnk0x240 = 6; break;
	case 12: mUnk0x240 = 7; break;
	}

	mUnk0x190 = (float)((Rand() % 360) * 3.14159274101257 / 180.0);
	mUnk0x194 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp748,62", 0.15f);
	mUnk0x244 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp749,63", 0) +
		Rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp750,63", 100);
	for (int i = 0; i < 40; ++i)
		mUnk0x19c[i] = 0;
	mUnk0x23c = 0;
	mUnk0x248 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SlotMachineDialog.cpp751,69", 40);
	CalcCurLight();
}

// FUNCTION: POPCAPGAME1 0x0049cfe0
void SlotMachineDialog::SyncState(DataSync& param_1)
{
	param_1.SyncLong(mUnk0x180);
	param_1.SyncLong(mUnk0x184);
	DataSync_SyncSmartPtr<Ball>(param_1, mBall);
	DataSync_SyncSmartPtrFactory<PhysObj>(param_1, mPhysObj, NULL);
	param_1.SyncFloat(mUnk0x190);
	param_1.SyncFloat(mUnk0x194);
	param_1.SyncLong(mUnk0x198);
	for (int i = 0; i < 40; ++i)
		param_1.SyncLong(mUnk0x19c[i]);
	param_1.SyncLong(mUnk0x23c);
	param_1.SyncLong(mUnk0x240);
	param_1.SyncLong(mUnk0x244);
	param_1.SyncLong(mUnk0x248);
	param_1.SyncLong(mUnk0x150);
	param_1.SyncLong(mUnk0x15C);
	param_1.SyncLong(mX);
	param_1.SyncLong(mY);
	param_1.SyncLong(mWidth);
	param_1.SyncLong(mHeight);
}
