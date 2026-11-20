#include "CollisionMgr.h"

#include "Ball.h"
#include "Hole.h"
#include "PhysObj.h"

#include <algorithm>
#include <cstddef>

using namespace Sexy;

// TEMPLATE: POPCAPGAME1 0x004baa10
// std::_Tree<std::_Tmap_traits<int,Sexy::MemoryImage *,std::greater<int>,std::allocator<std::pair<int const ,Sexy::MemoryImage *> >,1> >::_Buynode(void)

// FUNCTION: POPCAPGAME1 0x0044d870
CollisionMgr::CollisionMgr() : mUnk0x30(0), mUnk0x34(0)
{
	mUnk0x0 = false;
	mUnk0x78 = false;
}

// TEMPLATE: POPCAPGAME1 0x0041feb0
// std::vector<std::pair<Sexy::SmartPtr<Sexy::RefCount>,Sexy::SmartPtr<Sexy::RefCount> >,std::allocator<std::pair<Sexy::SmartPtr<Sexy::RefCount>,Sexy::SmartPtr<Sexy::RefCount> > > >::_Tidy

// TEMPLATE: POPCAPGAME1 0x00408ec0
// std::pair<Sexy::SmartPtr<Sexy::RefCount>,Sexy::SmartPtr<Sexy::RefCount> >::~pair<Sexy::SmartPtr<Sexy::RefCount>,Sexy::SmartPtr<Sexy::RefCount> >

