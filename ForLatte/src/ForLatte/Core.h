#pragma once

#ifdef FL_PLATFORM_WINDOWS
	#ifdef FL_BUILD_DLL
		#define ForLatte_API __declspec(dllexport)
	#else
		#define ForLatte_API __declspec(dllimport)
	#endif 
#else
	#error ForLatte only supports Windows!
#endif
