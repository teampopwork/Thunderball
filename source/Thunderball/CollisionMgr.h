#ifndef __COLLISION_MGR_H__
#define __COLLISION_MGR_H__

#include <set>
#include <utility>
#include <vector>
#include "../SexyAppFramework/SmartPtr.h"

namespace Sexy
{
class Ball;
class PhysObj;
class SexyVector2;

struct CollisionPoint {
	PhysObj* mObject;
	float mValue1;
	float mValue2;
};

class CollisionMgr {
public:
	bool mUnk0x0;
	std::vector<CollisionPoint> mObjects1;
	std::vector<CollisionPoint> mObjects2;
	std::set<std::pair<PhysObj*, PhysObj*> > mCollisions;
	int mUnk0x30;
	int mUnk0x34;
	std::vector<int> mUnk0x38;
	std::vector<std::pair<RefCountPtr, RefCountPtr> > mUnk0x48;
	int mUnk0x58;
	int mUnk0x5C;
	int mUnk0x60;
	int mUnk0x64;
	std::vector<int> mUnk0x68;
	bool mUnk0x78;

	CollisionMgr();
	~CollisionMgr();

	void RemoveObj(PhysObj* param_1, std::vector<CollisionPoint>* param_2);
	void RemoveObj(PhysObj* param_1);
	void SortEndPoints(std::vector<CollisionPoint>* param_1);
	void Clear();
	void AddObj(PhysObj* param_1, float* param_2, float* param_3, std::vector<CollisionPoint>* param_4);
	void AddObj(PhysObj* param_1);
	void NotifyCollision(PhysObj* param_1, PhysObj* param_2);
	void Update(bool param_1);
	void BeginUpdateOneBall(Ball* param_1);
	void UpdateOneBall(Ball* param_1, SexyVector2* param_2);
};

} // namespace Sexy

#endif // __COLLISION_MGR_H__
