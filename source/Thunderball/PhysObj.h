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

class PhysObj : public EditValObj {
public:
	PhysObj();
	virtual ~PhysObj();

	static PhysObj* ClassFactory(int param_1);
	virtual int GetClass();

	virtual float GetXPos();
	virtual float GetYPos();
	virtual void SetPos(float theX, float theY);
	virtual void Translate(float theDx, float theDy);
	virtual void SetVelocity(float theVx, float theVy);
	virtual void AdjustRect(float theX, float theY, float theWidth, float theHeight);
	virtual float GetOrigX();
	virtual float GetOrigY();

	virtual void SetActive(bool param_1);
	virtual void SetActiveWithGrowAnim(bool param_1);
	virtual void SetIsPeg(bool isPeg);
	virtual void SetPegType(PegType theType);
	virtual void SetMover(Mover* theMover);
	virtual void SetMoveRef(PhysObj* param_1);
	virtual void SetMoveUpdateCnt(int param_1);
	virtual void SetMoving(int param_1);
	virtual void SetMovingPercent(float param_1, bool param_2);
	virtual void SyncPosWithMover();

	virtual int GetTypeFlags();
	virtual bool HasTypeFlags(int param_1);
	virtual bool IsCollidableWith(PhysObj* param_1);

	virtual void InitDefaults();
	virtual void LoadImage();
	virtual void EditReloadImage();
	virtual void CreateMover();
	virtual void DeleteImage();
	virtual void AddedToGame();

	virtual void Draw(Graphics* g);
	virtual void DrawShadow(Graphics* g);
	virtual void DrawLight(Graphics* g);
	virtual void EditDrawPoints(Graphics* g);
	virtual void EditDrawMovement(Graphics* g);
	virtual void EditDrawOutline(Graphics* g);
	virtual void EditTranslate(float param_1, float param_2);
	virtual void EditSetPos(float param_1, float param_2);

	virtual void Update();
	virtual void UpdateSlowMo(float param_1);

	virtual void NotifyCollision(PhysObj* param_1);
	virtual void PegChangedHook(bool param_1);
	virtual void EditFinishDrag();
	virtual int EditGetDragMode(float param_1, float param_2);
	virtual void EditDoPointDrag(float param_1, float param_2);
	virtual bool EditContains(float param_1, float param_2, bool param_3);
	virtual int EditIntersects(Rect param_1);
	virtual void EditReflect(float param_1, float param_2, bool param_3, bool param_4);

	virtual void FinishDefaults();
	virtual void NotifyCollision();

	virtual void Reload();

	static void DrawImage(
		Graphics* g,
		Image* param_2,
		float param_3,
		float param_4,
		float param_5,
		bool param_6,
		bool param_7,
		bool param_8
	);
	static void DrawImage(
		Graphics* g,
		float param_2,
		float param_3,
		float param_4,
		bool param_5,
		int param_6,
		float param_7
	);
	static void DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6);

	virtual std::string* EditGetSetValHook(std::string* param_1, bool param_2);

	virtual void SyncState(DataSync* theSync);

	virtual Rect GetCenter();
};

} // namespace Sexy

#endif // __PHYSOBJ_H__
