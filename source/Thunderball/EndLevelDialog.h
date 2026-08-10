#ifndef __ENDLEVELDIALOG_H__
#define __ENDLEVELDIALOG_H__

#include "ConstEnums.h"
#include "ThunderDialog.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

#include <list>
#include <string>

namespace Sexy
{
class Board;
class Graphics;

class EndLevelDialog : public ThunderDialog, public ButtonListener {
public:
	Board* mBoard; // +0x17c
	int mUnk0x180; // +0x180
	char mPadding0x184[0x10]; // +0x184
	bool mShowNoButton; // +0x194
	bool mShowYesButton; // +0x195
	char mPadding0x196[0x2]; // +0x196
	int mUnk0x198; // +0x198
	char mPadding0x19c[0x28]; // +0x19c
	std::string mUnk0x1c4; // +0x1c4
	std::string mUnk0x1e0; // +0x1e0
	char mPadding0x1fc[0x5c]; // +0x1fc
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
