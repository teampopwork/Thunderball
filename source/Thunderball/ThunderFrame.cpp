#include "ThunderFrame.h"

#include "Res.h"

#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Rect.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00497200
ThunderFrame::ThunderFrame()
{
	mVisible = true;
	mMouseVisible = false;
	mHasTransparencies = true;
}

// FUNCTION: POPCAPGAME1 0x0049beb0
void ThunderFrame::Draw(Graphics* g)
{
	g->DrawImageBox(Rect(0, 0, mWidth, mHeight), IMAGE_DLG_BLUEFRAME);
}
