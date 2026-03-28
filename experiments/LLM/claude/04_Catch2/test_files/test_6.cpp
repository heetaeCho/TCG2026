#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

// ============================================================
// Construction Tests
// ============================================================

TEST(StringRefTest_6, DefaultConstructor_IsEmpty_6) {
    StringRef ref;
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

TEST(StringRefTest_6, ConstructFromRawChars_6) {
    StringRef ref("hello");
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_FALSE(ref.empty());
}

TEST(StringRefTest_6, ConstructFromRawCharsAndSize_6) {
    StringRef ref("hello world", 5);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_EQ(ref[0], 'h');
    EXPECT_EQ(ref[4], 'o');
}

TEST(StringRefTest_6, ConstructFromStdString_6) {
    std::string s = "test string";
    StringRef ref(s);
    EXPECT_EQ(ref.size(), s.size());
    EXPECT_FALSE(ref.empty());
}

TEST(StringRefTest_6, ConstructFromEmptyString_6) {
    StringRef ref("");
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

TEST(StringRefTest_6, ConstructFromEmptyStdString_6) {
    std::string s;
    StringRef ref(s);
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

// ============================================================
// operator[] Tests
// ============================================================

TEST(StringRefTest_6, SubscriptOperator_FirstChar_6) {
    StringRef ref("abcdef");
    EXPECT_EQ(ref[0], 'a');
}

TEST(StringRefTest_6, SubscriptOperator_LastChar_6) {
    StringRef ref("abcdef");
    EXPECT_EQ(ref[5], 'f');
}

TEST(StringRefTest_6, SubscriptOperator_MiddleChar_6) {
    StringRef ref("abcdef");
    EXPECT_EQ(ref[3], 'd');
}

TEST(StringRefTest_6, SubscriptOperator_SingleChar_6) {
    StringRef ref("x");
    EXPECT_EQ(ref[0], 'x');
}

// ============================================================
// empty() and size() Tests
// ============================================================

TEST(StringRefTest_6, EmptyOnNonEmptyString_6) {
    StringRef ref("notempty");
    EXPECT_FALSE(ref.empty());
}

TEST(StringRefTest_6, SizeReturnsCorrectLength_6) {
    StringRef ref("twelve chars");
    EXPECT_EQ(ref.size(), 12u);
}

// ============================================================
// data() Tests
// ============================================================

TEST(StringRefTest_6, DataReturnsPointerToContent_6) {
    const char* raw = "hello";
    StringRef ref(raw);
    EXPECT_EQ(ref.data(), raw);
}

TEST(StringRefTest_6, DataWithSizeConstructor_6) {
    const char* raw = "hello world";
    StringRef ref(raw, 5);
    EXPECT_EQ(ref.data(), raw);
}

// ============================================================
// Equality and Inequality Tests
// ============================================================

TEST(StringRefTest_6, EqualityOperator_SameContent_6) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_6, EqualityOperator_DifferentContent_6) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_6, EqualityOperator_DifferentLength_6) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
}

TEST(StringRefTest_6, EqualityOperator_BothEmpty_6) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_6, InequalityOperator_DifferentContent_6) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_6, InequalityOperator_SameContent_6) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_FALSE(a != b);
}

// ============================================================
// compare() Tests
// ============================================================

TEST(StringRefTest_6, CompareEqual_6) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareLessThan_6) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareGreaterThan_6) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareShorterPrefix_6) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_LT(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareLongerPrefix_6) {
    StringRef a("abcd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareEmptyStrings_6) {
    StringRef a;
    StringRef b;
    EXPECT_EQ(a.compare(b), 0);
}

TEST(StringRefTest_6, CompareEmptyVsNonEmpty_6) {
    StringRef a;
    StringRef b("abc");
    EXPECT_LT(a.compare(b), 0);
}

// ============================================================
// operator< Tests
// ============================================================

TEST(StringRefTest_6, LessThanOperator_True_6) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
}

TEST(StringRefTest_6, LessThanOperator_False_6) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_6, LessThanOperator_Equal_6) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
}

TEST(StringRefTest_6, LessThanOperator_PrefixIsShorter_6) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
}

// ============================================================
// substr() Tests
// ============================================================

TEST(StringRefTest_6, SubstrFromBeginning_6) {
    StringRef ref("hello world");
    StringRef sub = ref.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'h');
    EXPECT_EQ(sub[4], 'o');
}

TEST(StringRefTest_6, SubstrFromMiddle_6) {
    StringRef ref("hello world");
    StringRef sub = ref.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
    EXPECT_EQ(sub[4], 'd');
}

