#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== Construction Tests ====================

TEST(StringRefTest_685, DefaultConstruction_685) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_685, ConstructFromRawChars_685) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_685, ConstructFromRawCharsAndSize_685) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(std::string(sr), "hello");
}

TEST(StringRefTest_685, ConstructFromStdString_685) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_EQ(std::string(sr), s);
}

TEST(StringRefTest_685, ConstructFromEmptyRawChars_685) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_685, ConstructFromEmptyStdString_685) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ==================== empty() and size() Tests ====================

TEST(StringRefTest_685, EmptyReturnsTrueForDefault_685) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_685, EmptyReturnsFalseForNonEmpty_685) {
    StringRef sr("a");
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_685, SizeReturnsCorrectLength_685) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr.size(), 6u);
}

// ==================== data() Tests ====================

TEST(StringRefTest_685, DataReturnsValidPointer_685) {
    const char* raw = "hello";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

// ==================== operator[] Tests ====================

TEST(StringRefTest_685, SubscriptOperatorReturnsCorrectChar_685) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[4], 'e');
}

// ==================== Equality and Inequality Tests ====================

TEST(StringRefTest_685, EqualityOperatorSameContent_685) {
    StringRef sr1("hello");
    StringRef sr2("hello");
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefTest_685, EqualityOperatorDifferentContent_685) {
    StringRef sr1("hello");
    StringRef sr2("world");
    EXPECT_FALSE(sr1 == sr2);
}

TEST(StringRefTest_685, EqualityOperatorDifferentLengths_685) {
    StringRef sr1("hello");
    StringRef sr2("hell");
    EXPECT_FALSE(sr1 == sr2);
}

TEST(StringRefTest_685, InequalityOperator_685) {
    StringRef sr1("hello");
    StringRef sr2("world");
    EXPECT_TRUE(sr1 != sr2);
}

TEST(StringRefTest_685, InequalityOperatorSameContent_685) {
    StringRef sr1("hello");
    StringRef sr2("hello");
    EXPECT_FALSE(sr1 != sr2);
}

TEST(StringRefTest_685, EqualityBothEmpty_685) {
    StringRef sr1;
    StringRef sr2;
    EXPECT_TRUE(sr1 == sr2);
}

// ==================== compare() Tests ====================

TEST(StringRefTest_685, CompareEqualStrings_685) {
    StringRef sr1("abc");
    StringRef sr2("abc");
    EXPECT_EQ(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareLessThan_685) {
    StringRef sr1("abc");
    StringRef sr2("abd");
    EXPECT_LT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareGreaterThan_685) {
    StringRef sr1("abd");
    StringRef sr2("abc");
    EXPECT_GT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareShorterPrefix_685) {
    StringRef sr1("abc");
    StringRef sr2("abcd");
    EXPECT_LT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareLongerPrefix_685) {
    StringRef sr1("abcd");
    StringRef sr2("abc");
    EXPECT_GT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareEmptyStrings_685) {
    StringRef sr1;
    StringRef sr2;
    EXPECT_EQ(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareEmptyWithNonEmpty_685) {
    StringRef sr1;
    StringRef sr2("abc");
    EXPECT_LT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_685, CompareNonEmptyWithEmpty_685) {
    StringRef sr1("abc");
    StringRef sr2;
    EXPECT_GT(sr1.compare(sr2), 0);
}

// ==================== operator< Tests ====================

TEST(StringRefTest_685, LessThanOperatorTrue_685) {
    StringRef sr1("abc");
    StringRef sr2("abd");
    EXPECT_TRUE(sr1 < sr2);
}

TEST(StringRefTest_685, LessThanOperatorFalse_685) {
    StringRef sr1("abd");
    StringRef sr2("abc");
    EXPECT_FALSE(sr1 < sr2);
}

TEST(StringRefTest_685, LessThanOperatorEqual_685) {
    StringRef sr1("abc");
    StringRef sr2("abc");
    EXPECT_FALSE(sr1 < sr2);
}

TEST(StringRefTest_685, LessThanShorterString_685) {
    StringRef sr1("abc");
    StringRef sr2("abcd");
    EXPECT_TRUE(sr1 < sr2);
}

// ==================== substr() Tests ====================

TEST(StringRefTest_685, SubstrFromBeginning_685) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(std::string(sub), "hello");
}

TEST(StringRefTest_685, SubstrFromMiddle_685) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(std::string(sub), "world");
}

TEST(StringRefTest_685, SubstrZeroLength_685) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_685, SubstrEntireString_685) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(std::string(sub), "hello");
}

// ==================== Explicit conversion to std::string ====================

TEST(StringRefTest_685, ExplicitConversionToString_685) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_685, ExplicitConversionEmptyToString_685) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ==================== operator+= Tests ====================

TEST(StringRefTest_685, PlusEqualsAppendsToString_685) {
    std::string lhs = "hello ";
    StringRef rhs("world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

TEST(StringRefTest_685, PlusEqualsWithEmptyStringRef_685) {
    std::string lhs = "hello";
    StringRef rhs;
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

TEST(StringRefTest_685, PlusEqualsWithEmptyLhs_685) {
    std::string lhs;
    StringRef rhs("world");
    lhs += rhs;
    EXPECT_EQ(lhs, "world");
}

TEST(StringRefTest_685, PlusEqualsReturnsSameString_685) {
    std::string lhs = "hello";
    StringRef rhs(" world");
    std::string& result = (lhs += rhs);
    EXPECT_EQ(&result, &lhs);
    EXPECT_EQ(result, "hello world");
}

// ==================== operator+ Tests ====================

TEST(StringRefTest_685, PlusOperatorConcatenates_685) {
    StringRef sr1("hello ");
    StringRef sr2("world");
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_685, PlusOperatorBothEmpty_685) {
    StringRef sr1;
    StringRef sr2;
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "");
}

TEST(StringRefTest_685, PlusOperatorOneEmpty_685) {
    StringRef sr1("hello");
    StringRef sr2;
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "hello");
}

// ==================== operator<< Tests ====================

TEST(StringRefTest_685, StreamInsertionOperator_685) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_685, StreamInsertionEmpty_685) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ==================== Iterator Tests ====================

TEST(StringRefTest_685, BeginEndIterators_685) {
    StringRef sr("abc");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_685, BeginEqualsEndForEmpty_685) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_685, IteratorDistance_685) {
    StringRef sr("hello");
    EXPECT_EQ(std::distance(sr.begin(), sr.end()), 5);
}

// ==================== Cross-construction equality ====================

TEST(StringRefTest_685, StdStringAndRawCharEquality_685) {
    std::string s = "test";
    StringRef sr1(s);
    StringRef sr2("test");
    EXPECT_TRUE(sr1 == sr2);
}

// ==================== Single character string ====================

TEST(StringRefTest_685, SingleCharacterString_685) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
}

// ==================== Boundary: very large string ====================

TEST(StringRefTest_685, LargeString_685) {
    std::string large(10000, 'a');
    StringRef sr(large);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
}

// ==================== SubStr with partial size ====================

TEST(StringRefTest_685, SubstrSingleChar_685) {
    StringRef sr("abcde");
    StringRef sub = sr.substr(2, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'c');
}

// ==================== Compare with itself ====================

TEST(StringRefTest_685, CompareWithSelf_685) {
    StringRef sr("hello");
    EXPECT_EQ(sr.compare(sr), 0);
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
    EXPECT_FALSE(sr < sr);
}
