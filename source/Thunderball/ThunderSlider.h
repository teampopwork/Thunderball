#ifndef __THUNDERSLIDER_H__
#define __THUNDERSLIDER_H__

#include <SexyAppFramework/Slider.h>

namespace Sexy
{
class Graphics;
class ThunderSlider : public Slider {
public:
	std::string mUnk0xB8;

	ThunderSlider(const std::string& theString, int theId, SliderListener* theListener);

	virtual void Draw(Graphics* g);
};

} // namespace Sexy

#endif // __THUNDERSLIDER_H__
