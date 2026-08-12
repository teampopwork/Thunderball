#include "UpsellScreen.h"

#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/MusicInterface.h>

using namespace Sexy;

UpsellScreen::UpsellScreen(ThunderballApp* theApp, bool param_2)
{
}

UpsellScreen::~UpsellScreen()
{
}

void UpsellScreen::ButtonDepress(int theId)
{
}

void UpsellScreen::Draw(Graphics* g)
{
}

void UpsellScreen::DrawOverlay(Graphics* g)
{
}

void UpsellScreen::DrawBjorn(Graphics* g)
{
}

void UpsellScreen::DrawBuyNow(Graphics* g)
{
}

void UpsellScreen::DrawLevels(Graphics* g)
{
}

void UpsellScreen::DrawMasters(Graphics* g)
{
}

void UpsellScreen::DrawSpeechBubble(Graphics* g, int param_2, int param_3, bool param_4)
{
}

void UpsellScreen::DrawZoomText(Graphics* g, int param_2, int param_3, int param_4)
{
}

// FUNCTION: POPCAPGAME1 0x0048f260
void UpsellScreen::Pause(bool param_1)
{
	mPaused = param_1;
	if (param_1) {
		GetThunderballApp()->mMusicInterface->PauseAllMusic();
	}
	else {
		GetThunderballApp()->mMusicInterface->ResumeAllMusic();
	}
}

void UpsellScreen::SetCurBubble(int param_1)
{
}

void UpsellScreen::SetState(int param_1)
{
}
