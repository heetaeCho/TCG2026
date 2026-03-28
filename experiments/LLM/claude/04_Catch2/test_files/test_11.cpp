#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== Construction Tests ====================

TEST(StringRefTest_11, DefaultConstructor_EmptyString_11) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_11, ConstructFromRawChars_11) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_11, ConstructFromRawCharsAndSize_11) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[4], 'o');
}

TEST(StringRefTest_11, ConstructFromStdString_11) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_11, ConstructFromEmptyRawChars_11) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_11, ConstructFromEmptyStdString_11) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ==================== Size and Empty Tests ====================

TEST(StringRefTest_11, SizeReturnsCorrectLength_11) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr.size(), 6u);
}

TEST(StringRefTest_11, EmptyReturnsTrueForEmptyString_11) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_11, EmptyReturnsFalseForNonEmptyString_11) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

// ==================== Data and Access Tests ====================

TEST(StringRefTest_11, DataReturnsPointer_11) {
    const char* raw = "hello";
    StringRef sr(raw, 5);
    EXPECT_EQ(sr.data(), raw);
}

TEST(StringRefTest_11, SubscriptOperator_11) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[2], 'c');
    EXPECT_EQ(sr[3], 'd');
    EXPECT_EQ(sr[4], 'e');
}

// ==================== Iterator Tests ====================

TEST(StringRefTest_11, BeginEndIterators_11) {
    StringRef sr("hello");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_11, BeginEqualsEndForEmpty_11) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_11, IteratorDistance_11) {
    StringRef sr("test");
    EXPECT_EQ(std::distance(sr.begin(), sr.end()), 4);
}

// ==================== Comparison Tests ====================

TEST(StringRefTest_11, EqualityOperator_SameStrings_11) {
    StringRef sr1("hello");
    StringRef sr2("hello");
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefTest_11, EqualityOperator_DifferentStrings_11) {
    StringRef sr1("hello");
    StringRef sr2("world");
    EXPECT_FALSE(sr1 == sr2);
}

TEST(StringRefTest_11, EqualityOperator_DifferentLengths_11) {
    StringRef sr1("hello");
    StringRef sr2("hell");
    EXPECT_FALSE(sr1 == sr2);
}

TEST(StringRefTest_11, EqualityOperator_BothEmpty_11) {
    StringRef sr1;
    StringRef sr2;
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefTest_11, InequalityOperator_DifferentStrings_11) {
    StringRef sr1("hello");
    StringRef sr2("world");
    EXPECT_TRUE(sr1 != sr2);
}

TEST(StringRefTest_11, InequalityOperator_SameStrings_11) {
    StringRef sr1("hello");
    StringRef sr2("hello");
    EXPECT_FALSE(sr1 != sr2);
}

TEST(StringRefTest_11, LessThanOperator_11) {
    StringRef sr1("abc");
    StringRef sr2("abd");
    EXPECT_TRUE(sr1 < sr2);
    EXPECT_FALSE(sr2 < sr1);
}

TEST(StringRefTest_11, LessThanOperator_SameString_11) {
    StringRef sr1("abc");
    StringRef sr2("abc");
    EXPECT_FALSE(sr1 < sr2);
}

TEST(StringRefTest_11, LessThanOperator_PrefixIsShorter_11) {
    StringRef sr1("abc");
    StringRef sr2("abcd");
    EXPECT_TRUE(sr1 < sr2);
    EXPECT_FALSE(sr2 < sr1);
}

TEST(StringRefTest_11, CompareEqual_11) {
    StringRef sr1("hello");
    StringRef sr2("hello");
    EXPECT_EQ(sr1.compare(sr2), 0);
}

TEST(StringRefTest_11, CompareLessThan_11) {
    StringRef sr1("abc");
    StringRef sr2("abd");
    EXPECT_LT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_11, CompareGreaterThan_11) {
    StringRef sr1("abd");
    StringRef sr2("abc");
    EXPECT_GT(sr1.compare(sr2), 0);
}

TEST(StringRefTest_11, CompareDifferentLengths_11) {
    StringRef sr1("abc");
    StringRef sr2("abcd");
    EXPECT_LT(sr1.compare(sr2), 0);
    EXPECT_GT(sr2.compare(sr1), 0);
}

TEST(StringRefTest_11, CompareEmptyStrings_11) {
    StringRef sr1;
    StringRef sr2;
    EXPECT_EQ(sr1.compare(sr2), 0);
}

TEST(StringRefTest_11, CompareEmptyVsNonEmpty_11) {
    StringRef sr1;
    StringRef sr2("a");
    EXPECT_LT(sr1.compare(sr2), 0);
    EXPECT_GT(sr2.compare(sr1), 0);
}

// ==================== Substr Tests ====================

TEST(StringRefTest_11, SubstrFullString_11) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST(StringRefTest_11, SubstrPartial_11) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST(StringRefTest_11, SubstrFromMiddle_11) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("world"));
}

TEST(StringRefTest_11, SubstrZeroLength_11) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_11, SubstrSingleChar_11) {
    StringRef sr("hello");
    StringRef sub = sr.substr(1, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'e');
}

// ==================== Conversion Tests ====================

TEST(StringRefTest_11, ExplicitConversionToStdString_11) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_11, ExplicitConversionToStdString_Empty_11) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ==================== Operator+ Tests ====================

TEST(StringRefTest_11, PlusOperatorTwoStringRefs_11) {
    StringRef sr1("hello ");
    StringRef sr2("world");
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_11, PlusOperatorWithEmptyStringRef_11) {
    StringRef sr1("hello");
    StringRef sr2;
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_11, PlusOperatorBothEmpty_11) {
    StringRef sr1;
    StringRef sr2;
    std::string result = sr1 + sr2;
    EXPECT_EQ(result, "");
}

// ==================== Operator+= Tests ====================

TEST(StringRefTest_11, PlusEqualsOperator_11) {
    std::string s = "hello ";
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_11, PlusEqualsOperatorWithEmpty_11) {
    std::string s = "hello";
    StringRef sr;
    s += sr;
    EXPECT_EQ(s, "hello");
}

// ==================== Operator<< Tests ====================

TEST(StringRefTest_11, StreamInsertionOperator_11) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_11, StreamInsertionOperator_Empty_11) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ==================== Boundary Tests ====================

TEST(StringRefTest_11, SingleCharacterString_11) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_EQ(sr[0], 'x');
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_11, LongString_11) {
    std::string longStr(1000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 1000u);
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[999], 'a');
}

TEST(StringRefTest_11, StringWithNullCharInMiddle_11) {
    // Construct with explicit size to include null character
    const char data[] = "hel\0lo";
    StringRef sr(data, 6);
    EXPECT_EQ(sr.size(), 6u);
    EXPECT_EQ(sr[3], '\0');
    EXPECT_EQ(sr[4], 'l');
}

TEST(StringRefTest_11, EqualityWithDifferentSourcesSameContent_11) {
    std::string s = "hello";
    const char* raw = "hello";
    StringRef sr1(s);
    StringRef sr2(raw);
    EXPECT_TRUE(sr1 == sr2);
}

TEST(StringRefTest_11, SubstrDataPointsIntoOriginal_11) {
    const char* raw = "hello world";
    StringRef sr(raw);
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.data(), raw + 6);
}

TEST(StringRefTest_11, CopySemantics_11) {
    StringRef sr1("hello");
    StringRef sr2 = sr1;
    EXPECT_EQ(sr1, sr2);
    EXPECT_EQ(sr1.size(), sr2.size());
    EXPECT_EQ(sr1.data(), sr2.data());
}
