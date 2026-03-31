#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <cstring>

#include "catch2/catch_tostring.hpp"

// ============================================================
// Tests for chrono duration conversions
// ============================================================

TEST(StringMakerChronoDuration_100, NanosecondsConversion_100) {
    auto dur = std::chrono::nanoseconds(42);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("ns"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, MicrosecondsConversion_100) {
    auto dur = std::chrono::microseconds(100);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, MillisecondsConversion_100) {
    auto dur = std::chrono::milliseconds(500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_NE(result.find("500"), std::string::npos);
    EXPECT_NE(result.find("ms"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, SecondsConversion_100) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("s"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, MinutesConversion_100) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, HoursConversion_100) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("h"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, ZeroDuration_100) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, NegativeDuration_100) {
    auto dur = std::chrono::milliseconds(-250);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_NE(result.find("-250"), std::string::npos);
}

TEST(StringMakerChronoDuration_100, LargeDuration_100) {
    auto dur = std::chrono::nanoseconds(999999999LL);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_NE(result.find("999999999"), std::string::npos);
}

// ============================================================
// Tests for basic type StringMaker conversions
// ============================================================

TEST(StringMakerBasicTypes_100, IntConversion_100) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_100, IntZeroConversion_100) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerBasicTypes_100, IntNegativeConversion_100) {
    std::string result = Catch::StringMaker<int>::convert(-123);
    EXPECT_EQ(result, "-123");
}

TEST(StringMakerBasicTypes_100, LongConversion_100) {
    std::string result = Catch::StringMaker<long>::convert(1234567L);
    EXPECT_EQ(result, "1234567");
}

TEST(StringMakerBasicTypes_100, LongLongConversion_100) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST(StringMakerBasicTypes_100, UnsignedIntConversion_100) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_100, UnsignedLongConversion_100) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerBasicTypes_100, UnsignedLongLongConversion_100) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(18446744073709551615ULL);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBasicTypes_100, FloatConversion_100) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // The result should contain some representation of 3.14
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerBasicTypes_100, DoubleConversion_100) {
    std::string result = Catch::StringMaker<double>::convert(2.718281828);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBasicTypes_100, BoolTrueConversion_100) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBasicTypes_100, BoolFalseConversion_100) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST(StringMakerBasicTypes_100, CharConversion_100) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST(StringMakerBasicTypes_100, SignedCharConversion_100) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBasicTypes_100, UnsignedCharConversion_100) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for string-type StringMaker conversions
// ============================================================

TEST(StringMakerStringTypes_100, StdStringConversion_100) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST(StringMakerStringTypes_100, EmptyStdStringConversion_100) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty()); // Likely wrapped in quotes
}

TEST(StringMakerStringTypes_100, StringViewConversion_100) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST(StringMakerStringTypes_100, CharConstPtrConversion_100) {
    const char* str = "c-string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("c-string"), std::string::npos);
}

TEST(StringMakerStringTypes_100, CharPtrConversion_100) {
    char buf[] = "mutable";
    char* str = buf;
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

TEST(StringMakerStringTypes_100, NullCharPtrConversion_100) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for pointer/nullptr StringMaker conversions
// ============================================================

TEST(StringMakerPointerTypes_100, NullptrConversion_100) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    // Typically "nullptr" or "NULL"
    EXPECT_NE(result.find("null"), std::string::npos);
}

TEST(StringMakerPointerTypes_100, IntPointerConversion_100) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
    // Should contain hex address representation
}

TEST(StringMakerPointerTypes_100, NullIntPointerConversion_100) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for std::byte
// ============================================================

TEST(StringMakerByte_100, ByteConversion_100) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerByte_100, ByteZeroConversion_100) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for wstring types
// ============================================================

TEST(StringMakerWideStringTypes_100, WstringConversion_100) {
    std::wstring ws = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerWideStringTypes_100, WstringViewConversion_100) {
    std::wstring_view wsv = L"wide view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerWideStringTypes_100, WcharConstPtrConversion_100) {
    const wchar_t* ws = L"wchar_ptr";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerWideStringTypes_100, WcharMutablePtrConversion_100) {
    wchar_t buf[] = L"mutable_wide";
    wchar_t* ws = buf;
    std::string result = Catch::StringMaker<wchar_t*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary tests for chrono
// ============================================================

TEST(StringMakerChronoBoundary_100, MaxNanoseconds_100) {
    auto dur = std::chrono::nanoseconds(std::chrono::nanoseconds::max());
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChronoBoundary_100, MinNanoseconds_100) {
    auto dur = std::chrono::nanoseconds(std::chrono::nanoseconds::min());
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChronoBoundary_100, OneNanosecond_100) {
    auto dur = std::chrono::nanoseconds(1);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_NE(result.find("1"), std::string::npos);
}

// ============================================================
// Tests for time_point conversions
// ============================================================

TEST(StringMakerTimePoint_100, SystemClockNow_100) {
    auto tp = std::chrono::system_clock::now();
    std::string result = Catch::StringMaker<std::chrono::system_clock::time_point>::convert(tp);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTimePoint_100, SystemClockEpoch_100) {
    std::chrono::system_clock::time_point epoch{};
    std::string result = Catch::StringMaker<std::chrono::system_clock::time_point>::convert(epoch);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTimePoint_100, SteadyClockNow_100) {
    auto tp = std::chrono::steady_clock::now();
    std::string result = Catch::StringMaker<std::chrono::steady_clock::time_point>::convert(tp);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for floating-point edge cases
// ============================================================

TEST(StringMakerFloatEdgeCases_100, FloatZero_100) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerFloatEdgeCases_100, DoubleZero_100) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerFloatEdgeCases_100, NegativeFloat_100) {
    std::string result = Catch::StringMaker<float>::convert(-1.5f);
    EXPECT_NE(result.find("-"), std::string::npos);
}

TEST(StringMakerFloatEdgeCases_100, NegativeDouble_100) {
    std::string result = Catch::StringMaker<double>::convert(-99.99);
    EXPECT_NE(result.find("-"), std::string::npos);
}

// ============================================================
// Tests for integer boundary values
// ============================================================

TEST(StringMakerIntBoundary_100, IntMax_100) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerIntBoundary_100, IntMin_100) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}

TEST(StringMakerIntBoundary_100, UnsignedIntMax_100) {
    std::string result = Catch::StringMaker<unsigned int>::convert(std::numeric_limits<unsigned int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerIntBoundary_100, UnsignedIntZero_100) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}
