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
#include <SexyAppFramework/Debug.h>
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
ASSERT_OFFSET(LoadingScreen, mUnk0x9C, 0x9C);
ASSERT_OFFSET(LoadingScreen, mPlayNowPulseCount, 0xA0);
ASSERT_OFFSET(LoadingScreen, mUnk0xA4, 0xA4);
ASSERT_OFFSET(LoadingScreen, mAdventureStartDelay, 0xA8);
ASSERT_OFFSET(LoadingScreen, mBallAnimState, 0xAC);
ASSERT_OFFSET(LoadingScreen, mLogoBounceFrame, 0xB0);
ASSERT_OFFSET(LoadingScreen, mBallX, 0xB4);
ASSERT_OFFSET(LoadingScreen, mBallY, 0xB8);
ASSERT_OFFSET(LoadingScreen, mBallVelX, 0xBC);
ASSERT_OFFSET(LoadingScreen, mBallVelY, 0xC0);
ASSERT_OFFSET(LoadingScreen, mBallBounceInit, 0xC4);
ASSERT_OFFSET(LoadingScreen, mParticles, 0xC8);
ASSERT_OFFSET(LoadingScreen, mUnk0xD8, 0xD8);
ASSERT_OFFSET(LoadingScreen, mLevelLoadMusicThread, 0xDC);
ASSERT_OFFSET(LoadingScreen, mUnk0xE0, 0xE0);
ASSERT_OFFSET(LoadingScreen, mUnk0xE4, 0xE4);
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
	mUnk0xA4 = 0.0f;
	
	mUnk0x9C = 0;
	mPlayNowPulseCount = 0;
	mAdventureStartDelay = 0;
	mBallAnimState = 0;
	mLogoBounceFrame = 0;
	mBallBounceInit = false;
	mUnk0xE4 = 0;
	mUnk0xD8 = false;

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
		PostThreadMessageA((DWORD) mUnk0xE0, WM_QUIT, 0, 0);
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
    if (!mWidgetManager->mKeyDown[KEYCODE_CONTROL])
    {

		if (mWidgetManager->mKeyDown[0x48]) 
		{
			mApp->ShowHelpScreen(false, false);
			return;
		}

		if (mWidgetManager->mKeyDown[0x44]) 
		{
			mApp->mUnk0x760 = 3; 
		}

		if (mApp->mAdd8BitMaxTable[0x18] == '\0') 
		{
			mApp->mUnk0x760 = 2;
			QuickPlay();
			mApp->ShowBoard(true, true);
			return;
			
		}

		if (mApp->mCurProfile == NULL) 
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
	mApp->ShowBoard(true, true);
}

