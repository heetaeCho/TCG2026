#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== Construction Tests ====================

TEST(StringRefTest_3, DefaultConstruction_IsEmpty_3) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_3, ConstructFromRawChars_3) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_3, ConstructFromRawCharsAndSize_3) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(std::string(sr), "hello");
}

TEST(StringRefTest_3, ConstructFromStdString_3) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_EQ(std::string(sr), s);
}

TEST(StringRefTest_3, ConstructFromEmptyRawChars_3) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_3, ConstructFromEmptyStdString_3) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ==================== Conversion Tests ====================

TEST(StringRefTest_3, ExplicitConversionToStdString_3) {
    StringRef sr("hello");
    std::string result = static_cast<std::string>(sr);
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_3, ExplicitConversionEmptyToStdString_3) {
    StringRef sr;
    std::string result = static_cast<std::string>(sr);
    EXPECT_EQ(result, "");
}

// ==================== Equality / Inequality Tests ====================

TEST(StringRefTest_3, EqualityOperator_SameStrings_3) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_3, EqualityOperator_DifferentStrings_3) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_3, EqualityOperator_DifferentLengths_3) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_3, EqualityOperator_BothEmpty_3) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_3, EqualityOperator_OneEmpty_3) {
    StringRef a("hello");
    StringRef b;
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// ==================== Comparison Tests ====================

TEST(StringRefTest_3, Compare_EqualStrings_3) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_3, Compare_LessThan_3) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_3, Compare_GreaterThan_3) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_3, Compare_Prefix_3) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_3, Compare_LongerVsShorter_3) {
    StringRef a("abcd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_3, Compare_BothEmpty_3) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

// ==================== Less-Than Operator Tests ====================

TEST(StringRefTest_3, LessThanOperator_True_3) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_3, LessThanOperator_False_3) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_3, LessThanOperator_Equal_3) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_3, LessThanOperator_PrefixIsShorter_3) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

// ==================== Subscript Operator Tests ====================

TEST(StringRefTest_3, SubscriptOperator_FirstChar_3) {
    StringRef sr("hello");
    EXPECT_EQ(sr[0], 'h');
}

TEST(StringRefTest_3, SubscriptOperator_LastChar_3) {
    StringRef sr("hello");
    EXPECT_EQ(sr[4], 'o');
}

TEST(StringRefTest_3, SubscriptOperator_MiddleChar_3) {
    StringRef sr("hello");
    EXPECT_EQ(sr[2], 'l');
}

// ==================== Empty and Size Tests ====================

TEST(StringRefTest_3, Empty_DefaultConstructed_3) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_3, Empty_NonEmptyString_3) {
    StringRef sr("a");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_3, Size_ReturnsCorrectSize_3) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_3, Size_SingleChar_3) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
}

// ==================== Data Tests ====================

TEST(StringRefTest_3, Data_ReturnsPointerToChars_3) {
    const char* raw = "hello";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

TEST(StringRefTest_3, Data_ContentIsCorrect_3) {
    StringRef sr("hello");
    EXPECT_EQ(std::string(sr.data(), sr.size()), "hello");
}

// ==================== Substr Tests ====================

TEST(StringRefTest_3, Substr_FullString_3) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(std::string(sub), "hello");
}

TEST(StringRefTest_3, Substr_PartialFromStart_3) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 3);
    EXPECT_EQ(std::string(sub), "hel");
}

TEST(StringRefTest_3, Substr_PartialFromMiddle_3) {
    StringRef sr("hello");
    StringRef sub = sr.substr(2, 3);
    EXPECT_EQ(std::string(sub), "llo");
}

TEST(StringRefTest_3, Substr_ZeroLength_3) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_3, Substr_SingleChar_3) {
    StringRef sr("hello");
    StringRef sub = sr.substr(1, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'e');
}

// ==================== Iterator Tests ====================

TEST(StringRefTest_3, BeginEndIterator_CorrectRange_3) {
    StringRef sr("hello");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_3, BeginEndIterator_EmptyString_3) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_3, BeginEndIterator_Distance_3) {
    StringRef sr("test");
    EXPECT_EQ(std::distance(sr.begin(), sr.end()), 4);
}

// ==================== Concatenation Operator Tests ====================

TEST(StringRefTest_3, PlusOperator_TwoStrings_3) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_3, PlusOperator_EmptyAndNonEmpty_3) {
    StringRef a;
    StringRef b("hello");
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_3, PlusOperator_NonEmptyAndEmpty_3) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_3, PlusOperator_BothEmpty_3) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ==================== += Operator Tests ====================

TEST(StringRefTest_3, PlusEqualsOperator_AppendsToString_3) {
    std::string lhs = "hello";
    StringRef rhs(" world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

TEST(StringRefTest_3, PlusEqualsOperator_AppendEmpty_3) {
    std::string lhs = "hello";
    StringRef rhs;
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

TEST(StringRefTest_3, PlusEqualsOperator_AppendToEmpty_3) {
    std::string lhs;
    StringRef rhs("hello");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

// ==================== Stream Operator Tests ====================

TEST(StringRefTest_3, StreamOperator_OutputsCorrectly_3) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_3, StreamOperator_EmptyString_3) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ==================== Boundary / Edge Case Tests ====================

TEST(StringRefTest_3, SingleCharacterString_3) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_EQ(sr[0], 'x');
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(std::string(sr), "x");
}

TEST(StringRefTest_3, LongString_3) {
    std::string longStr(1000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 1000u);
    EXPECT_EQ(std::string(sr), longStr);
}

TEST(StringRefTest_3, StringWithNullInMiddle_SizeFromConstructor_3) {
    // When constructed with explicit size, null bytes should be included
    StringRef sr("hel\0lo", 6);
    EXPECT_EQ(sr.size(), 6u);
}

TEST(StringRefTest_3, CopySemantics_3) {
    StringRef original("hello");
    StringRef copy = original;
    EXPECT_EQ(copy, original);
    EXPECT_EQ(std::string(copy), "hello");
}

TEST(StringRefTest_3, CompareWithSelf_3) {
    StringRef sr("hello");
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
    EXPECT_FALSE(sr < sr);
    EXPECT_EQ(sr.compare(sr), 0);
}
