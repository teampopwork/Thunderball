#ifndef __DIALOGBUTTON_H__
#define __DIALOGBUTTON_H__

#include "ButtonWidget.h"

namespace Sexy
{

// VTABLE: POPCAPGAME1 0x006142cc
class DialogButton : public ButtonWidget
{
public:	
	Image*					mComponentImage;
	int						mTranslateX, mTranslateY;
	int						mTextOffsetX, mTextOffsetY;

public:
	DialogButton(Image* theComponentImage, int theId, ButtonListener* theListener);

	virtual void			Draw(Graphics* g);
};

}

#endif //__DIALOGBUTTON_H__