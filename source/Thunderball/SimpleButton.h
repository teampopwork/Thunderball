#ifndef __SIMPLEBUTTON_H__
#define __SIMPLEBUTTON_H__

#include <SexyAppFramework/ButtonWidget.h>

namespace Sexy
{
class Graphics;

// VTABLE: POPCAPGAME1 0x005fc30c Sexy::SimpleButton
class SimpleButton : public ButtonWidget {
public:
    Image* mImage; // 0x120
    int mUnk0x124;
    int mUnk0x128;
    int mUnk0x12c;

    SimpleButton(Image* theImage, int theId, ButtonListener* theListener);

    virtual void Draw(Graphics* g);
    virtual void MouseEnter();
    virtual void MouseLeave();
    virtual void MouseDown(int theX, int theY, int theClickCount);
    virtual void MouseUp(int theX, int theY);

}; // namespace Sexy

}
#endif // __SIMPLEBUTTON_H__