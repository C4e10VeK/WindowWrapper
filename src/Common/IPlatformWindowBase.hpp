#ifndef WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP
#define WINDOWWRAPPER_SRC_COMMON_PLATFORM_WINDOW_BASE_HPP

#include <string>

namespace winWrap
{
    class IPlatformWindowBase
{
    public:
        virtual ~IPlatformWindowBase() = default;

        virtual bool init(const std::string &title) = 0;
        virtual void setTitle(const std::string &title) = 0;
    };


}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
