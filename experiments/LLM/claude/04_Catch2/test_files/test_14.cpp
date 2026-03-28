#include <gtest/gtest.h>
#include "catch2/internal/catch_stringref.hpp"
#include <string>
#include <cstring>

// Test default constructor
TEST_F_OR_TEST(StringRefTest_14, DefaultConstructor_14) {
    // Using TEST instead of TEST_F since we don't need a fixture
}

TEST(StringRefTest_14, DefaultConstructor_14) {
    Catch::StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_14, ConstructFromCString_14) {
    Catch::StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST(StringRefTest_14, ConstructFromCharPtrAndSize_14) {
    const char* raw = "hello world";
    Catch::StringRef sr(raw, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_14, EmptyStringConstruction_14) {
    Catch::StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_14, UserDefinedLiteral_14) {
    auto sr = "hello"_catch_sr;
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_FALSE(sr.empty());
}

TEST(StringRefTest_14, UserDefinedLiteralEmpty_14) {
    auto sr = ""_catch_sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST(StringRefTest_14, EqualityOperatorSameContent_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2("hello");
    EXPECT_EQ(sr1, sr2);
}

TEST(StringRefTest_14, EqualityOperatorDifferentContent_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2("world");
    EXPECT_NE(sr1, sr2);
}

TEST(StringRefTest_14, EqualityOperatorDifferentLengths_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2("hell");
    EXPECT_NE(sr1, sr2);
}

TEST(StringRefTest_14, EqualityWithStdString_14) {
    Catch::StringRef sr("hello");
    std::string s("hello");
    EXPECT_EQ(sr, Catch::StringRef(s.c_str(), s.size()));
}

TEST(StringRefTest_14, CopyConstructor_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2(sr1);
    EXPECT_EQ(sr1, sr2);
    EXPECT_EQ(sr2.size(), 5u);
}

TEST(StringRefTest_14, CopyAssignment_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2("world");
    sr2 = sr1;
    EXPECT_EQ(sr1, sr2);
}

TEST(StringRefTest_14, MoveConstructor_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2(std::move(sr1));
    EXPECT_EQ(sr2.size(), 5u);
}

TEST(StringRefTest_14, MoveAssignment_14) {
    Catch::StringRef sr1("hello");
    Catch::StringRef sr2;
    sr2 = std::move(sr1);
    EXPECT_EQ(sr2.size(), 5u);
}

TEST(StringRefTest_14, DataPointerNonNull_14) {
    Catch::StringRef sr("hello");
    EXPECT_NE(sr.data(), nullptr);
}

TEST(StringRefTest_14, DataPointerForEmptyIsNotNull_14) {
    Catch::StringRef sr("");
    // Even empty string ref should have a valid data pointer
    EXPECT_NE(sr.data(), nullptr);
}

TEST(StringRefTest_14, SubscriptOperator_14) {
    Catch::StringRef sr("hello");
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[1], 'e');
    EXPECT_EQ(sr[2], 'l');
    EXPECT_EQ(sr[3], 'l');
    EXPECT_EQ(sr[4], 'o');
}

TEST(StringRefTest_14, BeginEnd_14) {
    Catch::StringRef sr("abc");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "abc");
}

TEST(StringRefTest_14, BeginEndEmpty_14) {
    Catch::StringRef sr("");
    EXPECT_EQ(sr.begin(), sr.end());
}

TEST(StringRefTest_14, ComparisonWithLiteral_14) {
    auto sr = "test"_catch_sr;
    EXPECT_EQ(sr, "test"_catch_sr);
    EXPECT_NE(sr, "other"_catch_sr);
}

TEST(StringRefTest_14, LiteralWithSpecialCharacters_14) {
    auto sr = "hello\nworld"_catch_sr;
    EXPECT_EQ(sr.size(), 11u);
}

TEST(StringRefTest_14, LiteralWithNullInMiddle_14) {
    // Using the literal operator with explicit size
    const char raw[] = "hel\0lo";
    Catch::StringRef sr(raw, 6);
    EXPECT_EQ(sr.size(), 6u);
}

TEST(StringRefTest_14, SizeIsCorrectForVariousStrings_14) {
    EXPECT_EQ(Catch::StringRef("").size(), 0u);
    EXPECT_EQ(Catch::StringRef("a").size(), 1u);
    EXPECT_EQ(Catch::StringRef("ab").size(), 2u);
    EXPECT_EQ(Catch::StringRef("abc").size(), 3u);
}

TEST(StringRefTest_14, ConstexprLiteral_14) {
    constexpr auto sr = "constexpr_test"_catch_sr;
    static_assert(sr.size() == 14, "Size should be 14");
    EXPECT_EQ(sr.size(), 14u);
}

TEST(StringRefTest_14, SubstringView_14) {
    const char* full = "hello world";
    Catch::StringRef sr(full, 5);
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr[0], 'h');
    EXPECT_EQ(sr[4], 'o');
}

TEST(StringRefTest_14, SelfAssignment_14) {
    Catch::StringRef sr("hello");
    sr = sr;
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(sr, "hello"_catch_sr);
}

TEST(StringRefTest_14, CompareEqualStringsWithDifferentOrigins_14) {
    char buf1[] = "hello";
    char buf2[] = "hello";
    Catch::StringRef sr1(buf1, 5);
    Catch::StringRef sr2(buf2, 5);
    EXPECT_EQ(sr1, sr2);
    // They point to different memory but should be equal
    EXPECT_NE(sr1.data(), sr2.data());
}

TEST(StringRefTest_14, LessThanOperator_14) {
    Catch::StringRef sr1("abc");
    Catch::StringRef sr2("abd");
    EXPECT_LT(sr1, sr2);
}

TEST(StringRefTest_14, LessThanOperatorSamePrefix_14) {
    Catch::StringRef sr1("abc");
    Catch::StringRef sr2("abcd");
    EXPECT_LT(sr1, sr2);
}

TEST(StringRefTest_14, ConversionToStdString_14) {
    Catch::StringRef sr("hello");
    std::string s(sr);
    EXPECT_EQ(s, "hello");
}
