#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <cstddef>

#include "catch2/catch_tostring.hpp"

// Helper to invoke StringMaker::convert for various types
// We use Catch::StringMaker<T>::convert(...) directly

class StringMakerTest_81 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== char const* ====================

TEST_F(StringMakerTest_81, ConvertCharConstPtr_NormalString_81) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    // Should contain the string content
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertCharConstPtr_EmptyString_81) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should produce some representation of an empty string
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertCharConstPtr_Nullptr_81) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ==================== char* ====================

TEST_F(StringMakerTest_81, ConvertCharPtr_NormalString_81) {
    char str[] = "world";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("world"), std::string::npos);
}

// ==================== std::string ====================

TEST_F(StringMakerTest_81, ConvertStdString_Normal_81) {
    std::string str = "test string";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertStdString_Empty_81) {
    std::string str = "";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertStdString_WithSpecialChars_81) {
    std::string str = "hello\nworld";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ==================== std::string_view ====================

TEST_F(StringMakerTest_81, ConvertStringView_Normal_81) {
    std::string_view sv = "view test";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("view test"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertStringView_Empty_81) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ==================== bool ====================

TEST_F(StringMakerTest_81, ConvertBool_True_81) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertBool_False_81) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_NE(result.find("false"), std::string::npos);
}

// ==================== int ====================

TEST_F(StringMakerTest_81, ConvertInt_Positive_81) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertInt_Negative_81) {
    std::string result = Catch::StringMaker<int>::convert(-7);
    EXPECT_NE(result.find("-7"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertInt_Zero_81) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertInt_MaxValue_81) {
    int maxVal = std::numeric_limits<int>::max();
    std::string result = Catch::StringMaker<int>::convert(maxVal);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertInt_MinValue_81) {
    int minVal = std::numeric_limits<int>::min();
    std::string result = Catch::StringMaker<int>::convert(minVal);
    EXPECT_FALSE(result.empty());
}

// ==================== long ====================

TEST_F(StringMakerTest_81, ConvertLong_Normal_81) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_NE(result.find("123456"), std::string::npos);
}

// ==================== long long ====================

TEST_F(StringMakerTest_81, ConvertLongLong_Normal_81) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_NE(result.find("9876543210"), std::string::npos);
}

// ==================== unsigned int ====================

TEST_F(StringMakerTest_81, ConvertUnsignedInt_Normal_81) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertUnsignedInt_Zero_81) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== unsigned long ====================

TEST_F(StringMakerTest_81, ConvertUnsignedLong_Normal_81) {
    std::string result = Catch::StringMaker<unsigned long>::convert(500UL);
    EXPECT_NE(result.find("500"), std::string::npos);
}

// ==================== unsigned long long ====================

TEST_F(StringMakerTest_81, ConvertUnsignedLongLong_Normal_81) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999999999999ULL);
    EXPECT_NE(result.find("999999999999"), std::string::npos);
}

// ==================== char ====================

TEST_F(StringMakerTest_81, ConvertChar_Printable_81) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Should contain the character representation
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertChar_Null_81) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertChar_Newline_81) {
    std::string result = Catch::StringMaker<char>::convert('\n');
    EXPECT_FALSE(result.empty());
}

// ==================== signed char ====================

TEST_F(StringMakerTest_81, ConvertSignedChar_Normal_81) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

// ==================== unsigned char ====================

TEST_F(StringMakerTest_81, ConvertUnsignedChar_Normal_81) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertUnsignedChar_Zero_81) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(0));
    EXPECT_FALSE(result.empty());
}

// ==================== float ====================

TEST_F(StringMakerTest_81, ConvertFloat_Normal_81) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain some representation of 3.14
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertFloat_Zero_81) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertFloat_Negative_81) {
    std::string result = Catch::StringMaker<float>::convert(-1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertFloat_Infinity_81) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertFloat_NaN_81) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// ==================== double ====================

TEST_F(StringMakerTest_81, ConvertDouble_Normal_81) {
    std::string result = Catch::StringMaker<double>::convert(2.718281828);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDouble_Zero_81) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDouble_Infinity_81) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDouble_NaN_81) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDouble_NegativeInfinity_81) {
    std::string result = Catch::StringMaker<double>::convert(-std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

// ==================== nullptr_t ====================

TEST_F(StringMakerTest_81, ConvertNullptr_81) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ==================== pointer ====================

TEST_F(StringMakerTest_81, ConvertPointer_NonNull_81) {
    int x = 42;
    std::string result = Catch::StringMaker<int*>::convert(&x);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertPointer_Null_81) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ==================== std::byte ====================

TEST_F(StringMakerTest_81, ConvertByte_Zero_81) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertByte_MaxValue_81) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{255});
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertByte_MidValue_81) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0xAB});
    EXPECT_FALSE(result.empty());
}

// ==================== wchar_t const* ====================

