// File: tests/string_contains_matcher_220_test.cpp

#include <gtest/gtest.h>
#include "catch2/matchers/catch_matchers_string.hpp"

// We only exercise the public interface and observable behavior.
// Assumptions used are limited to typical, externally visible semantics:
// - "contains" means substring check
// - Case sensitivity is controlled via the comparator's construction

using Catch::Matchers::CasedString;
using Catch::Matchers::StringContainsMatcher;

// Catch2 defines CaseSensitive with values Yes/No.
// If your include path differs, adjust the include above accordingly.
using Catch::CaseSensitive;

// --- Normal operation ---

TEST(StringContainsMatcher_220, ReturnsTrueWhenSubstringPresent_CaseSensitiveYes_220) {
    // comparator = "world" (case-sensitive)
    CasedString cmp("world", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    // source contains "world" exactly
    EXPECT_TRUE(matcher.match(std::string("hello world")));
}

TEST(StringContainsMatcher_220, ReturnsFalseWhenSubstringAbsent_CaseSensitiveYes_220) {
    CasedString cmp("mars", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    EXPECT_FALSE(matcher.match(std::string("hello world")));
}

// --- Case sensitivity boundary/variation ---

TEST(StringContainsMatcher_220, ReturnsFalseWhenCaseDoesNotMatch_WithCaseSensitiveYes_220) {
    CasedString cmp("WORLD", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    // Mismatch by case should not match when case-sensitive
    EXPECT_FALSE(matcher.match(std::string("hello world")));
}

TEST(StringContainsMatcher_220, ReturnsTrueWhenCaseDiffers_WithCaseSensitiveNo_220) {
    CasedString cmp("WORLD", CaseSensitive::No);
    StringContainsMatcher matcher(cmp);

    // Case-insensitive compare should match
    EXPECT_TRUE(matcher.match(std::string("hello world")));
}

// --- Edge conditions ---

TEST(StringContainsMatcher_220, EmptyNeedleMatchesAnySource_220) {
    CasedString cmp("", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    // Common substring semantics: empty needle is contained
    EXPECT_TRUE(matcher.match(std::string("anything")));
    EXPECT_TRUE(matcher.match(std::string("")));
}

TEST(StringContainsMatcher_220, NonEmptyNeedleDoesNotMatchEmptySource_220) {
    CasedString cmp("x", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    EXPECT_FALSE(matcher.match(std::string("")));
}

TEST(StringContainsMatcher_220, NeedleAtStartMiddleEnd_220) {
    CasedString cmp("ab", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match(std::string("ab...")));   // start
    EXPECT_TRUE(matcher.match(std::string("..ab..")));  // middle
    EXPECT_TRUE(matcher.match(std::string("...ab")));   // end
}

// --- Mixed Unicode / extended chars scenario (observable behavior only) ---

TEST(StringContainsMatcher_220, HandlesExtendedCharacters_WithoutThrowing_AndMatchesSubstring_220) {
    // Using UTF-8 substrings; we only assert observable contains behavior.
    CasedString cmp(u8"세계", CaseSensitive::Yes);
    StringContainsMatcher matcher(cmp);

    EXPECT_TRUE(matcher.match(std::string(u8"안녕 세계")));
    EXPECT_FALSE(matcher.match(std::string(u8"안녕 세상")));
}
