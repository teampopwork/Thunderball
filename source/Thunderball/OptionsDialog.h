#ifndef __OPTIONSDIALOG_H__
#define __OPTIONSDIALOG_H__

#include "ThunderCommon.h"
#include "ThunderDialog.h"

#include <SexyAppFramework/ButtonListener.h>
#include <SexyAppFramework/CheckboxListener.h>
#include <SexyAppFramework/SliderListener.h>

namespace Sexy
{
class ThunderSlider;
class ThunderCheckbox;
class ThunderButton;
class Graphics;
class WidgetManager;

class OptionsDialog : public ThunderDialog, public SliderListener, public CheckboxListener {
public:
	ThunderSlider* mMusicVolumeSlider;
	ThunderSlider* mSfxVolumeSlider;
	ThunderSlider* mFeverVolumeSlider;

	ThunderCheckbox* mFullscreenCheckbox;
	ThunderCheckbox* mCustomCursorsCheckbox;
	ThunderCheckbox* m3DAccelerationCheckbox;
	ThunderCheckbox* mColorblindModeCheckbox;

	ThunderButton* mHelpButton;
	ThunderButton* mUnk0x1A0;
	ThunderButton* mUnk0x1A4;
	ThunderButton* mMainMenuButton;
	ThunderButton* mNewLevelButton;
	ThunderButton* mNewChallengeButton;

	bool mFromGame;
	int mUnk0x1B8;

	OptionsDialog(bool theFromGame);
	virtual ~OptionsDialog();

	virtual void AddedToManager(WidgetManager* theManager);
	virtual void ButtonDepress(int theId);
	virtual void ButtonPress(int theId);
	virtual void CheckboxChecked(int theId, bool checked);
	virtual void Draw(Graphics* g);
	virtual int GetPreferredHeight(int theWidth);
	virtual void OrderInManagerChanged();
	virtual void RemovedFromManager(WidgetManager* theManager);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void SliderVal(int theId, double theVal);
};
} // namespace Sexy

#endif
