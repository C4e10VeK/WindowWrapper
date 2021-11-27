#ifndef WINDOWWRAPPER_WINDOWPARAMS_HPP
#define WINDOWWRAPPER_WINDOWPARAMS_HPP

#include "Types.hpp"
#include "VectorT.hpp"
#include <filesystem>
#include <utility>

namespace winWrap
{
	struct WindowParams
	{
		i32 width;
		i32 height;
		ivec2 position;

		std::filesystem::path icon;

		bool resizeable;

		explicit WindowParams(
				i32 _width = {},
				i32 _height = {},
				ivec2 _position = {},
				std::filesystem::path _icon = "",
				bool _resizeable = true
			)
			: width(_width),
			  height(_height),
			  position(_position),
			  icon(std::move(_icon)),
			  resizeable(_resizeable) { }
	};
}

#endif // WINDOWWRAPPER_WINDOWPARAMS_HPP
