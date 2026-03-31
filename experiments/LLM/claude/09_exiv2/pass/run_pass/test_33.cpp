#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <type_traits>
#include <limits>
#include <cmath>

// Include the header under test
#include "exiv2/types.hpp"

// Test with integer types
TEST(ToStringHelperTest_33, IntPositive_33) {
    int value = 42;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "42");
}

TEST(ToStringHelperTest_33, IntNegative_33) {
    int value = -123;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "-123");
}

TEST(ToStringHelperTest_33, IntZero_33) {
    int value = 0;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "0");
}

TEST(ToStringHelperTest_33, IntMax_33) {
    int value = std::numeric_limits<int>::max();
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

TEST(ToStringHelperTest_33, IntMin_33) {
    int value = std::numeric_limits<int>::min();
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with unsigned integer
TEST(ToStringHelperTest_33, UnsignedInt_33) {
    unsigned int value = 999;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "999");
}

TEST(ToStringHelperTest_33, UnsignedIntMax_33) {
    unsigned int value = std::numeric_limits<unsigned int>::max();
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with long
TEST(ToStringHelperTest_33, LongValue_33) {
    long value = 1234567890L;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "1234567890");
}

// Test with long long
TEST(ToStringHelperTest_33, LongLongValue_33) {
    long long value = 9876543210LL;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with double
TEST(ToStringHelperTest_33, DoublePositive_33) {
    double value = 3.14;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

TEST(ToStringHelperTest_33, DoubleNegative_33) {
    double value = -2.718;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

TEST(ToStringHelperTest_33, DoubleZero_33) {
    double value = 0.0;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with float
TEST(ToStringHelperTest_33, FloatValue_33) {
    float value = 1.5f;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with char
TEST(ToStringHelperTest_33, CharValue_33) {
    char value = 'A';
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "A");
}

TEST(ToStringHelperTest_33, CharDigit_33) {
    char value = '0';
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "0");
}

// Test with std::string
TEST(ToStringHelperTest_33, StdString_33) {
    std::string value = "hello world";
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "hello world");
}

TEST(ToStringHelperTest_33, EmptyString_33) {
    std::string value = "";
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "");
}

// Test with const char*
TEST(ToStringHelperTest_33, CString_33) {
    const char* value = "test string";
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "test string");
}

// Test with bool
TEST(ToStringHelperTest_33, BoolTrue_33) {
    bool value = true;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

TEST(ToStringHelperTest_33, BoolFalse_33) {
    bool value = false;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with short
TEST(ToStringHelperTest_33, ShortValue_33) {
    short value = 12345;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with unsigned long long
TEST(ToStringHelperTest_33, UnsignedLongLongMax_33) {
    unsigned long long value = std::numeric_limits<unsigned long long>::max();
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test that the result is a proper std::string (not empty for non-empty inputs)
TEST(ToStringHelperTest_33, ResultIsStdString_33) {
    int value = 7;
    auto result = Exiv2::toStringHelper(value, std::false_type{});
    static_assert(std::is_same<decltype(result), std::string>::value, "Return type should be std::string");
    EXPECT_FALSE(result.empty());
}

// Test with special double values
TEST(ToStringHelperTest_33, DoubleVerySmall_33) {
    double value = 1e-10;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

TEST(ToStringHelperTest_33, DoubleVeryLarge_33) {
    double value = 1e+15;
    std::ostringstream expected;
    expected << value;
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, expected.str());
}

// Test with a custom type that has operator<<
namespace {
struct CustomType {
    int x;
    int y;
    friend std::ostream& operator<<(std::ostream& os, const CustomType& ct) {
        os << "(" << ct.x << "," << ct.y << ")";
        return os;
    }
};
}

TEST(ToStringHelperTest_33, CustomStreamableType_33) {
    CustomType value{10, 20};
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "(10,20)");
}

TEST(ToStringHelperTest_33, CustomStreamableTypeNegative_33) {
    CustomType value{-1, -2};
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "(-1,-2)");
}

// Test with string containing special characters
TEST(ToStringHelperTest_33, StringWithSpecialChars_33) {
    std::string value = "line1\nline2\ttab";
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "line1\nline2\ttab");
}

// Test with single character string
TEST(ToStringHelperTest_33, SingleCharString_33) {
    std::string value = "X";
    std::string result = Exiv2::toStringHelper(value, std::false_type{});
    EXPECT_EQ(result, "X");
}
