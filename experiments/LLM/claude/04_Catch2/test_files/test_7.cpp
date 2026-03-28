#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ============================================================
// Default Construction Tests
// ============================================================

TEST(StringRefTest_7, DefaultConstructorCreatesEmptyString_7) {
    StringRef ref;
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// Construction from raw C-string
// ============================================================

TEST(StringRefTest_7, ConstructFromRawCString_7) {
    StringRef ref("hello");
    EXPECT_FALSE(ref.empty());
    EXPECT_EQ(ref.size(), 5u);
}

TEST(StringRefTest_7, ConstructFromEmptyRawCString_7) {
    StringRef ref("");
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// Construction from raw pointer and size
// ============================================================

TEST(StringRefTest_7, ConstructFromRawPointerAndSize_7) {
    const char* str = "hello world";
    StringRef ref(str, 5);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_FALSE(ref.empty());
}

TEST(StringRefTest_7, ConstructFromRawPointerAndZeroSize_7) {
    const char* str = "hello";
    StringRef ref(str, 0);
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// Construction from std::string
// ============================================================

TEST(StringRefTest_7, ConstructFromStdString_7) {
    std::string s = "test string";
    StringRef ref(s);
    EXPECT_EQ(ref.size(), s.size());
    EXPECT_FALSE(ref.empty());
}

TEST(StringRefTest_7, ConstructFromEmptyStdString_7) {
    std::string s;
    StringRef ref(s);
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// empty() tests
// ============================================================

TEST(StringRefTest_7, EmptyReturnsTrueForDefaultConstructed_7) {
    StringRef ref;
    EXPECT_TRUE(ref.empty());
}

TEST(StringRefTest_7, EmptyReturnsFalseForNonEmpty_7) {
    StringRef ref("abc");
    EXPECT_FALSE(ref.empty());
}

// ============================================================
// size() tests
// ============================================================

TEST(StringRefTest_7, SizeReturnsCorrectLength_7) {
    StringRef ref("abcdef");
    EXPECT_EQ(ref.size(), 6u);
}

TEST(StringRefTest_7, SizeIsZeroForEmptyString_7) {
    StringRef ref;
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// operator[] tests
// ============================================================

TEST(StringRefTest_7, SubscriptOperatorReturnsCorrectChar_7) {
    StringRef ref("hello");
    EXPECT_EQ(ref[0], 'h');
    EXPECT_EQ(ref[1], 'e');
    EXPECT_EQ(ref[2], 'l');
    EXPECT_EQ(ref[3], 'l');
    EXPECT_EQ(ref[4], 'o');
}

TEST(StringRefTest_7, SubscriptOperatorLastChar_7) {
    StringRef ref("abc");
    EXPECT_EQ(ref[2], 'c');
}

// ============================================================
// operator== and operator!= tests
// ============================================================

TEST(StringRefTest_7, EqualityOperatorSameStrings_7) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_7, EqualityOperatorDifferentStrings_7) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_7, EqualityOperatorDifferentLengths_7) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_7, EqualityOperatorBothEmpty_7) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_7, EqualityOperatorOneEmpty_7) {
    StringRef a("hello");
    StringRef b;
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// ============================================================
// operator< tests
// ============================================================

TEST(StringRefTest_7, LessThanOperator_7) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_7, LessThanOperatorEqualStrings_7) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_7, LessThanOperatorPrefixIsShorter_7) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_7, LessThanOperatorEmptyVsNonEmpty_7) {
    StringRef a;
    StringRef b("a");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ============================================================
// compare() tests
// ============================================================

TEST(StringRefTest_7, CompareEqualStrings_7) {
    StringRef a("test");
    StringRef b("test");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_7, CompareLessThan_7) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_7, CompareGreaterThan_7) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_7, CompareWithDifferentLengths_7) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_7, CompareEmptyStrings_7) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

// ============================================================
// data() tests
// ============================================================

TEST(StringRefTest_7, DataReturnsPointerToChars_7) {
    const char* raw = "hello";
    StringRef ref(raw, 5);
    EXPECT_EQ(ref.data(), raw);
}

TEST(StringRefTest_7, DataForDefaultConstructedIsNotNull_7) {
    StringRef ref;
    EXPECT_NE(ref.data(), nullptr);
}

// ============================================================
// substr() tests
// ============================================================

TEST(StringRefTest_7, SubstrFromBeginning_7) {
    StringRef ref("hello world");
    StringRef sub = ref.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST(StringRefTest_7, SubstrFromMiddle_7) {
    StringRef ref("hello world");
    StringRef sub = ref.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("world"));
}

