#include "EffectMgr.h"

#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/ModVal.h>

#include "ThunderCommon.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0043e540
Effect::Effect()
{
	mUnk0x44 = NULL;
	mUnk0x48 = NULL;
}

// FUNCTION: POPCAPGAME1 0x00440100
Effect::Effect(const Effect& param_1)
{
	mType = param_1.mType;
	mUnk0xc = param_1.mUnk0xc;
	mUnk0x10 = param_1.mUnk0x10;
	mUnk0x14 = param_1.mUnk0x14;
	mUnk0x18 = param_1.mUnk0x18;
	mUnk0x1c = param_1.mUnk0x1c;
	mUnk0x20 = param_1.mUnk0x20;
	mUnk0x24 = param_1.mUnk0x24;
	mUnk0x28 = param_1.mUnk0x28;
	mUnk0x2c = param_1.mUnk0x2c;
	mUnk0x30 = param_1.mUnk0x30;
	mUnk0x34 = param_1.mUnk0x34;
	mUnk0x4 = param_1.mUnk0x4;
	mUnk0x38 = param_1.mUnk0x38;
	mUnk0x3c = param_1.mUnk0x3c;
	mUnk0x40 = param_1.mUnk0x40;
	mUnk0x4c = param_1.mUnk0x4c;
	mUnk0x50 = param_1.mUnk0x50;
	mUnk0x54 = param_1.mUnk0x54;
	mUnk0x44 = NULL;
	mUnk0x48 = NULL;
}

// FUNCTION: POPCAPGAME1 0x00439bd0
Effect::~Effect()
{
	delete mUnk0x44;
	delete mUnk0x48;
}

// FUNCTION: POPCAPGAME1 0x004471e0
EffectMgr::EffectMgr()
{
}

// SYNTHETIC: POPCAPGAME1 0x0044b550
// Sexy::EffectMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00447210
EffectMgr::~EffectMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00443720
void EffectMgr::Clear()
{
	for (int i = 0; i < 5; ++i) {
		mEffects[i].clear();
	}
}

// FUNCTION: POPCAPGAME1 0x0044de40
Effect* EffectMgr::AddEffect(EffectType param_1, float param_2, float param_3, int param_4, bool param_5)
{
	int priority = ClampPriority(param_4);
	std::list<Effect>& effects = mEffects[PriorityToList(priority)];
	std::list<Effect>::iterator position = param_5 ? effects.begin() : effects.end();
	std::list<Effect>::iterator it = effects.insert(position, Effect());
	Effect* effect = &*it;
	effect->mUnk0x14 = param_2;
	effect->mType = param_1;
	effect->mUnk0x18 = param_3;
	effect->mUnk0x4 = priority;
	effect->mUnk0x10 = 100;
	return effect;
}

