#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <array>
#include <chrono>
#include <cstddef>
#include <sstream>

// Include Catch2's amalgamated header for StringMaker
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// ============================================================================
// Tests for StringMaker with basic types
// ============================================================================

TEST(StringMakerTest_919, ConvertInt_919) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_919, ConvertNegativeInt_919) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerTest_919, ConvertZeroInt_919) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerTest_919, ConvertLong_919) {
    std::string result = Catch::StringMaker<long>::convert(123456789L);
    EXPECT_EQ(result, "123456789");
}

TEST(StringMakerTest_919, ConvertLongLong_919) {
    std::string result = Catch::StringMaker<long long>::convert(9876543210LL);
    EXPECT_EQ(result, "9876543210");
}

TEST(StringMakerTest_919, ConvertUnsignedInt_919) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerTest_919, ConvertUnsignedLong_919) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerTest_919, ConvertUnsignedLongLong_919) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

TEST(StringMakerTest_919, ConvertSignedChar_919) {
    std::string result = Catch::StringMaker<signed char>::convert(65);
    // signed char may be displayed as a number
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertChar_919) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Typically shows 'A' in some quoted form
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST(StringMakerTest_919, ConvertUnsignedChar_919) {
    std::string result = Catch::StringMaker<unsigned char>::convert(66);
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Tests for StringMaker with floating point types
// ============================================================================

TEST(StringMakerTest_919, ConvertFloat_919) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
    // Should contain "3.14" approximately
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertDouble_919) {
    std::string result = Catch::StringMaker<double>::convert(2.718281828);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2.71828"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertFloatZero_919) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("0"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertDoubleNegative_919) {
    std::string result = Catch::StringMaker<double>::convert(-1.5);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("-1.5"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with bool
// ============================================================================

TEST(StringMakerTest_919, ConvertBoolTrue_919) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerTest_919, ConvertBoolFalse_919) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ============================================================================
// Tests for StringMaker with strings
// ============================================================================

TEST(StringMakerTest_919, ConvertStdString_919) {
    std::string result = Catch::StringMaker<std::string>::convert("hello");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertEmptyStdString_919) {
    std::string result = Catch::StringMaker<std::string>::convert("");
    EXPECT_FALSE(result.empty()); // Should at least have quotes
}

TEST(StringMakerTest_919, ConvertStringView_919) {
    std::string_view sv = "test_view";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test_view"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertCharConstPtr_919) {
    const char* str = "cstring";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("cstring"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertCharPtr_919) {
    char buf[] = "mutable";
    std::string result = Catch::StringMaker<char*>::convert(buf);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("mutable"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with nullptr
// ============================================================================

TEST(StringMakerTest_919, ConvertNullptr_919) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("nullptr"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with pointers
// ============================================================================

TEST(StringMakerTest_919, ConvertNonNullPointer_919) {
    int x = 42;
    std::string result = Catch::StringMaker<int*>::convert(&x);
    EXPECT_FALSE(result.empty());
    // Pointer representation typically starts with 0x
    EXPECT_NE(result.find("0x"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertNullPointer_919) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Tests for StringMaker with std::byte
// ============================================================================

TEST(StringMakerTest_919, ConvertByte_919) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0xFF});
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertByteZero_919) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0x00});
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Tests for StringMaker with ranges/containers
// ============================================================================

TEST(StringMakerTest_919, ConvertVectorInt_919) {
    std::vector<int> v = {1, 2, 3};
    std::string result = Catch::Detail::stringify(v);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertEmptyVector_919) {
    std::vector<int> v;
    std::string result = Catch::Detail::stringify(v);
    EXPECT_FALSE(result.empty());
    // Empty range typically shows "{  }" or similar
}

TEST(StringMakerTest_919, ConvertVectorString_919) {
    std::vector<std::string> v = {"hello", "world"};
    std::string result = Catch::Detail::stringify(v);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
    EXPECT_NE(result.find("world"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertListInt_919) {
    std::list<int> l = {10, 20, 30};
    std::string result = Catch::Detail::stringify(l);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertSetInt_919) {
    std::set<int> s = {5, 10, 15};
    std::string result = Catch::Detail::stringify(s);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("15"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertMapIntString_919) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    std::string result = Catch::Detail::stringify(m);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("one"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("two"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with C-style arrays
// ============================================================================

TEST(StringMakerTest_919, ConvertCStyleArrayInt_919) {
    int arr[] = {1, 2, 3, 4, 5};
    std::string result = Catch::Detail::stringify(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("5"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with chrono types
// ============================================================================

TEST(StringMakerTest_919, ConvertChronoMilliseconds_919) {
    auto dur = std::chrono::milliseconds(500);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("500"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertChronoSeconds_919) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertChronoMinutes_919) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertChronoHours_919) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertChronoMicroseconds_919) {
    auto dur = std::chrono::microseconds(1234);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1234"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertChronoNanoseconds_919) {
    auto dur = std::chrono::nanoseconds(999);
    std::string result = Catch::Detail::stringify(dur);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("999"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with wide strings
// ============================================================================

TEST(StringMakerTest_919, ConvertWstring_919) {
    std::wstring ws = L"wide";
    std::string result = Catch::StringMaker<std::wstring>::convert(ws);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("wide"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertWstringView_919) {
    std::wstring_view wsv = L"wview";
    std::string result = Catch::StringMaker<std::wstring_view>::convert(wsv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("wview"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertWcharConstPtr_919) {
    const wchar_t* ws = L"wchar";
    std::string result = Catch::StringMaker<wchar_t const*>::convert(ws);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("wchar"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertWcharPtr_919) {
    wchar_t buf[] = L"wmut";
    std::string result = Catch::StringMaker<wchar_t*>::convert(buf);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("wmut"), std::string::npos);
}

// ============================================================================
// Tests for boundary conditions
// ============================================================================

TEST(StringMakerTest_919, ConvertIntMax_919) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertIntMin_919) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertUnsignedLongLongMax_919) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(
        std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertDoubleInfinity_919) {
    std::string result = Catch::StringMaker<double>::convert(
        std::numeric_limits<double>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertDoubleNaN_919) {
    std::string result = Catch::StringMaker<double>::convert(
        std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(result.empty());
    // NaN is typically rendered as "nan" or "nanf"
}

TEST(StringMakerTest_919, ConvertFloatInfinity_919) {
    std::string result = Catch::StringMaker<float>::convert(
        std::numeric_limits<float>::infinity());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertFloatNaN_919) {
    std::string result = Catch::StringMaker<float>::convert(
        std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Tests for StringMaker with std::pair via stringify
// ============================================================================

TEST(StringMakerTest_919, ConvertPair_919) {
    std::pair<int, std::string> p = {42, "answer"};
    std::string result = Catch::Detail::stringify(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("answer"), std::string::npos);
}

// ============================================================================
// Tests for StringMaker with std::tuple via stringify
// ============================================================================

TEST(StringMakerTest_919, ConvertTuple_919) {
    auto t = std::make_tuple(1, "two", 3.0);
    std::string result = Catch::Detail::stringify(t);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("two"), std::string::npos);
}

TEST(StringMakerTest_919, ConvertEmptyTuple_919) {
    auto t = std::make_tuple();
    std::string result = Catch::Detail::stringify(t);
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Tests for StringMaker with single-element vector
// ============================================================================

TEST(StringMakerTest_919, ConvertSingleElementVector_919) {
    std::vector<int> v = {42};
    std::string result = Catch::Detail::stringify(v);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

// ============================================================================
// Tests for stream-insertable custom types
// ============================================================================

struct StreamableType_919 {
    int value;
    friend std::ostream& operator<<(std::ostream& os, const StreamableType_919& st) {
        return os << "StreamableType(" << st.value << ")";
    }
};

TEST(StringMakerTest_919, ConvertStreamableType_919) {
    StreamableType_919 obj{99};
    std::string result = Catch::Detail::stringify(obj);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("StreamableType(99)"), std::string::npos);
}

// ============================================================================
// Tests for large containers
// ============================================================================

TEST(StringMakerTest_919, ConvertLargeVector_919) {
    std::vector<int> v(100);
    for (int i = 0; i < 100; ++i) v[i] = i;
    std::string result = Catch::Detail::stringify(v);
    EXPECT_FALSE(result.empty());
    // Should contain at least some elements
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ============================================================================
// Tests for std::array
// ============================================================================

TEST(StringMakerTest_919, ConvertStdArray_919) {
    std::array<int, 3> arr = {10, 20, 30};
    std::string result = Catch::Detail::stringify(arr);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// ============================================================================
// Test for string with special characters
// ============================================================================

TEST(StringMakerTest_919, ConvertStringWithSpecialChars_919) {
    std::string s = "hello\nworld\t!";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerTest_919, ConvertStringWithQuotes_919) {
    std::string s = R"(he said "hi")";
    std::string result = Catch::StringMaker<std::string>::convert(s);
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Test for char const* null
// ============================================================================

TEST(StringMakerTest_919, ConvertNullCharConstPtr_919) {
    const char* str = nullptr;
    std::string result = Catch::Detail::stringify(str);
    EXPECT_FALSE(result.empty());
}
