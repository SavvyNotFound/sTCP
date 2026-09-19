#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace sTCP {

    class Log
    {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetBareLogger() { return s_BareLogger; }
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_BareLogger;
    };

}

#define sTCP_TRACE(...)     ::sTCP::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define sTCP_INFO(...)      ::sTCP::Log::GetCoreLogger()->info(__VA_ARGS__)
#define sTCP_WARN(...)      ::sTCP::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define sTCP_ERROR(...)     ::sTCP::Log::GetCoreLogger()->error(__VA_ARGS__)
#define sTCP_CRITICAL(...)  ::sTCP::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Bare Logger
#define sTCP_LOG(...)       ::sTCP::Log::GetBareLogger()->trace(__VA_ARGS__)
