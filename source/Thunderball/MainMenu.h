#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/ButtonListener.h>

namespace Sexy
{

// VTABLE: POPCAPGAME1 0x005fa4d4
class MainMenu : public Widget, public ButtonListener 
{
public:
    MainMenu();
    virtual ~MainMenu();
};
} // namespace Sexy

#endif // __MAINMENU_H__
