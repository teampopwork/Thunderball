#include "ThunderCommon.h"

#include "Res.h"
#include "SimpleButton.h"
#include "ThunderButton.h"
#include "ThunderCheckbox.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/CheckboxListener.h>
#include <SexyAppFramework/Dialog.h>
#include <SexyAppFramework/EditListener.h>
#include <SexyAppFramework/EditWidget.h>
#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Insets.h>
#include <SexyAppFramework/Rect.h>
#include <SexyAppFramework/WidgetManager.h>

using namespace Sexy;

// STUB: POPCAPGAME1 0x0040b570
void Sexy::SetButtonFontColor(int color)
{
}

// FUNCTION: POPCAPGAME1 0x0049c390
void Sexy::SwapRect(TRect<int>& rect1, TRect<int>& rect2)
{
	TRect<int> temp = rect1;
	rect1 = rect2;
	rect2 = temp;
}

// FUNCTION: POPCAPGAME1 0x004056c0
ButtonWidget* Sexy::MakeWinButton(Image* theImage, int theType)
{
	ButtonWidget* aButton = new ButtonWidget(theType, GetThunderballApp());
	aButton->mButtonImage = theImage;
	aButton->mWidth = theImage->mWidth;
	aButton->mHeight = theImage->mHeight;
	aButton->mZOrder = 1000;
	return aButton;
}

// FUNCTION: POPCAPGAME1 0x00405020
void Sexy::DrawScreenFrame(Graphics* g)
{
	using namespace Sexy;

	g->DrawImage(IMAGE_SCREENFRAMELEFT, 0, 0);

	g->DrawImage(IMAGE_SCREENFRAMETOP, IMAGE_SCREENFRAMELEFT->mWidth, 0);

	g->DrawImage(
		IMAGE_SCREENFRAMEBOTTOM,
		IMAGE_SCREENFRAMELEFT->mWidth,
		IMAGE_SCREENFRAMELEFT->mHeight - IMAGE_SCREENFRAMEBOTTOM->mHeight
	);

	g->DrawImage(IMAGE_SCREENFRAMERIGHT, IMAGE_SCREENFRAMELEFT->mWidth + IMAGE_SCREENFRAMETOP->mWidth, 0);
}

// FUNCTION: POPCAPGAME1 0x0040bc20
void Sexy::PositionDialog(Dialog* theDialog, int theWidth, bool param_3, int param_4)
{
	int theY = theDialog->mHeaderFont->StringWidth(theDialog->mDialogHeader) + theDialog->mContentInsets.mLeft +
			   theDialog->mContentInsets.mRight + theDialog->mBackgroundInsets.mLeft +
			   theDialog->mBackgroundInsets.mRight + 0x14;
	if (theWidth < theY) {
		theWidth = theY;
	}

	WidgetManager* aWidgetManager = NULL;
	if (gSexyApp->mDialogMap.size() != 0) {
		aWidgetManager = gSexyApp->mDialogMap.begin()->second->mWidgetManager;
	}

	int aPreferredHeight = theDialog->GetPreferredHeight(theWidth);

	int theX = 0;
	if (aWidgetManager == NULL) {
		if ((GetThunderballApp()->mDialogMap.size() != 0) || !param_3) {
			theX = 400 - theWidth / 2;
		}
		else if (theY < ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp142,731", 300)) {
			theX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp145,737", 0x122) -
				   theWidth / 2;
		}
		else {
			// STRING: POPCAPGAME1 0x005d5ac0
			theX =
				ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp143,733", 0x226) - theWidth;
			// STRING: POPCAPGAME1 0x005d5a78
			theY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp144,734", 0x32);
		}
	}
	else {
		if ((aWidgetManager->mKeyDown[0x48] == 10) && (aWidgetManager->mKeyDown[0x94])) {
			theY = aWidgetManager->mY +
				   ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp140,723", 0x8c);
		}
		else {
			theY = aWidgetManager->mY +
				   ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp141,725", 0);
		}

		theX = aWidgetManager->mX / 2 - aWidgetManager->mWidth / 2;
	}

	theDialog->Resize(theX, theY, theWidth, aPreferredHeight);
}

