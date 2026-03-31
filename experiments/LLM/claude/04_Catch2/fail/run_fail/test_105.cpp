#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <ctime>
#include <regex>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Helper to create a time_point from a known date
static std::chrono::system_clock::time_point makeTimePoint(int year, int month, int day, int hour, int min, int sec) {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    tm.tm_isdst = 0;
    
    // Use timegm on POSIX or _mkgmtime on MSVC to interpret as UTC
#ifdef _MSC_VER
    std::time_t t = _mkgmtime(&tm);
#else
    std::time_t t = timegm(&tm);
#endif
    return std::chrono::system_clock::from_time_t(t);
}

// ============================================================
// Tests for StringMaker<std::chrono::time_point<system_clock>>
// ============================================================

class StringMakerTimePointTest_105 : public ::testing::Test {};

// Test: A known epoch time (Unix epoch) should produce the correct ISO 8601 string
TEST_F(StringMakerTimePointTest_105, UnixEpochProducesCorrectString_105) {
    auto epoch = std::chrono::system_clock::from_time_t(0);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(epoch);
    EXPECT_EQ(result, "1970-01-01T00:00:00Z");
}

// Test: A specific known date/time should produce the correct ISO 8601 string
TEST_F(StringMakerTimePointTest_105, KnownDateProducesCorrectString_105) {
    auto tp = makeTimePoint(2017, 1, 16, 17, 6, 45);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "2017-01-16T17:06:45Z");
}

// Test: Another known date
TEST_F(StringMakerTimePointTest_105, AnotherKnownDate_105) {
    auto tp = makeTimePoint(2000, 12, 31, 23, 59, 59);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "2000-12-31T23:59:59Z");
}

// Test: Result string has the correct length (20 characters for "YYYY-MM-DDTHH:MM:SSZ")
TEST_F(StringMakerTimePointTest_105, ResultHasCorrectLength_105) {
    auto tp = makeTimePoint(2023, 6, 15, 12, 30, 0);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result.size(), 20u);
}

// Test: Result string matches ISO 8601 format pattern
TEST_F(StringMakerTimePointTest_105, ResultMatchesISO8601Pattern_105) {
    auto tp = makeTimePoint(2023, 6, 15, 12, 30, 0);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    std::regex pattern(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z)");
    EXPECT_TRUE(std::regex_match(result, pattern)) << "Result was: " << result;
}

// Test: Midnight boundary
TEST_F(StringMakerTimePointTest_105, MidnightBoundary_105) {
    auto tp = makeTimePoint(2023, 1, 1, 0, 0, 0);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "2023-01-01T00:00:00Z");
}

// Test: End of day boundary (23:59:59)
TEST_F(StringMakerTimePointTest_105, EndOfDayBoundary_105) {
    auto tp = makeTimePoint(2023, 12, 31, 23, 59, 59);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "2023-12-31T23:59:59Z");
}

// Test: String ends with 'Z' (UTC marker)
TEST_F(StringMakerTimePointTest_105, StringEndsWithZ_105) {
    auto tp = makeTimePoint(2020, 3, 14, 9, 26, 53);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result.back(), 'Z');
}

// Test: Time point with sub-second precision (milliseconds) should still format correctly (seconds only)
TEST_F(StringMakerTimePointTest_105, SubSecondPrecisionTruncated_105) {
    auto tp = makeTimePoint(2023, 6, 15, 12, 30, 45);
    // Add 500 milliseconds
    auto tp_ms = tp + std::chrono::milliseconds(500);
    std::string result = Catch::StringMaker<
        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>
    >::convert(
        std::chrono::time_point_cast<std::chrono::milliseconds>(tp_ms)
    );
    // The seconds should still be 45 since to_time_t truncates sub-seconds
    EXPECT_EQ(result.size(), 20u);
    // Should match the ISO format
    std::regex pattern(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z)");
    EXPECT_TRUE(std::regex_match(result, pattern)) << "Result was: " << result;
}

// Test: Year 2038 (important for 32-bit time_t systems, but should work on 64-bit)
TEST_F(StringMakerTimePointTest_105, Year2038_105) {
    auto tp = makeTimePoint(2038, 1, 19, 3, 14, 7);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "2038-01-19T03:14:07Z");
}

// Test: A date in 1970 (just after epoch)
TEST_F(StringMakerTimePointTest_105, JustAfterEpoch_105) {
    auto tp = std::chrono::system_clock::from_time_t(1);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_EQ(result, "1970-01-01T00:00:01Z");
}

// Test: Result is not empty
TEST_F(StringMakerTimePointTest_105, ResultIsNotEmpty_105) {
    auto tp = std::chrono::system_clock::now();
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_FALSE(result.empty());
}

// Test: Contains 'T' separator between date and time
TEST_F(StringMakerTimePointTest_105, ContainsTSeparator_105) {
    auto tp = makeTimePoint(2023, 7, 4, 10, 20, 30);
    std::string result = Catch::StringMaker<std::chrono::time_point<std::chrono::system_clock>>::convert(tp);
    EXPECT_NE(result.find('T'), std::string::npos);
}

