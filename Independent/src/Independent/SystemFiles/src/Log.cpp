#include "idpdpch.h"
#include "Independent/SystemFiles/include/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Independent {

	SharedPtr<spdlog::logger> Log::s_CoreLogger;
	SharedPtr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("INDEPENDENT");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}

