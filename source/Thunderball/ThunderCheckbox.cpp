#include "ThunderCheckbox.h"

#include "Res.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Graphics.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0049e7c0
ThunderCheckbox::ThunderCheckbox(
	Image* theUncheckedImage,
	Image* theCheckedImage,
	int theId,
	CheckboxListener* theCheckboxListener
)
	: Checkbox(theUncheckedImage, theCheckedImage, theId, theCheckboxListener)
{
	m_unk0x104 = 0;
	m_unk0x108 = 15;
	m_unk0xf4 = 0;
	m_unk0x120 = 0;
	m_unk0x124 = 0;
	m_unk0x128 = 0;
	m_unk0x12c = 0;
	m_unk0x130 = 0;
	m_unk0x134 = 0;
	m_unk0x138 = 0;
	m_unk0x13c = 0;
	m_unk0x110 = 0;
	m_unk0x10c = 0xffffffff;
	Font* dVar1 = FONT_BUTTON;
	m_unk0x140 = 0;
	m_unk0x118 = 0;
	m_unk0x148 = (double) 0x3fb47ae147ae147b;
	m_unk0x114 = 0;
	m_unk0x11c = 0;
	m_unk0x150 = (double) 0x3fc999999999999a;
	m_unk0xec = dVar1;
}

// FUNCTION: POPCAPGAME1 0x0049ecb0
ThunderCheckbox::~ThunderCheckbox()
{
}

// FUNCTION: POPCAPGAME1 0x0049bb10
void ThunderCheckbox::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x004970b0
void ThunderCheckbox::MouseDown(int x, int y, int theClickCount)
{
	if (!m_unk0x110 || !mChecked) {
		Checkbox::MouseDown(x, y, theClickCount);
	}

	if (0 <= m_unk0x10c) {
		GetThunderballApp()->PlaySample(m_unk0x10c);
	}
}

// FUNCTION: POPCAPGAME1 0x00497010
void ThunderCheckbox::MouseEnter()
{
	Checkbox::MouseEnter();
	if (m_unk0x150 == 0.0 && m_unk0x140 > 0.0) {
		m_unk0x140 = 0.0;
	}
	MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00497130
void ThunderCheckbox::MouseLeave()
{
	Checkbox::MouseLeave();
	if (!mIsDown) {
		if (mIsOver) {
			goto LAB_00497195;
		}
		if (0.0 < m_unk0x140) {
			if ((m_unk0x118 <= 0.0) || (m_unk0x140 = m_unk0x148 - m_unk0x140, m_unk0x140 < 0.0)) {
				m_unk0x140 = 0;
			}
			MarkDirty();
			return;
		}
	}
	if (mIsOver) {
		return;
	}

LAB_00497195:
	if ((0.0 < m_unk0x150) && (m_unk0x140 < 1.0)) {
		m_unk0x140 = m_unk0x150 + m_unk0x140;
		if (1.0 < m_unk0x140) {
			m_unk0x140 = 0;
			MarkDirty();
			return;
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00497100
void ThunderCheckbox::MouseUp(int x, int y, int theClickCount)
{
	Checkbox::MouseUp(x, y, theClickCount);
	MarkDirty();
}

// FUNCTION: POPCAPGAME1 0x00497050
void ThunderCheckbox::Update()
{
	Checkbox::Update();

	double dVar1 = 0.0;
	if ((m_unk0x148 != 0.0) && (m_unk0x140 > 0.0)) {
		if ((m_unk0x148 <= 0.0) || (m_unk0x140 != 0.0)) {
			MarkDirty();
			return;
		}
		dVar1 = 1.0;
	}
	m_unk0x140 = dVar1;
}
