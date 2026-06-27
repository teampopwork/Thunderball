#include "Board.h"

#include "AIMgr.h"
#include "Ball.h"
#include "Brick.h"
#include "CharacterDialog.h"
#include "CharacterMgr.h"
#include "CollisionMgr.h"
#include "DataSync.h"
#include "DebugMgr.h"
#include "EffectMgr.h"
#include "EndLevelDialog.h"
#include "FloatingTextMgr.h"
#include "Gun.h"
#include "ImageMgr.h"
#include "InterfaceMgr.h"
#include "LevelEditor.h"
#include "LogicMgr.h"
#include "PhysObj.h"
#include "PlayerInfo.h"
#include "Poly.h"
#include "ReplayDialog.h"
#include "Res.h"
#include "SlotMachineDialog.h"
#include "SoundMgr.h"
#include "StatsMgr.h"
#include "ThunderButton.h"
#include "ThunderCommon.h"
#include "ThunderDialog.h"
#include "ThunderballApp.h"
#include "TrophyMgr.h"
#include "TypingCheck.h"
#include "GameStats.h"

#include <SexyAppFramework/WidgetManager.h>
#include <SexyAppFramework/SexyMatrix.h>
#include <SexyAppFramework/DDInterface.h>
#include <SexyAppFramework/D3DInterface.h>
#include <SexyAppFramework/MusicInterface.h>
#include <SexyAppFramework/MemoryImage.h>
#include <SexyAppFramework/Graphics.h>
#include <list>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x004238a0
Board::Board(ThunderballApp* theApp)
{
	mApp = theApp;
	mAIMgr = new AIMgr(this);
	mCharacterMgr = theApp->mCharacterMgr;
	mCollisionMgr = new CollisionMgr();
	mDebugMgr = new DebugMgr(this);
	mEffectMgr = new EffectMgr();
	mFloatingTextMgr = new FloatingTextMgr();
	mInterfaceMgr = new InterfaceMgr(this);
	mLevelEditor = new LevelEditor(this);
	mLogicMgr = new LogicMgr(this);
	mSoundMgr = new SoundMgr();
	mReplayDialog = new ReplayDialog(this);
	mEndLevelDialog = new EndLevelDialog(this);
	mSlotMachineDialog = new SlotMachineDialog(this);

	mUnk0x1a8 = 0x4b;
	mUnk0x1ac = 0x28;
	mUnk0x1b0 = 0x28a;
	mUnk0x170 = 0;
	mUnk0x1b4 = 0x230;
	mUnk0xc1 = false;
	mUnk0xc2 = false;
	mUnk0xc3 = false;
	mUnk0xea = false;
	mUnk0xc7 = false;
	mUnk0xc0 = true;
	mUnk0x11d = true;
	mUnk0x11e = false;
	mUnk0x120 = true;
	mUnk0x121 = false;
	mUnk0x122 = false;
	mUnk0x123 = false;
	mUnk0xcc = 0;
	mUnk0xd0 = 0xfa;
	mUnk0xc8 = 0;
	mUnk0xd4 = 0;
	mUnk0xd8 = 0x14;
	mUnk0x1d0 = 0;
	mUnk0x1b8 = 0;
	mUnk0x1bc = 0;
	mUnk0x1c0 = 0;
	mUnk0xec = 0;
	mUnk0xf0 = 0;
	mUnk0xf4 = 0;
	mUnk0x1c8 = 0;
	mUnk0x1cc = 0;
	mUnk0x130 = 0;
	mUnk0x188 = 0;
	mUnk0x18c = 0;

	mGun = new Gun(this);

	float fVar25 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp3,147", 0x46) - mUnk0x1ac;
	float fVar26 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp2,147", 400) - mUnk0x1a8;
	mGun->SetPos(fVar25, fVar26);

	mMenuButton = MakeEmbeddedButton(0, this, IMAGE_DLG_MENU, false);
	mMenuButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp4,153", 0xc),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp5,153", 0x21c)
	);
	mMenuButton->mUnk0x148 = false;
	AddWidget(mMenuButton);

	mReplayButton = MakeEmbeddedButton(1, this, IMAGE_DLG_INSTANTREPLAY, false);
	mReplayButton->Move(
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp6,158", 0x2e0),
		ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp7,158", 0x21c)
	);
	mReplayButton->mUnk0x148 = false;
	mReplayButton->mDisabled = true;
	mReplayButton->mUnk0x158 = false;
	AddWidget(mReplayButton);

	char* checkStrs[] = {"kathy", "steve", "shanon", "zoom", "scott", "seattle", "piano", "pitcher", "tennis", NULL};
	for (int i = 0; checkStrs[i] != NULL; i++) {
		mTypingCheckList[i] = new TypingCheck(checkStrs[i]);
	}

	Clear(true);
}

// FUNCTION: POPCAPGAME1 0x004299a0
Board::~Board()
{
    CheckIncTip();
    delete mCollisionMgr;
    delete mDebugMgr;
    delete mEffectMgr;
    delete mFloatingTextMgr;
    delete mInterfaceMgr;
    delete mLevelEditor;
    delete mLogicMgr;
    delete mSoundMgr;
    delete mReplayDialog;

    if (mEndLevelDialog->mWidgetManager != NULL) {
        GetThunderballApp()->mWidgetManager->RemoveWidget(mEndLevelDialog);
    }

    if (mSlotMachineDialog->mWidgetManager != NULL) {
        GetThunderballApp()->mWidgetManager->RemoveWidget(mSlotMachineDialog);
    }

    delete mEndLevelDialog;
    delete mSlotMachineDialog;

    for (int i = 0; i < 9; i++) {
        delete mTypingCheckList[i];
    }

    DeleteReplays(false);
    RemoveAllWidgets(true, false);
}

