#ifndef __EFFECT_MGR_H__
#define __EFFECT_MGR_H__

#include <SexyAppFramework/SmartPtr.h>

#include <list>

namespace Sexy
{
class PhysObj;
class Graphics;
class Image;
class DataSync;
class SexyVector2;
enum EffectType;

class Effect {
public:
	int mUnk0x4;
	EffectType mType;
	int mUnk0xc;
	int mUnk0x10;
	float mUnk0x14;
	float mUnk0x18;
	int mUnk0x1c;
	int mUnk0x20;
	int mUnk0x24;
	float mUnk0x28;
	float mUnk0x2c;
	int mUnk0x30;
	int mUnk0x34;
	int mUnk0x38;
	int mUnk0x3c;
	bool mUnk0x40;
	Image* mUnk0x44;
	Image* mUnk0x48;
	RefCountPtr mUnk0x4c;
	RefCountPtr mUnk0x50;
	RefCountPtr mUnk0x54;

	Effect();
	Effect(const Effect& param_1);
	virtual ~Effect();
};

class EffectMgr {
public:
	std::list<Effect> mEffects[5];

	EffectMgr();
	virtual ~EffectMgr();

	void Clear();
	Effect* AddEffect(EffectType param_1, float param_2, float param_3, int param_4, bool param_5);
	Effect* AddLevelBumper(PhysObj* param_1);
	Effect* AddSpookyBallWrap(float param_1, float param_2, float param_3, float param_4);
	Effect* AddSpookyBall(float param_1, float param_2, bool param_3);
	Effect* AddStyleSpin(float param_1, float param_2);
	Effect* AddJimmy(bool param_1, int param_2, int param_3);
	Effect* AddCatcherGlow(int param_1, bool param_2);
	Effect* AddPyramid(float param_1, float param_2, bool param_3);
	Effect* AddFeverRainbow(int param_1);
	Effect* AddRay(float param_1, float param_2);
	Effect* AddFeverHoleEffect(float param_1, float param_2, int param_3);
	Effect* AddSpaceBlast(float param_1, float param_2, int param_3);
	Effect* AddZenPowerup(float param_1, float param_2);
	Effect* AddCannonBlast(float param_1, float param_2, float param_3);
	Effect* AddFeverPointsBlast(float param_1, float param_2);
	Effect* AddFeverBlast(float param_1, float param_2);
	Effect* AddFeverScoreText();
	Effect* AddBubble(float param_1, float param_2);
	Effect* AddFlowerSparkles(float param_1, float param_2);
	Effect* AddCoinFlip(float param_1, float param_2, bool param_3);
	Effect* AddMasterBadge(float param_1, float param_2, int param_3);
	Effect* AddRibbon(float param_1, float param_2, int param_3);
	Effect* AddExtremeFever(float param_1, float param_2, bool param_3, int param_4);

	void Update(bool param_1);
	void UpdateSlowMo(float param_1);
	void SyncState(DataSync& param_1);

	Effect* GetEffectByType(EffectType param_1);
	int EraseAllOfType(EffectType param_1);
	Effect* SetPriority(Effect* param_1, int param_2);
	void Draw(Graphics* param_1, int param_2);

	void FinishFeverRainbow();
	int ClampPriority(int param_1);
	int PriorityToList(int param_1);
	void SetCrackPoint(SexyVector2* param_1, int param_2, int param_3, int param_4);
};

} // namespace Sexy

#endif // __EFFECT_MGR_H__
