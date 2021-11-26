#ifndef WINDOWWRAPPER_INPUTUTILS_HPP
#define WINDOWWRAPPER_INPUTUTILS_HPP

#include <Common/Types.hpp>

namespace winWrap
{
	enum class Key;

	Key specificPlatformKeyToKey(u32 key);
	i32 keyToSpecificPlatformKey(Key key);
}

#endif // WINDOWWRAPPER_INPUTUTILS_HPP
