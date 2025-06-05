#pragma once
#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64	
		#define IDPD_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
/* check for ios and macos */
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define IDPD_PLATFORM_IOS
		#error "IOS is not supported"
	#elif TARGET_OS_MAC == 1
		#define IDPD_PLATFORM_MACOS
		#error "MacOS is not supported"
	#else
		#error "Unknown Apple platform!"
	#endif
/* check for android and linux */
#elif defined(__ANDROID__)
	#define IDPD_PLATFORM_ANDROID	
	#error "Android is not supported!"
	
#elif defined(__linux__)
	#define IDPD_PLATFORM_LINUX
	#error "Linux is not supported!"

#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif

// DLL support
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