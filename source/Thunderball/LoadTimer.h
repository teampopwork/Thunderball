#ifndef __LOAD_TIMER_H__
#define __LOAD_TIMER_H__

namespace Sexy
{
class LoadTimer {
public:
	LoadTimer();

	void Begin();
	void End();
	void AddTime();
};

} // namespace Sexy

#endif // __LOAD_TIMER_H__
