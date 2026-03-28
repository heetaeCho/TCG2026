#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <string>
#include <sstream>

using Catch::StringRef;

// ============================
// Default Construction
// ============================
TEST(StringRefTest_12, DefaultConstructedIsEmpty_12) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_12, DefaultConstructedBeginEqualsEnd_12) {
    StringRef sr;
    EXPECT_EQ(sr.begin(), sr.end());
}

// ============================
// Construction from raw C string
// ============================
TEST(StringRefTest_12, ConstructFromRawCString_12) {
    StringRef sr("hello");
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_12, ConstructFromEmptyCString_12) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================
// Construction from raw chars with size
// ============================
TEST(StringRefTest_12, ConstructFromRawCharsAndSize_12) {
    const char* data = "hello world";
    StringRef sr(data, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[4], 'o');
}

// ============================
// Construction from std::string
// ============================
TEST(StringRefTest_12, ConstructFromStdString_12) {
    std::string s = "testing";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), 7u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_12, ConstructFromEmptyStdString_12) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================
// data()
// ============================
TEST(StringRefTest_12, DataReturnsPointerToChars_12) {
    const char* raw = "abc";
    StringRef sr(raw, 3);
    EXPECT_EQ(sr.data(), raw);
}

// ============================
// operator[]
// ============================
TEST(StringRefTest_12, SubscriptOperatorAccessesCorrectCharacter_12) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[1], 'b');
    EXPECT_EQ(sr[5], 'f');
}

// ============================
// begin() and end()
// ============================
TEST(StringRefTest_12, BeginEndIterateCorrectly_12) {
    StringRef sr("abc");
    std::string result;
    for (auto it = sr.begin(); it != sr.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_12, EndMinusBeginEqualsSize_12) {
    StringRef sr("hello");
    EXPECT_EQ(static_cast<size_t>(sr.end() - sr.begin()), sr.size());
}

// ============================
// empty()
// ============================
TEST(StringRefTest_12, EmptyReturnsTrueForEmptyString_12) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_12, EmptyReturnsFalseForNonEmptyString_12) {
    StringRef sr("x");
    EXPECT_FALSE(sr.empty());
}

// ============================
// size()
// ============================
TEST(StringRefTest_12, SizeReturnsCorrectLength_12) {
    StringRef sr("twelve chars");
    EXPECT_EQ(sr.size(), 12u);
}

TEST(StringRefTest_12, SizeIsZeroForDefaultConstructed_12) {
    StringRef sr;
    EXPECT_EQ(sr.size(), 0u);
}

// ============================
// substr()
// ============================
TEST(StringRefTest_12, SubstrReturnsCorrectSubstring_12) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
    EXPECT_EQ(sub[4], 'd');
}

TEST(StringRefTest_12, SubstrFromBeginning_12) {
    StringRef sr("abcdef");
    StringRef sub = sr.substr(0, 3);
    EXPECT_EQ(sub.size(), 3u);
    EXPECT_EQ(sub[0], 'a');
    EXPECT_EQ(sub[2], 'c');
}

TEST(StringRefTest_12, SubstrZeroLength_12) {
    StringRef sr("hello");
    StringRef sub = sr.substr(2, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

// ============================
// operator==
// ============================
TEST(StringRefTest_12, EqualityOperatorSameStrings_12) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_12, EqualityOperatorDifferentStrings_12) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_12, EqualityOperatorDifferentLengths_12) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_12, EqualityOperatorBothEmpty_12) {
    StringRef a;
    StringRef b("");
    EXPECT_TRUE(a == b);
}

// ============================
// operator!=
// ============================
TEST(StringRefTest_12, InequalityOperatorDifferentStrings_12) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_12, InequalityOperatorSameStrings_12) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_FALSE(a != b);
}

// ============================
// operator<
// ============================
TEST(StringRefTest_12, LessThanOperatorTrue_12) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_12, LessThanOperatorFalse_12) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_12, LessThanOperatorEqualStrings_12) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_12, LessThanPrefixIsShorter_12) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

// ============================
// compare()
// ============================
TEST(StringRefTest_12, CompareEqualStringsReturnsZero_12) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_12, CompareLessThanReturnsNegative_12) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_12, CompareGreaterThanReturnsPositive_12) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_12, CompareShorterPrefix_12) {
    StringRef a("abc");
    StringRef b("abcdef");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_12, CompareLongerPrefix_12) {
    StringRef a("abcdef");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_12, CompareBothEmpty_12) {
    StringRef a;
    StringRef b("");
    EXPECT_EQ(a.compare(b), 0);
}

// ============================
// explicit operator std::string()
// ============================
TEST(StringRefTest_12, ExplicitConversionToStdString_12) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_12, ExplicitConversionEmptyToStdString_12) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ============================
// operator+ (StringRef + StringRef)
// ============================
TEST(StringRefTest_12, PlusOperatorConcatenates_12) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_12, PlusOperatorWithEmptyLeft_12) {
    StringRef a("");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "world");
}

TEST(StringRefTest_12, PlusOperatorWithEmptyRight_12) {
    StringRef a("hello");
    StringRef b("");
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_12, PlusOperatorBothEmpty_12) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================
// operator+= (std::string += StringRef)
// ============================
TEST(StringRefTest_12, PlusEqualsAppendsToString_12) {
    std::string s = "hello";
    StringRef sr(" world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_12, PlusEqualsWithEmptyStringRef_12) {
    std::string s = "hello";
    StringRef sr("");
    s += sr;
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_12, PlusEqualsToEmptyString_12) {
    std::string s;
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "world");
}

// ============================
// operator<< (ostream)
// ============================
TEST(StringRefTest_12, StreamInsertionOperator_12) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_12, StreamInsertionOperatorEmpty_12) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ============================
// Boundary: single character string
// ============================
TEST(StringRefTest_12, SingleCharacterString_12) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'x');
    EXPECT_EQ(sr.begin() + 1, sr.end());
}

// ============================
// Boundary: substr full string
// ============================
TEST(StringRefTest_12, SubstrFullString_12) {
    StringRef sr("hello");
    StringRef sub = sr.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == sr);
}

// ============================
// Comparing StringRef constructed different ways
// ============================
TEST(StringRefTest_12, CompareStringRefFromDifferentSources_12) {
    std::string s = "hello";
    StringRef a(s);
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_EQ(a.compare(b), 0);
}

// ============================
// Partial StringRef via substr and comparison
// ============================
TEST(StringRefTest_12, SubstrComparedWithFullString_12) {
    StringRef sr("hello world");
    StringRef sub = sr.substr(0, 5);
    StringRef expected("hello");
    EXPECT_TRUE(sub == expected);
}

// ============================
// Large string
// ============================
TEST(StringRefTest_12, LargeString_12) {
    std::string large(10000, 'a');
    StringRef sr(large);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[9999], 'a');
}

// ============================
// end() specifically
// ============================
TEST(StringRefTest_12, EndPointsPastLastChar_12) {
    StringRef sr("abc");
    auto it = sr.end();
    --it;
    EXPECT_EQ(*it, 'c');
}

TEST(StringRefTest_12, EndForEmptyStringEqualsBegin_12) {
    StringRef sr;
    EXPECT_EQ(sr.end(), sr.begin());
}

TEST(StringRefTest_12, EndMinusBeginGivesSize_12) {
    StringRef sr("test string");
    EXPECT_EQ(static_cast<std::size_t>(sr.end() - sr.begin()), sr.size());
}