// FUNCTION: POPCAPGAME1 0x004936b0
long double Sexy::GetLoadTime(int param_1)
{
	long double lVar1;

	switch (param_1) {
	case 0:
		lVar1 = (long double) 0;
		break;
	case 1:
		lVar1 = (long double) 0.007;
		break;
	case 2:
		lVar1 = (long double) 0.013;
		break;
	case 3:
		lVar1 = (long double) 0.018;
		break;
	case 4:
		lVar1 = (long double) 0.022;
		break;
	case 5:
		lVar1 = (long double) 0.023;
		break;
	case 6:
		lVar1 = (long double) 0.417;
		break;
	case 7:
		lVar1 = (long double) 0.418;
		break;
	case 8:
		lVar1 = (long double) 0.425;
		break;
	case 9:
		lVar1 = (long double) 0.431;
		break;
	case 10:
		lVar1 = (long double) 0.432;
		break;
	case 0xb:
		lVar1 = (long double) 0.436;
		break;
	case 0xc:
		lVar1 = (long double) 0.443;
		break;
	case 0xd:
		lVar1 = (long double) 0.454;
		break;
	case 0xe:
		lVar1 = (long double) 0.454;
		break;
	case 0xf:
		lVar1 = (long double) 0.455;
		break;
	case 0x10:
		lVar1 = (long double) 0.455;
		break;
	case 0x11:
		lVar1 = (long double) 0.455;
		break;
	case 0x12:
		lVar1 = (long double) 0.455;
		break;
	case 0x13:
		lVar1 = (long double) 0.455;
		break;
	case 0x14:
		lVar1 = (long double) 0.455;
		break;
	case 0x15:
		lVar1 = (long double) 0.455;
		break;
	case 0x16:
		lVar1 = (long double) 0.461;
		break;
	case 0x17:
		lVar1 = (long double) 0.461;
		break;
	case 0x18:
		lVar1 = (long double) 0.461;
		break;
	case 0x19:
		lVar1 = (long double) 0.461;
		break;
	case 0x1a:
		lVar1 = (long double) 0.461;
		break;
	case 0x1b:
		lVar1 = (long double) 0.461;
		break;
	case 0x1c:
		lVar1 = (long double) 0.461;
		break;
	case 0x1d:
		lVar1 = (long double) 0.463;
		break;
	case 0x1e:
		lVar1 = (long double) 0.464;
		break;
	case 0x1f:
		lVar1 = (long double) 0.464;
		break;
	case 0x20:
		lVar1 = (long double) 0.464;
		break;
	case 0x21:
		lVar1 = (long double) 0.464;
		break;
	case 0x22:
		lVar1 = (long double) 0.465;
		break;
	case 0x23:
		lVar1 = (long double) 0.465;
		break;
	case 0x24:
		lVar1 = (long double) 0.465;
		break;
	case 0x25:
		lVar1 = (long double) 0.465;
		break;
	case 0x26:
		lVar1 = (long double) 0.465;
		break;
	case 0x27:
		lVar1 = (long double) 0.465;
		break;
	case 0x28:
		lVar1 = (long double) 0.465;
		break;
	case 0x29:
		lVar1 = (long double) 0.466;
		break;
	case 0x2a:
		lVar1 = (long double) 0.466;
		break;
	case 0x2b:
		lVar1 = (long double) 0.466;
		break;
	case 0x2c:
		lVar1 = (long double) 0.466;
		break;
	case 0x2d:
		lVar1 = (long double) 0.466;
		break;
	case 0x2e:
		lVar1 = (long double) 0.468;
		break;
	case 0x2f:
		lVar1 = (long double) 0.468;
		break;
	case 0x30:
		lVar1 = (long double) 0.468;
		break;
	case 0x31:
		lVar1 = (long double) 0.468;
		break;
	case 0x32:
		lVar1 = (long double) 0.468;
		break;
	case 0x33:
		lVar1 = (long double) 0.469;
		break;
	case 0x34:
		lVar1 = (long double) 0.469;
		break;
	case 0x35:
		lVar1 = (long double) 0.469;
		break;
	case 0x36:
		lVar1 = (long double) 0.47;
		break;
	case 0x37:
		lVar1 = (long double) 0.472;
		break;
	case 0x38:
		lVar1 = (long double) 0.472;
		break;
	case 0x39:
		lVar1 = (long double) 0.472;
		break;
	case 0x3a:
		lVar1 = (long double) 0.472;
		break;
	case 0x3b:
		lVar1 = (long double) 0.472;
		break;
	case 0x3c:
		lVar1 = (long double) 0.472;
		break;
	case 0x3d:
		lVar1 = (long double) 0.473;
		break;
	case 0x3e:
		lVar1 = (long double) 0.473;
		break;
	case 0x3f:
		lVar1 = (long double) 0.473;
		break;
	case 0x40:
		lVar1 = (long double) 0.474;
		break;
	case 0x41:
		lVar1 = (long double) 0.474;
		break;
	case 0x42:
		lVar1 = (long double) 0.475;
		break;
	case 0x43:
		lVar1 = (long double) 0.476;
		break;
	case 0x44:
		lVar1 = (long double) 0.477;
		break;
	case 0x45:
		lVar1 = (long double) 0.477;
		break;
	case 0x46:
		lVar1 = (long double) 0.478;
		break;
	case 0x47:
		lVar1 = (long double) 0.478;
		break;
	case 0x48:
		lVar1 = (long double) 0.478;
		break;
	case 0x49:
		lVar1 = (long double) 0.478;
		break;
	case 0x4a:
		lVar1 = (long double) 0.478;
		break;
	case 0x4b:
		lVar1 = (long double) 0.479;
		break;
	case 0x4c:
		lVar1 = (long double) 0.479;
		break;
	case 0x4d:
		lVar1 = (long double) 0.479;
		break;
	case 0x4e:
		lVar1 = (long double) 0.481;
		break;
	case 0x4f:
		lVar1 = (long double) 0.482;
		break;
	case 0x50:
		lVar1 = (long double) 0.482;
		break;
	case 0x51:
		lVar1 = (long double) 0.482;
		break;
	case 0x52:
		lVar1 = (long double) 0.484;
		break;
	case 0x53:
		lVar1 = (long double) 0.484;
		break;
	case 0x54:
		lVar1 = (long double) 0.485;
		break;
	case 0x55:
		lVar1 = (long double) 0.485;
		break;
	case 0x56:
		lVar1 = (long double) 0.486;
		break;
	case 0x57:
		lVar1 = (long double) 0.486;
		break;
	case 0x58:
		lVar1 = (long double) 0.487;
		break;
	case 0x59:
		lVar1 = (long double) 0.489;
		break;
	case 0x5a:
		lVar1 = (long double) 0.489;
		break;
	case 0x5b:
		lVar1 = (long double) 0.49;
		break;
	case 0x5c:
		lVar1 = (long double) 0.49;
		break;
	case 0x5d:
		lVar1 = (long double) 0.49;
		break;
	case 0x5e:
		lVar1 = (long double) 0.49;
		break;
	case 0x5f:
		lVar1 = (long double) 0.49;
		break;
	case 0x60:
		lVar1 = (long double) 0.49;
		break;
	case 0x61:
		lVar1 = (long double) 0.49;
		break;
	case 0x62:
		lVar1 = (long double) 0.491;
		break;
	case 99:
		lVar1 = (long double) 0.492;
		break;
	case 100:
		lVar1 = (long double) 0.492;
		break;
	case 0x65:
		lVar1 = (long double) 0.492;
		break;
	case 0x66:
		lVar1 = (long double) 0.492;
		break;
	case 0x67:
		lVar1 = (long double) 0.493;
		break;
	case 0x68:
		lVar1 = (long double) 0.493;
		break;
	case 0x69:
		lVar1 = (long double) 0.494;
		break;
	case 0x6a:
		lVar1 = (long double) 0.494;
		break;
	case 0x6b:
		lVar1 = (long double) 0.494;
		break;
	case 0x6c:
		lVar1 = (long double) 0.494;
		break;
	case 0x6d:
		lVar1 = (long double) 0.494;
		break;
	case 0x6e:
		lVar1 = (long double) 0.494;
		break;
	case 0x6f:
		lVar1 = (long double) 0.494;
		break;
	case 0x70:
		lVar1 = (long double) 0.494;
		break;
	case 0x71:
		lVar1 = (long double) 0.495;
		break;
	case 0x72:
		lVar1 = (long double) 0.495;
		break;
	case 0x73:
		lVar1 = (long double) 0.495;
		break;
	case 0x74:
		lVar1 = (long double) 0.495;
		break;
	case 0x75:
		lVar1 = (long double) 0.495;
		break;
	case 0x76:
		lVar1 = (long double) 0.497;
		break;
	case 0x77:
		lVar1 = (long double) 0.497;
		break;
	case 0x78:
		lVar1 = (long double) 0.497;
		break;
	case 0x79:
		lVar1 = (long double) 0.498;
		break;
	case 0x7a:
		lVar1 = (long double) 0.498;
		break;
	case 0x7b:
		lVar1 = (long double) 0.498;
		break;
	case 0x7c:
		lVar1 = (long double) 0.498;
		break;
	case 0x7d:
		lVar1 = (long double) 0.498;
		break;
	case 0x7e:
		lVar1 = (long double) 0.498;
		break;
	case 0x7f:
		lVar1 = (long double) 0.498;
		break;
	case 0x80:
		lVar1 = (long double) 0.498;
		break;
	case 0x81:
		lVar1 = (long double) 0.5;
		break;
	case 0x82:
		lVar1 = (long double) 0.5;
		break;
	case 0x83:
		lVar1 = (long double) 0.5;
		break;
	case 0x84:
		lVar1 = (long double) 0.5;
		break;
	case 0x85:
		lVar1 = (long double) 0.5;
		break;
	case 0x86:
		lVar1 = (long double) 0.5;
		break;
	case 0x87:
		lVar1 = (long double) 0.501;
		break;
	case 0x88:
		lVar1 = (long double) 0.501;
		break;
	case 0x89:
		lVar1 = (long double) 0.501;
		break;
	case 0x8a:
		lVar1 = (long double) 0.501;
		break;
	case 0x8b:
		lVar1 = (long double) 0.503;
		break;
	case 0x8c:
		lVar1 = (long double) 0.503;
		break;
	case 0x8d:
		lVar1 = (long double) 0.504;
		break;
	case 0x8e:
		lVar1 = (long double) 0.504;
		break;
	case 0x8f:
		lVar1 = (long double) 0.508;
		break;
	case 0x90:
		lVar1 = (long double) 0.511;
		break;
	case 0x91:
		lVar1 = (long double) 0.513;
		break;
	case 0x92:
		lVar1 = (long double) 0.513;
		break;
	case 0x93:
		lVar1 = (long double) 0.513;
		break;
	case 0x94:
		lVar1 = (long double) 0.513;
		break;
	case 0x95:
		lVar1 = (long double) 0.514;
		break;
	case 0x96:
		lVar1 = (long double) 0.514;
		break;
	case 0x97:
		lVar1 = (long double) 0.516;
		break;
	case 0x98:
		lVar1 = (long double) 0.517;
		break;
	case 0x99:
		lVar1 = (long double) 0.517;
		break;
	case 0x9a:
		lVar1 = (long double) 0.517;
		break;
	case 0x9b:
		lVar1 = (long double) 0.518;
		break;
	case 0x9c:
		lVar1 = (long double) 0.518;
		break;
	case 0x9d:
		lVar1 = (long double) 0.519;
		break;
	case 0x9e:
		lVar1 = (long double) 0.52;
		break;
	case 0x9f:
		lVar1 = (long double) 0.521;
		break;
	case 0xa0:
		lVar1 = (long double) 0.522;
		break;
	case 0xa1:
		lVar1 = (long double) 0.522;
		break;
	case 0xa2:
		lVar1 = (long double) 0.533;
		break;
	case 0xa3:
		lVar1 = (long double) 0.534;
		break;
	case 0xa4:
		lVar1 = (long double) 0.544;
		break;
	case 0xa5:
		lVar1 = (long double) 0.544;
		break;
	case 0xa6:
		lVar1 = (long double) 0.544;
		break;
	case 0xa7:
		lVar1 = (long double) 0.546;
		break;
	case 0xa8:
		lVar1 = (long double) 0.546;
		break;
	case 0xa9:
		lVar1 = (long double) 0.547;
		break;
	case 0xaa:
		lVar1 = (long double) 0.547;
		break;
	case 0xab:
		lVar1 = (long double) 0.552;
		break;
	case 0xac:
		lVar1 = (long double) 0.555;
		break;
	case 0xad:
		lVar1 = (long double) 0.557;
		break;
	case 0xae:
		lVar1 = (long double) 0.561;
		break;
	case 0xaf:
		lVar1 = (long double) 0.574;
		break;
	case 0xb0:
		lVar1 = (long double) 0.59;
		break;
	case 0xb1:
		lVar1 = (long double) 0.593;
		break;
	case 0xb2:
		lVar1 = (long double) 0.597;
		break;
	case 0xb3:
		lVar1 = (long double) 0.597;
		break;
	case 0xb4:
		lVar1 = (long double) 0.6;
		break;
	case 0xb5:
		lVar1 = (long double) 0.6;
		break;
	case 0xb6:
		lVar1 = (long double) 0.6;
		break;
	case 0xb7:
		lVar1 = (long double) 0.6;
		break;
	case 0xb8:
		lVar1 = (long double) 0.6;
		break;
	case 0xb9:
		lVar1 = (long double) 0.6;
		break;
	case 0xba:
		lVar1 = (long double) 0.6;
		break;
	case 0xbb:
		lVar1 = (long double) 0.6;
		break;
	case 0xbc:
		lVar1 = (long double) 0.601;
		break;
	case 0xbd:
		lVar1 = (long double) 0.601;
		break;
	case 0xbe:
		lVar1 = (long double) 0.601;
		break;
	case 0xbf:
		lVar1 = (long double) 0.602;
		break;
	case 0xc0:
		lVar1 = (long double) 0.622;
		break;
	case 0xc1:
		lVar1 = (long double) 0.622;
		break;
	case 0xc2:
		lVar1 = (long double) 0.63;
		break;
	case 0xc3:
		lVar1 = (long double) 0.63;
		break;
	case 0xc4:
		lVar1 = (long double) 0.633;
		break;
	case 0xc5:
		lVar1 = (long double) 0.635;
		break;
	case 0xc6:
		lVar1 = (long double) 0.641;
		break;
	case 199:
		lVar1 = (long double) 0.648;
		break;
	case 200:
		lVar1 = (long double) 0.652;
		break;
	case 0xc9:
		lVar1 = (long double) 0.652;
		break;
	case 0xca:
		lVar1 = (long double) 0.654;
		break;
	case 0xcb:
		lVar1 = (long double) 0.654;
		break;
	case 0xcc:
		lVar1 = (long double) 0.654;
		break;
	case 0xcd:
		lVar1 = (long double) 0.665;
		break;
	case 0xce:
		lVar1 = (long double) 0.666;
		break;
	case 0xcf:
		lVar1 = (long double) 0.667;
		break;
	case 0xd0:
		lVar1 = (long double) 0.675;
		break;
	case 0xd1:
		lVar1 = (long double) 0.676;
		break;
	case 0xd2:
		lVar1 = (long double) 0.679;
		break;
	case 0xd3:
		lVar1 = (long double) 0.682;
		break;
	case 0xd4:
		lVar1 = (long double) 0.683;
		break;
	case 0xd5:
		lVar1 = (long double) 0.684;
		break;
	case 0xd6:
		lVar1 = (long double) 0.71;
		break;
	case 0xd7:
		lVar1 = (long double) 0.71;
		break;
	case 0xd8:
		lVar1 = (long double) 0.711;
		break;
	case 0xd9:
		lVar1 = (long double) 0.714;
		break;
	case 0xda:
		lVar1 = (long double) 0.715;
		break;
	case 0xdb:
		lVar1 = (long double) 0.715;
		break;
	case 0xdc:
		lVar1 = (long double) 0.715;
		break;
	case 0xdd:
		lVar1 = (long double) 0.717;
		break;
	case 0xde:
		lVar1 = (long double) 0.718;
		break;
	case 0xdf:
		lVar1 = (long double) 0.718;
		break;
	case 0xe0:
		lVar1 = (long double) 0.72;
		break;
	case 0xe1:
		lVar1 = (long double) 0.733;
		break;
	case 0xe2:
		lVar1 = (long double) 0.733;
		break;
	case 0xe3:
		lVar1 = (long double) 0.746;
		break;
	case 0xe4:
		lVar1 = (long double) 0.748;
		break;
	case 0xe5:
		lVar1 = (long double) 0.749;
		break;
	case 0xe6:
		lVar1 = (long double) 0.75;
		break;
	case 0xe7:
		lVar1 = (long double) 0.75;
		break;
	case 0xe8:
		lVar1 = (long double) 0.75;
		break;
	case 0xe9:
		lVar1 = (long double) 0.752;
		break;
	case 0xea:
		lVar1 = (long double) 0.753;
		break;
	case 0xeb:
		lVar1 = (long double) 0.753;
		break;
	case 0xec:
		lVar1 = (long double) 0.753;
		break;
	case 0xed:
		lVar1 = (long double) 0.753;
		break;
	case 0xee:
		lVar1 = (long double) 0.753;
		break;
	case 0xef:
		lVar1 = (long double) 0.754;
		break;
	case 0xf0:
		lVar1 = (long double) 0.754;
		break;
	case 0xf1:
		lVar1 = (long double) 0.754;
		break;
	case 0xf2:
		lVar1 = (long double) 0.755;
		break;
	case 0xf3:
		lVar1 = (long double) 0.755;
		break;
	case 0xf4:
		lVar1 = (long double) 0.755;
		break;
	case 0xf5:
		lVar1 = (long double) 0.756;
		break;
	case 0xf6:
		lVar1 = (long double) 0.756;
		break;
	case 0xf7:
		lVar1 = (long double) 0.766;
		break;
	case 0xf8:
		lVar1 = (long double) 0.767;
		break;
	case 0xf9:
		lVar1 = (long double) 0.767;
		break;
	case 0xfa:
		lVar1 = (long double) 0.767;
		break;
	case 0xfb:
		lVar1 = (long double) 0.767;
		break;
	case 0xfc:
		lVar1 = (long double) 0.767;
		break;
	case 0xfd:
		lVar1 = (long double) 0.767;
		break;
	case 0xfe:
		lVar1 = (long double) 0.767;
		break;
	case 0xff:
		lVar1 = (long double) 0.768;
		break;
	case 0x100:
		lVar1 = (long double) 0.768;
		break;
	case 0x101:
		lVar1 = (long double) 0.768;
		break;
	case 0x102:
		lVar1 = (long double) 0.77;
		break;
	case 0x103:
		lVar1 = (long double) 0.77;
		break;
	case 0x104:
		lVar1 = (long double) 0.77;
		break;
	case 0x105:
		lVar1 = (long double) 0.771;
		break;
	case 0x106:
		lVar1 = (long double) 0.773;
		break;
	case 0x107:
		lVar1 = (long double) 0.779;
		break;
	case 0x108:
		lVar1 = (long double) 0.782;
		break;
	case 0x109:
		lVar1 = (long double) 0.785;
		break;
	case 0x10a:
		lVar1 = (long double) 0.786;
		break;
	case 0x10b:
		lVar1 = (long double) 0.786;
		break;
	case 0x10c:
		lVar1 = (long double) 0.789;
		break;
	case 0x10d:
		lVar1 = (long double) 0.789;
		break;
	case 0x10e:
		lVar1 = (long double) 0.791;
		break;
	case 0x10f:
		lVar1 = (long double) 0.793;
		break;
	case 0x110:
		lVar1 = (long double) 0.794;
		break;
	case 0x111:
		lVar1 = (long double) 0.801;
		break;
	case 0x112:
		lVar1 = (long double) 0.807;
		break;
	case 0x113:
		lVar1 = (long double) 0.808;
		break;
	case 0x114:
		lVar1 = (long double) 0.813;
		break;
	case 0x115:
		lVar1 = (long double) 0.815;
		break;
	case 0x116:
		lVar1 = (long double) 0.818;
		break;
	case 0x117:
		lVar1 = (long double) 0.821;
		break;
	case 0x118:
		lVar1 = (long double) 0.821;
		break;
	case 0x119:
		lVar1 = (long double) 0.822;
		break;
	case 0x11a:
		lVar1 = (long double) 0.824;
		break;
	case 0x11b:
		lVar1 = (long double) 0.833;
		break;
	case 0x11c:
		lVar1 = (long double) 0.836;
		break;
	case 0x11d:
		lVar1 = (long double) 0.837;
		break;
	case 0x11e:
		lVar1 = (long double) 0.837;
		break;
	case 0x11f:
		lVar1 = (long double) 0.837;
		break;
	case 0x120:
		lVar1 = (long double) 0.837;
		break;
	case 0x121:
		lVar1 = (long double) 0.839;
		break;
	case 0x122:
		lVar1 = (long double) 0.841;
		break;
	case 0x123:
		lVar1 = (long double) 0.842;
		break;
	case 0x124:
		lVar1 = (long double) 0.842;
		break;
	case 0x125:
		lVar1 = (long double) 0.842;
		break;
	case 0x126:
		lVar1 = (long double) 0.843;
		break;
	case 0x127:
		lVar1 = (long double) 0.843;
		break;
	case 0x128:
		lVar1 = (long double) 0.843;
		break;
	case 0x129:
		lVar1 = (long double) 0.843;
		break;
	case 0x12a:
		lVar1 = (long double) 0.843;
		break;
	case 299:
		lVar1 = (long double) 0.843;
		break;
	case 300:
		lVar1 = (long double) 0.846;
		break;
	case 0x12d:
		lVar1 = (long double) 0.846;
		break;
	case 0x12e:
		lVar1 = (long double) 0.846;
		break;
	case 0x12f:
		lVar1 = (long double) 0.846;
		break;
	case 0x130:
		lVar1 = (long double) 0.846;
		break;
	case 0x131:
		lVar1 = (long double) 0.846;
		break;
	case 0x132:
		lVar1 = (long double) 0.847;
		break;
	case 0x133:
		lVar1 = (long double) 0.847;
		break;
	case 0x134:
		lVar1 = (long double) 0.847;
		break;
	case 0x135:
		lVar1 = (long double) 0.849;
		break;
	case 0x136:
		lVar1 = (long double) 0.849;
		break;
	case 0x137:
		lVar1 = (long double) 0.849;
		break;
	case 0x138:
		lVar1 = (long double) 0.852;
		break;
	case 0x139:
		lVar1 = (long double) 0.852;
		break;
	case 0x13a:
		lVar1 = (long double) 0.853;
		break;
	case 0x13b:
		lVar1 = (long double) 0.854;
		break;
	case 0x13c:
		lVar1 = (long double) 0.856;
		break;
	case 0x13d:
		lVar1 = (long double) 0.856;
		break;
	case 0x13e:
		lVar1 = (long double) 0.856;
		break;
	case 0x13f:
		lVar1 = (long double) 0.856;
		break;
	case 0x140:
		lVar1 = (long double) 0.856;
		break;
	case 0x141:
		lVar1 = (long double) 0.857;
		break;
	case 0x142:
		lVar1 = (long double) 0.857;
		break;
	case 0x143:
		lVar1 = (long double) 0.858;
		break;
	case 0x144:
		lVar1 = (long double) 0.859;
		break;
	case 0x145:
		lVar1 = (long double) 0.86;
		break;
	case 0x146:
		lVar1 = (long double) 0.86;
		break;
	case 0x147:
		lVar1 = (long double) 0.861;
		break;
	case 0x148:
		lVar1 = (long double) 0.863;
		break;
	case 0x149:
		lVar1 = (long double) 0.863;
		break;
	case 0x14a:
		lVar1 = (long double) 0.863;
		break;
	case 0x14b:
		lVar1 = (long double) 0.865;
		break;
	case 0x14c:
		lVar1 = (long double) 0.867;
		break;
	case 0x14d:
		lVar1 = (long double) 0.868;
		break;
	case 0x14e:
		lVar1 = (long double) 0.871;
		break;
	case 0x14f:
		lVar1 = (long double) 0.872;
		break;
	case 0x150:
		lVar1 = (long double) 0.874;
		break;
	case 0x151:
		lVar1 = (long double) 0.876;
		break;
	case 0x152:
		lVar1 = (long double) 0.878;
		break;
	case 0x153:
		lVar1 = (long double) 0.881;
		break;
	case 0x154:
		lVar1 = (long double) 0.882;
		break;
	case 0x155:
		lVar1 = (long double) 0.885;
		break;
	case 0x156:
		lVar1 = (long double) 0.886;
		break;
	case 0x157:
		lVar1 = (long double) 0.886;
		break;
	case 0x158:
		lVar1 = (long double) 0.886;
		break;
	case 0x159:
		lVar1 = (long double) 0.89;
		break;
	case 0x15a:
		lVar1 = (long double) 0.891;
		break;
	case 0x15b:
		lVar1 = (long double) 0.892;
		break;
	case 0x15c:
		lVar1 = (long double) 0.892;
		break;
	case 0x15d:
		lVar1 = (long double) 0.893;
		break;
	case 0x15e:
		lVar1 = (long double) 0.894;
		break;
	case 0x15f:
		lVar1 = (long double) 0.896;
		break;
	case 0x160:
		lVar1 = (long double) 0.898;
		break;
	case 0x161:
		lVar1 = (long double) 0.898;
		break;
	case 0x162:
		lVar1 = (long double) 0.898;
		break;
	case 0x163:
		lVar1 = (long double) 0.905;
		break;
	case 0x164:
		lVar1 = (long double) 0.914;
		break;
	case 0x165:
		lVar1 = (long double) 0.92;
		break;
	case 0x166:
		lVar1 = (long double) 0.929;
		break;
	case 0x167:
		lVar1 = (long double) 0.936;
		break;
	case 0x168:
		lVar1 = (long double) 0.944;
		break;
	case 0x169:
		lVar1 = (long double) 0.951;
		break;
	case 0x16a:
		lVar1 = (long double) 0.958;
		break;
	case 0x16b:
		lVar1 = (long double) 0.966;
		break;
	case 0x16c:
		lVar1 = (long double) 0.974;
		break;
	case 0x16d:
		lVar1 = (long double) 0.978;
		break;
	case 0x16e:
		lVar1 = (long double) 0.978;
		break;
	case 0x16f:
		lVar1 = (long double) 0.982;
		break;
	case 0x170:
		lVar1 = (long double) 0.984;
		break;
	case 0x171:
		lVar1 = (long double) 0.985;
		break;
	case 0x172:
		lVar1 = (long double) 0.987;
		break;
	case 0x173:
		lVar1 = (long double) 0.988;
		break;
	case 0x174:
		lVar1 = (long double) 0.989;
		break;
	case 0x175:
		lVar1 = (long double) 0.991;
		break;
	case 0x176:
		lVar1 = (long double) 0.992;
		break;
	case 0x177:
		lVar1 = (long double) 0.993;
		break;
	case 0x178:
		lVar1 = (long double) 0.994;
		break;
	case 0x179:
		lVar1 = (long double) 0.996;
		break;
	case 0x17a:
		lVar1 = (long double) 0.997;
		break;
	case 0x17b:
	case 0x17c:
		lVar1 = (long double) 0.998;
		break;
	default:
		lVar1 = (long double) 1;
	}
	return lVar1;
}

