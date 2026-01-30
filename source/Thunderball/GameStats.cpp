#include "GameStats.h"
#include "ThunderCommon.h"
#include "DataSync.h"

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00407450
GameStats::GameStats()
{
    Reset();
}

// FUNCTION: POPCAPGAME1 0x00402ed0
void GameStats::Add(GameStats* theStats)
{
    mUnk0x0 += theStats->mUnk0x0;

    if (theStats->mUnk0x4 > mUnk0x4)
    {
        mUnk0x4 = theStats->mUnk0x4;
    }

    if (theStats->mUnk0x8 > mUnk0x8)
    {
        mUnk0x8 = theStats->mUnk0x8;
    }
    
    mUnk0xc += theStats->mUnk0xc;
    mUnk0x10 += theStats->mUnk0x10;
    mUnk0x14 += theStats->mUnk0x14;
    mUnk0x18 += theStats->mUnk0x18;

    int* src = &theStats->mUnk0x24;
    int* dest = &mUnk0x1c;
    
    int i = 4;
    do {
        dest[0] += src[-2]; 
        dest[1] += src[-1]; 
        dest[2] += src[0];  
        dest[3] += src[1];  
        dest[4] += src[2];  

        dest += 5;
        src += 5;

    } while (--i);
}

// FUNCTION: POPCAPGAME1 0x00402eb0
void GameStats::CheckBestShot(int theScore)
{
    if (theScore > mUnk0x4) {
        mUnk0x4 = theScore;
    }
}

// FUNCTION: POPCAPGAME1 0x00402f50
int GameStats::GetTotalFreeBalls()
{
    return 0;
}

// FUNCTION: POPCAPGAME1 0x00407460
int GameStats::GetTotalStylePoints()
{
    return 0;
}

// FUNCTION: POPCAPGAME1 0x00402f60
int GameStats::GetTotalStyleShots() 
{
    return 0;
}

// FUNCTION: POPCAPGAME1 0x00402da0
void GameStats::Reset()
{
    mUnk0x0 = 0;
    mUnk0x4 = 0;
    mUnk0x8 = 0;
    mUnk0xc = 0;
    mUnk0x10 = 0;
    mUnk0x14 = 0;
    mUnk0x18 = 0;
    mUnk0x1c = 0;
    mUnk0x20 = 0;
    mUnk0x24 = 0;
    mUnk0x28 = 0;
    mUnk0x2c = 0;
    mUnk0x30 = 0;
    mUnk0x34 = 0;
    mUnk0x38 = 0;
    mUnk0x3c = 0;
    mUnk0x40 = 0;
    mUnk0x44 = 0;
    mUnk0x48 = 0;
    mUnk0x4c = 0;
    mUnk0x50 = 0;
    mUnk0x54 = 0;
    mUnk0x58 = 0;
    mUnk0x5c = 0;
    mUnk0x60 = 0;
    mUnk0x64 = 0;
    mUnk0x68 = 0;
}


// FUNCTION: POPCAPGAME1 0x00402e00
void GameStats::SyncState(DataSync* theSync) 
{
    if (theSync->mReader != NULL) 
    {
        Reset();
    }

    int byte = 1;
    theSync->SyncByte(byte);
    theSync->SyncLong(mUnk0x0);
    theSync->SyncLong(mUnk0x4);
    theSync->SyncLong(mUnk0x8);
    theSync->SyncLong(mUnk0xc);

}
