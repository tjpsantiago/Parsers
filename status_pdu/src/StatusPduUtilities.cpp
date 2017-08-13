#include <iostream>

#include <Logger.hpp>
#include <StatusPduUtilities.hpp>
#include <BufferReader.hpp>

namespace status_pdu
{

void Utilities::deserializeStatusPdu(
        common::BufferReader& reader,
        StatusPdu& statusPdu)
{
    uint16_t snByteData = reader.readNext16Bits();
    bool snBitData1 = reader.readBool();
    bool snBitData2 = reader.readBool();

    statusPdu.mAckSn = (snByteData << 2) + (snBitData1 << 1) + snBitData2;

    if (reader.readBool())
    {
        auto& nackSns = statusPdu.mNackSns;
        bool isFinished = false;

        do
        {
            uint16_t snByteData = reader.readNext16Bits();
            bool snBitData1 = reader.readBool();
            bool snBitData2 = reader.readBool();

            NackSn parsedNackPdu;
            parsedNackPdu.mNackSn = (snByteData << 2) + (snBitData1 << 1) + snBitData2;
            parsedNackPdu.mExtensionBit1 = reader.readBool();
            parsedNackPdu.mExtensionBit2 = reader.readBool();
            parsedNackPdu.mExtensionBit3 = reader.readBool();

            if (parsedNackPdu.mExtensionBit2)
            {
                parsedNackPdu.mSoStart = reader.readNext16Bits();
                parsedNackPdu.mSoEnd = reader.readNext16Bits();
            }

            if (parsedNackPdu.mExtensionBit3)
            {
                parsedNackPdu.mLength = reader.readNext8Bits();
            }

            isFinished = !parsedNackPdu.mExtensionBit1;

            nackSns.push_back(parsedNackPdu); } while (!isFinished); }
}

void Utilities::printStatusPdu(StatusPdu& statusPdu)
{
    log_inf("ACK_SN : %6u\n", statusPdu.mAckSn);

    if (!statusPdu.mNackSns.empty())
    {
        log_inf("%6s\t%6s\t%6s\t%6s\t%6s\t%6s\t%6s\n",
            "NACK SN", "E1", "E2", "E3", "SoStart", "SoEnd", "Length");

        for(auto nack : statusPdu.mNackSns)
        {
            log_inf("%6u\t%6s\t%6s\t%6s\t%6d\t%6d\t%6d\n",
                   nack.mNackSn,
                   (nack.mExtensionBit1 ? "true" : "false"),
                   (nack.mExtensionBit2 ? "true" : "false"),
                   (nack.mExtensionBit3 ? "true" : "false"),
                   static_cast<int>(nack.mSoStart),
                   static_cast<int>(nack.mSoEnd),
                   static_cast<int>(nack.mLength));
        }
    }
    else
    {
        log_inf("%s", "There are no nacked sequence numbers.\n");
    }
}

}  // namespace status_pdu

