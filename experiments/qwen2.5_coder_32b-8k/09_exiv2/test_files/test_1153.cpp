#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



TEST(d2DataTest_1153, NormalOperation_LittleEndian_1153) {

    byte buf[8];

    double value = 123.456;

    size_t result = d2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for 123.456 in little-endian

    uint64_t expectedValue = 0x405e9a73d3f14c40;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, NormalOperation_BigEndian_1153) {

    byte buf[8];

    double value = 123.456;

    size_t result = d2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for 123.456 in big-endian

    uint64_t expectedValue = 0x405e9a73d3f14c40;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = __builtin_bswap64(expectedValue);

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, ZeroValue_LittleEndian_1153) {

    byte buf[8];

    double value = 0.0;

    size_t result = d2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for 0.0 in little-endian

    uint64_t expectedValue = 0x0000000000000000;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, ZeroValue_BigEndian_1153) {

    byte buf[8];

    double value = 0.0;

    size_t result = d2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for 0.0 in big-endian

    uint64_t expectedValue = 0x0000000000000000;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, NegativeValue_LittleEndian_1153) {

    byte buf[8];

    double value = -123.456;

    size_t result = d2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for -123.456 in little-endian

    uint64_t expectedValue = 0xc05e9a73d3f14c40;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, NegativeValue_BigEndian_1153) {

    byte buf[8];

    double value = -123.456;

    size_t result = d2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for -123.456 in big-endian

    uint64_t expectedValue = 0xc05e9a73d3f14c40;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = __builtin_bswap64(expectedValue);

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, MaxDouble_LittleEndian_1153) {

    byte buf[8];

    double value = std::numeric_limits<double>::max();

    size_t result = d2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for max double in little-endian

    uint64_t expectedValue = 0x7fefffffffffffff;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, MaxDouble_BigEndian_1153) {

    byte buf[8];

    double value = std::numeric_limits<double>::max();

    size_t result = d2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for max double in big-endian

    uint64_t expectedValue = 0x7fefffffffffffff;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = __builtin_bswap64(expectedValue);

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, MinDouble_LittleEndian_1153) {

    byte buf[8];

    double value = std::numeric_limits<double>::min();

    size_t result = d2Data(buf, value, littleEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for min double in little-endian

    uint64_t expectedValue = 0x10000000000000;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = expectedValue;

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, MinDouble_BigEndian_1153) {

    byte buf[8];

    double value = std::numeric_limits<double>::min();

    size_t result = d2Data(buf, value, bigEndian);

    EXPECT_EQ(result, 8);

    // Expected byte sequence for min double in big-endian

    uint64_t expectedValue = 0x10000000000000;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = __builtin_bswap64(expectedValue);

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}



TEST(d2DataTest_1153, InvalidByteOrder_1153) {

    byte buf[8];

    double value = 123.456;

    size_t result = d2Data(buf, value, invalidByteOrder);

    // Since invalidByteOrder is not handled in the function,

    // we expect it to behave like bigEndian as per implementation.

    EXPECT_EQ(result, 8);

    // Expected byte sequence for 123.456 in big-endian

    uint64_t expectedValue = 0x405e9a73d3f14c40;

    union { uint64_t ull_; byte b_[8]; } u;

    u.ull_ = __builtin_bswap64(expectedValue);

    EXPECT_TRUE(std::equal(u.b_, u.b_ + 8, buf));

}
