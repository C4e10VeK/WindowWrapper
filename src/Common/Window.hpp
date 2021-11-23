#ifndef WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

#include <memory>

#include "IWindowBase.hpp"
#include "IPlatformWindowBase.hpp"

namespace winWrap
{
    class Window : IWindowBase
    {
    private:
        std::shared_ptr<IPlatformWindowBase> m_platformWindowBase;
        std::string m_title;
        bool m_isClosed;
    public:
        explicit Window(const std::string &title, int width = 800, int height = 600);

        bool init() override;

        bool isClosed() const override;
        void close() override;

        std::string getTitle() const override;
        void setTitle(const std::string &title) override;

        bool init(const std::string &title, int width, int height);
    private:
        static std::shared_ptr<IPlatformWindowBase> createWindow(int width, int height);
    };
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
