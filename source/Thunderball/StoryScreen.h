#ifndef __STORYSCREEN_H__
#define __STORYSCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/Rect.h>
#include <vector>

namespace Sexy
{
class ThunderballApp;
class Graphics;

class StoryData {};

class StoryScreen : public Widget, public ButtonListener {
public:
	StoryScreen(ThunderballApp* theApp, bool param_2, bool param_3);
	virtual ~StoryScreen();

	virtual void ButtonDepress(int theId);
	virtual void KeyChar(SexyChar theChar);
	virtual void KeyDown(KeyCode keyCode);
	virtual void MouseDown(int theX, int theY, int theButton);
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);
	virtual void Update();

	void InitText();
	void PlayOdeNote(int noteId);
	void DrawFireworks(Graphics* g);
	void DrawStars(Graphics* g);
	void DrawWin(Graphics* g);
	void DoDrawText(Graphics* g, Rect& param_2, std::vector<StoryData> param_3, int param_4);
	void DoUpdate();
	void UpdateParticles();
	void UpdateStars();
	void UpdateWin();
};
} // namespace Sexy

#endif // __STORYSCREEN_H__
