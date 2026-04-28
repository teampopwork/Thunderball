#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>
#include <SexyAppFramework/Widget.h>
#include <string>

namespace Sexy
{
class Board;
class PhysObj;
class Graphics;
class DataSync;
class WidgetManager;

class EditVal {
public:
	bool mStringCached;
	bool mNumCached;
	std::string mString;
	double mNum;

	EditVal();
	EditVal(std::string& theValue);
	EditVal(double theValue);

	double ToNum();
	std::string ToString();
};

// VTABLE: POPCAPGAME1 0x005d2a24
class EditValObj : public RefCount {
public:
	EditVal* mEditVal; // +0x8
	bool mUnk0xc;      // +0xc
	bool mUnk0xd;      // +0xd

	EditValObj();

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);

	bool EditValSyncNum(int& theNum);
	bool EditValSyncNum(int& theNum, int param_2, int param_3);

	bool EditValSyncNum(ulong& theNum);

	bool EditValSyncNum(float& theNum);
	bool EditValSyncNum(float& theNum, float param_2, float param_3);

	bool EditValSyncBool(bool& theBool);
	bool EditValSyncString(std::string& theString);

	double GetEditValNum();
	void SetEditValNum(double theNum);

	bool EditKeyPrefix(const std::string& param_1, const std::string& param_2);

	void EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4);
	void EditSetVal(const std::string& theKey, EditVal* theVal, bool param_3);
	void EditGetVal(const std::string& theKey, EditVal* theVal);

	bool EditGetSetValDelegate(EditValObj* theObj, const std::string& param_2);
};

class GlobalEditVal : public EditValObj {
public:
	virtual ~GlobalEditVal();
	GlobalEditVal();
	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
};

// VTABLE: POPCAPGAME1 0x005d7354
class LevelEditor : public Widget {
public:
	LevelEditor(Board* param_1);
	virtual ~LevelEditor();

	virtual void MouseMove(int param_1, int param_2);
	virtual void MouseEnter();
	virtual void MouseLeave();
	virtual void MouseUp(int param_1, int param_2, int param_3);
	virtual void MouseDrag(int param_1, int param_2);
	virtual void MouseDown(int param_1, int param_2, int param_3);
	virtual void MouseWheel(int param_1);
	virtual void KeyDown(KeyCode param_1);
	virtual void KeyChar(char param_1);
	virtual void AddedToManager(WidgetManager* param_1);
	virtual void RemovedFromManager(WidgetManager* param_1);
	virtual void Draw(Graphics* param_1);
	virtual void Update();

	void LoadLevel(std::string* param_1);
	void LoadNextLevel();
	void SaveLevel(std::string* param_1);
	void InspectAutoSaves(bool param_1);
	void DoAutoSave(bool param_1);
	void Init();
	void ToggleEdit(bool param_1, bool param_2);
	void Reset();

	void CreateGridImage();
	void DrawGrid(Graphics* param_1);
	void DrawObjectEdit(Graphics* param_1, PhysObj* param_2, int param_3);

	void EditClearSel();
	void SetSingleSelMode(bool param_1);
	void SelectNextObject(bool param_1);
	void RemoveSelObject(PhysObj* param_1);
	void InsertSelObject(PhysObj* param_1, bool param_2);
	void SetSelectFlags(int param_1);
	void SetDisplayFlags(int param_1);
	void SetInterfaceMode(int param_1);
	void SetDragMode(int param_1);
	void BeginOrderMode(bool param_1);
	void GetObjZOrder(std::list<Sexy::SmartPtr<PhysObj>>::iterator param_1, bool param_2, bool param_3);

	void RefreshEditWidgets();
	void SetNumEditors(int param_1);
	void GetLastFocusEditor();
	void ShowKeyboardHelp();
	void DoRightClickPopup(bool param_1);

	int GetMouseX();
	int GetMouseY();
	std::list<Sexy::SmartPtr<PhysObj>>::iterator EditGetObjAt(int param_1, int param_2);
	void EditGetClosestGridPos(float* param_1, float* param_2);
	bool IsAltKeyUsed(int param_1);

	void EditClear();
	void EditClearPlace();
	void EditClearLevel();
	void EditCopyAttributes();
	void EditCopy(int param_1);
	void EditPaste(int param_1, bool param_2);
	void EditDelete(bool param_1, bool param_2);
	void EditPerformUndo(bool param_1);
	void EditMarkUndoPoint(bool param_1);
	void EditClearUndoPoint();

	void EditMoveSel(int param_1, int param_2);
	void EditResetMoveTimes();
	void EditSetDrawMovements(bool param_1, bool param_2);
	void EditCheckBindMove(PhysObj* param_1, float param_2, float param_3);

	void EditBringToFront(bool param_1, bool param_2);

	void CreateNewBrick();
	void GetCurBrickAttributes();
	void DoBrickDrag(bool param_1);
	void DoBrickAttach();
	void ReversePoly();
	void AddBrick(bool param_1, bool param_2);
	void MakeBrickCircle(bool param_1);
	void EditBindBlocks(bool param_1);
	void ConnectHole(bool param_1);

	void StartPlaceObj(int param_1);
	void IncPlaceObj(int param_1);
	void AddLine();
	void AddPoly();
	void LoadImageObject();

	void SyncGlobals(DataSync* param_1);

	void DoPageUpDown(bool param_1);
	void DoNumberKeyBuffer(int param_1, bool param_2);

	void ReflectSelected(bool param_1, bool param_2);

	void GiveEqualPhase();
	void MoveFeverStuff(bool param_1);
	void ShowFreeBallStuff(bool param_1);
};

} // namespace Sexy

#endif // __LEVELEDITOR_H__
