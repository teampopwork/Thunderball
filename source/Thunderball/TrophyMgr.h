
#ifndef __TROPHY_MGR_H__
#define __TROPHY_MGR_H__

#include <string>

namespace Sexy
{
class ThunderballApp;
class ConfigParser;
struct TrophyInfo;
struct TrophyPage;

class TrophyMgr {
public:
	TrophyMgr(ThunderballApp* theApp);
	virtual ~TrophyMgr();

	void Clear();

	bool Load(char* theFile);
	bool ReadConfig(const std::string& thePath);
	bool ReadTrophyPage(ConfigParser* theParser);
	bool ReadTrophyConfig(ConfigParser* theParser, TrophyInfo* theInfo);

	TrophyInfo* GetTrophyInfoById(int theId);
	TrophyPage* GetTrophyPage(int theId);

private:
	ThunderballApp* mApp;
};

} // namespace Sexy

#endif // __TROPHY_MGR_H__
