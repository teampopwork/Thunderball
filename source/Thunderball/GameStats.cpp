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
    m_unk0x0 += theStats->m_unk0x0;

    if (theStats->m_unk0x4 > m_unk0x4)
    {
        m_unk0x4 = theStats->m_unk0x4;
    }

    if (theStats->m_unk0x8 > m_unk0x8)
    {
        m_unk0x8 = theStats->m_unk0x8;
    }
    
    m_unk0xc += theStats->m_unk0xc;
    m_unk0x10 += theStats->m_unk0x10;
    m_unk0x14 += theStats->m_unk0x14;
    m_unk0x18 += theStats->m_unk0x18;

    int* src = &theStats->m_unk0x24;
    int* dest = &m_unk0x1c;
    
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
    if (theScore > m_unk0x4) {
        m_unk0x4 = theScore;
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
    m_unk0x0 = 0;
    m_unk0x4 = 0;
    m_unk0x8 = 0;
    m_unk0xc = 0;
    m_unk0x10 = 0;
    m_unk0x14 = 0;
    m_unk0x18 = 0;
    m_unk0x1c = 0;
    m_unk0x20 = 0;
    m_unk0x24 = 0;
    m_unk0x28 = 0;
    m_unk0x2c = 0;
    m_unk0x30 = 0;
    m_unk0x34 = 0;
    m_unk0x38 = 0;
    m_unk0x3c = 0;
    m_unk0x40 = 0;
    m_unk0x44 = 0;
    m_unk0x48 = 0;
    m_unk0x4c = 0;
    m_unk0x50 = 0;
    m_unk0x54 = 0;
    m_unk0x58 = 0;
    m_unk0x5c = 0;
    m_unk0x60 = 0;
    m_unk0x64 = 0;
    m_unk0x68 = 0;
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
    theSync->SyncLong(m_unk0x0);
    theSync->SyncLong(m_unk0x4);
    theSync->SyncLong(m_unk0x8);
    theSync->SyncLong(m_unk0xc);

}
