#include "ThunderDialog.h"

#include "Res.h"

#include <SexyAppFramework/Graphics.h>

using namespace Sexy;

// SYNTHETIC: POPCAPGAME1 0x0049bef0
// Sexy::ThunderDialog::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x00497280
ThunderDialog::ThunderDialog(
	int theId,
	bool isModal,
	const SexyString& theDialogHeader,
	const SexyString& theDialogLines,
	const SexyString& theDialogFooter,
	int theButtonMode
)
	: Dialog(
		  IMAGE_DLG_BUTTON3,
		  IMAGE_DLG_DIALOGBOX,
		  theId,
		  isModal,
		  theDialogHeader,
		  theDialogLines,
		  theDialogFooter,
		  theButtonMode
	  )
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497550
ThunderDialog::~ThunderDialog()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497720
void ThunderDialog::CancelScroll()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497580
void ThunderDialog::DoScroll(bool param_1)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497690
void ThunderDialog::DoScrollOff(bool param_1)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497700
void ThunderDialog::FinishScroll()
{
	// TODO
}

// FUNCTION: POPCAPGAME1 0x00497750
int ThunderDialog::GetLeft()
{
	
	return mX + mContentInsets.mLeft + mBackgroundInsets.mLeft -
	// STRING: POPCPGAME1 0x005fcb70
		   ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderDialog.cpp848,166", 0);
}

// STUB: POPCAPGAME1 0x00497780
int ThunderDialog::GetRight()
{
	// TODO
	return 0;
}

// STUB: POPCAPGAME1 0x004977a0
int ThunderDialog::GetTop()
{
	// TODO
	return 0;
}

// STUB: POPCAPGAME1 0x004977e0
int ThunderDialog::GetWidth()
{
	// TODO
	return 0;
}

// STUB: POPCAPGAME1 0x00497570
bool ThunderDialog::IsScrolling()
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x00497820
void ThunderDialog::Draw(Graphics* g)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497930
void ThunderDialog::KeyDown(KeyCode theKey)
{
	// TODO
}

// STUB: POPCAPGAME1 0x00497910
void ThunderDialog::MouseDown(int x, int y, int theClickCount)
{
	// TODO
}

// STUB: POPCAPGAME1 0x0049bf20
void ThunderDialog::Update()
{
	// TODO
}

// STUB: POPCAPGAME1 0x004a9700
void ThunderDialog::CheckboxChecked(int theId, bool checked)
{
	// TODO
}
