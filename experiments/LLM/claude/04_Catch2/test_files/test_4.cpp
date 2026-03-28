#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <string>
#include <sstream>

using Catch::StringRef;

// ============================================================
// Default Construction
// ============================================================
TEST(StringRefTest_4, DefaultConstructedIsEmpty_4) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Construction from raw C-string
// ============================================================
TEST(StringRefTest_4, ConstructFromRawCString_4) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

// ============================================================
// Construction from raw C-string with explicit size
// ============================================================
TEST(StringRefTest_4, ConstructFromRawCStringWithSize_4) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr, StringRef("hello"));
}

// ============================================================
// Construction from std::string
// ============================================================
TEST(StringRefTest_4, ConstructFromStdString_4) {
    std::string s = "testing";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), 7u);
    EXPECT_FALSE(sr.empty());
}

// ============================================================
// Equality operator
// ============================================================
TEST(StringRefTest_4, EqualityOperator_SameStrings_4) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_4, EqualityOperator_DifferentStrings_4) {
    StringRef a("abc");
    StringRef b("def");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_4, EqualityOperator_DifferentLengths_4) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_4, EqualityOperator_BothEmpty_4) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_4, EqualityOperator_OneEmpty_4) {
    StringRef a;
    StringRef b("x");
    EXPECT_FALSE(a == b);
}

// ============================================================
// Inequality operator
// ============================================================
TEST(StringRefTest_4, InequalityOperator_4) {
    StringRef a("abc");
    StringRef b("xyz");
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != StringRef("abc"));
}

// ============================================================
// Subscript operator
// ============================================================
TEST(StringRefTest_4, SubscriptOperator_4) {
    StringRef sr("hello");
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[1], 'e');
    EXPECT_EQ(sr[4], 'o');
}

// ============================================================
// empty()
// ============================================================
TEST(StringRefTest_4, EmptyOnNonEmptyString_4) {
    StringRef sr("a");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_4, EmptyOnEmptyString_4) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
}

// ============================================================
// size()
// ============================================================
TEST(StringRefTest_4, SizeReturnsCorrectLength_4) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr.size(), 6u);
}

TEST(StringRefTest_4, SizeOfEmptyIsZero_4) {
    StringRef sr;
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// data()
// ============================================================
TEST(StringRefTest_4, DataReturnsPointerToContent_4) {
    const char* raw = "hello";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// ============================================================
// substr()
// ============================================================
TEST(StringRefTest_4, SubstrFromBeginning_4) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST(StringRefTest_4, SubstrFromMiddle_4) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("world"));
}

TEST(StringRefTest_4, SubstrZeroLength_4) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
}

// ============================================================
// begin() / end() iterators
// ============================================================
TEST(StringRefTest_4, BeginEndIterators_4) {
    StringRef sr("abc");
    std::string result;
    for (auto it = sr.begin(); it != sr.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_4, RangeBasedFor_4) {
    StringRef sr("xyz");
    std::string result;
    for (char c : sr) {
        result += c;
    }
    EXPECT_EQ(result, "xyz");
}

// ============================================================
// Explicit conversion to std::string
// ============================================================
TEST(StringRefTest_4, ExplicitConversionToStdString_4) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_4, ExplicitConversionEmptyToStdString_4) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ============================================================
// compare()
// ============================================================
TEST(StringRefTest_4, CompareEqual_4) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_4, CompareLessThan_4) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_4, CompareGreaterThan_4) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_4, CompareDifferentLengthPrefix_4) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_4, CompareDifferentLengthPrefixReverse_4) {
    StringRef a("abcd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_4, CompareBothEmpty_4) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

// ============================================================
// operator<
// ============================================================
TEST(StringRefTest_4, LessThanOperatorTrue_4) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_4, LessThanOperatorFalse_4) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_4, LessThanOperatorEqual_4) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_4, LessThanShorterPrefix_4) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

// ============================================================
// operator+ (StringRef + StringRef -> std::string)
// ============================================================
TEST(StringRefTest_4, PlusOperator_4) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_4, PlusOperatorWithEmpty_4) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_4, PlusOperatorBothEmpty_4) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= (std::string += StringRef)
// ============================================================
TEST(StringRefTest_4, PlusEqualsOperator_4) {
    std::string s = "hello ";
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_4, PlusEqualsEmptyStringRef_4) {
    std::string s = "hello";
    StringRef sr;
    s += sr;
    EXPECT_EQ(s, "hello");
}

// ============================================================
// operator<< (ostream)
// ============================================================
TEST(StringRefTest_4, OutputStreamOperator_4) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_4, OutputStreamOperatorEmpty_4) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ============================================================
// Boundary: Single character
// ============================================================
TEST(StringRefTest_4, SingleCharacterString_4) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
}

// ============================================================
// Boundary: Strings with embedded content treated as expected
// ============================================================
TEST(StringRefTest_4, ConstructFromExplicitSizeWithNullChar_4) {
    const char data[] = "ab\0cd";
    StringRef sr(data, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[2], '\0');
    EXPECT_EQ(sr[3], 'c');
}

// ============================================================
// Equality with embedded null differs from truncated version
// ============================================================
TEST(StringRefTest_4, EqualityWithEmbeddedNull_4) {
    const char data1[] = "ab\0cd";
    const char data2[] = "ab\0xy";
    StringRef a(data1, 5);
    StringRef b(data2, 5);
    // memcmp should detect difference at position 3
    EXPECT_FALSE(a == b);
}

// ============================================================
// Equality: same prefix different suffix
// ============================================================
TEST(StringRefTest_4, SamePrefixDifferentSuffix_4) {
    StringRef a("abcX");
    StringRef b("abcY");
    EXPECT_FALSE(a == b);
}

// ============================================================
// Large string
// ============================================================
TEST(StringRefTest_4, LargeString_4) {
    std::string large(10000, 'a');
    StringRef sr(large);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
    EXPECT_EQ(sr, StringRef(large));
}
