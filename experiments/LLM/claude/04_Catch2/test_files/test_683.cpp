#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== Construction Tests ====================

TEST(StringRefTest_683, DefaultConstruction_683) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_683, ConstructFromRawString_683) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_683, ConstructFromRawStringAndSize_683) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(std::string(sr.data(), sr.size()), "hello");
}

TEST(StringRefTest_683, ConstructFromStdString_683) {
    std::string s = "testing";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_EQ(std::string(sr.data(), sr.size()), s);
}

TEST(StringRefTest_683, ConstructFromEmptyRawString_683) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_683, ConstructFromEmptyStdString_683) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ==================== Data Access Tests ====================

TEST(StringRefTest_683, DataReturnsPointer_683) {
    const char* raw = "test";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

TEST(StringRefTest_683, IndexOperator_683) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[5], 'f');
}

TEST(StringRefTest_683, BeginEnd_683) {
    StringRef sr("abc");
    EXPECT_EQ(sr.end() - sr.begin(), 3);
    EXPECT_EQ(*sr.begin(), 'a');
}

TEST(StringRefTest_683, BeginEndEmptyString_683) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

// ==================== Empty and Size Tests ====================

TEST(StringRefTest_683, EmptyReturnsTrueForDefault_683) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_683, EmptyReturnsFalseForNonEmpty_683) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_683, SizeReturnsCorrectValue_683) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
}

// ==================== Comparison Tests ====================

TEST(StringRefTest_683, EqualityOperator_SameStrings_683) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_683, EqualityOperator_DifferentStrings_683) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_683, EqualityOperator_DifferentLengths_683) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_683, EqualityOperator_BothEmpty_683) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_683, InequalityOperator_683) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_683, InequalityOperator_SameStrings_683) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_683, LessThanOperator_683) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_683, LessThanOperator_PrefixShorter_683) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_683, LessThanOperator_Equal_683) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_683, CompareEqual_683) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_683, CompareLessThan_683) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_683, CompareGreaterThan_683) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_683, CompareDifferentLengths_683) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

TEST(StringRefTest_683, CompareEmptyStrings_683) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_683, CompareEmptyWithNonEmpty_683) {
    StringRef a;
    StringRef b("hello");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

// ==================== Conversion Tests ====================

TEST(StringRefTest_683, ExplicitConversionToStdString_683) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_683, ExplicitConversionEmptyToStdString_683) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ==================== Substr Tests ====================

TEST(StringRefTest_683, SubstrFromBeginning_683) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(std::string(sub.data(), sub.size()), "hello");
}

TEST(StringRefTest_683, SubstrFromMiddle_683) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(std::string(sub.data(), sub.size()), "world");
}

TEST(StringRefTest_683, SubstrZeroLength_683) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_683, SubstrFullString_683) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(std::string(sub.data(), sub.size()), "hello");
}

// ==================== Stream Operator Tests ====================

TEST(StringRefTest_683, StreamOperator_683) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_683, StreamOperatorEmpty_683) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

TEST(StringRefTest_683, StreamOperatorWithPartialData_683) {
    StringRef sr("hello world", 5);
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

// ==================== Concatenation Tests ====================

TEST(StringRefTest_683, PlusOperator_683) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_683, PlusOperatorWithEmpty_683) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_683, PlusOperatorBothEmpty_683) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

TEST(StringRefTest_683, PlusEqualsOperator_683) {
    std::string lhs = "hello ";
    StringRef rhs("world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

TEST(StringRefTest_683, PlusEqualsOperatorWithEmpty_683) {
    std::string lhs = "hello";
    StringRef rhs;
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

// ==================== Iteration Tests ====================

TEST(StringRefTest_683, RangeBasedFor_683) {
    StringRef sr("abc");
    std::string result;
    for (char c : sr) {
        result += c;
    }
    EXPECT_EQ(result, "abc");
}

// ==================== Edge Case Tests ====================

TEST(StringRefTest_683, SingleCharacterString_683) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_EQ(sr[0], 'x');
}

TEST(StringRefTest_683, StringWithNullInMiddle_683) {
    // When constructed with explicit size, null characters should be preserved
    const char data[] = "he\0lo";
    StringRef sr(data, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[2], '\0');
    EXPECT_EQ(sr[3], 'l');
}

TEST(StringRefTest_683, EqualityWithStdStringConstruction_683) {
    std::string s = "test string";
    StringRef sr1(s);
    StringRef sr2("test string");
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefTest_683, CompareWithSelf_683) {
    StringRef sr("hello");
    EXPECT_EQ(sr.compare(sr), 0);
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
    EXPECT_FALSE(sr < sr);
}
