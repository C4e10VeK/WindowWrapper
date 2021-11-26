#include <iostream>

#include <WindowWrapper.hpp>

int main()
{
	winWrap::WindowParams params(800, 600, {100, 100}, false);

//	winWrap::Window wnd("Hello World", params);
	winWrap::Window wnd;

	if (!wnd.init("Hello World", params))
	{
		std::cerr << "Failed to create Window" << std::endl;
		std::abort();
	}

	wnd.keyEvent += [](winWrap::IWindow &sender, winWrap::Key key, winWrap::EventType type)
	{
		std::cout << static_cast<winWrap::i32>(key) << std::endl;
		if (key == winWrap::Key::Escape)
			sender.close();
	};

	while (!wnd.isClosed())
	{
		wnd.pollEvent();
	}

	return EXIT_SUCCESS;
}

