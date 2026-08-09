#include "UserDialog.h"

#include <SexyAppFramework/ListWidget.h>

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

// FUNCTION: POPCAPGAME1 0x004981b0
void UserDialog::FinishRenameUser(std::string* name)
{
	int anIndex = mUserList->mSelectIdx;
	if (anIndex >= (mUnk0x198 != false)) {
		mUserList->SetLine(anIndex, *name);
	}
}

// FUNCTION: POPCAPGAME1 0x004ace40
std::string UserDialog::GetSelName()
{
	if (mUserList->mSelectIdx >= 0 && mUserList->mSelectIdx < mUserList->GetLineCount()) {
		return mUserList->GetStringAt(mUserList->mSelectIdx);
	}

	return "";
}

void UserDialog::ListClicked(int param_1, int param_2, int param_3)
{
}
