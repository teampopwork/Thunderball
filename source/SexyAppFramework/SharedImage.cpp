#include "SharedImage.h"
#include "DDImage.h"
#include "SexyAppBase.h"

using namespace Sexy;

SharedImage::SharedImage()
{
	mImage = NULL;
	mRefCount = 0;
}

// FUNCTION: POPCAPGAME1 0x004d3160
SharedImageRef::SharedImageRef(const SharedImageRef& theSharedImageRef)
{
	mSharedImage = theSharedImageRef.mSharedImage;
	if (mSharedImage != NULL)
		mSharedImage->mRefCount++;
	mUnsharedImage = theSharedImageRef.mUnsharedImage;	
	mOwnsUnshared = false;
}

// FUNCTION: POPCAPGAME1 0x004d3190
SharedImageRef::SharedImageRef()
{
	mSharedImage = NULL;
	mUnsharedImage = NULL;
	mOwnsUnshared = false;
}

// FUNCTION: POPCAPGAME1 0x004d31a0
SharedImageRef::SharedImageRef(SharedImage* theSharedImage)
{
	mSharedImage = theSharedImage;
	if (theSharedImage != NULL)
		mSharedImage->mRefCount++;

	mUnsharedImage = NULL;
	mOwnsUnshared = false;
}

// FUNCTION: POPCAPGAME1 0x004db370
SharedImageRef::~SharedImageRef()
{
	Release();
}

// FUNCTION: POPCAPGAME1 0x004d31c0
void SharedImageRef::Release()
{	
	if (mOwnsUnshared)
		delete mUnsharedImage;
	mUnsharedImage = NULL;
	if (mSharedImage != NULL)
	{
		if (--mSharedImage->mRefCount == 0)
			gSexyAppBase->mCleanupSharedImages = true;
	}
	mSharedImage = NULL;
}

// FUNCTION: POPCAPGAME1 0x004d3210
SharedImageRef& SharedImageRef::operator=(const SharedImageRef& theSharedImageRef)
{
	Release();
	mSharedImage = theSharedImageRef.mSharedImage;
	if (mSharedImage != NULL)
		mSharedImage->mRefCount++;
	return *this;
}

// FUNCTION: POPCAPGAME1 0x004d3240
SharedImageRef&	SharedImageRef::operator=(SharedImage* theSharedImage)
{
	Release();
	mSharedImage = theSharedImage;
	mSharedImage->mRefCount++;
	return *this;
}

// FUNCTION: POPCAPGAME1 0x004d3260
SharedImageRef& SharedImageRef::operator=(MemoryImage* theUnsharedImage)
{
	Release();
	mUnsharedImage = theUnsharedImage;	
	return *this;
}

MemoryImage* SharedImageRef::operator->()
{
	return (MemoryImage*) *this;
}

// FUNCTION: POPCAPGAME1 0x004dc730
SharedImageRef::operator Image*()
{	
	return (MemoryImage*) *this;
}

SharedImageRef::operator MemoryImage*()
{
	if (mUnsharedImage != NULL)
		return mUnsharedImage;
	else
		return (DDImage*) *this;
}

// FUNCTION: POPCAPGAME1 0x004d3280
SharedImageRef::operator DDImage*()
{
	if (mSharedImage != NULL)
		return mSharedImage->mImage;
	else
		return NULL;
}
