#pragma once

#ifdef IDPD_PLATFORM_WINDOWS
#if IDPD_DYNAMIC_LINK
	#ifdef IDPD_BUILD_DLL
		#define INDEPENDENT_API __declspec(dllexport)
	#else
		#define INDEPENDENT_API __declspec(dllimport)
	#endif
#else
	#define INDEPENDENT_API
#endif
#else
	#error Independent only support Windows for now!
#endif

#ifdef IDPD_DEBUG
	#define IDPD_ENABLE_ASSERTS
#endif

#ifdef IDPD_ENABLE_ASSERTS
	#define IDPD_ASSERT(x, ...) { if(!(x)) { IDPD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define IDPD_CORE_ASSERT(x, ...) { if(!(x)) { IDPD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define IDPD_ASSERT(x, ...)
	#define IDPD_CORE_ASSERT(x, ...)
#endif
 
#define BIT(x) (1 << x)

#define IDPD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)