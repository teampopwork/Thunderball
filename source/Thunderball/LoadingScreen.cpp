#include "LoadingScreen.h"

#include "Res.h"
#include "SafetyCheck.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderballApp.h"

#include <SexyAppFramework/Font.h>
#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/Graphics.h>
#include <SexyAppFramework/ResourceManager.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/SoundInstance.h>
#include <SexyAppFramework/SoundManager.h>
#include <SexyAppFramework/WidgetManager.h>
#include <SexyAppFramework/Rect.h>
#include <cstddef>
#include <cstdlib>
#include <math.h>
#include <process.h>
#include <string>

using namespace Sexy;

ASSERT_SIZE(LoadingScreen, 0xF0);
ASSERT_OFFSET(LoadingScreen, mApp, 0x8C);
ASSERT_OFFSET(LoadingScreen, mPlayNowButton, 0x90);
ASSERT_OFFSET(LoadingScreen, mLoadProgress, 0x94);
ASSERT_OFFSET(LoadingScreen, mSunRotationAngle, 0x98);
ASSERT_OFFSET(LoadingScreen, m_unk0x9C, 0x9C);
ASSERT_OFFSET(LoadingScreen, mPlayNowPulseCount, 0xA0);
ASSERT_OFFSET(LoadingScreen, m_unk0xA4, 0xA4);
ASSERT_OFFSET(LoadingScreen, mAdventureStartDelay, 0xA8);
ASSERT_OFFSET(LoadingScreen, mBallAnimState, 0xAC);
ASSERT_OFFSET(LoadingScreen, mLogoBounceFrame, 0xB0);
ASSERT_OFFSET(LoadingScreen, mBallX, 0xB4);
ASSERT_OFFSET(LoadingScreen, mBallY, 0xB8);
ASSERT_OFFSET(LoadingScreen, mBallVelX, 0xBC);
ASSERT_OFFSET(LoadingScreen, mBallVelY, 0xC0);
ASSERT_OFFSET(LoadingScreen, mBallBounceInit, 0xC4);
ASSERT_OFFSET(LoadingScreen, mParticles, 0xC8);
//ASSERT_OFFSET(LoadingScreen, m_unk0xCC, 0xCC);
//ASSERT_OFFSET(LoadingScreen, m_unk0xD0, 0xD0);
//ASSERT_OFFSET(LoadingScreen, m_unk0xD4, 0xD4);
ASSERT_OFFSET(LoadingScreen, m_unk0xD8, 0xD8);
ASSERT_OFFSET(LoadingScreen, mLevelLoadMusicThread, 0xDC);
ASSERT_OFFSET(LoadingScreen, m_unk0xE0, 0xE0);
ASSERT_OFFSET(LoadingScreen, m_unk0xE4, 0xE4);
ASSERT_OFFSET(LoadingScreen, mDisplayPartnerLogo, 0xE8);
ASSERT_OFFSET(LoadingScreen, mLightBeamCount, 0xEC);

// SYNTHETIC: POPCAPGAME1 0x004af650
// Sexy::LoadingScreen::`scalar deleting destructor'

// TEMPLATE: POPCAPGAME1 0x0040cea0
// std::basic_string<char,std::char_traits<char>,std::allocator<char> >::assign(char const *, unsigned int)

// FUNCTION: POPCAPGAME1 0x004b1fe0
LoadingScreen::LoadingScreen(ThunderballApp* theApp)
{
	
	mApp = theApp;
	mLoadProgress = 0.0f;
	mSunRotationAngle = 0.0f;
	m_unk0xA4 = 0.0f;
	
	m_unk0x9C = 0;
	mPlayNowPulseCount = 0;
	mAdventureStartDelay = 0;
	mBallAnimState = 0;
	mLogoBounceFrame = 0;
	mBallBounceInit = false;
	m_unk0xE4 = 0;
	m_unk0xD8 = false;

	mPlayNowButton = new ThunderButton(IMAGE_LOAD_PLAYNOW, 0, (ButtonListener*)this);
	Image* aPlayNowImage = IMAGE_LOAD_PLAYNOW;
	int aButtonHeight = aPlayNowImage->mHeight;
	int aButtonWidth = aPlayNowImage->mWidth;

	mPlayNowButton->mButtonImage = aPlayNowImage;
	mPlayNowButton->mComponentImage = NULL;

	mPlayNowButton->mWidth = aButtonWidth;
	aButtonHeight /= 2;
	mPlayNowButton->mHeight = aButtonHeight;

	mPlayNowButton->mNormalRect = Rect(0, 0, aButtonWidth, aButtonHeight);
	mPlayNowButton->mOverRect = Rect(0, aButtonHeight, aButtonWidth, aButtonHeight);

	mPlayNowButton->Move(
		// STRING: POPCAPGAME1 0x0060c6c8
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp383,66", 0xe4),
		// STRING: POPCAPGAME1 0x0060c710
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp384,66", 0x1be)
	);

	mPlayNowButton->SetVisible(false);
	AddWidget(mPlayNowButton);

	// STRING: POPCAPGAME1 0x0060c6b4
    mDisplayPartnerLogo = mApp->GetBoolean("DisplayPartnerLogo", false);

	mLightBeamCount = 0;
	mLevelLoadMusicThread = 0;
}

