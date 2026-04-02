#ifndef __HIGHSCORE_MGR_H__
#define __HIGHSCORE_MGR_H__

#include <string>
#include <list>


namespace Sexy
{
class DataSync;

class HighScoreMgr {
public:
	HighScoreMgr();
	virtual ~HighScoreMgr();

	void CreateDefHighScores(std::list<std::string>* theList, std::string* param);
	void SyncState(DataSync* theSync);
	void Save();
	void Load();
	void GetScores(std::string* param_1, bool param_2);
	void Submit(std::string* name, std::string* param2, int score, bool param4, bool param5);
};

} // namespace Sexy

#endif // __HIGHSCORE_MGR_H__
