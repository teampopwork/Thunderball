#ifndef __EFFECT_MGR_H__
#define __EFFECT_MGR_H__

namespace Sexy
{
class PhysObj;
class Graphics;
class DataSync;
class SexyVector2;
enum EffectType;

class Effect {
public:
	int mUnk0xc;
};

class EffectMgr {
public:
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
	void SyncState(DataSync* param_1);

	Effect* GetEffectByType(EffectType param_1);
	void EraseAllOfType(EffectType param_1);
	void SetPriority(Effect* param_1, int param_2);
	void Draw(Graphics* param_1, int param_2);

	void FinishFeverRainbow();
	int ClampPriority(int param_1);
	int PriorityToList(int param_1);
	void SetCrackPoint(SexyVector2* param_1, int param_2, int param_3, int param_4);
	void SetPriority(Effect* param_1, int param_2, int param_3); // overload helper
};

} // namespace Sexy

#endif // __EFFECT_MGR_H__
