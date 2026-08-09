#include "TrophyMgr.h"

using namespace Sexy;

// SYNTHETIC: POPCAPGAME1 0x004737f0
// Sexy::TrophyMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00473760
TrophyMgr::TrophyMgr(ThunderballApp* theApp)
{
	mApp = theApp;
	Clear();
}

// FUNCTION: POPCAPGAME1 0x004718d0
TrophyMgr::~TrophyMgr()
{
}

// STUB: POPCAPGAME1 0x00471960
void TrophyMgr::Clear()
{
	// TODO
}

// STUB: POPCAPGAME1 0x00474550
bool TrophyMgr::Load(char* theFile)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x00474390
bool TrophyMgr::ReadConfig(const std::string& thePath)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x00473e70
bool TrophyMgr::ReadTrophyPage(ConfigParser* theParser)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x00468900
bool TrophyMgr::ReadTrophyConfig(ConfigParser* theParser, TrophyInfo* theInfo)
{
	// TODO
	return false;
}

// STUB: POPCAPGAME1 0x004430b0
TrophyInfo* TrophyMgr::GetTrophyInfoById(int theId)
{
	std::map<int, TrophyInfo*>::iterator anItr = mTrophyInfos.find(theId);
	return anItr == mTrophyInfos.end() ? NULL : anItr->second;
}

// STUB: POPCAPGAME1 0x0043d970
TrophyPage* TrophyMgr::GetTrophyPage(int theId)
{
	if (theId >= 0 && theId < (int)mPages.size())
		return &mPages[theId];
	return NULL;
}
