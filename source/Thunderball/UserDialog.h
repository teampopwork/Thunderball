#ifndef __USERDIALOG_H__
#define __USERDIALOG_H__

#include "ThunderDialog.h"

#include <string>

namespace Sexy
{
class ThunderballApp;
class WidgetManager;
class Graphics;
class ListWidget;
class ScrollbarWidget;

class UserDialog : public ThunderDialog {
public:
	int mUnk0x178;
	ThunderballApp* mApp; // +0x17C
	ListWidget* mUserList; // +0x180
	ScrollbarWidget* mScrollbar; // +0x184
	int mUnk0x188;
	int mUnk0x18C;
	int mUnk0x190;
	int mUnk0x194;
	bool mUnk0x198;

	UserDialog(ThunderballApp* theApp);
	virtual ~UserDialog();

	virtual void AddedToManager(WidgetManager* theWidgetManager);
	virtual void RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void ButtonDepress(int theId);
	virtual void Draw(Graphics* g);
	virtual int GetPreferredHeight(int theWidth);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);

	void CheckShowScrollbar();
	void FinishDeleteUser();
	void FinishRenameUser(std::string* name);
	std::string GetSelName();
	void ListClicked(int param_1, int param_2, int param_3);
};
} // namespace Sexy

#endif // __USERDIALOG_H__
