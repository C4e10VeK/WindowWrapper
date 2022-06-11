#pragma once

#include "Types.hpp"
#include "Vector.hpp"

namespace winWrap
{
	struct WindowParams
	{
		Size size;
		ivec2 position;
		bool resizeable;

		explicit WindowParams(
				Size _size = {},
				ivec2 _position = {},
				bool _resizeable = true
			) : size(_size),
			  	position(_position),
			  	resizeable(_resizeable) { }

		explicit WindowParams(
				i32 _width = {},
				i32 _height = {},
				ivec2 _position = {},
				bool _resizeable = true
			) : WindowParams({_width, _height}, _position, _resizeable) { }
	};
}

