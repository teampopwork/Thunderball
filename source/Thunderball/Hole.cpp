#include "Hole.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004810e0
Hole::Hole()
{
    mUnk0xe4 = 0;
    mUnk0xf4 = 0.0f;
    mUnk0xf8 = 0.0f;
    mUnk0xfc = 0.0f;
    mUnk0x100 = 0.0f;
    mUnk0x10 = 1;
    mUnk0xec = 0;
    mUnk0x10c = false;
    mUnk0xf0 = 0;
    mUnk0xe8 = 0;
    SetSize(100, 0x14);
}

// SYNTHETIC: POPCAPGAME1 0x004811e0
// Sexy::Hole::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00481160
Hole::~Hole()
{
}

// STUB: POPCAPGAME1 0x00480530
bool Hole::EditGetSetValHook(std::string* param_1, bool param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x00481210
void Hole::SyncState(DataSync* param_1)
{
}

// STUB: POPCAPGAME1 0x00481140
int Hole::GetClass()
{
	return 8;
}

// STUB: POPCAPGAME1 0x00478110
void Hole::EditDrawOutline(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00475540
void Hole::SetPos(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x004754f0
void Hole::Translate(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00475600
void Hole::SetVelocity(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x0047a930
void Hole::Update()
{
}

// STUB: POPCAPGAME1 0x0047ce60
void Hole::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x0047a230
void Hole::DrawLight(Graphics* g)
{
    PhysObj::DrawLight(g);
}

// STUB: POPCAPGAME1 0x0047dfa0
float Hole::GetXPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x00481150
float Hole::GetYPos()
{
	return 0.0f;
}

// FUNCTION: POPCAPGAME1 0x00475580
void Hole::SetSize(int param_1, int param_2)
{
    mUnk0x104 = param_1;
    mUnk0x108 = param_2;
    mUnk0x14 = mUnk0xf4 - (float)param_1 * 0.5;
    mUnk0x1c = (float)(int)param_1 * 0.5 + mUnk0xf4;
    mUnk0x18 = mUnk0xf8 - (float)param_2 * 0.5;
    mUnk0x20 = (float)(int)param_2 * 0.5 + mUnk0xf8;
}

// STUB: POPCAPGAME1 0x004755f0
void Hole::SetFlashCount(int param_1)
{
}

// STUB: POPCAPGAME1 0x004781c0
bool Hole::CheckCollision(Ball* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047cac0
void Hole::DrawHole(Graphics* g, int param_2, int param_3)
{
}
