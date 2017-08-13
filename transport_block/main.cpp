#include <iostream>
#include <cstdint>
#include <vector>

#include <Disassembler.hpp>
#include <BufferReader.hpp>

int main(int argv, char** argc)
{
    constexpr auto HEADER_SIZE = 4u;

    std::vector<uint8_t> payload;
    transport_block::Disassembler disassembler;

    for(auto i = 1; i <= argv - 1; ++i)
    {
        auto value = std::stoul(argc[i], nullptr, 16);

        payload.push_back(value);
    }

    disassembler.disassemble(payload);
}
