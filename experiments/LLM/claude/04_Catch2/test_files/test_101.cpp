#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <cstring>

#include "catch2/catch_tostring.hpp"

// Tests for std::chrono::duration<Value, std::ratio<1>> (seconds) conversion
class CatchToStringDurationSeconds_101 : public ::testing::Test {};

TEST_F(CatchToStringDurationSeconds_101, ZeroSeconds_101) {
    std::chrono::duration<int, std::ratio<1>> dur(0);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_EQ(result, "0 s");
}

TEST_F(CatchToStringDurationSeconds_101, PositiveIntegerSeconds_101) {
    std::chrono::duration<int, std::ratio<1>> dur(5);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_EQ(result, "5 s");
}

TEST_F(CatchToStringDurationSeconds_101, NegativeIntegerSeconds_101) {
    std::chrono::duration<int, std::ratio<1>> dur(-3);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_EQ(result, "-3 s");
}

TEST_F(CatchToStringDurationSeconds_101, LargePositiveSeconds_101) {
    std::chrono::duration<long long, std::ratio<1>> dur(1000000);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_EQ(result, "1000000 s");
}

TEST_F(CatchToStringDurationSeconds_101, FloatingPointSeconds_101) {
    std::chrono::duration<double, std::ratio<1>> dur(3.14);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    // Should contain "3.14" and end with " s"
    EXPECT_NE(result.find("3.14"), std::string::npos);
    EXPECT_NE(result.find(" s"), std::string::npos);
}

TEST_F(CatchToStringDurationSeconds_101, OneSecond_101) {
    std::chrono::seconds dur(1);
    auto result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_EQ(result, "1 s");
}

// Tests for other duration specializations
class CatchToStringDurationOther_101 : public ::testing::Test {};