// STUB: POPCAPGAME1 0x0045bc60
Effect* EffectMgr::AddLevelBumper(PhysObj* param_1)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x004514d0
Effect* EffectMgr::AddSpookyBallWrap(float param_1, float param_2, float param_3, float param_4)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00451310
Effect* EffectMgr::AddSpookyBall(float param_1, float param_2, bool param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00451140
Effect* EffectMgr::AddStyleSpin(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00450ff0
Effect* EffectMgr::AddJimmy(bool param_1, int param_2, int param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00450d30
Effect* EffectMgr::AddCatcherGlow(int param_1, bool param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00450c60
Effect* EffectMgr::AddPyramid(float param_1, float param_2, bool param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00450940
Effect* EffectMgr::AddFeverRainbow(int param_1)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044fd20
Effect* EffectMgr::AddRay(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044fe00
Effect* EffectMgr::AddFeverHoleEffect(float param_1, float param_2, int param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044fa20
Effect* EffectMgr::AddSpaceBlast(float param_1, float param_2, int param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044f830
Effect* EffectMgr::AddZenPowerup(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044efe0
Effect* EffectMgr::AddCannonBlast(float param_1, float param_2, float param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044ec30
Effect* EffectMgr::AddFeverPointsBlast(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044e880
Effect* EffectMgr::AddFeverBlast(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044e7f0
Effect* EffectMgr::AddFeverScoreText()
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044e740
Effect* EffectMgr::AddBubble(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044e010
Effect* EffectMgr::AddFlowerSparkles(float param_1, float param_2)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044dfc0
Effect* EffectMgr::AddCoinFlip(float param_1, float param_2, bool param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044df70
Effect* EffectMgr::AddMasterBadge(float param_1, float param_2, int param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044df20
Effect* EffectMgr::AddRibbon(float param_1, float param_2, int param_3)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0044e1c0
Effect* EffectMgr::AddExtremeFever(float param_1, float param_2, bool param_3, int param_4)
{
	return NULL;
}

// STUB: POPCAPGAME1 0x0045bf10
void EffectMgr::Update(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0045bfb0
void EffectMgr::UpdateSlowMo(float param_1)
{
}

// STUB: POPCAPGAME1 0x00457340
void EffectMgr::SyncState(DataSync& param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00441650
Effect* EffectMgr::GetEffectByType(EffectType param_1)
{
	for (int i = 0; i < 5; ++i) {
		for (std::list<Effect>::iterator it = mEffects[i].begin(); it != mEffects[i].end(); ++it) {
			if (it->mType == param_1) {
				return &*it;
			}
		}
	}
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x00443780
int EffectMgr::EraseAllOfType(EffectType param_1)
{
	int count = 0;
	for (int i = 0; i < 5; ++i) {
		std::list<Effect>::iterator it = mEffects[i].begin();
		while (it != mEffects[i].end()) {
			if (it->mType == param_1) {
				++count;
				it = mEffects[i].erase(it);
			} else {
				++it;
			}
		}
	}
	return count;
}

// FUNCTION: POPCAPGAME1 0x0044dd30
Effect* EffectMgr::SetPriority(Effect* param_1, int param_2)
{
	int priority = ClampPriority(param_2);
	int oldPriority = ClampPriority(param_1->mUnk0x4);
	if (oldPriority == priority) {
		return param_1;
	}

	std::list<Effect>& oldEffects = mEffects[PriorityToList(oldPriority)];
	std::list<Effect>& newEffects = mEffects[PriorityToList(priority)];
	std::list<Effect>::iterator inserted = newEffects.insert(newEffects.end(), *param_1);
	Effect* effect = &*inserted;
	effect->mUnk0x4 = priority;

	for (std::list<Effect>::iterator it = oldEffects.begin(); it != oldEffects.end(); ++it) {
		if (&*it == param_1) {
			oldEffects.erase(it);
			break;
		}
	}
	return effect;
}

// STUB: POPCAPGAME1 0x004573b0
void EffectMgr::Draw(Graphics* param_1, int param_2)
{
}

// FUNCTION: POPCAPGAME1 0x004415c0
void EffectMgr::FinishFeverRainbow()
{
	int duration = ModVal(
		0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\EffectMgr.cpp880,4400", 60);
	for (int i = 0; i < 5; ++i) {
		for (std::list<Effect>::iterator it = mEffects[i].begin(); it != mEffects[i].end(); ++it) {
			if (it->mType == (EffectType)0x18) {
				it->mUnk0x10 = it->mUnk0xc + 100;
			} else if (it->mType == (EffectType)0x26) {
				it->mUnk0x10 = it->mUnk0xc + 80;
			} else if (it->mType == (EffectType)0x15) {
				it->mUnk0x10 = it->mUnk0xc + duration;
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0043bc60
int EffectMgr::ClampPriority(int param_1)
{
	if (param_1 < -1) {
		return -1;
	}
	if (param_1 > 3) {
		return 3;
	}
	return param_1;
}

// FUNCTION: POPCAPGAME1 0x004363c0
int EffectMgr::PriorityToList(int param_1)
{
	return param_1 + 1;
}

// STUB: POPCAPGAME1 0x00433850
void EffectMgr::SetCrackPoint(SexyVector2* param_1, int param_2, int param_3, int param_4)
{
}

