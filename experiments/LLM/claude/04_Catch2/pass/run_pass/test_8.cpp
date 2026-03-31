#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== Construction Tests ====================

TEST(StringRefTest_8, DefaultConstructorCreatesEmptyString_8) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_8, ConstructFromRawChars_8) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_8, ConstructFromRawCharsAndSize_8) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[4], 'o');
}

TEST(StringRefTest_8, ConstructFromStdString_8) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_8, ConstructFromEmptyRawChars_8) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_8, ConstructFromEmptyStdString_8) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ==================== Size and Empty Tests ====================

TEST(StringRefTest_8, SizeReturnsCorrectValue_8) {
    StringRef sr("abc");
    EXPECT_EQ(sr.size(), 3u);
}

TEST(StringRefTest_8, EmptyReturnsTrueForDefault_8) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_8, EmptyReturnsFalseForNonEmpty_8) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

// ==================== Subscript Operator Tests ====================

TEST(StringRefTest_8, SubscriptOperatorReturnsCorrectChar_8) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[5], 'f');
}

TEST(StringRefTest_8, SubscriptOperatorFirstChar_8) {
    StringRef sr("Z");
    EXPECT_EQ(sr[0], 'Z');
}

// ==================== Equality Operators ====================

TEST(StringRefTest_8, EqualityOperatorSameStrings_8) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_8, EqualityOperatorDifferentStrings_8) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_8, EqualityOperatorDifferentLengths_8) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_8, EqualityOperatorBothEmpty_8) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_8, EqualityOperatorEmptyVsNonEmpty_8) {
    StringRef a;
    StringRef b("x");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// ==================== Comparison and Less-Than Tests ====================

TEST(StringRefTest_8, LessThanOperator_8) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_8, LessThanOperatorSameStrings_8) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_8, LessThanOperatorPrefix_8) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_8, CompareReturnsZeroForEqual_8) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_8, CompareReturnsNegativeForLesser_8) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_8, CompareReturnsPositiveForGreater_8) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_8, CompareDifferentLengths_8) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

TEST(StringRefTest_8, CompareEmptyStrings_8) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_8, CompareEmptyVsNonEmpty_8) {
    StringRef a;
    StringRef b("x");
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

// ==================== Conversion Tests ====================

TEST(StringRefTest_8, ExplicitConversionToStdString_8) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_8, ExplicitConversionEmptyToStdString_8) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ==================== Data Tests ====================

TEST(StringRefTest_8, DataReturnsPointer_8) {
    const char* raw = "hello";
    StringRef sr(raw, 5);
    EXPECT_EQ(sr.data(), raw);
}

TEST(StringRefTest_8, DataForDefaultConstructed_8) {
    StringRef sr;
    EXPECT_NE(sr.data(), nullptr);
}

// ==================== Substr Tests ====================

TEST(StringRefTest_8, SubstrFullString_8) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == StringRef("hello"));
}

TEST(StringRefTest_8, SubstrPartial_8) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == StringRef("hello"));
}

TEST(StringRefTest_8, SubstrFromMiddle_8) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == StringRef("world"));
}

TEST(StringRefTest_8, SubstrZeroLength_8) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_8, SubstrSingleChar_8) {
    StringRef sr("hello");
    StringRef sub = sr.substr(1, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'e');
}

// ==================== Iterator Tests ====================

TEST(StringRefTest_8, BeginEndIterators_8) {
    StringRef sr("abc");
    auto it = sr.begin();
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(*it, 'c');
    ++it;
    EXPECT_EQ(it, sr.end());
}

TEST(StringRefTest_8, BeginEqualsEndForEmpty_8) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_8, RangeBasedForLoop_8) {
    StringRef sr("abc");
    std::string result;
    for (char c : sr) {
        result += c;
    }
    EXPECT_EQ(result, "abc");
}

// ==================== Concatenation Operator Tests ====================

TEST(StringRefTest_8, PlusOperatorConcatenation_8) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_8, PlusOperatorWithEmpty_8) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_8, PlusOperatorBothEmpty_8) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

TEST(StringRefTest_8, PlusEqualsOperator_8) {
    std::string lhs = "hello";
    StringRef rhs(" world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

TEST(StringRefTest_8, PlusEqualsOperatorWithEmpty_8) {
    std::string lhs = "hello";
    StringRef rhs;
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

// ==================== Stream Operator Tests ====================

TEST(StringRefTest_8, StreamOutputOperator_8) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_8, StreamOutputOperatorEmpty_8) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ==================== Boundary Tests ====================

TEST(StringRefTest_8, SingleCharacterString_8) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
    EXPECT_EQ(static_cast<std::string>(sr), "x");
}

TEST(StringRefTest_8, LongString_8) {
    std::string longStr(10000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
}

TEST(StringRefTest_8, StringWithNullCharactersViaSize_8) {
    const char data[] = "he\0lo";
    StringRef sr(data, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[2], '\0');
    EXPECT_EQ(sr[3], 'l');
}

// ==================== Copy and Assignment Tests ====================

TEST(StringRefTest_8, CopyConstruction_8) {
    StringRef a("hello");
    StringRef b(a);
    EXPECT_TRUE(a == b);
    EXPECT_EQ(a.size(), b.size());
}

TEST(StringRefTest_8, CopyAssignment_8) {
    StringRef a("hello");
    StringRef b;
    b = a;
    EXPECT_TRUE(a == b);
    EXPECT_EQ(a.size(), b.size());
}

TEST(StringRefTest_8, AssignDifferentValue_8) {
    StringRef a("hello");
    StringRef b("world");
    a = b;
    EXPECT_TRUE(a == StringRef("world"));
}
