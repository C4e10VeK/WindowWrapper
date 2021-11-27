#ifndef WINDOWWRAPPER_INPUTUTILS_HPP
#define WINDOWWRAPPER_INPUTUTILS_HPP

#include <Common/Types.hpp>

namespace winWrap
{
	enum class Key;

	struct KeyInfo
	{
		u64 key;
#if defined(_WIN32) || defined(__MINGW32__)
		i64 lParam;
#endif
	};

	Key specificPlatformKeyToKey(KeyInfo info);
	i32 keyToSpecificPlatformKey(Key key);
}

#endif // WINDOWWRAPPER_INPUTUTILS_HPP
