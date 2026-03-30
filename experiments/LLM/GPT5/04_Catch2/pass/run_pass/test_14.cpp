// File: stringref_udl_tests_14.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_stringref.hpp"

class StringRefLiteralTest_14 : public ::testing::Test {};

// Helper to compare a StringRef to an expected std::string
static std::string ToStdString(const Catch::StringRef& sr) {
    return std::string(sr.data(), sr.size());
}

// [Normal] Basic ASCII literal
TEST_F(StringRefLiteralTest_14, BasicLiteralConstructsCorrectRef_14) {
    auto sr = "hello"_catch_sr;
    EXPECT_EQ(sr.size(), 5u);
    EXPECT_EQ(ToStdString(sr), std::string("hello"));
}

// [Boundary] Empty string literal
TEST_F(StringRefLiteralTest_14, EmptyLiteralYieldsSizeZero_14) {
    auto sr = ""_catch_sr;
    EXPECT_EQ(sr.size(), 0u);
    // When size==0, data() may be non-null (points at a literal), so compare via size only.
    EXPECT_EQ(ToStdString(sr), std::string());
}

// [Boundary] Embedded null bytes are preserved (size tracks full literal length)
TEST_F(StringRefLiteralTest_14, EmbeddedNullsArePreserved_14) {
    auto sr = "a\0b"_catch_sr; // literal length is 3 including the null
    EXPECT_EQ(sr.size(), 3u);
    const std::string expected("a\0b", 3);
    EXPECT_EQ(ToStdString(sr), expected);
    // Spot-check characters around the null byte
    ASSERT_GE(sr.size(), 3u);
    EXPECT_EQ(sr.data()[0], 'a');
    EXPECT_EQ(sr.data()[1], '\0');
    EXPECT_EQ(sr.data()[2], 'b');
}

// [Normal] Spaces and punctuation are preserved verbatim
TEST_F(StringRefLiteralTest_14, SpacesAndPunctuationPreserved_14) {
    auto sr = "  Catch2: v3.0, ok?!  "_catch_sr;
    EXPECT_EQ(ToStdString(sr), std::string("  Catch2: v3.0, ok?!  "));
    EXPECT_EQ(sr.size(), std::string("  Catch2: v3.0, ok?!  ").size());
}

// [Boundary] Long-ish literal to ensure size is tracked correctly
TEST_F(StringRefLiteralTest_14, LongLiteralSizeIsCorrect_14) {
    // Build a reasonably long literal via concatenation (no runtime logic)
    auto sr =
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"_catch_sr; // 256 'a's

    EXPECT_EQ(sr.size(), 256u);
    EXPECT_TRUE(std::all_of(sr.data(), sr.data() + sr.size(),
                            [](char c){ return c == 'a'; }));
}

// [Normal] Different literals produce different views
TEST_F(StringRefLiteralTest_14, DifferentLiteralsProduceDifferentViews_14) {
    auto s1 = "foo"_catch_sr;
    auto s2 = "bar"_catch_sr;
    EXPECT_NE(ToStdString(s1), ToStdString(s2));
    EXPECT_EQ(ToStdString(s1), std::string("foo"));
    EXPECT_EQ(ToStdString(s2), std::string("bar"));
}
