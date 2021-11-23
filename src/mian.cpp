#include <iostream>

#include <X11/Xlib.h>

#include "LinuxWindow/X11Window.hpp"

#include "Common/Window.hpp"

int main()
{
    winWrap::Window wnd("Hello world");

    if(!wnd.init())
    {
        std::cerr << "Failed to create Window" << std::endl;
        std::abort();
    }

//	winWrap::X11Window wnd(800, 600);
//	if (!wnd.init("Hello World"))
//	{
//		std::cerr << "Failed to create Window" << std::endl;
//		std::abort();
//	}
//
//    Atom wm_delete_window = XInternAtom(wnd.m_display, "WM_DELETE_WINDOW", False);
//    XSetWMProtocols(wnd.m_display, wnd.m_xWindow, &wm_delete_window, 1);
//
//	while (!wnd.isClosed())
//	{
//        while (XPending(wnd.m_display) > 0)
//        {
//            XEvent e;
//            XNextEvent(wnd.m_display, &e);
//            switch (e.type)
//            {
//            case KeyPress:
//            {
//                printf("KeyPress: %x\n", e.xkey.keycode);
//                if (e.xkey.keycode == 0x09)
//                    wnd.close();
//            }
//            break;
//            default:
//                break;
//            }
//
//            if (e.type == ClientMessage)
//            {
//                if (e.xclient.data.l[0] == wm_delete_window)
//                {
//                    wnd.close();
//                }
//            }
//
//            if (e.type == DestroyNotify)
//            {
//                wnd.close();
//            }
//        }
//	}

	return EXIT_SUCCESS;
}

