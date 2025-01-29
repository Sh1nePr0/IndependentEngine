#pragma once

#ifdef IDPD_PLATFORM_WINDOWS
	#ifdef IDPD_BUILD_DLL
		#define INDEPENDENT_API __declspec(dllexport)
	#else
		#define INDEPENDENT_API __declspec(dllimport)
	#endif
#else
	#error Independent only support Windows for now!
#endif
