#include "BassMusicInterface.h"
#include "BassLoader.h"
#include "..\PakLib\PakInterface.h"

using namespace Sexy;

#define BASS2_MUSIC_RAMP			BASS_MUSIC_RAMP	// normal ramping

#define BASS_CONFIG_BUFFER			0

// FUNCTION: POPCAPGAME1 0x0052db40
BassMusicInfo::BassMusicInfo()
{	
	mVolume = 0.0;
	mVolumeAdd = 0.0;
	mVolumeCap = 1.0;
	mStopOnFade = false;
	mHMusic = NULL;
	mHStream = NULL;
}

// SYNTHETIC: POPCAPGAME1 0x0054fe80
// Sexy::BassMusicInterface::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x0054fc60
BassMusicInterface::BassMusicInterface(HWND theHWnd)
{
	LoadBassDLL();

	MIXERCONTROLDETAILS mcd;
	MIXERCONTROLDETAILS_UNSIGNED mxcd_u;
	MIXERLINECONTROLS mxlc;
	MIXERCONTROL mlct;
	MIXERLINE mixerLine;
	HMIXEROBJ phmx;
	MIXERCAPS pmxcaps;	

	mixerOpen((HMIXER*) &phmx, 0, 0, 0, MIXER_OBJECTF_MIXER);
	mixerGetDevCaps(0, &pmxcaps, sizeof(pmxcaps));

	mxlc.cbStruct = sizeof(mxlc);	
	mxlc.cbmxctrl = sizeof(mlct);
	mxlc.pamxctrl = &mlct;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mixerLine.cbStruct = sizeof(mixerLine);
	mixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
	mixerGetLineInfo(phmx, &mixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
	mxlc.dwLineID = mixerLine.dwLineID;
	mixerGetLineControls(phmx, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);	

	mcd.cbStruct = sizeof(mcd);
	mcd.dwControlID = mlct.dwControlID;
	mcd.cChannels = 1;
	mcd.cMultipleItems = 0;
	mcd.cbDetails = sizeof(mxcd_u);
	mcd.paDetails = &mxcd_u;
	
	mixerGetControlDetails(phmx, &mcd, 0L);

	//return mxcd_u.dwValue;	

	BOOL success;

	if (gBass->mVersion2)
	{
		success = gBass->BASS_Init2(1, 44100, 0, theHWnd, NULL);
		gBass->BASS_SetConfig(BASS_CONFIG_BUFFER, 2000);
	}
	else
		success = gBass->BASS_Init(-1, 44100, 0, theHWnd);

	mixerSetControlDetails(phmx, &mcd, 0L);

	gBass->BASS_Start();

	mixerClose((HMIXER) phmx);

	mMaxMusicVolume = 40;

	mMusicLoadFlags = gBass->mVersion2 ? BASS_MUSIC_LOOP | BASS2_MUSIC_RAMP : BASS_MUSIC_LOOP;
}

// FUNCTION: POPCAPGAME1 0x0054fbc0
BassMusicInterface::~BassMusicInterface()
{
	gBass->BASS_Stop();
	gBass->BASS_Free();

	FreeBassDLL();
}

// FUNCTION: POPCAPGAME1 0x0054f410
bool BassMusicInterface::LoadMusic(int theSongId, const std::string& theFileName)
{
	HMUSIC aHMusic = NULL;
	HSTREAM aStream = NULL;
	
	std::string anExt;
	int aDotPos = theFileName.find_last_of('.');
	if (aDotPos!=std::string::npos)
		anExt = StringToLower(theFileName.substr(aDotPos+1));

	if (anExt=="wav" || anExt=="ogg" || anExt=="mp3")
		aStream = gBass->BASS_StreamCreateFile(FALSE, (void*) theFileName.c_str(), 0, 0, 0);
	else
	{
		PFILE* aFP = p_fopen(theFileName.c_str(), "rb");
		if (aFP == NULL)
			return false;

		p_fseek(aFP, 0, SEEK_END);
		int aSize = p_ftell(aFP);
		p_fseek(aFP, 0, SEEK_SET);

		uchar* aData = new uchar[aSize];
		p_fread(aData, 1, aSize, aFP);
		p_fclose(aFP);

		if (gBass->mVersion2)
			aHMusic = gBass->BASS_MusicLoad2(FALSE, (void*) theFileName.c_str(), 0, 0, BASS_MUSIC_LOOP | BASS2_MUSIC_RAMP, 0);
		else
			aHMusic = gBass->BASS_MusicLoad(FALSE, (void*) theFileName.c_str(), 0, 0, BASS_MUSIC_LOOP);

		delete aData;
	}

	if (aHMusic==NULL && aStream==NULL)
		return false;
	
	BassMusicInfo aMusicInfo;	
	aMusicInfo.mHMusic = aHMusic;
	aMusicInfo.mHStream = aStream;
	mMusicMap.insert(BassMusicMap::value_type(theSongId, aMusicInfo));

	return true;	
}

// FUNCTION: POPCAPGAME1 0x0054d360
void BassMusicInterface::PlayMusic(int theSongId, int theOffset, bool noLoop)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = aMusicInfo->mVolumeCap;
		aMusicInfo->mVolumeAdd = 0.0;
		aMusicInfo->mStopOnFade = noLoop;
		gBass->BASS_ChannelSetAttributes(aMusicInfo->GetHandle(), -1, (int) (aMusicInfo->mVolume*100), -101);			   

		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		if (aMusicInfo->mHMusic)
		{
			if (gBass->mVersion2)
				gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, BASS_MUSIC_POSRESET | BASS2_MUSIC_RAMP | (noLoop ? 0 : BASS_MUSIC_LOOP), TRUE);
			else
				gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, noLoop ? 0 : BASS_MUSIC_LOOP, TRUE);
		}
		else
		{
			BOOL flush = theOffset == -1 ? FALSE : TRUE;
			gBass->BASS_StreamPlay(aMusicInfo->mHStream, flush, noLoop ? 0 : BASS_MUSIC_LOOP);
			if (theOffset > 0)
				gBass->BASS_ChannelSetPosition(aMusicInfo->mHStream, theOffset);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0054d4a0
void BassMusicInterface::StopMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = 0.0;
		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
	}
}

