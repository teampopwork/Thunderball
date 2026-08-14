#include "HighScoreMgr.h"

#include "DataSync.h"

#include <cstdlib>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x0040a920
HighScoreEntry::HighScoreEntry() {}

// FUNCTION: POPCAPGAME1 0x00436670
void HighScoreEntry::SyncState(DataSync& theSync)
{
	theSync.SyncString(mName);
	theSync.SyncLong(mScore);
}

// FUNCTION: POPCAPGAME1 0x00473e00
HighScoreMgr::HighScoreMgr()
{
}

// SYNTHETIC: POPCAPGAME1 0x00473e40
// Sexy::HighScoreMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00471e70
HighScoreMgr::~HighScoreMgr()
{
}

// FUNCTION: POPCAPGAME1 0x0045c300
void HighScoreMgr::CreateDefHighScores(std::list<HighScoreEntry>* theList, std::string* param)
{
	const char* aNames[] = {
		"Andy", "Anthony", "Ben", "Bill", "Brian", "Ace", "Chad", "Dave",
		"Del", "Ed", "Jimmy Goggle", "Eric", "Hans", "Isaac", "Jason", "James",
		"Jeff", "Joe", "John", "Josh", "Juho", "Kathy", "Katrina", "Mark",
		"Matt", "Max", "Shawn", "Stephen", "Sukhbir", "Tysen", "Walter", "Wes"
	};

	bool isAdventure = param->compare(0, param->length(), "_adventure", 10) == 0;
	int aScore = isAdventure ? 20000000 : 300000;

	for (int i = 0; i < 10; ++i) {
		HighScoreEntry anEntry;
		anEntry.mName = aNames[rand() % 32];
		anEntry.mScore = aScore;
		theList->push_back(anEntry);

		if (isAdventure) {
			aScore -= i == 0 ? 3000000 : 1500000;
		}
		else {
			aScore -= 10000;
		}
	}
}

// TEMPLATE: POPCAPGAME1 0x00471da0
// Sexy::DataSync_SyncSTLMapImplSimple<std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > > > >,Sexy::DataSyncFunc_SyncString,Sexy::DataSyncFunc_SyncHighScoreList>

// TEMPLATE: POPCAPGAME1 0x0046e480
// Sexy::DataSync_SyncSTLMapImpl<std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > > > >,Sexy::DataSyncFunc_SyncString,Sexy::DataSyncFunc_SyncHighScoreList,Sexy::DataSyncFunc_AllocStack<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,Sexy::DataSyncFunc_AllocStack<std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > > >

// TEMPLATE: POPCAPGAME1 0x00469020
// std::_Tree<std::_Tmap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > > >,0> >::_Erase

// TEMPLATE: POPCAPGAME1 0x0040abd0
// Sexy::DataSyncFunc_AllocStack<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >::Alloc

// TEMPLATE: POPCAPGAME1 0x00454510
// Sexy::DataSyncFunc_AllocStack<std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > >::Alloc

// TEMPLATE: POPCAPGAME1 0x0043f380
// std::list<Sexy::SexyMatrix3,std::allocator<Sexy::SexyMatrix3> >::_Buynode

// TEMPLATE: POPCAPGAME1 0x00462850
// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > >::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > >(class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const &, class std::list<class Sexy::HighScoreEntry, class std::allocator<class Sexy::HighScoreEntry>> const &)

// TEMPLATE: POPCAPGAME1 0x00460010
// std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >

// TEMPLATE: POPCAPGAME1 0x004543f0
// std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::_Insert<std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::_Const_iterator<1> >

// TEMPLATE: POPCAPGAME1 0x0044cd90
// std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::_Buynode

// TEMPLATE: POPCAPGAME1 0x00445d00
// std::_Construct<Sexy::HighScoreEntry,Sexy::HighScoreEntry>

// TEMPLATE: POPCAPGAME1 0x004de610
// std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::_Incsize

// TEMPLATE: POPCAPGAME1 0x004fc300
// std::_Tree<std::_Tmap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >,0> >::const_iterator::operator!=

