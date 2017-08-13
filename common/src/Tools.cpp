/*
 * Copyright (c) Nokia 2017. All rights reserved.
 */

#include "Tools.hpp"

namespace common
{
namespace utilities
{
    uint32_t shiftLeftOneByte(uint32_t data)
    {
        constexpr uint8_t BYTE = 8u;
        return (data << BYTE);
    }

    uint8_t getBitSlice(uint8_t data, uint8_t start_offset)
    {
        uint8_t mask = 0x00;
        for (auto i = 0u; i < start_offset; ++i)
        {
            mask = (mask << 1u) | 1u;
        }
        return getMaskedValue(data, mask);
    }

    bool getBit(uint8_t data, uint8_t bit_index)
    {
        return (data & (1u << (bit_index-1)));
    }

    uint16_t convertNumberOfBitsToBytes(uint16_t numOfBits)
    {
        constexpr uint8_t BITS_PER_BYTE = 8u;
        return (numOfBits + (BITS_PER_BYTE - 1)) >> 3;
    }

    std::string getCurrentBinaryDirectory(void)
    {
        char result[PATH_MAX] = {'\0'};
        size_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if(0 != count)
        {
            std::string wholePath(result);
            size_t pathEnd = wholePath.find_last_of("/");
            return wholePath.substr(0, pathEnd+1);
        }
        return std::string();
    }

}  // namespace utilities
}  // namespace common
