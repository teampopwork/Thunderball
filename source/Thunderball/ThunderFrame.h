#ifndef __THUNDERFRAME_H__
#define __THUNDERFRAME_H__

#include <SexyAppFramework/Widget.h>

namespace Sexy
{
class Graphics;

// VTABLE: POPCAPGAME1 0x005fc47c
class ThunderFrame : public Widget {
public:
	ThunderFrame();

	virtual void Draw(Graphics* g);
};
} // namespace Sexy

#endif // __THUNDERFRAME_H__
