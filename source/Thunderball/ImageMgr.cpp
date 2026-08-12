#include "ImageMgr.h"

#include <SexyAppFramework/Image.h>
#include <SexyAppFramework/DDImage.h>
#include <SexyAppFramework/MemoryImage.h>
#include <SexyAppFramework/SexyApp.h>

using namespace Sexy;

// FUNCTION: POPCAPGAME1 0x00464960
ImageMgr::ImageMgr()
{
}

// SYNTHETIC: POPCAPGAME1 0x00464a00
// Sexy::ImageMgr::`scalar deleting destructor'

// FUNCTION: POPCAPGAME1 0x00461020
ImageMgr::~ImageMgr()
{
}

// FUNCTION: POPCAPGAME1 0x0044b580
void ImageMgr::AddDeleteImage(Image* theImage)
{
	if (theImage != NULL) {
		mDeleteImages.insert(theImage);
	}
}

// FUNCTION: POPCAPGAME1 0x00457610
void ImageMgr::Clear()
{
	for (std::map<std::string, MemoryImage*>::iterator it = mImages.begin(); it != mImages.end(); ++it) {
		delete it->second;
	}
	for (std::set<Image*>::iterator it = mDeleteImages.begin(); it != mDeleteImages.end(); ++it) {
		delete *it;
	}
	mImages.clear();
	mDeleteImages.clear();
}

// FUNCTION: POPCAPGAME1 0x00457760
MemoryImage* ImageMgr::GetImage(std::string* theName, bool* param_2, bool param_3)
{
	std::map<std::string, MemoryImage*>::iterator anItr = mImages.find(std::string(*theName));
	if (anItr->second == NULL) {
		if (param_3) {
			anItr->second = gSexyApp->GetImage(*theName, true);
		}
		if (param_2 != NULL) {
			*param_2 = false;
		}
	}
	else if (param_2 != NULL) {
		*param_2 = true;
	}
	return anItr->second;
}

// FUNCTION: POPCAPGAME1 0x0045c560
void ImageMgr::PutImage(std::string* theName, MemoryImage* theImage, bool param_3)
{
	MemoryImage*& anOldImage = mImages[*theName];
	if (anOldImage != theImage) {
		if (param_3 && anOldImage != NULL) {
			delete anOldImage;
		}
		anOldImage = theImage;
	}
}