// FUNCTION: POPCAPGAME1 0x004942f0
bool Sexy::SolveLinearSystem(float a, float b, float e, float c, float d, float f, float* outX, float* outY)
{
	float det = (a * d) - (b * c);

	if (det == 0.0f) {
		return false;
	}

	float numX = (e * d) - (f * b);
	*outX = numX / det;

	float numY = (a * f) - (e * c);
	*outY = numY / det;

	return true;
}

// FUNCTION: POPCAPGAME1 0x004bc4b0
float Sexy::InterpValF(
	int currentTime,
	int phase1Duration,
	int phase2Duration,
	float startVal,
	float midVal,
	float endVal
)
{
	if (currentTime < phase1Duration) {
		float t = (float) currentTime / (float) phase1Duration;
		return (1.0f - t) * startVal + (t * midVal);
	}

	int totalTimePhase1And2 = phase2Duration + phase1Duration;
	if (currentTime < totalTimePhase1And2) {
		float t = (float) (currentTime - phase1Duration) / (float) phase2Duration;
		return (1.0f - t) * midVal + (t * endVal);
	}

	return endVal;
}

// STUB: POPCAPGAME1 0x00404b70
int Sexy::GetStyleShotScore(Sexy::StyleShot, bool, int)
{
	return 0;
}

