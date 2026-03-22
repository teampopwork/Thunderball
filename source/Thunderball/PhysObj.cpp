#include "PhysObj.h"

using namespace Sexy;

PhysObj::PhysObj()
{
}

PhysObj::~PhysObj()
{
}

PhysObj* PhysObj::ClassFactory(int param_1)
{
	return NULL;
}

int PhysObj::GetClass()
{
	return 0;
}

float PhysObj::GetXPos()
{
	return 0.0f;
}

float PhysObj::GetYPos()
{
	return 0.0f;
}

void PhysObj::SetPos(float theX, float theY)
{
}

void PhysObj::Translate(float theDx, float theDy)
{
}

void PhysObj::SetVelocity(float theVx, float theVy)
{
}
void PhysObj::AdjustRect(float theX, float theY, float theWidth, float theHeight)
{
}

float PhysObj::GetOrigX()
{
	return 0.0f;
}

float PhysObj::GetOrigY()
{
	return 0.0f;
}

void PhysObj::SetActive(bool param_1)
{
}

void PhysObj::SetActiveWithGrowAnim(bool param_1)
{
}

void PhysObj::SetIsPeg(bool isPeg)
{
}

void PhysObj::SetPegType(PegType theType)
{
}
void PhysObj::SetMover(Mover* theMover)
{
}
void PhysObj::SetMoveRef(PhysObj* param_1)
{
}
void PhysObj::SetMoveUpdateCnt(int param_1)
{
}
void PhysObj::SetMoving(int param_1)
{
}
void PhysObj::SetMovingPercent(float param_1, bool param_2)
{
}
void PhysObj::SyncPosWithMover()
{
}

int PhysObj::GetTypeFlags()
{
	return 0;
}

bool PhysObj::HasTypeFlags(int param_1)
{
	return false;
}

bool PhysObj::IsCollidableWith(PhysObj* param_1)
{
	return false;
}

void PhysObj::InitDefaults()
{
}

void PhysObj::LoadImage()
{
}

void PhysObj::EditReloadImage()
{
}

void PhysObj::CreateMover()
{
}

void PhysObj::DeleteImage()
{
}

void PhysObj::AddedToGame()
{
}

void PhysObj::Draw(Graphics* g)
{
}

void PhysObj::DrawShadow(Graphics* g)
{
}

void PhysObj::DrawLight(Graphics* g)
{
}

void PhysObj::EditDrawPoints(Graphics* g)
{
}

void PhysObj::EditDrawMovement(Graphics* g)
{
}

void PhysObj::EditDrawOutline(Graphics* g)
{
}

void PhysObj::EditTranslate(float param_1, float param_2)
{
}

void PhysObj::EditSetPos(float param_1, float param_2)
{
}

void PhysObj::Update()
{
}

void PhysObj::UpdateSlowMo(float param_1)
{
}

void PhysObj::NotifyCollision(PhysObj* param_1)
{
}

void PhysObj::NotifyCollision()
{
}

void PhysObj::PegChangedHook(bool param_1)
{
}

void PhysObj::EditFinishDrag()
{
}

int PhysObj::EditGetDragMode(float param_1, float param_2)
{
	return 0;
}

void PhysObj::EditDoPointDrag(float param_1, float param_2)
{
}

bool PhysObj::EditContains(float param_1, float param_2, bool param_3)
{
	return false;
}

int PhysObj::EditIntersects(Rect param_1)
{
	return 0;
}

void PhysObj::EditReflect(float param_1, float param_2, bool param_3, bool param_4)
{
}

void PhysObj::FinishDefaults()
{
}

void PhysObj::Reload()
{
}

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

void PhysObj::DrawImage(Graphics* g, float param_2, float param_3, float param_4, bool param_5, bool param_6)
{
}

std::string* PhysObj::EditGetSetValHook(std::string* param_1, bool param_2)
{
	return NULL;
}

void PhysObj::SyncState(DataSync* theSync)
{
}

Rect PhysObj::GetCenter()
{
	return Rect();
}
