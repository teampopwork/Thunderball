#ifndef __BALL_H__
#define __BALL_H__

#include "PhysObj.h"

#include <string>
#include <vector>

namespace Sexy
{

class SexyVector2;

class Ball : public PhysObj {
public:
	Ball(bool param_1);
	virtual ~Ball();

	virtual bool EditGetSetValHook(std::string* param_1, bool param_2);
	virtual void SyncState(DataSync* param_1);
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
	bool CheckBallCollision(Ball* param_1);
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
