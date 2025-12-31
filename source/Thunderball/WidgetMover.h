#ifndef __WIDGETMOVER_H__
#define __WIDGETMOVER_H__

#include <SexyAppFramework/Widget.h>
#include <list>

namespace Sexy
{
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class MovingWidget {
public:
	MovingWidget();
	bool Update();
	Widget* mWidget;      // +0x00
	int mTicks;           // +0x04
	bool mRemoveWhenDone; // +0x08
	float mStartX;        // +0x0C
	float mStartY;        // +0x10
	float mTargetX;       // +0x14
	float mTargetY;       // +0x18
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// VTABLE: POPCAPGAME1 0x005d5da4
class WidgetMover {
public:
	std::list<MovingWidget> mWidgets; // +0x4
	int m_unk0xc;                     // +0x0C

	WidgetMover();
	virtual ~WidgetMover();

	void Clear();
	MovingWidget* GetWidgetData(Widget* param_1, bool param_2);
	bool IsMoving();
	void RemoveWidget(Widget* param_1);
	void ScrollOff(Widget* param_1, int param_2, bool param_3);
	void ScrollOn(Widget* param_1, int param_2);
	void Update();
	bool WillRemove(Widget* param_1);
};
} // namespace Sexy

#endif // __WIDGETMOVER_H__
