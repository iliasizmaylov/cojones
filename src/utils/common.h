#pragma once

#include <iostream>

template <class... Args>
static void __clog(Args&& ...in)
{
	([&] {
		std::cout << in << " ";
	}(), ...);
}

#define COJONES_LOG_INFO(...)	\
	__clog("COJONES [INFO]:", __FUNC__, ":", __VA_ARGS__);
#define COJONES_LOG_ERR(...)	\
	__clog("COJONES [ERROR]:", __FUNC__, ":", __VA_ARGS__);
