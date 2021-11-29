#ifndef WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP
#define WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP

#include <string>
#include "Types.hpp"

namespace winWrap
{
	template <typename T>
	struct vec2;

	using Size = vec2<i32>;

	struct InternalEvent;
	struct WindowParams;

	class IPlatformWindow
	{
	public:
		virtual ~IPlatformWindow() = default;

		virtual bool init(const std::string &title, const WindowParams &params) = 0;

		virtual i32 getWidth() const = 0;
		virtual i32 getHeight() const = 0;

		virtual Size getSize() const = 0;

		virtual vec2<i32> getPosition() const = 0;
		virtual void setPosition(const vec2<i32> &position) = 0;

		virtual void setTitle(const std::string &title) = 0;

		virtual void setResizable(bool resizable) = 0;

		virtual bool pollEvent(InternalEvent &event) = 0;
	};	
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
