#ifndef __FLOATING_TEXT_MGR_H__
#define __FLOATING_TEXT_MGR_H__

#include <SexyAppFramework/SmartPtr.h>

#include <list>
#include <string>
#include <utility>
#include <vector>

namespace Sexy
{
class Graphics;
class Image;
class DataSync;
class PhysObj;

class FloatingText {
public:
	Image* mImage;                                   // +0x4
	std::vector<std::string> mStrings;               // +0x8
	std::vector<int> mUnk0x18;                       // +0x18
	std::vector<std::pair<float, int> > mUnk0x28;      // +0x28
	std::vector<int> mUnk0x38;                       // +0x38
	int mUnk0x48;
	int mUnk0x4c;
	int mUnk0x50;
	int mUnk0x54;
	int mId;                                         // +0x58
	int mUnk0x5c;
	int mUnk0x60;
	int mUnk0x64;
	int mUnk0x68;
	int mUnk0x6c;
	int mUnk0x70;
	int mUnk0x74;
	int mUnk0x78;
	int mUnk0x7c;
	int mUnk0x80;
	int mUnk0x84;
	int mUnk0x88;
	int mUnk0x8c;
	float mUnk0x90;
	int mUnk0x94;
	int mUnk0x98;
	bool mUnk0x9c;
	bool mUnk0x9d;
	char mUnk0x9e[2];
	int mUnk0xa0;
	int mUnk0xa4;
	int mUnk0xa8;
	int mUnk0xac;
	int mUnk0xb0;
	RefCountPtr mUnk0xb4;
	int mUnk0xb8;
	int mUnk0xbc;

	FloatingText();
	virtual ~FloatingText();
	void AddScale(float param_1, int param_2);
	void CreateTextImage();
	void Draw(Graphics* g);
	void HoldPos(int param_1);
	void MoveTo(int param_1, int param_2, int param_3);
	void SetRefObj(PhysObj* param_1);
	void SetText(const std::string& param_1);
	void SyncState(DataSync& param_1);
	void Update();
	void UpdatePos();
	void UpdateRotation();
	void UpdateScale();
	void Reset();
};

class FloatingTextMgr {
public:
	int mNextId;                                     // +0x4
	std::list<FloatingText> mTexts;                  // +0x8

	FloatingTextMgr();
	virtual ~FloatingTextMgr();

	FloatingText* GetTextById(int param_1);
	void EraseText(int param_1);
	void Draw(Graphics* param_1, int param_2);
	void Update();
	void Clear();
	void AddText();
	void SyncState(DataSync& param_1);
};

} // namespace Sexy

#endif // __FLOATING_TEXT_MGR_H__