// TEMPLATE: POPCAPGAME1 0x0043da20
// std::list<Sexy::ResourceManager::BaseRes *,std::allocator<Sexy::ResourceManager::BaseRes *> >::_Iterator<1>::operator--

// TEMPLATE: POPCAPGAME1 0x0044c1e0
// std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >::erase

// TEMPLATE: POPCAPGAME1 0x004fc4b0
// std::list<Sexy::ResourceManager::BaseRes *,std::allocator<Sexy::ResourceManager::BaseRes *> >::_Const_iterator<1>::operator++

// TEMPLATE: POPCAPGAME1 0x0041ff30
// std::list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int> > >::~list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int> > >

// TEMPLATE: POPCAPGAME1 0x0046dc30
// std::_Tree<std::_Tmap_traits<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> > > >,0> >::insert(class std::_Tree<class std::_Tmap_traits<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>, class std::list<class Sexy::HighScoreEntry, class std::allocator<class Sexy::HighScoreEntry>>, struct std::less<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>>, class std::allocator<struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const, class std::list<class Sexy::HighScoreEntry, class std::allocator<class Sexy::HighScoreEntry>>>>, 0>>::iterator, struct std::pair<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const, class std::list<class Sexy::HighScoreEntry, class std::allocator<class Sexy::HighScoreEntry>>> const &)

// TEMPLATE: POPCAPGAME1 0x0041dfd0
// std::list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,int> > >::clear

// TEMPLATE: POPCAPGAME1 0x00460120
// Sexy::DataSync_SyncSTLListImplSimple<std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,Sexy::DataSyncFunc_SyncHighScoreEntry>

// TEMPLATE: POPCAPGAME1 0x0045a130
// Sexy::DataSync_SyncSTLListImpl<std::list<Sexy::HighScoreEntry,std::allocator<Sexy::HighScoreEntry> >,Sexy::DataSyncFunc_SyncHighScoreEntry,Sexy::DataSyncFunc_AllocStack<Sexy::HighScoreEntry> >

// TEMPLATE: POPCAPGAME1 0x004428c0
// Sexy::DataSyncFunc_AllocStack<Sexy::HighScoreEntry>::Alloc

// FUNCTION: POPCAPGAME1 0x00471eb0
void HighScoreMgr::SyncState(DataSync& theSync)
{
	int aVersion = 2;
	theSync.SyncLong(aVersion);
	theSync.mVersion = aVersion;
	if (1 < aVersion) {
		DataSync_SyncSTLMapImplSimple(theSync, mHighScores, DataSyncFunc_SyncString(), DataSyncFunc_SyncHighScoreList());
	}
}

// STUB: POPCAPGAME1 0x00472060
void HighScoreMgr::Save()
{
}

// FUNCTION: POPCAPGAME1 0x00471f00
void HighScoreMgr::Load()
{
	mHighScores.clear();
	DataReader aReader;
	if (aReader.OpenFile(GetAppDataFolder() + "userdata/highscores.dat")) {
		DataSync aSync(aReader);
		SyncState(aSync);
		aSync.SyncPointers();
	}
}

// FUNCTION: POPCAPGAME1 0x00472430
std::list<HighScoreEntry>* HighScoreMgr::GetScores(std::string* param_1, bool param_2)
{
	if (param_1->empty()) {
		return NULL;
	}

	std::list<HighScoreEntry>& aScores = mHighScores[*param_1];
	if (aScores.empty()) {
		CreateDefHighScores(&aScores, param_1);
	}

	if (param_2) {
		std::list<HighScoreEntry>::iterator it = aScores.begin();
		while (it != aScores.end() && !it->mIsActive) {
			++it;
		}
		if (it == aScores.end()) {
			return NULL;
		}
	}

	return &aScores;
}

// STUB: POPCAPGAME1 0x00472210
void HighScoreMgr::Submit(std::string* name, std::string* param2, int score, bool param4, bool param5)
{
}
