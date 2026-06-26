#ifndef __HOLE_H__
#define __HOLE_H__

#include "PhysObj.h"

#include <string>

namespace Sexy
{

class Ball;

// VTABLE: POPCAPGAME1 0x005f1ebc
class Hole : public PhysObj {
public:
    int mUnk0xe4; // +0xe4
    int mUnk0xe8; // +0xe8
    int mUnk0xec; // +0xec
    int mUnk0xf0; // +0xf0
    float mUnk0xf4; // +0xf4
    float mUnk0xf8; // +0xf8
    float mUnk0xfc; // +0xfc
    float mUnk0x100; // +0x100
    int mUnk0x104; // +0x104
    int mUnk0x108; // +0x108
    bool mUnk0x10c; // +0x10c

	Hole();
	virtual ~Hole();

	virtual bool EditGetSetValHook(std::string* param_1, bool param_2);
	virtual void SyncState(DataSync& param_1);
	virtual int GetClass();
	virtual void EditDrawOutline(Graphics* g);
	virtual void SetPos(float param_1, float param_2);
	virtual void Translate(float param_1, float param_2);
	virtual void SetVelocity(float param_1, float param_2);
	virtual void Update();
	virtual void Draw(Graphics* g);
	virtual void DrawLight(Graphics* g);
	virtual float GetXPos();
	virtual float GetYPos();

	void SetSize(int param_1, int param_2);
	void SetFlashCount(int param_1);
	bool CheckCollision(Ball* param_1);
	void DrawHole(Graphics* g, int param_2, int param_3);
};

} // namespace Sexy

#endif // __HOLE_H__
