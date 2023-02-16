#pragma once

#include "ForLatte/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ForLatte {
	class ForLatte_API Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}
	};

}

// Core Log Macros
#define FL_CORE_TRACE(...) ForLatte::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FL_CORE_INFO(...)  ForLatte::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FL_CORE_WARN(...)  ForLatte::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FL_CORE_ERROR(...) ForLatte::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FL_CORE_FATAL(...) ForLatte::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define FL_TRACE(...)      ForLatte::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FL_INFO(...)       ForLatte::Log::GetClientLogger()->info(__VA_ARGS__)
#define FL_WARN(...)       ForLatte::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FL_ERROR(...)      ForLatte::Log::GetClientLogger()->error(__VA_ARGS__)
#define FL_FATAL(...)      ForLatte::Log::GetClientLogger()->critical(__VA_ARGS__)