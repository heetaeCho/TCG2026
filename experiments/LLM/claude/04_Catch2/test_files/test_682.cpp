#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ============================================================
// compare() tests
// ============================================================

TEST(StringRefCompareTest_682, EqualStringsReturnZero_682) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, FirstLessThanSecondLexicographically_682) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, FirstGreaterThanSecondLexicographically_682) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, ShorterStringIsLessWhenPrefixMatches_682) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, LongerStringIsGreaterWhenPrefixMatches_682) {
    StringRef a("abcd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, EmptyStringsAreEqual_682) {
    StringRef a("");
    StringRef b("");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, EmptyVsNonEmptyIsLess_682) {
    StringRef a("");
    StringRef b("a");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, NonEmptyVsEmptyIsGreater_682) {
    StringRef a("a");
    StringRef b("");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, SingleCharacterEqual_682) {
    StringRef a("x");
    StringRef b("x");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, SingleCharacterLess_682) {
    StringRef a("a");
    StringRef b("b");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, SingleCharacterGreater_682) {
    StringRef a("z");
    StringRef b("a");
    EXPECT_GT(a.compare(b), 0);
}

// ============================================================
// Constructor tests
// ============================================================

TEST(StringRefConstructorTest_682, DefaultConstructorCreatesEmptyRef_682) {
    StringRef s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(StringRefConstructorTest_682, ConstructFromCString_682) {
    StringRef s("hello");
    EXPECT_EQ(s.size(), 5u);
    EXPECT_FALSE(s.empty());
}

TEST(StringRefConstructorTest_682, ConstructFromStdString_682) {
    std::string str = "world";
    StringRef s(str);
    EXPECT_EQ(s.size(), 5u);
    EXPECT_FALSE(s.empty());
}

TEST(StringRefConstructorTest_682, ConstructFromCStringWithSize_682) {
    const char* raw = "hello world";
    StringRef s(raw, 5);
    EXPECT_EQ(s.size(), 5u);
}

TEST(StringRefConstructorTest_682, ConstructFromEmptyCString_682) {
    StringRef s("");
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

// ============================================================
// Equality and inequality operators
// ============================================================

TEST(StringRefEqualityTest_682, EqualStrings_682) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefEqualityTest_682, DifferentStrings_682) {
    StringRef a("foo");
    StringRef b("bar");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefEqualityTest_682, DifferentLengths_682) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefEqualityTest_682, BothEmpty_682) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

// ============================================================
// operator< tests
// ============================================================

TEST(StringRefLessThanTest_682, LexicographicallyLess_682) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessThanTest_682, PrefixIsShorter_682) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThanTest_682, EqualStringsNotLess_682) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThanTest_682, EmptyLessThanNonEmpty_682) {
    StringRef a("");
    StringRef b("a");
    EXPECT_TRUE(a < b);
}

// ============================================================
// operator[] tests
// ============================================================

TEST(StringRefIndexTest_682, AccessFirstChar_682) {
    StringRef s("hello");
    EXPECT_EQ(s[0], 'h');
}

TEST(StringRefIndexTest_682, AccessLastChar_682) {
    StringRef s("hello");
    EXPECT_EQ(s[4], 'o');
}

TEST(StringRefIndexTest_682, AccessMiddleChar_682) {
    StringRef s("hello");
    EXPECT_EQ(s[2], 'l');
}

// ============================================================
// empty() and size() tests
// ============================================================

TEST(StringRefSizeTest_682, NonEmptyString_682) {
    StringRef s("test");
    EXPECT_EQ(s.size(), 4u);
    EXPECT_FALSE(s.empty());
}

TEST(StringRefSizeTest_682, EmptyString_682) {
    StringRef s("");
    EXPECT_EQ(s.size(), 0u);
    EXPECT_TRUE(s.empty());
}

TEST(StringRefSizeTest_682, DefaultConstructedIsEmpty_682) {
    StringRef s;
    EXPECT_EQ(s.size(), 0u);
    EXPECT_TRUE(s.empty());
}

