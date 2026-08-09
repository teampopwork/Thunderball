#include "SlotMachineDialog.h"

#include "Ball.h"
#include "Board.h"
#include "DataSync.h"
#include "PhysObj.h"

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

// STUB: POPCAPGAME1 0x0049cd40
void SlotMachineDialog::Init(Ball* param_1, PhysObj* param_2)
{
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
