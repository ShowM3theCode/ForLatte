#pragma once

#ifdef FL_PLATFORM_WINDOWS
#ifdef FL_DYNAMIC_LINK
	#ifdef FL_BUILD_DLL
		#define ForLatte_API __declspec(dllexport)
	#else
		#define ForLatte_API __declspec(dllimport)
	#endif 
#else
	#define ForLatte_API
#endif
#else
	#error ForLatte only supports Windows!
#endif

#ifdef FL_DEBUG
	#define FL_ENABLE_ASSERTS
#endif

#ifndef FL_ENABLE_ASSERTS
	#define FL_ASSERT(x, ...) { FL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
	#define FL_CORE_ASSERT(x, ...) { FL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define FL_ASSERT(x, ...) 
	#define FL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
