#include "OptionsDialog.h"

using namespace Sexy;

OptionsDialog::OptionsDialog(bool param_1)
	: ThunderDialog(0x13, true, param_1 ? "MENU" : "OPTIONS", "", param_1 ? "Back To Game" : "Done", 3)
{
}

OptionsDialog::~OptionsDialog()
{
}

void OptionsDialog::AddedToManager(WidgetManager* theManager)
{
}

void OptionsDialog::ButtonDepress(int theId)
{
}

void OptionsDialog::ButtonPress(int theId)
{
}

void OptionsDialog::CheckboxChecked(int theId, bool checked)
{
}

void OptionsDialog::Draw(Graphics* g)
{
}

int OptionsDialog::GetPreferredHeight(int theWidth)
{
	return 0;
}

void OptionsDialog::OrderInManagerChanged()
{
}

void OptionsDialog::RemovedFromManager(WidgetManager* theManager)
{
}

void OptionsDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
}

void OptionsDialog::SliderVal(int theId, double theVal)
{
}