// FUNCTION: POPCAPGAME1 0x00423fa0
CollisionMgr::~CollisionMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00443660
void CollisionMgr::RemoveObj(PhysObj* param_1, std::vector<EndPoint>* param_2)
{
	int anIndex = 0;
	while (anIndex < (int) param_2->size()) {
		if ((*param_2)[anIndex].mObject == param_1) {
			param_2->erase(param_2->begin() + anIndex);
		}
		else {
			++anIndex;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004465a0
void CollisionMgr::RemoveObj(PhysObj* param_1)
{
	RemoveObj(param_1, &mObjects1);
	RemoveObj(param_1, &mObjects2);
	std::set<std::pair<PhysObj*, PhysObj*>>::iterator anItr = mCollisions.begin();
	while (anItr != mCollisions.end()) {
		if (anItr->first == param_1 || anItr->second == param_1) {
			mCollisions.erase(anItr++);
		}
		else {
			++anItr;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0044b1e0
void CollisionMgr::SortEndPoints(std::vector<EndPoint>* param_1)
{
	if (param_1 == NULL || param_1->empty()) {
		return;
	}

	for (int i = 0; i < (int)param_1->size(); ++i) {
		int j = i;
		while (j > 0 && (*param_1)[j].mValue1 < (*param_1)[j - 1].mValue1) {
			EndPoint& aEndPoint1 = (*param_1)[j];
			EndPoint& aEndPoint2 = (*param_1)[j - 1];
			
			if (!aEndPoint2.mValue2 && aEndPoint1.mValue2) {
				PhysObj* aPhysObj1 = aEndPoint2.mObject;
				PhysObj* aPhysObj2 = aEndPoint1.mObject;

				if (aPhysObj1->mUnk0x10 == 2 && aPhysObj2->mUnk0x10 == 2) {
					if (aPhysObj1->mCurSortId < aPhysObj2->mCurSortId) {
						mCollisions.erase(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj1, aPhysObj2));
					}
					else {
						mCollisions.erase(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj2, aPhysObj1));
					}
				} else if (aPhysObj1->mUnk0x10 == 2) {
					mCollisions.erase(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj1, aPhysObj2));
				} else if (aPhysObj2->mUnk0x10 == 2) {
					mCollisions.erase(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj2, aPhysObj1));
				}
			} else if (aEndPoint2.mValue2 && !aEndPoint1.mValue2) {
				PhysObj* aPhysObj1 = aEndPoint2.mObject;
				PhysObj* aPhysObj2 = aEndPoint1.mObject;

				Ball* aBall = (aPhysObj1->mUnk0x10 == 2) ? static_cast<Ball*>(aPhysObj1) : NULL;
                PhysObj* aOtherPhysObj = (aPhysObj1->mUnk0x10 == 2) ? aPhysObj2 : aPhysObj1;

                if (aBall != NULL && aBall->FUN_004326e0(aOtherPhysObj)) {
                    if (aPhysObj1->mUnk0x10 == 2 && aPhysObj2->mUnk0x10 == 2) {
                        if (aPhysObj1->mCurSortId < aPhysObj2->mCurSortId) {
                            mCollisions.insert(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj1, aPhysObj2));
                        } else {
                            mCollisions.insert(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj2, aPhysObj1));
                        }
                    } else {
                        mCollisions.insert(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(aPhysObj1, aPhysObj2));
                    }
                }
			}

			EndPoint aTemp = aEndPoint1;
            aEndPoint1 = aEndPoint2;
            aEndPoint2 = aTemp;

			--j;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00446560
void CollisionMgr::Clear()
{
	mCollisions.clear();
	mObjects1.clear();
	mObjects2.clear();
}

// TEMPLATE: POPCAPGAME1 0x0043f7c0
// std::_Lower_bound<Sexy::CollisionMgr::EndPoint *,Sexy::CollisionMgr::EndPoint,int>

// TEMPLATE: POPCAPGAME1 0x004b0ca0
// std::vector<Sexy::CollisionMgr::EndPoint,std::allocator<Sexy::CollisionMgr::EndPoint> >::insert

// FUNCTION: POPCAPGAME1 0x0044d920
void CollisionMgr::AddObj(PhysObj* param_1, float param_2, float param_3, std::vector<EndPoint>* param_4)
{
	EndPoint aEndPoint1;
	aEndPoint1.mObject = param_1;
	aEndPoint1.mValue1 = param_2;
	aEndPoint1.mValue2 = true;

	EndPoint aEndPoint2;
	aEndPoint2.mObject = param_1;
	aEndPoint2.mValue1 = param_3;
	aEndPoint2.mValue2 = false;

	std::vector<EndPoint>::iterator anItr;

	anItr = std::lower_bound(param_4->begin(), param_4->end(), aEndPoint1);
	param_4->insert(anItr, aEndPoint1);
	anItr = std::lower_bound(param_4->begin(), param_4->end(), aEndPoint2);
	param_4->insert(anItr, aEndPoint2);
}

// FUNCTION: POPCAPGAME1 0x0044d9d0
void CollisionMgr::AddObj(PhysObj* param_1)
{
	for (std::vector<EndPoint>::iterator anItr = mObjects1.begin(); anItr != mObjects1.end(); ++anItr) {
		if (anItr->mObject != NULL) {
			PhysObj* aPhysObj = anItr->mObject;
			if (param_1->mUnk0x10 == 2) {
				if (aPhysObj->mUnk0x10 != 2 || static_cast<Ball*>(aPhysObj)->mUnk0x163 && static_cast<Ball*>(param_1)->mUnk0x163 && param_1->FUN_004326e0(aPhysObj)) {
					std::vector<std::pair<PhysObj*, PhysObj*>>::value_type aPair;
					if (aPhysObj->mUnk0x10 == 2) {
						if (param_1->mCurSortId < aPhysObj->mCurSortId) {
							aPair.first = param_1;
							aPair.second = aPhysObj;
						}
						else {
							aPair.first = aPhysObj;
							aPair.second = param_1;
						}
					}
					else {
						aPair.first = param_1;
						aPair.second = aPhysObj;
					}
					mCollisions.insert(aPair);
				}
			}
			else if (aPhysObj->mUnk0x10 == 2 && param_1->FUN_004326e0(aPhysObj)) {
				mCollisions.insert(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(param_1, aPhysObj));
			}
		}
	}

	AddObj(param_1, param_1->mUnk0x14, param_1->mUnk0x18, &mObjects1);
	AddObj(param_1, param_1->mUnk0x18, param_1->mUnk0x20, &mObjects2);
}

// FUNCTION: POPCAPGAME1 0x0045ad30
void CollisionMgr::NotifyCollision(PhysObj* param_1, PhysObj* param_2)
{
	if (param_1->mUnk0x10 == 2 || param_2->mUnk0x10 == 2) {
		if (param_1->mUnk0x10 == 2) {
			mUnk0x48.push_back(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(param_1, param_2));
		}
		else {
			mUnk0x48.push_back(std::vector<std::pair<PhysObj*, PhysObj*>>::value_type(param_2, param_1));
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0045add0
void CollisionMgr::Update(bool param_1)
{
	mUnk0x38.resize(0);
	if (param_1) {
		PhysObj::mNotifyCollisionFunc = NULL;
		PhysObj::mNotifyCollisionData = NULL;
		mUnk0x48.clear();
	}

	SortEndPoints(&mObjects1);
	SortEndPoints(&mObjects2);

	Ball* aBall = NULL;
	for (std::set<std::pair<PhysObj*, PhysObj*>>::iterator anItr = mCollisions.begin(); anItr != mCollisions.end(); ++anItr) {
		PhysObj* aPhysObj1 = anItr->first;
		PhysObj* aPhysObj2 = anItr->second;

		aBall = static_cast<Ball*>(aPhysObj1);

		if (aBall != NULL && aBall != mUnk0x34) {
			aBall->DoCollideUpdate(&mUnk0x38, NULL);
			mUnk0x38.clear();
		}
		mUnk0x34 = aBall;

		if (!aPhysObj1->IsCollidableWith(aPhysObj2)) {
			continue;
		}

		switch (aPhysObj2->mUnk0x10) {
		case 1:
			static_cast<Hole*>(aPhysObj2)->CheckCollision(aBall);
			break;
		case 2:
			static_cast<Ball*>(aPhysObj2)->CheckBallCollision(aBall);
			break;
		case 3:
		case 4:
		case 5:
			mUnk0x38.push_back(aPhysObj2);
			break;
		default:
			break;
		}
	}

	if (aBall != NULL) {
		aBall->DoCollideUpdate(&mUnk0x38, NULL);
		mUnk0x38.clear();
	}

	PhysObj::mNotifyCollisionFunc = NULL;
}

// STUB: POPCAPGAME1 0x00454dc0
void CollisionMgr::BeginUpdateOneBall(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x00454f90
void CollisionMgr::UpdateOneBall(Ball* param_1, SexyVector2* param_2)
{
}
