#include "ThunderCommon.h"

#include "Res.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/ButtonWidget.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/Rect.h>

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

// STUB: POPCAPGAME1 0x000040bc20
void Sexy::PositionDialog(Dialog* param_1, int param_2, bool param_3, int param_4)
{
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
bool Sexy::SolveLinearSystem(float a, float b, float e, float c, float d, float f, float* outX, float* outY) {
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
float Sexy::Lerp(int currentTime, int phase1Duration, int phase2Duration, 
                      float startVal, float midVal, float endVal) 
{
    if (currentTime < phase1Duration) {
        float t = (float)currentTime / (float)phase1Duration;
        return (1.0f - t) * startVal + (t * midVal);
    }

    int totalTimePhase1And2 = phase2Duration + phase1Duration;
    if (currentTime < totalTimePhase1And2) {
        float t = (float)(currentTime - phase1Duration) / (float)phase2Duration;
        return (1.0f - t) * midVal + (t * endVal);
    }

    return endVal;
}

// STUB: POPCAPGAME1 0x00404b70
int Sexy::GetStyleShotScore(Sexy::StyleShot, bool, int) 
{
	return 0;
}