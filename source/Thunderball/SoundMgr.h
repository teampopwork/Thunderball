#ifndef __SOUNDMGR_H__
#define __SOUNDMGR_H__

namespace Sexy
{
class DataSync;
class SoundDesc;
class SoundInstance;

class SoundMgr
{
  public:
	SoundMgr();
	virtual ~SoundMgr();

	void PauseMusic(bool param_1);
	void FadeMusic(int param_1);
	void CancelFade();
	void KillAllSounds();
	void Clear();
	void SyncState(DataSync* param_1);
	SoundInstance* PlaySample(SoundDesc* param_1);
	void AddSound(int param_1, float param_2, int param_3, int param_4, int param_5, float param_6);
	void AddFadeSound(SoundInstance* param_1);
	void UpdateSounds();
	void Update();
	void Mute(bool param_1);
};

} // namespace Sexy

#endif // __SOUNDMGR_H__