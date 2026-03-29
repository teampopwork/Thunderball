#include "ThunderSlider.h"

#include "Res.h"
#include "ThunderCommon.h"

#include <SexyAppFramework/Color.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/ModVal.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004ab510
ThunderSlider::ThunderSlider(const std::string& theString, int theId, SliderListener* theListener)
	: Slider((Image*) NULL, IMAGE_DLG_SLIDERORB, theId, theListener)
{
	mUnk0xB8 = theString;
	mClip = false;
}

// SYNTHETIC: POPCAPGAME1 0x004ab5a0
// Sexy::ThunderSlider::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0049bd70
void ThunderSlider::Draw(Graphics* g)
{
	int theY;
	int theX;
	// STRING: POPCAPGAME1 0x00600780
	theX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp826,452", -0xaa);
	// STRING: POPCAPGAME1 0x00600738
	theY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp827,453", -2);
	g->DrawImage(IMAGE_DLG_SLIDER, theX, theY);

	g->SetFont(FONT_BUTTON);
	// STRING: POPCAPGAME1 0x006006f0
	Color aColor(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp828,457", 0xffffff));
	g->SetColor(aColor);

	SetButtonFontColor(0xd);
	g->DrawString(
		mUnk0xB8,
		// STRING: POPCAPGAME1 0x00600660
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp829,459", 0x12) + theX,
		// STRING: POPCAPGAME1 0x006006a8
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp830,459", 0x1f) + theY
	);

	double val = (double)(mThumbImage->mWidth / 2);
	int width = (int)((IMAGE_DLG_SLIDERHILIGHT->mWidth - val * -2) * mVal);

	if (width < 0) {
		width = 0;
	}
	if (width > IMAGE_DLG_SLIDERHILIGHT->mWidth) {
		width = IMAGE_DLG_SLIDERHILIGHT->mWidth;
	}

	Rect aRect = Rect(0, 0, width, IMAGE_DLG_SLIDERHILIGHT->mHeight);
	// STRING: POPCAPGAME1 0x00600618
	int sliderY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderButton.cpp831,465", 9);

	g->DrawImage(
		IMAGE_DLG_SLIDERHILIGHT,
		0,
		sliderY,
		aRect
	);

	Slider::Draw(g);
}
