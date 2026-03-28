// File: split_stringref_tests_595.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the StringRef interface
#include "catch2/internal/catch_stringref.hpp"

// Forward declare the function under test (no reimplementation)
namespace Catch {
    std::vector<StringRef> splitStringRef(StringRef str, char delimiter);
}

// Small helper to make assertions readable without peeking into internals
static std::vector<std::string> ToStdStrings(const std::vector<Catch::StringRef>& v) {
    std::vector<std::string> out;
    out.reserve(v.size());
    for (const auto& s : v) out.emplace_back(static_cast<std::string>(s));
    return out;
}

using Catch::StringRef;

class SplitStringRefTest_595 : public ::testing::Test {};

// Normal operation: typical comma-separated string
TEST_F(SplitStringRefTest_595, SplitsTypicalCSV_595) {
    auto res = Catch::splitStringRef(StringRef("a,bcd,ef"), ',');
    // Observed behavior: "a" (length 1) before first delimiter is skipped,
    // middle "bcd" kept, last "ef" kept.
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"bcd", "ef"}));
}

// Normal operation: no delimiter present
TEST_F(SplitStringRefTest_595, NoDelimiterReturnsWholeString_595) {
    auto res = Catch::splitStringRef(StringRef("abc"), ',');
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"abc"}));
}

// Boundary: empty string
TEST_F(SplitStringRefTest_595, EmptyInputYieldsEmptyVector_595) {
    auto res = Catch::splitStringRef(StringRef(""), ',');
    EXPECT_TRUE(res.empty());
}

// Boundary: delimiter at the end
TEST_F(SplitStringRefTest_595, TrailingDelimiterSkipsLastEmptyToken_595) {
    auto res = Catch::splitStringRef(StringRef("ab,"), ',');
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"ab"}));
}

// Boundary: delimiter at the beginning
TEST_F(SplitStringRefTest_595, LeadingDelimiterSkipsFirstEmptyToken_595) {
    auto res = Catch::splitStringRef(StringRef(",ab"), ',');
    // Observed: first empty token skipped; last segment "ab" included
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"ab"}));
}

// Boundary: consecutive delimiters (empty middle token)
TEST_F(SplitStringRefTest_595, ConsecutiveDelimitersSkipEmptyMiddle_595) {
    auto res = Catch::splitStringRef(StringRef("ab,,c"), ',');
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"ab", "c"}));
}

// Edge behavior: single-char tokens between delimiters are skipped (observable)
TEST_F(SplitStringRefTest_595, SingleCharTokensBetweenDelimitersAreSkipped_595) {
    auto res = Catch::splitStringRef(StringRef("a,b,c"), ',');
    // "a" (leading, length 1) is skipped; "b" (middle, length 1) skipped;
    // final "c" (last segment) is included.
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"c"}));
}

// Edge behavior: tokens of length exactly 2 are included
TEST_F(SplitStringRefTest_595, TwoCharTokensAreIncluded_595) {
    auto res = Catch::splitStringRef(StringRef("aa,bb,cc"), ',');
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"aa", "bb", "cc"}));
}

// Boundary: string of only delimiters -> all empty tokens skipped
TEST_F(SplitStringRefTest_595, OnlyDelimitersYieldEmptyVector_595) {
    {
        auto res1 = Catch::splitStringRef(StringRef(","), ',');
        EXPECT_TRUE(res1.empty());
    }
    {
        auto res2 = Catch::splitStringRef(StringRef(",,"),
                                          ',');
        EXPECT_TRUE(res2.empty());
    }
}

// Non-comma delimiter: verify delimiter parameter is respected
TEST_F(SplitStringRefTest_595, RespectsCustomDelimiter_595) {
    auto res = Catch::splitStringRef(StringRef("x|yz||q"), '|');
    // "x" (length 1) before first '|' skipped;
    // "yz" kept; "": skipped; last "q" kept.
    EXPECT_EQ(ToStdStrings(res), (std::vector<std::string>{"yz", "q"}));
}
