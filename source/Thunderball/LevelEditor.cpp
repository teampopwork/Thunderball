#include "LevelEditor.h"

#include <SexyAppFramework/Common.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0040b010
EditVal::EditVal()
{
	mStringCached = false;
	mNumCached = false;
	mString = "";
	mNum = 0;
}

// FUNCTION: POPCAPGAME1 0x004111a0
EditVal::EditVal(std::string& theValue)
{
	mStringCached = true;
	mNumCached = false;
	mString = theValue;
}

// FUNCTION: POPCAPGAME1 0x0040b030
EditVal::EditVal(double theValue)
{
	mStringCached = false;
	mNumCached = true;
	mNum = theValue;
}

// FUNCTION: POPCAPGAME1 0x00411210
std::string EditVal::ToString()
{
	if (mStringCached == false) {
		char local_14[2];
		mString = StrFormat(local_14, "%g", mNum);
		mStringCached = true;
	}

	return mString;
}

// FUNCTION: POPCAPGAME1 0x004091b0
double EditVal::ToNum()
{
	if (mNumCached == false) {
		int iVar1 = sscanf(mString.c_str(), "%lf", &mNum);
		if (iVar1 != 1) {
			mNum = 0;
		}
		mNumCached = true;
	}

	return mNum;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// STUB: POPCAPGAME1 0x00402d00
EditValObj::EditValObj()
{
}

// SYNTHETIC: POPCAPGAME1 0x004073e0
// Sexy::EditValObj::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0054b760
bool EditValObj::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x0041ec80
bool EditValObj::EditValSyncNum(int& theNum)
{
	return false;
}

// STUB: POPCAPGAME1 0x004112a0
bool EditValObj::EditValSyncNum(int& theNum, int param_2, int param_3)
{
	return false;
}

// STUB: POPCAPGAME1 0x00411380
bool EditValObj::EditValSyncNum(ulong& theNum)
{
	return false;
}

// STUB: POPCAPGAME1 0x00411470
bool EditValObj::EditValSyncNum(float& theNum)
{
	return false;
}

// STUB: POPCAPGAME1 0x00411530
bool EditValObj::EditValSyncNum(float& theNum, float param_2, float param_3)
{
	return false;
}

// STUB: POPCAPGAME1 0x00411640
bool EditValObj::EditValSyncBool(bool& theBool)
{
	return false;
}

// STUB: POPCAPGAME1 0x0041ed40
bool EditValObj::EditValSyncString(std::string& theString)
{
	return false;
}

// STUB: POPCAPGAME1 0x0040a100
double EditValObj::GetEditValNum()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00411730
void EditValObj::SetEditValNum(double theNum)
{
}

// STUB: POPCAPGAME1 0x004091f0
bool EditValObj::EditKeyPrefix(const std::string& param_1, const std::string& param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x00402d20
void EditValObj::EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4)
{
}

// STUB: POPCAPGAME1 0x00407410
void EditValObj::EditSetVal(const std::string& theKey, EditVal* theVal, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00407430
void EditValObj::EditGetVal(const std::string& theKey, EditVal* theVal)
{
}

// STUB: POPCAPGAME1 0x00402d60
bool EditValObj::EditGetSetValDelegate(EditValObj* theObj, const std::string& param_2)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// STUB: POPCAPGAME1 0x00402f90
GlobalEditVal::GlobalEditVal()
{
}

// SYNTHETIC: POPCAPGAME1 0x00407490
// Sexy::GlobalEditVal::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00402fc0
GlobalEditVal::~GlobalEditVal()
{
}

// STUB: POPCAPGAME1 0x0041ee00
bool GlobalEditVal::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// STUB: POPCAPGAME1 0x00422ab0
LevelEditor::LevelEditor(Board* param_1)
{
}

// SYNTHETIC: POPCAPGAME1 0x00422d60
// Sexy::LevelEditor::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00421400
LevelEditor::~LevelEditor()
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::MouseMove(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::MouseEnter()
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::MouseLeave()
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::RefreshEditWidgets()
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::SetNumEditors(int param_1)
{
}

// STUB: POPCAPGAME1 0x
void LevelEditor::InsertSelObject(PhysObj* param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x
std::list<Sexy::SmartPtr<PhysObj>>::iterator LevelEditor::EditGetObjAt(int param_1, int param_2)
{
	return std::list<Sexy::SmartPtr<PhysObj>>::iterator();
}

// STUB: POPCAPGAME1 0x
void LevelEditor::EditGetClosestGridPos(float* param_1, float* param_2)
{
}

// STUB: POPCAPGAME1 0x00403190
int LevelEditor::GetMouseX()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00403210
int LevelEditor::GetMouseY()
{
	return 0;
}

// STUB: POPCAPGAME1 0x0042b0c0
void LevelEditor::EditClearLevel()
{
}

// STUB: POPCAPGAME1 0x00428b50
void LevelEditor::EditCopyAttributes()
{
}

// STUB: POPCAPGAME1 0x0040a220
void LevelEditor::EditBindBlocks(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040b0f0
void LevelEditor::ConnectHole(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040a2c0
void LevelEditor::EditCheckBindMove(PhysObj* param_1, float param_2, float param_3)
{
}

// STUB: POPCAPGAME1 0x0040a360
void LevelEditor::EditSetDrawMovements(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00403290
void LevelEditor::EditClearUndoPoint()
{
}

// STUB: POPCAPGAME1 0x0040b1b0
void LevelEditor::EditMoveSel(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x0040a410
void LevelEditor::EditResetMoveTimes()
{
}

// STUB: POPCAPGAME1 0x0040b060
void LevelEditor::Reset()
{
}

// STUB: POPCAPGAME1 0x004074c0
void LevelEditor::DoBrickDrag(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040a520
void LevelEditor::DoBrickAttach()
{
}

// STUB: POPCAPGAME1 0x0040a680
void LevelEditor::ReversePoly()
{
}

// STUB: POPCAPGAME1 0x00411990
void LevelEditor::GiveEqualPhase()
{
}

// STUB: POPCAPGAME1 0x004032b0
void LevelEditor::GetLastFocusEditor()
{
}

// STUB: POPCAPGAME1 0x00407520
void LevelEditor::DoRightClickPopup(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040a6f0
void LevelEditor::GetObjZOrder(std::list<Sexy::SmartPtr<PhysObj>>::iterator param_1, bool param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00411b60
void LevelEditor::ShowKeyboardHelp()
{
}

// STUB: POPCAPGAME1 0x004032f0
bool LevelEditor::IsAltKeyUsed(int param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x00403480
void LevelEditor::CreateNewBrick()
{
}

// STUB: POPCAPGAME1 0x00423080
void LevelEditor::StartPlaceObj(int param_1)
{
}

// STUB: POPCAPGAME1 0x004076c0
void LevelEditor::GetCurBrickAttributes()
{
}

// STUB: POPCAPGAME1 0x0040a830
void LevelEditor::MoveFeverStuff(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0040b300
void LevelEditor::ShowFreeBallStuff(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00407740
void LevelEditor::DrawObjectEdit(Graphics* param_1, PhysObj* param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x004117e0
void LevelEditor::EditClearSel()
{
}

// STUB: POPCAPGAME1 0x00422d90
void LevelEditor::EditBringToFront(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00411c50
void LevelEditor::SetSelectFlags(int param_1)
{
}

// STUB: POPCAPGAME1 0x00411d80
void LevelEditor::SetDisplayFlags(int param_1)
{
}

// STUB: POPCAPGAME1 0x00411dc0
void LevelEditor::SetInterfaceMode(int param_1)
{
}

// STUB: POPCAPGAME1 0x0041f310
void LevelEditor::SyncGlobals(DataSync* param_1)
{
}

// STUB: POPCAPGAME1 0x0041f5f0
void LevelEditor::BeginOrderMode(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004118c0
void LevelEditor::RemoveSelObject(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0040a450
void LevelEditor::SetDragMode(int param_1)
{
}

// STUB: POPCAPGAME1 0x0041f6a0
void LevelEditor::MouseUp(int param_1, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x004280a0
void LevelEditor::SaveLevel(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x00428770
void LevelEditor::DoAutoSave(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00428e40
void LevelEditor::Update()
{
}

// STUB: POPCAPGAME1 0x00425f90
void LevelEditor::EditCopy(int param_1)
{
}

// STUB: POPCAPGAME1 0x00426450
void LevelEditor::EditMarkUndoPoint(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004265c0
void LevelEditor::SelectNextObject(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00426790
void LevelEditor::SetSingleSelMode(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00426730
void LevelEditor::MouseDrag(int param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x00428aa0
void LevelEditor::EditDelete(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042ab00
void LevelEditor::EditClearPlace()
{
}

// STUB: POPCAPGAME1 0x0042ab30
void LevelEditor::EditClear()
{
}

// STUB: POPCAPGAME1 0x0042e060
void LevelEditor::LoadLevel(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x0042e0b0
void LevelEditor::LoadNextLevel()
{
}

// STUB: POPCAPGAME1 0x0042e1f0
void LevelEditor::InspectAutoSaves(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0042b490
void LevelEditor::AddLine()
{
}

// STUB: POPCAPGAME1 0x0042b6c0
void LevelEditor::AddPoly()
{
}

// STUB: POPCAPGAME1 0x0042b8b0
void LevelEditor::AddBrick(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042ba70
void LevelEditor::MakeBrickCircle(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0042c270
void LevelEditor::LoadImageObject()
{
}

// STUB: POPCAPGAME1 0x00428cb0
void LevelEditor::IncPlaceObj(int param_1)
{
}

// STUB: POPCAPGAME1 0x00428d20
void LevelEditor::DoPageUpDown(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00428d50
void LevelEditor::MouseWheel(int param_1)
{
}

// STUB: POPCAPGAME1 0x0042ab50
void LevelEditor::EditPaste(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042b210
void LevelEditor::EditPerformUndo(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0042bda0
void LevelEditor::DoNumberKeyBuffer(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042e950
void LevelEditor::MouseDown(int param_1, int param_2, int param_3)
{
}

// STUB: POPCAPGAME1 0x0042be30
void LevelEditor::KeyDown(KeyCode param_1)
{
}

// STUB: POPCAPGAME1 0x0042c8e0
void LevelEditor::ReflectSelected(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00421590
void LevelEditor::Init()
{
}

// STUB: POPCAPGAME1 0x0042e620
void LevelEditor::ToggleEdit(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0042eee0
void LevelEditor::KeyChar(char param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00402fd0
void LevelEditor::AddedToManager(WidgetManager* param_1)
{
	Widget::AddedToManager(param_1);
}

// STUB: POPCAPGAME1 0x00428940
void LevelEditor::RemovedFromManager(WidgetManager* param_1)
{
}

// STUB: POPCAPGAME1 0x00403310
void LevelEditor::CreateGridImage()
{
}

// STUB: POPCAPGAME1 0x00403550
void LevelEditor::DrawGrid(Graphics* param_1)
{
}

// STUB: POPCAPGAME1 0x004a6820
void LevelEditor::Draw(Graphics* param_1)
{
}
