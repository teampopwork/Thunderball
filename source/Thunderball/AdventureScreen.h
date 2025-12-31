#ifndef __ADVENTURE_SCREEN_H__
#define __ADVENTURE_SCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class ThunderballApp;
class Graphics;
class SexyChar;

// VTABLE: POPCAPGAME1 0x00005f2a24
class AdventureScreen : public Widget, public ButtonListener {
public:
	AdventureScreen(ThunderballApp* theApp);
	virtual ~AdventureScreen();

	virtual void Update();
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);
	virtual void ButtonDepress(int theId);

	void StartGame();
	void DrawHighScores(Graphics* g, int x, int y);
	void DrawPersonalHighScores(Graphics* g, int x, int y);
	void DrawStats(Graphics* g, int x, int y, bool param_1);
};
} // namespace Sexy

#endif // __ADVENTURE_SCREEN_H__
