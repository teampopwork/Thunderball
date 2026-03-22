#include "ProfileMgr.h"

#include "DataSync.h"
#include "PlayerInfo.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/SexyAppBase.h>

using namespace Sexy;

int gProfileVersion = 1;

// SYNTHETIC: POPCAPGAME1 0x00464d60
// Sexy::ProfileMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00464ce0
ProfileMgr::ProfileMgr()
{
	Clear();
}

// FUNCTION: POPCAPGAME1 0x00461640
ProfileMgr::~ProfileMgr()
{
}

// FUNCTION: POPCAPGAME1 0x00458d50
void ProfileMgr::Clear()
{
	mProfileMap.clear();
	mNextProfileId = 1;
	mNextProfileUseSeq = 1;
}

// FUNCTION: POPCAPGAME1 0x00473490
void ProfileMgr::Load()
{
	Buffer aBuf;

	if (gSexyAppBase->ReadBufferFromFile("userdata/users.dat", &aBuf)) {
		DataReader aReader;
		aReader.OpenMemory((void*) aBuf.GetDataPtr(), aBuf.GetDataLen(), false);

		DataSync aSync(aReader);
		SyncState(aSync);
	}
}

// FUNCTION: POPCAPGAME1 0x004735f0
void ProfileMgr::Save()
{
	DataWriter aWriter;
	aWriter.OpenMemory(32);

	DataSync aSync(aWriter);
	SyncState(aSync);

	gSexyAppBase->WriteBytesToFile("userdata/users.dat", aWriter.mMemoryHandle, aWriter.mMemoryPosition);
}

// FUNCTION: POPCAPGAME1 0x00442e10
PlayerInfo* ProfileMgr::GetProfile(const std::string& theName)
{
	ProfileMap::iterator iter = mProfileMap.find(theName);

	if (iter == mProfileMap.end()) {
		return NULL;
	}

	PlayerInfo* profile = &iter->second;

	profile->LoadDetails();
	profile->mUseSeq = mNextProfileUseSeq;

	++mNextProfileUseSeq;

	return profile;
}

// FUNCTION: POPCAPGAME1 0x004717c0
PlayerInfo* ProfileMgr::AddProfile(const std::string& theName)
{
	std::pair<ProfileMap::iterator, bool> anEntry = mProfileMap.insert(std::make_pair(theName, PlayerInfo()));
	if (!anEntry.second) {
		return NULL;
	}

	PlayerInfo* profile = &anEntry.first->second;
	profile->mName = theName;
	profile->mId = mNextProfileId++;
	profile->mUseSeq = mNextProfileUseSeq++;

	DeleteOldProfiles();

	return profile;
}

// FUNCTION: POPCAPGAME1 0x00441ca0
PlayerInfo* ProfileMgr::GetAnyProfile()
{
	if (mProfileMap.size() == 0) {
		return NULL;
	}

	PlayerInfo* profile = &mProfileMap.begin()->second;

	profile->LoadDetails();
	profile->mUseSeq = mNextProfileUseSeq;

	++mNextProfileUseSeq;

	return profile;
}

// FUNCTION: POPCAPGAME1 0x00473280
void ProfileMgr::SyncState(DataSync& theSync)
{
	unsigned int aVersion = gProfileVersion;
	theSync.SyncLong(aVersion);

	if (aVersion != gProfileVersion) {
		return;
	}

	if (theSync.mReader) {
		mProfileMap.clear();

		int aCount = theSync.mReader->ReadShort();
		int aUseSeq = 0;
		int aId = 0;

		for (int i = 0; i < aCount; i++) {
			PlayerInfo aProfile;
			aProfile.SyncSummary(theSync);

			if (aUseSeq < aProfile.mUseSeq) {
				aUseSeq = aProfile.mUseSeq;
			}

			if (aId < aProfile.mId) {
				aId = aProfile.mId;
			}

			mProfileMap[aProfile.mName] = aProfile;
		}

		mNextProfileId = aId + 1;
		mNextProfileUseSeq = aUseSeq + 1;
	}
	else {
		theSync.mWriter->WriteShort(mProfileMap.size());

		for (ProfileMap::iterator i = mProfileMap.begin(); i != mProfileMap.end(); i++) {
			i->second.SyncSummary(theSync);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00452710
void ProfileMgr::DeleteOldestProfile()
{
	if (mProfileMap.empty()) {
		return;
	}

	ProfileMap::iterator anItr = mProfileMap.begin();
	for (ProfileMap::iterator i = mProfileMap.begin(); i != mProfileMap.end(); i++) {
		if (i->second.mUseSeq < anItr->second.mUseSeq) {
			anItr = i;
		}
	}

	anItr->second.DeleteUserFiles();
	mProfileMap.erase(anItr);
}

// FUNCTION: POPCAPGAME1 0x004527e0
void ProfileMgr::DeleteOldProfiles()
{
	while (mProfileMap.size() > 200) {
		DeleteOldestProfile();
	}
}

// FUNCTION: POPCAPGAME1 0x00452670
void ProfileMgr::DeleteProfile(ProfileMap::iterator theItr)
{
	theItr->second.DeleteUserFiles();
	mProfileMap.erase(theItr);
}

// FUNCTION: POPCAPGAME1 0x004526b0
bool ProfileMgr::DeleteProfile(const std::string& theName)
{
	ProfileMap::iterator anItr = mProfileMap.find(theName);

	if (anItr == mProfileMap.end()) {
		return false;
	}

	DeleteProfile(anItr);
	return true;
}

// FUNCTION: POPCAPGAME1 0x00471640
bool ProfileMgr::RenameProfile(const std::string& theOldName, const std::string& theNewName)
{
	ProfileMap::iterator anItr = mProfileMap.find(theOldName);

	if (anItr == mProfileMap.end()) {
		return false;
	}

	if (stricmp(theOldName.c_str(), theNewName.c_str()) != 0) {
		std::pair<ProfileMap::iterator, bool> anInsert = mProfileMap.insert(std::make_pair(theNewName, anItr->second));
		if (!anInsert.second) {
			return false;
		}

		mProfileMap.erase(anItr);
		anItr = anInsert.first;
	}

	anItr->second.mName = theNewName;
	return true;
}
