#include <iostream>
#include <cstdint>
#include <vector>

#include <BufferReader.hpp>
#include <StatusPduUtilities.hpp>

int main(int argv, char** argc)
{
    constexpr auto HEADER_SIZE = 4u;

    std::vector<uint8_t> payload;
    status_pdu::StatusPdu statusPdu;
    status_pdu::Utilities utils;

    for(auto i = 1; i <= argv - 1; ++i)
    {
        auto value = std::stoul(argc[i], nullptr, 16);

        payload.push_back(value);
    }

    common::BufferReader reader(payload.data(), payload.size());
    for (auto flushCounter = 0; flushCounter < HEADER_SIZE; ++flushCounter)
    {
        reader.readBool();
    }

    utils.deserializeStatusPdu(reader, statusPdu);

    utils.printStatusPdu(statusPdu);
}
