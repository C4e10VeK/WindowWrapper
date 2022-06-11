#pragma once

#include "Time.hpp"
#include <type_traits>
#include <chrono>

// Retrieved from https://github.com/SFML/SFML/blob/master/include/SFML/System/Clock.hpp

namespace winWrap
{
	class Clock
	{
	private:
		using InteranlClock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
												 std::chrono::high_resolution_clock,
												 std::chrono::steady_clock>;

		InteranlClock::time_point m_offsetTime;
	public:
		explicit Clock();

		Time getElapsedTime();
		Time getTime();
	};
} // namespace winWrap
