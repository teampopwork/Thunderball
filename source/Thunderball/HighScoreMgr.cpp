#include "HighScoreMgr.h"

#include <cstdlib>

using namespace Sexy;

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

// STUB: POPCAPGAME1 0x00471eb0
void HighScoreMgr::SyncState(DataSync& theSync)
{
}

// STUB: POPCAPGAME1 0x00472060
void HighScoreMgr::Save()
{
}

// STUB: POPCAPGAME1 0x00471f00
void HighScoreMgr::Load()
{
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
