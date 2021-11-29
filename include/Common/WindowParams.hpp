#ifndef WINDOWWRAPPER_WINDOWPARAMS_HPP
#define WINDOWWRAPPER_WINDOWPARAMS_HPP

#include "Types.hpp"
#include "VectorT.hpp"

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

#endif // WINDOWWRAPPER_WINDOWPARAMS_HPP
