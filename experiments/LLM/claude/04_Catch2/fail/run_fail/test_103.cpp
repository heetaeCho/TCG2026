#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <cstring>
#include <limits>

#include "catch2/catch_tostring.hpp"

// Tests for chrono duration conversions (hours specifically, as shown in the partial code)
// and other StringMaker conversions visible through the interface.

class StringMakerChronoTest_103 : public ::testing::Test {};

// ==================== Hours duration tests ====================

TEST_F(StringMakerChronoTest_103, HoursDurationZero_103) {
    std::chrono::hours duration(0);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_EQ(result, "0 h");
}

TEST_F(StringMakerChronoTest_103, HoursDurationPositive_103) {
    std::chrono::hours duration(5);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_EQ(result, "5 h");
}

TEST_F(StringMakerChronoTest_103, HoursDurationNegative_103) {
    std::chrono::hours duration(-3);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_EQ(result, "-3 h");
}

TEST_F(StringMakerChronoTest_103, HoursDurationOne_103) {
    std::chrono::hours duration(1);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_EQ(result, "1 h");
}

TEST_F(StringMakerChronoTest_103, HoursDurationLargeValue_103) {
    std::chrono::hours duration(10000);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_EQ(result, "10000 h");
}

// ==================== Seconds duration tests ====================

TEST_F(StringMakerChronoTest_103, SecondsDurationZero_103) {
    std::chrono::seconds duration(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(duration);
    EXPECT_EQ(result, "0 s");
}

TEST_F(StringMakerChronoTest_103, SecondsDurationPositive_103) {
    std::chrono::seconds duration(42);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(duration);
    EXPECT_EQ(result, "42 s");
}

TEST_F(StringMakerChronoTest_103, SecondsDurationNegative_103) {
    std::chrono::seconds duration(-10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(duration);
    EXPECT_EQ(result, "-10 s");
}

// ==================== Minutes duration tests ====================

TEST_F(StringMakerChronoTest_103, MinutesDurationZero_103) {
    std::chrono::minutes duration(0);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(duration);
    EXPECT_EQ(result, "0 m");
}

TEST_F(StringMakerChronoTest_103, MinutesDurationPositive_103) {
    std::chrono::minutes duration(15);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(duration);
    EXPECT_EQ(result, "15 m");
}

TEST_F(StringMakerChronoTest_103, MinutesDurationNegative_103) {
    std::chrono::minutes duration(-7);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(duration);
    EXPECT_EQ(result, "-7 m");
}

// ==================== Milliseconds duration tests ====================

TEST_F(StringMakerChronoTest_103, MillisecondsDuration_103) {
    std::chrono::milliseconds duration(500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(duration);
    // Milliseconds should produce some output with appropriate suffix
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("500"), std::string::npos);
}

// ==================== StringMaker for basic types ====================

class StringMakerBasicTypesTest_103 : public ::testing::Test {};

TEST_F(StringMakerBasicTypesTest_103, IntConvert_103) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerBasicTypesTest_103, IntConvertNegative_103) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerBasicTypesTest_103, IntConvertZero_103) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerBasicTypesTest_103, LongConvert_103) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST_F(StringMakerBasicTypesTest_103, LongLongConvert_103) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST_F(StringMakerBasicTypesTest_103, UnsignedIntConvert_103) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerBasicTypesTest_103, UnsignedLongConvert_103) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerBasicTypesTest_103, UnsignedLongLongConvert_103) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// ==================== Bool tests ====================

TEST_F(StringMakerBasicTypesTest_103, BoolTrue_103) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerBasicTypesTest_103, BoolFalse_103) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ==================== String tests ====================

TEST_F(StringMakerBasicTypesTest_103, StdStringConvert_103) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, StdStringEmpty_103) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty()); // Should at least have quotes or something
}

TEST_F(StringMakerBasicTypesTest_103, CharConstPtrConvert_103) {
    const char* input = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(input);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, CharConstPtrNull_103) {
    const char* input = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(input);
    // Should handle nullptr gracefully
    EXPECT_FALSE(result.empty());
}

