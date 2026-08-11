#ifndef __ENDLEVELDIALOG_H__
#define __ENDLEVELDIALOG_H__

#include "ConstEnums.h"
#include "ThunderDialog.h"

#include <SexyAppFramework/Widget.h>

#include <list>
#include <string>

namespace Sexy
{
class Board;
class Graphics;
class HighScoreEntry;
class ThunderballApp;
class ThunderButton;

// SIZE: 0x260
class EndLevelDialog : public ThunderDialog {
public:
	ThunderballApp* mApp; // +0x178
	Board* mBoard; // +0x17c
	int mUnk0x180; // +0x180
	ThunderButton* mUnk0x184; // +0x184
	ThunderButton* mUnk0x188; // +0x188
	int mUnk0x18c; // +0x18c
	int mUnk0x190; // +0x190
	bool mShowNoButton; // +0x194
	bool mShowYesButton; // +0x195
	char mPadding0x196[0x2]; // +0x196
	int mUnk0x198; // +0x198
	int mUnk0x19c; // +0x19c
	int mUnk0x1a0; // +0x1a0
	int mUnk0x1a4; // +0x1a4
	int mUnk0x1a8; // +0x1a8
	int mUnk0x1ac; // +0x1ac
	int mUnk0x1b0; // +0x1b0
	int mUnk0x1b4; // +0x1b4
	int mUnk0x1b8; // +0x1b8
	int mUnk0x1bc; // +0x1bc
	std::string mUnk0x1c0; // +0x1c0
	std::string mUnk0x1dc; // +0x1dc
	HighScoreEntry* mHighScoreEntry; // +0x1f8
	int mUnk0x1fc; // +0x1fc
	int mUnk0x200; // +0x200
	int mUnk0x204; // +0x204
	int mUnk0x208; // +0x208
	int mUnk0x20c; // +0x20c
	int mUnk0x210; // +0x210
	int mUnk0x214; // +0x214
	int mUnk0x218; // +0x218
	int mUnk0x21c; // +0x21c
	int mUnk0x220; // +0x220
	int mUnk0x224; // +0x224
	int mUnk0x228; // +0x228
	int mUnk0x22c; // +0x22c
	int mUnk0x230; // +0x230
	int mUnk0x234; // +0x234
	int mUnk0x238; // +0x238
	int mUnk0x23c; // +0x23c
	int mUnk0x240; // +0x240
	int mUnk0x244; // +0x244
	int mUnk0x248; // +0x248
	int mUnk0x24c; // +0x24c
	int mUnk0x250; // +0x250
	bool mUnk0x254; // +0x254
	char mPadding0x255[3]; // +0x255
	int mUnk0x258; // +0x258
	int mUnk0x25c; // +0x25c

	EndLevelDialog(Board* param_1);
	virtual ~EndLevelDialog();

	virtual void Resize(int param_1, int param_2, int param_3, int param_4);
	virtual void SetVisible(bool param_1);
	virtual void Update();
	virtual void MouseMove(int param_1, int param_2);
	virtual void MouseDown(int param_1, int param_2, int param_3);
	virtual void MouseLeave();
	virtual void Draw(Graphics* param_1);
	virtual void ButtonDepress(int param_1);
	virtual int GetPreferredHeight(int param_1);

	void UpdateStats();
	void DrawAdventureWin(Graphics* param_1);
	void DrawChallengeResult(Graphics* param_1);
	void DrawTip(Graphics* param_1);
	void ComputeStats();
	void FinishHighScoreEntryDialog(std::string& param_1);
	void InitTip();
	void Init(EndLevelMode param_1, std::list<int>* param_2);
	void DrawHighScores(Graphics* param_1);
	void DrawAdventureComplete(Graphics* param_1);
	void DrawTwoPlayerResult(Graphics* param_1);
	void DrawStats(Graphics* param_1);
};

} // namespace Sexy

#endif // __ENDLEVELDIALOG_H__