// FUNCTION: POPCAPGAME1 0x004a6e70
LoadingScreen::~LoadingScreen()
{
	RemoveAllWidgets(true, false);

	std::string aPrefix = "Load";
	if (mApp != NULL) {
		mApp->mResourceManager->DeleteResources(aPrefix);
	}

	if (mLevelLoadMusicThread != 0) {
		PostThreadMessageA((DWORD) m_unk0xE0, WM_QUIT, 0, 0);
		WaitForSingleObject((HANDLE) mLevelLoadMusicThread, INFINITE);
	}
}

// FUNCTION: POPCAPGAME1 0x00494510
void LoadingScreen::DrawOverlay(Graphics* g)
{
    DrawScreenFrame(g);

    if ((0 < mPlayNowPulseCount) && (mPlayNowPulseCount < 0x32)) {
        double pulseValue;
        if (mPlayNowPulseCount < 0x19) {
            pulseValue = (double)mPlayNowPulseCount;
        } else {
            pulseValue = (double)(0x32 - mPlayNowPulseCount);
        }

        float pulseFactor = (float)(pulseValue / 25.0);

        // STRING: POPCAPGAME1 0x005fa440
        float finalAlpha = pulseFactor * ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp429,490", 100);

        Graphics localG(*g); 
        localG.SetColorizeImages(true);
        localG.SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
        localG.SetColor(Color((int)finalAlpha, (int)finalAlpha, (int)finalAlpha));

        localG.Translate(mPlayNowButton->mX, mPlayNowButton->mY);
        mPlayNowButton->Draw(&localG);
    }

    int updateCnt = mUpdateCnt;
    // STRING: POPCAPGAME1 0x005fa3f8
    int fadeLimit = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp430,499", 550);

    if ((updateCnt >= fadeLimit) || !mDisplayPartnerLogo) {
		updateCnt = mUpdateCnt;

		// STRING: POPCAPGAME1 0x005fa3b0
    	fadeLimit = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp431,499", 300);
    } 
    
	if (updateCnt < fadeLimit) {
		int alpha = 255; // 0x494672: Default EAX to 0xFF

		if (mDisplayPartnerLogo && updateCnt > 450) {
				alpha = ((550 - updateCnt) * 255) / 100;
		}
		
		else if (!mDisplayPartnerLogo && updateCnt > 200) {
				alpha = ((300 - updateCnt) * 255) / 100;
		} 
	
		g->SetColor(Sexy::Color(0, alpha));
		g->FillRect(0, 0, mWidth, mHeight);
	}
		
    
    

    updateCnt = mUpdateCnt;
    // STRING: POPCAPGAME1 0x005fa368
    fadeLimit = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp432,510", 200);
                int alpha = 0xff; 

    if (updateCnt < fadeLimit) {
        int alpha = 0xff;
        if (updateCnt < 50) {
            alpha = (updateCnt * 0xff) / 50; 
        } else if (updateCnt > 150) {
            alpha = ((200 - updateCnt) * 0xff) / 50;
        }

        g->SetColor(Color(0xffffff, alpha));
        g->SetColorizeImages(true);
        g->DrawImage(IMAGE_LOAD_POPCAP, (mWidth - IMAGE_LOAD_POPCAP->mWidth) / 2, (mHeight - IMAGE_LOAD_POPCAP->mHeight) / 2);
        g->SetColorizeImages(false);
    } else {
        // STRING: POPCAPGAME1 0x005fa320
        fadeLimit = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp433,523", 250);
        

        if (updateCnt > fadeLimit) {
			int currentUpdate = mUpdateCnt;

            // STRING: POPCAPGAME1 0x005fa2d8
            int partnerFadeMax = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp434,523", 450);
            if (currentUpdate < partnerFadeMax) {
                if (mDisplayPartnerLogo) {
                	int alpha = 0xff; 

                    if (currentUpdate < 300) {
                        alpha = ((currentUpdate - 250) * 0xff) / 50;
                    } else if (currentUpdate > 400) {
                        alpha = ((450 - currentUpdate) * 0xff) / 50;
                    }

					g->SetColor(Color(0xffffff, alpha));
					g->SetColorizeImages(true);
					g->DrawImage(IMAGE_PARTNER, (mWidth - IMAGE_PARTNER->mWidth) / 2, (mHeight - IMAGE_PARTNER->mHeight) / 2);
					g->SetColorizeImages(false);
                }

                
            }
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004948d0
void LoadingScreen::ButtonDepress(int theId)
{
    // dVar1 was the WidgetManager accessed via the this-pointer adjustment
    // field_0x105 is mKeyDown[VK_CONTROL] (0xF4 + 0x11)
    if (!mWidgetManager->mKeyDown[0x11]) // 0x11 = VK_CONTROL
    {
        // 0x13C, 0x138, and 0x135 are likely other mKeyDown keys or flags
        // For example: SHIFT (0x10) or ALT (0x12)
        if (mWidgetManager->mKeyDown[72]) 
        {
            mApp->ShowHelpScreen(false, false);
            return;
        }

        if (!mWidgetManager->mKeyDown[0x138 - 0xF4]) 
        {
            if (!mWidgetManager->mKeyDown[0x135 - 0xF4]) 
            {
                if (mApp->mCurProfile == 0) 
                {
					// STRING: POPCAPGAME1 0x005fa490
                    if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp467,745", 1) != 0)
                    {
                        mPlayNowButton->SetDisabled(true);
						mApp->DoCreateUserDialog();
                        return;
                    }
                }
                mApp->ShowMainMenu();
                return;
            }
            mApp->m_unk0x760 = 2; 
        }
        else 
        {
            mApp->m_unk0x760 = 3; 
        }

        //this->FinishLoadingSequencer();
    }
    mApp->ShowBoard(true, true);
}

// FUNCTION: POPCAPGAME1 0x004948b0
void LoadingScreen::ButtonPress(int theId, int theClickCount)
{
	mApp->PlaySample(SOUND_BUTTON1);
}


// FUNCTION: POPCAPGAME1 0x004a7250
void LoadingScreen::Draw(Graphics* g)
{
	Widget::Draw(g);
	Color bgColor(0);
	g->SetColor(bgColor);
	g->FillRect(0, 0, mWidth, mHeight);
	g->DrawImage(IMAGE_LOAD_BACK, 0, 0);

	// STRING: POPCAPGAME1 0x006078f8
	float sunTravel = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp435,549", 500);

	int sunY = (int)(1.0f - m_unk0xA4 * sunTravel - 214.0f);
	int sunX;
	Image* sunImage = NULL;

	if (g->mIs3D && mSunRotationAngle != 0.0f) {
		double angleRad = mSunRotationAngle * (SEXY_PI / 180.0);

		// STRING: POPCAPGAME1 0x006078a8
		int rotY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp437,553", 383);

		// STRING: POPCAPGAME1 0x00607860
		int rotX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp436,553", 394);

		g->DrawImageRotated(IMAGE_SUNGLOW, -0x24, sunY, angleRad, rotX, rotY, NULL);

		// STRING: POPCAPGAME1 0x00607818
		sunY += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp439,554", 307);

		// STRING: POPCAPGAME1 0x006077d0
		sunX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp438,554", 283);

		sunImage = IMAGE_LOAD_SUNHEAD;
	} else {
		sunImage = IMAGE_SUNGLOW;
		sunX = -0x24;
	}

	g->DrawImage(sunImage, sunX, sunY);

	// STRING: POPCAPGAME1 0x00607788
	int hillImageX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp440,572", 0xaa);

	// STRING: POPCAPGAME1 0x00607740
	int curveEndY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp441,573", 0x8c);

	// STRING: POPCAPGAME1 0x006076f8
	float curveStartY = (float)ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp442,574", 200);

	// STRING: POPCAPGAME1 0x006076b0
	int logoBounceThreshold = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp443,575", -0x3c);

	// STRING: POPCAPGAME1 0x00607668
	double logoYOffset = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp444,577", 0x32);

	// STRING: POPCAPGAME1 0x00607620
	int logoRadius = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp445,578", 0x46);

	// GLOBAL: POPCAPGAME1 0x0064a35d
	static bool needCalc;
	// GLOBAL: POPCAPGAME1 0x00650a7c
	static float a;
	// GLOBAL: POPCAPGAME1 0x00650a80
	static float b;
	// GLOBAL: POPCAPGAME1 0x00650a84
	static float y;

	if (!needCalc)
	{
		int sumY = (int)curveStartY + curveEndY;

		int sq70 = logoYOffset * logoYOffset;

		y = (float)sumY;

		float valA = (float)curveEndY - y;

		curveStartY = (float)sq70;
		logoYOffset = logoBounceThreshold + curveEndY;

		SolveLinearSystem(
			valA,
			0.0f,
			(float)logoYOffset,
			(float)curveStartY,
			(float)(logoRadius * 70),
			y,
			&a,
			&b
		);

		needCalc = true;
	}

	int checkVal = m_unk0xE4;
	float fCheck = (float)checkVal;

	curveStartY = (fCheck * b * fCheck) + (a * fCheck) + y;

	if (m_unk0xE4 < curveStartY)
	{
		g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, (int)curveStartY);
	}

	// STRING: POPCAPGAME1 0x006075d8
	int logoY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp446,604", 10);
	int bounceFrame = mLogoBounceFrame;
	int tempCheck = checkVal;

	if (bounceFrame > 0 && bounceFrame < tempCheck)
	{
		// STRING: POPCAPGAME1 0x00607590
		int bounceModVal = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp447,605", 8);

		bounceFrame = (int)(mLogoBounceFrame * -ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp448,605", 1.5) + bounceModVal);
	}
	else
	{
		bounceFrame = 0;
	}

	if (logoBounceThreshold > 0 && logoBounceThreshold < tempCheck)
	{
		curveEndY += checkVal;
	}

	g->DrawImage(IMAGE_LOAD_HILL, 0, 0x11d);

	g->SetColorizeImages(true);

	// STRING: POPCAPGAME1 0x00607500
	int val120 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp450,612", 120);

	float fShadow = (float)val120 * m_unk0xA4 * m_unk0xA4;
	int iShadow = (int)fShadow;

	// STRING: POPCAPGAME1 0x006074b8
	int valColor = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp449,612", 0x101010);
	g->SetColor(Color(valColor, iShadow));

	// STRING: POPCAPGAME1 0x00607470
	int shadowY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp452,615", 290);
	// STRING: POPCAPGAME1 0x00607428
	int shadowX = checkVal + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp451,614", 162);

	g->DrawImage(IMAGE_LOAD_SHADOW, shadowX, shadowY);

	g->SetColorizeImages(false);

	g->DrawImage(IMAGE_LOAD_OVERLAY,
		// STRING: POPCAPGAME1 0x00607398
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp453,620", 201),
		// STRING: POPCAPGAME1 0x006073e0
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp454,621", 420));

	if (m_unk0xE4 >= 0 && m_unk0xE4 < 70)
	{
		g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, curveStartY);
	}
	else
	{
		g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, curveEndY);
		if (mLogoBounceFrame != 0)
		{
			g->SetColorizeImages(true);
			g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);

			// STRING: POPCAPGAME1 0x00607350
			int alphaMax = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp456,633", 25);

			// STRING: POPCAPGAME1 0x00607308
			int lerpDur = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp455,633", 5);

			float lerpVal = Lerp(mLogoBounceFrame, lerpDur, 0, 0.0f, 0.0f, (float)alphaMax);

			int alpha = (int)(lerpVal * (float)ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp457,634", 128));

			g->SetColor(Color(0xffffff, alpha));
			g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, curveEndY);

			g->SetColorizeImages(false);
			g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
		}
	}

	for (int i = 0; i < mLightBeamCount; i++)
	{
		DrawLight(g, i);
	}

	// STRING: POPCAPGAME1 0x00607278
	int textY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp458,645", 200);
	// STRING: POPCAPGAME1 0x00607230
	int textX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp459,646", 460);

	std::string loadingText;

	if (mApp->IsScreenSaver())
	{
		// STRING: POPCAPGAME1 0x00607214
		loadingText = "Starting Screensaver";
	}
	else if (mApp->m_unk0x7b0 != 0)
	{
		// STRING: POPCAPGAME1 0x00607200
		loadingText = "Loading Replay...";
	}
	else if (mLoadProgress < 1.0f)
	{
		// STRING: POPCAPGAME1 0x006071f4
		loadingText = "Loading...";
	}

	if (loadingText.length() != 0)
	{
		g->SetFont(FONT_OVERLOAD16OUTLINE);

		// STRING: POPCAPGAME1 0x006071b0
		int fontColor = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp460,658", 0xffec91);
		Color textColor(fontColor);
		g->SetColor(textColor);

		int textX = (g->GetFont()->StringWidth(loadingText) - mWidth) / 2;

		g->DrawString(loadingText,
			// STRING: POPCAPGAME1 0x00607120
			textX + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp461,659", 0),
			// STRING: POPCAPGAME1 0x00607168
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp462,659", 0x22b));
	}

	DrawParticles(g);

	Transform t;
	if (mBallAnimState > 0)
	{
		g->DrawImageTransform(IMAGE_LOAD_BALL, t, mBallX, mBallY);
	}

	if (m_unk0xD8 != 0)
	{
		g->DrawImage(IMAGE_LOAD_DELUXE,
			// STRING: POPCAPGAME1 0x00607090
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp463,679", 300),
			// STRING: POPCAPGAME1 0x006070d8
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp464,679", 334)
		);

		g->SetColorizeImages(true);
		g->SetColor(Color(0));

		g->DrawImage(IMAGE_LOAD_TM,
			// STRING: POPCAPGAME1 0x00607000
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp465,682", 574),
			// STRING: POPCAPGAME1 0x00607048
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp466,682", 310));

		g->SetColorizeImages(false);
	}

	DeferOverlay(0);
}

// FUNCTION: POPCAPGAME1 0x00494890
void LoadingScreen::KeyChar(SexyChar theChar)
{
	if (theChar == 'b') {
		DoBallBounce();
	}
}

// FUNCTION: POPCAPGAME1 0x004b4270
void LoadingScreen::Update()
{
	Widget::Update();

	float loadTime = GetLoadTime(mApp->mCompletedLoadingThreadTasks);
	if (mPlayNowPulseCount != 0) {
		mPlayNowPulseCount++;
	}

	int updateCnt = mUpdateCnt;
	if (updateCnt == 1 && mBallBounceInit == false) {
		mApp->mYieldMainThread = false;
		mApp->ClearUpdateBacklog(false);
		if (SOUND_MORNING >= NULL) {
			SoundInstance* aInstance = mApp->mSoundManager->GetSoundInstance(SOUND_MORNING);
			if (aInstance != NULL) {
				aInstance->Play(false, true);
			}
		} 
	}
	else if (updateCnt == 80 && mApp->mLoadingThreadCompleted == false && mBallAnimState == 0) {
		mApp->mYieldMainThread = true;
	}
	

	UpdateBall();
	UpdateParticles();

	if (mLogoBounceFrame > 0) {
		mLogoBounceFrame++;
		// STRING: POPCAPGAME1 0x0060d250
		int val = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp394,191", 30);
		if (mLogoBounceFrame > val) {
			mLogoBounceFrame = 0;
		}
		MarkDirty();
	}

	updateCnt = mUpdateCnt;
	// STRING: POPCAPGAME1 0x0060d208
	int displayCutoff = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp395,198", 550);
	if (updateCnt <= displayCutoff) {
		if (!mDisplayPartnerLogo) {
			// STRING: POPCAPGAME1 0x0060d1c0
			displayCutoff = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp396,198", 250);
            
		}

		if (updateCnt <= displayCutoff) {
			if (updateCnt > 1 && mApp->m_unk0x779) {
				DoLevelLoadMusic();
			} else {
				if (loadTime > 0.0f) {
					m_unk0xE4++;
				}
			}
		}

		updateCnt = mUpdateCnt;
		float maxLoadThreshold = 1.0f;
		if (!mApp->mLoaded) {
			if (loadTime >= maxLoadThreshold) {
				maxLoadThreshold = 0.9999;
			}
		} else {
			loadTime = 1.0f;
		}

		
	}

	// STRING: POPCAPGAME1 0x0060d178
	int progressStart = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp398,218", 250);
	updateCnt = mUpdateCnt;
	// STRING: POPCAPGAME1 0x0060d130
	float displayProgress = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp397,218", 0.001f);
	displayProgress *= (float)(updateCnt - progressStart);

	if (mDisplayPartnerLogo) {
		// STRING: POPCAPGAME1 0x0060d0e8
		int progressPartnerStart = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp400,220", 550);
		updateCnt = mUpdateCnt;
		// STRING: POPCAPGAME1 0x0060d0a0
		displayProgress = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp399,220", 0.00143f);
		displayProgress = displayProgress * (float)(updateCnt - progressPartnerStart);
	}

	if (mLevelLoadMusicThread != 0 && (0.99 < displayProgress)) {
		displayProgress = 0.99f;
	}

	if (displayProgress > loadTime) {
		loadTime = displayProgress;
	}

	if (loadTime < 0.0f) {
		loadTime = 0.0f;
	}

	if (mLoadProgress < loadTime) {
		mLoadProgress += 0.01f;
		if (loadTime < mLoadProgress) {
			mLoadProgress = loadTime;
		}

		mLightBeamCount = (int)(mLoadProgress * 25.0f);
		MarkDirty();
		

		if (mLoadProgress < 1.0f) 
    	{
			mPlayNowPulseCount = 1;
			if (mApp->IsScreenSaver() || mApp->m_unk0x7b0 != 0) 
			{
				if (mApp->m_unk0x7b0 != 0) 
				{
					mApp->ShowReplay(false);
					return;
				}
			}
			mApp->ShowBoard(true, true);
			return;
		}

		if (m_unk0xA4 < mLoadProgress) {
			m_unk0xA4 = mLoadProgress;
			MarkDirty();
		}

		if (m_unk0xA4 >= 1.0f) 
		{
			if (updateCnt > 550) 
			{
				m_unk0xA4 = 1.0f;

				if (mBallAnimState == 0) 
				{
					DoBallBounce();
				}
			}
		}

		if (m_unk0xA4 < 1.0f) 
		{	
			// STRING: POPCAPGAME1 0x0060d058
			float aRotationSpeed = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp401,281", 0.2f);
			
			mPlayNowPulseCount++;
			mSunRotationAngle += aRotationSpeed;

			if (mApp->Is3DAccelerated()) 
			{
				MarkDirty();
			}
    	}

		if (mAdventureStartDelay > 0) {
			mAdventureStartDelay--;
			if (mAdventureStartDelay == 0) {
				mApp->StartAdventureGame();
			}
		}

		// STRING: POPCAPGAME1 0x0060d010
		int aPulseThreshold = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp402,295", 550);

		if (mUpdateCnt > aPulseThreshold)
		{
			int remainingCapacity = mParticles.capacity() - mParticles.size();
			
			if (remainingCapacity != 0)
			{
				MarkDirty();
			}
			
		}
		else
		{
			MarkDirty();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00494370
void LoadingScreen::DoBallBounce()
{
	mApp->ClearUpdateBacklog(false);
	if (!mBallBounceInit) {
		mApp->mYieldMainThread = false;
	}

	mBallAnimState = 1;
	// STRING: POPCAPGAME1 0x005fa1b8
	mBallX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp385,102", 0xcd);
	// STRING: POPCAPGAME1 0x005fa170
	mBallY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp386,103", -0x14);
	// STRING: POPCAPGAME1 0x005fa128
	mBallVelX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp387,104", 4.5f);
	mBallVelY = 0.0f;
	mLogoBounceFrame = 0;
}

// FUNCTION: POPCAPGAME1 0x004a71f0
void LoadingScreen::DoLevelLoadMusic()
{
	LoadingScreen* self = this;
	HANDLE aThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LevelLoadMusicThreadProc, self, 0, (LPDWORD)&self);
	mLevelLoadMusicThread = aThread;
	m_unk0xE0              = (int)self;
	bool isLoading = mApp->m_unk0x779;
	while (isLoading) {
		Sleep(10);
		isLoading = mApp->m_unk0x779;
	}
}

// FUNCTION: POPCAPGAME1 0x00494420
void LoadingScreen::DrawLight(Graphics* g, int param_2)
{
	int aCel = 0;

	switch (param_2) {
	case 0:
		aCel = 4;
		break;
	case 1:
		aCel = 3;
		break;
	case 23:
		aCel = 1;
		break;
	case 24:
		aCel = 0;
		break;
	default:
		aCel = 2;
		break;
	}

	Image* lights = IMAGE_LOAD_LIGHTS;
	Rect local_1c = lights->GetCelRect(aCel);

	// STRING: POPCAPGAME1 0x005fa290
	float fVar1 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp427,472", 13.9f);
	double local_c = (double) (fVar1 * (float) param_2);

	// STRING: POPCAPGAME1 0x005fa248
	int xOffset = (int)(local_c + (double)ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp426,472", 0xe0));

	// STRING: POPCAPGAME1 0x005fa200
	int theY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp428,473", 0x1bf);
	g->DrawImage(lights, xOffset, theY, local_1c);
}

// FUNCTION: POPCAPGAME1 0x004998c0
void LoadingScreen::DrawParticles(Graphics* g)
{
    g->PushState();
    g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE); // Assembly: PUSH 0x1

    for (size_t i = 0; i < mParticles.size(); ++i)
    {
        int alpha = mParticles[i].mAlpha;

        // STRING: POPCAPGAME1 0x005fe828
        int b = rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp421,377", 0x80);
        // STRING: POPCAPGAME1 0x005fe7e0
        int g_val = rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp420,377", 0x80);
        // STRING: POPCAPGAME1 0x005fe798
        int r = rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp419,377", 0x80);

		Color particleColor(r, g_val, b, alpha);
        g->SetColor(particleColor);
		
		float theX = (mParticles[i].mX);
		float theY = (mParticles[i].mY);


        int rectH = (rand() % 2) + 1;
		int rectW = (rand() % 2) + 1;

        g->FillRect((int)theX, (int)theY, rectW, rectH);

        // 4. Sparkle Logic
        if ((rand() % 0xFF) < mParticles[i].mAlpha)
        {
            g->SetColor(Color(0x20201));

			float sparkXf = mParticles[i].mX;
			float sparkYf = mParticles[i].mY;

            // STRING: POPCAPGAME1 0x00005fe750
            int sparkH = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp425,383", 8);
            // STRING: POPCAPGAME1 0x00005fe708
            int sparkW = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp424,383", 8);
            // STRING: POPCAPGAME1 0x00005fe6c0
            int sparkY = sparkYf - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp423,383", 4);
            // STRING: POPCAPGAME1 0x00005fe678
            int sparkX = sparkXf - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp422,383", 4);

            g->FillRect( sparkX, sparkY, sparkW, sparkH);
        }
    }

    g->PopState();
}

// FUNCTION: POPCAPGAME1 0x004b40b0
void LoadingScreen::UpdateBall()
{
	if ((mBallAnimState > 0) && (mBallAnimState <= 2)) {
		// STRING: POPCAPGAME1 0x0060cfc8
		mBallVelY += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp388,116", 0.75f);
		mBallX += mBallVelX;
		mBallY += mBallVelY;

		// STRING: POPCAPGAME1 0x0060cf80
		int rightX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp389,120", 0x348);

		double ballY = mBallY;

		// STRING: POPCAPGAME1 0x0060cf38
		int groundY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp390,121", 0xaa);

		if (ballY > (double)groundY && mBallAnimState == 1) {
			mLogoBounceFrame = 1;
			mBallAnimState = 2;

			// STRING: POPCAPGAME1 0x0060cef0
			mBallVelY *= -ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp391,125", 0.9f);

			// STRING: POPCAPGAME1 0x0060cea8
			mBallVelX *= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp392,126", 1.0f);

			if ((SOUND_PEGHIT_LOW >= 0)) {
				mApp->PlaySample(SOUND_PEGHIT_LOW);
			}
		}
		else if (mBallX > (float) rightX) {
			double ballX = mBallX;
			// STRING: POPCAPGAME1 0x0060ce60
   			int extra = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp393,143", 0x14);

			if (ballX > (double)(rightX + extra)) {
				mApp->mYieldMainThread = !mApp->mLoadingThreadCompleted;
				
				mBallAnimState = 3;
			}
		}
	

		if (mBallX < (float)rightX) {
			SpawnParticles();
		}

		MarkDirty();
	}
}

// STUB: POPCAPGAME1 0x0049f2d0
void LoadingScreen::UpdateParticles()
{
	
}

// TEMPLATE: POPCAPGAME1 0x004b2420
// std::vector<Sexy::Particle,std::allocator<Sexy::Particle> >::push_back

// FUNCTION: POPCAPGAME1 0x004b3b90
void Sexy::LoadingScreen::SpawnParticles()
{
    // STRING: POPCAPGAME1 0x0060ce18
    int i = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp403,306", -7);
    if (i <= Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp404,306", 7))
    {
        do {
            Particle aParticle;

            aParticle.mAngle  = atan2(mBallVelY, mBallVelX);
			

			// STRING: POPCAPGAME1 0x0060cd88
			double aRandX = (double)(rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp406,312", 30));
            double aCosPerp = cos((double)aParticle.mAngle + (SEXY_PI / 2.0f));

			// STRING: POPCAPGAME1 0x0060cd40
            double aDistScaleX = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp405,312", 4.3f);

			double xScaled = aDistScaleX * aCosPerp * (double)i;

			// STRING: POPCAPGAME1 0x0060ccf8
			aParticle.mX = (xScaled + (double)mBallX + aRandX) - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp407,312", 15);

			// STRING: POPCAPGAME1 0x0060ccb0
            double aRandY = (double)(rand() % ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp409,313", 30));
            double aSinPerp = sin((double)aParticle.mAngle + (double)(SEXY_PI / 2.0f));


			// STRING: POPCAPGAME1 0x0060cc68
            double aDistScaleY = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp408,313", 4.3f);

			double yScaled = aDistScaleY * aSinPerp * (double)i;

			// STRING: POPCAPGAME1 0x0060cc20
            aParticle.mY = (yScaled + (double)mBallY+ aRandY) - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp410,313", 15);

			// STRING: POPCAPGAME1 0x0060cbd8
            double aVelScaleX = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp411,315", -0.071f);
            aParticle.mVelX = aVelScaleX * aCosPerp * (double)i;

			// STRING: POPCAPGAME1 0x0060cb90
            double aVelScaleY = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp412,316", -0.071f);
            aParticle.mVelY = aVelScaleY * aSinPerp * (double)i;

            // 5. Attributes
			// STRING: POPCAPGAME1 0x0060cb48
            aParticle.mAlpha = Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp413,318", 255);
            aParticle.mFlip = (0 < i);

            mParticles.push_back(aParticle);

            i++;
		// STRING: POPCAPGAME1 0x0060cdd0
        } while (i <= Sexy::ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp404,306", 7));
    }
}

// FUNCTION: POPCAPGAME1 0x004a6f90
void LoadingScreen::LevelLoadMusicThreadProc(LPVOID lpParameter)
{
	Sexy::LoadingScreen* loadingScreen = (Sexy::LoadingScreen*) lpParameter;
	Sexy::ThunderballApp* app = loadingScreen->mApp;

	app->LoadLevelMusic();

	WIN32_FIND_DATAA findData;
	// STRING: POPCAPGAME1 0x00606ff4
	HANDLE hFind = FindFirstFileA("music\\*.*", &findData);

	if (hFind != INVALID_HANDLE_VALUE) {
		
		do {
			MSG msg;
			if (PeekMessageA(&msg, NULL, WM_NULL, WM_NULL, PM_REMOVE)) {
				break;
			}

			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				// STRING: POPCAPGAME1 0x0000606fe4
				if (_stricmp(findData.cFileName, "odetojoy.ogg") != 0 &&
				// STRING: POPCAPGAME1 0x0000606fd8
					_stricmp(findData.cFileName, "opening.ogg") != 0) {
					char* ext = strrchr(findData.cFileName, '.');
					if (ext != NULL) {
						ext++;

						// STRING: POPCAPGAME1 0x00606fd4
						if (_stricmp(ext, "ogg") == 0 
						// STRING: POPCAPGAME1 0x00606fd0
						|| _stricmp(ext, "mp3") == 0 
						// STRING: POPCAPGAME1 0x00606fcc
						|| _stricmp(ext, "it") == 0 
						// STRING: POPCAPGAME1 0x00606fc8
						|| _stricmp(ext, "xm") == 0 
						// STRING: POPCAPGAME1 0x00606fc4
						|| _stricmp(ext, "mo3") == 0) {
							// STRING: POPCAPGAME1 0x00606fbc
							std::string path = "music\\";
							path += findData.cFileName;

							app->LoadMusic(app->m_unk0x7b8, path);

							app->m_unk0x7b8++;
						}
					}
				}
			}
		} while (FindNextFileA(hFind, &findData) != 0);

		FindClose(hFind);
	}

	// STRING: POPCAPGAME1 0x0000606f9c
	OutputDebugStringA("Done with level music loading\r\n");

	loadingScreen->mLevelLoadMusicThread = NULL;
}
