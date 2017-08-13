#pragma once

#include <map>
#include <cstdint>

#include <StatusPdu.hpp>
#include <ELcidDlSch.hpp>
#include <BufferReader.hpp>

namespace transport_block
{
using LcidSizePair = std::pair<int, int>;
using LcidPayloadPair = std::pair<int, std::vector<uint8_t>>;
using LcidStatusPduPair = std::pair<int, status_pdu::StatusPdu>;

class Disassembler
{
public:
    Disassembler() = default;
    virtual ~Disassembler() = default;

    void disassemble(std::vector<uint8_t>& payload);
    void disassembleHeader(common::BufferReader& reader);
    void disassemblePayload(common::BufferReader& reader);

private:
    bool isCtrlElement(int lcid);
    bool isReservedElement(int lcid);
    uint8_t getCtrlElementDataLength(int lcid) const;
    void disassembleStatusPdu(int lcid, std::vector<uint8_t>& payload);

    std::vector<LcidSizePair> _header;

    std::vector<LcidPayloadPair> _payload;

    std::vector<LcidStatusPduPair> _status;
};

} // namespace transport_block
