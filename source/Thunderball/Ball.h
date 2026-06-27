#ifndef __BALL_H__
#define __BALL_H__

#include "PhysObj.h"

#include <SexyAppFramework/SmartPtr.h>
#include <SexyAppFramework/Rect.h>
#include <SexyAppFramework/SexyVector.h>

#include <string>
#include <vector>

namespace Sexy
{

class SoundInstance;

// VTABLE: POPCAPGAME1 0x005f19b4
class Ball : public PhysObj {
public:
    static float mDefRadius;

    int mUnk0xe4; // +0xe4
    int mUnk0xe8; // +0xe8
    float mUnk0xec; // +0xec
    float mUnk0xf0; // +0xf0
    float mUnk0xf4; // +0xf4
    float mUnk0xf8; // +0xf8
    float mUnk0xfc; // +0xfc
    float mUnk0x100; // +0x100
    float mUnk0x104; // +0x104
    float mUnk0x108; // +0x108
    SexyVector2 mUnk0x10c[5];
    float mUnk0x134; // +0x134
    float mUnk0x138; // +0x138
    float mUnk0x13c; // +0x13c
    bool mUnk0x140; // +0x140
    bool mUnk0x141; // +0x141
    bool mUnk0x142; // +0x142
    bool mUnk0x143; // +0x143
    bool mUnk0x144; // +0x144
    bool mUnk0x145; // +0x145
    bool mUnk0x146; // +0x146
    int mUnk0x148; // +0x148
    int mUnk0x14c; // +0x14c
    int mUnk0x150; // +0x150
    int mUnk0x154; // +0x154
    int mUnk0x158; // +0x158
    SmartPtr<PhysObj> mUnk0x15c; // +0x15c
    bool mUnk0x160; // +0x160
    bool mUnk0x161; // +0x161
    bool mUnk0x162; // +0x162
    bool mUnk0x163; // +0x163
    bool mUnk0x164; // +0x164
    bool mUnk0x165; // +0x165
    SexyVector2 mUnk0x168; // +0x168
    float mUnk0x170; // +0x170
    float mUnk0x174; // +0x174
    int mUnk0x178; // +0x178
    int mUnk0x17c; // +0x17c
    int mUnk0x180; // +0x180
    SoundInstance* mUnk0x184; // +0x184
    SmartPtr<Ball> mUnk0x188; // +0x188
    bool mUnk0x18c; // +0x18c
    bool mUnk0x18d; // +0x18d

	Ball(bool param_1);
	virtual ~Ball();

	virtual bool EditGetSetValHook(std::string& param_1, bool param_2);
	virtual void SyncState(DataSync& theSync);
	virtual int GetClass();
	virtual void SetPos(float param_1, float param_2);
	virtual void Translate(float param_1, float param_2);
	virtual void SetVelocity(float param_1, float param_2);
    virtual void Update();
	virtual void UpdateSlowMo(float param_1);
	virtual void DrawShadow(Graphics* g);
	virtual void Draw(Graphics* g);
	virtual void AddedToGame();
	virtual SexyVector2 GetCenter();
	virtual float GetXPos();
	virtual float GetYPos();
	virtual bool IsCollidableWith(PhysObj* param_1);

	void SetAbsPos(float param_1, float param_2);
	void SyncBounds();
	void SetRadius(float param_1);
	void StartFireballSound();
	void StopFireballSound();
	void SetFireballRadius();
	void SetFireball(bool param_1);
	void DoNonCollideUpdate();
	void DrawHat(Graphics* g);
	bool CheckCollision(SexyVector2* param_1, SexyVector2* param_2, float param_3, float* param_4, SexyVector2* param_5);
	bool CheckCollision(PhysObj* param_1, float param_2, float param_3);
	void SetHoleOut(PhysObj* param_1, int param_2);
	void SetHat(bool param_1, bool param_2);
	void DoBallBallCollision(Ball* param_1);
	void DoBallPegCollision(Ball* param_1);
	void DoBallCollision(Ball* param_1);
	void CheckBallCollision(Ball* param_1);
	void DoLineCollision(
		SexyVector2* param_1,
		PhysObj* param_2,
		SexyVector2* param_3,
		SexyVector2* param_4,
		SexyVector2* param_5,
		SexyVector2* param_6
	);
	void DoCollideUpdate(std::vector<PhysObj*>* param_1, SexyVector2* param_2);
};

} // namespace Sexy

#endif // __BALL_H__
