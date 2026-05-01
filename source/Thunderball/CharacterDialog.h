#ifndef __CHARACTERDIALOG_H__
#define __CHARACTERDIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/CheckboxListener.h>

namespace Sexy {
class Board;
class Graphics;
class WidgetManager;

class CharacterDialog : public ThunderDialog, public CheckboxListener {
public:
    bool mUnk0x219;

    CharacterDialog(Board* param_1);
    virtual ~CharacterDialog();

    virtual void AddedToManager(WidgetManager* param_1);
    virtual void RemovedFromManager(WidgetManager* param_1);
    virtual void Resize(int param_1, int param_2, int param_3, int param_4);
    virtual int GetPreferredHeight(int param_1);
    virtual void Update();
    virtual void Draw(Graphics* param_1);

    
    void SyncDifficultyVisibility();
    bool CanSelectCharacter(int param_1);
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
