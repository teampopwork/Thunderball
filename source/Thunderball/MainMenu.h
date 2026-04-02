#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "ThunderballApp.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/HyperlinkWidget.h>
#include <string>

namespace Sexy
{
class Graphics;
class ThunderButton;
class SimpleButton;

// VTABLE: POPCAPGAME1 0x005fa4fc Sexy::Widget
// VTABLE: POPCAPGAME1 0x005fa4d8 Sexy::ButtonListener
// VTABLE: POPCAPGAME1 0x005fa4d4 Sexy::MainMenu
class MainMenu : public Widget, public ButtonListener {
public:
	ThunderballApp* mApp; // +0x8C
	HyperlinkWidget* mRegisterLink; // +0x90
	ThunderButton* mAdventureButton; // +0x94
	ThunderButton* mSoloButton; // +0x98
	ThunderButton* mChallengeButton; // +0x9C
	ThunderButton* mDuelButton; // +0xA0
	ThunderButton* mDemoButton; // +0xA4
	ThunderButton* mReplayButton; // +0xA8
	ThunderButton* mOptionsButton; // +0xAC
	ThunderButton* mQuitButton; // +0xB0
	SimpleButton* mUpsellButton; // +0xB4
	
	int mUnk0xB8;         // +0xB8
	int mUnk0xBC;         // +0xBC
	bool mUnk0xC0;        // +0xC0
	bool mUnk0xC1;        // +0xC1
	int mUnk0xC4;         // +0xC4
	int mUnk0xC8;         // +0xC8
	int mUnk0xCC;        // +0xCC
	int mUnk0xD0;        // +0xD0
	int mUnk0xD4;        // +0xD4
	int mUnk0xD8;        // +0xD8
	int mUnk0xDC;        // +0xDC
	int mUnk0xE0;        // +0xE0
	int mUnk0xE4;        // +0xE4
	int mUnk0xE8;         // +0xE8
	int mUnk0xEC;         // +0xEC
	int mUnk0xF0;         // +0xF0

	MainMenu(ThunderballApp* theApp);
	virtual ~MainMenu();

	virtual void ButtonDepress(int theId);
	virtual void ButtonMouseEnter(int theId);
	virtual void Draw(Graphics* g);
	virtual void MouseMove(int x, int y);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Update();

	bool HandleControlClick(int param_1);
	void DoNotYet(std::string& param_1);
	void DrawSpeechBubble(Graphics* g, int param_2, int param_3, bool param_4);
	void DrawTrophyEffect(Graphics* g);
	void SetCurBubble(int param_1, int param_2);
	void StartGame();
	void StartTrophyEffect();
	void SyncPlayerInfo();
};

} // namespace Sexy

#endif // __MAIN_MENU_H__
