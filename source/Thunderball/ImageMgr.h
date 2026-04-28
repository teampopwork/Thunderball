#ifndef __IMAGE_MGR_H__
#define __IMAGE_MGR_H__

#include <string>

namespace Sexy
{
class Image;
class MemoryImage;

class ImageMgr {
public:
    ImageMgr();
    virtual ~ImageMgr();

    void AddDeleteImage(Image* theImage);
    void Clear();

    MemoryImage* GetImage(std::string* theName, bool* param_2, bool param_3);
    void PutImage(std::string* theName, MemoryImage* theImage, bool param_3);
};

} // namespace Sexy

#endif // __IMAGE_MGR_H__
