#pragma once

#ifdef _WIN32

#include <Windows.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace Independent::D3D12 {

    inline void CheckHRESULT(HRESULT result, const char* operation)
    {
        if (SUCCEEDED(result))
            return;

        std::ostringstream message;

        message << operation
            << " failed. HRESULT = 0x"
            << std::hex
            << std::uppercase
            << static_cast<unsigned long>(result);

        throw std::runtime_error(message.str());
    }

}

#endif