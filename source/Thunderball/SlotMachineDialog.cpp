#include "SlotMachineDialog.h"

#include "Ball.h"
#include "Board.h"
#include "DataSync.h"
#include "LogicMgr.h"
#include "PhysObj.h"
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

// STUB: POPCAPGAME1 0x00496120
void SlotMachineDialog::Resize(int param_1, int param_2, int param_3, int param_4)
{
}

// STUB: POPCAPGAME1 0x00496130
int SlotMachineDialog::GetPreferredHeight(int param_1)
{
    return 0;
}

// STUB: POPCAPGAME1 0x00496150
void SlotMachineDialog::Draw(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x00496730
void SlotMachineDialog::CalcCurLight()
{
}

// STUB: POPCAPGAME1 0x0049b3d0
bool SlotMachineDialog::UpdatePointer(bool param_1)
{
    return false;
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
