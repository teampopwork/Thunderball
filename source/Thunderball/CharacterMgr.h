#ifndef __CHARACTERMGR_H__
#define __CHARACTERMGR_H__

#include <string>
#include <vector>

namespace Sexy
{
class Board;
class Graphics;
class ConfigParser;
class DataSync;
class Image;
class ImageMgr;

class CharacterInfo {
public:
	std::vector<int> mFrames;
	std::vector<std::string> mTips;
	int mUnk0x20;
	int mUnk0x24;
	int mUnk0x28;
	std::string mName;
	std::string mDescription;
	int mUnk0x64;
	int mUnk0x68;
	int mUnk0x6C;
	int mUnk0x70;
	int mUnk0x74;
	int mUnk0x78;
};

class CharacterMgr {
public:
	ImageMgr* mImageMgr;
	Image* mImage1;
	Image* mImage2;
	std::vector<CharacterInfo> mCharacters;
	int mCurCharacter;
	int mUnk0x24;
	int mUnk0x28;
	int mUnk0x2C;
	int mUnk0x30;
	int mUnk0x34;
	int mUnk0x38;
	int mUnk0x3C;
	int mUnk0x40;
	char mUnk0x44;
	bool mUnk0x45;
	float mUnk0x48;
	float mUnk0x4C;
	float mUnk0x50;
	float mUnk0x54;
	float mUnk0x58;
	float mUnk0x5C;
	float mUnk0x60;
	float mUnk0x64;
	float mUnk0x68;
	float mUnk0x6C;
	float mUnk0x70;
	bool mUnk0x74;
	int mUnk0x78;
	int mUnk0x7C;
	float mUnk0x80;
	float mUnk0x84;
	int mUnk0x88;
	int mUnk0x8C;
	int mUnk0x90;

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
	CharacterInfo* GetCharacterInfo(int param_1);
	CharacterInfo* GetCharacterInfoSafe(int param_1);
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
