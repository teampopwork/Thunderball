#include "CollisionMgr.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0044d870
CollisionMgr::CollisionMgr() : mUnk0x30(0), mUnk0x34(0)
{
	mUnk0x0 = false;
	mUnk0x78 = false;
}

// FUNCTION: POPCAPGAME1 0x00423fa0
CollisionMgr::~CollisionMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00443660
void CollisionMgr::RemoveObj(PhysObj* param_1, std::vector<CollisionPoint>* param_2)
{
	int anIndex = 0;
	while (anIndex < (int)param_2->size())
	{
		if ((*param_2)[anIndex].mObject == param_1)
			param_2->erase(param_2->begin() + anIndex);
		else
			++anIndex;
	}
}

// FUNCTION: POPCAPGAME1 0x004465a0
void CollisionMgr::RemoveObj(PhysObj* param_1)
{
	RemoveObj(param_1, &mObjects1);
	RemoveObj(param_1, &mObjects2);
	std::set<std::pair<PhysObj*, PhysObj*> >::iterator anItr = mCollisions.begin();
	while (anItr != mCollisions.end())
	{
		if (anItr->first == param_1 || anItr->second == param_1)
			mCollisions.erase(anItr++);
		else
			++anItr;
	}
}

// STUB: POPCAPGAME1 0x0044b1e0
void CollisionMgr::SortEndPoints(std::vector<CollisionPoint>* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00446560
void CollisionMgr::Clear()
{
	mCollisions.clear();
	mObjects1.clear();
	mObjects2.clear();
}

// STUB: POPCAPGAME1 0x0044d920
void CollisionMgr::AddObj(PhysObj* param_1, float* param_2, float* param_3, std::vector<CollisionPoint>* param_4)
{
}

// STUB: POPCAPGAME1 0x0044d9d0
void CollisionMgr::AddObj(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0045ad30
void CollisionMgr::NotifyCollision(PhysObj* param_1, PhysObj* param_2)
{
}

// STUB: POPCAPGAME1 0x0045add0
void CollisionMgr::Update(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00454dc0
void CollisionMgr::BeginUpdateOneBall(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x00454f90
void CollisionMgr::UpdateOneBall(Ball* param_1, SexyVector2* param_2)
{
}
