#ifndef __THUNDERDIALOG_H__
#define __THUNDERDIALOG_H__

#include <SexyAppFramework/CheckboxListener.h>
#include <SexyAppFramework/Dialog.h>

namespace Sexy
{
class ThunderDialog : public Dialog, public CheckboxListener {
public:
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
	void DoScroll(bool param_1);
	void DoScrollOff(bool param_1);
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
	virtual void CheckboxChecked(int theId, bool checked);
};
} // namespace Sexy

#endif
