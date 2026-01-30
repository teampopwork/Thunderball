#ifndef __THUNDERCOMMON_H__
#define __THUNDERCOMMON_H__

#include <SexyAppFramework/Rect.h>

#define SEXY_PI 3.1415901f

namespace Sexy
{
class ButtonWidget;
class Image;
class Graphics;
class Dialog;
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
// 04896b0 DoDrawStat
} // namespace Sexy

#endif // __THUNDERCOMMON_H__