// FUNCTION: POPCAPGAME1 0x0054cc50
void BassMusicInterface::StopAllMusic()
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		aMusicInfo->mVolume = 0.0;
		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		++anItr;
	}
}

// FUNCTION: POPCAPGAME1 0x0054eac0
void BassMusicInterface::UnloadMusic(int theSongId)
{
	StopMusic(theSongId);
	
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (aMusicInfo->mHStream)
			gBass->BASS_StreamFree(aMusicInfo->mHStream);
		else if (aMusicInfo->mHMusic)
			gBass->BASS_MusicFree(aMusicInfo->mHMusic);

		mMusicMap.erase(anItr);
	}
}

// FUNCTION: POPCAPGAME1 0x0054ccd0
void BassMusicInterface::UnloadAllMusic()
{
	StopAllMusic();
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (aMusicInfo->mHStream)
			gBass->BASS_StreamFree(aMusicInfo->mHStream);
		else if (aMusicInfo->mHMusic)
			gBass->BASS_MusicFree(aMusicInfo->mHMusic);
	}
	mMusicMap.clear();
}

// FUNCTION: POPCAPGAME1 0x0054d510
void BassMusicInterface::PauseMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		gBass->BASS_ChannelPause(aMusicInfo->GetHandle());
	}
}

// FUNCTION: POPCAPGAME1 0x0054cdc0
void BassMusicInterface::PauseAllMusic()
{
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		if (gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PLAYING)
			gBass->BASS_ChannelPause(aMusicInfo->GetHandle());
	}
}

// FUNCTION: POPCAPGAME1 0x0054ce60
void BassMusicInterface::ResumeAllMusic()
{
	for (BassMusicMap::iterator anItr = mMusicMap.begin(); anItr != mMusicMap.end(); ++anItr)
	{
		BassMusicInfo* aMusicInfo = &anItr->second;

		if (gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PAUSED)
			gBass->BASS_ChannelResume(aMusicInfo->GetHandle());
	}
}

// FUNCTION: POPCAPGAME1 0x0054d580
void BassMusicInterface::ResumeMusic(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
		gBass->BASS_ChannelResume(aMusicInfo->GetHandle());
	}
}

// FUNCTION: POPCAPGAME1 0x0054d5f0
void BassMusicInterface::FadeIn(int theSongId, int theOffset, double theSpeed, bool noLoop)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
				
		aMusicInfo->mVolumeAdd = theSpeed;
		aMusicInfo->mStopOnFade = noLoop;

		gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
		gBass->BASS_ChannelSetAttributes(aMusicInfo->GetHandle(), -1, (int) (aMusicInfo->mVolume*100), -101);
		if (aMusicInfo->mHMusic)
		{
			if (theOffset == -1)
				gBass->BASS_MusicPlay(aMusicInfo->mHMusic);
			else
			{
				if (gBass->mVersion2)
					gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, BASS2_MUSIC_RAMP | (noLoop ? 0 : BASS_MUSIC_LOOP), TRUE);
				else
					gBass->BASS_MusicPlayEx(aMusicInfo->mHMusic, theOffset, noLoop ? 0 : BASS_MUSIC_LOOP, TRUE);
			}
		}
		else
		{
			BOOL flush = theOffset == -1 ? FALSE : TRUE;
			gBass->BASS_StreamPlay(aMusicInfo->mHStream, flush, noLoop ? 0 : BASS_MUSIC_LOOP);
			if (theOffset > 0)
				gBass->BASS_ChannelSetPosition(aMusicInfo->mHStream, theOffset);
		}

	}
}