TEST_F(CatchToStringDurationOther_101, MillisecondsDuration_101) {
    std::chrono::milliseconds dur(500);
    auto result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST_F(CatchToStringDurationOther_101, MinutesDuration_101) {
    std::chrono::duration<int, std::ratio<60>> dur(2);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

TEST_F(CatchToStringDurationOther_101, HoursDuration_101) {
    std::chrono::duration<int, std::ratio<3600>> dur(1);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("h"), std::string::npos);
}

TEST_F(CatchToStringDurationOther_101, MicrosecondsDuration_101) {
    std::chrono::microseconds dur(1234);
    auto result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_NE(result.find("1234"), std::string::npos);
}

TEST_F(CatchToStringDurationOther_101, NanosecondsDuration_101) {
    std::chrono::nanoseconds dur(999);
    auto result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_NE(result.find("999"), std::string::npos);
}

// Tests for basic type StringMaker conversions
class CatchToStringBasicTypes_101 : public ::testing::Test {};

TEST_F(CatchToStringBasicTypes_101, IntConversion_101) {
    auto result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(CatchToStringBasicTypes_101, NegativeIntConversion_101) {
    auto result = Catch::StringMaker<int>::convert(-7);
    EXPECT_EQ(result, "-7");
}

TEST_F(CatchToStringBasicTypes_101, ZeroIntConversion_101) {
    auto result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(CatchToStringBasicTypes_101, BoolTrueConversion_101) {
    auto result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(CatchToStringBasicTypes_101, BoolFalseConversion_101) {
    auto result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST_F(CatchToStringBasicTypes_101, CharConversion_101) {
    auto result = Catch::StringMaker<char>::convert('A');
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(CatchToStringBasicTypes_101, FloatConversion_101) {
    auto result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(CatchToStringBasicTypes_101, DoubleConversion_101) {
    auto result = Catch::StringMaker<double>::convert(2.5);
    EXPECT_NE(result.find("2.5"), std::string::npos);
}

TEST_F(CatchToStringBasicTypes_101, LongConversion_101) {
    auto result = Catch::StringMaker<long>::convert(100L);
    EXPECT_EQ(result, "100");
}

TEST_F(CatchToStringBasicTypes_101, LongLongConversion_101) {
    auto result = Catch::StringMaker<long long>::convert(9999999999LL);
    EXPECT_EQ(result, "9999999999");
}

TEST_F(CatchToStringBasicTypes_101, UnsignedIntConversion_101) {
    auto result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(CatchToStringBasicTypes_101, UnsignedLongConversion_101) {
    auto result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST_F(CatchToStringBasicTypes_101, UnsignedLongLongConversion_101) {
    auto result = Catch::StringMaker<unsigned long long>::convert(12345678901234ULL);
    EXPECT_EQ(result, "12345678901234");
}

// Tests for string type conversions
class CatchToStringStringTypes_101 : public ::testing::Test {};

TEST_F(CatchToStringStringTypes_101, StdStringConversion_101) {
    std::string input = "hello";
    auto result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(CatchToStringStringTypes_101, EmptyStdStringConversion_101) {
    std::string input;
    auto result = Catch::StringMaker<std::string>::convert(input);
    // Should produce a valid string representation, even if empty
    EXPECT_FALSE(result.empty() && result.find("\"\"") == std::string::npos);
}

TEST_F(CatchToStringStringTypes_101, CStringConversion_101) {
    const char* input = "test";
    auto result = Catch::StringMaker<char const*>::convert(input);
    EXPECT_NE(result.find("test"), std::string::npos);
}

TEST_F(CatchToStringStringTypes_101, NullCStringConversion_101) {
    const char* input = nullptr;
    auto result = Catch::StringMaker<char const*>::convert(input);
    // Should handle null without crashing
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchToStringStringTypes_101, StringViewConversion_101) {
    std::string_view input = "view_test";
    auto result = Catch::StringMaker<std::string_view>::convert(input);
    EXPECT_NE(result.find("view_test"), std::string::npos);
}

// Tests for pointer and nullptr
class CatchToStringPointers_101 : public ::testing::Test {};

TEST_F(CatchToStringPointers_101, NullptrConversion_101) {
    auto result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

TEST_F(CatchToStringPointers_101, NonNullPointerConversion_101) {
    int x = 42;
    int* ptr = &x;
    auto result = Catch::StringMaker<int*>::convert(ptr);
    // Should contain some hex address representation
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchToStringPointers_101, NullPointerConversion_101) {
    int* ptr = nullptr;
    auto result = Catch::StringMaker<int*>::convert(ptr);
    EXPECT_FALSE(result.empty());
}

// Boundary tests for duration
class CatchToStringDurationBoundary_101 : public ::testing::Test {};

TEST_F(CatchToStringDurationBoundary_101, MaxIntSeconds_101) {
    std::chrono::duration<int, std::ratio<1>> dur(std::numeric_limits<int>::max());
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find(" s"), std::string::npos);
}

TEST_F(CatchToStringDurationBoundary_101, MinIntSeconds_101) {
    std::chrono::duration<int, std::ratio<1>> dur(std::numeric_limits<int>::min());
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find(" s"), std::string::npos);
}

TEST_F(CatchToStringDurationBoundary_101, ZeroMinutes_101) {
    std::chrono::duration<int, std::ratio<60>> dur(0);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(CatchToStringDurationBoundary_101, ZeroHours_101) {
    std::chrono::duration<int, std::ratio<3600>> dur(0);
    auto result = Catch::StringMaker<decltype(dur)>::convert(dur);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Signed char / unsigned char
class CatchToStringCharTypes_101 : public ::testing::Test {};

TEST_F(CatchToStringCharTypes_101, SignedCharConversion_101) {
    signed char val = 65; // 'A'
    auto result = Catch::StringMaker<signed char>::convert(val);
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchToStringCharTypes_101, UnsignedCharConversion_101) {
    unsigned char val = 255;
    auto result = Catch::StringMaker<unsigned char>::convert(val);
    EXPECT_FALSE(result.empty());
}

TEST_F(CatchToStringCharTypes_101, UnsignedCharZero_101) {
    unsigned char val = 0;
    auto result = Catch::StringMaker<unsigned char>::convert(val);
    EXPECT_FALSE(result.empty());
}
