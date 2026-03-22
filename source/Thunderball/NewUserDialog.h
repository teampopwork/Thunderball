#ifndef __NEW_USER_DIALOG_H__
#define __NEW_USER_DIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/Common.h>
#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/EditListener.h>

#include <string>

namespace Sexy
{   
class Graphics;
class EditWidget;
class ThunderButton;
class ThunderballApp;

class NewUserDialog : public ThunderDialog, public EditListener {
public:
    ThunderballApp* mApp; // +0x17C
    EditWidget* mUnk0x180;
    ThunderButton* mUnk0x184;
    bool mUnk0x188;
    std::string mUnk0x18C;
    int mUnk0x1A8;

    NewUserDialog(ThunderballApp* theApp, bool param_2, bool param_3, bool param_4);
    virtual ~NewUserDialog();

    virtual void Draw(Graphics* g);
    virtual void DrawOverlay(Graphics* g);
    virtual void Update();
    virtual int GetPreferredHeight(int theWidth);
    virtual void AddedToManager(WidgetManager* theWidgetManager);
    virtual void RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void EditWidgetText(int theId, const SexyString& theString);
    virtual bool AllowChar(int theId, SexyChar theChar);

};

}






















#endif // __NEW_USER_DIALOG_H__