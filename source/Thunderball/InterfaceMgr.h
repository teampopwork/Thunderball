#ifndef __INTERFACE_MGR_H__
#define __INTERFACE_MGR_H__

#include <SexyAppFramework/SexyVector.h>

#include <string>
#include <vector>

namespace Sexy
{
class Board;
class DataSync;
class Graphics;
class Image;
class MemoryImage;
class ThunderballApp;

class InterfaceMgr {
public:
	ThunderballApp* mApp; // +0x4
	Board* mBoard; // +0x8
	MemoryImage* mImages[9]; // +0xc
	int mUnk0x30; // +0x30
	int mUnk0x34; // +0x34
	int mUnk0x38; // +0x38
	int mUnk0x3c; // +0x3c
	int mUnk0x40; // +0x40
	int mUnk0x44; // +0x44
	int mUnk0x48; // +0x48
	int mUnk0x4c; // +0x4c
	int mUnk0x50; // +0x50
	int mUnk0x54; // +0x54
	int mUnk0x58; // +0x58
	int mUnk0x5c; // +0x5c
	int mUnk0x60; // +0x60
	int mUnk0x64; // +0x64
	int mUnk0x68; // +0x68
	int mUnk0x6c; // +0x6c
	std::string mUnk0x70; // +0x70
	char mPadding0x8c[0x8]; // +0x8c
	int mUnk0x94; // +0x94
	int mUnk0x98; // +0x98
	int mUnk0x9c; // +0x9c
	std::string mUnk0xa0; // +0xa0
	std::string mUnk0xbc; // +0xbc
	int mUnk0xd8; // +0xd8
	int mUnk0xdc; // +0xdc
	int mUnk0xe0; // +0xe0
	int mUnk0xe4; // +0xe4
	int mUnk0xe8; // +0xe8
	int mUnk0xec; // +0xec
	int mUnk0xf0; // +0xf0
	int mUnk0xf4; // +0xf4
	int mUnk0xf8; // +0xf8
	int mUnk0xfc[25]; // +0xfc
	bool mUnk0x160; // +0x160
	bool mUnk0x161; // +0x161
	char mPadding0x162[0x2]; // +0x162
	std::vector<SexyVector2> mUnk0x164; // +0x164

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
	void SyncState(DataSync& param_1);
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
