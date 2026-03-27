// File: tests/splitReporterSpec_688_tests.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the real StringRef header in your tree:
#include "catch2/internal/catch_stringref.hpp"

// Forward-declare the function under test (same signature & namespace).
namespace Catch { namespace Detail {
    std::vector<std::string> splitReporterSpec(Catch::StringRef reporterSpec);
}}

// For brevity in tests
using Catch::StringRef;
using Catch::Detail::splitReporterSpec;

namespace {

TEST(SplitReporterSpec_688, EmptyInput_YieldsSingleEmptyPart_688) {
    StringRef in{""};
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "");
}

TEST(SplitReporterSpec_688, NoSeparator_SinglePartWholeString_688) {
    StringRef in{"console"};
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "console");
}

TEST(SplitReporterSpec_688, SingleSeparator_SplitsIntoTwoParts_688) {
    StringRef in{"console::xml"};
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "console");
    EXPECT_EQ(parts[1], "xml");
}

TEST(SplitReporterSpec_688, LeadingSeparator_EmptyFirstPart_688) {
    StringRef in{"::xml"};
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "");        // leading "::" -> empty first token
    EXPECT_EQ(parts[1], "xml");
}

TEST(SplitReporterSpec_688, TrailingSeparator_EmptyLastPart_688) {
    StringRef in{"console::"};
    auto parts = splitReporterSpec(in);
    // trailing "::" should produce a trailing empty token
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "console");
    EXPECT_EQ(parts[1], "");
}

TEST(SplitReporterSpec_688, MultipleSeparators_SplitsAllTokens_688) {
    StringRef in{"a::b::c"};
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(SplitReporterSpec_688, ConsecutiveSeparators_EmptyMiddleToken_688) {
    StringRef in{"a::::b"}; // "a", "", "b"
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "");   // empty between the two "::"
    EXPECT_EQ(parts[2], "b");
}

TEST(SplitReporterSpec_688, SingleColon_NoSplitOccurs_688) {
    StringRef in{"con:sole"}; // only one colon at a time, never "::"
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "con:sole");
}

TEST(SplitReporterSpec_688, TripleColon_LeavesResidualSingleColon_688) {
    StringRef in{":::xml"};
    // Expected: first "::" -> empty token, remainder starts with single ":" (not a separator)
    auto parts = splitReporterSpec(in);
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "");
    EXPECT_EQ(parts[1], ":xml");
}

TEST(SplitReporterSpec_688, LongWithoutSeparator_RemainsSinglePart_688) {
    std::string longName(1024, 'x');
    auto parts = splitReporterSpec(StringRef{longName});
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], longName);
}

} // namespace
