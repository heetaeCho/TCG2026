#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <chrono>

#include "catch2/catch_tostring.hpp"

// Test fixture for StringMaker tests
class StringMakerTest_82 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for StringMaker<char const*>::convert
// ============================================================

TEST_F(StringMakerTest_82, CharConstPointer_NormalString_82) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should produce a quoted string representation
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerTest_82, CharConstPointer_EmptyString_82) {
    const char* str = "";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, CharConstPointer_NullPointer_82) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<char*>::convert
// ============================================================

TEST_F(StringMakerTest_82, CharPointer_NormalString_82) {
    char str[] = "world";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("world"), std::string::npos);
}

// ============================================================
// Tests for StringMaker<std::string>::convert
// ============================================================

TEST_F(StringMakerTest_82, StdString_NormalString_82) {
    std::string str = "test string";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerTest_82, StdString_EmptyString_82) {
    std::string str = "";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, StdString_StringWithSpecialChars_82) {
    std::string str = "line1\nline2\ttab";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::string_view>::convert
// ============================================================

TEST_F(StringMakerTest_82, StringView_NormalString_82) {
    std::string_view sv = "view test";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("view test"), std::string::npos);
}

TEST_F(StringMakerTest_82, StringView_EmptyView_82) {
    std::string_view sv = "";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<bool>::convert
// ============================================================

TEST_F(StringMakerTest_82, Bool_True_82) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(StringMakerTest_82, Bool_False_82) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("false"), std::string::npos);
}

// ============================================================
// Tests for StringMaker<std::nullptr_t>::convert
// ============================================================

TEST_F(StringMakerTest_82, Nullptr_82) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<int>::convert
// ============================================================

TEST_F(StringMakerTest_82, Int_Positive_82) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_82, Int_Negative_82) {
    std::string result = Catch::StringMaker<int>::convert(-7);
    EXPECT_EQ(result, "-7");
}

TEST_F(StringMakerTest_82, Int_Zero_82) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_82, Int_MaxValue_82) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Int_MinValue_82) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<long>::convert
// ============================================================

TEST_F(StringMakerTest_82, Long_Positive_82) {
    std::string result = Catch::StringMaker<long>::convert(100L);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerTest_82, Long_Negative_82) {
    std::string result = Catch::StringMaker<long>::convert(-100L);
    EXPECT_EQ(result, "-100");
}

// ============================================================
// Tests for StringMaker<long long>::convert
// ============================================================

TEST_F(StringMakerTest_82, LongLong_LargeValue_82) {
    long long val = 9999999999LL;
    std::string result = Catch::StringMaker<long long>::convert(val);
    EXPECT_EQ(result, "9999999999");
}

// ============================================================
// Tests for StringMaker<unsigned int>::convert
// ============================================================

TEST_F(StringMakerTest_82, UnsignedInt_Normal_82) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_82, UnsignedInt_Zero_82) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

// ============================================================
// Tests for StringMaker<unsigned long>::convert
// ============================================================

TEST_F(StringMakerTest_82, UnsignedLong_Normal_82) {
    std::string result = Catch::StringMaker<unsigned long>::convert(255UL);
    EXPECT_EQ(result, "255");
}

// ============================================================
// Tests for StringMaker<unsigned long long>::convert
// ============================================================

TEST_F(StringMakerTest_82, UnsignedLongLong_LargeValue_82) {
    unsigned long long val = 18446744073709551615ULL;
    std::string result = Catch::StringMaker<unsigned long long>::convert(val);
    EXPECT_EQ(result, "18446744073709551615");
}

// ============================================================
// Tests for StringMaker<signed char>::convert
// ============================================================

TEST_F(StringMakerTest_82, SignedChar_Normal_82) {
    signed char c = 65; // 'A'
    std::string result = Catch::StringMaker<signed char>::convert(c);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, SignedChar_Negative_82) {
    signed char c = -1;
    std::string result = Catch::StringMaker<signed char>::convert(c);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<char>::convert
// ============================================================

TEST_F(StringMakerTest_82, Char_PrintableChar_82) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_82, Char_Newline_82) {
    std::string result = Catch::StringMaker<char>::convert('\n');
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Char_NullChar_82) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<unsigned char>::convert
// ============================================================

