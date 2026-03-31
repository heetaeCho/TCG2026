#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ============================================================
// Default Construction Tests
// ============================================================

TEST(StringRefTest_5, DefaultConstructor_IsEmpty_5) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from raw C-string
// ============================================================

TEST(StringRefTest_5, ConstructFromRawCString_5) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_5, ConstructFromEmptyRawCString_5) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from std::string
// ============================================================

TEST(StringRefTest_5, ConstructFromStdString_5) {
    std::string s = "world";
    StringRef sr(s);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_5, ConstructFromEmptyStdString_5) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction with raw pointer and size
// ============================================================

TEST(StringRefTest_5, ConstructFromRawCharsAndSize_5) {
    const char* data = "abcdef";
    StringRef sr(data, 3);
    EXPECT_EQ(sr.size(), 3u);
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[2], 'c');
}

// ============================================================
// Equality and Inequality Operators
// ============================================================

TEST(StringRefTest_5, EqualityOperator_SameContent_5) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_5, EqualityOperator_DifferentContent_5) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_5, EqualityOperator_DifferentLengths_5) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_5, EqualityOperator_BothEmpty_5) {
    StringRef a;
    StringRef b("");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_5, EqualityOperator_OneEmptyOneNot_5) {
    StringRef a;
    StringRef b("x");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// ============================================================
// operator[]
// ============================================================

TEST(StringRefTest_5, IndexOperator_5) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[4], 'e');
}

// ============================================================
// empty() and size()
// ============================================================

TEST(StringRefTest_5, EmptyOnNonEmpty_5) {
    StringRef sr("notempty");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_5, SizeReturnsCorrectLength_5) {
    StringRef sr("12345");
    EXPECT_EQ(sr.size(), 5u);
}

// ============================================================
// data()
// ============================================================

TEST(StringRefTest_5, DataReturnsPointerToChars_5) {
    const char* raw = "hello";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// ============================================================
// substr()
// ============================================================

TEST(StringRefTest_5, SubstrFromStart_5) {
    StringRef sr("hello world");
    auto sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'h');
    EXPECT_EQ(sub[4], 'o');
}

TEST(StringRefTest_5, SubstrFromMiddle_5) {
    StringRef sr("hello world");
    auto sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
    EXPECT_EQ(sub[4], 'd');
}

TEST(StringRefTest_5, SubstrZeroLength_5) {
    StringRef sr("hello");
    auto sub = sr.substr(2, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

// ============================================================
// compare()
// ============================================================

TEST(StringRefTest_5, CompareEqual_5) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_5, CompareLessThan_5) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_5, CompareGreaterThan_5) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_5, CompareShorterVsLonger_5) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_5, CompareLongerVsShorter_5) {
    StringRef a("abcd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_5, CompareBothEmpty_5) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

// ============================================================
// operator<
// ============================================================

TEST(StringRefTest_5, LessThanOperator_True_5) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_5, LessThanOperator_False_5) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_5, LessThanOperator_Equal_5) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_5, LessThanOperator_PrefixIsShorter_5) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

// ============================================================
// Explicit conversion to std::string
// ============================================================

TEST(StringRefTest_5, ExplicitConversionToStdString_5) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_5, ExplicitConversionEmptyToStdString_5) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ============================================================
// operator+ (StringRef + StringRef)
// ============================================================

TEST(StringRefTest_5, PlusOperatorTwoStringRefs_5) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_5, PlusOperatorWithEmpty_5) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_5, PlusOperatorBothEmpty_5) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= (std::string += StringRef)
// ============================================================

TEST(StringRefTest_5, PlusEqualsOperator_5) {
    std::string s = "hello";
    StringRef sr(" world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_5, PlusEqualsOperatorEmptyStringRef_5) {
    std::string s = "hello";
    StringRef sr;
    s += sr;
    EXPECT_EQ(s, "hello");
}

// ============================================================
// operator<< (ostream)
// ============================================================

TEST(StringRefTest_5, StreamOutputOperator_5) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_5, StreamOutputOperatorEmpty_5) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ============================================================
// Iterators (begin/end)
// ============================================================

TEST(StringRefTest_5, BeginEndIteration_5) {
    StringRef sr("abc");
    std::string collected;
    for (auto it = sr.begin(); it != sr.end(); ++it) {
        collected += *it;
    }
    EXPECT_EQ(collected, "abc");
}

TEST(StringRefTest_5, BeginEqualsEndForEmpty_5) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_5, RangeBasedForLoop_5) {
    StringRef sr("xyz");
    std::string collected;
    for (char c : sr) {
        collected += c;
    }
    EXPECT_EQ(collected, "xyz");
}

// ============================================================
// Boundary: Single character
// ============================================================

TEST(StringRefTest_5, SingleCharacter_5) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
}

// ============================================================
// Interop: StringRef from std::string matches raw C-string
// ============================================================

TEST(StringRefTest_5, StdStringAndRawCStringEquality_5) {
    std::string s = "test123";
    StringRef a(s);
    StringRef b("test123");
    EXPECT_TRUE(a == b);
}

// ============================================================
// Substr with full length
// ============================================================

TEST(StringRefTest_5, SubstrFullLength_5) {
    StringRef sr("hello");
    auto sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == sr);
}

// ============================================================
// Compare with different string content but same prefix
// ============================================================

TEST(StringRefTest_5, CompareWithSamePrefix_5) {
    StringRef a("abcx");
    StringRef b("abcy");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

// ============================================================
// Self-equality
// ============================================================

TEST(StringRefTest_5, SelfEquality_5) {
    StringRef sr("self");
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
    EXPECT_EQ(sr.compare(sr), 0);
    EXPECT_FALSE(sr < sr);
}
