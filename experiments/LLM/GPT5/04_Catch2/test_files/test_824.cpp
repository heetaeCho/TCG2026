// File: tests/reporters/default_list_tests_824.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// Catch2 headers (public interfaces used by defaultListTests)
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_source_line_info.hpp" // In Catch2 v3, SourceLineInfo is public

using namespace Catch;

namespace {

// Minimal helper to build a TestCaseInfo from public types only
static TestCaseInfo makeInfo(const std::string& name,
                             const std::string& tags,
                             const SourceLineInfo& line) {
    NameAndTags nt{name, tags};
    // className is not relevant to printed output here
    return TestCaseInfo(StringRef{}, nt, line);
}

// Helper to wrap TestCaseInfo into TestCaseHandle
static TestCaseHandle makeHandle(TestCaseInfo& info) {
    // We do not invoke the test, so invoker can be nullptr.
    return TestCaseHandle(&info, nullptr);
}

struct DefaultListTests_Fixture_824 : ::testing::Test {
    std::ostringstream out;
    // We only need a valid pointer; colouring behavior is outside our assertions.
    // In Catch2, ColourImpl can be constructed with a null IStream*.
    ColourImpl colour{nullptr};

    // Build a pair of test cases: one with tags, one without, with stable line infos.
    TestCaseInfo infoA = makeInfo("AlphaCase",            "",                SourceLineInfo{"alpha.cpp", 11});
    TestCaseInfo infoB = makeInfo("BetaCase",   "[fast][ui]",                SourceLineInfo{"beta.cpp",  22});

    std::vector<TestCaseHandle> tests{
        makeHandle(infoA),
        makeHandle(infoB),
    };
};

} // end anonymous namespace

// Quiet verbosity -> should not print the "All available..." / "Matching..." headers,
// but should list test names (via listTestNamesOnly used internally).
TEST_F(DefaultListTests_Fixture_824, QuietVerbosityNamesOnly_824) {
    defaultListTests(out, &colour, tests, /*isFiltered=*/false, Verbosity::Quiet);

    const std::string s = out.str();

    // Should not contain the verbose headers
    EXPECT_EQ(s.find("All available test cases:"), std::string::npos);
    EXPECT_EQ(s.find("Matching test cases:"), std::string::npos);

    // Names should appear (observable behavior)
    EXPECT_NE(s.find("AlphaCase"), std::string::npos);
    EXPECT_NE(s.find("BetaCase"),  std::string::npos);
}

// Normal verbosity, unfiltered -> prints "All available test cases:",
// indented names, tag lines for tests that have tags, and a pluralized summary.
TEST_F(DefaultListTests_Fixture_824, NormalVerbosity_AllAvailableHeaderAndTags_824) {
    defaultListTests(out, &colour, tests, /*isFiltered=*/false, Verbosity::Normal);

    const std::string s = out.str();

    // Header
    EXPECT_NE(s.find("All available test cases:"), std::string::npos);
    EXPECT_EQ(s.find("Matching test cases:"), std::string::npos);

    // Names should be present (indented by Column().indent(2) internally).
    // We only assert presence, not exact whitespace formatting.
    EXPECT_NE(s.find("AlphaCase"), std::string::npos);
    EXPECT_NE(s.find("BetaCase"),  std::string::npos);

    // Tags are printed when verbosity > Quiet and tags are non-empty.
    // Expect the aggregated tag string to appear somewhere.
    EXPECT_NE(s.find("fast"), std::string::npos);
    EXPECT_NE(s.find("ui"),   std::string::npos);

    // Summary line (pluralisation), content must mention "test case"
    EXPECT_NE(s.find("test case"), std::string::npos);
    // Should not say "matching" in the summary when unfiltered
    EXPECT_EQ(s.find("matching test case"), std::string::npos);

    // The function ends with an extra blank line. Check it ends with "\n\n".
    ASSERT_FALSE(s.empty());
    EXPECT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size()-2), std::string("\n\n"));
}

// Normal verbosity, filtered -> prints "Matching test cases:" and a
// summary mentioning "matching".
TEST_F(DefaultListTests_Fixture_824, NormalVerbosity_MatchingHeaderAndSummary_824) {
    defaultListTests(out, &colour, tests, /*isFiltered=*/true, Verbosity::Normal);

    const std::string s = out.str();

    // Header
    EXPECT_NE(s.find("Matching test cases:"), std::string::npos);
    EXPECT_EQ(s.find("All available test cases:"), std::string::npos);

    // Names appear
    EXPECT_NE(s.find("AlphaCase"), std::string::npos);
    EXPECT_NE(s.find("BetaCase"),  std::string::npos);

    // Summary mentions "matching"
    EXPECT_NE(s.find("matching test case"), std::string::npos);

    ASSERT_FALSE(s.empty());
    EXPECT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size()-2), std::string("\n\n"));
}

// High verbosity -> in addition to normal output, line info should be printed.
TEST_F(DefaultListTests_Fixture_824, HighVerbosity_IncludesLineInfo_824) {
    defaultListTests(out, &colour, tests, /*isFiltered=*/false, Verbosity::High);

    const std::string s = out.str();

    // Header for unfiltered listings
    EXPECT_NE(s.find("All available test cases:"), std::string::npos);

    // Names
    EXPECT_NE(s.find("AlphaCase"), std::string::npos);
    EXPECT_NE(s.find("BetaCase"),  std::string::npos);

    // Line info (stringified "file:line" should appear)
    EXPECT_NE(s.find("alpha.cpp"), std::string::npos);
    EXPECT_NE(s.find("beta.cpp"),  std::string::npos);
    // It is reasonable to also expect the line numbers (11 and 22) to be present
    // without tying ourselves to exact formatting by TextFlow::Column.
    EXPECT_NE(s.find("11"), std::string::npos);
    EXPECT_NE(s.find("22"), std::string::npos);

    // Tags still shown at High verbosity (since > Quiet)
    EXPECT_NE(s.find("fast"), std::string::npos);
    EXPECT_NE(s.find("ui"),   std::string::npos);

    // Summary line and flush/newlines
    EXPECT_NE(s.find("test case"), std::string::npos);
    ASSERT_FALSE(s.empty());
    EXPECT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size()-2), std::string("\n\n"));
}