TEST_F(StringMakerTest_82, UnsignedChar_Normal_82) {
    unsigned char c = 200;
    std::string result = Catch::StringMaker<unsigned char>::convert(c);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, UnsignedChar_Zero_82) {
    unsigned char c = 0;
    std::string result = Catch::StringMaker<unsigned char>::convert(c);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<float>::convert
// ============================================================

TEST_F(StringMakerTest_82, Float_Normal_82) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Float_Zero_82) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Float_Negative_82) {
    std::string result = Catch::StringMaker<float>::convert(-1.5f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}

TEST_F(StringMakerTest_82, Float_Infinity_82) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Float_NaN_82) {
    std::string result = Catch::StringMaker<float>::convert(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<double>::convert
// ============================================================

TEST_F(StringMakerTest_82, Double_Normal_82) {
    std::string result = Catch::StringMaker<double>::convert(3.14159265358979);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Double_Zero_82) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Double_Infinity_82) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Double_NaN_82) {
    std::string result = Catch::StringMaker<double>::convert(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Double_NegativeInfinity_82) {
    std::string result = Catch::StringMaker<double>::convert(-std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for StringMaker<std::byte>::convert
// ============================================================

TEST_F(StringMakerTest_82, Byte_Normal_82) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Byte_Zero_82) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for pointer conversion
// ============================================================

TEST_F(StringMakerTest_82, Pointer_NonNull_82) {
    int x = 5;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, Pointer_Null_82) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for signed char const* array conversion
// ============================================================

TEST_F(StringMakerTest_82, SignedCharArray_NormalString_82) {
    signed char str[] = { 'H', 'i', '\0' };
    const signed char* p = str;
    // Use the array-based convert for signed char arrays
    std::string result = Catch::StringMaker<signed char[3]>::convert(str);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for wstring conversion
// ============================================================

TEST_F(StringMakerTest_82, WString_Normal_82) {
    std::wstring wstr = L"wide string";
    std::string result = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, WString_Empty_82) {
    std::wstring wstr = L"";
    std::string result = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for wstring_view conversion
// ============================================================

TEST_F(StringMakerTest_82, WStringView_Normal_82) {
    std::wstring_view wsv = L"wide view";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for wchar_t const* conversion
// ============================================================

TEST_F(StringMakerTest_82, WCharConstPointer_Normal_82) {
    const wchar_t* wstr = L"wchar test";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, WCharConstPointer_Null_82) {
    const wchar_t* wstr = nullptr;
    std::string result = Catch::StringMaker<wchar_t const*>::convert(wstr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for chrono durations
// ============================================================

TEST_F(StringMakerTest_82, ChronoDuration_Nanoseconds_82) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoDuration_Microseconds_82) {
    auto dur = std::chrono::microseconds(1000);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoDuration_Milliseconds_82) {
    auto dur = std::chrono::milliseconds(250);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoDuration_Seconds_82) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoDuration_Minutes_82) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoDuration_Hours_82) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for chrono time_point
// ============================================================

TEST_F(StringMakerTest_82, ChronoTimePoint_SystemClock_82) {
    auto tp = std::chrono::system_clock::now();
    std::string result = Catch::StringMaker<std::chrono::system_clock::time_point>::convert(tp);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, ChronoTimePoint_SteadyClock_82) {
    auto tp = std::chrono::steady_clock::now();
    std::string result = Catch::StringMaker<std::chrono::steady_clock::time_point>::convert(tp);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for stream-insertable types
// ============================================================

TEST_F(StringMakerTest_82, StreamInsertable_StdString_82) {
    // std::string is stream insertable; test via general StringMaker
    std::string val = "stream test";
    std::string result = Catch::StringMaker<std::string>::convert(val);
    EXPECT_NE(result.find("stream test"), std::string::npos);
}

// ============================================================
// Tests for member pointer conversion
// ============================================================

struct TestStruct_82 {
    int member;
    void method() {}
};

TEST_F(StringMakerTest_82, MemberDataPointer_82) {
    int TestStruct_82::* mp = &TestStruct_82::member;
    std::string result = Catch::StringMaker<int TestStruct_82::*>::convert(mp);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_82, MemberFunctionPointer_82) {
    void (TestStruct_82::* mfp)() = &TestStruct_82::method;
    std::string result = Catch::StringMaker<void (TestStruct_82::*)()>::convert(mfp);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Additional boundary tests for char arrays
// ============================================================

TEST_F(StringMakerTest_82, CharArray_SingleChar_82) {
    const char arr[] = "A";
    std::string result = Catch::StringMaker<char[2]>::convert(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerTest_82, CharArray_LongString_82) {
    const char arr[] = "This is a fairly long test string for boundary testing";
    std::string result = Catch::StringMaker<char[55]>::convert(arr);
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for consistency: same input should produce same output
// ============================================================

TEST_F(StringMakerTest_82, Consistency_SameIntProducesSameResult_82) {
    std::string result1 = Catch::StringMaker<int>::convert(42);
    std::string result2 = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_82, Consistency_SameStringProducesSameResult_82) {
    std::string result1 = Catch::StringMaker<std::string>::convert("test");
    std::string result2 = Catch::StringMaker<std::string>::convert("test");
    EXPECT_EQ(result1, result2);
}

TEST_F(StringMakerTest_82, Consistency_DifferentIntsProduceDifferentResults_82) {
    std::string result1 = Catch::StringMaker<int>::convert(1);
    std::string result2 = Catch::StringMaker<int>::convert(2);
    EXPECT_NE(result1, result2);
}
