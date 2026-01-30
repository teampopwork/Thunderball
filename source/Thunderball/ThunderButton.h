#ifndef __THUNDERBUTTON_H__
#define __THUNDERBUTTON_H__

#include <SexyAppFramework/DialogButton.h>

namespace Sexy
{
class Graphics;

// SIZE: 0x160
// VTABLE: POPCAPGAME1 0x006003d4
class ThunderButton : public DialogButton {
public:
	int mUnk0x138;
	int mUnk0x13c;
	int mUnk0x140;
	int mUnk0x144;
	bool mUnk0x148;
	int mUnk0x14c;
	bool mUnk0x150;
	bool mUnk0x151;
	int mUnk0x154;
	bool mUnk0x158;
	bool mUnk0x159;
	int mUnk0x15c;

	ThunderButton(Image* theComponentImage, int theId, ButtonListener* theListener);

	virtual void Draw(Graphics* g);
	virtual void MouseDown(int x, int y, int theClickCount);
	virtual void MouseEnter();
	virtual void MouseUp(int x, int y, int theClickCount);
	virtual void Update();

	void Blink(int param_1, bool param_2);
	void StopBlink();
};
} // namespace Sexy

#endif // __THUNDERBUTTON_H__
