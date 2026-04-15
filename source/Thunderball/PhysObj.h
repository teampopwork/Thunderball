#ifndef __PHYSOBJ_H__
#define __PHYSOBJ_H__

#include "LevelEditor.h"

#include <SexyAppFramework/Rect.h>
#include <string>

namespace Sexy
{
class Graphics;
class Image;
class DataSync;
class Mover;
enum PegType;

// VTABLE: POPCAPGAME1 0x005f1924
class PhysObj : public EditValObj {
public:
	PhysObj();
	virtual ~PhysObj();

	static PhysObj* ClassFactory(int param_1);

	virtual bool EditGetSetValHook(const std::string& param_1, bool param_2);
	virtual void SyncState(DataSync* theSync);
	virtual int GetClass();
	virtual int GetTypeFlags();
	virtual void EditDrawMovement(Graphics* g);
	virtual void EditDrawOutline(Graphics* g);
	virtual void EditDrawPoints(Graphics* g);
	virtual void EditContains(float param_1, float param_2, bool param_3);
	virtual void EditIntersects(Rect param_1);
	virtual void EditTranslate(float param_1, float param_2);
	virtual void EditSetPos(float param_1, float param_2);
	virtual void EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual void EditFinishDrag();
	virtual void EditReloadImage();
	virtual void EditReflect(float param_1, float param_2, bool param_3, bool param_4);
	virtual void SetPos(float theX, float theY);
	virtual void Translate(float theDx, float theDy);
	virtual void SetVelocity(float theVx, float theVy);
	virtual void PegChangedHook(bool param_1);
	virtual void DeleteImage();
	virtual void Update();
	virtual void UpdateSlowMo(float param_1);
	virtual void DrawShadow(Graphics* g);
	virtual void Draw(Graphics* g);
	virtual void DrawLight(Graphics* g);
	virtual void AddedToGame();
	virtual void NotifyCollision(PhysObj* param_1);
	virtual Rect GetCenter();
	virtual float GetXPos();
	virtual float GetYPos();
	virtual bool IsCollidableWith(PhysObj* param_1);
	virtual void SetActiveWithGrowAnim(bool param_1);

	void AdjustRect(float theX, float theY, float theWidth, float theHeight);
	float GetOrigX();
	float GetOrigY();
	void SetActive(bool param_1);
	void SetIsPeg(bool isPeg);
	void SetPegType(PegType theType);
	void SetMoveUpdateCnt(int param_1);
	void SetMovingPercent(float param_1, bool param_2);
	void SyncPosWithMover();
	bool HasTypeFlags(int param_1);
	void InitDefaults();
	void LoadImage();

	void DrawImage(
		Graphics* g,
		Image* param_2,
		float param_3,
		float param_4,
		float param_5,
		bool param_6,
		bool param_7,
		bool param_8
	);
	void DrawImage(
		Graphics* g,
		float param_2,
		float param_3,
		float param_4,
		bool param_5,
		int param_6,
		float param_7
	);
	void DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6);

};

} // namespace Sexy

#endif // __PHYSOBJ_H__
