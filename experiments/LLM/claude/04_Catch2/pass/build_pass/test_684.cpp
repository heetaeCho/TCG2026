#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ============================================================
// Default Construction Tests
// ============================================================

TEST(StringRefTest_684, DefaultConstructorCreatesEmptyStringRef_684) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from raw C-string
// ============================================================

TEST(StringRefTest_684, ConstructFromRawCString_684) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_684, ConstructFromEmptyCString_684) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from std::string
// ============================================================

TEST(StringRefTest_684, ConstructFromStdString_684) {
    std::string s = "world";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_684, ConstructFromEmptyStdString_684) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from raw pointer + size
// ============================================================

TEST(StringRefTest_684, ConstructFromRawPointerAndSize_684) {
    const char* data = "abcdef";
    StringRef sr(data, 3);
    EXPECT_EQ(sr.size(), 3u);
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[2], 'c');
}

// ============================================================
// Equality / Inequality
// ============================================================

TEST(StringRefTest_684, EqualityOperatorSameContent_684) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_684, EqualityOperatorDifferentContent_684) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_684, EqualityOperatorDifferentLength_684) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_684, EqualityBothEmpty_684) {
    StringRef a;
    StringRef b("");
    EXPECT_TRUE(a == b);
}

// ============================================================
// Subscript operator
// ============================================================

TEST(StringRefTest_684, SubscriptOperator_684) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[4], 'e');
}

// ============================================================
// data()
// ============================================================

TEST(StringRefTest_684, DataReturnsPointer_684) {
    const char* raw = "test";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// ============================================================
// empty() and size()
// ============================================================

TEST(StringRefTest_684, EmptyReturnsTrueForEmptyRef_684) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_684, EmptyReturnsFalseForNonEmptyRef_684) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_684, SizeReturnsCorrectLength_684) {
    StringRef sr("testing");
    EXPECT_EQ(sr.size(), 7u);
}

// ============================================================
// substr()
// ============================================================

TEST(StringRefTest_684, SubstrFromStart_684) {
    StringRef sr("hello world");
    auto sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'h');
    EXPECT_EQ(sub[4], 'o');
}

TEST(StringRefTest_684, SubstrFromMiddle_684) {
    StringRef sr("hello world");
    auto sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
    EXPECT_EQ(sub[4], 'd');
}

TEST(StringRefTest_684, SubstrZeroLength_684) {
    StringRef sr("hello");
    auto sub = sr.substr(2, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

// ============================================================
// compare()
// ============================================================

TEST(StringRefTest_684, CompareEqual_684) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_684, CompareLessThan_684) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_684, CompareGreaterThan_684) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_684, CompareDifferentLengthsShorterFirst_684) {
    StringRef a("ab");
    StringRef b("abc");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_684, CompareDifferentLengthsLongerFirst_684) {
    StringRef a("abc");
    StringRef b("ab");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_684, CompareBothEmpty_684) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

// ============================================================
// operator<
// ============================================================

TEST(StringRefTest_684, LessThanOperatorTrue_684) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_684, LessThanOperatorFalse_684) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_684, LessThanOperatorEqual_684) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_684, LessThanShorterString_684) {
    StringRef a("ab");
    StringRef b("abc");
    EXPECT_TRUE(a < b);
}

// ============================================================
// operator+ (free function)
// ============================================================

TEST(StringRefTest_684, OperatorPlusConcatenation_684) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_684, OperatorPlusEmptyLhs_684) {
    StringRef a("");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "world");
}

TEST(StringRefTest_684, OperatorPlusEmptyRhs_684) {
    StringRef a("hello");
    StringRef b("");
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_684, OperatorPlusBothEmpty_684) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= (std::string += StringRef)
// ============================================================

TEST(StringRefTest_684, OperatorPlusEqualsAppends_684) {
    std::string s = "hello";
    StringRef sr(" world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_684, OperatorPlusEqualsEmptyStringRef_684) {
    std::string s = "hello";
    StringRef sr("");
    s += sr;
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_684, OperatorPlusEqualsToEmptyString_684) {
    std::string s;
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "world");
}

// ============================================================
// operator<< (ostream)
// ============================================================

TEST(StringRefTest_684, StreamOutputOperator_684) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_684, StreamOutputOperatorEmpty_684) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ============================================================
// Explicit conversion to std::string
// ============================================================

TEST(StringRefTest_684, ExplicitConversionToStdString_684) {
    StringRef sr("convert me");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "convert me");
}

TEST(StringRefTest_684, ExplicitConversionEmptyToStdString_684) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ============================================================
// begin() / end() iterators
// ============================================================

TEST(StringRefTest_684, BeginEndIterators_684) {
    StringRef sr("abc");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_684, BeginEndForEmpty_684) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_684, IteratorDistance_684) {
    StringRef sr("test");
    auto dist = std::distance(sr.begin(), sr.end());
    EXPECT_EQ(static_cast<size_t>(dist), sr.size());
}

// ============================================================
// Boundary: Single character StringRef
// ============================================================

TEST(StringRefTest_684, SingleCharacter_684) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
}

// ============================================================
// Boundary: Very long string
// ============================================================

TEST(StringRefTest_684, LongString_684) {
    std::string longStr(10000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
}

// ============================================================
// Concatenation result size correctness
// ============================================================

TEST(StringRefTest_684, ConcatenationResultSize_684) {
    StringRef a("abc");
    StringRef b("defgh");
    std::string result = a + b;
    EXPECT_EQ(result.size(), 8u);
    EXPECT_EQ(result, "abcdefgh");
}

// ============================================================
// Compare with prefix
// ============================================================

TEST(StringRefTest_684, CompareWithPrefix_684) {
    StringRef a("abcd");
    StringRef b("abcde");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

// ============================================================
// StringRef from std::string retains correct data
// ============================================================

TEST(StringRefTest_684, StdStringConstructionCorrectData_684) {
    std::string s = "Hello, World!";
    StringRef sr(s);
    for (size_t i = 0; i < s.size(); ++i) {
        EXPECT_EQ(sr[i], s[i]);
    }
}

// ============================================================
// Substr at end of string
// ============================================================

TEST(StringRefTest_684, SubstrAtEnd_684) {
    StringRef sr("abcdef");
    auto sub = sr.substr(3, 3);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub[0], 'd');
    EXPECT_EQ(sub[1], 'e');
    EXPECT_EQ(sub[2], 'f');
}

// ============================================================
// Equality between StringRef from different sources
// ============================================================

TEST(StringRefTest_684, EqualityFromDifferentSources_684) {
    const char* raw = "test";
    std::string stdStr = "test";
    StringRef a(raw);
    StringRef b(stdStr);
    EXPECT_TRUE(a == b);
    EXPECT_EQ(a.compare(b), 0);
}
