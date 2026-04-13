#ifndef __THUNDERCOMMON_H__
#define __THUNDERCOMMON_H__

#include <SexyAppFramework/Rect.h>

#define SEXY_PI 3.1415901f

namespace Sexy
{
class ButtonWidget;
class EditWidget;
class ButtonListener;
class EditListener;
class CheckboxListener;
class Image;
class Graphics;
class Dialog;
class ThunderButton;
class SimpleButton;
class DialogButton;
class ThunderCheckbox;
enum StyleShot;

void SetButtonFontColor(int color);
void SwapRect(TRect<int>& rect1, TRect<int>& rect2);
ButtonWidget* MakeWinButton(Image* theImage, int theType);
void DrawScreenFrame(Graphics* g);
void PositionDialog(Dialog* param_1, int param_2, bool param_3, int param_4);
long double GetLoadTime(int param_1);
bool SolveLinearSystem(float a, float b, float e, float c, float d, float f, float* outX, float* outY);
float InterpValF(int currentTime, int phase1Duration, int phase2Duration, 
                      float startVal, float midVal, float endVal);
int GetStyleShotScore(Sexy::StyleShot, bool, int);
ThunderButton* MakeEmbeddedButton(int theId, ButtonListener *theListener, Image *theImage, bool param_4);
ThunderButton* MakeButton(int theId, ButtonListener* theListener, std::string const& theString, Image* theImage);
ThunderButton* MakePurpleButton(int theId, ButtonListener* theListener, std::string const& theString);
SimpleButton* MakeSimpleButton(int theId, ButtonListener* theListener, Image* theImage, int param_4, int param_5);
EditWidget* CreateEditWidget(int theId, EditListener* theListener);
void SetupButton(DialogButton* theButton, bool param_2);
void SetupEditWidget(EditWidget* theEditWidget);
void DoNameWidthEnforce(EditWidget* theEditWidget);
void DrawEditBox(Graphics* g, EditWidget* theEditWidget);
ThunderButton* MakeButtonCopy(DialogButton* theButton);
int Clamp(int val, int minVal, int maxVal);
ThunderCheckbox* MakeCheckbox(int theId, CheckboxListener* theListener, int param_3);
ThunderCheckbox* MakeCheckbox2(int theId, CheckboxListener* theListener, std::string const& theString, int param_4);
ThunderButton* MakeBottomButton(int theId, ButtonListener* theListener, std::string const& theString);
int GetColorForCharacter(int param_1);
// 04896b0 DoDrawStat
} // namespace Sexy

#endif // __THUNDERCOMMON_H__
