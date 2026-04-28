#ifndef __BRICK_H__
#define __BRICK_H__

#include "Poly.h"

#include <string>

namespace Sexy
{
class SexyVector2;

// VTABLE: POPCAPGAME1 0x005f1fdc
class Brick : public Poly {
public:
	Brick();
	virtual ~Brick();

	virtual bool EditGetSetValHook(std::string* param_1, bool param_2);
	virtual void SyncState(DataSync* param_1);
	virtual int GetClass();
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditReloadImage();
	virtual void EditReflect(float param_1, float param_2, bool param_3);
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
