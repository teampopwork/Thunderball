#ifndef __DDINTERFACE_H__
#define __DDINTERFACE_H__

#include "Common.h"
#include "CritSect.h"
#include "NativeDisplay.h"
#include "Rect.h"
#include "Ratio.h"

#include <ddraw.h>

namespace Sexy
{

class SexyAppBase;
class DDImage;
class Image;
class MemoryImage;
class D3DInterface;
class D3DTester;

typedef std::set<DDImage*> DDImageSet;

class DDInterface : public NativeDisplay
{
public:
	enum
	{
		RESULT_OK					= 0,
		RESULT_FAIL					= 1,
		RESULT_DD_CREATE_FAIL		= 2,
		RESULT_SURFACE_FAIL			= 3,
		RESULT_EXCLUSIVE_FAIL		= 4,
		RESULT_DISPCHANGE_FAIL		= 5,
		RESULT_INVALID_COLORDEPTH	= 6,
		RESULT_3D_FAIL				= 7
	};

	SexyAppBase*			mApp;
	D3DInterface*			mD3DInterface;
	D3DTester*				mD3DTester;
	bool					mIs3D;

	CritSect				mCritSect;
	bool					mInRedraw;
	LPDIRECTDRAW			mDD;
	LPDIRECTDRAW7			mDD7;
	LPDIRECTDRAWSURFACE		mPrimarySurface; // +0x60
	LPDIRECTDRAWSURFACE		mSecondarySurface; // +0x64
	LPDIRECTDRAWSURFACE		mDrawSurface; // +0x68
	LPDIRECTDRAWSURFACE		mScaleSurfaces[4]; // +0x6c
	int						mWidth; // +0x7c
	int						mHeight; // +0x80
	Ratio					mAspect; // +0x84
	int						mDesktopWidth; // +0x8c
	int						mDesktopHeight; // +0x90
	Ratio					mDesktopAspect; // +0x94
	bool					mIsWidescreen; // +0x9c
	int						mDisplayWidth; // +0xa0
	int						mDisplayHeight; // +0xa4
	Ratio					mDisplayAspect; // +0xa8

	Rect					mPresentationRect; // +0xb0
	int						mFullscreenBits;
	DWORD					mRefreshRate;
	DWORD					mMillisecondsPerFrame; // +0xc8
	int						mScanLineFailCount; // +0xcc

	int*					mRedAddTable;
	int*					mGreenAddTable;
	int*					mBlueAddTable;

	ulong					mRedConvTable[256];
	ulong					mGreenConvTable[256];
	ulong					mBlueConvTable[256];

	bool					mInitialized; // +0xcdc
	HWND					mHWnd; // +0xce0
	bool					mIsWindowed; // +0xce4
	DDImage*				mScreenImage; // +0xce8
	DDImage*				mSecondaryScreenImage; // +0xcec
	DDImageSet				mDDImageSet; // +0xcf0
	bool					mVideoOnlyDraw;
	ulong					mInitCount; // +0xd00

	int						mCursorWidth; // +0xd04
	int						mCursorHeight; // +0xd08
	int						mNextCursorX;
	int						mNextCursorY;
	int						mCursorX;
	int						mCursorY;
	Image*					mCursorImage;
	bool					mHasOldCursorArea; // +0xd20
	LPDIRECTDRAWSURFACE		mOldCursorArea; // +0xd24
	LPDIRECTDRAWSURFACE		mNewCursorArea;	// +0xd28
	DDImage*				mOldCursorAreaImage; // +0xd2c
	DDImage*				mNewCursorAreaImage; // +0xd30

	std::string				mErrorString; // +0xd34

public:
	bool					CopyBitmap(LPDIRECTDRAWSURFACE theSurface, HBITMAP TheBitmap, int theX, int theY, int theWidth, int theHeight);
	ulong					GetColorRef(ulong theRGB);
	void					AddDDImage(DDImage* theDDImage);
	void					RemoveDDImage(DDImage* theDDImage);
	void					Remove3DData(MemoryImage* theImage); // for 3d texture cleanup

	void					Cleanup();
	bool					GotDXError(HRESULT theResult, const char *theContext = "");

	void					RestoreOldCursorAreaFrom(LPDIRECTDRAWSURFACE theSurface, bool adjust);
	void					DrawCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust);
	void					MoveCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust, int theNewCursorX, int theNewCursorY);

	HRESULT					CreateSurface(DDSURFACEDESC2 *theDesc, LPDIRECTDRAWSURFACE *theSurface, void*);
	void					ClearSurface(LPDIRECTDRAWSURFACE theSurface);
	bool					Do3DTest(HWND theHWND);
	void					CreateScaleSurfaces(int theWidth, int theHeight);

public:
	DDInterface(SexyAppBase* theApp);
	virtual ~DDInterface();

	static std::string		ResultToString(int theResult);

	DDImage*				GetScreenImage();
	int						Init(HWND theWindow, bool IsWindowed);	
	bool					Redraw(Rect* theClipRect = NULL);	
	void					SetVideoOnlyDraw(bool videoOnly);
	void					RemapMouse(int& theX, int& theY);

	bool					SetCursorImage(Image* theImage);
	void					SetCursorPos(int theCursorX, int theCursorY);
};

}

#endif //__DDINTERFACE_H__

