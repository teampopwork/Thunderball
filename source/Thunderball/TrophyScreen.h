
#ifndef __TROPHY_SCREEN_H__
#define __TROPHY_SCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class ThunderballApp;
class Graphics;
class DDImage;

class TrophyScreen : public Widget, public ButtonListener {
public:
	TrophyScreen(ThunderballApp* theApp);
	virtual ~TrophyScreen();

	virtual void Update();
	virtual void Draw(Graphics* g);
	virtual void DrawOverlay(Graphics* g);

	virtual void ButtonPress(int theId, int theClickCount);
	virtual void ButtonDepress(int theId);
	virtual void ButtonMouseEnter(int theId);
	virtual void ButtonMouseLeave(int theId);

	void SyncPlayerInfo();
	void SyncPageNum();
	bool CanSelectTrophy();
	bool CanSelectTrophy(int param);
	void DoPlay();

	void DrawBadge(Graphics* g, int theId);
	void DrawTrophyInfo(Graphics* g, int theId);
	void DrawImageAndRect(Graphics *g,Image *param_2,int param_3,int param_4,int param_5,int param_6);


	DDImage* GetLevelImage(const std::string& theLevel);
};

} // namespace Sexy

#endif // __TROPHY_SCREEN_H__
