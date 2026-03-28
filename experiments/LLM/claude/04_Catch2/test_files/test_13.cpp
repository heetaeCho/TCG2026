#include <gtest/gtest.h>
#include "catch2/internal/catch_stringref.hpp"
#include <string>
#include <cstring>

using namespace Catch;

// ============================================================
// Tests for StringRef construction
// ============================================================

TEST(StringRefTest_13, DefaultConstructor_13) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_13, ConstructFromCString_13) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_13, ConstructFromCStringAndSize_13) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_13, ConstructFromStdString_13) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_13, ConstructFromEmptyCString_13) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_13, ConstructFromEmptyStdString_13) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

// ============================================================
// Tests for UDL operator
// ============================================================

TEST(StringRefTest_13, UserDefinedLiteral_13) {
    auto sr = "hello"_sr;
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_13, UserDefinedLiteralEmpty_13) {
    auto sr = ""_sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_13, UserDefinedLiteralWithEmbeddedNull_13) {
    auto sr = StringRef("he\0lo", 5);
    EXPECT_EQ(sr.size(), 5u);
}

// ============================================================
// Tests for comparison
// ============================================================

TEST(StringRefTest_13, EqualityOperatorSameContent_13) {
    StringRef a("hello");
    StringRef b("hello");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringRefTest_13, EqualityOperatorDifferentContent_13) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_13, EqualityOperatorDifferentLength_13) {
    StringRef a("hello");
    StringRef b("hell");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringRefTest_13, EqualityWithStdString_13) {
    StringRef sr("hello");
    std::string s = "hello";
    EXPECT_TRUE(sr == StringRef(s));
}

TEST(StringRefTest_13, EqualityEmptyStrings_13) {
    StringRef a;
    StringRef b("");
    EXPECT_TRUE(a == b);
}

// ============================================================
// Tests for less-than / ordering
// ============================================================

TEST(StringRefTest_13, LessThanOperator_13) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_13, LessThanOperatorSameContent_13) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefTest_13, LessThanOperatorPrefix_13) {
    StringRef a("abc");
    StringRef b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ============================================================
// Tests for data access
// ============================================================

TEST(StringRefTest_13, DataReturnsValidPointer_13) {
    StringRef sr("hello");
    EXPECT_NE(sr.data(), nullptr);
    EXPECT_EQ(std::strncmp(sr.data(), "hello", 5), 0);
}

TEST(StringRefTest_13, BeginEndIterators_13) {
    StringRef sr("hello");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "hello");
}

TEST(StringRefTest_13, SubscriptOperator_13) {
    StringRef sr("hello");
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[1], 'e');
    EXPECT_EQ(sr[4], 'o');
}

// ============================================================
// Tests for conversion
// ============================================================

TEST(StringRefTest_13, ConvertToStdString_13) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_13, ConvertEmptyToStdString_13) {
    StringRef sr;
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "");
}

// ============================================================
// Tests for empty() and size()
// ============================================================

TEST(StringRefTest_13, SizeMatchesContent_13) {
    StringRef sr("abc");
    EXPECT_EQ(sr.size(), 3u);
}

TEST(StringRefTest_13, EmptyWhenDefault_13) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
}

TEST(StringRefTest_13, NotEmptyWhenContentPresent_13) {
    StringRef sr("a");
    EXPECT_FALSE(sr.empty());
}

// ============================================================
// Tests for copy semantics
// ============================================================

TEST(StringRefTest_13, CopyConstructor_13) {
    StringRef original("hello");
    StringRef copy(original);
    EXPECT_EQ(original, copy);
    EXPECT_EQ(copy.size(), 5u);
}

TEST(StringRefTest_13, CopyAssignment_13) {
    StringRef original("hello");
    StringRef other("world");
    other = original;
    EXPECT_EQ(other, original);
}

// ============================================================
// Tests for substr-like behavior (if available)
// ============================================================

TEST(StringRefTest_13, PartialStringRef_13) {
    const char* text = "hello world";
    StringRef sr(text, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr, StringRef("hello"));
}

// ============================================================
// Boundary conditions
// ============================================================

TEST(StringRefTest_13, SingleCharacter_13) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_EQ(sr[0], 'x');
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_13, ZeroSizeFromPointerAndSize_13) {
    StringRef sr("hello", 0);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_13, LongString_13) {
    std::string longStr(10000, 'a');
    StringRef sr(longStr);
    EXPECT_EQ(sr.size(), 10000u);
    EXPECT_FALSE(sr.empty());
}

// ============================================================
// Tests for stream output (if operator<< is available)
// ============================================================

TEST(StringRefTest_13, StreamOutput_13) {
    StringRef sr("hello");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hello");
}

TEST(StringRefTest_13, StreamOutputEmpty_13) {
    StringRef sr;
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "");
}

// ============================================================
// Test isNullTerminated or c_str if available
// ============================================================

TEST(StringRefTest_13, CStrReturnsNullTerminated_13) {
    StringRef sr("hello");
    // c_str() should return a null-terminated version
    // This test only runs if c_str() is part of the interface
    // If not, this test will fail to compile and should be removed
    // For now, we test data-based access
    std::string reconstructed(sr.data(), sr.size());
    EXPECT_EQ(reconstructed, "hello");
}

// ============================================================
// Self-equality tests
// ============================================================

TEST(StringRefTest_13, SelfEquality_13) {
    StringRef sr("test");
    EXPECT_TRUE(sr == sr);
    EXPECT_FALSE(sr != sr);
}

TEST(StringRefTest_13, CompareWithDifferentSource_13) {
    std::string s1 = "hello";
    std::string s2 = "hello";
    StringRef sr1(s1);
    StringRef sr2(s2);
    EXPECT_TRUE(sr1 == sr2);
}
