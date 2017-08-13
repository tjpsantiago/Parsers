#pragma once

namespace status_pdu
{
    constexpr auto AM_WINDOW_SIZE = 131072; //for 18-bit SN
    constexpr auto MAX_VALUE_MODULO = 262144;
    constexpr auto OFFSET = 1;
    constexpr auto SN_BIT_COUNT = 18;
    constexpr auto SO_BIT_COUNT = 16;
    constexpr auto SN_EXTENSION_BIT_COUNT = 1;
    constexpr auto NACK_LENGTH_BIT_COUNT = 8;
    constexpr auto PDU_HEADER_SIZE = 3;
    constexpr auto PDU_SEGMENT_HEADER_SIZE = 5;
    constexpr auto MAX_STATUS_PDU_SIZE = 0xFFFF; // arbitrary number (value may change)
}  // namespace status_pdu
