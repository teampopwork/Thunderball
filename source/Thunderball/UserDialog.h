#ifndef __USERDIALOG_H__
#define __USERDIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/ListListener.h>

#include <string>

namespace Sexy
{
class ThunderballApp;
class WidgetManager;
class Graphics;
class ListWidget;
class ScrollbarWidget;
class ThunderButton;
class ThunderFrame;

class UserDialog : public ThunderDialog, public ListListener {
public:
	ThunderballApp* mApp; // +0x17C
	ListWidget* mUserList; // +0x180
	ScrollbarWidget* mScrollbar; // +0x184
	ThunderButton* mRenameButton; // +0x188
	ThunderButton* mDeleteButton; // +0x18C
	ThunderButton* mCreateButton; // +0x190
	ThunderFrame* mFrame; // +0x194
	bool mHasCreateEntry; // +0x198

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
	virtual void ListClicked(int theId, int theIdx, int theClickCount);
};
} // namespace Sexy

#endif // __USERDIALOG_H__
