#ifndef __ADVENTURE_SCREEN_H__
#define __ADVENTURE_SCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <list>

namespace Sexy
{
class ThunderballApp;
class ThunderButton;
class HighScoreEntry;
class MemoryImage;
class PlayerInfo;
class Graphics;

// VTABLE: POPCAPGAME1 0x005f2a24 Sexy::Widget
// VTABLE: POPCAPGAME1 0x005f2a00 Sexy::ButtonListener
class AdventureScreen : public Widget, public ButtonListener {
public:
	ThunderballApp* mApp;                   // +0x8c
	PlayerInfo* mCurProfile;                // +0x90
	std::list<HighScoreEntry>* mHighScores; // +0x94
	MemoryImage* mUnk0x98;                  // +0x98
	bool mUnk0x9c;                          // +0x9c

	ThunderButton* mMainMenuButton; // +0xa0;
	ThunderButton* mContinueButton; // +0xa4;
	ThunderButton* mRestartButton;  // +0xa8;

	AdventureScreen(ThunderballApp* theApp);
	virtual ~AdventureScreen();

	virtual void Update();
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);
	virtual void ButtonDepress(int theId);

	void StartGame();
	void DrawHighScores(Graphics* g, int theX, int theY);
	void DrawPersonalHighScores(Graphics* g, int theX, int theY);
	void DrawStats(Graphics* g, int theX, int theY, bool param_1);
};
} // namespace Sexy

#endif // __ADVENTURE_SCREEN_H__
