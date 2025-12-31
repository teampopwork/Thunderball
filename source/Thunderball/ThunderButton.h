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
	int m_unk0x138;
	int m_unk0x13c;
	int m_unk0x140;
	int m_unk0x144;
	bool m_unk0x148;
	int m_unk0x14c;
	bool m_unk0x150;
	bool m_unk0x151;
	int m_unk0x154;
	bool m_unk0x158;
	bool m_unk0x159;
	int m_unk0x15c;

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