// FUNCTION: POPCAPGAME1 0x00402fd0
void Board::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
}

// FUNCTION: POPCAPGAME1 0x00406bf0
void Board::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	NotifyRemoving();
}

// FUNCTION: POPCAPGAME1 0x004025a0
void Board::GotFocus()
{
	Widget::GotFocus();
}

// FUNCTION: POPCAPGAME1 0x004025b0
void Board::LostFocus()
{
	Widget::LostFocus();
}

// FUNCTION: POPCAPGAME1 0x00402790
void Board::MouseMove(int theX, int theY)
{
	if (!mDebugMgr->MouseMove(theX, theY)) {
		mLogicMgr->MouseMove(theX, theY);
	}
}

// FUNCTION: POPCAPGAME1 0x004027d0
void Board::MouseDrag(int theX, int theY)
{
	if (!mDebugMgr->MouseDrag(theX, theY)) {
		mLogicMgr->MouseDrag(theX, theY);
	}
}

// FUNCTION: POPCAPGAME1 0x00402810
void Board::MouseDown(int theX, int theY, int theClickCount)
{
	if (mUnk0x1c0 != mUpdateCnt) {
		if (mUnk0x130 != 0) {
			mUnk0x130 = 1;
		}
	}
	else if (!mDebugMgr->MouseDown(theX, theY, theClickCount)) {
		if (mUnk0x1b8 != 0) {
			Pause(false);
		}
		else {
			mLogicMgr->MouseDown(theX, theY, theClickCount, false, false);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x004028a0
void Board::MouseUp(int theX, int theY, int theClickCount)
{
	if (!mDebugMgr->MouseUp(theX, theY, theClickCount) && (mUnk0x1b8 == 0)) {
		mLogicMgr->MouseUp(theX, theY, theClickCount, false);
	}
}

// FUNCTION: POPCAPGAME1 0x004028f0
void Board::MouseEnter()
{
	if (!mDebugMgr->MouseEnter()) {
		mLogicMgr->MouseEnter();
	}
}

// FUNCTION: POPCAPGAME1 0x00402910
void Board::MouseLeave()
{
	if (!mDebugMgr->MouseLeave()) {
		mLogicMgr->MouseLeave();
	}
}

// FUNCTION: POPCAPGAME1 0x00402930
void Board::KeyDown(KeyCode theKey)
{
	if (!mUnk0xea && !mLogicMgr->KeyDown(theKey) && (mUnk0x1b8 == 0)) {
		if (theKey == KEYCODE_RETURN) {
			MouseDown(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY, 1);
		}
		else if (theKey == KEYCODE_LEFT) {
			mLogicMgr->MouseWheel(-1);
		}
		else if (theKey == KEYCODE_RIGHT) {
			mLogicMgr->MouseWheel(1);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00406ec0
void Board::MouseWheel(int theDelta)
{
	if (!mDebugMgr->MouseWheel(theDelta) && (mUnk0x1b4 == 0)) {
		mLogicMgr->MouseWheel(theDelta);
	}
}

// STUB: POPCAPGAME1 0x00406f70
void Board::DrawOverlay(Graphics* g)
{
}

// STUB: POPCAPGAME1 0x00410e10
void Board::Update()
{
}

// FUNCTION: POPCAPGAME1 0x00425f00
void Board::ButtonDepress(int theId)
{
	if (mUnk0x108 == 0) {
		if ((theId == 1) && (mLogicMgr->mUnk0x4 == 1 || mLogicMgr->mUnk0x4 == 5) && (mUnk0xfc != 0) && (mReplayDialog->mWidgetManager == NULL)) {
			mReplayDialog->SetMode(false, mReplayButton->mUnk0x150, true);
			ShowReplay(-1, false);
			ShowReplayDialog();
		}
		else if (theId == 0) {
			mApp->DoOptionsDialog();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x0042df70
void Board::KeyChar(SexyChar theChar)
{
	bool bVar1 = mUnk0xea;
	if (mDebugMgr->KeyChar(theChar)) {
		mUnk0xea = false;
		if (bVar1) {
			mApp->KillDialog(1);
			mApp->KillDialog(0x23);
			mApp->KillDialog(0xd);
		}
	}
	else {
		if (!mUnk0xea) {
			if (mLogicMgr->KeyChar(theChar) && (mUnk0x1b8 == 0 || theChar == ' ')) {
				for (int i = 0; i < 9; i++) {
					if (mTypingCheckList[i]->Check(theChar)) {
						ActivateTypingCheck(i);
					}
				}
				if (theChar == ' ') {
					Pause(false);
				}
			}
		}
	}
}

// STUB: POPCAPGAME1 0x00425290
void Board::Draw(Graphics* g)
{
}

// FUNCTION: POPCAPGAME1 0x00402280
void Board::ShowEndLevelDialog()
{
	if (mLogicMgr->mUnk0x124) {
		if (mApp->mCurProfile != NULL && mApp->mCurProfile->mUnk0xee) {
			mApp->mCurProfile->mUnk0xee = false;
			mApp->mCurProfile->mUnk0xec = true;
		}
	}

	mEndLevelDialog->SetVisible(true);
	mWidgetManager->AddWidget(mEndLevelDialog);
}

// FUNCTION: POPCAPGAME1 0x00402480
void Board::RemoveSlotMachineDialog()
{
	if (mSlotMachineDialog->mWidgetManager != NULL) {
		mWidgetManager->RemoveWidget(mSlotMachineDialog);
		mSoundMgr->PauseMusic(false);
		mUnk0x1c0 = 0;
		mIsOver = Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY);
	}
}

// FUNCTION: POPCAPGAME1 0x00406a20
void Board::SubmitTotalStats()
{
	if (!mUnk0x11f && !mLogicMgr->mUnk0x124) {
		if ((mApp->mGameMode == ADVENTURE || mApp->mGameMode == QUICK_PLAY || mApp->mGameMode == CHALLENGE) && (0 < mLogicMgr->mUnk0x248[0].mUnk0x0)) {
			mUnk0x11f = true;
			mApp->mCurProfile->AddTotalStats(mLogicMgr->mUnk0x248[0]);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00402000
bool Board::Cheated()
{
	return mDebugMgr->mUnk0x20;
}

// FUNCTION: POPCAPGAME1 0x00402010
bool Board::HasShot()
{
	return mLogicMgr->mUnk0x248[0].mUnk0x0 > 0;
}

// FUNCTION: POPCAPGAME1 0x00402030
void Board::PositionReplayDialog()
{
	int iVar2 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp8,672", 0x48);
	int iVar3 = mReplayDialog->GetPreferredHeight(iVar2);
	int iVar5 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp10,676", 600) - iVar3;
	int iVar4 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp9,675", 0x31e);

	if (ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp11,678", 10) < mUnk0x108) {
		if (mApp->Is3DAccelerated()) {
			iVar4 -= (mUnk0xfc - 10) * ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp13,682", 0x10) / 10;
			iVar5 += (mUnk0xfc - 10) * ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp12,681", 0x10) / 10;
		}
	}

	mReplayDialog->Resize(iVar4, iVar5, iVar2, iVar3);
}

// FUNCTION: POPCAPGAME1 0x00402130
void Board::ShowReplayDialog()
{
	mLogicMgr->mUnk0xf5 = 1;
	mReplayDialog->StopBlinkingButtons();
	if (mReplayDialog->mWidgetManager == NULL) {
		PositionReplayDialog();
		if (mUnk0xc5 == 0) {
			mReplayDialog->DoScroll(true);
			// STRING: POPCAPGAME1 0x005d2868
			mReplayDialog->mY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp14,813", 10) + mReplayDialog->mHeight - IMAGE_DLG_REPLAYTOP->mHeight;
		}
		mWidgetManager->AddWidget(mReplayDialog);
	}
}

// FUNCTION: POPCAPGAME1 0x004021b0
void Board::RecordTrophyResult(bool param_1)
{
    if (mUnk0x128 != 0 && mUnk0xb4 == 4) {
        StatsMgr* aStatsMgr = mApp->mStatsMgr;
        TrophyStats* aStats = aStatsMgr->GetStatsForTrophy(mUnk0x128->mId);
        if (param_1) {
            aStats->mUnk0x0 += 1;
        } else {
            aStats->mUnk0x4 += 1;
        }
        aStatsMgr->Save(NULL);   
    }
}

// FUNCTION: POPCAPGAME1 0x00402210
void Board::ResizeEndLevelDialog()
{
    int iVar1 = mEndLevelDialog->GetPreferredHeight(mEndLevelDialog->mWidth);
    int iVar4 = (600 - iVar1) / 2;

    if (iVar4 < 55) {
        iVar4 = 55;
    }

    if (590 < iVar4 + iVar1) {
        iVar4 = 590 - iVar1;
    }

    mEndLevelDialog->Resize((800 - mEndLevelDialog->mWidth) / 2, iVar4, mEndLevelDialog->mWidth, iVar1);
}

// FUNCTION: POPCAPGAME1 0x004022f0
void Board::DoCharacterDialog(bool param_1)
{
	mUnk0xea = 1;
	CharacterDialog* aDialog = new CharacterDialog(this);
	int iVar1 = aDialog->mWidth;
	int iVar5 = 0;
	if (aDialog->mUnk0x219 != 0) {
		// STRING: POPCAPGAME1 0x005d28e0
		iVar5 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp16,1076", 0x28);
	}
	else {
		// STRING: POPCAPGAME1 0x005d28a4
		iVar5 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp17,1076", 0x3c);
	}

	aDialog->Resize((800 - iVar1) / 2, iVar5, iVar1, aDialog->GetPreferredHeight(iVar5));
	if (param_1) {
		aDialog->DoScroll(true);
	}
	mApp->AddDialog(aDialog->mId, aDialog);
}

// FUNCTION: POPCAPGAME1 0x004023f0
void Board::DoSlotMachineDialog(Ball* param_1, PhysObj* param_2)
{
    mSoundMgr->PauseMusic(true);
    mSlotMachineDialog->Init(param_1, param_2);
    mSlotMachineDialog->Resize((800 - mSlotMachineDialog->mWidth) / 2, ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp19,1118", 0x8c), mSlotMachineDialog->mWidth, mSlotMachineDialog->mHeight);
    mSlotMachineDialog->DoScroll(true);
    mWidgetManager->AddWidget(mSlotMachineDialog);
}

// FUNCTION: POPCAPGAME1 0x00402500
void Board::NotifyRemoving()
{
	mSoundMgr->PauseMusic(false);
	mWidgetManager->RemoveWidget(mLevelEditor);
	mWidgetManager->RemoveWidget(mReplayDialog);
	mWidgetManager->RemoveWidget(mSlotMachineDialog);

	if (mEndLevelDialog->mWidgetManager != NULL || mEndLevelDialog->mVisible || mWidgetManager == NULL) {
		mWidgetManager->RemoveWidget(mEndLevelDialog);
	} else {
		mEndLevelDialog->DoScrollOff(0);
		mApp->KillDialog(1);
		mApp->KillDialog(0x23);
	}
}

// FUNCTION: POPCAPGAME1 0x004025c0
void Board::Pause(bool param_1)
{
    if (param_1) {
        mMenuButton->mMouseVisible = false;
        mReplayButton->mMouseVisible = false;
        mReplayDialog->SetMouseVisibility(false);
        mUnk0x1b8++;
        
        
        if (GetThunderballApp()->GetDialog(16) != NULL) {
            return;
        }

        if (GetThunderballApp()->GetDialog(12) != NULL) {
            return;
        }

        if (GetThunderballApp()->GetDialog(15) != NULL /* && dialog->mUnk0x17c == NULL */) {
            return;
        }

        if (mApp->mUnk0x77c == 0) {
            mSoundMgr->PauseMusic(true);
            MarkDirty();
            return;
        }
    } else {
        mUnk0x1b8--;
        if (mUnk0x1b8 < 0) {
            mUnk0x1b8 = 0;
        }

        if (mUnk0x1b8 == 0) {
            mUnk0x121 = true;
            mSoundMgr->PauseMusic(false);
            mUnk0x1c0 = mUpdateCnt;
            if (mWidgetManager != NULL && mWidgetManager->mMouseIn) {
                MouseMove(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY);
            }
        }
        
    }

    MarkDirty();
}

// STUB: POPCAPGAME1 0x0040d000
void Board::DoReplayFileDialog(bool param_1, int param_2, bool param_3)
{
    Pause(true);
}

// FUNCTION: POPCAPGAME1 0x00406c10
void Board::CheckIncTip()
{
	if (mUnk0x122) {
		if (mApp->mCurProfile != NULL) {
			mApp->mCurProfile->IncTip(mEndLevelDialog->mUnk0x258);
		}
		mUnk0x122 = false;
	}
}

// FUNCTION: POPCAPGAME1 0x004026f0
void Board::SetSlowMo(bool param_1, int param_2)
{
	mUnk0xc1 = param_1;
	mUnk0xc3 = false;
	mUnk0xc8 = 0;
	mUnk0xc2 = false;
	mUnk0xcc = 0;
	mUnk0xd0 = param_2;
	mUnk0xd4 = 0;
	if (!param_1) {
		if (!mLogicMgr->mUnk0xfa) {
			mLogicMgr->KillSlowMoSound();
		}
		mUnk0x11c = false;
	}
}

// FUNCTION: POPCAPGAME1 0x00406da0
void Board::UpdateTwoPlayerStats()
{
    int dVar4 = 0;

    if (mLogicMgr->mUnk0x178 < mLogicMgr->mUnk0x174) {
        mApp->mUnk0x87c++;
        dVar4 = 0;
    } else {
        dVar4 = -1;
        if (mLogicMgr->mUnk0x174 < mLogicMgr->mUnk0x178) {
            mApp->mUnk0x880++;
            dVar4 = 1;
        }
    }

    if (dVar4 == mApp->mUnk0x894) {
        mApp->mUnk0x898++;
    } else {
        mApp->mUnk0x894 = dVar4;
        mApp->mUnk0x898 = 1;
    }

    mApp->mUnk0x89c->Add(mLogicMgr->mUnk0x248[0]);
    mApp->mUnk0x908->Add(mLogicMgr->mUnk0x248[1]);

    if (999999999 < mApp->mUnk0x88c || 999999999 < mApp->mUnk0x890) {
        mApp->mUnk0x88c = 0;
        mApp->mUnk0x890 = 0;
    }

    mApp->mUnk0x88c += mLogicMgr->mUnk0x174;
    mApp->mUnk0x890 += mLogicMgr->mUnk0x178;
}

// FUNCTION: POPCAPGAME1 0x00402760
void Board::BeginShot()
{
	if (mDebugMgr->mUnk0x4 == 0) {
		if (!mApp->IsScreenSaver()) {
			mApp->SetCursor(CURSOR_POINTER);
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00402ab0
void Board::ClearZoom()
{
	mUnk0xf8 = 0;
	mUnk0x104 = 0;
	mUnk0x108 = 0;
	PositionReplayDialog();
}

// FUNCTION: POPCAPGAME1 0x00402ad0
void Board::UpdateMgrs()
{
	if (!mLogicMgr->mUnk0xf5) {
		mAIMgr->Update();
	}

	mDebugMgr->Update();
	mLogicMgr->Update();

	if (!mUnk0xc2) {
		mCharacterMgr->CalcLookPos(this, false);
		mCharacterMgr->Update();
		mEffectMgr->Update(mUnk0xc1);
		mSoundMgr->Update();
	}
	else {
		mCharacterMgr->UpdateSlowMo();
		mSoundMgr->UpdateSounds();
	}

	if (mUnk0xc1) {
		mEffectMgr->UpdateSlowMo(mUnk0xd0 / 1000.0f);
	}

	mFloatingTextMgr->Update();
	mInterfaceMgr->Update();
}

// FUNCTION: POPCAPGAME1 0x00402ba0
void Board::UpdateSlowMo()
{
    if (mUnk0xc1) {
        mUnk0xcc += mUnk0xd0;
        if (mUnk0xcc < 1000) {
            mUnk0xc2 = true;
        } else {
            mUnk0xc2 = false;
            mUnk0xcc %= 1000;
        }

        if (!mUnk0xc3) {
            if (0 < mUnk0xc8 && mUnk0xc8-- == 0) {
                mUnk0xc3 = true;
            }
        } else {
            mUnk0xd0 += 20;
            if (ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp102,3739",900) <= mUnk0xd0 && mUnk0xd0 < ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp103,3739",0x398) && mLogicMgr->mUnk0xf9) {
                mLogicMgr->DoFeverMissed();
            }
            if (999 < mUnk0xd0) {
                SetSlowMo(false, 250);
            }
        }

        if (mUnk0xd4 != 0) {
            if (mUnk0xd4 < mUnk0xd0) {
                mUnk0xd0 -= mUnk0xd8;
                if (mUnk0xd0 <= mUnk0xd4) {
                    mUnk0xd0 = mUnk0xd4;
                    mUnk0xd4 = 0;
                    return;
                }
            } else {
                mUnk0xd0 += mUnk0xd8;
                if (mUnk0xd4 <= mUnk0xd0) {
                    mUnk0xd0 = mUnk0xd4;
                    mUnk0xd4 = 0;
                }
                if (999 < mUnk0xd0) {
                    SetSlowMo(false, 250);
                }
            }
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004073a0
bool Board::IsAltKeyUsed(WPARAM wParam)
{
	if (wParam == 0x65) {
		return true;
	}

	if (EditingLevel()) {
		return mLevelEditor->IsAltKeyUsed(wParam);
	}

	return false;
}

// FUNCTION: POPCAPGAME1 0x00402cf0
void Board::FinishHighScoreEntryDialog(std::string* param_1)
{
	mEndLevelDialog->FinishHighScoreEntryDialog(param_1);
}

// FUNCTION: POPCAPGAME1 0x00406c50
void Board::DrawShadow(Graphics* g, int param_2, int param_3, bool param_4)
{
    g->Translate(param_2, param_3);
    Image* aImage = IMAGE_INT_BACKSHADOW;
    int iVar3 = IMAGE_INT_BACKSHADOW->mWidth;
    int iVar2 = aImage->mHeight - ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp25,1834",0x19);

    Rect local_54 = Rect(0, 0, 0x1e, iVar2);
    Rect local_14 = Rect(0x1e, 0, 0xcd, 0x19);
    Rect local_24 = Rect(0xeb, 0, 0xad, 0x6c);
    Rect local_34 = Rect(0x198, 0, 0xcf, 0x19);
    Rect local_44 = Rect(0x267, 0, iVar3 + -0x267, iVar2);
    Rect local_64 = Rect(0, iVar2, iVar3, aImage->mHeight - iVar2);

    if (!param_4) {
        g->DrawImage(aImage, 0, 0, local_54);
        g->DrawImage(aImage, local_14.mX, local_14.mY, local_14);
        g->DrawImage(aImage, local_24.mX, local_24.mY, local_24);
        g->DrawImage(aImage, local_34.mX, local_34.mY, local_34);
        g->DrawImage(aImage, local_44.mX, local_44.mY, local_44);
    } else {
        g->DrawImage(aImage, 0, iVar2, local_64);
    }

    g->Translate(-param_2, -param_3);
}

// FUNCTION: POPCAPGAME1 0x00409020
void Board::MakeShadow(Image* param_1, int param_2, int param_3)
{
    Graphics aGraphics = Graphics(param_1);
    int iVar1 = (param_2 - param_1->mWidth) / 2;
    int iVar2 = (param_3 - param_1->mHeight) / 2;

    int iVar3 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp23,1810",1) - iVar1;
    int iVar4 = ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp24,1811",10) - iVar2;
    DrawShadow(&aGraphics, iVar3 - (param_2 - iVar1 / 2), iVar4 - (param_3 - iVar2 / 2), true);
}

// FUNCTION: POPCAPGAME1 0x004098b0
void Board::SyncColorblind()
{
	for (std::list<SmartPtr<PhysObj>>::iterator it = mUnk0x190.begin(); it != mUnk0x190.end(); ++it) {
		PhysObj* obj = it->get();
		if (obj->GetClass() == 6 && obj->mPegInfo != NULL) {
			Brick* brick = static_cast<Brick*>(obj);
			brick->DeleteImage();
			brick->CreateImage();
		}
	}
}

// FUNCTION: POPCAPGAME1 0x00409aa0
void Board::SetShowBackground(bool param_1)
{
    mUnk0xc0 = param_1;
    for (std::list<SmartPtr<PhysObj>>::iterator it = mUnk0x190.begin(); it != mUnk0x190.end(); ++it) {
        PhysObj* obj = it->get();
        if (obj->mUnk0x27 && obj->mUnk0xb4 != NULL && 400 < obj->mUnk0xb4->mWidth && 400 < obj->mUnk0xb4->mHeight) {
            obj->mUnk0x25 = mUnk0xc0;
            mUnk0xe8 = mUnk0xc0;
        }
    }
}

// FUNCTION: POPCAPGAME1 0x004029c0
bool Board::DoZoom(Graphics* g)
{
    if (0.0f < mUnk0xf8 && g->mIs3D && mUnk0x11d) {
        float fVar1 = mUnk0xf8;
        SexyTransform2D aTransform;
        fVar1 *= ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp66,2994", 1.0f) + 1.0f;
        aTransform.Translate(-(float) mUnk0xfc, -(float) mUnk0x100);
        aTransform.Scale(fVar1, fVar1);
        aTransform.Translate((float) mUnk0xfc, (float) mUnk0x100);
        mApp->mDDInterface->mD3DInterface->PushTransform(aTransform);
        return true;
    }
    return false;
}

// STUB: POPCAPGAME1 0x00420dd0
void Board::CheckTrophyAccomplishments()
{
    if (mApp->mCurProfile != NULL && mUnk0x128 != NULL && mUnk0xb4 != DEMO) {
        if ((mUnk0x128->mUnk0x74 == 0 && mUnk0x128->mUnk0x6c < 2) && (mUnk0x128->mUnk0x88.empty() && mDebugMgr->mUnk0x20 == 0) || mDebugMgr->mUnk0x21 != 0) {
            mApp->mCurProfile->CheckTrophyTopScore(mUnk0x128->mId, mLogicMgr->mUnk0x174);
        }

        if (mEndLevelDialog->mUnk0x180 == 6) {
            mApp->mCurProfile->AwardTrophy(mUnk0x128->mId);
            mUnk0x128->mUnk0x60 = 1;
        }
    }
}

// FUNCTION: POPCAPGAME1 0x00409920
void Board::CheckForBackground()
{
    mInterfaceMgr->SyncStageNum();
    for (std::list<SmartPtr<PhysObj>>::iterator it = mUnk0x190.begin(); it != mUnk0x190.end(); ++it) {
        PhysObj* obj = it->get();
        if (obj->mUnk0x27 && obj->mUnk0xb4 != NULL && 400 < obj->mUnk0xb4->mWidth && 400 < obj->mUnk0xb4->mHeight) {
            mUnk0xe8 = mUnk0xc0;
            obj->mUnk0x25 = mUnk0xc0;
            if (!obj->mUnk0x2f) {
                size_t uVar3 = obj->mUnk0x94.find("levels/");
                if (uVar3 != std::string::npos) {
                    SexyVector2 aCenter = obj->GetCenter();
                    MakeShadow(obj->mUnk0xb4, aCenter.x, aCenter.y);
                    obj->mUnk0xb4->mD3DFlags |= 0x8;
                }
            }
        }
    }
}

// STUB: POPCAPGAME1 0x00409b40
void Board::CheckExploderForFever(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0040ad10
void Board::UpdateZoom()
{
}

// FUNCTION: POPCAPGAME1 0x00406a80
void Board::CalcEndLevelDialog()
{
    bool cVar2 = mLogicMgr->BeatLevel();
    if (mUnk0x128 != NULL && 0 < mUnk0x128->mUnk0x70) {
        int iVar3 = 0;
        if (mUnk0x128->mUnk0x7c != 0) {
            iVar3 = (mUnk0x128->mUnk0x80 - mUnk0x128->mUnk0x7c) / 28;
        }
        if (iVar3 - 1 <= mUnk0xf0) {
            cVar2 = mUnk0x128->mUnk0x70 < mLogicMgr->mUnk0x174;
        }
    }

    if (mUnk0xb4 == 1) {
        mEndLevelDialog->mUnk0x180 = cVar2 ? 0 : 2;
    } else if (mUnk0xb4 != 4 || mUnk0x128 == NULL) {
        mEndLevelDialog->mUnk0x180 = 1;
    } else if (!mUnk0x128->mUnk0x74) {
        if (mUnk0xf0 < mUnk0x128->mUnk0x78->size()) {
            mEndLevelDialog->mUnk0x180 = 4;
        }
    } else if (cVar2) {
        if (mUnk0x128->mUnk0x78->size() <= mUnk0xf0) {
            RecordTrophyResult(true);
            mEndLevelDialog->mUnk0x180 = 6;
        } else {
            mEndLevelDialog->mUnk0x180 = 5;
        }
    } else if (mUnk0xdc < 1) {
        RecordTrophyResult(false);
        mEndLevelDialog->mUnk0x180 = 2;

    } else {
        mEndLevelDialog->mUnk0x180 = 3;
    }
}

// STUB: POPCAPGAME1 0x00422640
void Board::PlayMusic()
{
}

// FUNCTION: POPCAPGAME1 0x0040cf70
void Board::DeleteReplays(bool param_1)
{
    if (!param_1) {
        if (mUnk0x188 != NULL) {
            delete mUnk0x188;
        }
        mUnk0x188 = NULL;
    }

    if (mUnk0x18c != NULL) {
        delete mUnk0x18c;
    }
    mUnk0x18c = NULL;

    if (0 < mUnk0x174.size()) {
        for (int i = 0; i < mUnk0x174.size(); i++) {
            delete mUnk0x174[i];
        }
    }
    mUnk0x174.clear();
}

// FUNCTION: POPCAPGAME1 0x00420920
bool Board::LoadReplayFile(std::string& param_1)
{
    Buffer aBuffer = Buffer();
    bool uVar2 = mApp->ReadBufferFromFile(param_1, &aBuffer, true);
    if (uVar2) {
        DeleteReplays(true);
        DataReader aReader = DataReader();
        aReader.OpenMemory((void*)aBuffer.GetDataPtr(), aBuffer.GetDataLen(), false);
        ulong uVar5 = aReader.ReadLong();
        if (uVar5 < 50) {
            DataWriter* aWriter = new DataWriter();
            aWriter->OpenMemory(aBuffer.GetDataLen());
            aWriter->WriteBytes((void*)aBuffer.GetDataPtr(), aBuffer.GetDataLen());
            mUnk0x174.push_back(aWriter);
            return true;
        }

        uVar5 = aReader.ReadShort();
        int i = 0;
        if (uVar5 != 0) {
            while (i != uVar5) {
                ulong uVar6 = aReader.ReadLong();
                
                if (!aReader.CanReadBytes(uVar6)) {
                    return 0;
                }
                
                DataWriter* aWriter = new DataWriter();
                aWriter->OpenMemory(uVar6);
                
                void* sourceBuffer = aReader.ReadBytesFromMem(uVar6);
                aWriter->WriteBytes(sourceBuffer, uVar6);
                
                mUnk0x174.push_back(aWriter);
                
                i++;
            }
        }
    }
    return true;
}

// STUB: POPCAPGAME1 0x0040d8e0
PhysObj* Board::FindObj(PhysObj* param_1, bool param_2)
{
    return NULL;
}

// FUNCTION: POPCAPGAME1 0x004090d0
void Board::Reload()
{
    SmartPtr<Ball> aBall = new Ball(false);

    if (!mLogicMgr->mUnk0x69) {
        if (ModVal(0,"SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp101,3680",false)) {
            aBall->SetHat(true, true);
        }
    }
    mGun->Reload(aBall);
}

// FUNCTION: POPCAPGAME1 0x0040d7d0
void Board::Clear(bool param_1)
{
    GetThunderballApp()->mMusicInterface->StopMusic(0);
    mAIMgr->Clear();
    GetImageMgr()->Clear();
    mCollisionMgr->Clear();
    mDebugMgr->Clear();
    mEffectMgr->Clear();
    mFloatingTextMgr->Clear();
    mInterfaceMgr->Clear();
    mSoundMgr->Clear();
    mGun->Clear();
    mLogicMgr->Clear(param_1, false);
    mCharacterMgr->Clear(false);
    mCharacterMgr->CalcLookPos(this, true);
    mUnk0x190.clear();
    mUnk0x19c.clear();
    mUnk0x1d4.erase();
    PhysObj::gCurSortId = 0;
    mUnk0xe4 = 0;
    mUnk0xe8 = false;
    mUnk0xe9 = false;
    mUnk0xc4 = false;
    SetSlowMo(false, 250);
    DeleteReplays(false);
}

// STUB: POPCAPGAME1 0x00421070
void Board::AddObj(PhysObj* param_1, std::list<Sexy::SmartPtr<PhysObj>>::iterator param_2)
{
}

// STUB: POPCAPGAME1 0x00422a90
void Board::AddObj(PhysObj* param_1)
{
}

// STUB: POPCAPGAME1 0x0040fed0
void Board::RemoveObj(PhysObj* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x00410120
void Board::KillAllBalls()
{
    for (std::list<SmartPtr<Ball>>::iterator it = mUnk0x19c.begin(); it != mUnk0x19c.end(); ++it) {
        Ball* aBall = it->get();
        if (!aBall->mUnk0x140) {
            RemoveObj(aBall);
        }
    }
}

// STUB: POPCAPGAME1 0x00409d50
void Board::CheckForFever(Ball* param_1)
{
}

// STUB: POPCAPGAME1 0x00410ae0
void Board::UpdateObjects(bool param_1)
{
}

// STUB: POPCAPGAME1 0x00424fd0
void Board::CreateLayers()
{
}

// STUB: POPCAPGAME1 0x0040ac40
void Board::InitEndLevelDialog(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x0040f400
void Board::SyncCharacterOptions(bool param_1)
{
}

// STUB: POPCAPGAME1 0x0041e910
void Board::DoStageDialog(bool param_1)
{
}

// STUB: POPCAPGAME1 0x004227c0
void Board::LoadLevelBase(std::string* param_1, std::list<Sexy::SmartPtr<PhysObj>> param_2, bool param_3)
{
}

// STUB: POPCAPGAME1 0x0040fd90
void Board::ChangeHighScore(HighScoreEntry* param_1)
{
}

// STUB: POPCAPGAME1 0x00420b50
void Board::SubmitHighScore()
{
}

// STUB: POPCAPGAME1 0x00420e80
void Board::CheckClearAccomplishment()
{
}

// STUB: POPCAPGAME1 0x00427f20
void Board::DoLevelDone()
{
}

// STUB: POPCAPGAME1 0x0040f980
void Board::SyncModeOptions()
{
}

// STUB: POPCAPGAME1 0x00424090
void Board::SyncState(DataSync& theSync)
{
}

// STUB: POPCAPGAME1 0x00424a70
void Board::SetSyncPoint(DataWriter* param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00424c50
void Board::EndReplay()
{
}

// STUB: POPCAPGAME1 0x00427e50
bool Board::NeedSaveGame()
{
	return false;
}

// STUB: POPCAPGAME1 0x004249c0
void* Board::GetSyncPoint()
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00424d40
void Board::ShowReplay(int param_1, bool param_2)
{
}

// STUB: POPCAPGAME1 0x00424be0
void* Board::GetReplayPoint()
{
	return NULL;
}

// STUB: POPCAPGAME1 0x00424860
void Board::LoadGame(Buffer* param_1)
{
}

// STUB: POPCAPGAME1 0x00427d60
void Board::SaveGame()
{
}

// STUB: POPCAPGAME1 0x004101a0
void Board::MakeThumbnail()
{
}

// STUB: POPCAPGAME1 0x0041ea50
void Board::SetupLevel()
{
}

// STUB: POPCAPGAME1 0x00429d10
void Board::LoadLevel2(std::string* param_1)
{
}

// STUB: POPCAPGAME1 0x0042aae0
void Board::LoadLevel(std::string* param_1)
{
}

// FUNCTION: POPCAPGAME1 0x0042da00
void Board::Reset()
{
	SubmitTotalStats();
	CheckIncTip();
	mUnk0xb4 = mApp->mGameMode;
	mUnk0xf8 = 0;
	mUnk0xec++;
	mUnk0xf4++;
	mUnk0x104 = 0;
	mUnk0x108 = 0;
	mUnk0x10c = 0;
	mUnk0x110 = false;
	mUnk0x11c = 0;
	mUnk0x120 = true;
	mUnk0x12c = 0;

	if (mApp->mCurProfile != NULL && mApp->mGameMode == ADVENTURE) {
		mApp->mCurProfile->mUnk0x208++;
		if (1 < mApp->mCurProfile->mUnk0x208) {
			mApp->mCurProfile->mUnk0x20c++;
		}
		mApp->mCurProfile->mUnk0xec = true;
	}

	mUnk0xea = false;
	mUnk0xc7 = false;
	mUnk0x11f = 0;

	mApp->KillDialog(1);
	mWidgetManager->RemoveWidget(mReplayDialog);
	RemoveSlotMachineDialog();

	if (mEndLevelDialog->mWidgetManager == NULL || mEndLevelDialog->mVisible != false) {
		mWidgetManager->RemoveWidget(mEndLevelDialog);
	}
}

// FUNCTION: POPCAPGAME1 0x0042db70
void Board::LoadEasterEggLevel(std::string* param_1, int param_2)
{
	if (mApp->mGameMode == QUICK_PLAY || mApp->mGameMode == DUEL) {
		std::string levelName = "levels/" + *param_1;
		std::string levelPath = levelName + ".dat";
		mUnk0x1d4 = levelPath;
		mUnk0x123 = true;
		mUnk0x124 = param_2;
		Reset();
	}
}

// FUNCTION: POPCAPGAME1 0x0042dc60
void Board::ActivateTypingCheck(int param_1)
{
	std::string aString;
	int iVar5;
	bool bVar10;
	uint uVar6;
	bool bVar7;
	switch (param_1) {
	case 0:
		if ((mLogicMgr->mUnk0x4 != 1) || (mUnk0xb4 != 2)) return;

		iVar5 = mLogicMgr->mUnk0x128;
		bVar10 = mLogicMgr->mUnk0x1cc[iVar5] != POWERUP_2;
		uVar6 = (uint) bVar10;
		*(uint*) (mLogicMgr->mUnk0x1cc[iVar5]) = (int) (uVar6 << 0x1f) >> 0x1f & 2;
		*(uint*) (mLogicMgr->mUnk0x1e4[iVar5]) = (int) (uVar6 << 0x1f) >> 0x1f & 1000;
		mLogicMgr->ActivatePowerup(POWERUP_2, bVar10);
		break;

	case 1:
		if (mLogicMgr->mUnk0x4 != 1) {
			return;
		}

		mLogicMgr->SetWearHat(true);
		break;

	case 2:
		SetShowBackground(false);
		break;

	case 3:
		bVar7 = !mUnk0x11d;
		mUnk0x11d = bVar7;
		aString = bVar7 ? "Zoom Enabled" : "Zoom Disabled";
		break;

	case 4:
		bVar7 = !mUnk0x11e;
		mUnk0x11e = bVar7;
		aString = bVar7 ? "RightClick Speedup Enabled" : "RightClick Speedup Disabled";
		break;

	case 5:
		LoadEasterEggLevel(new std::string("seattle"), 0);
		break;

	case 6:
		LoadEasterEggLevel(new std::string("piano"), 1);
		break;

	case 7:
		LoadEasterEggLevel(new std::string("pitcher"), 2);
		break;

	case 8:
		LoadEasterEggLevel(new std::string("tennisracket"), 3);
		break;

	default:
		return;
	}
	if (!aString.empty()) {
		FloatingText* floatingText = mLogicMgr->AddStandardText(
			aString,
			mGun->mUnk0x114,
			mGun->mUnk0x118 + ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp54,2698", 0x5a),
			0x30
		);

		floatingText->mUnk0x68 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp55,2702", 100) + 10;
		floatingText->mUnk0x60 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp56,2704", 0xffff00);
		floatingText->mUnk0x54 = 0xffffffff;
		floatingText->mUnk0x8c = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp57,2706", 0.0f);
		floatingText->mUnk0x78 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp58,2707", 10);
		floatingText->mUnk0x74 = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp59,2708", 10);
	}
}

// FUNCTION: POPCAPGAME1 0x00410940
void Board::DrawScreenSaver(Graphics* g)
{
	g->SetColor(Color(0));
	g->FillRect(0, 0, mWidth, mHeight);

	g->SetFont(FONT_OVERLOAD24OUTLINE);

	g->SetColor(Color(0xffffff00));

	std::string str = "Peggle ScreenSaver Will Resume in";
	Rect rect;
	rect.mWidth = mWidth;
	rect.mX = 0;
	rect.mY = ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp64,2976", 200);
	rect.mHeight = 0;
	g->WriteWordWrapped(rect, str);

	str = StrFormat("%d", mUnk0x1c8 / 100 + 1);
	g->SetFont(FONT_OVERLOAD24OUTLINE);
	rect.mY += ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\Board.cpp65,2981", 0x3c);
	g->WriteWordWrapped(rect, str);
}

// FUNCTION: POPCAPGAME1 0x004024e0
bool Board::EditingLevel()
{
	return mLevelEditor->mWidgetManager != NULL;
}
