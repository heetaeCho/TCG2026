#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "exiv2/types.hpp"

// Test with integer types (arithmetic = true_type)
TEST(ToStringHelperTest_32, IntValue_32) {
    int val = 42;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "42");
}

TEST(ToStringHelperTest_32, NegativeIntValue_32) {
    int val = -100;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "-100");
}

TEST(ToStringHelperTest_32, ZeroValue_32) {
    int val = 0;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "0");
}

TEST(ToStringHelperTest_32, LongValue_32) {
    long val = 1234567890L;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "1234567890");
}

TEST(ToStringHelperTest_32, LongLongValue_32) {
    long long val = 9876543210LL;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "9876543210");
}

TEST(ToStringHelperTest_32, UnsignedIntValue_32) {
    unsigned int val = 4294967295U;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "4294967295");
}

TEST(ToStringHelperTest_32, UnsignedLongValue_32) {
    unsigned long val = 123456UL;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "123456");
}

TEST(ToStringHelperTest_32, UnsignedLongLongValue_32) {
    unsigned long long val = 18446744073709551615ULL;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "18446744073709551615");
}

TEST(ToStringHelperTest_32, FloatValue_32) {
    float val = 3.14f;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    // std::to_string for float produces a specific representation
    EXPECT_EQ(result, std::to_string(3.14f));
}

TEST(ToStringHelperTest_32, DoubleValue_32) {
    double val = 2.71828;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(2.71828));
}

TEST(ToStringHelperTest_32, LongDoubleValue_32) {
    long double val = 1.61803398875L;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(1.61803398875L));
}

TEST(ToStringHelperTest_32, NegativeFloatValue_32) {
    float val = -0.5f;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(-0.5f));
}

TEST(ToStringHelperTest_32, IntMaxValue_32) {
    int val = std::numeric_limits<int>::max();
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST(ToStringHelperTest_32, IntMinValue_32) {
    int val = std::numeric_limits<int>::min();
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

TEST(ToStringHelperTest_32, ShortValue_32) {
    short val = 32767;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(val));
}

TEST(ToStringHelperTest_32, NegativeShortValue_32) {
    short val = -32768;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(val));
}

TEST(ToStringHelperTest_32, DoubleZeroValue_32) {
    double val = 0.0;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, std::to_string(0.0));
}

TEST(ToStringHelperTest_32, OneValue_32) {
    int val = 1;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "1");
}

TEST(ToStringHelperTest_32, NegativeOneValue_32) {
    int val = -1;
    std::string result = Exiv2::toStringHelper(val, std::true_type{});
    EXPECT_EQ(result, "-1");
}
