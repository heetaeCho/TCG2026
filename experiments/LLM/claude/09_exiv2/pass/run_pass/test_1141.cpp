#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Include necessary headers
#include "exiv2/types.hpp"

namespace Exiv2 {
int32_t getLong(const byte* buf, ByteOrder byteOrder);
}

using namespace Exiv2;

class GetLongTest_1141 : public ::testing::Test {
protected:
    byte buf[4];
};

// Test basic little-endian decoding
TEST_F(GetLongTest_1141, LittleEndianBasicValue_1141) {
    // Value 0x04030201 in little-endian: 01 02 03 04
    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 0x04030201);
}

// Test basic big-endian decoding
TEST_F(GetLongTest_1141, BigEndianBasicValue_1141) {
    // Value 0x01020304 in big-endian: 01 02 03 04
    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 0x01020304);
}

// Test zero value in little-endian
TEST_F(GetLongTest_1141, LittleEndianZero_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 0);
}

// Test zero value in big-endian
TEST_F(GetLongTest_1141, BigEndianZero_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 0);
}

// Test value 1 in little-endian
TEST_F(GetLongTest_1141, LittleEndianOne_1141) {
    buf[0] = 0x01;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 1);
}

// Test value 1 in big-endian
TEST_F(GetLongTest_1141, BigEndianOne_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x01;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 1);
}

// Test max positive value (0x7FFFFFFF) in little-endian
TEST_F(GetLongTest_1141, LittleEndianMaxPositive_1141) {
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0x7F;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 0x7FFFFFFF);
}

// Test max positive value (0x7FFFFFFF) in big-endian
TEST_F(GetLongTest_1141, BigEndianMaxPositive_1141) {
    buf[0] = 0x7F;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 0x7FFFFFFF);
}

// Test all 0xFF bytes in little-endian (should be -1 as int32_t)
TEST_F(GetLongTest_1141, LittleEndianAllFF_1141) {
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, -1);
}

// Test all 0xFF bytes in big-endian (should be -1 as int32_t)
TEST_F(GetLongTest_1141, BigEndianAllFF_1141) {
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, -1);
}

// Test that little-endian and big-endian produce different results for non-palindrome data
TEST_F(GetLongTest_1141, DifferentByteOrderDifferentResult_1141) {
    buf[0] = 0x01;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t le_result = getLong(buf, littleEndian);
    int32_t be_result = getLong(buf, bigEndian);
    EXPECT_NE(le_result, be_result);
    EXPECT_EQ(le_result, 1);
    EXPECT_EQ(be_result, 0x01000000);
}

// Test that same byte pattern with swapped byte order gives same result when bytes are symmetric
TEST_F(GetLongTest_1141, SymmetricBytePattern_1141) {
    buf[0] = 0xAB;
    buf[1] = 0xCD;
    buf[2] = 0xCD;
    buf[3] = 0xAB;
    int32_t le_result = getLong(buf, littleEndian);
    int32_t be_result = getLong(buf, bigEndian);
    EXPECT_EQ(le_result, be_result);
}

// Test value 256 in little-endian
TEST_F(GetLongTest_1141, LittleEndian256_1141) {
    buf[0] = 0x00;
    buf[1] = 0x01;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 256);
}

// Test value 256 in big-endian
TEST_F(GetLongTest_1141, BigEndian256_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x01;
    buf[3] = 0x00;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 256);
}

// Test value 65536 in little-endian
TEST_F(GetLongTest_1141, LittleEndian65536_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x01;
    buf[3] = 0x00;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 65536);
}

// Test value 65536 in big-endian
TEST_F(GetLongTest_1141, BigEndian65536_1141) {
    buf[0] = 0x00;
    buf[1] = 0x01;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, 65536);
}

// Test negative value -1 encoded in little-endian
TEST_F(GetLongTest_1141, LittleEndianNegativeOne_1141) {
    // -1 in two's complement = 0xFFFFFFFF
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, -1);
}

// Test minimum int32 value (0x80000000) in big-endian
TEST_F(GetLongTest_1141, BigEndianMinInt32_1141) {
    buf[0] = 0x80;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, static_cast<int32_t>(0x80000000));
}

// Test minimum int32 value (0x80000000) in little-endian
TEST_F(GetLongTest_1141, LittleEndianMinInt32_1141) {
    buf[0] = 0x00;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x80;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, static_cast<int32_t>(0x80000000));
}

// Test specific known value 0xDEADBEEF in big-endian
TEST_F(GetLongTest_1141, BigEndianDeadBeef_1141) {
    buf[0] = 0xDE;
    buf[1] = 0xAD;
    buf[2] = 0xBE;
    buf[3] = 0xEF;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, static_cast<int32_t>(0xDEADBEEF));
}

// Test specific known value 0xDEADBEEF in little-endian
TEST_F(GetLongTest_1141, LittleEndianDeadBeef_1141) {
    buf[0] = 0xEF;
    buf[1] = 0xBE;
    buf[2] = 0xAD;
    buf[3] = 0xDE;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, static_cast<int32_t>(0xDEADBEEF));
}

// Test that only the least significant byte differs
TEST_F(GetLongTest_1141, LittleEndianOnlyLSBSet_1141) {
    buf[0] = 0xAB;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, 0xAB);
}

// Test that only the most significant byte is set in big-endian
TEST_F(GetLongTest_1141, BigEndianOnlyMSBSet_1141) {
    buf[0] = 0xAB;
    buf[1] = 0x00;
    buf[2] = 0x00;
    buf[3] = 0x00;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, static_cast<int32_t>(0xAB000000));
}

// Test consistency: encoding a known value in LE, then reading it back
TEST_F(GetLongTest_1141, LittleEndianRoundTrip_1141) {
    int32_t expected = 0x12345678;
    buf[0] = 0x78;
    buf[1] = 0x56;
    buf[2] = 0x34;
    buf[3] = 0x12;
    int32_t result = getLong(buf, littleEndian);
    EXPECT_EQ(result, expected);
}

// Test consistency: encoding a known value in BE, then reading it back
TEST_F(GetLongTest_1141, BigEndianRoundTrip_1141) {
    int32_t expected = 0x12345678;
    buf[0] = 0x12;
    buf[1] = 0x34;
    buf[2] = 0x56;
    buf[3] = 0x78;
    int32_t result = getLong(buf, bigEndian);
    EXPECT_EQ(result, expected);
}
