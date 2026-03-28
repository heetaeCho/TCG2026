#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Test getValue<uint16_t> with little-endian byte order
TEST(GetValueUint16Test_138, LittleEndian_138) {
    byte buf[2] = {0x01, 0x00};
    uint16_t result = getValue<uint16_t>(buf, littleEndian);
    EXPECT_EQ(result, 1);
}

// Test getValue<uint16_t> with big-endian byte order
TEST(GetValueUint16Test_138, BigEndian_138) {
    byte buf[2] = {0x00, 0x01};
    uint16_t result = getValue<uint16_t>(buf, bigEndian);
    EXPECT_EQ(result, 1);
}

// Test getValue<uint16_t> with zero value
TEST(GetValueUint16Test_138, ZeroValue_138) {
    byte buf[2] = {0x00, 0x00};
    uint16_t resultLE = getValue<uint16_t>(buf, littleEndian);
    uint16_t resultBE = getValue<uint16_t>(buf, bigEndian);
    EXPECT_EQ(resultLE, 0);
    EXPECT_EQ(resultBE, 0);
}

// Test getValue<uint16_t> with maximum uint16 value (0xFFFF)
TEST(GetValueUint16Test_138, MaxValue_138) {
    byte buf[2] = {0xFF, 0xFF};
    uint16_t resultLE = getValue<uint16_t>(buf, littleEndian);
    uint16_t resultBE = getValue<uint16_t>(buf, bigEndian);
    EXPECT_EQ(resultLE, 0xFFFF);
    EXPECT_EQ(resultBE, 0xFFFF);
}

// Test getValue<uint16_t> with little-endian specific value 0x0102
TEST(GetValueUint16Test_138, LittleEndianSpecificValue_138) {
    // 0x0102 in little-endian: low byte first
    byte buf[2] = {0x02, 0x01};
    uint16_t result = getValue<uint16_t>(buf, littleEndian);
    EXPECT_EQ(result, 0x0102);
}

// Test getValue<uint16_t> with big-endian specific value 0x0102
TEST(GetValueUint16Test_138, BigEndianSpecificValue_138) {
    // 0x0102 in big-endian: high byte first
    byte buf[2] = {0x01, 0x02};
    uint16_t result = getValue<uint16_t>(buf, bigEndian);
    EXPECT_EQ(result, 0x0102);
}

// Test that little-endian and big-endian produce swapped results for same buffer
TEST(GetValueUint16Test_138, EndianSwap_138) {
    byte buf[2] = {0xAB, 0xCD};
    uint16_t resultLE = getValue<uint16_t>(buf, littleEndian);
    uint16_t resultBE = getValue<uint16_t>(buf, bigEndian);
    EXPECT_EQ(resultLE, 0xCDAB);
    EXPECT_EQ(resultBE, 0xABCD);
}

// Test getValue<uint16_t> with 0x8000 (boundary: highest bit set)
TEST(GetValueUint16Test_138, HighBitSet_138) {
    // Big-endian: 0x80, 0x00 => 0x8000
    byte bufBE[2] = {0x80, 0x00};
    uint16_t resultBE = getValue<uint16_t>(bufBE, bigEndian);
    EXPECT_EQ(resultBE, 0x8000);

    // Little-endian: 0x00, 0x80 => 0x8000
    byte bufLE[2] = {0x00, 0x80};
    uint16_t resultLE = getValue<uint16_t>(bufLE, littleEndian);
    EXPECT_EQ(resultLE, 0x8000);
}

// Test getValue<uint16_t> with value 255 (0x00FF)
TEST(GetValueUint16Test_138, Value255_138) {
    // Big-endian
    byte bufBE[2] = {0x00, 0xFF};
    uint16_t resultBE = getValue<uint16_t>(bufBE, bigEndian);
    EXPECT_EQ(resultBE, 0x00FF);

    // Little-endian
    byte bufLE[2] = {0xFF, 0x00};
    uint16_t resultLE = getValue<uint16_t>(bufLE, littleEndian);
    EXPECT_EQ(resultLE, 0x00FF);
}

// Test getValue<uint16_t> with value 256 (0x0100)
TEST(GetValueUint16Test_138, Value256_138) {
    // Big-endian
    byte bufBE[2] = {0x01, 0x00};
    uint16_t resultBE = getValue<uint16_t>(bufBE, bigEndian);
    EXPECT_EQ(resultBE, 0x0100);

    // Little-endian
    byte bufLE[2] = {0x00, 0x01};
    uint16_t resultLE = getValue<uint16_t>(bufLE, littleEndian);
    EXPECT_EQ(resultLE, 0x0100);
}

// Test consistency: getValue should match getUShort
TEST(GetValueUint16Test_138, ConsistencyWithGetUShort_138) {
    byte buf[2] = {0x34, 0x12};
    uint16_t fromGetValue = getValue<uint16_t>(buf, littleEndian);
    uint16_t fromGetUShort = getUShort(buf, littleEndian);
    EXPECT_EQ(fromGetValue, fromGetUShort);

    fromGetValue = getValue<uint16_t>(buf, bigEndian);
    fromGetUShort = getUShort(buf, bigEndian);
    EXPECT_EQ(fromGetValue, fromGetUShort);
}
