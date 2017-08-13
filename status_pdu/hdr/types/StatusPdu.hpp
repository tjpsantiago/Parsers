#pragma once

#include <vector>
#include <NackSn.hpp>

namespace status_pdu
{

struct StatusPdu
{
    uint32_t mAckSn = 0u;
    std::vector<NackSn> mNackSns;
};

}  // namespace status_pdu
