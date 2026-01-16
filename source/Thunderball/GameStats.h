#ifndef __GAMESTATS_H__
#define __GAMESTATS_H__

namespace Sexy
{
class DataSync;

class GameStats
{
public:
    int m_unk0x0;
    int m_unk0x4;
    int m_unk0x8;
    int m_unk0xc;
    int m_unk0x10;
    int m_unk0x14;
    int m_unk0x18;
    int m_unk0x1c;
    int m_unk0x20;
    int m_unk0x24;
    int m_unk0x28;
    int m_unk0x2c;
    int m_unk0x30;
    int m_unk0x34;
    int m_unk0x38;
    int m_unk0x3c;
    int m_unk0x40;
    int m_unk0x44;
    int m_unk0x48;
    int m_unk0x4c;
    int m_unk0x50;
    int m_unk0x54;
    int m_unk0x58;
    int m_unk0x5c;
    int m_unk0x60;
    int m_unk0x64;
    int m_unk0x68;

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