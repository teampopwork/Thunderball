#include "Ball.h"

#include <SexyAppFramework/SexyVector.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x00480de0
Ball::Ball(bool param_1)
{
}

// SYNTHETIC: POPCAPGAME1 0x0047f130
// Sexy::Ball::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x0047dae0
Ball::~Ball()
{
}

// STUB: POPCAPGAME1 0x00480400
bool Ball::EditGetSetValHook(std::string* param_1, bool param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x00483410
void Ball::SyncState(DataSync* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x004547a0
int Ball::GetClass()
{
	return 7;
}

// STUB: POPCAPGAME1 0x00474e60
void Ball::SetPos(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00474eb0
void Ball::Translate(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00475600
void Ball::SetVelocity(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x0047a450
void Ball::Update()
{
}

// STUB: POPCAPGAME1 0x0047a8d0
void Ball::UpdateSlowMo(float param_1)
{
}

// STUB: POPCAPGAME1 0x0047b0c0
void Ball::Draw(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x004838f0
void Ball::DrawShadow(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00477070
void Ball::AddedToGame()
{
}

// STUB: POPCAPGAME1 0x00474e40
SexyVector2 Ball::GetCenter()
{
	return SexyVector2(0.0f, 0.0f);
}

// STUB: POPCAPGAME1 0x0047df90
float Ball::GetXPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x004547b0
float Ball::GetYPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x00477a00
bool Ball::IsCollidableWith(PhysObj* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x00474dd0
void Ball::SetAbsPos(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00474fc0
void Ball::SyncBounds()
{
}

// STUB: POPCAPGAME1 0x004770b0
void Ball::SetRadius(float param_1)
{
}

// STUB: POPCAPGAME1 0x00474f00
void Ball::StartFireballSound()
{
}

// STUB: POPCAPGAME1 0x00474f70
void Ball::StopFireballSound()
{
}

// STUB: POPCAPGAME1 0x00474fb0
void Ball::SetFireballRadius()
{
}

// STUB: POPCAPGAME1 0x004770d0
void Ball::SetFireball(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00475200
void Ball::DoNonCollideUpdate()
{
}

// STUB: POPCAPGAME1 0x00477a60
void Ball::DrawHat(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00475000
bool Ball::CheckCollision(SexyVector2* param_1, SexyVector2* param_2, float param_3, float* param_4, SexyVector2* param_5)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047f4c0
bool Ball::CheckCollision(PhysObj* param_1, float param_2, float param_3)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047a350
void Ball::SetHoleOut(PhysObj* param_1, int param_2)
{
}

// STUB: POPCAPGAME1 0x00480f50
void Ball::SetHat(bool param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00477110
void Ball::DoBallBallCollision(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x00477340
void Ball::DoBallPegCollision(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x004775b0
void Ball::DoBallCollision(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x0047a3b0
bool Ball::CheckBallCollision(Ball* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x004775f0
void Ball::DoLineCollision(
	SexyVector2* param_1,
	PhysObj* param_2,
	SexyVector2* param_3,
	SexyVector2* param_4,
	SexyVector2* param_5,
	SexyVector2* param_6
)
{
}

// STUB: POPCAPGAME1 0x0047f160
void Ball::DoCollideUpdate(std::vector<PhysObj*>* param_1, SexyVector2* param_2)
{
}
