#ifndef WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

#include <string>

namespace winWrap
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual bool init() = 0;
        virtual bool isClosed() const = 0;
        virtual void close() = 0;
        virtual std::string getTitle() const = 0;
        virtual void setTitle(const std::string &title) = 0;
    };


}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
