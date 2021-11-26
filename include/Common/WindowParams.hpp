#ifndef WINDOWWRAPPER_WINDOWPARAMS_HPP
#define WINDOWWRAPPER_WINDOWPARAMS_HPP

#include "Types.hpp"
#include "VectorT.hpp"

namespace winWrap
{
	struct WindowParams
	{
		i32 width;
		i32 height;

		ivec2 position;

		bool resizeable;

		explicit WindowParams(i32 _width = {}, i32 _height = {}, ivec2 _position = {}, bool _resizeable = true)
			: width(_width),
			  height(_height),
			  position(_position),
			  resizeable(_resizeable) { }
	};
}

#endif // WINDOWWRAPPER_WINDOWPARAMS_HPP
