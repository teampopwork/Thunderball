#include "UserDialog.h"

#include "ThunderballApp.h"

#include <SexyAppFramework/ListWidget.h>
#include <SexyAppFramework/ScrollbarWidget.h>

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

// FUNCTION: POPCAPGAME1 0x004acec0
void UserDialog::ButtonDepress(int theId)
{
	Dialog::ButtonDepress(theId);
	std::string aName = GetSelName();
	switch (theId) {
	case 0:
		if (!aName.empty()) {
			mApp->DoRenameUserDialog(aName);
		}
		break;
	case 1:
		if (!aName.empty()) {
			mApp->DoConfirmDeleteUserDialog(aName);
		}
		break;
	case 2:
		mApp->DoCreateUserDialog();
		break;
	}
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

// FUNCTION: POPCAPGAME1 0x004980d0
void UserDialog::CheckShowScrollbar()
{
	bool shouldShow = mScrollbar->GetThumbSize() != 0;
	if (shouldShow != mScrollbar->mVisible) {
		Resize(mX, mY, mWidth, mHeight);
	}
}

// FUNCTION: POPCAPGAME1 0x00498150
void UserDialog::FinishDeleteUser()
{
	int anIndex = mUserList->mSelectIdx;
	mUserList->RemoveLine(anIndex);
	int aMinIndex = mUnk0x198 != false;
	anIndex--;
	if (anIndex < aMinIndex) {
		anIndex = aMinIndex;
	}

	if (mUserList->GetLineCount() > aMinIndex) {
		mUserList->SetSelect(anIndex);
	}
	CheckShowScrollbar();
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
