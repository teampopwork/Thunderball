#ifndef __CHARACTERDIALOG_H__
#define __CHARACTERDIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/CheckboxListener.h>
#include <SexyAppFramework/DialogListener.h>

#include <string>
#include <vector>

namespace Sexy {
class Board;
class ButtonWidget;
class CharacterMgr;
class Checkbox;
class Graphics;
class Image;
class PlayerInfo;
class ThunderballApp;
class WidgetManager;

struct CharacterButtonEntry {
	ButtonWidget* mButton;
	int mUnk0x4;
	int mUnk0x8;
};

// SIZE: 0x248
class CharacterDialog : public ThunderDialog, public CheckboxListener, public DialogListener {
public:
	ThunderballApp* mApp; // +0x180
	Board* mBoard; // +0x184
	CharacterMgr* mCharacterMgr; // +0x188
	PlayerInfo* mPlayerInfo; // +0x18c
	ButtonWidget* mNameButtons[2]; // +0x190
	Checkbox* mPlayCheckboxes[2]; // +0x198
	Checkbox* mDifficultyCheckboxes[4]; // +0x1a0
	Image* mCharacterImage; // +0x1b0
	Image* mCharacterShadowImage; // +0x1b4
	Image* mRandomImage; // +0x1b8
	int mUnk0x1bc; // +0x1bc
	std::string mNames[2]; // +0x1c0
	int mNameX[2]; // +0x1f8
	float mUnk0x200; // +0x200
	float mUnk0x204; // +0x204
	int mUnk0x208; // +0x208
	int mUnk0x20c; // +0x20c
	int mUnk0x210; // +0x210
	int mUnk0x214; // +0x214
	bool mUnk0x218; // +0x218
	bool mUnk0x219; // +0x219
	bool mUnk0x21a; // +0x21a
	bool mUnk0x21b; // +0x21b
	int mUnk0x21c; // +0x21c
	int mUnk0x220; // +0x220
	int mUnk0x224; // +0x224
	std::vector<CharacterButtonEntry> mCharacterButtons[2]; // +0x228

    CharacterDialog(Board* param_1);
    virtual ~CharacterDialog();

    virtual void AddedToManager(WidgetManager* param_1);
    virtual void RemovedFromManager(WidgetManager* param_1);
    virtual void Resize(int param_1, int param_2, int param_3, int param_4);
    virtual int GetPreferredHeight(int param_1);
    virtual void Update();
    virtual void Draw(Graphics* param_1);

    
    void SyncDifficultyVisibility();
    int CanSelectCharacter(int param_1);
    void SyncNamePos();

    void CheckboxChecked(int param_1, bool param_2);

    void SelectCharacter(int param_1, int param_2);
    void ButtonPress(int param_1, int param_2);

    void DrawCharacterInfo(Graphics* param_1, int param_2);

    void SaveDetails();
    void DialogButtonDepress(int param_1, int param_2);
    void ButtonDepress(int param_1);
};

} // namespace Sexy

#endif // __CHARACTERDIALOG_H__
