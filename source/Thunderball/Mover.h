#ifndef __MOVER_H__
#define __MOVER_H__

#include "LevelEditor.h"

#include <string>

namespace Sexy
{

class Graphics;
class DataSync;
class PhysObj;

class Mover : public EditValObj {
public:
	Mover();
	virtual ~Mover();

	int mType; // +0x10
	int mOffset; // +0x14
	int mRadius; // +0x18
	int mTime; // +0x1C
	float mPhase; // +0x20
	float mMoveRotation; // +0x24
	int mRadius2; // +0x28
	int mPause1; // +0x2C
	int mPhase1; // +0x30
	int mPause2; // +0x34
	int mPhase2; // +0x38
	float mMaxAngle; // +0x3C
	float mPostDelayPhase; // +0x40
	float mRotation; // +0x44
	PhysObj* mPhysObj; // +0x48
	

	float mUnk0x54;
	float mUnk0x58;
	float mUnk0x5c;
	float mUnk0x60;
	int mUnk0x64;

    virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);

	void Translate(float param_1, float param_2);
	void SetPos(float param_1, float param_2);
	float GetTimeTillPhase(int param_1, float param_2);
	int GetMovePos(int param_1);
	void CalcPos(int param_1, float param_2);
	void DrawMovement(Graphics* g);
	void InitDefaults();
	void SyncState(DataSync* param_1);
};

} // namespace Sexy

#endif // __MOVER_H__