#ifndef __CHARACTERMGR_H__
#define __CHARACTERMGR_H__

#include <string>

namespace Sexy
{
class Board;
class Graphics;
class CharacterInfo;
class ConfigParser;
class DataSync;

class CharacterMgr {
public:
	CharacterMgr();
	virtual ~CharacterMgr();

	void CalcEyePos(bool param_1);
	void CalcLookPos(Board* theBoard, bool param_2);
	void CalcPowerupActive(Board* theBoard);
	void CheckCrossEyeFix();
	void Clear(bool param_1);
	void CreateShooterImage(int param_1);
	void DoCharMove(int param_1, int param_2, bool param_3);
	void DoPowerupBlink(int param_1);
	void DoPowerupCountBlink();
	void EndPowerupBlink();
	void Draw(Graphics* g, Board* theBoard);
	void DrawBack(Graphics* g1, Graphics* g2, Board* theBoard);
	void DrawFront(Graphics* g1, Graphics* g2, Board* theBoard);
	std::string* GetCharacterDesc(int param_1);
	int GetCharacterIdByName(std::string* param_1);
	int GetCharacterInfo(int param_1);
	int GetCharacterInfoSafe(int param_1);
	int GetCharacterName(int param_1);
	int GetCharacterTip(int param_1, unsigned long param_2);
	int GetCurCharFrame(CharacterInfo* param_1);
	void InitDefault();
	void Load();
	void ReadConfig(std::string* param_1);
	void ReaderCharacterConfig(ConfigParser* param_1, CharacterInfo* param_2);
	int ReadPowerupType(ConfigParser* param_1, std::string* param_2);
	void Resync();
	int SetCurCharacter(int param_1);
	void SetYinYangEye(bool param_1);
	void SyncState(DataSync& theState);
	void Update();
	void UpdatePaused();
	void UpdateSlowMo();
};
} // namespace Sexy

#endif // __CHARACTERMGR_H__
