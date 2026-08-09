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
	char mPad0x150[0x2c];         // +0x150
	float mAngularVelocity;       // +0x17c
	bool mUnk0x180;               // +0x180
	char mPad0x181[0x13];         // +0x181
	bool mUnk0x194;               // +0x194
	char mPad0x195[3];            // +0x195
	int mUnk0x198;                // +0x198
	int mUnk0x19c;                // +0x19c
	bool mUnk0x1a0;               // +0x1a0
	bool mUnk0x1a1;               // +0x1a1
	bool mUnk0x1a2;               // +0x1a2
	char mPad0x1a3[0x1d];         // +0x1a3
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
	void CalcPoints();
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
