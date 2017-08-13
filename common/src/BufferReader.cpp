#include <BufferReader.hpp>

#include <algorithm>

namespace common
{

BufferReader::BufferReader(const uint8_t *dataBuffer, const uint32_t size)
    : mDataBuffer(dataBuffer)
    , mBufferSize(size)
    , mByteIter(0)
    , mBitIter(0)
{
}

bool BufferReader::endOfBuffer() const
{
    return mBufferSize <= mByteIter;
}

uint8_t BufferReader::readNext8Bits()
{
    if (mByteIter >= mBufferSize)
    {
        return 0;
    }

    uint8_t value;
    if (mBitIter != 0)
    {
        const uint8_t currentBitIt = mBitIter;
        uint8_t currentByteValue = (readUInt8() << currentBitIt);
        uint8_t nextByteValue = (mDataBuffer[mByteIter] >> (CHAR_BIT - currentBitIt));
        value = currentByteValue + nextByteValue;
        mBitIter = currentBitIt;
    }
    else
    {
        value = mDataBuffer[mByteIter];
        shiftByteIterator();
    }
    return value;
}

uint8_t BufferReader::readUInt8()
{
    if (mByteIter >= mBufferSize)
    {
        return 0;
    }

    uint8_t value = mDataBuffer[mByteIter];
    shiftByteIterator();
    return value;
}

int8_t BufferReader::readInt8()
{
    return static_cast<int8_t>(readUInt8());
}

uint16_t BufferReader::readNext16Bits()
{
    const uint16_t firstByte = readNext8Bits();
    const uint16_t secondByte = readNext8Bits();

    uint16_t value = 0;
    value |= firstByte << 8;
    value |= secondByte;

    return value;
}

uint16_t BufferReader::readUInt16()
{
    const uint16_t firstByte = readUInt8();
    const uint16_t secondByte = readUInt8();

    uint16_t value = 0;
    value |= firstByte << 8;
    value |= secondByte;

    return value;
}

int16_t BufferReader::readInt16()
{
    return static_cast<int16_t>(readUInt16());
}

uint32_t BufferReader::readUInt32()
{
    uint8_t numOfBytes = 4;
    uint8_t readBytes[numOfBytes];
    for(auto i = 0; i < numOfBytes; ++i)
    {
        readBytes[i] = readUInt8();
    }

    uint32_t value = 0;
    for(auto i = 0; i < numOfBytes; ++i)
    {
        value |= readBytes[i] << (8* (numOfBytes - i -1));
    }

    return value;
}

int32_t BufferReader::readInt32()
{
    return static_cast<int32_t>(readUInt32());
}

bool BufferReader::readBool()
{
    const bool result = (readSingleBit() == 1);
    return result;
}

uint8_t BufferReader::readSingleBit()
{
    if (mByteIter >= mBufferSize)
    {
        return 0;
    }

    const uint8_t currentByte = mDataBuffer[mByteIter];
    const uint8_t shift = ((CHAR_BIT - 1) - mBitIter);
    const uint8_t mask = (1 << shift);
    const uint8_t result = (currentByte & mask) == mask ? 1 : 0;

    shiftBitIterator();
    return result;
}

void BufferReader::readRaw(uint8_t *destination, const uint32_t size)
{
    if ((mByteIter + size) > mBufferSize)
    {
        return;
    }

    for (auto i = 0u; i < size; ++i)
    {
        destination[i] = readUInt8();
    }
}

std::vector<uint8_t> BufferReader::readRaw(const uint32_t size)
{
    std::vector<uint8_t> tmpRawData;

    if ((mByteIter + size) > mBufferSize)
    {
        return tmpRawData;
    }

    for (auto i = 0u; i < size; ++i)
    {
        tmpRawData.push_back(readUInt8());
    }
    return tmpRawData;
}

std::vector<uint8_t> BufferReader::readRemainingBuffer(const uint32_t size)
{
    std::vector<uint8_t> tmpRawData;
    uint32_t sizeToRead = size;

    if ((mByteIter + size) > mBufferSize)
    {
        sizeToRead = mBufferSize - mByteIter;
    }

    for (auto i = 0u; i < sizeToRead; ++i)
    {
        tmpRawData.push_back(readUInt8());
    }
    return tmpRawData;
}

void BufferReader::shiftBitIterator()
{
    ++mBitIter;
    if (mBitIter == CHAR_BIT)
    {
        mBitIter = 0;
        shiftByteIterator();
    }
}

void BufferReader::shiftByteIterator()
{
    if (mByteIter < mBufferSize)
    {
        ++mByteIter;
        mBitIter = 0;
    }
}

} // namespace common
