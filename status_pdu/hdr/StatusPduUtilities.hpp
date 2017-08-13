#pragma once

#include <vector>
#include <cstdint>

#include <NackSn.hpp>
#include <StatusPdu.hpp>
#include <Constants.hpp>

namespace common
{
class BufferReader;
}

namespace status_pdu
{

class Utilities
{
public:
    static void deserializeStatusPdu(
            common::BufferReader& reader,
            StatusPdu& statusPdu);

    static void printStatusPdu(StatusPdu& statusPdu);
};

}  // namespace status_pdu

