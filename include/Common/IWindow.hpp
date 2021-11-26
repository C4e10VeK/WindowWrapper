#ifndef WINDOWWRAPPER_IWINDOW_HPP
#define WINDOWWRAPPER_IWINDOW_HPP

#include "Types.hpp"

#include "Event.hpp"
#include <string>

namespace winWrap
{
	template<typename T> struct vec2;
	using ivec2 = vec2<i32>;

	struct WindowParams;

	class IPlatformWindow;

	class IWindow
	{
	public:
		virtual ~IWindow() = default;

		virtual bool init(const std::string &title, const WindowParams &params) = 0;

		virtual bool isClosed() const = 0;
		virtual void close() = 0;

		virtual const std::string &getTitle() const = 0;
		virtual void setTitle(const std::string &title) = 0;

		virtual i32 getWidth() const = 0;
		virtual i32 getHeight() const = 0;

		virtual const ivec2 &getPosition() const = 0;
		virtual void setPosition(const ivec2 &position) = 0;

		virtual void pollEvent() = 0;
	};
}

#endif // WINDOWWRAPPER_IWINDOW_HPP
