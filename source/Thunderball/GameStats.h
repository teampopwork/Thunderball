#ifndef __GAMESTATS_H__
#define __GAMESTATS_H__

namespace Sexy
{
class DataSync;

class GameStats
{
public:
    int mUnk0x0;
    int mUnk0x4;
    int mUnk0x8;
    int mUnk0xc;
    int mUnk0x10;
    int mUnk0x14;
    int mUnk0x18;
    int mUnk0x1c;
    int mUnk0x20;
    int mUnk0x24;
    int mUnk0x28;
    int mUnk0x2c;
    int mUnk0x30;
    int mUnk0x34;
    int mUnk0x38;
    int mUnk0x3c;
    int mUnk0x40;
    int mUnk0x44;
    int mUnk0x48;
    int mUnk0x4c;
    int mUnk0x50;
    int mUnk0x54;
    int mUnk0x58;
    int mUnk0x5c;
    int mUnk0x60;
    int mUnk0x64;
    int mUnk0x68;

    GameStats();
    void Add(GameStats* theStats);
    void CheckBestShot(int theScore);
    int GetTotalFreeBalls();
    int GetTotalStylePoints();
    int GetTotalStyleShots();
    void Reset();
    void SyncState(DataSync* theSync);
};

} // namespace Sexy

#endif // __GAMESTATS_H__