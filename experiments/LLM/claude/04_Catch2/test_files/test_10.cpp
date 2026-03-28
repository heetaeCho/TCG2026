#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// Default constructor tests
TEST(StringRefTest_10, DefaultConstructorCreatesEmptyString_10) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_10, DefaultConstructorDataNotNull_10) {
    StringRef sr;
    EXPECT_NE(sr.data(), nullptr);
}

// Constructor from raw C string
TEST(StringRefTest_10, ConstructFromCString_10) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_10, ConstructFromEmptyCString_10) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// Constructor from raw chars and size
TEST(StringRefTest_10, ConstructFromCStringAndSize_10) {
    const char* str = "hello world";
    StringRef sr(str, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr.data(), str);
}

// Constructor from std::string
TEST(StringRefTest_10, ConstructFromStdString_10) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_10, ConstructFromEmptyStdString_10) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// data() tests
TEST(StringRefTest_10, DataReturnsCorrectPointer_10) {
    const char* raw = "data test";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// operator[] tests
TEST(StringRefTest_10, IndexOperatorReturnsCorrectChar_10) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[5], 'f');
}

// empty() tests
TEST(StringRefTest_10, EmptyReturnsTrueForEmptyString_10) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_10, EmptyReturnsFalseForNonEmptyString_10) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

// size() tests
TEST(StringRefTest_10, SizeReturnsCorrectLength_10) {
    StringRef sr("twelve chars");
    EXPECT_EQ(sr.size(), 12u);
}

TEST(StringRefTest_10, SizeIsZeroForDefault_10) {
    StringRef sr;
    EXPECT_EQ(sr.size(), 0u);
}

// operator== tests
TEST(StringRefTest_10, EqualityOperatorSameContent_10) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_10, EqualityOperatorDifferentContent_10) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_10, EqualityOperatorDifferentLength_10) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_10, EqualityOperatorBothEmpty_10) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
}

// operator!= tests
TEST(StringRefTest_10, InequalityOperatorDifferentContent_10) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_10, InequalityOperatorSameContent_10) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_FALSE(a != b);
}

// operator< tests
TEST(StringRefTest_10, LessThanOperator_10) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_10, LessThanOperatorEqualStrings_10) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_10, LessThanOperatorPrefixIsShorter_10) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// compare() tests
TEST(StringRefTest_10, CompareEqualStrings_10) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_10, CompareLessThan_10) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_10, CompareGreaterThan_10) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_10, CompareDifferentLengths_10) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

// substr() tests
TEST(StringRefTest_10, SubstrFromBeginning_10) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST(StringRefTest_10, SubstrFromMiddle_10) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("world"));
}

TEST(StringRefTest_10, SubstrZeroLength_10) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

// explicit operator std::string() tests
TEST(StringRefTest_10, ExplicitConversionToStdString_10) {
    StringRef sr("convert me");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "convert me");
}

TEST(StringRefTest_10, ExplicitConversionEmptyToStdString_10) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// operator+ tests
TEST(StringRefTest_10, PlusOperatorConcatenates_10) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_10, PlusOperatorWithEmptyLeft_10) {
    StringRef a;
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "world");
}

TEST(StringRefTest_10, PlusOperatorWithEmptyRight_10) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_10, PlusOperatorBothEmpty_10) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// operator+= tests
TEST(StringRefTest_10, PlusEqualsAppendsToString_10) {
    std::string s = "hello ";
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_10, PlusEqualsWithEmptyStringRef_10) {
    std::string s = "hello";
    StringRef sr;
    s += sr;
    EXPECT_EQ(s, "hello");
}

// operator<< tests
TEST(StringRefTest_10, StreamOutputOperator_10) {
    StringRef sr("stream test");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "stream test");
}

TEST(StringRefTest_10, StreamOutputOperatorEmpty_10) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// begin/end iterator tests
TEST(StringRefTest_10, BeginEndIterators_10) {
    StringRef sr("abc");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_10, BeginEndIteratorsEmpty_10) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_10, IteratorDistance_10) {
    StringRef sr("hello");
    auto dist = std::distance(sr.begin(), sr.end());
    EXPECT_EQ(static_cast<size_t>(dist), sr.size());
}

// Boundary: single character string
TEST(StringRefTest_10, SingleCharString_10) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
}

// Boundary: construct with partial raw string and size
TEST(StringRefTest_10, PartialRawStringConstruction_10) {
    const char* raw = "hello world";
    StringRef sr(raw, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr, StringRef("hello"));
}

// Compare with std::string constructed StringRef
TEST(StringRefTest_10, StdStringAndCStringEquality_10) {
    std::string s = "test";
    StringRef fromStd(s);
    StringRef fromC("test");
    EXPECT_TRUE(fromStd == fromC);
}

// Substr with data pointer verification
TEST(StringRefTest_10, SubstrDataPointsIntoOriginal_10) {
    const char* raw = "hello world";
    StringRef sr(raw);
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.data(), raw + 6);
}

// Compare with itself
TEST(StringRefTest_10, CompareWithSelf_10) {
    StringRef sr("self");
    EXPECT_EQ(sr.compare(sr), 0);
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
    EXPECT_FALSE(sr < sr);
}

// Long string
TEST(StringRefTest_10, LongString_10) {
    std::string longStr(10000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
}

// Equality with different lengths but same prefix
TEST(StringRefTest_10, EqualityDifferentLengthSamePrefix_10) {
    StringRef a("abc");
    StringRef b("abcdef");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}
