#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {
    using byte = uint8_t;
    size_t s2Data(byte* buf, int16_t s, ByteOrder byteOrder);
}

class S2DataTest_1149 : public ::testing::Test {
protected:
    Exiv2::byte buf[2];
};

// Test return value is always 2 for little endian
TEST_F(S2DataTest_1149, ReturnValueIsTwo_LittleEndian_1149) {
    size_t result = Exiv2::s2Data(buf, 0x1234, Exiv2::littleEndian);
    EXPECT_EQ(result, 2u);
}

// Test return value is always 2 for big endian
TEST_F(S2DataTest_1149, ReturnValueIsTwo_BigEndian_1149) {
    size_t result = Exiv2::s2Data(buf, 0x1234, Exiv2::bigEndian);
    EXPECT_EQ(result, 2u);
}

// Test little endian byte ordering with a known value
TEST_F(S2DataTest_1149, LittleEndian_KnownValue_1149) {
    Exiv2::s2Data(buf, 0x1234, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x34);
    EXPECT_EQ(buf[1], 0x12);
}

// Test big endian byte ordering with a known value
TEST_F(S2DataTest_1149, BigEndian_KnownValue_1149) {
    Exiv2::s2Data(buf, 0x1234, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
}

// Test with zero value in little endian
TEST_F(S2DataTest_1149, LittleEndian_Zero_1149) {
    Exiv2::s2Data(buf, 0, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with zero value in big endian
TEST_F(S2DataTest_1149, BigEndian_Zero_1149) {
    Exiv2::s2Data(buf, 0, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with maximum positive int16_t value (0x7FFF) in little endian
TEST_F(S2DataTest_1149, LittleEndian_MaxPositive_1149) {
    Exiv2::s2Data(buf, 0x7FFF, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x7F);
}

// Test with maximum positive int16_t value (0x7FFF) in big endian
TEST_F(S2DataTest_1149, BigEndian_MaxPositive_1149) {
    Exiv2::s2Data(buf, 0x7FFF, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with -1 (0xFFFF) in little endian
TEST_F(S2DataTest_1149, LittleEndian_NegativeOne_1149) {
    Exiv2::s2Data(buf, -1, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with -1 (0xFFFF) in big endian
TEST_F(S2DataTest_1149, BigEndian_NegativeOne_1149) {
    Exiv2::s2Data(buf, -1, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with minimum int16_t value (-32768 = 0x8000) in little endian
TEST_F(S2DataTest_1149, LittleEndian_MinNegative_1149) {
    int16_t minVal = std::numeric_limits<int16_t>::min(); // -32768
    Exiv2::s2Data(buf, minVal, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x80);
}

// Test with minimum int16_t value (-32768 = 0x8000) in big endian
TEST_F(S2DataTest_1149, BigEndian_MinNegative_1149) {
    int16_t minVal = std::numeric_limits<int16_t>::min(); // -32768
    Exiv2::s2Data(buf, minVal, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x80);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x00FF in little endian
TEST_F(S2DataTest_1149, LittleEndian_LowByteOnly_1149) {
    Exiv2::s2Data(buf, 0x00FF, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x00FF in big endian
TEST_F(S2DataTest_1149, BigEndian_LowByteOnly_1149) {
    Exiv2::s2Data(buf, 0x00FF, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with value where high byte is set, low byte is zero (0x0100) in little endian
TEST_F(S2DataTest_1149, LittleEndian_HighByteOnly_1149) {
    Exiv2::s2Data(buf, 0x0100, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test with value where high byte is set, low byte is zero (0x0100) in big endian
TEST_F(S2DataTest_1149, BigEndian_HighByteOnly_1149) {
    Exiv2::s2Data(buf, 0x0100, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 1 in little endian
TEST_F(S2DataTest_1149, LittleEndian_One_1149) {
    Exiv2::s2Data(buf, 1, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 1 in big endian
TEST_F(S2DataTest_1149, BigEndian_One_1149) {
    Exiv2::s2Data(buf, 1, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test with negative value -256 (0xFF00) in little endian
TEST_F(S2DataTest_1149, LittleEndian_Negative256_1149) {
    Exiv2::s2Data(buf, -256, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with negative value -256 (0xFF00) in big endian
TEST_F(S2DataTest_1149, BigEndian_Negative256_1149) {
    Exiv2::s2Data(buf, -256, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x55AA in little endian (alternating bits pattern)
TEST_F(S2DataTest_1149, LittleEndian_AlternatingBits_1149) {
    Exiv2::s2Data(buf, 0x55AA, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0x55);
}

// Test with value 0x55AA in big endian (alternating bits pattern)
TEST_F(S2DataTest_1149, BigEndian_AlternatingBits_1149) {
    Exiv2::s2Data(buf, 0x55AA, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x55);
    EXPECT_EQ(buf[1], 0xAA);
}

// Verify big and little endian produce swapped bytes
TEST_F(S2DataTest_1149, ByteOrderSwapsBytes_1149) {
    Exiv2::byte bufLE[2], bufBE[2];
    int16_t val = 0x1234;
    Exiv2::s2Data(bufLE, val, Exiv2::littleEndian);
    Exiv2::s2Data(bufBE, val, Exiv2::bigEndian);
    EXPECT_EQ(bufLE[0], bufBE[1]);
    EXPECT_EQ(bufLE[1], bufBE[0]);
}
