#include <iostream>

#include <WinWrap/WindowWrapper.hpp>

int main()
{
	winWrap::WindowParams params(800, 600, winWrap::ivec2(100), true);

//	winWrap::Window wnd("Hello World", params);
	winWrap::Window wnd;
	
	if (!wnd.init("Hello World", params))
	{
		std::cerr << "Failed to create Window" << std::endl;
		std::abort();
	}

	wnd.keyPressed = winWrap::createCallback([](winWrap::IWindow &sender, winWrap::Key key)
	{
		std::cout << "Key: " << static_cast<winWrap::u32>(key) << std::endl;
		if (key == winWrap::Key::Escape)
			sender.close();
	});

	wnd.resized = winWrap::createCallback([](auto &wnd, auto size)
	{
		std::cout << "Size = " << "{width: " << size.width << "; height: " << size.height << "}" << std::endl;
	});

	wnd.mouseButtonPressed = winWrap::createCallback([](auto &wnd, auto btn)
	{
		if (btn == winWrap::Button::Left)
			std::cout << "left btn clicked" << std::endl;
	});

	while (!wnd.isClosed())
	{
		wnd.pollEvents();
	}

	return EXIT_SUCCESS;
}

