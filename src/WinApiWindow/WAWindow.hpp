#ifndef WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP
#define WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

#include "../Common/IPlatformWindowBase.hpp"

namespace winWrap
{
    class WAWindow : public IPlatformWindowBase
{
        bool init(const std::string &title) override;

        void setTitle(const std::string &title) override;
    };
}

#endif // WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP
