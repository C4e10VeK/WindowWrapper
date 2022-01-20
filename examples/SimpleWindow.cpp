#include <iostream>

#include <WindowWrapper.hpp>

int main()
{
	winWrap::WindowParams params(800, 600, winWrap::ivec2(100), false);

//	winWrap::Window wnd("Hello World", params);
	winWrap::Window wnd;
	
	if (!wnd.init("Hello World", params))
	{
		std::cerr << "Failed to create Window" << std::endl;
		std::abort();
	}

	wnd.keyPressed = winWrap::createCallback([](winWrap::IWindow &sender, winWrap::Key key)
	{
		if (key == winWrap::Key::Escape)
			sender.close();
	});


	while (!wnd.isClosed())
	{
		wnd.pollEvents();
	}

	return EXIT_SUCCESS;
}

