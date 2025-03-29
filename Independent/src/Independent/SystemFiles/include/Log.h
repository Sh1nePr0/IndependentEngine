#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Independent/Core/include/containers/SharedPtr.h"


namespace Independent {

	class INDEPENDENT_API Log
	{
	public:
		static void Init();

		inline static SharedPtr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static SharedPtr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static SharedPtr<spdlog::logger> s_CoreLogger;
		static SharedPtr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define IDPD_CORE_TRACE(...)    ::Independent::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IDPD_CORE_INFO(...)     ::Independent::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IDPD_CORE_WARNING(...)  ::Independent::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IDPD_CORE_ERROR(...)    ::Independent::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IDPD_CORE_FATAL(...)    ::Independent::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define IDPD_TRACE(...)			::Independent::Log::GetClientLogger()->trace(__VA_ARGS__)
#define IDPD_INFO(...)			::Independent::Log::GetClientLogger()->info(__VA_ARGS__)
#define IDPD_WARNING(...)		::Independent::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IDPD_ERROR(...)			::Independent::Log::GetClientLogger()->error(__VA_ARGS__)
#define IDPD_FATAL(...)			::Independent::Log::GetClientLogger()->fatal(__VA_ARGS__)

