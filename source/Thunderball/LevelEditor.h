#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include "DataSync.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>
#include <SexyAppFramework/Widget.h>
#include <list>
#include <set>
#include <string>

namespace Sexy
{
class Board;
class PhysObj;
class Graphics;
class DataSync;
class MemoryImage;
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
	bool SetEditValNum(double theNum);

	bool EditKeyPrefix(const std::string& param_1, const std::string& param_2);

	bool EditGetSetVal(const std::string& theKey, EditVal* theVal, bool param_3, bool param_4);
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
// SIZE: 0x2f4
class LevelEditor : public Widget {
public:
	Board* mBoard; // +0x88
	MemoryImage* mGridImage; // +0x8c
	SmartPtr<GlobalEditVal> mGlobalEditVal; // +0x90
	int mUnk0x94; // +0x94
	Widget* mEditWidgets[5]; // +0x98
	int mUnk0xac; // +0xac
	DataWriter mUnk0xb0[11]; // +0xb0
	DataWriter mUndoWriter; // +0x1e4
	DataWriter mUnk0x200; // +0x200
	std::set<PhysObj*> mUnk0x21c; // +0x21c
	std::list<SmartPtr<PhysObj> > mSelectedObjects; // +0x228
	int mUnk0x234; // +0x234
	bool mUnk0x238; // +0x238
	char mPadding0x239[3]; // +0x239
	int mUnk0x23c; // +0x23c
	int mUnk0x240; // +0x240
	int mUnk0x244; // +0x244
	int mUnk0x248; // +0x248
	int mUnk0x24c; // +0x24c
	int mUnk0x250; // +0x250
	int mUnk0x254; // +0x254
	int mUnk0x258; // +0x258
	float mUnk0x25c; // +0x25c
	float mUnk0x260; // +0x260
	float mUnk0x264; // +0x264
	float mUnk0x268; // +0x268
	float mUnk0x26c; // +0x26c
	float mUnk0x270; // +0x270
	float mUnk0x274; // +0x274
	bool mUnk0x278; // +0x278
	bool mUnk0x279; // +0x279
	char mPadding0x27a[2]; // +0x27a
	int mUnk0x27c; // +0x27c
	int mUnk0x280; // +0x280
	int mUnk0x284; // +0x284
	bool mUnk0x288; // +0x288
	char mPadding0x289[3]; // +0x289
	int mUnk0x28c; // +0x28c
	int mUnk0x290; // +0x290
	int mUnk0x294; // +0x294
	bool mUnk0x298; // +0x298
	bool mUnk0x299; // +0x299
	bool mUnk0x29a; // +0x29a
	bool mUnk0x29b; // +0x29b
	bool mUnk0x29c; // +0x29c
	char mPadding0x29d[3]; // +0x29d
	int mUnk0x2a0; // +0x2a0
	bool mUnk0x2a4; // +0x2a4
	bool mUnk0x2a5; // +0x2a5
	char mPadding0x2a6[2]; // +0x2a6
	std::string mUnk0x2a8; // +0x2a8
	int mUnk0x2c4; // +0x2c4
	int mUnk0x2c8; // +0x2c8
	int mUnk0x2cc; // +0x2cc
	bool mUnk0x2d0; // +0x2d0
	char mPadding0x2d1[3]; // +0x2d1
	float mUnk0x2d4; // +0x2d4
	float mUnk0x2d8; // +0x2d8
	float mUnk0x2dc; // +0x2dc
	float mUnk0x2e0; // +0x2e0
	float mUnk0x2e4; // +0x2e4
	float mUnk0x2e8; // +0x2e8
	int mUnk0x2ec; // +0x2ec
	int mUnk0x2f0; // +0x2f0

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
