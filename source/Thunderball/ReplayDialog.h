#ifndef __REPLAYDIALOG_H__
#define __REPLAYDIALOG_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy {
class Board;
class Graphics;
class WidgetManager;

class ReplayDialog : public Widget, public ButtonListener {
public:
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
	virtual void Draw(Graphics* param_1);
	virtual void Update();
	virtual void DrawOverlay(Graphics* param_1);
	void SetMode(bool param_1, bool param_2, bool param_3);
	virtual void ButtonDepress(int param_1);
};

} // namespace Sexy

#endif // __REPLAYDIALOG_H__
