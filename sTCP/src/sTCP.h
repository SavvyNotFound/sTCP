#pragma once

#include <sTCP/Log.h>

#include <csignal>
#define sTCP_DEBUGBREAK() raise(SIGTRAP)

#ifdef sTCP_ENABLE_ASSERTS
    #define sTCP_ASSERT(x, ...) { if(!(x)) { sTCP_ERROR("Assertion Failed: {0}", __VA_ARGS__); sTCP_DEBUGBREAK(); } }
    #define sTCP_CORE_ASSERT(x, ...) { if(!(x)) { sTCP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); sTCP_DEBUGBREAK(); } }
#else
    #define sTCP_ASSERT(x, ...)
    #define sTCP_CORE_ASSERT(x, ...)
#endif

namespace sTCP {

    bool Init();

}