TEST(StringRefTest_6, SubstrZeroLength_6) {
    StringRef ref("hello");
    StringRef sub = ref.substr(0, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST(StringRefTest_6, SubstrEntireString_6) {
    StringRef ref("hello");
    StringRef sub = ref.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_TRUE(sub == ref);
}

TEST(StringRefTest_6, SubstrSingleChar_6) {
    StringRef ref("hello");
    StringRef sub = ref.substr(2, 1);
    EXPECT_EQ(sub.size(), 1u);
    EXPECT_EQ(sub[0], 'l');
}

// ============================================================
// begin() / end() Tests
// ============================================================

TEST(StringRefTest_6, BeginEndIterators_6) {
    StringRef ref("abc");
    std::string result;
    for (auto it = ref.begin(); it != ref.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_6, BeginEndOnEmpty_6) {
    StringRef ref;
    EXPECT_EQ(ref.begin(), ref.end());
}

TEST(StringRefTest_6, RangeBasedFor_6) {
    StringRef ref("xyz");
    std::string result;
    for (char c : ref) {
        result += c;
    }
    EXPECT_EQ(result, "xyz");
}

// ============================================================
// Explicit conversion to std::string
// ============================================================

TEST(StringRefTest_6, ExplicitConversionToStdString_6) {
    StringRef ref("hello");
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_6, ExplicitConversionEmptyToStdString_6) {
    StringRef ref;
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "");
}

TEST(StringRefTest_6, ExplicitConversionWithSizeConstructor_6) {
    StringRef ref("hello world", 5);
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "hello");
}

// ============================================================
// operator+ Tests
// ============================================================

TEST(StringRefTest_6, PlusOperatorConcatenates_6) {
    StringRef a("hello");
    StringRef b(" world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST(StringRefTest_6, PlusOperatorWithEmpty_6) {
    StringRef a("hello");
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_6, PlusOperatorBothEmpty_6) {
    StringRef a;
    StringRef b;
    std::string result = a + b;
    EXPECT_EQ(result, "");
}

// ============================================================
// operator+= Tests
// ============================================================

TEST(StringRefTest_6, PlusEqualsOperator_6) {
    std::string s = "hello";
    StringRef ref(" world");
    s += ref;
    EXPECT_EQ(s, "hello world");
}

TEST(StringRefTest_6, PlusEqualsOperatorWithEmptyRef_6) {
    std::string s = "hello";
    StringRef ref;
    s += ref;
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_6, PlusEqualsOperatorOnEmptyString_6) {
    std::string s;
    StringRef ref("hello");
    s += ref;
    EXPECT_EQ(s, "hello");
}

// ============================================================
// operator<< Tests
// ============================================================

TEST(StringRefTest_6, StreamOutputOperator_6) {
    StringRef ref("hello");
    std::ostringstream oss;
    oss << ref;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_6, StreamOutputOperatorEmpty_6) {
    StringRef ref;
    std::ostringstream oss;
    oss << ref;
    EXPECT_EQ(oss.str(), "");
}

TEST(StringRefTest_6, StreamOutputOperatorPartialString_6) {
    StringRef ref("hello world", 5);
    std::ostringstream oss;
    oss << ref;
    EXPECT_EQ(oss.str(), "hello");
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(StringRefTest_6, SingleCharacterString_6) {
    StringRef ref("a");
    EXPECT_EQ(ref.size(), 1u);
    EXPECT_FALSE(ref.empty());
    EXPECT_EQ(ref[0], 'a');
}

TEST(StringRefTest_6, CompareWithSelf_6) {
    StringRef ref("hello");
    EXPECT_EQ(ref.compare(ref), 0);
    EXPECT_TRUE(ref == ref);
    EXPECT_FALSE(ref != ref);
    EXPECT_FALSE(ref < ref);
}

TEST(StringRefTest_6, SubstrAtEnd_6) {
    StringRef ref("hello");
    StringRef sub = ref.substr(5, 0);
    EXPECT_TRUE(sub.empty());
}

TEST(StringRefTest_6, CopyConstructor_6) {
    StringRef original("hello");
    StringRef copy(original);
    EXPECT_TRUE(copy == original);
    EXPECT_EQ(copy.size(), original.size());
}

TEST(StringRefTest_6, AssignmentOperator_6) {
    StringRef a("hello");
    StringRef b("world");
    b = a;
    EXPECT_TRUE(b == a);
    EXPECT_EQ(b.size(), a.size());
}

TEST(StringRefTest_6, EqualityWithDifferentSources_6) {
    const char* raw = "hello";
    std::string str = "hello";
    StringRef a(raw);
    StringRef b(str);
    EXPECT_TRUE(a == b);
}

TEST(StringRefTest_6, StringWithNullInMiddle_ViaSize_6) {
    const char data[] = "he\0lo";
    StringRef ref(data, 5);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_EQ(ref[2], '\0');
    EXPECT_EQ(ref[3], 'l');
}

TEST(StringRefTest_6, DataPreservesPointer_6) {
    std::string s = "test";
    StringRef ref(s);
    EXPECT_EQ(ref.data(), s.c_str());
}
