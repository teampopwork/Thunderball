#ifndef __PEGINFO_H__
#define __PEGINFO_H__

#include "LevelEditor.h"
#include "ConstEnums.h"

#include <string>

namespace Sexy
{
class DataSync;
class Graphics;
class PhysObj;
class Brick;
class Ball;

class PegInfo : public EditValObj {
public:
	PegType mPegType; // +0x10
	bool mUnk0x14; // +0x14
	bool mUnk0x15; // +0x15
	bool mUnk0x16; // +0x16

	PegInfo();
	virtual ~PegInfo();

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
	virtual void SyncState(DataSync* param_1);
	virtual void Update(PhysObj* param_1);

	void Reset();
	void SetHit(bool param_1);
	void DoFlash(int param_1);
	void DoFlashBlink(int param_1);
	void DrawBigPulse(Graphics* param_1, int param_2, float param_3, float param_4, int param_5, int param_6);
	void DrawBrick(Brick* param_1, Graphics* param_2);
	void DrawGlow(PhysObj* param_1, Graphics* param_2);
	void DrawLight(PhysObj* param_1, Graphics* param_2);
	void DrawBall(Ball* param_1, Graphics* param_2);
    void DrawColorblind(Graphics* param_1, PhysObj* param_2);
	void IncCrumble();
};


} // namespace Sexy

#endif // __PEGINFO_H__
