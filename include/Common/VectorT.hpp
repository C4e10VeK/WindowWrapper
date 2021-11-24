#ifndef WINDOWWRAPPER_SRC_COMMON_VECTORT_HPP
#define WINDOWWRAPPER_SRC_COMMON_VECTORT_HPP

#include "Types.hpp"

namespace winWrap
{
	template <typename T>
	struct vec2
	{
		T x;
		T y;

		vec2() = default;
		explicit vec2(T s) : x(s), y(s) { }
		vec2(T _x, T _y) : x(_x), y(_y) { }

		constexpr vec2<T> operator+=(const vec2<T> &v) const
		{
			return {x + v.x, y + v.y};
		}

		constexpr vec2<T> operator-=(const vec2<T> &v) const
		{
			return {x - v.x, y - v.y};
		}
	};

	using ivec2 = vec2<i32>;
	using uvec2 = vec2<u32>;
	using fvec2 = vec2<float>;
}

#endif // WINDOWWRAPPER_SRC_COMMON_VECTORT_HPP