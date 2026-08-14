#include "SoundMgr.h"

#include "ThunderCommon.h"
#include "ThunderballApp.h"
#include "DataSync.h"

#include <SexyAppFramework/MusicInterface.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/SoundManager.h>

using namespace Sexy;

void SoundMgr::SoundDesc::SyncState(DataSync& theSync)
{
	theSync.SyncLong(mUnk0x0);
	theSync.SyncLong(mUnk0x4);
	theSync.SyncLong(mUnk0x8);
	theSync.SyncFloat(mUnk0xc);
	if (48 < theSync.mVersion) {
		theSync.SyncFloat(mUnk0x10);
	}
}

// TEMPLATE: POPCAPGAME1 0x0043f490
// std::_Tree<std::_Tmap_traits<int,Sexy::SoundMgr::SoundDesc,std::less<int>,std::allocator<std::pair<int const ,Sexy::SoundMgr::SoundDesc> >,1> >::_Buynode(void)

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
	DataSync_SyncSTLMapImplSimple(theSync, mUnk0x4, DataSyncFunc_SyncInt(), DataSyncFunc_SyncClass<SoundDesc>());
	if (0x2f < theSync.mVersion) {
		theSync.SyncLong(mUnk0x10);
	}

	if (theSync.mReader != NULL) {
		mUnk0x28.clear();
	}
}

// FUNCTION: POPCAPGAME1 0x00458e80
void SoundMgr::PlaySample(SoundDesc* param_1)
{
	int& aLastPlayTime = mUnk0x28[param_1];
	if (aLastPlayTime != 0 && GetThunderballApp()->mUpdateCount - aLastPlayTime < param_1->mUnk0x0) {
		return;
	}

	aLastPlayTime = GetThunderballApp()->mUpdateCount;
	SoundInstance* anInstance = GetThunderballApp()->mSoundManager->GetSoundInstance(param_1->mUnk0x4);
	if (anInstance != NULL) {
		if (param_1->mUnk0xc != 0.0f) {
			anInstance->AdjustPitch(param_1->mUnk0xc);
		}
		if (param_1->mUnk0x8 != 0) {
			anInstance->SetPan(param_1->mUnk0x8);
		}
		if (0.0f < param_1->mUnk0x10) {
			anInstance->SetVolume(param_1->mUnk0x10);
		}
		anInstance->Play(false, true);
	}
}

// FUNCTION: POPCAPGAME1 0x0045af70
void SoundMgr::AddSound(int param_1, int param_2)
{
	AddSound(param_1, 0.0f, 0,0, param_2, -1.0f);
}

// FUNCTION: POPCAPGAME1 0x0045afa0
void SoundMgr::AddSound(int param_1, float param_2, int param_3)
{
	AddSound(param_1, param_2, 0, 0, param_3, -1.0f);
}

// FUNCTION: POPCAPGAME1 0x00458f30
void SoundMgr::AddSound(int param_1, float param_2, int param_3, int param_4, int param_5, float param_6)
{
	if (param_6 == 0.0f) {
		return;
	}

	SoundDesc theDesc;
	theDesc.mUnk0x0 = param_5;
	theDesc.mUnk0x4 = param_1;
	theDesc.mUnk0x8 = param_3;
	theDesc.mUnk0xc = param_2;
	theDesc.mUnk0x10 = param_6;
	if (param_4 == 0) {
		PlaySample(&theDesc);
		return;
	}

	mUnk0x4.insert(std::pair<int, SoundDesc>(mUnk0x10 + param_4, theDesc));
}

// FUNCTION: POPCAPGAME1 0x00452810
void SoundMgr::AddFadeSound(SoundInstance* param_1)
{
	mUnk0x48.push_back(param_1);
}

// FUNCTION: POPCAPGAME1 0x00441d50
void SoundMgr::UpdateSounds()
{
	if (mUnk0x20 > 0 && --mUnk0x20 == 0) {
		mUnk0x18 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SoundMgr.cpp1422,199", 0.01f);
	}

	if (mUnk0x18 != 0.0f) {
		float aMinVolume = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\SoundMgr.cpp1423,204", 0.4f);
		float anOldVolume = mUnk0x14;
		mUnk0x14 += mUnk0x18;
		if (mUnk0x14 < aMinVolume) {
			mUnk0x14 = aMinVolume;
		}
		else if (mUnk0x14 > 1.0f) {
			mUnk0x14 = 1.0f;
		}

		if (anOldVolume != mUnk0x14) {
			ThunderballApp* anApp = GetThunderballApp();
			anApp->mMusicInterface->SetSongVolume(anApp->mUnk0x77c, mUnk0x14);
		}
	}

	for (std::list<SoundInstance*>::iterator it = mUnk0x48.begin(); it != mUnk0x48.end();) {
		SoundInstance* anInstance = *it;
		if (!anInstance->IsPlaying()) {
			anInstance->Release();
			it = mUnk0x48.erase(it);
		}
		else {
			float aVolume = (float) (anInstance->GetVolume() - 0.05);
			if (aVolume <= 0.0f) {
				anInstance->Release();
				it = mUnk0x48.erase(it);
			}
			else {
				anInstance->SetVolume(aVolume);
				++it;
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00458fc0
void SoundMgr::Update()
{
	++mUnk0x10;
	for (std::multimap<int, SoundDesc>::iterator it = mUnk0x4.begin(); it != mUnk0x4.end();) {
		if (it->first <= mUnk0x10) {
			PlaySample(&it->second);
			it = mUnk0x4.erase(it);
		}
		else {
			++it;
		}
	}
	UpdateSounds();
}

// STUB: POPCAPGAME1 0x
void SoundMgr::Mute(bool param_1)
{
}
