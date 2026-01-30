#include "WidgetMover.h"

#include <SexyAppFramework/SexyApp.h>
#include <SexyAppFramework/Widget.h>
#include <list>

using namespace Sexy;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x00405ff0
MovingWidget::MovingWidget()
{
	mWidget = NULL;
	mTicks = 0;
	mRemoveWhenDone = false;
	mStartX = 0.0f;
	mStartY = 0.0f;
	mTargetX = 0.0f;
	mTargetY = 0.0f;
}

// FUNCTION: POPCAPGAME1 0x00406010
bool MovingWidget::Update()
{
	mTicks -= 1;

	if (mWidget != NULL) {
		if (mTicks > 0) {
			const float total = 20.0f;
			float elapsed = total - (float) mTicks;
			float t = elapsed / total;

			float cx = mStartX + (mTargetX - mStartX) * t;
			float cy = mStartY + (mTargetY - mStartY) * t;
			if (mWidget != NULL) {
				mWidget->Move((int) cx, (int) cy);
			}
		}
		else {
			if (mWidget != NULL) {
				mWidget->Move((int) mTargetX, (int) mTargetY);
			}
		}
	}

	if (mTicks == 0) {
		if (mRemoveWhenDone) {
			if (gSexyApp != NULL) {
				gSexyApp->SafeDeleteWidget(mWidget);
			}
		}

		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// SYNTHETIC: POPCAPGAME1 0x0040d3c0
// Sexy::WidgetMover::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0040d390
WidgetMover::WidgetMover()
{
}

// STUB: POPCAPGAME1 0x0040c660
WidgetMover::~WidgetMover()
{
}

// FUNCTION: POPCAPGAME1 0x0040c700
void WidgetMover::Clear()
{
	mWidgets.clear();
	mUnk0xc = 0;
}

// FUNCTION: POPCAPGAME1 0x00421d90
MovingWidget* WidgetMover::GetWidgetData(Widget* param_1, bool param_2)
{
	for (std::list<MovingWidget>::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it) {
		if (it->mWidget == param_1) {
			return &*it;
		}
	}

	if (param_2 == false) {
		return NULL;
	}

	MovingWidget entry;
	entry.mWidget = param_1;
	mWidgets.push_back(entry);

	return &mWidgets.back();
}

// FUNCTION: POPCAPGAME1 0x00408550
bool WidgetMover::IsMoving()
{
	return mUnk0xc != 0;
}

// FUNCTION: POPCAPGAME1 0x0040c7a0
void WidgetMover::RemoveWidget(Widget* param_1)
{
	for (std::list<MovingWidget>::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it) {
		if (it->mWidget == param_1) {
			mWidgets.erase(it);
			return;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00421f80
void WidgetMover::ScrollOff(Widget* param_1, int param_2, bool param_3)
{
	if (param_1 == NULL) {
		return;
	}

	MovingWidget* pMVar6 = GetWidgetData(param_1, true);
	if (pMVar6 == NULL) {
		return;
	}

	int iVar2 = param_1->mX;
	int iVar3 = param_1->mY;
	int iVar4 = param_1->mWidth;
	int iVar5 = param_1->mHeight;

	pMVar6->mTicks = 0x14;
	float fVar7 = (float) iVar3;
	float fVar8 = (float) iVar2;
	pMVar6->mStartY = fVar7;
	pMVar6->mStartX = fVar8;
	pMVar6->mRemoveWhenDone = param_3;

	switch (param_2) {
	case 0:
		pMVar6->mTargetY = fVar7;
		pMVar6->mTargetX = fVar8;
		break;
	case 1:
		pMVar6->mTargetY = fVar7;
		pMVar6->mTargetX = (float) -iVar4;
		break;
	case 2:
		// Use app width
		pMVar6->mTargetY = fVar7;
		pMVar6->mTargetX = (float) gSexyApp->mWidth;
		break;
	case 3:
		pMVar6->mTargetY = (float) gSexyApp->mHeight;
		pMVar6->mTargetX = fVar8;
		break;
	case 4:
		pMVar6->mTargetY = (float) -iVar5;
		pMVar6->mTargetX = fVar8;
		break;
	default:
		break;
	}

	// set widget removal flags and hide mouse
	param_1->mWidgetFlagsMod.mRemoveFlags |= 0x31;
	param_1->mMouseVisible = false;
}

// FUNCTION: POPCAPGAME1 0x00421e40
void WidgetMover::ScrollOn(Widget* param_1, int param_2)
{
	if (param_1 == NULL) {
		return;
	}

	MovingWidget* pMVar6 = GetWidgetData(param_1, true);
	if (pMVar6 == NULL) {
		return;
	}

	int iVar2 = param_1->mX;
	int iVar1 = param_1->mY;
	float local_10 = (float) param_1->mX;
	int iVar5 = param_1->mWidth;
	int iVar4 = param_1->mHeight;

	pMVar6->mTicks = 0x14;
	pMVar6->mRemoveWhenDone = 0;
	float fVar3 = (float) iVar1;
	pMVar6->mTargetX = local_10;
	pMVar6->mTargetY = fVar3;

	switch (param_2) {
	case 0:
		pMVar6->mStartX = local_10;
		pMVar6->mStartY = fVar3;
		param_1->mWidgetFlagsMod.mRemoveFlags = 0;
		param_1->mMouseVisible = true;
		return;
	case 1:
		iVar5 = gSexyApp->mWidth;
		break;
	case 2:
		iVar5 = -iVar5;
		break;
	case 3:
		fVar3 = (float) -iVar4;
		pMVar6->mStartX = local_10;
		pMVar6->mStartY = fVar3;
		param_1->mWidgetFlagsMod.mRemoveFlags = 0;
		param_1->mMouseVisible = true;
		return;
	case 4:
		iVar5 = gSexyApp->mHeight;
		pMVar6->mStartX = local_10;
		pMVar6->mStartY = (float) iVar5;
		param_1->mWidgetFlagsMod.mRemoveFlags = 0;
		param_1->mMouseVisible = true;
		return;
	default:
		param_1->mWidgetFlagsMod.mRemoveFlags = 0;
		param_1->mMouseVisible = true;
		return;
	}

	local_10 = (float) iVar5;
	pMVar6->mStartX = local_10;
	pMVar6->mStartY = fVar3;
	param_1->mWidgetFlagsMod.mRemoveFlags = 0;
	param_1->mMouseVisible = true;
}

// FUNCTION: POPCAPGAME1 0x0040c670
void WidgetMover::Update()
{
	for (std::list<MovingWidget>::iterator it = mWidgets.begin(); it != mWidgets.end();) {
		if (it->Update()) {
			it = mWidgets.erase(it);
		}
		else {
			++it;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004220d0
bool WidgetMover::WillRemove(Widget* param_1)
{
	MovingWidget* mw = GetWidgetData(param_1, false);
	if (mw == NULL) {
		return false;
	}

	return (mw->mRemoveWhenDone != 0);
}