// STUB: POPCAPGAME1 0x00494850
void LoadingScreen::QuickPlay() {
	printf("QuickPlay invoked\n");
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
    Color aBackgroundColor = Color(0);
    g->SetColor(aBackgroundColor);
    g->FillRect(0, 0, mWidth, mHeight);
    g->DrawImage(IMAGE_LOAD_BACK, 0, 0);

    // STRING: POPCAPGAME1 0x006078f8
    int sunY = (1.0f - mUnk0xA4) * (float)ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp435,549", 500) - 214.0;

    if (g->mIs3D && mSunRotationAngle != 0.0f) {
        double angleRad = mSunRotationAngle * SEXY_PI / 180.0;

        g->DrawImageRotated(IMAGE_SUNGLOW, -0x24, sunY, angleRad, 
			// STRING: POPCAPGAME1 0x00607860
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp436,553", 394), 
			// STRING: POPCAPGAME1 0x006078a8
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp437,553", 383), NULL);

        g->DrawImage(IMAGE_LOAD_SUNHEAD, 
        	// STRING: POPCAPGAME1 0x006077d0
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp438,554", 283),
        	// STRING: POPCAPGAME1 0x00607818
			ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp439,554", 307) + sunY);

    } else {
        g->DrawImage(IMAGE_SUNGLOW, -0x24, sunY);
    }

    

    // STRING: POPCAPGAME1 0x00607788
    int hillImageX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp440,572", 0xaa);

    // STRING: POPCAPGAME1 0x00607740
    int curveEndY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp441,573", 0x8c);

    // STRING: POPCAPGAME1 0x006076f8
    int curveStartY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp442,574", 200);

    // STRING: POPCAPGAME1 0x006076b0
    int logoBounceThreshold = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp443,575", -0x3c);

    // STRING: POPCAPGAME1 0x00607668
    int logoYOffset = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp444,577", 0x32);

    // STRING: POPCAPGAME1 0x00607620
    int logoRadius = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp445,578", 0x46);

    // GLOBAL: POPCAPGAME1 0x0064a35d
    static bool needCalc = true;
    // GLOBAL: POPCAPGAME1 0x00650a7c
    static float a = 0.0f;
    // GLOBAL: POPCAPGAME1 0x00650a80
    static float b = 0.0f;
    // GLOBAL: POPCAPGAME1 0x00650a84
    static float y = 0.0f;

    if (needCalc)
    {
        y = curveStartY + curveEndY;
        needCalc = false;
        curveStartY = logoBounceThreshold + curveEndY - y;
        

        SolveLinearSystem(
            logoYOffset * logoYOffset,
            logoYOffset,
            curveStartY,
            logoRadius * logoRadius,
            logoRadius,
            curveEndY - y,
            &b,
            &a
        );
    }

    OutputDebug("LoadingScreen::Draw: a=%x, b=%x, y=%x\n", *(int*)&a, *(int*)&b, *(int*)&y);
    int logoY = (b * mUnk0xE4 * mUnk0xE4) + (a * mUnk0xE4) + y;

    if (mUnk0xE4 < logoYOffset) {
        g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, logoY);
    }

    // STRING: POPCAPGAME1 0x006075d8
    if (mLogoBounceFrame > 0 && mLogoBounceFrame < ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp446,604", 10))
    {
        // STRING: POPCAPGAME1 0x00607548
        mLogoBounceFrame = (mLogoBounceFrame * -ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp448,605", 1.5f) +
            // STRING: POPCAPGAME1 0x00607590
            ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp447,605", 8));
    }
    else
    {
        mLogoBounceFrame = 0;
    }


    if (logoBounceThreshold > 0 && logoBounceThreshold < mUnk0xE4)
    {
        logoY += mUnk0xE4;
    }

    g->DrawImage(IMAGE_LOAD_HILL, 0, 0x11d);

    g->SetColorizeImages(true);

    g->SetColor(Color(
        // STRING: POPCAPGAME1 0x006074b8
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp449,612", 0x101010), 
        // STRING: POPCAPGAME1 0x00607500
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp450,612", 120) * mUnk0xA4 * mUnk0xA4
    ));

    g->DrawImage(
        IMAGE_LOAD_SHADOW, 
        // STRING: POPCAPGAME1 0x00607428
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp451,614", 162), 
        // STRING: POPCAPGAME1 0x00607470
        logoYOffset + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp452,615", 290)
    );

    g->SetColorizeImages(false);

    g->DrawImage(IMAGE_LOAD_OVERLAY,
        // STRING: POPCAPGAME1 0x00607398
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp453,620", 201),
        // STRING: POPCAPGAME1 0x006073e0
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp454,621", 420));

    if (mUnk0xE4 >= logoYOffset && mUnk0xE4 < logoRadius)
    {
        g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, logoY);
    }
    else
    {
        if (mUnk0xE4 >= logoRadius)
        {
            g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, curveEndY);
            if (mLogoBounceFrame != 0)
            {
                g->SetColorizeImages(true);
                g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);

                // STRING: POPCAPGAME1 0x006072c0
                int alpha = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp457,634", 128) * InterpValF(
                    mLogoBounceFrame, 
                    // STRING: POPCAPGAME1 0x00607308
                    ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp455,633", 5), 
                    // STRING: POPCAPGAME1 0x00607350
                    ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp456,633", 25),
                    0.0f, 
                    1.0f, 
                    0.0f
                );

                g->SetColor(Color(0xffffff, alpha));
                g->DrawImage(IMAGE_LOAD_LOGO, hillImageX, curveEndY);
                g->SetColorizeImages(false);
                g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
            }
        }
    }

    for (int i = 0; i < mLightBeamCount; i++)
    {
        DrawLight(g, i);
    }

    // STRING: POPCAPGAME1 0x00607278
    int loadingTextBaseY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp458,645", 200);
    // STRING: POPCAPGAME1 0x00607230
    int loadingTextBaseX = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp459,646", 460);

    std::string loadingText;

    if (mApp->IsScreenSaver())
    {
        // STRING: POPCAPGAME1 0x00607214
        loadingText = "Starting Screensaver";
    }
    else if (mApp->mUnk0x7b0 != 0)
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

        int loadingTextXCentered = (mWidth - g->GetFont()->StringWidth(loadingText)) / 2;

        g->DrawString(loadingText,
            // STRING: POPCAPGAME1 0x00607120
            loadingTextXCentered + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp461,659", 0),
            // STRING: POPCAPGAME1 0x00607168
            ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp462,659", 0x22b));
    }

    DrawParticles(g);

    Transform t;
    if (mBallAnimState > 0)
    {
        g->DrawImageTransform(IMAGE_LOAD_BALL, t, mBallX, mBallY);
    }

    if (mUnk0xD8 != 0)
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

    if (updateCnt == 1 && !mBallBounceInit) {
        mApp->mYieldMainThread = false;
        mApp->ClearUpdateBacklog(false);
        
        if ((int)SOUND_MORNING >= 0) {
            SoundInstance* aInstance = mApp->mSoundManager->GetSoundInstance(SOUND_MORNING);
            if (aInstance != NULL) {
                aInstance->Play(false, true);
            }
        } 
    } else if (updateCnt == 80 && !mApp->mLoadingThreadCompleted && mBallAnimState == 0) {
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
    
    if ((updateCnt > displayCutoff) || !mDisplayPartnerLogo) {
            updateCnt = mUpdateCnt;
            // STRING: POPCAPGAME1 0x0060d1c0
            displayCutoff = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp396,198", 250);
    }
        
    if (updateCnt <= displayCutoff) {
        if (updateCnt > 1) {
            if (mApp->mUnk0x779) {
                DoLevelLoadMusic();
            } 
        } 
    } else if (loadTime > 0.0f) {
        mUnk0xE4++;
    }

    if (!mApp->mLoaded && loadTime >= 1.0f) {
        loadTime = 0.9999f;
    }

    updateCnt = mUpdateCnt;
    // STRING: POPCAPGAME1 0x0060d178
    float displayProgress = (updateCnt - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp398,218", 250)) * 
    // STRING: POPCAPGAME1 0x0060d130
    ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp397,218", 0.001f);

    if (mDisplayPartnerLogo) {
        
        updateCnt = mUpdateCnt;

        // STRING: POPCAPGAME1 0x0060d0e8
        displayProgress = (float)(updateCnt - ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp400,220", 550)) * 
        // STRING: POPCAPGAME1 0x0060d0a0
        ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp399,220", 0.00143f);
    }

    if (mLevelLoadMusicThread != NULL && displayProgress > 0.99f) {
        displayProgress = 0.99f;
    }

    if (loadTime > displayProgress) {
        loadTime = displayProgress;
    }

    if (loadTime < 0.0f) {
        loadTime = 0.0f;
    }

    if (mLoadProgress < loadTime) {
        mLoadProgress += 0.01f;
        if (mLoadProgress > loadTime) {
            mLoadProgress = loadTime;
        }

        mLightBeamCount = (int)(mLoadProgress * 25.0f);
        MarkDirty();        

        if (mLoadProgress == 1.0f) {
            mPlayNowPulseCount = 1;
            
            if (!mApp->IsScreenSaver() && !mApp->mUnk0x7b0) {
                mPlayNowButton->SetVisible(true);
                mUnk0xD8 = true;
                if (mApp->mUnk0x7b0) {
                    mApp->ShowReplay(false);
                    return;
                } 
            } else {
                mApp->mUnk0x760 = 6;
                mApp->ShowBoard(true, true);
                return;
            }
        }
    }

    if (mUnk0xA4 < mLoadProgress) {    
        mUnk0xA4 = mLoadProgress;
        MarkDirty();
    }

    if (mUnk0xA4 >= 1.0f) {
        if (mUpdateCnt > 550) {
            if (mBallAnimState == 0) {
                mUnk0xA4 = 1.0f;
                DoBallBounce();
            } 
        }   
    }

    if (mUnk0xA4 >= 1.0f) {   
        // STRING: POPCAPGAME1 0x0060d058
        mSunRotationAngle += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp401,281", 0.2f);

        mUnk0x9C++;
        if (mApp->Is3DAccelerated()) {
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

    if (mUpdateCnt > aPulseThreshold) {
        if (mParticles.size() > 0) {
            MarkDirty();
        }
    } else {
        MarkDirty();
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
	mUnk0xE0              = (int)self;
	bool isLoading = mApp->mUnk0x779;
	while (isLoading) {
		Sleep(10);
		isLoading = mApp->mUnk0x779;
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
		mBallVelY += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp388,116", 0.2f);
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

// FUNCTION: POPCAPGAME1 0x0049f2d0
void LoadingScreen::UpdateParticles()
{
    for (size_t i = 0; i < mParticles.size(); i++)
    {
        // STRING: POPCAPGAME1 0x00601ff0
        mParticles[i].mAlpha -= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp414,332", 6);

        if (mParticles[i].mAlpha <= 0)
        {
            if (i < mParticles.size() - 1)
            {
                mParticles[i] = mParticles.back();
            }

            mParticles.pop_back();
        }
        else
        {
            float speedFactor = 0.25 - (mParticles[i].mVelX * mParticles[i].mVelY) + (mParticles[i].mVelX * mParticles[i].mVelY);
            // STRING: POPCAPGAME1 0x00601fa8
            mParticles[i].mY += + mParticles[i].mVelY + (speedFactor * ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp415,345", 3.0f) * sin(mParticles[i].mAngle));
            // STRING: POPCAPGAME1 0x00601f60
            mParticles[i].mX += mParticles[i].mVelX + (speedFactor * ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp416,346", 3.0f) * cos(mParticles[i].mAngle));

            float angleDelta;
            if (mParticles[i].mFlip)
            {
                angleDelta = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp417,350", 0.015f);
            }
            else
            {
                angleDelta = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp418,350", -0.015f);
            }
            mParticles[i].mAngle += angleDelta;
        }
    }
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

// TEMPLATE: POPCAPGAME1 0x0040f290
// std::operator+<char,std::char_traits<char>,std::allocator<char> >(class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const &, char const *)

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
			if (!PeekMessageA(&msg, NULL, WM_NULL, WM_NULL, PM_REMOVE) || msg.message == 0x12 || !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
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
							app->LoadMusic(app->mUnk0x780, path + findData.cFileName);

							
						}
					}
				}
                app->mUnk0x780++;
			}
		} while (FindNextFileA(hFind, &findData) != 0);

		FindClose(hFind);
	}

	// STRING: POPCAPGAME1 0x0000606f9c
	OutputDebugStringA("Done with level music loading\r\n");

	loadingScreen->mLevelLoadMusicThread = NULL;
}
