#ifndef __REPLAYDIALOG_H__
#define __REPLAYDIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/ButtonListener.h>

namespace Sexy
{
class Board;
class ThunderButton;
class Graphics;
class WidgetManager;

class ReplayDialog : public ThunderDialog {
public:
	Board* mBoard;                    // +0x178
	ThunderButton* mReplayButton;     // +0x17C
	ThunderButton* mOptionButtons[4]; // +0x180
	int mUnk0x190;                    // +0x190
	bool mUnk0x194;                   // +0x194
	bool mUnk0x195;                   // +0x195
	bool mUnk0x196;                   // +0x196

	ReplayDialog(Board* param_1);
	virtual ~ReplayDialog();

	virtual void RemovedFromManager(WidgetManager* param_1);
	void SetMouseVisibility(bool param_1);
	virtual void Resize(int param_1, int param_2, int param_3, int param_4);
	virtual void MouseDown(int param_1, int param_2, int param_3);
	virtual int GetPreferredHeight(int param_1);
	bool IsFast();
	void BlinkDoneButton();
	void StopBlinkingButtons();
	virtual void ButtonPress(int param_1);
	virtual void Draw(Graphics* g);
	virtual void Update();
	virtual void DrawOverlay(Graphics* g);
	void SetMode(bool param_1, bool param_2, bool param_3);
	virtual void ButtonDepress(int param_1);
};

} // namespace Sexy

#endif // __REPLAYDIALOG_H__
