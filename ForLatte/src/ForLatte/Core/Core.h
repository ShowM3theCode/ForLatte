#pragma once

#include <memory>

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

#ifdef FL_ENABLE_ASSERTS
	#define FL_ASSERT(x, ...) { if (!(x)) { FL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FL_CORE_ASSERT(x, ...) { if (!(x)) { FL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FL_ASSERT(x, ...) 
	#define FL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ForLatte {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
