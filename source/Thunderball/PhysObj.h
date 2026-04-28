#ifndef __PHYSOBJ_H__
#define __PHYSOBJ_H__

#include "LevelEditor.h"
#include "ConstEnums.h"

#include <SexyAppFramework/Rect.h>
#include <string>

namespace Sexy
{
class Graphics;
class PegInfo;
class Image;
class DataSync;
class Mover;
class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1924
class PhysObj : public EditValObj {
public:
	static int mSyncType;
	static bool mFastLoad;

	int mUnk0x10; // +0x10

	float mUnk0x14; // +0x14
	float mUnk0x18; // +0x18
	float mUnk0x1c; // +0x1c
	float mUnk0x20; // +0x20

	bool mUnk0x24;
	bool mUnk0x25;
	bool mUnk0x26;
	bool mUnk0x27;
	bool mUnk0x28;
	bool mUnk0x29;
	bool mUnk0x2a;
	bool mUnk0x2b;
	bool mUnk0x2c;
	bool mUnk0x2d;
	bool mUnk0x2e;
	bool mUnk0x2f;
	bool mUnk0x30;

	float mUnk0x34;
	float mUnk0x38;
	float mUnk0x3c;
	int mUnk0x40;
	int mUnk0x44;

	SmartPtr<Mover> mMover; // +0x48
	int mUnk0x4c;
	int mUnk0x50;
	int mUnk0x54;
	static int gCurSortId;
	int mCurSortId; // +0x58
	

	std::string mUnk0x5c;
	std::string mUnk0x78;
	std::string mUnk0x94;

	int mUnk0xb0;
	Image* mUnk0xb4;
	float mUnk0xb8;
	float mUnk0xbc;
	float mUnk0xc0;
	bool mUnk0xc4;
	int mUnk0xc8;
	int mUnk0xcc;
	SmartPtr<PegInfo> mPegInfo; // +0xd0
	int mUnk0xd4;
	int mUnk0xd8;
	int mUnk0xdc;
	bool mUnk0xe0;
	bool mUnk0xe1;


	PhysObj();
	virtual ~PhysObj();

	static PhysObj* ClassFactory(int param_1);

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
	virtual void SyncState(DataSync* theSync);
	virtual int GetClass();
	virtual uint GetTypeFlags();
	virtual void EditDrawMovement(Graphics* g);
	virtual void EditDrawOutline(Graphics* g);
	virtual void EditDrawPoints(Graphics* g);
	virtual bool EditContains(float param_1, float param_2, bool param_3);
	virtual bool EditIntersects(Rect param_1);
	virtual void EditTranslate(float param_1, float param_2);
	virtual void EditSetPos(float param_1, float param_2);
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditFinishDrag();
	virtual void EditReloadImage();
	virtual void EditReflect(float param_1, float param_2, bool param_3);
	virtual void SetPos(float theX, float theY);
	virtual void Translate(float theDx, float theDy);
	virtual void SetVelocity(float theVx, float theVy);
	virtual void PegChangedHook(bool param_1);
	virtual void DeleteImage();
	virtual void Update();
	virtual void UpdateSlowMo(float param_1);
	virtual void DrawShadow(Graphics* g);
	virtual void Draw(Graphics* g);
	virtual void DrawLight(Graphics* g);
	virtual void AddedToGame();
	virtual void NotifyCollision(PhysObj* param_1);
	virtual SexyVector2 GetCenter();
	virtual float GetXPos();
	virtual float GetYPos();
	virtual bool IsCollidableWith(PhysObj* param_1);
	virtual void SetActiveWithGrowAnim(bool param_1);

	void AdjustRect(float theX, float theY, float theWidth, float theHeight);
	float GetOrigX();
	float GetOrigY();
	void SetActive(bool param_1);
	void SetIsPeg(bool isPeg);
	void SetPegType(PegType theType);
	void SetMoveUpdateCnt(int param_1);
	void SetMovingPercent(float param_1, bool param_2);
	void SyncPosWithMover();
	bool HasTypeFlags(int param_1);
	void InitDefaults();
	bool LoadImage();

	void DrawImage(
		Graphics* g,
		Image* param_2,
		float param_3,
		float param_4,
		float param_5,
		bool param_6,
		bool param_7
	);
	void DrawImage(
		Graphics* g,
		float param_2,
		float param_3,
		float param_4,
		bool param_5,
		int param_6,
		float param_7
	);
	void DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6);
};

} // namespace Sexy

#endif // __PHYSOBJ_H__
