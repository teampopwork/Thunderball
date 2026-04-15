#include "PhysObj.h"

using namespace Sexy;

// STUB: POPCAPGAME1 0x00480660
PhysObj::PhysObj()
{
}

// SYNTHETIC: POPCAPGAME1 0x0047dfb0
// Sexy::PhysObj::`scalar deleting destructor'

// STUB: POPCAPGAME1 0x0047d230
PhysObj::~PhysObj()
{
}

// STUB: POPCAPGAME1 0x00404ca0
PhysObj* PhysObj::ClassFactory(int param_1)
{
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x004fa750
int PhysObj::GetClass()
{
	return 1;
}

// STUB: POPCAPGAME1 0x0047d350
float PhysObj::GetXPos()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x0047d370
float PhysObj::GetYPos()
{
	return 0.0f;
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::SetPos(float theX, float theY)
{
}

// STUB: POPCAPGAME1 0x00476b00
void PhysObj::Translate(float theDx, float theDy)
{
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::SetVelocity(float theVx, float theVy)
{
}

void PhysObj::AdjustRect(float theX, float theY, float theWidth, float theHeight)
{
}

// STUB: POPCAPGAME1 0x00479700
float PhysObj::GetOrigX()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x00479720
float PhysObj::GetOrigY()
{
	return 0.0f;
}

// STUB: POPCAPGAME1 0x004769f0
void PhysObj::SetActive(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00454790
void PhysObj::SetActiveWithGrowAnim(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0047af50
void PhysObj::SetIsPeg(bool isPeg)
{
}

// STUB: POPCAPGAME1 0x00479870
void PhysObj::SetPegType(PegType theType)
{
}

// STUB: POPCAPGAME1 0x00479980
void PhysObj::SetMoveUpdateCnt(int param_1)
{
}

// STUB: POPCAPGAME1 0x004799a0
void PhysObj::SetMovingPercent(float param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00479940
void PhysObj::SyncPosWithMover()
{
}

// STUB: POPCAPGAME1 0x00479890
int PhysObj::GetTypeFlags()
{
	return 0;
}

// STUB: POPCAPGAME1 0x00476b30
bool PhysObj::HasTypeFlags(int param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047d390
bool PhysObj::IsCollidableWith(PhysObj* param_1)
{
	return false;
}

// STUB: POPCAPGAME1 0x0047f740
void PhysObj::InitDefaults()
{
}

// STUB: POPCAPGAME1 0x0047f830
void PhysObj::LoadImage()
{
}

// FUNCTION: POPCAPGAME1 0x0047f960
void PhysObj::EditReloadImage()
{
	LoadImage();
}

// STUB: POPCAPGAME1 0x004769c0
void PhysObj::DeleteImage()
{
}

// FUNCTION: POPCAPGAME1 0x0052a680
void PhysObj::AddedToGame()
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::DrawShadow(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00479b70
void PhysObj::DrawLight(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::EditDrawPoints(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00479ff0
void PhysObj::EditDrawMovement(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00476b50
void PhysObj::EditDrawOutline(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x004797c0
void PhysObj::EditTranslate(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00479800
void PhysObj::EditSetPos(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00479a30
void PhysObj::Update()
{
}

// STUB: POPCAPGAME1 0x00479b00
void PhysObj::UpdateSlowMo(float param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::NotifyCollision(PhysObj* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00497dc0
void PhysObj::PegChangedHook(bool param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0052a680
void PhysObj::EditFinishDrag()
{
}

// STUB: POPCAPGAME1 0x00476a80
void PhysObj::EditGetDragMode(float param_1, float param_2)
{
}

// FUNCTION: POPCAPGAME1 0x0053ea70
void PhysObj::EditDoPointDrag(float param_1, float param_2)
{
}

// STUB: POPCAPGAME1 0x00476a30
void PhysObj::EditContains(float param_1, float param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x00479740
void PhysObj::EditIntersects(Rect param_1)
{
}

// STUB: POPCAPGAME1 0x00476a90
void PhysObj::EditReflect(float param_1, float param_2, bool param_3, bool param_4)
{
}

// STUB: POPCAPGAME1 0x00479b90
void PhysObj::DrawImage(
	Graphics* g,
	Image* param_2,
	float param_3,
	float param_4,
	float param_5,
	bool param_6,
	bool param_7,
	bool param_8
)
{
}

// STUB: POPCAPGAME1 0x00479d50
void PhysObj::DrawImage(
	Graphics* g,
	float param_2,
	float param_3,
	float param_4,
	bool param_5,
	int param_6,
	float param_7
)
{
}

// STUB: POPCAPGAME1 0x00479fb0
void PhysObj::DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6)
{
}

// STUB: POPCAPGAME1 0x0047f970
bool PhysObj::EditGetSetValHook(const std::string& param_1, bool param_2)
{
	return false;
}

// STUB: POPCAPGAME1 0x00480750
void PhysObj::SyncState(DataSync* theSync)
{
}

// STUB: POPCAPGAME1 0x00476a00
Rect PhysObj::GetCenter()
{
	return Rect();
}
