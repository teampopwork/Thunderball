#ifndef __AIMGR_H__
#define __AIMGR_H__

namespace Sexy
{
class Board;
class Graphics;
class PhysObj;
class SexyVector2;
class DataSync;

class AIMgr {
public:
	AIMgr(Board* param_1);
	~AIMgr();

	float KeepAngleInRange(float param_1);
	void GetEyePos(SexyVector2* param_1);
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
