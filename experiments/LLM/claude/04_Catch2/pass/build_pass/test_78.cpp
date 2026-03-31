#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <chrono>
#include <cstddef>
#include <vector>

#include "catch2/catch_tostring.hpp"

// ===========================================================================
// Tests for StringMaker with various types
// ===========================================================================

// --- Integer types ---

TEST(StringMakerTest_78, ConvertInt_78) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_78, ConvertIntZero_78) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerTest_78, ConvertNegativeInt_78) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerTest_78, ConvertIntMax_78) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST(StringMakerTest_78, ConvertIntMin_78) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

TEST(StringMakerTest_78, ConvertLong_78) {
    std::string result = Catch::StringMaker<long>::convert(123456L);
    EXPECT_EQ(result, "123456");
}

TEST(StringMakerTest_78, ConvertLongLong_78) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST(StringMakerTest_78, ConvertUnsignedInt_78) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_78, ConvertUnsignedLong_78) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerTest_78, ConvertUnsignedLongLong_78) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// --- Char types ---

TEST(StringMakerTest_78, ConvertChar_78) {
    std::string result = Catch::StringMaker<char>::convert('A');
    // Catch typically wraps char in quotes
    EXPECT_FALSE(result.empty());
    // Should contain 'A' somewhere
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST(StringMakerTest_78, ConvertSignedChar_78) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertUnsignedChar_78) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(65));
    EXPECT_FALSE(result.empty());
}

// --- Floating point types ---

TEST(StringMakerTest_78, ConvertFloat_78) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain "3.14" approximately
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertFloatZero_78) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertDouble_78) {
    std::string result = Catch::StringMaker<double>::convert(2.71828);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.71"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertDoubleZero_78) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertDoubleNegative_78) {
    std::string result = Catch::StringMaker<double>::convert(-1.5);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-"), std::string::npos);
}

// --- String types ---

TEST(StringMakerTest_78, ConvertStdString_78) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertEmptyStdString_78) {
    std::string input;
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Should produce some representation of empty string
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertStringView_78) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertEmptyStringView_78) {
    std::string_view sv;
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
}

// --- C-string types ---

TEST(StringMakerTest_78, ConvertCharConstPtr_78) {
    const char* str = "c-string";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_NE(result.find("c-string"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertCharPtr_78) {
    char buf[] = "mutable";
    char* str = buf;
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertNullCharConstPtr_78) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should handle nullptr gracefully
    EXPECT_FALSE(result.empty());
}

// --- Bool ---

TEST(StringMakerTest_78, ConvertBoolTrue_78) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerTest_78, ConvertBoolFalse_78) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// --- nullptr ---

TEST(StringMakerTest_78, ConvertNullptr_78) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// --- Pointer types ---

TEST(StringMakerTest_78, ConvertNonNullPointer_78) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    // Should produce some hex address representation
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertNullPointer_78) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    // Should indicate null
    EXPECT_FALSE(result.empty());
}

// --- std::byte ---

TEST(StringMakerTest_78, ConvertByte_78) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertByteZero_78) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// --- Chrono duration types ---

TEST(StringMakerTest_78, ConvertChronoNanoseconds_78) {
    auto dur = std::chrono::nanoseconds(500);
    std::string result = Catch::StringMaker<std::chrono::nanoseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoMicroseconds_78) {
    auto dur = std::chrono::microseconds(1234);
    std::string result = Catch::StringMaker<std::chrono::microseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1234"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoMilliseconds_78) {
    auto dur = std::chrono::milliseconds(100);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoSeconds_78) {
    auto dur = std::chrono::seconds(5);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoMinutes_78) {
    auto dur = std::chrono::minutes(10);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoHours_78) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertChronoZeroDuration_78) {
    auto dur = std::chrono::seconds(0);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

// --- Stream-insertable custom type via template ---

struct StreamableType {
    int value;
    friend std::ostream& operator<<(std::ostream& os, const StreamableType& st) {
        os << "StreamableType(" << st.value << ")";
        return os;
    }
};

TEST(StringMakerTest_78, ConvertStreamInsertableCustomType_78) {
    StreamableType st{99};
    std::string result = Catch::StringMaker<StreamableType>::convert(st);
    EXPECT_NE(result.find("StreamableType(99)"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertStreamInsertableCustomTypeNegative_78) {
    StreamableType st{-5};
    std::string result = Catch::StringMaker<StreamableType>::convert(st);
    EXPECT_NE(result.find("StreamableType(-5)"), std::string::npos);
}

// --- Wide string types ---

TEST(StringMakerTest_78, ConvertWideString_78) {
    std::wstring ws = L"wide";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("wide"), std::string::npos);
}

TEST(StringMakerTest_78, ConvertEmptyWideString_78) {
    std::wstring ws;
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertWideStringView_78) {
    std::wstring_view wsv = L"wview";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertWcharConstPtr_78) {
    const wchar_t* ws = L"wchar";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertWcharPtr_78) {
    wchar_t buf[] = L"wbuf";
    wchar_t* ws = buf;
    std::string result = Catch::StringMaker<wchar_t*>::convert(ws);
    EXPECT_FALSE(result.empty());
}

// --- Boundary: large values ---

TEST(StringMakerTest_78, ConvertUnsignedLongLongMax_78) {
    auto val = std::numeric_limits<unsigned long long>::max();
    std::string result = Catch::StringMaker<unsigned long long>::convert(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(StringMakerTest_78, ConvertLongLongMin_78) {
    auto val = std::numeric_limits<long long>::min();
    std::string result = Catch::StringMaker<long long>::convert(val);
    EXPECT_EQ(result, std::to_string(val));
}

// --- Multiple conversions (ensure no state leakage) ---

TEST(StringMakerTest_78, MultipleConversionsNoStateLeak_78) {
    std::string r1 = Catch::StringMaker<int>::convert(1);
    std::string r2 = Catch::StringMaker<int>::convert(2);
    std::string r3 = Catch::StringMaker<int>::convert(3);
    EXPECT_EQ(r1, "1");
    EXPECT_EQ(r2, "2");
    EXPECT_EQ(r3, "3");
}

TEST(StringMakerTest_78, ConvertStringWithSpecialChars_78) {
    std::string input = "hello\nworld\ttab";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // The result should contain the original content (possibly with escaping)
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_78, ConvertStringWithQuotes_78) {
    std::string input = "he said \"hi\"";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
}
