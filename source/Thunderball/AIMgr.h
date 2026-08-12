#ifndef __AIMGR_H__
#define __AIMGR_H__

#include <list>
#include <SexyAppFramework/SmartPtr.h>
#include <SexyAppFramework/SexyVector.h>

namespace Sexy
{
class Board;
class Graphics;
class PhysObj;
class SexyVector2;
class DataSync;

class AIMgr {
public:
	Board* mBoard;
	class CollisionMgr* mCollisionMgr;
	std::list<SmartPtr<PhysObj> > mUnk0xC;
	std::list<SmartPtr<PhysObj> > mUnk0x18;
	std::list<SmartPtr<PhysObj> > mUnk0x24;
	std::list<SmartPtr<PhysObj> > mUnk0x30;
	SmartPtr<PhysObj> mUnk0x3C;
	SmartPtr<PhysObj> mUnk0x40;
	SmartPtr<PhysObj> mUnk0x44;
	SmartPtr<PhysObj> mUnk0x48;
	bool mUnk0x4C;
	bool mUnk0x4D;
	bool mUnk0x4E;
	bool mUnk0x4F;
	int mUnk0x50;
	int mUnk0x54;
	int mUnk0x58;
	int mUnk0x5C;
	int mUnk0x60;
	float mUnk0x64;
	int mUnk0x68;
	int mUnk0x6C;
	int mUnk0x70;
	int mUnk0x74;
	float mUnk0x78;
	float mUnk0x7C;
	SexyVector2 mEyePos;
	float mUnk0x88;
	float mUnk0x8C;

	AIMgr(Board* param_1);
	virtual ~AIMgr();

	float KeepAngleInRange(float param_1);
	bool GetEyePos(SexyVector2* param_1);
	void NotifyCollision(PhysObj* param_1, PhysObj* param_2);
	float GetAngleForPeg(PhysObj* param_1);
	void Draw(Graphics* param_1);
	void UpdateFreeBallRadius(int param_1);
	void UpdateOneFrame();
	float CalcDefAngle();
	void Clear();
	void Update();
	void BeginThinking2(bool param_1, float param_2, int param_3);
	void BeginThinking(bool param_1, float param_2, int param_3, int param_4);
};

} // namespace Sexy

#endif // __AIMGR_H__
