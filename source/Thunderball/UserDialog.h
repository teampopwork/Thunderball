#ifndef __USERDIALOG_H__
#define __USERDIALOG_H__

#include "ThunderDialog.h"

#include <string>

namespace Sexy
{
class ThunderballApp;
class WidgetManager;
class Graphics;

class UserDialog : public ThunderDialog {
public:
	ThunderballApp* mApp;

	UserDialog(ThunderballApp* theApp);
	virtual ~UserDialog();

	virtual void AddedToManager(WidgetManager* theManager);
	virtual void RemovedFromManager(WidgetManager* theManager);
	virtual void ButtonDepress(int theId);
	virtual void Draw(Graphics* g);
	virtual int GetPreferredHeight(int theWidth);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);

	void CheckShowScrollbar();
	void FinishDeleteUser();
	void FinishRenameUser(std::string* name);
	std::string* GetSelName();
	void ListCLicked(int param_1, int param_2, int param_3);
};
} // namespace Sexy

#endif // __USERDIALOG_H__
