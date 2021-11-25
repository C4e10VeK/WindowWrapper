#include <iostream>

#include <WindowWrapper.hpp>

void onKeyPress(winWrap::IWindow &sender, winWrap::u32 key)
{
	if (key == 0x09)
		sender.close();
}

int main()
{
	winWrap::WindowParams params(800, 600, {100, 100});

//	winWrap::Window wnd("Hello World", params);
	winWrap::Window wnd;

	if (!wnd.init("Hello World", params))
	{
		std::cerr << "Failed to create Window" << std::endl;
		std::abort();
	}

	wnd.keyPressed += &onKeyPress;

	while (!wnd.isClosed())
	{
		wnd.pollEvent();
	}

	return EXIT_SUCCESS;
}

