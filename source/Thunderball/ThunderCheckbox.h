#ifndef __THUNDERCHECKBOX_H__
#define __THUNDERCHECKBOX_H__

#include <SexyAppFramework/Checkbox.h>

namespace Sexy
{
class Graphics;
class Image;
class Font;
class CheckboxListener;

// SIZE: 0x158
// VTABLE: POPCAPGAME1 0x00601d9c
class ThunderCheckbox : public Checkbox {
public:
	Font* mUnk0xec; // +0xec
	int mUnk0xf0;   // +0xf0
	bool mUnk0xf4;  // +0xf4
	char padding0xf8[0xc];
	int mUnk0x104;    // +0x104
	int mUnk0x108;    // +0x108
	int mUnk0x10c;    // +0x10c
	bool mUnk0x110;   // +0x110
	int mUnk0x114;    // +0x114
	int mUnk0x118;    // +0x118
	int mUnk0x11c;    // +0x11c
	int mUnk0x120;    // +0x120
	int mUnk0x124;    // +0x124
	int mUnk0x128;    // +0x128
	int mUnk0x12c;    // +0x12c
	int mUnk0x130;    // +0x130
	int mUnk0x134;    // +0x134
	int mUnk0x138;    // +0x138
	int mUnk0x13c;    // +0x13c
	double mUnk0x140; // +0x140
	double mUnk0x148; // +0x148
	double mUnk0x150; // +0x150

	ThunderCheckbox(Image* theUncheckedImage, Image* theCheckedImage, int theId, CheckboxListener* theCheckboxListener);
	virtual ~ThunderCheckbox();

	virtual void Draw(Graphics* g);
	virtual void MouseDown(int x, int y, int theClickCount);
	virtual void MouseEnter();
	virtual void MouseLeave();
	virtual void MouseUp(int x, int y, int theClickCount);
	virtual void Update();
};

} // namespace Sexy

#endif // __THUNDERCHECKBOX_H__
