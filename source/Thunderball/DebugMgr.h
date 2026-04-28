#ifndef __DEBUG_MGR_H__
#define __DEBUG_MGR_H__

namespace Sexy
{
class Board;
class Ball;

class DebugMgr {
public:
	DebugMgr(Board* param_1);
	~DebugMgr();

	void MarkCheat();
	void SyncFlipperState();
	void MouseMove(int param_1, int param_2);
	void MouseDrag(int param_1, int param_2);
	void MouseEnter();
	void MouseLeave();
	void KeyChar(char param_1);
	void MouseWheel(int param_1);
	void UpdateMouseBall();
	void SyncFeverState();
	Ball* GetBallAt(float param_1, float param_2);
	void SyncNumDebugPegs();
	void InitLevel();
	void Clear();
	void SetMouseBall(Ball* param_1);
	void MouseUp(int param_1, int param_2, int param_3);
	void MouseDown(int param_1, int param_2, int param_3);
	void DeleteBalls(bool param_1);
	void Update();
};

} // namespace Sexy

#endif // __DEBUG_MGR_H__
