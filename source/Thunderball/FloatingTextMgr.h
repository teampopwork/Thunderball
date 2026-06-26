#ifndef __FLOATING_TEXT_MGR_H__
#define __FLOATING_TEXT_MGR_H__

namespace Sexy
{
class Graphics;
class DataSync;

class FloatingText {
	public:
		int mUnk0x54;
		int mUnk0x60;
		int mUnk0x68;
		int mUnk0x74;
		int mUnk0x78;
		int mUnk0x8c;
};

class FloatingTextMgr {
public:
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
