#ifndef __SOUNDMGR_H__
#define __SOUNDMGR_H__

#include <list>
#include <map>

namespace Sexy
{
class DataSync;
class SoundInstance;

// VTABLE: POPCAPGAME1 0x005e9f5c
class SoundMgr {
	class SoundDesc {
	public:
		int mUnk0x0;    // +0x0
		int mUnk0x4;    // +0x4
		int mUnk0x8;    // +0x8
		float mUnk0xc;  // +0xc
		float mUnk0x10; // +0x10
	};

public:
	std::multimap<int, SoundDesc*> mUnk0x4;  // +0x4
	int mUnk0x10;                            // +0x10
	float mUnk0x14;                          // +0x14
	float mUnk0x18;                          // +0x18
	bool mUnk0x1c;                           // +0x1c
	int mUnk0x20;                            // +0x20
	std::multimap<SoundDesc*, int> mUnk0x28; // +0x28
	std::list<SoundInstance*> mUnk0x48;      // +0x48

	SoundMgr();
	virtual ~SoundMgr();

	void PauseMusic(bool param_1);
	void FadeMusic(int param_1);
	void CancelFade();
	void KillAllSounds();
	void Clear();
	void SyncState(DataSync* param_1);
	SoundInstance* PlaySample(SoundDesc* param_1);
	void AddSound(int param_1, int param_2);
	void AddSound(int param_1, float param_2, int param_3, int param_4, int param_5, float param_6);
	void AddFadeSound(SoundInstance* param_1);
	void UpdateSounds();
	void Update();
	void Mute(bool param_1);
};

} // namespace Sexy

#endif // __SOUNDMGR_H__
