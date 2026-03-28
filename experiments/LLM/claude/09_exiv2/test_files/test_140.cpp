#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

namespace {

using namespace Exiv2;

// Test normal operation with little-endian byte order
TEST(ToDataUint32Test_140, LittleEndianNormalValue_140) {
    byte buf[4] = {0};
    uint32_t value = 0x12345678;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x78);
    EXPECT_EQ(buf[1], 0x56);
    EXPECT_EQ(buf[2], 0x34);
    EXPECT_EQ(buf[3], 0x12);
}

// Test normal operation with big-endian byte order
TEST(ToDataUint32Test_140, BigEndianNormalValue_140) {
    byte buf[4] = {0};
    uint32_t value = 0x12345678;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
    EXPECT_EQ(buf[2], 0x56);
    EXPECT_EQ(buf[3], 0x78);
}

// Test boundary: zero value
TEST(ToDataUint32Test_140, ZeroValue_140) {
    byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint32_t value = 0;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test boundary: maximum uint32_t value
TEST(ToDataUint32Test_140, MaxUint32Value_140) {
    byte buf[4] = {0};
    uint32_t value = 0xFFFFFFFF;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test boundary: maximum uint32_t value with little endian
TEST(ToDataUint32Test_140, MaxUint32LittleEndian_140) {
    byte buf[4] = {0};
    uint32_t value = 0xFFFFFFFF;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test value with only the least significant byte set
TEST(ToDataUint32Test_140, OnlyLSBSet_140) {
    byte buf[4] = {0};
    uint32_t value = 0x000000AB;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0xAB);
}

// Test value with only the most significant byte set
TEST(ToDataUint32Test_140, OnlyMSBSet_140) {
    byte buf[4] = {0};
    uint32_t value = 0xAB000000;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xAB);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value with only the most significant byte set, little endian
TEST(ToDataUint32Test_140, OnlyMSBSetLittleEndian_140) {
    byte buf[4] = {0};
    uint32_t value = 0xAB000000;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0xAB);
}

// Test that the return value is always 4 (size of uint32_t)
TEST(ToDataUint32Test_140, ReturnValueIsFour_140) {
    byte buf[4] = {0};
    EXPECT_EQ(toData(buf, static_cast<uint32_t>(0), littleEndian), 4u);
    EXPECT_EQ(toData(buf, static_cast<uint32_t>(1), bigEndian), 4u);
    EXPECT_EQ(toData(buf, static_cast<uint32_t>(0xFFFFFFFF), littleEndian), 4u);
}

// Test value of 1 in little endian
TEST(ToDataUint32Test_140, ValueOneLittleEndian_140) {
    byte buf[4] = {0};
    uint32_t value = 1;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test value of 1 in big endian
TEST(ToDataUint32Test_140, ValueOneBigEndian_140) {
    byte buf[4] = {0};
    uint32_t value = 1;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x01);
}

// Test zero value big endian
TEST(ToDataUint32Test_140, ZeroValueBigEndian_140) {
    byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint32_t value = 0;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test a distinctive pattern to verify byte ordering
TEST(ToDataUint32Test_140, DistinctBytePattern_140) {
    byte buf[4] = {0};
    uint32_t value = 0x01020304;
    
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
    
    result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x04);
    EXPECT_EQ(buf[1], 0x03);
    EXPECT_EQ(buf[2], 0x02);
    EXPECT_EQ(buf[3], 0x01);
}

// Test that buffer content doesn't affect surrounding memory
TEST(ToDataUint32Test_140, DoesNotOverflowBuffer_140) {
    byte buf[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    uint32_t value = 0x12345678;
    size_t result = toData(buf + 1, value, bigEndian);
    EXPECT_EQ(result, 4u);
    // Check sentinel bytes are untouched
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[5], 0xAA);
    // Check written data
    EXPECT_EQ(buf[1], 0x12);
    EXPECT_EQ(buf[2], 0x34);
    EXPECT_EQ(buf[3], 0x56);
    EXPECT_EQ(buf[4], 0x78);
}

} // namespace
