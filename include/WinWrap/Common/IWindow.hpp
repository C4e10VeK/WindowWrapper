#pragma once

#include "Types.hpp"

#include <string>

namespace winWrap
{
	template<typename T> struct vec2;
	using ivec2 = vec2<i32>;

	using Size = ivec2;

	struct WindowParams;

	class IPlatformWindow;

	class IWindow
	{
	public:
		virtual ~IWindow() = default;

		virtual bool init(const std::string &title, const WindowParams &params) = 0;

		[[nodiscard]] virtual bool isClosed() const = 0;
		virtual void close() = 0;

		[[nodiscard]] virtual i32 getWidth() const = 0;
		[[nodiscard]] virtual i32 getHeight() const = 0;

		[[nodiscard]] virtual Size getSize() const = 0;
		[[nodiscard]] virtual Size getWindowSize() const = 0;

		[[nodiscard]] virtual ivec2 getPosition() const = 0;
		virtual void setPosition(const ivec2 &position) = 0;

		[[nodiscard]] virtual const std::string &getTitle() const = 0;
		virtual void setTitle(const std::string &title) = 0;

		virtual WindowParams getParams() = 0;

		virtual void pollEvents() = 0;
	};
}

