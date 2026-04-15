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
	ThunderSlider* mMusicVolumeSlider; // +0x180
	ThunderSlider* mSfxVolumeSlider;   // +0x184
	ThunderSlider* mFeverVolumeSlider; // +0x188

	ThunderCheckbox* mFullscreenCheckbox; // +0x18C
	ThunderCheckbox* mCustomCursorsCheckbox; // +0x190
	ThunderCheckbox* m3DAccelerationCheckbox; // +0x194
	ThunderCheckbox* mColorblindModeCheckbox; // +0x198

	ThunderButton* mHelpButton; // +0x19C
	ThunderButton* mUnk0x1A0;
	ThunderButton* mUnk0x1A4;
	ThunderButton* mMainMenuButton; // +0x1A8
	ThunderButton* mNewLevelButton; // +0x1AC
	ThunderButton* mNewChallengeButton; // +0x1B0

	bool mFromGame;
	int mUnk0x1B8;

	OptionsDialog(bool theFromGame);
	virtual ~OptionsDialog();

	virtual void AddedToManager(WidgetManager* theWidgetManager);
	virtual void ButtonDepress(int theId);
	virtual void CheckboxChecked(int theId, bool checked);
	virtual void Draw(Graphics* g);
	virtual int GetPreferredHeight(int theWidth);
	virtual void OrderInManagerChanged();
	virtual void RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void SliderVal(int theId, double theVal);
};
} // namespace Sexy

#endif