// ============================================================
// data() tests
// ============================================================

TEST(StringRefDataTest_682, DataPointsToContent_682) {
    const char* raw = "hello";
    StringRef s(raw);
    EXPECT_EQ(s.data(), raw);
}

// ============================================================
// substr() tests
// ============================================================

TEST(StringRefSubstrTest_682, SubstrFromBeginning_682) {
    StringRef s("hello world");
    StringRef sub = s.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'h');
    EXPECT_EQ(sub[4], 'o');
}

TEST(StringRefSubstrTest_682, SubstrFromMiddle_682) {
    StringRef s("hello world");
    StringRef sub = s.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
}

TEST(StringRefSubstrTest_682, SubstrZeroLength_682) {
    StringRef s("hello");
    StringRef sub = s.substr(0, 0);
    EXPECT_EQ(sub.size(), 0u);
    EXPECT_TRUE(sub.empty());
}

// ============================================================
// begin() and end() tests
// ============================================================

TEST(StringRefIteratorTest_682, BeginEndDistance_682) {
    StringRef s("hello");
    auto dist = s.end() - s.begin();
    EXPECT_EQ(dist, 5);
}

TEST(StringRefIteratorTest_682, EmptyStringBeginEqualsEnd_682) {
    StringRef s;
    EXPECT_EQ(s.begin(), s.end());
}

TEST(StringRefIteratorTest_682, IterateOverContent_682) {
    StringRef s("abc");
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// ============================================================
// Explicit conversion to std::string
// ============================================================

TEST(StringRefConversionTest_682, ConvertToStdString_682) {
    StringRef s("hello");
    std::string str = static_cast<std::string>(s);
    EXPECT_EQ(str, "hello");
}

TEST(StringRefConversionTest_682, EmptyConvertToStdString_682) {
    StringRef s;
    std::string str = static_cast<std::string>(s);
    EXPECT_EQ(str, "");
}

// ============================================================
// operator+ tests
// ============================================================

TEST(StringRefConcatTest_682, ConcatenateTwoStringRefs_682) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefConcatTest_682, ConcatenateWithEmpty_682) {
    StringRef a("hello");
    StringRef b("");
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefConcatTest_682, ConcatenateBothEmpty_682) {
    StringRef a("");
    StringRef b("");
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= tests
// ============================================================

TEST(StringRefAppendTest_682, AppendToStdString_682) {
    std::string lhs = "hello";
    StringRef rhs(" world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

TEST(StringRefAppendTest_682, AppendEmptyStringRef_682) {
    std::string lhs = "hello";
    StringRef rhs("");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello");
}

// ============================================================
// operator<< tests
// ============================================================

TEST(StringRefStreamTest_682, OutputToStream_682) {
    StringRef s("hello");
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "hello");
}

TEST(StringRefStreamTest_682, EmptyOutputToStream_682) {
    StringRef s("");
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "");
}

// ============================================================
// compare() additional boundary tests
// ============================================================

TEST(StringRefCompareTest_682, CompareWithSelf_682) {
    StringRef a("test");
    EXPECT_EQ(a.compare(a), 0);
}

TEST(StringRefCompareTest_682, CompareDefaultConstructed_682) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, CompareWithStdStringConstructed_682) {
    std::string s1 = "apple";
    std::string s2 = "banana";
    StringRef a(s1);
    StringRef b(s2);
    EXPECT_LT(a.compare(b), 0);
    EXPECT_GT(b.compare(a), 0);
}

TEST(StringRefCompareTest_682, CompareLongStrings_682) {
    std::string s1(1000, 'a');
    std::string s2(1000, 'a');
    s2[999] = 'b';
    StringRef a(s1);
    StringRef b(s2);
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompareTest_682, CompareIdenticalLongStrings_682) {
    std::string s1(1000, 'x');
    std::string s2(1000, 'x');
    StringRef a(s1);
    StringRef b(s2);
    EXPECT_EQ(a.compare(b), 0);
}