// FUNCTION: POPCAPGAME1 0x00407d90
ThunderButton* Sexy::MakeEmbeddedButton(int theId, ButtonListener* theListener, Image* theImage, bool param_4)
{
	int aBtnWidth = theImage->mWidth;
	int aBtnHeight = theImage->mHeight;

	if (theImage->mNumCols > 1) {
		aBtnWidth /= 2;
	}
	else {
		aBtnHeight /= 2;
	}

	if (param_4 && theImage->mNumRows == 1 && theImage->mNumCols == 1) {
		aBtnHeight = theImage->mHeight;
		aBtnWidth = theImage->mWidth;
	}

	ThunderButton* aBtn = new ThunderButton(theImage, theId, theListener);

	aBtn->mWidth = aBtnWidth;
	aBtn->mHeight = aBtnHeight;

	aBtn->mUnk0x15c = 0x11;
	aBtn->mClickSound = SOUND_BUTTON1;

	aBtn->mNormalRect.mWidth = 1;
	aBtn->mNormalRect.mHeight = 0;

	if (aBtnHeight != theImage->mHeight) {
		aBtn->mOverRect = Rect(0, 0, aBtnWidth, aBtnHeight);
		aBtn->mDownRect = Rect(0, aBtnHeight, aBtnWidth, aBtnHeight);
	}
	else {
		aBtn->mOverRect = Rect(0, 0, aBtnWidth, aBtnHeight);
		aBtn->mDownRect = Rect(aBtnWidth, 0, aBtnWidth, aBtnHeight);
	}

	if (param_4) {
		aBtn->mUnk0x159 = true;
		aBtn->mDownRect = aBtn->mOverRect;
	}

	return aBtn;
}

