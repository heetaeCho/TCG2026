#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ==================== operator< tests ====================

TEST(StringRefLessThan_681, EmptyStringsAreNotLessThan_681) {
    StringRef a;
    StringRef b;
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, EmptyStringIsLessThanNonEmpty_681) {
    StringRef a;
    StringRef b("hello");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThan_681, NonEmptyIsNotLessThanEmpty_681) {
    StringRef a("hello");
    StringRef b;
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, SameStringsAreNotLessThan_681) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, LexicographicallySmallerIsLessThan_681) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThan_681, LexicographicallyLargerIsNotLessThan_681) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, ShorterPrefixIsLessThanLonger_681) {
    StringRef a("ab");
    StringRef b("abc");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThan_681, LongerStringWithSamePrefixIsNotLessThanShorter_681) {
    StringRef a("abc");
    StringRef b("ab");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, SingleCharacterComparison_681) {
    StringRef a("a");
    StringRef b("b");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessThan_681, SingleCharacterEqualNotLessThan_681) {
    StringRef a("a");
    StringRef b("a");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, DifferentLengthsFirstCharSmaller_681) {
    StringRef a("a");
    StringRef b("ba");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThan_681, DifferentLengthsFirstCharLarger_681) {
    StringRef a("ba");
    StringRef b("a");
    EXPECT_FALSE(a < b);
}

TEST(StringRefLessThan_681, LongerStringLexicographicallySmaller_681) {
    StringRef a("abcd");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefLessThan_681, LongerStringLexicographicallyLarger_681) {
    StringRef a("abd");
    StringRef b("abcd");
    EXPECT_FALSE(a < b);
}

// ==================== Constructor and basic interface tests ====================

TEST(StringRefBasic_681, DefaultConstructorCreatesEmptyString_681) {
    StringRef s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(StringRefBasic_681, ConstructFromCString_681) {
    StringRef s("hello");
    EXPECT_EQ(s.size(), 5u);
    EXPECT_FALSE(s.empty());
}

TEST(StringRefBasic_681, ConstructFromStdString_681) {
    std::string str = "world";
    StringRef s(str);
    EXPECT_EQ(s.size(), 5u);
}

TEST(StringRefBasic_681, ConstructFromRawCharsAndSize_681) {
    const char* data = "hello world";
    StringRef s(data, 5);
    EXPECT_EQ(s.size(), 5u);
}

// ==================== Equality and inequality tests ====================

TEST(StringRefEquality_681, EqualStringsAreEqual_681) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefEquality_681, DifferentStringsAreNotEqual_681) {
    StringRef a("test");
    StringRef b("other");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefEquality_681, DifferentLengthStringsAreNotEqual_681) {
    StringRef a("test");
    StringRef b("tes");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// ==================== Subscript operator tests ====================

TEST(StringRefSubscript_681, AccessFirstCharacter_681) {
    StringRef s("hello");
    EXPECT_EQ(s[0], 'h');
}

TEST(StringRefSubscript_681, AccessLastCharacter_681) {
    StringRef s("hello");
    EXPECT_EQ(s[4], 'o');
}

TEST(StringRefSubscript_681, AccessMiddleCharacter_681) {
    StringRef s("hello");
    EXPECT_EQ(s[2], 'l');
}

// ==================== substr tests ====================

TEST(StringRefSubstr_681, SubstrFromStart_681) {
    StringRef s("hello world");
    StringRef sub = s.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == StringRef("hello"));
}

TEST(StringRefSubstr_681, SubstrFromMiddle_681) {
    StringRef s("hello world");
    StringRef sub = s.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == StringRef("world"));
}

TEST(StringRefSubstr_681, SubstrZeroLength_681) {
    StringRef s("hello");
    StringRef sub = s.substr(0, 0);
    EXPECT_TRUE(sub.empty());
}

// ==================== data() tests ====================

TEST(StringRefData_681, DataReturnsPointerToContent_681) {
    const char* raw = "hello";
    StringRef s(raw);
    EXPECT_EQ(s.data(), raw);
}

// ==================== begin/end tests ====================

TEST(StringRefIterator_681, BeginEndDistanceEqualsSize_681) {
    StringRef s("hello");
    EXPECT_EQ(static_cast<size_t>(s.end() - s.begin()), s.size());
}

TEST(StringRefIterator_681, EmptyStringBeginEqualsEnd_681) {
    StringRef s;
    EXPECT_EQ(s.begin(), s.end());
}

// ==================== explicit std::string conversion ====================

TEST(StringRefConversion_681, ConvertToStdString_681) {
    StringRef s("hello");
    std::string str = static_cast<std::string>(s);
    EXPECT_EQ(str, "hello");
}

TEST(StringRefConversion_681, EmptyConvertToStdString_681) {
    StringRef s;
    std::string str = static_cast<std::string>(s);
    EXPECT_EQ(str, "");
}

// ==================== compare tests ====================

TEST(StringRefCompare_681, EqualStringsCompareToZero_681) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefCompare_681, SmallerStringComparesNegative_681) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompare_681, LargerStringComparesPositive_681) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefCompare_681, ShorterPrefixComparesNegative_681) {
    StringRef a("ab");
    StringRef b("abc");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefCompare_681, LongerPrefixComparesPositive_681) {
    StringRef a("abc");
    StringRef b("ab");
    EXPECT_GT(a.compare(b), 0);
}

// ==================== operator+ tests ====================

TEST(StringRefConcatenation_681, ConcatenateTwoStrings_681) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefConcatenation_681, ConcatenateWithEmpty_681) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

// ==================== operator+= tests ====================

TEST(StringRefAppend_681, AppendToStdString_681) {
    std::string lhs = "hello";
    StringRef rhs(" world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

// ==================== operator<< tests ====================

TEST(StringRefStream_681, OutputToStream_681) {
    StringRef s("hello");
    std::ostringstream os;
    os << s;
    EXPECT_EQ(os.str(), "hello");
}

// ==================== Edge case: operator< with prefix relationships ====================

TEST(StringRefLessThan_681, PrefixRelationshipShortVsLong_681) {
    // "abc" < "abcd" should be true
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessThan_681, IdenticalContentDifferentSources_681) {
    std::string s1 = "test";
    std::string s2 = "test";
    StringRef a(s1);
    StringRef b(s2);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessThan_681, StrictWeakOrderingConsistency_681) {
    StringRef a("apple");
    StringRef b("banana");
    StringRef c("cherry");
    
    // If a < b and b < c, then a < c (transitivity)
    if ((a < b) && (b < c)) {
        EXPECT_TRUE(a < c);
    }
    
    // Irreflexivity: !(a < a)
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(b < b);
    EXPECT_FALSE(c < c);
}

TEST(StringRefLessThan_681, AsymmetryProperty_681) {
    StringRef a("abc");
    StringRef b("abd");
    // If a < b then !(b < a)
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}
