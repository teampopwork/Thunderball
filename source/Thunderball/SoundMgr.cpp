#include "SoundMgr.h"

#include "ThunderCommon.h"
#include "ThunderballApp.h"
#include "DataSync.h"

#include <SexyAppFramework/MusicInterface.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/SoundManager.h>

using namespace Sexy;

// TEMPLATE: POPCAPGAME1 0x00
// std::_Tree<std::_Tmap_traits<int,Sexy::MemoryImage *,std::greater<int>,std::allocator<std::pair<int const ,Sexy::MemoryImage *> >,1> >::_Buynode(void)

// FUNCTION: POPCAPGAME1 0x0045f1d0
SoundMgr::SoundMgr()
{
	Clear();
	mUnk0x14 = 1.0f;
	mUnk0x1c = false;
	mUnk0x18 = 0.0f;
}

// SYNTHETIC: POPCAPGAME1 0x0045f290
// Sexy::SoundMgr::`scalar deleting destructor'

// TEMPLATE: POPCAPGAME1 0x0043f190
// std::list<PakCollection,std::allocator<PakCollection> >::_Tidy

// TEMPLATE: POPCAPGAME1 0x00449dc0
// std::_Tree<std::_Tmap_traits<int,Sexy::MemoryImage *,std::greater<int>,std::allocator<std::pair<int const ,Sexy::MemoryImage *> >,1> >::erase(class std::_Tree<class std::_Tmap_traits<int, class Sexy::SoundMgr::SoundDesc *, struct std::less<int>, class std::allocator<struct std::pair<int const, class Sexy::SoundMgr::SoundDesc *>>, 1>>::iterator, class std::_Tree<class std::_Tmap_traits<int, class Sexy::SoundMgr::SoundDesc *, struct std::less<int>, class std::allocator<struct std::pair<int const, class Sexy::SoundMgr::SoundDesc *>>, 1>>::iterator)

// FUNCTION: POPCAPGAME1 0x00458dd0
SoundMgr::~SoundMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00437560
void SoundMgr::PauseMusic(bool param_1)
{
	if (mUnk0x1c != param_1) {
		mUnk0x1c = param_1;
		if (mUnk0x1c) {
			GetThunderballApp()->mMusicInterface->PauseAllMusic();
		}
		else {
			GetThunderballApp()->mMusicInterface->ResumeAllMusic();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004375a0
void SoundMgr::FadeMusic(int param_1)
{
	if (0.0f < GetThunderballApp()->mMusicVolume && 0.0f < GetThunderballApp()->mSfxVolume) {
		if (mUnk0x20 < param_1) {
			mUnk0x20 = param_1;
		}
		mUnk0x18 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SoundMgr.cpp1421,101", -0.03f);
	}
}

// FUNCTION: POPCAPGAME1 0x00437600
void SoundMgr::CancelFade()
{
	mUnk0x20 = 0;
	mUnk0x18 = 0.0f;
	mUnk0x14 = 1.0f;
}

// TEMPLATE: POPCAPGAME1 0x0043f110
// std::_Tree<std::_Tmap_traits<int,Sexy::MemoryImage *,std::greater<int>,std::allocator<std::pair<int const ,Sexy::MemoryImage *> >,1> >::_Erase

// FUNCTION: POPCAPGAME1 0x00441f30
void SoundMgr::KillAllSounds()
{
	mUnk0x4.clear();
	for (std::list<SoundInstance*>::iterator it = mUnk0x48.begin(); it != mUnk0x48.end(); ++it) {
		delete *it;
	}
	mUnk0x48.clear();
}

// FUNCTION: POPCAPGAME1 0x00442e90
void SoundMgr::Clear()
{
	mUnk0x4.clear();
	mUnk0x28.clear();
	mUnk0x10 = 0;
	KillAllSounds();
}

// FUNCTION: POPCAPGAME1 0x0045f2c0
void SoundMgr::SyncState(DataSync& theSync)
{
	// DataSync_SyncSTLMapImplSimple<int, SoundDesc*>(param_1, mUnk0x4);
	if (0x2f < theSync.mVersion) {
		theSync.SyncLong(mUnk0x10);
	}

	if (theSync.mReader != NULL) {
		mUnk0x28.clear();
	}
}

// STUB: POPCAPGAME1 0x00458e80
SoundInstance* SoundMgr::PlaySample(SoundDesc* param_1)
{
	return NULL;
}

// FUNCTION: POPCAPGAME1 0x0045af70
void SoundMgr::AddSound(int param_1, int param_2)
{
	AddSound(param_1, 0.0f, 0,0, param_2, -1.0f);
}

// FUNCTION: POPCAPGAME1 0x00458f30
void SoundMgr::AddSound(int param_1, float param_2, int param_3, int param_4, int param_5, float param_6)
{
	if (param_6 == 0.0f) {
		SoundDesc theDesc;
		theDesc.mUnk0x4 = param_1;
		theDesc.mUnk0xc = param_2;
		theDesc.mUnk0x8 = param_3;
		theDesc.mUnk0x0 = param_5;
		theDesc.mUnk0x10 = param_6;
		if (param_4 == 0) {
			PlaySample(&theDesc);
		} else {
			theDesc.mUnk0x0 = param_4 + mUnk0x10;
			theDesc.mUnk0x4 = param_5;
			theDesc.mUnk0x8 = param_1;
			theDesc.mUnk0xc = param_3;
			theDesc.mUnk0x10 = param_2;
			mUnk0x4.insert(std::pair<int, SoundDesc*>(theDesc.mUnk0x0, &theDesc));
		}
	}
}

// STUB: POPCAPGAME1 0x00452810
void SoundMgr::AddFadeSound(SoundInstance* param_1)
{
}

// STUB: POPCAPGAME1 0x00441d50
void SoundMgr::UpdateSounds()
{
}

// STUB: POPCAPGAME1 0x00458fc0
void SoundMgr::Update()
{
}

// STUB: POPCAPGAME1 0x
void SoundMgr::Mute(bool param_1)
{
}