TEST_F(StringMakerTest_81, ConvertWcharConstPtr_Normal_81) {
    const wchar_t* wstr = L"wide";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertWcharConstPtr_Empty_81) {
    const wchar_t* wstr = L"";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

// ==================== wchar_t* ====================

TEST_F(StringMakerTest_81, ConvertWcharPtr_Normal_81) {
    wchar_t wstr[] = L"widechar";
    std::string result = Catch::StringMaker<wchar_t*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

// ==================== std::wstring ====================

TEST_F(StringMakerTest_81, ConvertWstring_Normal_81) {
    std::wstring wstr = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertWstring_Empty_81) {
    std::wstring wstr = L"";
    std::string result = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

// ==================== std::wstring_view ====================

TEST_F(StringMakerTest_81, ConvertWstringView_Normal_81) {
    std::wstring_view wsv = L"wide view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

// ==================== C-style array (char const[]) ====================

TEST_F(StringMakerTest_81, ConvertCharArray_Normal_81) {
    // The convert for T const(&arr)[SZ] with char arrays
    const char arr[] = "array test";
    // StringMaker for char const* should handle this
    std::string result = Catch::StringMaker<char const*>::convert(arr);
    EXPECT_NE(result.find("array test"), std::string::npos);
}

// ==================== Chrono durations ====================

TEST_F(StringMakerTest_81, ConvertDuration_Nanoseconds_81) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDuration_Microseconds_81) {
    auto dur = std::chrono::microseconds(1000);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDuration_Milliseconds_81) {
    auto dur = std::chrono::milliseconds(250);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertDuration_Seconds_81) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain 's' for seconds
    EXPECT_NE(result.find("s"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertDuration_Minutes_81) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain 'm' for minutes
    EXPECT_NE(result.find("m"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertDuration_Hours_81) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    // Should contain 'h' for hours
    EXPECT_NE(result.find("h"), std::string::npos);
}

TEST_F(StringMakerTest_81, ConvertDuration_ZeroSeconds_81) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

// ==================== Chrono time_point ====================

TEST_F(StringMakerTest_81, ConvertTimePoint_SystemClock_81) {
    auto tp = std::chrono::system_clock::now();
    std::string result = Catch::StringMaker<decltype(tp)>::convert(tp);
    EXPECT_FALSE(result.empty());
}

// ==================== Stream-insertable types ====================

TEST_F(StringMakerTest_81, ConvertStreamInsertableType_81) {
    // std::string is stream-insertable, already tested above
    // Test with an int which is also stream-insertable via StringMaker specialization
    std::string result = Catch::StringMaker<int>::convert(12345);
    EXPECT_EQ(result, "12345");
}

// ==================== signed char const* ====================

TEST_F(StringMakerTest_81, ConvertSignedCharConstPtr_Normal_81) {
    const signed char str[] = "signed";
    std::string result = Catch::StringMaker<signed char const*>::convert(reinterpret_cast<const signed char*>(str));
    EXPECT_FALSE(result.empty());
}

// ==================== unsigned char const* ====================

TEST_F(StringMakerTest_81, ConvertUnsignedCharConstPtr_Normal_81) {
    const unsigned char str[] = "unsigned";
    std::string result = Catch::StringMaker<unsigned char const*>::convert(reinterpret_cast<const unsigned char*>(str));
    EXPECT_FALSE(result.empty());
}

// ==================== Consistency tests ====================

TEST_F(StringMakerTest_81, ConvertInt_SameValueGivesSameResult_81) {
    std::string result1 = Catch::StringMaker<int>::convert(42);
    std::string result2 = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_81, ConvertDouble_SameValueGivesSameResult_81) {
    std::string result1 = Catch::StringMaker<double>::convert(3.14);
    std::string result2 = Catch::StringMaker<double>::convert(3.14);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_81, ConvertString_SameValueGivesSameResult_81) {
    std::string result1 = Catch::StringMaker<std::string>::convert("abc");
    std::string result2 = Catch::StringMaker<std::string>::convert("abc");
    EXPECT_EQ(result1, result2);
}

// ==================== Boundary: very long string ====================

TEST_F(StringMakerTest_81, ConvertStdString_VeryLongString_81) {
    std::string longStr(10000, 'x');
    std::string result = Catch::StringMaker<std::string>::convert(longStr);
    EXPECT_FALSE(result.empty());
}

// ==================== Boundary: large integer values ====================

TEST_F(StringMakerTest_81, ConvertUnsignedLongLong_MaxValue_81) {
    unsigned long long maxVal = std::numeric_limits<unsigned long long>::max();
    std::string result = Catch::StringMaker<unsigned long long>::convert(maxVal);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_81, ConvertLongLong_MinValue_81) {
    long long minVal = std::numeric_limits<long long>::min();
    std::string result = Catch::StringMaker<long long>::convert(minVal);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}
