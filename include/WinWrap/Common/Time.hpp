#pragma once

#include "Types.hpp"

// Retrieved from https://github.com/SFML/SFML/blob/master/include/SFML/System/Time.hpp

namespace winWrap
{
	class Time
	{
	private:
		i64 m_microSeconds;
	public:
		constexpr Time() : m_microSeconds(0) { }
		constexpr Time(i64 microSeconds) : m_microSeconds(microSeconds) { }

		constexpr double getSeconds() const
		{
			return static_cast<double>(m_microSeconds / 1000000.0);
		}

		constexpr i64 getMicroSeconds() const
		{
			return m_microSeconds;
		}

		constexpr i32 getMilliSeconds() const
		{
			return static_cast<i32>(m_microSeconds / 1000);
		}
	};
} // namespace winWrap
