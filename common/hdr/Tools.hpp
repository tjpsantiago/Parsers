/*
 * Copyright (c) Nokia 2017. All rights reserved.
 */

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>

namespace common
{
namespace utilities
{
     /* shift data by one byte to the left.
      * Parameters:
      *     * data - value to be shifted
      * Return Value:
      *     - value of data shifted to the left by one byte.
      * Example:
      *     shiftLeftOneByte(0x10FF) // returns 0xFF00
      *     shiftLeftOneByte(0xFF0000FF) // returns 0x0000FF00 or 0xFF00 for short
      *     shiftLeftOneByte(0xF0AB1234) // returns 0xAB123400
      */
    uint32_t shiftLeftOneByte(uint32_t data);

     /* function to get value of the data from start_offset to LSB
     * Parameters :
     *      * data - one byte value to be masked
     *      * start_offset - MSB bit index of mask
     * Return Value:
     *      - value of data ANDed with the mask created
     * Example:
     *      getBitSlice(0xFF, 8) // returns 0xFF
     *      getBitSlice(0xFF, 5) // returns 0x1F
     *      getBitSlice(0xFF, 9) // returns 0xFF
     * note:
     *      1. LSB is the right-most bit and MSB is the left-most bit
     *      2. data is maximum of one byte only. (8 bits max)
     *      3. If start offset is greater than 8, function will return data parameter.
     */
    uint8_t getBitSlice(uint8_t data, uint8_t start_offset);

    /* function to check if a bit inside a one byte data is set
     * Parameters:
     *      * data - one byte data to evaluate
     *      * bit_index - bit index to check value from
     * Return Value:
     *      - true - if bit is set
     *      - false - if bit is unset
     * Examples:
     *      getBit(0xFF, 0x01) // returns true
     *      getBit(0x01, 0x02) // returns false
     *      getBit(0xF0, 0x80) // returns true
     */
    bool getBit(uint8_t data, uint8_t bit_index);


    /* function to convert given number of bits to minimum byte/s that will fit it.
     * Parameters:
     *      * numOfBits - number of bits to convert to Bytes
     * Return Value:
     *      - Minimum number of bytes that can contain the given number of bits.
     * Examples:
     *      bitsToByte(16) // returns 2
     *      bitsToByte(18) // returns 3
     *      bitsToByte(65) // returns 9
     */
    uint16_t convertNumberOfBitsToBytes(uint16_t numOfBits);

    /* function to get value of the data based from the given mask.
     * Parameters:
     *      * data - one byte value to be masked
     *      * mask - value to use as mask
     * Return Value:
     *      - value of data ANDed with mask.
     * Examples:
     *      getMaskedValue(0xFF, 0x11) // return 0x11
     *      getMaskedValue(0xEF, 0x81) // return 0x01
     *      getMaskedValue(0x88, 0x88) // return 0x10
     */
    template <typename T>
    T getMaskedValue(T data, T mask)
    {
        return (data & mask);
    }

    /* function to mask value of the data from index
     * startBitPos to numOfBits to the right
     * Parameters :
     *      * data - value to be masked
     *      * startBitPos - MSB bit index of mask
     *      * numOfBits - length of mask
     * Return Value:
     *      - value of data ANDed with the mask created
     * Example:
     *      maskBitSlice(0xEFFF, 16, 8) // returns 0xEF00
     * note:
     *      1. LSB is the right-most bit and MSB is the left-most bit
     */
    template <typename T>
    T maskBitSlice(T data, uint8_t startBitPos, uint8_t numOfBits)
    {
        T mask = ((1 << (numOfBits)) - 1) << (startBitPos - numOfBits);
        return (data & mask);
    }

    /* function to get value of the data from index
     * startBitPos to numOfBits to the right
     * Parameters :
     *      * data - one byte value to be masked
     *      * startBitPos - MSB bit index of mask
     *      * numOfBits - length of mask
     * Return Value:
     *      - value of data from startBitPos to numOfBit to the right
     * Example:
     *      getBitSlice(0xEFFF, 16, 8) // returns 0xEF
     * note:
     *      1. LSB is the right-most bit and MSB is the left-most bit
     */
    template <typename T>
    T getBitSlice(T data, uint8_t startBitPos, uint8_t numOfBits)
    {
        T mask = (1 << (numOfBits)) - 1;
        return (data >> (startBitPos - numOfBits)) & mask;
    }

    /* function to convert vector to string
     * Parameters:
     *      * buffer - vector that will be converted
     * Return Value:
     *      - string - string conversion of vector input
     */
    template <typename T>
    std::string vectorToHexString(const std::vector<T>& buffer)
    {
        std::stringstream strOut;
        strOut << std::hex << std::setfill('0') << std::uppercase;
        for(const auto& e : buffer)
        {
            strOut << std::setw(2) << static_cast<uint32_t>(e) << " ";
        }
        return strOut.str();
    }

    /* function to convert payload to string
     * Parameters:
     *      * buffer - pointer that will be converted
     *      * size - size of buffer
     * Return Value:
     *      - string - string conversion of input
     */
    template <typename T>
    std::string payloadToHexString(T* buffer, uint8_t size)
    {
        std::stringstream strOut;
        strOut << std::hex << std::setfill('0') << std::uppercase;
        for(auto i = 0; i < size; i++)
        {
            strOut << std::setw(2) << static_cast<uint32_t>(*(buffer + i)) << " ";
        }
        return strOut.str();
    }

    /* function to get binary directory
     * for a specific crnti and serving cell index.
     * Return Value:
     *      - string - path to binary.
     */
    std::string getCurrentBinaryDirectory(void);
}  // namespace utilities
}  // namespace common
