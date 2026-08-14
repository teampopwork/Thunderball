#ifndef __HIGHSCORE_MGR_H__
#define __HIGHSCORE_MGR_H__

#include "DataSync.h"

#include <list>
#include <map>
#include <string>
namespace Sexy
{
class HighScoreEntry {
public:
	std::string mName;
	int mScore;
	bool mIsActive;

	HighScoreEntry();
	void SyncState(DataSync& theSync);
};

class HighScoreMgr {
public:
	std::map<std::string, std::list<HighScoreEntry> > mHighScores;

	HighScoreMgr();
	virtual ~HighScoreMgr();

	void CreateDefHighScores(std::list<HighScoreEntry>* theList, std::string* param_1);
	void SyncState(DataSync& theSync);
	void Save();
	void Load();
	std::list<HighScoreEntry>* GetScores(std::string* param_1, bool param_2);
	void Submit(std::string* name, std::string* param2, int score, bool param4, bool param5);
};

struct DataSyncFunc_SyncHighScoreEntry { void Sync(DataSync &theSync, HighScoreEntry &theVal) { theVal.SyncState(theSync); } };
struct DataSyncFunc_SyncHighScoreList { void Sync(DataSync &theSync, std::list<HighScoreEntry> &theVal) { DataSync_SyncSTLListImplSimple(theSync, theVal, DataSyncFunc_SyncHighScoreEntry()); } };


} // namespace Sexy

#endif // __HIGHSCORE_MGR_H__
