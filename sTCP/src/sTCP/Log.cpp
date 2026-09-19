#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace sTCP {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_BareLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("[SERVER]");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_BareLogger = spdlog::stdout_color_mt("BareLogger");
        s_BareLogger->set_pattern("%v");
        s_BareLogger->set_level(spdlog::level::trace);
    }

}
