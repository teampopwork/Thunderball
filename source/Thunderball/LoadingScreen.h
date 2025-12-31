#ifndef __LOADING_SCREEN_H__
#define __LOADING_SCREEN_H__

#include "ThunderballApp.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class SexyAppBase;
class Graphics;
class ThunderButton;

struct Particle {
	float mX;     // +0x00
	float mY;     // +0x04
	int mAlpha;   // +0x08
	float mVelX;  // +0x0C
	float mVelY;  // +0x10
	bool mFlip;   // +0x14
	float mAngle; // +0x18
};

// SIZE: 0xF0
// VTABLE: POPCAPGAME1 0x00606e84 Sexy::Widget
// VTABLE: POPCAPGAME1 0x00606e60 Sexy::ButtonListener
class LoadingScreen : public Widget, public ButtonListener {
public:
	ThunderballApp* mApp;              // +0x8C
	ThunderButton* mPlayNowButton;     // +0x90
	float mLoadProgress;               // +0x94
	float mSunRotationAngle;           // +0x98
	int m_unk0x9C;                     // +0x9C
	int mPlayNowPulseCount;            // +0xA0
	float m_unk0xA4;                     // +0xA4
	int mAdventureStartDelay;          // +0xA8
	int mBallAnimState;                // +0xAC
	int mLogoBounceFrame;              // +0xB0
	float mBallX;                      // +0xB4
	float mBallY;                      // +0xB8
	float mBallVelX;                   // +0xBC
	float mBallVelY;                   // +0xC0
	bool mBallBounceInit;              // +0xC4
	std::vector<Particle> mParticles; // +0xC8
	//int m_unk0xCC;                     // +0xCC
	//int m_unk0xD0;                     // +0xD0
	//int m_unk0xD4;                     // +0xD4
	bool m_unk0xD8;                    // +0xD8
	HANDLE mLevelLoadMusicThread;      // +0xDC
	int m_unk0xE0;                     // +0xE0
	int m_unk0xE4;                     // +0xE4
	bool mDisplayPartnerLogo;          // +0xE8
	int mLightBeamCount;               // +0xEC

	LoadingScreen(ThunderballApp* theApp);
	virtual ~LoadingScreen();

	virtual void DrawOverlay(Graphics* g);
	virtual void ButtonDepress(int theId);
	virtual void ButtonPress(int theId, int theClickCount);
	virtual void Draw(Graphics* g);
	virtual void KeyChar(SexyChar theChar); // vtable+0xBC
	virtual void Update();

	void DoBallBounce();
	void DoLevelLoadMusic();
	void DrawLight(Graphics* g, int param_2);
	void DrawParticles(Graphics* g);
	void SpawnParticles();
	void UpdateBall();
	void UpdateParticles();
	void QuickPlay();

	static void LevelLoadMusicThreadProc(void* theArg);
};
} // namespace Sexy

#endif // __LOADING_SCREEN_H__