// FUNCTION: POPCAPGAME1 0x0054d740
void BassMusicInterface::FadeOut(int theSongId, bool stopSong, double theSpeed)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		
		if (aMusicInfo->mVolume != 0.0)
		{
			aMusicInfo->mVolumeAdd = -theSpeed;			
		}

		aMusicInfo->mStopOnFade = stopSong;
	}
}

// FUNCTION: POPCAPGAME1 0x0054cf00
void BassMusicInterface::FadeOutAll(bool stopSong, double theSpeed)
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;
				
		aMusicInfo->mVolumeAdd = -theSpeed;
		aMusicInfo->mStopOnFade = stopSong;

		++anItr;
	}
}

// FUNCTION: POPCAPGAME1 0x0054b210
void BassMusicInterface::SetVolume(double theVolume)
{
	int aVolume = (int) (theVolume * mMaxMusicVolume);
	
	if (gBass->mVersion2)
	{
		gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_MUSIC*/6, (int) (theVolume * 100));
		gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_STREAM*/5, (int) (theVolume * 100));
	}
	else
		gBass->BASS_SetGlobalVolumes(aVolume, aVolume, aVolume);		
}

// FUNCTION: POPCAPGAME1 0x0054d7b0
void BassMusicInterface::SetSongVolume(int theSongId, double theVolume)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;

		aMusicInfo->mVolume = theVolume;
		gBass->BASS_ChannelSetAttributes(aMusicInfo->GetHandle(), -1, (int) (aMusicInfo->mVolume*100), -101);
	}
}

// FUNCTION: POPCAPGAME1 0x0054d840
void BassMusicInterface::SetSongMaxVolume(int theSongId, double theMaxVolume)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;

		aMusicInfo->mVolumeCap = theMaxVolume;
		aMusicInfo->mVolume = min(aMusicInfo->mVolume, theMaxVolume);
		gBass->BASS_ChannelSetAttributes(aMusicInfo->GetHandle(), -1, (int) (aMusicInfo->mVolume*100), -101);
	}
}

// FUNCTION: POPCAPGAME1 0x0054d8e0
bool BassMusicInterface::IsPlaying(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		return gBass->BASS_ChannelIsActive(aMusicInfo->GetHandle()) == BASS_ACTIVE_PLAYING;
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x0054d960
void BassMusicInterface::SetMusicAmplify(int theSongId, double theAmp)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;		
		gBass->BASS_MusicSetAmplify(aMusicInfo->GetHandle(), (int) (theAmp * 100));
	}
}

// FUNCTION: POPCAPGAME1 0x0054cf80
void BassMusicInterface::Update()
{
	BassMusicMap::iterator anItr = mMusicMap.begin();
	while (anItr != mMusicMap.end())
	{
		BassMusicInfo* aMusicInfo = &anItr->second;

		if (aMusicInfo->mVolumeAdd != 0.0)
		{
			aMusicInfo->mVolume += aMusicInfo->mVolumeAdd;
			
			if (aMusicInfo->mVolume > aMusicInfo->mVolumeCap)
			{
				aMusicInfo->mVolume = aMusicInfo->mVolumeCap;
				aMusicInfo->mVolumeAdd = 0.0;
			}
			else if (aMusicInfo->mVolume < 0.0)
			{
				aMusicInfo->mVolume = 0.0;
				aMusicInfo->mVolumeAdd = 0.0;

				if (aMusicInfo->mStopOnFade)
					gBass->BASS_ChannelStop(aMusicInfo->GetHandle());
			}

			gBass->BASS_ChannelSetAttributes(aMusicInfo->GetHandle(), -1, (int) (aMusicInfo->mVolume*100), -101);
		}

		++anItr;
	}	
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// MODs are broken up into several orders or patterns. This returns the current order a song is on.
// FUNCTION: POPCAPGAME1 0x0054d9f0
int BassMusicInterface::GetMusicOrder(int theSongId)
{
	BassMusicMap::iterator anItr = mMusicMap.find(theSongId);
	if (anItr != mMusicMap.end())
	{		
		BassMusicInfo* aMusicInfo = &anItr->second;
		int aPosition = gBass->BASS_MusicGetOrderPosition(aMusicInfo->GetHandle());
		return aPosition;
	}
	return -1;
}