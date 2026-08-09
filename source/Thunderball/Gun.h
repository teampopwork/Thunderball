#ifndef __GUN_H__
#define __GUN_H__

#include "Poly.h"

#include <list>
#include <string>
#include <utility>
#include <vector>
#include <SexyAppFramework/SexyVector.h>

namespace Sexy
{
class Board;
class Graphics;
class DataSync;
class Ball;

// VTABLE: POPCAPGAME1 0x005f286c
class Gun : public Poly {
public:
	Board* mBoard;                // +0x148
	int mUpdateCount;             // +0x14c
	float mAngle;                 // +0x150
	float mTargetAngle;           // +0x154
	float mUnk0x158;              // +0x158
	float mUnk0x15c;              // +0x15c
	float mUnk0x160;              // +0x160
	float mUnk0x164;              // +0x164
	float mUnk0x168;              // +0x168
	float mUnk0x16c;              // +0x16c
	float mUnk0x170;              // +0x170
	float mUnk0x174;              // +0x174
	float mUnk0x178;              // +0x178
	float mAngularVelocity;       // +0x17c
	bool mUnk0x180;               // +0x180
	char mPad0x181[3];            // +0x181
	float mLastTrackedAngle;      // +0x184
	float mSettledAngle;          // +0x188
	int mSettledUpdate;           // +0x18c
	int mAngleStableTicks;        // +0x190
	bool mUnk0x194;               // +0x194
	bool mUnk0x195;               // +0x195
	char mPad0x196[2];            // +0x196
	int mUnk0x198;                // +0x198
	int mUnk0x19c;                // +0x19c
	bool mUnk0x1a0;               // +0x1a0
	bool mUnk0x1a1;               // +0x1a1
	bool mUnk0x1a2;               // +0x1a2
	char mPad0x1a3;               // +0x1a3
	float mUnk0x1a4;              // +0x1a4
	float mUnk0x1a8;              // +0x1a8
	float mUnk0x1ac;              // +0x1ac
	float mUnk0x1b0;              // +0x1b0
	float mUnk0x1b4;              // +0x1b4
	float mUnk0x1b8;              // +0x1b8
	float mUnk0x1bc;              // +0x1bc
	SmartPtr<Ball> mBall;         // +0x1c0
	std::vector<SexyVector2> mGuidePoints; // +0x1c4
	std::list<std::pair<float, int> > mAngleHistory; // +0x1d4

	Gun(Board* param_1);
	virtual ~Gun();

	virtual void SyncState(DataSync& param_1);
	virtual int GetClass();
	virtual void Update();
	virtual void UpdateSlowMo(float param_1);
	virtual void Draw(Graphics* param_1);

	void UpdateCommon();
	bool CanFire();
	int GetMaxGuideLength();
	bool NeedDrawMouseClick();
	void DrawBouncyGuide(Graphics* param_1);
	void DoDrawGuide(Graphics* param_1, float param_2, float param_3, float param_4, float param_5, int param_6, int param_7, int param_8, bool param_9);
	void DrawGuide(Graphics* param_1, bool param_2);
	float CalcAngularVelocity();
	__declspec(noinline) void CalcPoints();
	void SetFireball(bool param_1);
	void Reload(Ball* param_1);
	void SetAngle(float param_1, bool param_2);
	void UpdateBouncyGuide();
	void Fire(bool param_1);
	void Clear();
	void SetDoBouncyGuide(bool param_1);
};

} // namespace Sexy

#endif // __GUN_H__
