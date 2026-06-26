#ifndef __BLENDEDIMAGE_H__
#define __BLENDEDIMAGE_H__

#include <SexyAppFramework/Image.h>

namespace Sexy
{
class Graphics;
class MemoryImage;

// VTABLE: POPCAPGAME1 0x005d4f2c
class BlendedImage {
public:
    MemoryImage* mUnk0x4; // +0x4
    Rect mUnk0x8; // +0x8
    MemoryImage* mUnk0x18[4][4]; // +0x18

	BlendedImage();
	virtual ~BlendedImage();

	void DeleteImages();
	void Create(MemoryImage* param_1, Rect& param_2);
	void Create(MemoryImage* param_1);
	void CreateImage(int param_1, int param_2);
	void Draw(Graphics* g, float param_2, float param_3);
};

} // namespace Sexy

#endif // __BLENDEDIMAGE_H__
