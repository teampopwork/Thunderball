#ifndef __THUNDERDIALOG_H__
#define __THUNDERDIALOG_H__

#include <SexyAppFramework/CheckboxListener.h>
#include <SexyAppFramework/Dialog.h>


namespace Sexy
{
class Graphics;

class ThunderDialog;
typedef void (*DrawFunc)(ThunderDialog*, Graphics*);

class ThunderDialog : public Dialog {
public:
	int mUnk0x150;
	int mUnk0x154;
	int mUnk0x158;
	int mUnk0x15C;
	bool mUnk0x160;
	bool mUnk0x161;
	bool mUnk0x162;
	bool mUnk0x163;
	int mUnk0x164;
	int mUnk0x168;
	int mUnk0x16C;
	bool mUnk0x170;
	DrawFunc mUnk0x174;


	ThunderDialog(
		int theId,
		bool isModal,
		const SexyString& theDialogHeader,
		const SexyString& theDialogLines,
		const SexyString& theDialogFooter,
		int theButtonMode
	);

	virtual ~ThunderDialog();

	void CancelScroll();
	void DoScroll(int param_1);
	void DoScrollOff(int param_1);
	void FinishScroll();
	int GetLeft();
	int GetRight();
	int GetTop();
	int GetWidth();
	bool IsScrolling();

	virtual void Draw(Graphics* g);
	virtual void KeyDown(KeyCode theKey);
	virtual void MouseDown(int x, int y, int theClickCount);
	virtual void Update();
};
} // namespace Sexy

#endif