// FUNCTION: POPCAPGAME1 0x00407c40
void Sexy::SetupButton(DialogButton* theButton, bool param_2)
{
	if (theButton != NULL) {
		int aImageWidth = theButton->mComponentImage->mWidth;
		int aImageHeight = theButton->mComponentImage->mHeight;

		if (param_2) {
			aImageWidth /= 3;
			theButton->mNormalRect = Rect(0, 0, aImageWidth, aImageHeight);
			theButton->mOverRect = Rect(aImageWidth, 0, aImageWidth, aImageHeight);
			theButton->mDownRect = Rect(aImageWidth * 2, 0, aImageWidth, aImageHeight);
		}
		else {
			aImageHeight /= 3;
			theButton->mNormalRect = Rect(0, 0, aImageWidth, aImageHeight);
			theButton->mOverRect = Rect(0, aImageHeight, aImageWidth, aImageHeight);
			theButton->mDownRect = Rect(0, aImageHeight * 2, aImageWidth, aImageHeight);
		}

		theButton->SetFont(FONT_BUTTON);
		theButton->mTextOffsetY =
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp131,504", 5);
		Color aColor0 = Color(0xffffff);
		theButton->SetColor(0, aColor0);
		Color aColor1 = Color(0xffffff);
		theButton->SetColor(1, aColor1);
	}
}

