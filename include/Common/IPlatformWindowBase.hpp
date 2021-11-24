#ifndef WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP
#define WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP

#include <string>
#include "Types.hpp"

namespace winWrap
{
	template <typename T>
	struct vec2;

	struct WindowParams;

	class IPlatformWindowBase
	{
	public:
		virtual ~IPlatformWindowBase() = default;

		virtual bool init(const std::string &title, const WindowParams &params) = 0;

		virtual bool isClosed() const = 0;
		virtual void close() = 0;

		virtual const std::string &getTitle() const = 0;
		virtual void setTitle(const std::string &title) = 0;

		virtual i32 getWidth() const = 0;
		virtual i32 getHeight() const = 0;

		virtual const vec2<i32> &getPosition() const = 0;
		virtual void setPosition(const vec2<i32> &position) = 0;

		virtual void pollEvent() = 0;
	};

	using IWindow = IPlatformWindowBase;
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
