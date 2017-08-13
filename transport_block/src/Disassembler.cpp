#include <iostream>
#include <utility>
#include <algorithm>

#include <Tools.hpp>
#include <StatusPduUtilities.hpp>
#include <Disassembler.hpp>

#include <Logger.hpp>

namespace transport_block
{

void Disassembler::disassemble(std::vector<uint8_t>& payload)
{
    common::BufferReader reader(payload.data(), payload.size());
    disassembleHeader(reader);
    disassemblePayload(reader);
}

void Disassembler::disassembleHeader(common::BufferReader& reader)
{
    const auto extensionMask = 32;
    const auto lcidMask = 31;
    auto extensionBit = true;

    while (extensionBit)
    {
        auto byteData = reader.readUInt8();

        extensionBit = static_cast<bool>(common::utilities::getMaskedValue<uint8_t>(byteData, extensionMask));
        auto lcid = common::utilities::getMaskedValue<uint8_t>(byteData, lcidMask);

        if (isReservedElement(lcid) || ELcidDlSch::Padding == static_cast<ELcidDlSch>(lcid))
        {
            log_dbg("Decoded Reserved/Padding Header: E = %s, LCID = %#04x\n", (extensionBit ? "true" : "false"), lcid);
            continue;
        }

        if (isCtrlElement(lcid))
        {
            log_dbg("Decoded Control Element Header: E = %s, LCID = %#04x\n", (extensionBit ? "true" : "false"), lcid);
            _header.push_back({lcid, getCtrlElementDataLength(lcid)});
            continue;
        }
        else
        {
            /// MAC SDU
            auto length = 0xFFFF;
            if (extensionBit)
            {
                length = reader.readUInt16();
            }
            log_dbg("Decoded MAC SDU Header: E = %s, LCID = %#04x\n", (extensionBit ? "true" : "false"), lcid);
            _header.push_back({lcid, length});
        }
    }


    for(const auto lcidSizePair : _header)
    {
        log_dbg("lcid : %#04x, payload size : %-10u\n", lcidSizePair.first, lcidSizePair.second);
    }
}

void Disassembler::disassemblePayload(common::BufferReader& reader)
{
    for(auto lcidSizePair : _header)
    {
        auto isStatusPdu = false;
        if (0xFFFF == lcidSizePair.second)
        {
            lcidSizePair.second = reader.getBufferSize() - reader.getByteIterator();
        }
        std::vector<uint8_t> payload = {};
        for(auto i = 0u; i < lcidSizePair.second; ++i)
        {
            if (i == 0u)
            {
                auto byte = reader.readUInt8();
                if (!(byte & 0xF0))
                {
                    isStatusPdu = true;
                }
                payload.push_back(byte);
            }
            else
            {
                payload.push_back(reader.readUInt8());
            }
        }
        if (isStatusPdu)
        {
            disassembleStatusPdu(lcidSizePair.first, payload);
        }
        _payload.push_back(std::make_pair(lcidSizePair.first, payload));
    }

    for(auto lcidPayloadPair : _payload)
    {
        log_inf("%s\n", "-----------------------------------------------------");
        auto payloadString = common::utilities::vectorToHexString<uint8_t>(lcidPayloadPair.second);
        auto status = std::find_if(std::begin(_status), std::end(_status),
                [lcidPayloadPair](const auto& x){
                    return x.first == lcidPayloadPair.first;
        });
        log_inf("lcid : %#04x, payload : %s\n", lcidPayloadPair.first, payloadString.c_str());

        if (status != std::end(_status))
        {
            status_pdu::Utilities utils;
            utils.printStatusPdu(status->second);
        }
        log_inf("%s\n", "-----------------------------------------------------");
    }
}

uint8_t Disassembler::getCtrlElementDataLength(int lcid) const
{
    switch (static_cast<ELcidDlSch>(lcid))
    {
        case ELcidDlSch::UeContentionResolution:
            log_dbg("UE_CONTENTION_RESOLUTION has payload size of 6\n");
            return 6;
        case ELcidDlSch::TimingAdvancedCmd:
            log_dbg("TIMING_ADVANCE_CMD has payload size of 1\n");
            return 1;
        case ELcidDlSch::BrsBeamChangeInd:
            log_dbg("BRS_BEAM_CHANGE_IND has payload of size 2\n");
            return 2;
        case ELcidDlSch::BrrsBeamChangeInd:
            log_dbg("BRRS_BEAM_CHANGE_IND has payload of size 1\n");
            return 1;
        default:
            log_dbg("Error: LCID is not a control element. Returning 0\n");
            return 0;
    }
}

bool Disassembler::isCtrlElement(int lcid)
{
    auto id =  static_cast<ELcidDlSch>(lcid);
    if ((ELcidDlSch::UeContentionResolution == id) ||
        (ELcidDlSch::TimingAdvancedCmd == id) ||
        (ELcidDlSch::BrsBeamChangeInd == id) ||
        (ELcidDlSch::BrrsBeamChangeInd == id))
    {
        return true;
    }
    return false;
}

bool Disassembler::isReservedElement(int lcid)
{
    auto id =  static_cast<ELcidDlSch>(lcid);
    if (((ELcidDlSch::ReservedMin <= id) &&
        (ELcidDlSch::ReservedMax >= id)) ||
        (ELcidDlSch::Reserved == id))
    {
        return true;
    }
    return false;
}

void Disassembler::disassembleStatusPdu(int lcid, std::vector<uint8_t>& payload)
{
    constexpr auto HEADER_SIZE = 4u;
    status_pdu::StatusPdu statusPdu;
    status_pdu::Utilities utils;
    common::BufferReader reader(payload.data(), payload.size());

    for (auto flushCounter = 0; flushCounter < HEADER_SIZE; ++flushCounter)
    {
        reader.readBool();
    }

    utils.deserializeStatusPdu(reader, statusPdu);

    _status.push_back(std::make_pair(lcid, statusPdu));
}

} // namespace transport_block