TEST(StringRefTest_7, SubstrZeroLength_7) {
    StringRef ref("hello");
    StringRef sub = ref.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_7, SubstrSingleChar_7) {
    StringRef ref("hello");
    StringRef sub = ref.substr(1, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'e');
}

// ============================================================
// Explicit conversion to std::string
// ============================================================

TEST(StringRefTest_7, ExplicitConversionToStdString_7) {
    StringRef ref("hello");
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_7, ExplicitConversionEmptyToStdString_7) {
    StringRef ref;
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "");
}

// ============================================================
// operator+ tests
// ============================================================

TEST(StringRefTest_7, ConcatenationOfTwoStringRefs_7) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_7, ConcatenationWithEmptyStringRef_7) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_7, ConcatenationBothEmpty_7) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= tests
// ============================================================

TEST(StringRefTest_7, PlusEqualsAppendsToStdString_7) {
    std::string s = "hello";
    StringRef ref(" world");
    s += ref;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_7, PlusEqualsWithEmptyStringRef_7) {
    std::string s = "hello";
    StringRef ref;
    s += ref;
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_7, PlusEqualsToEmptyStdString_7) {
    std::string s;
    StringRef ref("hello");
    s += ref;
    EXPECT_EQ(s, "hello");
}

// ============================================================
// operator<< tests
// ============================================================

TEST(StringRefTest_7, StreamInsertionOperator_7) {
    StringRef ref("hello");
    std::ostringstream os;
    os << ref;
    EXPECT_EQ(os.str(), "hello");
}

TEST(StringRefTest_7, StreamInsertionOperatorEmpty_7) {
    StringRef ref;
    std::ostringstream os;
    os << ref;
    EXPECT_EQ(os.str(), "");
}

// ============================================================
// Iterator tests
// ============================================================

TEST(StringRefTest_7, BeginEndIteratorTraversal_7) {
    StringRef ref("abc");
    std::string result;
    for (auto it = ref.begin(); it != ref.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_7, BeginEqualsEndForEmptyStringRef_7) {
    StringRef ref;
    EXPECT_EQ(ref.begin(), ref.end());
}

TEST(StringRefTest_7, RangeBasedForLoop_7) {
    StringRef ref("xyz");
    std::string result;
    for (char c : ref) {
        result += c;
    }
    EXPECT_EQ(result, "xyz");
}

// ============================================================
// Boundary and edge cases
// ============================================================

TEST(StringRefTest_7, SingleCharacterString_7) {
    StringRef ref("a");
    EXPECT_EQ(ref.size(), 1u);
    EXPECT_FALSE(ref.empty());
    EXPECT_EQ(ref[0], 'a');
}

TEST(StringRefTest_7, CompareStringRefWithItself_7) {
    StringRef ref("hello");
    EXPECT_TRUE(ref == ref);
    EXPECT_FALSE(ref != ref);
    EXPECT_FALSE(ref < ref);
    EXPECT_EQ(ref.compare(ref), 0);
}

TEST(StringRefTest_7, SubstrFullString_7) {
    StringRef ref("hello");
    StringRef sub = ref.substr(0, 5);
    EXPECT_EQ(sub, ref);
}

TEST(StringRefTest_7, ConstructFromStdStringAndCompareWithRawCString_7) {
    std::string s = "test";
    StringRef fromStdString(s);
    StringRef fromRaw("test");
    EXPECT_TRUE(fromStdString == fromRaw);
}

TEST(StringRefTest_7, LongString_7) {
    std::string longStr(1000, 'x');
    StringRef ref(longStr);
    EXPECT_EQ(ref.size(), 1000u);
    EXPECT_FALSE(ref.empty());
    EXPECT_EQ(ref[0], 'x');
    EXPECT_EQ(ref[999], 'x');
}

TEST(StringRefTest_7, StringWithNullCharInMiddle_7) {
    const char data[] = "hel\0lo";
    // Constructing with explicit size to include null char
    StringRef ref(data, 6);
    EXPECT_EQ(ref.size(), 6u);
}

TEST(StringRefTest_7, CopyConstructor_7) {
    StringRef original("hello");
    StringRef copy(original);
    EXPECT_EQ(copy, original);
    EXPECT_EQ(copy.size(), original.size());
}

TEST(StringRefTest_7, AssignmentOperator_7) {
    StringRef a("hello");
    StringRef b("world");
    b = a;
    EXPECT_EQ(b, a);
}

TEST(StringRefTest_7, EqualityWithDifferentSourcesSameContent_7) {
    std::string s1 = "hello";
    std::string s2 = "hello";
    StringRef a(s1);
    StringRef b(s2);
    // Different underlying pointers but same content
    EXPECT_TRUE(a == b);
}