// ==================== Char tests ====================

TEST_F(StringMakerBasicTypesTest_103, CharConvert_103) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, SignedCharConvert_103) {
    std::string result = Catch::StringMaker<signed char>::convert(65);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerBasicTypesTest_103, UnsignedCharConvert_103) {
    std::string result = Catch::StringMaker<unsigned char>::convert(255);
    EXPECT_FALSE(result.empty());
}

// ==================== Float/Double tests ====================

TEST_F(StringMakerBasicTypesTest_103, FloatConvert_103) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain "3.14" approximately
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, FloatConvertZero_103) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, DoubleConvert_103) {
    std::string result = Catch::StringMaker<double>::convert(2.718281828);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerBasicTypesTest_103, DoubleConvertNegative_103) {
    std::string result = Catch::StringMaker<double>::convert(-1.5);
    EXPECT_NE(result.find("-1.5"), std::string::npos);
}

// ==================== Nullptr tests ====================

TEST_F(StringMakerBasicTypesTest_103, NullptrConvert_103) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ==================== Pointer tests ====================

TEST_F(StringMakerBasicTypesTest_103, PointerNonNull_103) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerBasicTypesTest_103, PointerNull_103) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ==================== string_view tests ====================

TEST_F(StringMakerBasicTypesTest_103, StringViewConvert_103) {
    std::string_view sv = "hello";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerBasicTypesTest_103, StringViewEmpty_103) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ==================== Hours boundary/edge tests ====================

TEST_F(StringMakerChronoTest_103, HoursDurationMaxValue_103) {
    // Use a very large hours value
    std::chrono::hours duration(std::chrono::hours::max());
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find(" h"), std::string::npos);
}

TEST_F(StringMakerChronoTest_103, HoursDurationMinValue_103) {
    std::chrono::hours duration(std::chrono::hours::min());
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(duration);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find(" h"), std::string::npos);
}

// ==================== Microseconds tests ====================

TEST_F(StringMakerChronoTest_103, MicrosecondsDuration_103) {
    std::chrono::microseconds duration(1500);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(duration);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1500"), std::string::npos);
}

// ==================== Nanoseconds tests ====================

TEST_F(StringMakerChronoTest_103, NanosecondsDuration_103) {
    std::chrono::nanoseconds duration(42);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(duration);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

// ==================== Custom duration with ratio<3600> ====================

TEST_F(StringMakerChronoTest_103, CustomHoursDuration_103) {
    // Using a custom duration type that uses ratio<3600> but with double
    using double_hours = std::chrono::duration<double, std::ratio<3600>>;
    double_hours duration(2.5);
    std::string result = Catch::StringMaker<double_hours>::convert(duration);
    EXPECT_NE(result.find("2.5"), std::string::npos);
    EXPECT_NE(result.find(" h"), std::string::npos);
}

// ==================== std::byte tests ====================

TEST_F(StringMakerBasicTypesTest_103, ByteConvert_103) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerBasicTypesTest_103, ByteConvertZero_103) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// ==================== Multiple conversions (ensure no state issues) ====================

TEST_F(StringMakerChronoTest_103, MultipleHoursConversions_103) {
    std::chrono::hours d1(1);
    std::chrono::hours d2(2);
    std::chrono::hours d3(3);
    
    std::string r1 = Catch::StringMaker<std::chrono::hours>::convert(d1);
    std::string r2 = Catch::StringMaker<std::chrono::hours>::convert(d2);
    std::string r3 = Catch::StringMaker<std::chrono::hours>::convert(d3);
    
    EXPECT_EQ(r1, "1 h");
    EXPECT_EQ(r2, "2 h");
    EXPECT_EQ(r3, "3 h");
}

TEST_F(StringMakerBasicTypesTest_103, MultipleIntConversions_103) {
    EXPECT_EQ(Catch::StringMaker<int>::convert(1), "1");
    EXPECT_EQ(Catch::StringMaker<int>::convert(2), "2");
    EXPECT_EQ(Catch::StringMaker<int>::convert(3), "3");
}
