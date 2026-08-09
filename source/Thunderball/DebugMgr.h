#ifndef __DEBUG_MGR_H__
#define __DEBUG_MGR_H__

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SmartPtr.h>

namespace Sexy
{
class Board;
class Ball;

class DebugMgr {
public:
	bool mUnk0x4;
	bool mUnk0x5;
	bool mUnk0x6;
	SmartPtr<Ball> mMouseBall;
	float mMouseOffsetX;
	float mMouseOffsetY;
	int mUnk0x14;
	int mUnk0x18;
	int mUnk0x1C;
	bool mUnk0x20;
	bool mUnk0x21;
	Board* mBoard;

	DebugMgr(Board* param_1);
	virtual ~DebugMgr();

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
