#pragma once

#include <type_traits>
#include <climits>
#include <cstdint>
#include <vector>

namespace common
{

class BufferReader
{
public:
    BufferReader(const uint8_t* dataBuffer, const uint32_t size);
    BufferReader(const BufferReader&) = delete;
    BufferReader& operator=(const BufferReader&) = delete;

    bool endOfBuffer() const;

    uint8_t readNext8Bits();
    uint8_t readUInt8();
    int8_t readInt8();

    uint16_t readNext16Bits();
    uint16_t readUInt16();
    int16_t readInt16();

    uint32_t readUInt32();
    int32_t readInt32();

    bool readBool();

    void readRaw(uint8_t* destination, const uint32_t size);
    std::vector<uint8_t> readRaw(const uint32_t size);
    std::vector<uint8_t> readRemainingBuffer(const uint32_t size);

    uint32_t getByteIterator() const { return mByteIter; }
    uint32_t getBufferSize() const { return mBufferSize; }

private:
    void shiftByteIterator();
    void shiftBitIterator();

    uint8_t readBitsImpl(const uint8_t numOfBits);
    uint8_t readSingleBit();

    const uint8_t* mDataBuffer;
    const uint32_t mBufferSize;

    uint32_t mByteIter;
    uint8_t mBitIter;
};

} // namespace common

