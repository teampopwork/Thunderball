#ifndef __GUN_H__
#define __GUN_H__

#include "Poly.h"

#include <string>

namespace Sexy
{
class Board;
class Graphics;
class DataSync;
class Ball;

// VTABLE: POPCAPGAME1 0x005f1234
class Gun : public Poly {
public:
	Gun(Board* param_1);
	virtual ~Gun();

	virtual void SyncState(DataSync* param_1);
	virtual int GetClass();
	virtual void Update();
	virtual void UpdateSlowMo(float param_1);
	virtual void Draw(Graphics* param_1);

	void UpdateCommon();
	bool CanFire();
	float GetMaxGuideLength();
	bool NeedDrawMouseClick();
	void DrawBouncyGuide(Graphics* param_1);
	void DoDrawGuide(Graphics* param_1, float param_2, float param_3, float param_4, float param_5, int param_6, int param_7, int param_8, bool param_9);
	void DrawGuide(Graphics* param_1, bool param_2);
	void CalcAngularVelocity();
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
