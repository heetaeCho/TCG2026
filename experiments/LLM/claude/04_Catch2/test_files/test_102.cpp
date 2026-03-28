#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <cstring>

#include "catch2/catch_tostring.hpp"

// Test the convert function for std::chrono::duration with minutes (std::ratio<60>)

class CatchToStringMinutesDurationTest_102 : public ::testing::Test {
protected:
    // Helper to call the convert function under test
    template <typename Value>
    std::string convertMinutes(std::chrono::duration<Value, std::ratio<60>> const& duration) {
        return Catch::StringMaker<std::chrono::duration<Value, std::ratio<60>>>::convert(duration);
    }
};

// Normal operation: positive integer minutes
TEST_F(CatchToStringMinutesDurationTest_102, PositiveIntegerMinutes_102) {
    std::chrono::duration<int, std::ratio<60>> dur(5);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "5 m");
}

// Normal operation: zero minutes
TEST_F(CatchToStringMinutesDurationTest_102, ZeroMinutes_102) {
    std::chrono::duration<int, std::ratio<60>> dur(0);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "0 m");
}

// Normal operation: negative minutes
TEST_F(CatchToStringMinutesDurationTest_102, NegativeMinutes_102) {
    std::chrono::duration<int, std::ratio<60>> dur(-3);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "-3 m");
}

// Normal operation: one minute
TEST_F(CatchToStringMinutesDurationTest_102, OneMinute_102) {
    std::chrono::duration<int, std::ratio<60>> dur(1);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "1 m");
}

// Normal operation: large value
TEST_F(CatchToStringMinutesDurationTest_102, LargeMinuteValue_102) {
    std::chrono::duration<long long, std::ratio<60>> dur(1000000LL);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "1000000 m");
}

// Normal operation: negative one minute
TEST_F(CatchToStringMinutesDurationTest_102, NegativeOneMinute_102) {
    std::chrono::duration<int, std::ratio<60>> dur(-1);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "-1 m");
}

// Boundary: maximum int value
TEST_F(CatchToStringMinutesDurationTest_102, MaxIntMinutes_102) {
    std::chrono::duration<int, std::ratio<60>> dur(std::numeric_limits<int>::max());
    std::string result = convertMinutes(dur);
    std::string expected = std::to_string(std::numeric_limits<int>::max()) + " m";
    EXPECT_EQ(result, expected);
}

// Boundary: minimum int value
TEST_F(CatchToStringMinutesDurationTest_102, MinIntMinutes_102) {
    std::chrono::duration<int, std::ratio<60>> dur(std::numeric_limits<int>::min());
    std::string result = convertMinutes(dur);
    std::string expected = std::to_string(std::numeric_limits<int>::min()) + " m";
    EXPECT_EQ(result, expected);
}

// Floating point minutes
TEST_F(CatchToStringMinutesDurationTest_102, FloatingPointMinutes_102) {
    std::chrono::duration<double, std::ratio<60>> dur(2.5);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "2.5 m");
}

// Floating point zero minutes
TEST_F(CatchToStringMinutesDurationTest_102, FloatingPointZeroMinutes_102) {
    std::chrono::duration<double, std::ratio<60>> dur(0.0);
    std::string result = convertMinutes(dur);
    // Should contain "0" and " m"
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find(" m"), std::string::npos);
}

// Floating point negative minutes
TEST_F(CatchToStringMinutesDurationTest_102, FloatingPointNegativeMinutes_102) {
    std::chrono::duration<double, std::ratio<60>> dur(-1.5);
    std::string result = convertMinutes(dur);
    EXPECT_EQ(result, "-1.5 m");
}

// Verify result ends with " m" suffix
TEST_F(CatchToStringMinutesDurationTest_102, ResultEndsWithMinuteSuffix_102) {
    std::chrono::duration<int, std::ratio<60>> dur(42);
    std::string result = convertMinutes(dur);
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result.substr(result.size() - 2), " m");
}

// Using std::chrono::minutes directly
TEST_F(CatchToStringMinutesDurationTest_102, StdChronoMinutes_102) {
    std::chrono::minutes dur(10);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_EQ(result, "10 m");
}

// Test seconds duration conversion
class CatchToStringSecondsDurationTest_102 : public ::testing::Test {};

TEST_F(CatchToStringSecondsDurationTest_102, PositiveSeconds_102) {
    std::chrono::duration<int, std::ratio<1>> dur(30);
    std::string result = Catch::StringMaker<std::chrono::duration<int, std::ratio<1>>>::convert(dur);
    EXPECT_EQ(result, "30 s");
}

TEST_F(CatchToStringSecondsDurationTest_102, ZeroSeconds_102) {
    std::chrono::duration<int, std::ratio<1>> dur(0);
    std::string result = Catch::StringMaker<std::chrono::duration<int, std::ratio<1>>>::convert(dur);
    EXPECT_EQ(result, "0 s");
}

// Test hours duration conversion
class CatchToStringHoursDurationTest_102 : public ::testing::Test {};

TEST_F(CatchToStringHoursDurationTest_102, PositiveHours_102) {
    std::chrono::duration<int, std::ratio<3600>> dur(2);
    std::string result = Catch::StringMaker<std::chrono::duration<int, std::ratio<3600>>>::convert(dur);
    EXPECT_EQ(result, "2 h");
}

TEST_F(CatchToStringHoursDurationTest_102, ZeroHours_102) {
    std::chrono::duration<int, std::ratio<3600>> dur(0);
    std::string result = Catch::StringMaker<std::chrono::duration<int, std::ratio<3600>>>::convert(dur);
    EXPECT_EQ(result, "0 h");
}

// Test basic StringMaker conversions
class CatchStringMakerBasicTest_102 : public ::testing::Test {};

TEST_F(CatchStringMakerBasicTest_102, IntConversion_102) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(CatchStringMakerBasicTest_102, NegativeIntConversion_102) {
    std::string result = Catch::StringMaker<int>::convert(-7);
    EXPECT_EQ(result, "-7");
}

TEST_F(CatchStringMakerBasicTest_102, ZeroIntConversion_102) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(CatchStringMakerBasicTest_102, BoolTrueConversion_102) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(CatchStringMakerBasicTest_102, BoolFalseConversion_102) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST_F(CatchStringMakerBasicTest_102, CharConversion_102) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchStringMakerBasicTest_102, StringConversion_102) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    // String conversion typically wraps in quotes
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(CatchStringMakerBasicTest_102, FloatConversion_102) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchStringMakerBasicTest_102, DoubleConversion_102) {
    std::string result = Catch::StringMaker<double>::convert(2.718);
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchStringMakerBasicTest_102, NullptrConversion_102) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchStringMakerBasicTest_102, LongLongConversion_102) {
    std::string result = Catch::StringMaker<long long>::convert(123456789LL);
    EXPECT_EQ(result, "123456789");
}

TEST_F(CatchStringMakerBasicTest_102, UnsignedIntConversion_102) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_EQ(result, "100");
}
