#pragma once

#include <cstdint>

namespace status_pdu
{

struct NackSn
{
    uint32_t mNackSn = 0u;
    bool mExtensionBit1 = true;
    bool mExtensionBit2 = false;
    bool mExtensionBit3 = false;
    uint16_t mSoStart = 0u;
    uint16_t mSoEnd = 0u;
    uint8_t mLength = 0u;
};

}  // namespace status_pdu
