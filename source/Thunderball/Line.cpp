#include "Line.h"

#include <SexyAppFramework/SexyVector.h>

#include <math.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x00481440
Line::Line()
{
}

// STUB: POPCAPGAME1 0x00481480
Line::Line(float param_1, float param_2, float param_3, float param_4)
{
}

// SYNTHETIC: POPCAPGAME1 0x0047f5a0
// Sexy::Line::`scalar destroying destructor'

// STUB: POPCAPGAME1 0x0047df70
Line::~Line()
{
}

// STUB: POPCAPGAME1 0x004814f0
void Line::SyncState(DataSync* sync)
{
}

// FUNCTION: POPCAPGAME1 0x0047df80
int Line::GetClass()
{
	return 2;
}

// STUB: POPCAPGAME1 0x00476190
void Line::EditDrawOutline(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x000476310
void Line::EditDrawPoints(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00478db0
bool Line::EditContains(float param_1, float param_2, bool param_3)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478be0
void Line::EditGetDragMode(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00478ca0
void Line::EditDoPointDrag(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00478d10
void Line::EditReflect(float param_1, float param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00478440
void Line::SetPos(float theX, float theY)
{
}

// STUB: POPCAPGAME1 0x00475620
void Line::Translate(float theDx, float theDy)
{
}

// STUB: POPCAPGAME1 0x00475600
void Line::SetVelocity(float theVx, float theVy)
{
}

// STUB: POPCAPGAME1 0x00476390
void Line::Draw(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x005f1abc
float Line::GetXPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x0047dfa0
float Line::GetYPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x004782f0
void Line::Init(float param_1, float param_2, float param_3, float param_4)
{
}

// STUB: POPCAPGAME1 0x00476010
bool Line::IsPartlyInsideRect(Rect* theRect)
{
	return false;
}

// FUNCTION: POPCAPGAME1 0x00476380
bool Line::EditIntersects(Rect* theRect)
{
	return IsPartlyInsideRect(theRect);
}

// STUB: POPCAPGAME1 0x00475660
void Line::CalcEdgeHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
}

// STUB: POPCAPGAME1 0x00475660
void Line::CalcVertexHitVelocity(SexyVector2* param_1, SexyVector2* param_2)
{
}

// STUB: POPCAPGAME1 0x00475bd0
bool Line::CircleIntersect(float param_1, float param_2, float param_3, SexyVector2* param_4, SexyVector2* param_5)
{
	return false;
}

// STUB: POPCAPGAME1 0x00475890
bool Line::CheckEdgeTimeCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	SexyVector2* param_4,
	SexyVector2* param_5,
	SexyVector2* hitNormal,
	float* hitTime
)
{
	return false;
}

// STUB: POPCAPGAME1 0x004756c0
bool Line::CheckVertexTimeCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	float* param_4,
	SexyVector2* param_5,
	float param_6,
	float param_7,
	SexyVector2* param_8,
	SexyVector2* param_9
)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478500
bool Line::CheckPenetration(
	SexyVector2* param_1,
	float param_2,
	SexyVector2* param_3,
	SexyVector2* param_4,
	SexyVector2* param_5
)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478940
bool Line::CheckCollision(
	SexyVector2* param_1,
	SexyVector2* param_2,
	float param_3,
	float* param_4,
	SexyVector2* param_5,
	SexyVector2* param_6,
	SexyVector2* param_7,
	bool param_8
)
{
	return false;
}

// STUB: POPCAPGAME1 0x00478ac0
float Line::GetDistanceFromPoint(float param_1, float param_2)
{
	return 0.0f;
}

