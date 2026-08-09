#ifndef __BRICK_H__
#define __BRICK_H__

#include "BlendedImage.h"
#include "Poly.h"

#include <string>

namespace Sexy
{
class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1fdc
class Brick : public Poly {
public:
	float mUnk0x148; // +0x148
	float mUnk0x14c; // +0x14c
	float mUnk0x150; // +0x150
	float mUnk0x154; // +0x154
	float mUnk0x158; // +0x158
	float mUnk0x15c; // +0x15c
	float mUnk0x160; // +0x160
	float mUnk0x164; // +0x164
	int mUnk0x168; // +0x168
	int mUnk0x16c; // +0x16c
	int mUnk0x170; // +0x170
	int mUnk0x174; // +0x174
	int mUnk0x178; // +0x178
	int mUnk0x17c; // +0x17c
	bool mUnk0x180; // +0x180
	bool mUnk0x181; // +0x181
	bool mUnk0x182; // +0x182
	BlendedImage mUnk0x184[10]; // +0x184
	Image* mUnk0x4f4[9]; // +0x4f4
	MemoryImage* mUnk0x518; // +0x518

	Brick();
	virtual ~Brick();

	virtual bool EditGetSetValHook(std::string* param_1, bool param_2);
	virtual void SyncState(DataSync& param_1);
	virtual int GetClass();
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditReloadImage();
	virtual void EditReflect(float param_1, float param_2, bool param_3, bool param_4);
	virtual void DrawShadow(Graphics* g);
	virtual void Draw(Graphics* g);
	virtual void PegChangedHook(bool param_1);
	virtual void DeleteImage();

	Image* GetTextureImage();
	void GetCorners(SexyVector2* param_1);
	void CreateImage(int param_1);
	void CreateImage();
	void DrawBrick(Graphics* g, int param_2);
	void InitFromParams();
	void CommonAttach(SexyVector2* param_1, SexyVector2* param_2, bool param_3, bool param_4);
	void AnchoredInit();
	void AnchoredStretch(int param_1, int param_2, bool param_3, bool param_4);
	int AttachTo(Sexy::Brick* param_1, int param_2, int param_3, bool param_4);
};

} // namespace Sexy

#endif // __BRICK_H__
