#ifndef __INTERFACE_MGR_H__
#define __INTERFACE_MGR_H__

#include <string>

namespace Sexy
{
class Board;
class DataSync;
class Graphics;
class Image;

class InterfaceMgr {
public:
	InterfaceMgr(Board* param_1);
	virtual ~InterfaceMgr();

	int GetBallBottom();
	void AddScoreUpdateDelay(int param_1);
	void DrawScore(Graphics* param_1, std::string* param_2, bool param_3);
	void DrawSmallMode(Graphics* param_1, std::string* param_2, bool param_3);
	void DrawMode(Graphics* param_1, std::string* param_2, bool param_3);
	void DrawDetail(Graphics* param_1, std::string* param_2, bool param_3, int param_4);
	void DrawScoreBlink(Graphics* param_1);
	int GetBallX();
	void DrawSuperFront(Graphics* param_1);
	void EndShot();
	void DoShotMeterBlink();
	void DoFeverBlink();
	void UpdateShotMeter();
	bool IsScoreAccurate();
	void DoFeverMultBlink();
	void DoFever();
	void UpdatePaused();
	void CheckHighScoreSync();
	void SettleDown();
	void UpdateScoreDisp();
	void DrawShotMeter(Graphics* param_1);
	void DrawImageToInterface(Image* param_1, int param_2, int param_3, int param_4);
	void DrawImageCelToInterface(Image* param_1, int param_2, int param_3);
	void LoadGun();
	void DrawFeverLights(Graphics* param_1);
	void BeginShot();
	void UpdateHighScore(bool param_1);
	void InitLevel();
	int GetTopBallY();
	int GetNumVisibleBalls();
	void DrawBalls(Graphics* param_1);
	void UpdateBalls();
	void SetNumBalls(int param_1);
	void Clear();
	void AddBottomBall(int param_1);
	void Update();
	void AddTopBalls(int param_1);
	void SyncState(DataSync* param_1);
	void SyncStageNum();
	void DrawBallsLeftDetail(Graphics* param_1, int param_2, bool param_3);
	void DrawOnePlayer(Graphics* param_1);
	void DrawStageMode(Graphics* param_1);
	void DrawTrophyMode(Graphics* param_1);
	void DrawTwoPlayer(Graphics* param_1);
	void DrawBack(Graphics* param_1);
	void DrawFront(Graphics* param_1);
};

} // namespace Sexy

#endif // __INTERFACE_MGR_H__
