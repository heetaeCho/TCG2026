#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Test normal operation with big endian byte order
TEST(ToDataInt32Test_143, BigEndianPositiveValue_143) {
    byte buf[4] = {0};
    int32_t value = 0x01020304;
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test normal operation with little endian byte order
TEST(ToDataInt32Test_143, LittleEndianPositiveValue_143) {
    byte buf[4] = {0};
    int32_t value = 0x01020304;
    size_t result = toData(buf, value, littleEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x04);
    EXPECT_EQ(buf[1], 0x03);
    EXPECT_EQ(buf[2], 0x02);
    EXPECT_EQ(buf[3], 0x01);
}

// Test with zero value
TEST(ToDataInt32Test_143, ZeroValue_143) {
    byte buf[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    int32_t value = 0;
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test with negative value big endian
TEST(ToDataInt32Test_143, BigEndianNegativeValue_143) {
    byte buf[4] = {0};
    int32_t value = -1; // 0xFFFFFFFF
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test with negative value little endian
TEST(ToDataInt32Test_143, LittleEndianNegativeValue_143) {
    byte buf[4] = {0};
    int32_t value = -1; // 0xFFFFFFFF
    size_t result = toData(buf, value, littleEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test with INT32_MAX
TEST(ToDataInt32Test_143, MaxInt32BigEndian_143) {
    byte buf[4] = {0};
    int32_t value = INT32_MAX; // 0x7FFFFFFF
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test with INT32_MAX little endian
TEST(ToDataInt32Test_143, MaxInt32LittleEndian_143) {
    byte buf[4] = {0};
    int32_t value = INT32_MAX; // 0x7FFFFFFF
    size_t result = toData(buf, value, littleEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x7F);
}

// Test with INT32_MIN
TEST(ToDataInt32Test_143, MinInt32BigEndian_143) {
    byte buf[4] = {0};
    int32_t value = INT32_MIN; // 0x80000000
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x80);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test with INT32_MIN little endian
TEST(ToDataInt32Test_143, MinInt32LittleEndian_143) {
    byte buf[4] = {0};
    int32_t value = INT32_MIN; // 0x80000000
    size_t result = toData(buf, value, littleEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x80);
}

// Test return value is always 4 bytes for int32_t
TEST(ToDataInt32Test_143, ReturnValueIsFourBytes_143) {
    byte buf[4] = {0};
    int32_t value = 42;
    
    size_t resultBE = toData(buf, value, bigEndian);
    EXPECT_EQ(resultBE, 4u);
    
    size_t resultLE = toData(buf, value, littleEndian);
    EXPECT_EQ(resultLE, 4u);
}

// Test with value 1 big endian
TEST(ToDataInt32Test_143, ValueOneBigEndian_143) {
    byte buf[4] = {0};
    int32_t value = 1;
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x01);
}

// Test with value 1 little endian
TEST(ToDataInt32Test_143, ValueOneLittleEndian_143) {
    byte buf[4] = {0};
    int32_t value = 1;
    size_t result = toData(buf, value, littleEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}

// Test with value 256 to check byte boundaries
TEST(ToDataInt32Test_143, Value256BigEndian_143) {
    byte buf[4] = {0};
    int32_t value = 256; // 0x00000100
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x01);
    EXPECT_EQ(buf[3], 0x00);
}

// Test with value -2
TEST(ToDataInt32Test_143, NegativeTwoBigEndian_143) {
    byte buf[4] = {0};
    int32_t value = -2; // 0xFFFFFFFE
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFE);
}

// Test that buffer is correctly overwritten
TEST(ToDataInt32Test_143, BufferOverwritten_143) {
    byte buf[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    int32_t value = 0;
    size_t result = toData(buf, value, bigEndian);
    
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
}