// FUNCTION: POPCAPGAME1 0x0041bc70
ThunderButton* Sexy::MakeButton(int theId, ButtonListener* theListener, const std::string& theString, Image* theImage)
{
	if (theImage == NULL) {
		theImage = IMAGE_DLG_BUTTON3;
	}

	ThunderButton* aBtn = new ThunderButton(theImage, theId, theListener);
	aBtn->mLabel = theString;
	aBtn->mWidth = aBtn->mComponentImage->mWidth;
	aBtn->mHeight = aBtn->mComponentImage->mHeight / 3;

	if (theImage == IMAGE_DLG_BROWNBUTTON1 || theImage == IMAGE_DLG_BROWNBUTTON2) {
		aBtn->mUnk0x15c = 0;
	}
	else {
		aBtn->mUnk0x15c = 3;
	}

	aBtn->mClickSound = SOUND_BUTTON1;
	SetupButton(static_cast<DialogButton*>(aBtn), false);
	return aBtn;
}

// FUNCTION: POPCAPGAME1 0x0041bd60
ThunderButton* Sexy::MakePurpleButton(int theId, ButtonListener* theListener, const std::string& theString)
{
	ThunderButton* aBtn = MakeButton(theId, theListener, theString, IMAGE_DLG_PURPLEBUTTON);
	aBtn->mUnk0x15c = 10;
	aBtn->mTextOffsetX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp132,539", 0);
	aBtn->mTextOffsetY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp133,540", 5);
	return aBtn;
}

