#include "WAWindow.hpp"

namespace winWrap
{
	bool PlatformWindow::init(const std::string &title, int width, int height)
	{
		return false;
	}

	bool PlatformWindow::isClosed() const
	{
		return true;
	}

	void PlatformWindow::close()
	{

	}

	const std::string &PlatformWindow::getTitle() const
	{
		return m_title;
	}

	void PlatformWindow::setTitle(const std::string &title)
	{

	}

	i32 PlatformWindow::getWidth() const
	{
		return 0;
	}

	i32 PlatformWindow::getHeight() const
	{
		return 0;
	}

	void PlatformWindow::pollEvent()
	{

	}
}