#ifndef __COLLISION_MGR_H__
#define __COLLISION_MGR_H__

#include <vector>

namespace Sexy
{
class Ball;
class PhysObj;
class SexyVector2;

class CollisionMgr {
public:
	CollisionMgr();
	virtual ~CollisionMgr();

	void RemoveObj(PhysObj* param_1, std::vector<PhysObj*>* param_2);
	void RemoveObj(PhysObj* param_1);
	void SortEndPoints(std::vector<PhysObj*>* param_1);
	void Clear();
	void AddObj(PhysObj* param_1, float* param_2, float* param_3, std::vector<PhysObj*>* param_4);
	void AddObj(PhysObj* param_1);
	void NotifyCollision(PhysObj* param_1, PhysObj* param_2);
	void Update(bool param_1);
	void BeginUpdateOneBall(Ball* param_1);
	void UpdateOneBall(Ball* param_1, SexyVector2* param_2);
};

} // namespace Sexy

#endif // __COLLISION_MGR_H__
