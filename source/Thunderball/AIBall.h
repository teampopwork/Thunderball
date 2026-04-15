#ifndef __AIBALL_H__
#define __AIBALL_H__

#include "Ball.h"

#include <vector>

namespace Sexy
{

// VTABLE: POPCAPGAME1 0x005e7a54
class AIBall : public Ball {
public:
	AIBall();
	virtual ~AIBall();

	virtual void Update();
	virtual void NotifyCollision(PhysObj* param_1);
	virtual bool IsCollidableWith(PhysObj* param_1);

	void DoExploder(PhysObj* param_1);
	void DoTimeBomb();
	void DoFeverTron(PhysObj* param_1);
	void CopyAttributes(AIBall* param_1);
	void DoMultiball(PhysObj* param_1);
	void SyncObjects(DataSync* param_1, std::vector<PhysObj*>* param_2);
};

} // namespace Sexy

#endif // __AIBALL_H__
