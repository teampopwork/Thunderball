#include "Font.h"
#include "Image.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004cc850
Font::Font()
{	
	mAscent = 0;
	mHeight = 0;
	mAscentPadding = 0;
	mLineSpacingOffset = 0;
}

// FUNCTION: POPCAPGAME1 0x004cc870
Font::Font(const Font& theFont) :
	mAscent(theFont.mAscent),
	mHeight(theFont.mHeight),
	mAscentPadding(theFont.mAscentPadding),
	mLineSpacingOffset(theFont.mLineSpacingOffset)
{
}

// SYNTHETIC: POPCAPGAME1 0x004d7440
// Sexy::Font::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x004cc8a0
Font::~Font()
{
}

// FUNCTION: POPCAPGAME1 0x004cc8b0
int	Font::GetAscent()
{
	return mAscent;
}

// FUNCTION: POPCAPGAME1 0x004cc8c0
int	Font::GetAscentPadding()
{
	return mAscentPadding;
}

// FUNCTION: POPCAPGAME1 0x004cc8d0
int	Font::GetDescent()
{
	return mHeight - mAscent;
}

// FUNCTION: POPCAPGAME1 0x00556c50
int	Font::GetHeight()
{
	return mHeight;
}

// FUNCTION: POPCAPGAME1 0x004cc8e0
int Font::GetLineSpacingOffset()
{
	return mLineSpacingOffset;
}

// FUNCTION: POPCAPGAME1 0x004cc8f0
int Font::GetLineSpacing()
{
	return mHeight + mLineSpacingOffset;
}

// FUNCTION: POPCAPGAME1 0x004cc900
int Font::StringWidth(const SexyString& theString)
{
	return 0;
}

// FUNCTION: POPCAPGAME1 0x004de510
int Font::CharWidth(SexyChar theChar)
{
	SexyString aString(1, theChar);
	return StringWidth(aString);
}

// FUNCTION: POPCAPGAME1 0x004cc910
int Font::CharWidthKern(SexyChar theChar, SexyChar thePrevChar)
{
	return CharWidth(theChar);
}

void Font::DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect)
{
}