// FUNCTION: POPCAPGAME1 0x00405270
SimpleButton* Sexy::MakeSimpleButton(int theId, ButtonListener* theListener, Image* theImage, int param_4, int param_5)
{
	SimpleButton* aBtn = new SimpleButton(theImage, theId, theListener);
	aBtn->mWidth = theImage->mWidth + param_4;
	aBtn->mHeight = theImage->mHeight + param_5;
	return aBtn;
}

// FUNCTION: POPCAPGAME1 0x00405330
void Sexy::SetupEditWidget(EditWidget* theEditWidget)
{
	theEditWidget->SetFont(FONT_PLAIN);
	theEditWidget->SetColor(0, Color(0, 0));
	theEditWidget->SetColor(1, Color(0, 0));
	theEditWidget->SetColor(
		2,
		Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp150,792", 0))
	);
	theEditWidget->SetColor(
		3,
		Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp151,793", 128))
	);
	theEditWidget->SetColor(
		4,
		Color(ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp152,794", 0xffffff))
	);
	theEditWidget->mHeight = 0x18;
}

// FUNCTION: POPCAPGAME1 0x00405420
EditWidget* Sexy::CreateEditWidget(int theId, EditListener* theListener)
{
	EditWidget* aEditWidget = new EditWidget(theId, theListener);
	SetupEditWidget(aEditWidget);
	return aEditWidget;
}

void Sexy::DoNameWidthEnforce(EditWidget* theEditWidget)
{
	theEditWidget->mMaxChars = 12;
	theEditWidget->AddWidthCheckFont(
		FONT_OVERLOAD24,
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp149,781", 0xbe)
	);
}

void Sexy::DrawEditBox(Graphics* g, EditWidget* theEditWidget)
{
	theEditWidget->Draw(g);
}

// FUNCTION: POPCAPGAME1 0x00497220
ThunderButton* Sexy::MakeButtonCopy(DialogButton* theButton)
{
	if (theButton == NULL) {
		return NULL;
	}
	else {
		ThunderButton* aBtn = MakeButton(theButton->mId, theButton->mButtonListener, theButton->mLabel, NULL);
		aBtn->Resize(theButton->mX, theButton->mY, theButton->mWidth, theButton->mHeight);
		delete theButton;
		return aBtn;
	}
}

// FUNCTION: POPCAPGAME1 0x004066f0
int Sexy::Clamp(int val, int minVal, int maxVal)
{
	if (val < minVal) {
		return minVal;
	}
	if (val > maxVal) {
		return maxVal;
	}
	return val;
}

// FUNCTION: POPCAPGAME1 0x00407ef0
ThunderCheckbox* Sexy::MakeCheckbox(int theId, CheckboxListener* theListener, int param_3)
{
	int aWidth;
	int aHeight;
	ThunderCheckbox* aCheckbox;

	if (param_3 == 0) {
		aWidth = IMAGE_DLG_BUTTON1->mWidth;
		aHeight = IMAGE_DLG_BUTTON1->mHeight / 4;
		aCheckbox = new ThunderCheckbox(IMAGE_DLG_BUTTON1, IMAGE_DLG_BUTTON1, theId, theListener);

		aCheckbox->mCheckedRect.mX = 0;
		aCheckbox->mCheckedRect.mY = 0;
		aCheckbox->mUncheckedRect.mX = 0;
		aCheckbox->mUncheckedHilightRect.mX = 0;
		aCheckbox->mCheckedHilightRect.mX = 0;
		aCheckbox->mUncheckedRect.mY = aHeight * 2;
		aCheckbox->mUncheckedHilightRect.mY = aHeight;
		aCheckbox->mCheckedHilightRect.mY = aHeight * 3;
		aCheckbox->mCheckedRect.mWidth = aWidth;
		aCheckbox->mUncheckedHilightRect.mWidth = aWidth;
		aCheckbox->mUncheckedRect.mWidth = aWidth;
		aCheckbox->mCheckedHilightRect.mWidth = aWidth;
		aCheckbox->mCheckedRect.mHeight = aHeight;
		aCheckbox->mUncheckedHilightRect.mHeight = aHeight;
		aCheckbox->mUncheckedRect.mHeight = aHeight;
		aCheckbox->mCheckedHilightRect.mHeight = aHeight;

		aCheckbox->mUnk0x114 =
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp134,637", 0x28);
		aCheckbox->mUnk0x118 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp135,638", 2);

		aCheckbox->mUnk0x11c = param_3;
		aCheckbox->mUnk0x10c = SOUND_BUTTON2;
	}
	else if (param_3 == 1) {
		aWidth = IMAGE_DLG_BUTTON2->mWidth;
		aHeight = IMAGE_DLG_BUTTON2->mHeight / 3;
		aCheckbox = new ThunderCheckbox(IMAGE_DLG_BUTTON2, IMAGE_DLG_BUTTON2, theId, theListener);

		aCheckbox->mCheckedRect.mX = 0;
		aCheckbox->mCheckedRect.mY = 0;
		aCheckbox->mUncheckedRect.mX = 0;
		aCheckbox->mUncheckedHilightRect.mX = 0;
		aCheckbox->mCheckedHilightRect.mX = 0;
		aCheckbox->mUncheckedRect.mY = aHeight * 2;
		aCheckbox->mUncheckedHilightRect.mY = aHeight;
		aCheckbox->mCheckedHilightRect.mY = 0;
		aCheckbox->mCheckedRect.mWidth = aWidth;
		aCheckbox->mUncheckedHilightRect.mWidth = aWidth;
		aCheckbox->mUncheckedRect.mWidth = aWidth;
		aCheckbox->mCheckedHilightRect.mWidth = aWidth;
		aCheckbox->mCheckedRect.mHeight = aHeight;
		aCheckbox->mUncheckedHilightRect.mHeight = aHeight;
		aCheckbox->mUncheckedRect.mHeight = aHeight;
		aCheckbox->mCheckedHilightRect.mHeight = 0;

		aCheckbox->mUnk0x114 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp136,652", 0);
		aCheckbox->mUnk0x118 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp137,653", 2);

		aCheckbox->mUnk0x11c = param_3;
		aCheckbox->mUnk0x10c = SOUND_BUTTON2;
	}
	else {
		return NULL;
	}

	aCheckbox->mUnk0x110 = true;
	aCheckbox->Resize(0, 0, aWidth, aHeight);
	aCheckbox->mChecked = true;

	return aCheckbox;
}

// FUNCTION: POPCAPGAME1 0x0041be70
ThunderCheckbox* Sexy::MakeCheckbox2(
	int theId,
	CheckboxListener* theListener,
	const std::string& theString,
	int param_4
)
{
	ThunderCheckbox* aCheckbox = MakeCheckbox(theId, theListener, param_4);

	aCheckbox->mLabel.assign(theString, 0, 0xffffffff);

	aCheckbox->mWidth = aCheckbox->mUnk0xec->StringWidth(theString);

	if (param_4 == 0) {
		// STRING: POPCAPGAME1 0x005d6848
		aCheckbox->mWidth += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp138,673", 0x3c);
	}
	else {
		// STRING: POPCAPGAME1 0x005d6800
		aCheckbox->mWidth += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\ThunderCommon.cpp139,675", 0x1e);
	}

	return aCheckbox;
}

// FUNCTION: POPCAPGAME1 0x0041bdc0
ThunderButton* Sexy::MakeBottomButton(int theId, ButtonListener* theListener, const std::string& theString)
{
	ThunderButton* aBtn = MakeButton(theId, theListener, theString, NULL);
	aBtn->mComponentImage = IMAGE_DLG_PLAYBUTTON1;
	aBtn->mWidth = IMAGE_DLG_PLAYBUTTON1->mWidth;
	aBtn->mHeight = IMAGE_DLG_PLAYBUTTON1->mHeight / 2;
	aBtn->mNormalRect.mHeight = 0;
	aBtn->mNormalRect.mWidth = 1;

	aBtn->mOverRect = Rect(0, 0, aBtn->mWidth, aBtn->mHeight / 2);
	aBtn->mDownRect = Rect(0, aBtn->mHeight / 2, aBtn->mWidth, aBtn->mHeight / 2);

	return aBtn;
}

// FUNCTION: POPCAPGAME1 0x00489d90
int Sexy::GetColorForCharacter(int param_1)
{
	switch (param_1) {
	case 0:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp189,1026", 0x88ffff);
	case 1:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp190,1027", 0x88ff88);
	case 2:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp191,1028", 0xffff88);
	case 3:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp192,1029", 0xa080ff);
	case 4:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp193,1030", 0x88ccff);
	case 5:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp194,1031", 0xffaa44);
	case 6:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp195,1032", 0xff88ff);
	case 7:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp196,1033", 0xff4444);
	case 8:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp197,1034", 0xff00);
	case 9:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp198,1035", 0xb6bcd6);
	default:
		return ModVal(0, "SEXY_SEXYMODVAL.\\StoryScreen.cpp199,1036", 0xffffff);
	}
}
