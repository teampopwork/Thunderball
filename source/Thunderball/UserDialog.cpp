#include "UserDialog.h"

using namespace Sexy;

UserDialog::UserDialog(ThunderballApp* theApp) : ThunderDialog(0x18, true, "WHO ARE YOU?", "", "", 2)
{
	mApp = theApp;
}

UserDialog::~UserDialog()
{
}

void UserDialog::AddedToManager(WidgetManager* theWidgetManager)
{
}

void UserDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
}

void UserDialog::ButtonDepress(int theId)
{
}

void UserDialog::Draw(Graphics* g)
{
}

int UserDialog::GetPreferredHeight(int theWidth)
{
	return 0;
}

void UserDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
}

void UserDialog::CheckShowScrollbar()
{
}

void UserDialog::FinishDeleteUser()
{
}

void UserDialog::FinishRenameUser(std::string* name)
{
}

std::string* UserDialog::GetSelName()
{
	return NULL;
}

void UserDialog::ListClicked(int param_1, int param_2, int param_3)
{
}
