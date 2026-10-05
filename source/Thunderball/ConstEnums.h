#ifndef __CONSTENUMS_H__
#define __CONSTENUMS_H__

namespace Sexy
{
enum GameMode {
	UNKNOWN_0 = 0,
	ADVENTURE = 1,
	QUICK_PLAY = 2,
	DUEL = 3,
	CHALLENGE = 4,
	UNKNOWN_5 = 5,
	DEMO = 6
};

enum PowerupType {
	POWERUP_0 = 0,
	POWERUP_1 = 1,
	POWERUP_2 = 2,
	POWERUP_4 = 4,
	POWERUP_7 = 7,
	POWERUP_10 = 10
};

enum StyleShot;
enum LogicState {
	LOGICSTATE_5 = 5,
	LOGICSTATE_6 = 6
};

enum PegType {
	NONE = 0,
	NORMAL = 1,
	GOAL = 2,
	SCORE = 3,
	POWERUP = 4
};

enum EndLevelMode;

enum EffectType {
	EFFECT_0 = 0,
	EFFECT_1 = 1,
	EFFECT_2 = 2,
	EFFECT_3 = 3,
	EFFECT_4 = 4,
	EFFECT_5 = 5,
	EFFECT_6 = 6,
	EFFECT_7 = 7,
	EFFECT_22 = 22,
	EFFECT_33 = 33
};

} // namespace Sexy

#endif // __CONSTENUMS_H__
