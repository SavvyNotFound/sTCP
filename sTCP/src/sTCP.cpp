#include "sTCP.h"

#include <sTCP/Log.h>

namespace sTCP {

    bool Init()
    {
        Log::Init();

        sTCP_INFO("Initialized Succesfully");

        return true;
    }

}