// ============================================================
// Tests for StringMaker<std::chrono::duration> specializations
// ============================================================

class StringMakerDurationTest_105 : public ::testing::Test {};

// Test: Duration in seconds
TEST_F(StringMakerDurationTest_105, SecondsConversion_105) {
    std::chrono::seconds dur(42);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain "42" and "s"
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test: Duration in milliseconds
TEST_F(StringMakerDurationTest_105, MillisecondsConversion_105) {
    std::chrono::milliseconds dur(1500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

// Test: Duration in minutes
TEST_F(StringMakerDurationTest_105, MinutesConversion_105) {
    std::chrono::minutes dur(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
}

// Test: Duration in hours
TEST_F(StringMakerDurationTest_105, HoursConversion_105) {
    std::chrono::hours dur(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2"), std::string::npos);
}

// Test: Zero duration
TEST_F(StringMakerDurationTest_105, ZeroDuration_105) {
    std::chrono::seconds dur(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test: Negative duration
TEST_F(StringMakerDurationTest_105, NegativeDuration_105) {
    std::chrono::seconds dur(-10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker basic types
// ============================================================

class StringMakerBasicTypesTest_105 : public ::testing::Test {};

// Test: Bool true
TEST_F(StringMakerBasicTypesTest_105, BoolTrue_105) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

// Test: Bool false
TEST_F(StringMakerBasicTypesTest_105, BoolFalse_105) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// Test: Integer conversion
TEST_F(StringMakerBasicTypesTest_105, IntConversion_105) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

// Test: Negative integer
TEST_F(StringMakerBasicTypesTest_105, NegativeIntConversion_105) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

// Test: Zero integer
TEST_F(StringMakerBasicTypesTest_105, ZeroIntConversion_105) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

// Test: Unsigned int
TEST_F(StringMakerBasicTypesTest_105, UnsignedIntConversion_105) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_EQ(result, "100");
}

// Test: Long long
TEST_F(StringMakerBasicTypesTest_105, LongLongConversion_105) {
    std::string result = Catch::StringMaker<long long>::convert(1234567890123LL);
    EXPECT_NE(result.find("1234567890123"), std::string::npos);
}

// Test: nullptr
TEST_F(StringMakerBasicTypesTest_105, NullptrConversion_105) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// Test: char conversion
TEST_F(StringMakerBasicTypesTest_105, CharConversion_105) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find('A'), std::string::npos);
}

// Test: String conversion
TEST_F(StringMakerBasicTypesTest_105, StringConversion_105) {
    std::string result = Catch::StringMaker<std::string>::convert("hello world");
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test: Empty string conversion
TEST_F(StringMakerBasicTypesTest_105, EmptyStringConversion_105) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should at least contain quotes or something
}

// Test: Float conversion
TEST_F(StringMakerBasicTypesTest_105, FloatConversion_105) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

// Test: Double conversion
TEST_F(StringMakerBasicTypesTest_105, DoubleConversion_105) {
    std::string result = Catch::StringMaker<double>::convert(2.71828);
    EXPECT_FALSE(result.empty());
}

// Test: Pointer conversion (non-null)
TEST_F(StringMakerBasicTypesTest_105, NonNullPointerConversion_105) {
    int x = 42;
    std::string result = Catch::StringMaker<int*>::convert(&x);
    EXPECT_FALSE(result.empty());
}

// Test: Null pointer conversion
TEST_F(StringMakerBasicTypesTest_105, NullPointerConversion_105) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// Test: C-string conversion
TEST_F(StringMakerBasicTypesTest_105, CStringConversion_105) {
    const char* str = "test";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("test"), std::string::npos);
}

// Test: Null C-string
TEST_F(StringMakerBasicTypesTest_105, NullCStringConversion_105) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// Test: string_view conversion
TEST_F(StringMakerBasicTypesTest_105, StringViewConversion_105) {
    std::string_view sv = "hello";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test: std::byte conversion
TEST_F(StringMakerBasicTypesTest_105, ByteConversion_105) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// Test: signed char conversion
TEST_F(StringMakerBasicTypesTest_105, SignedCharConversion_105) {
    signed char sc = 65;
    std::string result = Catch::StringMaker<signed char>::convert(sc);
    EXPECT_FALSE(result.empty());
}

// Test: unsigned char conversion
TEST_F(StringMakerBasicTypesTest_105, UnsignedCharConversion_105) {
    unsigned char uc = 255;
    std::string result = Catch::StringMaker<unsigned char>::convert(uc);
    EXPECT_FALSE(result.empty());
}

// Test: long conversion
TEST_F(StringMakerBasicTypesTest_105, LongConversion_105) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_NE(result.find("123456"), std::string::npos);
}

// Test: unsigned long conversion
TEST_F(StringMakerBasicTypesTest_105, UnsignedLongConversion_105) {
    std::string result = Catch::StringMaker<unsigned long>::convert(999999UL);
    EXPECT_NE(result.find("999999"), std::string::npos);
}

// Test: unsigned long long conversion
TEST_F(StringMakerBasicTypesTest_105, UnsignedLongLongConversion_105) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(18446744073709551615ULL);
    EXPECT_FALSE(result.empty());
}
