#ifndef __EFFECT_MGR_H__
#define __EFFECT_MGR_H__

namespace Sexy
{
class Effect;
class PhysObj;
class Graphics;
class DataSync;
class SexyVector2;
enum EffectType;

class EffectMgr {
public:
	EffectMgr();
	virtual ~EffectMgr();

	void Clear();
	void AddEffect(EffectType param_1, float param_2, float param_3, int param_4, bool param_5);
	void AddLevelBumper(PhysObj* param_1);
	void AddSpookyBallWrap(float param_1, float param_2, float param_3, float param_4);
	void AddSpookyBall(float param_1, float param_2, bool param_3);
	void AddStyleSpin(float param_1, float param_2);
	void AddJimmy(bool param_1, int param_2, int param_3);
	void AddCatcherGlow(int param_1, bool param_2);
	void AddPyramid(float param_1, float param_2, bool param_3);
	void AddFeverRainbow(int param_1);
	void AddRay(float param_1, float param_2);
	void AddFeverHoleEffect(float param_1, float param_2, int param_3);
	void AddSpaceBlast(float param_1, float param_2, int param_3);
	void AddZenPowerup(float param_1, float param_2);
	void AddCannonBlast(float param_1, float param_2, float param_3);
	void AddFeverPointsBlast(float param_1, float param_2);
	void AddFeverBlast(float param_1, float param_2);
	void AddFeverScoreText();
	void AddBubble(float param_1, float param_2);
	void AddFlowerSparkles(float param_1, float param_2);
	void AddCoinFlip(float param_1, float param_2, bool param_3);
	void AddMasterBadge(float param_1, float param_2, int param_3);
	void AddRibbon(float param_1, float param_2, int param_3);
	void AddExtremeFever(float param_1, float param_2, bool param_3, int param_4);

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
