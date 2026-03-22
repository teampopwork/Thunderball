#ifndef __PROFILEMGR_H__
#define __PROFILEMGR_H__

#include "PlayerInfo.h"

#include <SexyAppFramework/Common.h>

#include <map>
#include <string>

namespace Sexy
{
class DataSync;
class PlayerInfo;

typedef std::map<std::string, PlayerInfo, StringLessNoCase> ProfileMap;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ProfileMgr {
protected:
	ProfileMap mProfileMap;
	unsigned int mNextProfileId;
	unsigned int mNextProfileUseSeq;

	void SyncState(DataSync& theSync);

	void DeleteOldestProfile();
	void DeleteOldProfiles();
	void DeleteProfile(ProfileMap::iterator theItr);

public:
	ProfileMgr();
	virtual ~ProfileMgr();

	void Clear();
	void Load();
	void Save();

	int GetNumProfiles() { return (int) mProfileMap.size(); }

	PlayerInfo* GetProfile(const std::string& theName);
	PlayerInfo* AddProfile(const std::string& theName);
	PlayerInfo* GetAnyProfile();
	bool DeleteProfile(const std::string& theName);
	bool RenameProfile(const std::string& theOldName, const std::string& theNewName);

	const ProfileMap& GetProfileMap() { return mProfileMap; }
};

} // namespace Sexy

#endif
