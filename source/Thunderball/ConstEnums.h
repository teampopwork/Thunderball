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

enum PowerupType;
enum StyleShot;
enum LogicState;

enum PegType {
	NONE = 0,
	NORMAL = 1,
	GOAL = 2,
	SCORE = 3,
	POWERUP = 4
};

enum EndLevelMode;


} // namespace Sexy

#endif // __CONSTENUMS_H__
