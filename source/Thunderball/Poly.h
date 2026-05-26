#ifndef __POLY_H__
#define __POLY_H__

#include "Line.h"
#include "PhysObj.h"

#include <string>
#include <vector>

namespace Sexy
{

class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1f4c
class Poly : public PhysObj {
public:
	std::vector<SexyVector2*> mUnk0xe8;    // +0xe4
	std::vector<SexyVector2*> mUnk0xf8;    // +0xf8
	std::vector<SmartPtr<Line>> mUnk0x108; // +0x108
	float mUnk0x114;                       // +0x114
	float mUnk0x118;                       // +0x118
	float mUnk0x11c;                       // +0x11c
	float mUnk0x120;                       // +0x120
	float mUnk0x124;                       // +0x124
	float mUnk0x128;                       // +0x128
	bool mUnk0x12c;                        // +0x12c
	bool mUnk0x12d;                        // +0x12d
	bool mUnk0x12e;                        // +0x12e
	bool mUnk0x12f;                        // +0x12f
	bool mUnk0x130;                        // +0x130
	int mUnk0x134;                         // +0x134
	int mUnk0x138;                         // +0x138
	int mUnk0x13c;                         // +0x13c
	int mUnk0x140;                         // +0x140
	bool mUnk0x144;                        // +0x144
	bool mUnk0x145;                        // +0x145
	bool mUnk0x146;                        // +0x146

	Poly();
	virtual ~Poly();

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
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
