#ifndef __THUNDERCHECKBOX_H__
#define __THUNDERCHECKBOX_H__

#include <SexyAppFramework/Checkbox.h>
#include <SexyAppFramework/Rect.h>
#include <string>

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
	Font* mUnk0xec;             // +0xec
	std::string mLabel;         // +0xf0
	int mUnk0x10c;              // +0x10c
	bool mUnk0x110;             // +0x110
	int mUnk0x114;              // +0x114
	int mUnk0x118;              // +0x118
	int mUnk0x11c;              // +0x11c
	Rect mUncheckedHilightRect; // +0x120
	Rect mCheckedHilightRect;   // +0x130
	double mUnk0x140;           // +0x140
	double mUnk0x148;           // +0x148
	double mUnk0x150;           // +0x150

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
