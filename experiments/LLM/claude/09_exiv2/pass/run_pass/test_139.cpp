#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

namespace {

using namespace Exiv2;

// Test normal operation with little-endian byte order
TEST(ToDataUint16Test_139, LittleEndianNormalValue_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x1234;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x34);
    EXPECT_EQ(buf[1], 0x12);
}

// Test normal operation with big-endian byte order
TEST(ToDataUint16Test_139, BigEndianNormalValue_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x1234;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
}

// Test boundary: zero value with little-endian
TEST(ToDataUint16Test_139, ZeroValueLittleEndian_139) {
    byte buf[2] = {0xFF, 0xFF};
    uint16_t value = 0x0000;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test boundary: zero value with big-endian
TEST(ToDataUint16Test_139, ZeroValueBigEndian_139) {
    byte buf[2] = {0xFF, 0xFF};
    uint16_t value = 0x0000;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test boundary: max uint16_t value with little-endian
TEST(ToDataUint16Test_139, MaxValueLittleEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0xFFFF;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test boundary: max uint16_t value with big-endian
TEST(ToDataUint16Test_139, MaxValueBigEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0xFFFF;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with value 0x00FF little-endian
TEST(ToDataUint16Test_139, LowByteOnlyLittleEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x00FF;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x00FF big-endian
TEST(ToDataUint16Test_139, LowByteOnlyBigEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x00FF;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with value 0xFF00 little-endian
TEST(ToDataUint16Test_139, HighByteOnlyLittleEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0xFF00;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with value 0xFF00 big-endian
TEST(ToDataUint16Test_139, HighByteOnlyBigEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0xFF00;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

// Test return value is always 2 (size of uint16_t)
TEST(ToDataUint16Test_139, ReturnValueIsTwo_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0xABCD;
    EXPECT_EQ(toData(buf, value, littleEndian), 2u);
    EXPECT_EQ(toData(buf, value, bigEndian), 2u);
}

// Test value 1 with both byte orders
TEST(ToDataUint16Test_139, ValueOneLittleEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x0001;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

TEST(ToDataUint16Test_139, ValueOneBigEndian_139) {
    byte buf[2] = {0, 0};
    uint16_t value = 0x0001;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test that buffer is correctly overwritten (not just appended)
TEST(ToDataUint16Test_139, BufferOverwrite_139) {
    byte buf[2] = {0xAA, 0xBB};
    uint16_t value = 0x0102;
    toData(buf, value, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// Test consistency: write then verify both endianness produce swapped results
TEST(ToDataUint16Test_139, EndianConsistency_139) {
    byte bufLE[2] = {0, 0};
    byte bufBE[2] = {0, 0};
    uint16_t value = 0xABCD;
    
    toData(bufLE, value, littleEndian);
    toData(bufBE, value, bigEndian);
    
    // For a non-symmetric value, LE and BE should produce reversed bytes
    EXPECT_EQ(bufLE[0], bufBE[1]);
    EXPECT_EQ(bufLE[1], bufBE[0]);
}

}  // namespace
