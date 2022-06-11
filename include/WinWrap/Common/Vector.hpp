#pragma once

#include "Types.hpp"

namespace winWrap
{
	template <typename T>
	struct vec2
	{
		union
		{
			T x;
			T width;
		};

		union
		{
			T y;
			T height;
		};

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

		constexpr bool operator==(const vec2<T> &v) const
		{
			return (x == v.x && y == v.y);
		}

		constexpr bool operator!=(const vec2<T> &v) const
		{
			return (x != v.x && y != v.y);
		}
	};

	template <typename T>
	constexpr vec2<T> operator+(const vec2<T> &v1, const vec2<T> &v2)
	{
		return vec2<T>(v1.x + v2.x, v1.y + v2.y);
	}

	template <typename T>
	constexpr vec2<T> operator-(const vec2<T> &v1, const vec2<T> &v2)
	{
		return vec2<T>(v1.x - v2.x, v1.y - v2.y);
	}

	template <typename T>
	constexpr vec2<T> operator*(const vec2<T> &v1, const vec2<T> &v2)
	{
		return vec2<T>(v1.x * v2.x, v1.y * v2.y);
	}

	template <typename T>
	constexpr vec2<T> operator/(const vec2<T> &v1, const vec2<T> &v2)
	{
		return vec2<T>(v1.x / v2.x, v1.y / v2.y);
	}

	template <typename T>
	constexpr vec2<T> operator*(const vec2<T> &v, const float &s)
	{
		return vec2<T>(v.x * s, v.y * s);
	}

	template <typename T>
	constexpr vec2<T> operator/(const vec2<T> &v, const float &s)
	{
		return vec2<T>(v.x / s, v.y / s);
	}

	using ivec2 = vec2<i32>;
	using Size = ivec2;
	using uvec2 = vec2<u32>;
	using fvec2 = vec2<float>;
	using dvec2 = vec2<double>;
}

