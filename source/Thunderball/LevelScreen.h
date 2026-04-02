#ifndef __LEVELSCREEN_H__
#define __LEVELSCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class ThunderballApp;
class Graphics;

class LevelScreen : public Widget, public ButtonListener {
public:
    LevelScreen(ThunderballApp* theApp);
    virtual ~LevelScreen();

    virtual void Update();
    virtual void Draw(Graphics* g);

    void SyncPlayerInfo();
    void DrawLevelInfo(Graphics* g, int theX, int theY);
    void SyncStageNum();
    void DoPlay(int theId);
    bool CanSelectLevel(int theId);

    virtual void ButtonDepress(int theId);
    virtual void ButtonMouseEnter(int theId);
    virtual void ButtonMouseLeave(int theId);
    virtual void ButtonPress(int theId, int theMouseButton);
};

} // namespace Sexy

#endif // __LEVELSCREEN_H__