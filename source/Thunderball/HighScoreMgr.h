#ifndef __HIGHSCORE_MGR_H__
#define __HIGHSCORE_MGR_H__

#include <list>
#include <string>

namespace Sexy
{
class DataSync;

class HighScoreEntry {};

class HighScoreMgr {
public:
	HighScoreMgr();
	virtual ~HighScoreMgr();

	void CreateDefHighScores(std::list<HighScoreEntry>* theList, std::string* param_1);
	void SyncState(DataSync* theSync);
	void Save();
	void Load();
	std::list<HighScoreEntry>* GetScores(std::string* param_1, bool param_2);
	void Submit(std::string* name, std::string* param2, int score, bool param4, bool param5);
};

} // namespace Sexy

#endif // __HIGHSCORE_MGR_H__
