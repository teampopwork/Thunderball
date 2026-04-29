#ifndef __ENDLEVELDIALOG_H__
#define __ENDLEVELDIALOG_H__

#include 

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/Widget.h>

#include <list>
#include <string>

namespace Sexy
{
class Board;
class Graphics;

class EndLevelDialog : public Widget, public ButtonListener {
public:
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
	void FinishHighScoreEntryDialog(std::string* param_1);
	void InitTip();
	void Init(EndLevelMode param_1, std::list<int>* param_2);
	void DrawHighScores(Graphics* param_1);
	void DrawAdventureComplete(Graphics* param_1);
	void DrawTwoPlayerResult(Graphics* param_1);
	void DrawStats(Graphics* param_1);
};

} // namespace Sexy

#endif // __ENDLEVELDIALOG_H__