#ifndef __LEVELSCREEN_H__
#define __LEVELSCREEN_H__

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class ThunderballApp;
class Graphics;
class PlayerInfo;

class LevelScreen : public Widget, public ButtonListener {
public:
    ThunderballApp* mApp;          // +0x8c
    void* mUnk0x90;                // +0x90
    int mUnk0x94;                  // +0x94
    int mUnk0x98;                  // +0x98
    int mUnk0x9c;                  // +0x9c
    PlayerInfo* mPlayerInfo;        // +0xa0
    int mUnk0xa4;                  // +0xa4
    int mStage;                     // +0xa8
    int mHoveredLevel;             // +0xac
    int mHoverTicks;               // +0xb0
    char mUnk0xb4[0x78];           // +0xb4
    void* mUnk0x12c;               // +0x12c
    void* mUnk0x130;               // +0x130
    void* mUnk0x134;               // +0x134
    void* mUnk0x138;               // +0x138

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
