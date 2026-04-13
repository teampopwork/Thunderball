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
class ThunderButton;
class HyperlinkWidget;

class StoryData {};

class StoryScreen : public Widget, public ButtonListener {
public:
	ThunderballApp* mApp; // +0x8c
	ThunderButton* mUnk0x90; // +0x90
	HyperlinkWidget* mUnk0x94; // +0x94
	int mUnk0x98; // +0x98
	int mUnk0x9c; // +0x9c
	int mUnk0xa0; // +0xa0
	int mUnk0xa4; // +0xa4
	int mUnk0xb0; // +0xb0
	int mUnk0xb4; // +0xb4
	int mUnk0xb8; // +0xb8
	int mUnk0xcc; // +0xcc
	int mUnk0xd4; // +0xd4
	int mUnk0xd8; // +0xd8
	int mUnk0xdc; // +0xdc
	int mUnk0xe4; // +0xe4
	int mUnk0xe8; // +0xe8
	int mUnk0xec; // +0xec
	bool mUnk0xf1; // +0xf1
	bool mUnk0xf2; // +0xf2
	int mUnk0xf4; // +0xf4
	int mUnk0xfc; // +0xfc
	int mUnk0x100; // +0x100
	int mUnk0x108; // +0x108
	int mUnk0x10c; // +0x10c

	StoryScreen(ThunderballApp* theApp, bool param_2, bool param_3);
	virtual ~StoryScreen();

	virtual void ButtonDepress(int theId);
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
