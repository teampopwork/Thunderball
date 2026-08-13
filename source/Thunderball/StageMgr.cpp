#include "StageMgr.h"

#include "ConfigParser.h"
#include "PlayerInfo.h"
#include "ThunderballApp.h"


using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00441fd0
LevelInfo::LevelInfo()
{
}

// SYNTHETIC: POPCAPGAME1 0x00442f00
// Sexy::LevelInfo::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00442020
LevelInfo::~LevelInfo()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x0044b6b0
// Sexy::StoryData::StoryData

// TEMPLATE: POPCAPGAME1 0x0044a860
// std::_Destroy_range<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >(class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> *, class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> *, class std::allocator<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>> &, struct std::_Nonscalar_ptr_iterator_tag)

// FUNCTION: POPCAPGAME1 0x0045f810
// Sexy::StoryData::~StoryData

// FUNCTION: POPCAPGAME1 0x00461a00
StageInfo::StageInfo()
{
}

// SYNTHETIC: POPCAPGAME1 0x00464d90
// Sexy::StageInfo::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00461a70
StageInfo::~StageInfo()
{
}

// FUNCTION: POPCAPGAME1 0x0043d7d0
LevelInfo* StageInfo::GetLevelInfo(int param_1)
{
	if (param_1 < 0 || param_1 >= (int) mUnk0x5c.size()) {
		return NULL;
	}
	else {
		return mUnk0x5c[param_1].get();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FUNCTION: POPCAPGAME1 0x00461940
StageMgr::StageMgr(ThunderballApp* theApp)
{
	mApp = theApp;
}

// SYNTHETIC: POPCAPGAME1 0x004619d0
// Sexy::StageMgr::`scalar deleting destructor'

// TEMPLATE: POPCAPGAME1 0x00445d70
//  std::_Destroy_range<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >

// TEMPLATE: POPCAPGAME1 0x0044c820
// std::_Tree<std::_Tmap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Sexy::SmartPtr<Sexy::LevelInfo>,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Sexy::SmartPtr<Sexy::LevelInfo> > >,1> >::erase(class std::_Tree<class std::_Tmap_traits<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>, class Sexy::SmartPtr<class Sexy::LevelInfo>, struct std::less<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>>, class std::allocator<struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const, class Sexy::SmartPtr<class Sexy::LevelInfo>>>, 1>>::iterator, class std::_Tree<class std::_Tmap_traits<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>, class Sexy::SmartPtr<class Sexy::LevelInfo>, struct std::less<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>>, class std::allocator<struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const, class Sexy::SmartPtr<class Sexy::LevelInfo>>>, 1>>::iterator)

// FUNCTION: POPCAPGAME1 0x0045f380
StageMgr::~StageMgr()
{
}

// FUNCTION: POPCAPGAME1 0x0045f460
void StageMgr::Clear()
{
	mUnk0x8 = 0;
	mUnk0xc.clear();
	mUnk0x1c.clear();
	mUnk0x2c.clear();
}

// FUNCTION: POPCAPGAME1 0x00442ff0
LevelInfo* StageMgr::GetLevelInfoByName(const std::string& theName)
{
	std::multimap<std::string, SmartPtr<LevelInfo>>::iterator it = mUnk0x1c.find(theName);
	if (it == mUnk0x1c.end()) {
		return NULL;
	}
	else {
		return it->second.get();
	}
}

// FUNCTION: POPCAPGAME1 0x0043d870
int StageMgr::GetNumStages()
{
	return (int) mUnk0xc.size();
}

// STUB: POPCAPGAME1 0x00459060
void StageMgr::GetRandomLevel(
	int param_1,
	int param_2,
	int* param_3,
	int* param_4,
	bool param_5,
	int param_6,
	bool param_7
)
{
	printf("StageMgr::GetRandomLevel stub called\n");
}

// FUNCTION: POPCAPGAME1 0x004592b0
void StageMgr::GetRandomLevel(PlayerInfo* param_1, int* param_2, int* param_3, bool param_4, int param_5, bool param_6)
{
	GetRandomLevel(param_1->mUnk0x28, param_1->mUnk0x2c, param_2, param_3, param_4, param_5, true);
}

// FUNCTION: POPCAPGAME1 0x004592e0
LevelInfo* StageMgr::GetRandomLevel(PlayerInfo* param_1, bool param_2, int param_3)
{
	int stageNum = -1;
	int levelNum = -1;
	GetRandomLevel(param_1, &stageNum, &levelNum, param_2, param_3, true);
	StageInfo* stage = GetStageInfo(stageNum);
	if (stage == NULL) {
		return NULL;
	}
	else {
		return stage->GetLevelInfo(levelNum);
	}
}

// FUNCTION: POPCAPGAME1 0x0043d820
StageInfo* StageMgr::GetStageInfo(int param_1)
{
	if (-1 <= param_1 && param_1 < (int) mUnk0xc.size()) {
		return mUnk0xc[param_1].get();
	}
	else {
		return NULL;
	}
}

// FUNCTION: POPCAPGAME1 0x00442f30
const std::string& StageMgr::GetTip(unsigned long param_1)
{
	if (mUnk0x2c.empty()) {
		static std::string anEmptyTip;
		return anEmptyTip;
	}

	return mUnk0x2c[param_1 % mUnk0x2c.size()];
}

// FUNCTION: POPCAPGAME1 0x00468830
void StageMgr::Load(char* param_1)
{
	if (param_1 != NULL) {
		std::string path = param_1;
		ReadConfig(path);
	}
	else {
		std::string path = "levels/stages.cfg";
		ReadConfig(path);
	}
}

// FUNCTION: POPCAPGAME1 0x00437620
void StageMgr::MarkLastUseTime(LevelInfo* param_1)
{
	param_1->mUnk0x8 = ++mUnk0x8;
}

// FUNCTION: POPCAPGAME1 0x004685f0
void StageMgr::ReadConfig(std::string& pathString)
{
	Clear();

	ConfigParser parser(true);
	parser.Open(pathString, true);

	bool inStageGroup = false;

	while (parser.ReadNext()) {
		if (parser.mUnk0x9c == 1) {
			if (parser.GroupTypeIs("Stage", true)) {
				inStageGroup = true;

				SmartPtr<StageInfo> stageInfo = new StageInfo();

				mUnk0xc.push_back(stageInfo);
			}
			else {
				parser.ErrorUnexpectedGroupType();
			}
		}
		else if (parser.mUnk0x9c == 2) {
			inStageGroup = false;
		}
		else {
			if (!inStageGroup) {
				ReadKeyVal(&parser);
			}
			else {
				StageInfo* currentStage = mUnk0xc.back();
				ReadStageConfig(&parser, currentStage);
			}
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00468300
void StageMgr::ReadKeyVal(ConfigParser* theConfigParser)
{
	StringParser* aStringParser = theConfigParser->GetValParser();
	if (stricmp(theConfigParser->mUnk0x64.c_str(), "ExcludeRandStages") == 0) {
		if (aStringParser->mUnk0x4 < aStringParser->mUnk0x8) {
			do {
				int anInt = aStringParser->ReadInt();
				StageInfo* aStageInfo = GetStageInfo(anInt);
				if (aStageInfo == NULL) {
					theConfigParser->Error(StrFormat("Stage not found: %d", anInt - 1), false, true);
				}

				for (int i = 0; i < aStageInfo->mUnk0x5c.size(); i++) {
					aStageInfo->mUnk0x5c[i]->mUnk0x84 = true;
				}
			} while (aStringParser->CheckNextChar(',') && aStringParser->mUnk0x4 < aStringParser->mUnk0x8);
		}
	}
	else {
		if (stricmp(theConfigParser->mUnk0x64.c_str(), "IncludeRandStages") == 0) {
			if (aStringParser->mUnk0x4 < aStringParser->mUnk0x8) {
				do {
					int anInt = aStringParser->ReadInt();
					StageInfo* aStageInfo = GetStageInfo(anInt);
					if (aStageInfo == NULL) {
						theConfigParser->Error(StrFormat("Stage not found: %d", anInt - 1), false, true);
					}

					for (int i = 0; i < aStageInfo->mUnk0x5c.size(); i++) {
						aStageInfo->mUnk0x5c[i]->mUnk0x84 = false;
					}
				} while (aStringParser->CheckNextChar(',') && aStringParser->mUnk0x4 < aStringParser->mUnk0x8);
			}
		}
		else {
			if (stricmp(theConfigParser->mUnk0x64.c_str(), "ExcludeRandLevels") != 0) {
				if (stricmp(theConfigParser->mUnk0x64.c_str(), "IncludeRandLevels") != 0) {
					if (stricmp(theConfigParser->mUnk0x64.c_str(), "Tip") == 0) {
						std::string aTip;
						if (aStringParser->ReadString(aTip, true, true)) {
							mUnk0x2c.push_back(aTip);
						}
					}
				}
				else {
					theConfigParser->ErrorUnexpectedKey();
				}
				return;
			}
		}

		bool local_31 = stricmp(theConfigParser->mUnk0x64.c_str(), "ExcludeRandLevels") == 0;
		while (aStringParser->mUnk0x4 < aStringParser->mUnk0x8) {
			std::string aLevelName = aStringParser->ReadString(true, true);
			LevelInfo* aLevelInfo = GetLevelInfoByName(aLevelName);
			if (aLevelInfo == NULL) {
				theConfigParser->Error("Level not found: " + aLevelName, false, true);
			}
			else {
				aLevelInfo->mUnk0x84 = local_31;
			}

			if (!aStringParser->CheckNextChar(',')) {
				break;
			}
		}
	}
}

// STUB: POPCAPGAME1 0x00467d50
void StageMgr::ReadStageConfig(ConfigParser* theConfigParser, StageInfo* param_2)
{
}

// FUNCTION: POPCAPGAME1 0x0043d890
void StageMgr::ResetLastUseTimes()
{
	mUnk0x8 = 0;
	for (int aStage = 0; aStage < (int) mUnk0xc.size(); aStage++) {
		StageInfo* aStageInfo = mUnk0xc[aStage].get();
		for (int aLevel = 0; aLevel < (int) aStageInfo->mUnk0x5c.size(); aLevel++) {
			aStageInfo->mUnk0x5c[aLevel]->mUnk0x8 = -1000;
		}
	}
}
