#ifndef __DEBUG_MGR_H__
#define __DEBUG_MGR_H__

#include <SexyAppFramework/Common.h>

namespace Sexy
{
class Board;
class Ball;

class DebugMgr {
public:
	int mUnk0x4;
	bool mUnk0x20;

	DebugMgr(Board* param_1);
	~DebugMgr();

	void MarkCheat();
	void SyncFlipperState();
	bool MouseMove(int theX, int theY);
	bool MouseDrag(int theX, int theY);
	bool MouseEnter();
	bool MouseLeave();
	bool KeyChar(SexyChar theKey);
	bool MouseWheel(int theDelta);
	void UpdateMouseBall();
	void SyncFeverState();
	Ball* GetBallAt(float param_1, float param_2);
	void SyncNumDebugPegs();
	void InitLevel();
	void Clear();
	void SetMouseBall(Ball* param_1);
	bool MouseUp(int theX, int theY, int theClickCount);
	bool MouseDown(int theX, int theY, int theClickCount);
	void DeleteBalls(bool param_1);
	void Update();
};

} // namespace Sexy

#endif // __DEBUG_MGR_H__
