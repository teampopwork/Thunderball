#ifndef __HELPSCREEN_H__
#define __HELPSCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>
#include <string>

namespace Sexy
{
class ThunderballApp;
class Graphics;

class HelpScreen : public Widget, public ButtonListener
{
  public:
	HelpScreen(ThunderballApp* theApp, bool param_1);
	virtual ~HelpScreen();

	virtual void ButtonDepress(int theId);
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);
	virtual void Update();

	void DrawPage0(Graphics* g);
	void DrawPage1(Graphics* g);
	void DrawPage2(Graphics* g);
	void DrawPage3(Graphics* g);
	void DrawPage4(Graphics* g);
	void DrawPage5(Graphics* g);
	void DrawPage6(Graphics* g);
	void DrawPage7(Graphics* g);
	void DrawPage8(Graphics* g);
	void DrawPanelRect2(Graphics* g, int* param_2, std::string* param_4, std::string* param_5, std::string* param_6);
	void DrawSummaryText(Graphics* g, std::string& param_1, const std::string& param_2);
	void SetCurPage(int param_1);
};
} // namespace Sexy

#endif // __HELPSCREEN_H__