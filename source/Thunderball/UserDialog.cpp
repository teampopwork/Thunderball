#include "UserDialog.h"

#include "ProfileMgr.h"
#include "Res.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderFrame.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/ListWidget.h>
#include <SexyAppFramework/ModVal.h>
#include <SexyAppFramework/ScrollbarWidget.h>
#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004ac970
UserDialog::UserDialog(ThunderballApp* theApp) : ThunderDialog(0x18, true, "WHO ARE YOU?", "", "", 2)
{
	mApp = theApp;
	mUnk0x163 = true;
	mHasCreateEntry =
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\UserDialog.cpp935,37", 0) != 0;

	mUserList = MakeListWidget(0, this);
	mUserList->mJustify = ListWidget::JUSTIFY_CENTER;
	mFrame = new ThunderFrame();
	mScrollbar = new ScrollbarWidget(0, mUserList);
	mRenameButton = MakeButton(0, this, "Rename", NULL);
	mDeleteButton = MakeButton(1, this, "Delete", NULL);
	mCreateButton = MakeButton(
		2,
		this,
		ModVal(
			0,
			"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\UserDialog.cpp936,47",
			"Create New User"
		),
		NULL
	);
	mUserList->mScrollbar = mScrollbar;

	if (mHasCreateEntry) {
		mUserList->AddLine("(Create a New User)", false);
	}

	if (mApp->mCurProfile != NULL) {
		mUserList->SetSelect(mUserList->AddLine(mApp->mCurProfile->mName, false));
	}

	const ProfileMap& aProfileMap = mApp->mProfileMgr->GetProfileMap();
	for (ProfileMap::const_iterator anItr = aProfileMap.begin(); anItr != aProfileMap.end(); ++anItr) {
		if (mApp->mCurProfile == NULL || mApp->mCurProfile->mName != anItr->second.mName) {
			mUserList->AddLine(anItr->second.mName, false);
		}
	}

	AddWidget(mUserList);
	AddWidget(mScrollbar);
	AddWidget(mRenameButton);
	AddWidget(mDeleteButton);
	AddWidget(mCreateButton);
	AddWidget(mFrame);
}

// FUNCTION: POPCAPGAME1 0x00497dd0
UserDialog::~UserDialog()
{
	RemoveAllWidgets(true);
}

// FUNCTION: POPCAPGAME1 0x00498120
void UserDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	Dialog::AddedToManager(theWidgetManager);
	theWidgetManager->SetFocus(mUserList);
}

void UserDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Dialog::RemovedFromManager(theWidgetManager);
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

// FUNCTION: POPCAPGAME1 0x004981f0
void UserDialog::Draw(Graphics* g)
{
	ThunderDialog::Draw(g);
}

// FUNCTION: POPCAPGAME1 0x004980a0
int UserDialog::GetPreferredHeight(int theWidth)
{
	return Dialog::GetPreferredHeight(theWidth) +
		   ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\UserDialog.cpp947,115", 0xff);
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
	int aMinIndex = mHasCreateEntry != false;
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
	if (anIndex >= (mHasCreateEntry != false)) {
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

// FUNCTION: POPCAPGAME1 0x00498200
void UserDialog::ListClicked(int theId, int theIdx, int theClickCount)
{
	if (theIdx == 0 && mHasCreateEntry) {
		mApp->PlaySample(SOUND_BUTTON1);
		mApp->DoCreateUserDialog();
		return;
	}

	mUserList->SetSelect(theIdx);
	if (theClickCount == 2) {
		mApp->FinishUserDialog(true);
	}
}
