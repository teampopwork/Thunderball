#ifndef __LINE_H__
#define __LINE_H__

#include "PhysObj.h"

#include <SexyAppFramework/Rect.h>

namespace Sexy
{

class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1a44
class Line : public PhysObj {
public:
	Line();
	Line(float param_1, float param_2, float param_3, float param_4);
	virtual ~Line();

	virtual void SyncState(DataSync* sync);
	virtual int GetClass();
	virtual void EditDrawOutline(Graphics* g);
	virtual void EditDrawPoints(Graphics* g);
	virtual bool EditContains(float param_1, float param_2, bool param_3);
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditReflect(float param_1, float param_2, bool param_3);
	virtual void SetPos(float theX, float theY);
	virtual void Translate(float theDx, float theDy);
	virtual void SetVelocity(float theVx, float theVy);
	virtual void Draw(Graphics* g);
	virtual float GetXPos();
	virtual float GetYPos();

	void Init(float param_1, float param_2, float param_3, float param_4);

	bool IsPartlyInsideRect(Rect* theRect);
	bool EditIntersects(Rect* theRect);
	void CalcEdgeHitVelocity(SexyVector2* param_1, SexyVector2* param_2);
	void CalcVertexHitVelocity(SexyVector2* param_1, SexyVector2* param_2);
	bool CircleIntersect(float param_1, float param_2, float param_3, SexyVector2* param_4, SexyVector2* param_5);
	bool CheckEdgeTimeCollision(
		SexyVector2* param_1,
		SexyVector2* param_2,
		float param_3,
		SexyVector2* param_4,
		SexyVector2* param_5,
		SexyVector2* hitNormal,
		float* hitTime
	);
	bool CheckVertexTimeCollision(
		SexyVector2* param_1,
		SexyVector2* param_2,
		float param_3,
		float* param_4,
		SexyVector2* param_5,
		float param_6,
		float param_7,
		SexyVector2* param_8,
		SexyVector2* param_9
	);
	bool CheckPenetration(
		SexyVector2* param_1,
		float param_2,
		SexyVector2* param_3,
		SexyVector2* param_4,
		SexyVector2* param_5
	);
	bool CheckCollision(
		SexyVector2* param_1,
		SexyVector2* param_2,
		float param_3,
		float* param_4,
		SexyVector2* param_5,
		SexyVector2* param_6,
		SexyVector2* param_7,
		bool param_8
	);
	float GetDistanceFromPoint(float param_1, float param_2);
};

} // namespace Sexy

#endif // __LINE_H__
