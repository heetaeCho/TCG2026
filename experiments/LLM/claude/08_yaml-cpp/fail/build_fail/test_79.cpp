#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <locale>

// Since we only have the partial interface, we need to include the actual header
// or replicate the minimal structure needed for testing.
// Based on the provided code, streamable_to_string::impl converts a key to string
// using stringstream with classic locale.

// Attempt to include the actual header
#include "yaml-cpp/traits.h"

// If the above include doesn't work directly, we define the struct based on the interface
// provided. However, per constraints, we treat implementation as black box.

namespace {

// Test with integer types
TEST(StreamableToStringTest_79, IntegerToString_79) {
    int key = 42;
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    EXPECT_EQ(result, "42");
}

TEST(StreamableToStringTest_79, NegativeIntegerToString_79) {
    int key = -100;
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    EXPECT_EQ(result, "-100");
}

TEST(StreamableToStringTest_79, ZeroToString_79) {
    int key = 0;
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    EXPECT_EQ(result, "0");
}

// Test with double/float types
TEST(StreamableToStringTest_79, DoubleToString_79) {
    double key = 3.14;
    std::string result = YAML::streamable_to_string<double, true>::impl(key);
    // Using classic locale, decimal separator should be '.'
    EXPECT_NE(result.find('.'), std::string::npos);
    // Verify it parses back correctly
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, 3.14);
}

TEST(StreamableToStringTest_79, FloatToString_79) {
    float key = 2.5f;
    std::string result = YAML::streamable_to_string<float, true>::impl(key);
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 2.5f);
}

// Test with string type
TEST(StreamableToStringTest_79, StringToString_79) {
    std::string key = "hello";
    std::string result = YAML::streamable_to_string<std::string, true>::impl(key);
    EXPECT_EQ(result, "hello");
}

TEST(StreamableToStringTest_79, EmptyStringToString_79) {
    std::string key = "";
    std::string result = YAML::streamable_to_string<std::string, true>::impl(key);
    EXPECT_EQ(result, "");
}

// Test with char type
TEST(StreamableToStringTest_79, CharToString_79) {
    char key = 'A';
    std::string result = YAML::streamable_to_string<char, true>::impl(key);
    EXPECT_EQ(result, "A");
}

// Test with unsigned int
TEST(StreamableToStringTest_79, UnsignedIntToString_79) {
    unsigned int key = 12345;
    std::string result = YAML::streamable_to_string<unsigned int, true>::impl(key);
    EXPECT_EQ(result, "12345");
}

// Test with long type
TEST(StreamableToStringTest_79, LongToString_79) {
    long key = 9999999L;
    std::string result = YAML::streamable_to_string<long, true>::impl(key);
    EXPECT_EQ(result, "9999999");
}

// Test boundary: max int
TEST(StreamableToStringTest_79, MaxIntToString_79) {
    int key = std::numeric_limits<int>::max();
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    std::stringstream expected;
    expected.imbue(std::locale::classic());
    expected << std::numeric_limits<int>::max();
    EXPECT_EQ(result, expected.str());
}

// Test boundary: min int
TEST(StreamableToStringTest_79, MinIntToString_79) {
    int key = std::numeric_limits<int>::min();
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    std::stringstream expected;
    expected.imbue(std::locale::classic());
    expected << std::numeric_limits<int>::min();
    EXPECT_EQ(result, expected.str());
}

// Test that classic locale is used (no thousands separator for large numbers)
TEST(StreamableToStringTest_79, ClassicLocaleNoThousandsSeparator_79) {
    int key = 1000000;
    std::string result = YAML::streamable_to_string<int, true>::impl(key);
    EXPECT_EQ(result, "1000000");
    // Ensure no commas or other separators
    EXPECT_EQ(result.find(','), std::string::npos);
    EXPECT_EQ(result.find(' '), std::string::npos);
}

// Test with bool type
TEST(StreamableToStringTest_79, BoolTrueToString_79) {
    bool key = true;
    std::string result = YAML::streamable_to_string<bool, true>::impl(key);
    EXPECT_EQ(result, "1");
}

TEST(StreamableToStringTest_79, BoolFalseToString_79) {
    bool key = false;
    std::string result = YAML::streamable_to_string<bool, true>::impl(key);
    EXPECT_EQ(result, "0");
}

// Test with negative double
TEST(StreamableToStringTest_79, NegativeDoubleToString_79) {
    double key = -0.001;
    std::string result = YAML::streamable_to_string<double, true>::impl(key);
    double parsed = std::stod(result);
    EXPECT_DOUBLE_EQ(parsed, -0.001);
}

// Test with long long
TEST(StreamableToStringTest_79, LongLongToString_79) {
    long long key = 123456789012345LL;
    std::string result = YAML::streamable_to_string<long long, true>::impl(key);
    EXPECT_EQ(result, "123456789012345");
}

}  // namespace
