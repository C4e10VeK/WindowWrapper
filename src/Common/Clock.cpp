#include <WinWrap/Common/Clock.hpp>

namespace winWrap
{
	Clock::Clock() : m_offsetTime(InteranlClock::now()) { }

	Time Clock::getElapsedTime()
	{
		static InteranlClock::time_point startTime = m_offsetTime;
		const InteranlClock::time_point now = InteranlClock::now();
		std::chrono::duration res = now - startTime;
		startTime = now;

		return Time(std::chrono::duration_cast<std::chrono::microseconds>(res).count());
	}

	Time Clock::getTime()
	{
		const InteranlClock::time_point now = InteranlClock::now();
		std::chrono::duration res = now - m_offsetTime;

		return Time(std::chrono::duration_cast<std::chrono::microseconds>(res).count());
	}
	
} // namespace winWrap
