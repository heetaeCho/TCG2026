#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Test normal operation with little-endian byte order
TEST(ToDataInt16Test_142, LittleEndianPositiveValue_142) {
    byte buf[2] = {0, 0};
    int16_t value = 0x0102;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x02);
    EXPECT_EQ(buf[1], 0x01);
}

// Test normal operation with big-endian byte order
TEST(ToDataInt16Test_142, BigEndianPositiveValue_142) {
    byte buf[2] = {0, 0};
    int16_t value = 0x0102;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// Test with zero value
TEST(ToDataInt16Test_142, ZeroValue_142) {
    byte buf[2] = {0xFF, 0xFF};
    int16_t value = 0;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with zero value big endian
TEST(ToDataInt16Test_142, ZeroValueBigEndian_142) {
    byte buf[2] = {0xFF, 0xFF};
    int16_t value = 0;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with negative value little endian
TEST(ToDataInt16Test_142, NegativeValueLittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -1; // 0xFFFF in two's complement
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with negative value big endian
TEST(ToDataInt16Test_142, NegativeValueBigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -1;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with max int16_t value little endian
TEST(ToDataInt16Test_142, MaxValueLittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 32767; // 0x7FFF
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x7F);
}

// Test with max int16_t value big endian
TEST(ToDataInt16Test_142, MaxValueBigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 32767; // 0x7FFF
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with min int16_t value little endian
TEST(ToDataInt16Test_142, MinValueLittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -32768; // 0x8000
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x80);
}

// Test with min int16_t value big endian
TEST(ToDataInt16Test_142, MinValueBigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -32768; // 0x8000
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x80);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x00FF little endian
TEST(ToDataInt16Test_142, Value0x00FFLittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 0x00FF; // 255
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 0x00FF big endian
TEST(ToDataInt16Test_142, Value0x00FFBigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 0x00FF; // 255
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test return value is always 2
TEST(ToDataInt16Test_142, ReturnValueIsAlwaysTwo_142) {
    byte buf[2];
    int16_t value = 42;
    EXPECT_EQ(toData(buf, value, littleEndian), 2u);
    EXPECT_EQ(toData(buf, value, bigEndian), 2u);
}

// Test with value 1 little endian
TEST(ToDataInt16Test_142, Value1LittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 1;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 1 big endian
TEST(ToDataInt16Test_142, Value1BigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 1;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test with value 256 (0x0100) little endian
TEST(ToDataInt16Test_142, Value256LittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 256; // 0x0100
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test with value 256 (0x0100) big endian
TEST(ToDataInt16Test_142, Value256BigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = 256; // 0x0100
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test that buffer content is fully overwritten
TEST(ToDataInt16Test_142, BufferOverwritten_142) {
    byte buf[2] = {0xAA, 0xBB};
    int16_t value = 0x0304;
    toData(buf, value, bigEndian);
    EXPECT_EQ(buf[0], 0x03);
    EXPECT_EQ(buf[1], 0x04);
}

// Test negative value -256 (0xFF00) little endian
TEST(ToDataInt16Test_142, NegValue256LittleEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -256; // 0xFF00
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test negative value -256 (0xFF00) big endian
TEST(ToDataInt16Test_142, NegValue256BigEndian_142) {
    byte buf[2] = {0, 0};
    int16_t value = -256; // 0xFF00
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}
