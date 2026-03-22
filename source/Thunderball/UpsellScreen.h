#ifndef __UPSELLSCREEN_H__
#define __UPSELLSCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class ThunderballApp;
class Graphics;

class UpsellScreen : public Widget, public ButtonListener {
public:
	UpsellScreen(ThunderballApp* theApp, bool param_2);
	virtual ~UpsellScreen();

	virtual void ButtonDepress(int theId);
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);

	void DrawBjorn(Graphics* g);
	void DrawBuyNow(Graphics* g);
	void DrawLevels(Graphics* g);
	void DrawMasters(Graphics* g);
	void DrawSpeechBubble(Graphics* g, int param_2, int param_3, bool param_4);
	void DrawZoomText(Graphics* g, int param_2, int param_3, int param_4);
	void Pause(bool param_1);
	void SetCurBubble(int param_1);
	void SetState(int param_1);
};
} // namespace Sexy

#endif // __UPSELLSCREEN_H__
