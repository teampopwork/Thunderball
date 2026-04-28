#ifndef __POLY_H__
#define __POLY_H__

#include "PhysObj.h"

#include <string>

namespace Sexy
{

class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1f4c
class Poly : public PhysObj {
public:
	Poly();
	virtual ~Poly();

	virtual bool EditGetSetValHook(std::string* param_1, bool param_2);
	virtual void SyncState(DataSync* theSync);
	virtual int GetClass();
	virtual void EditDrawOutline(Graphics* g);
	virtual void EditDrawPoints(Graphics* g);
	virtual bool EditContains(float param_1, float param_2, bool param_3);
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditFinishDrag();
	virtual void EditReflect(float param_1, float param_2, bool param_3);
	virtual void SetPos(float param_1, float param_2);
	virtual void Translate(float param_1, float param_2);
	virtual void SetVelocity(float param_1, float param_2);
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
	virtual void SetActiveWithGrowAnim(bool param_1);
	virtual void InitDefaults();

	void AddBubbles(int param_1);
	void ActualSetPos(float param_1, float param_2);
	void CalcBoundingBox();
	void CheckConvex();
	void InitRotatedFromPoints(float param_1);
	void DelayedInitRotatedFromPoints(float param_1);
	void EnsureLines();
	bool PointInside(float param_1, float param_2);
	bool GetStandardRectF(FRect* param_1);
	bool GetStandardRect(Rect* param_1);
	bool EditIntersects(Rect* param_1);
	void DrawPoly(Graphics* g, int param_2, int param_3);
	bool CheckCollision(
		SexyVector2* param_1,
		SexyVector2* param_2,
		float param_3,
		float* param_4,
		SexyVector2* param_5,
		SexyVector2* param_6,
		SexyVector2* param_7,
		SexyVector2* param_8
	);
	void SetRotation(float param_1);
	void AddPoint(float param_1, float param_2);
	void InitFromPoints();
	void ReverseLines();
	void SetNormalDir(int param_1);
	void Close();
	void MoveCenterTo(float param_1, float param_2);
	void SetScale(float param_1);
	void InitFromRect(float param_1, float param_2, float param_3, float param_4);
	void SyncCommon(DataSync* theSync, bool param_2);
};

} // namespace Sexy

#endif // __POLY_H__
