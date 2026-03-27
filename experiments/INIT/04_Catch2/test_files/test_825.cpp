// File: tests/print_test_run_totals_825.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Catch2 headers (adjust include paths to your tree if needed)
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_console_colour.hpp"

using namespace Catch;

namespace {

// Utility: build Totals in a readable way without touching internals
Totals makeTotals(
    uint64_t tc_passed, uint64_t tc_failed, uint64_t tc_failedOk, uint64_t tc_skipped,
    uint64_t as_passed, uint64_t as_failed, uint64_t as_failedOk, uint64_t as_skipped) {
    Totals t;
    t.testCases.passed      = tc_passed;
    t.testCases.failed      = tc_failed;
    t.testCases.failedButOk = tc_failedOk;
    t.testCases.skipped     = tc_skipped;

    t.assertions.passed      = as_passed;
    t.assertions.failed      = as_failed;
    t.assertions.failedButOk = as_failedOk;
    t.assertions.skipped     = as_skipped;

    return t;
}

// A minimal colour impl to satisfy the API; we do not assert on colours.
// Passing nullptr to the real ColourImpl is typically fine for Catch2; if your
// build requires a valid IStream, replace with an appropriate instance.
struct NoopColourImpl : ColourImpl {
    NoopColourImpl() : ColourImpl(nullptr) {}
};

} // namespace

// -----------------------------------------------------------------------------
// Normal case: no tests ran -> exact message line
// -----------------------------------------------------------------------------
TEST(PrintTestRunTotalsTest_825, NoTestsRan_PrintsNotice_825) {
    std::ostringstream os;
    NoopColourImpl colour;

    Totals totals = makeTotals(
        /*tc_passed*/0, /*tc_failed*/0, /*tc_failedOk*/0, /*tc_skipped*/0,
        /*as_passed*/0, /*as_failed*/0, /*as_failedOk*/0, /*as_skipped*/0);

    printTestRunTotals(os, colour, totals);

    const std::string out = os.str();
    // We do not check for any color codes; only the stable text.
    EXPECT_NE(out.find("No tests ran"), std::string::npos);
    // The implementation appends a newline; do a light check it ends with '\n'
    EXPECT_EQ(out.back(), '\n');
}

// -----------------------------------------------------------------------------
// All tests passed summary path (assertions > 0 and all test cases passed)
// Verifies message contains counts & pluralization-friendly substrings.
// -----------------------------------------------------------------------------
TEST(PrintTestRunTotalsTest_825, AllTestsPassed_MessageIncludesCounts_825) {
    std::ostringstream os;
    NoopColourImpl colour;

    // assertions.total() > 0 and all test cases passed => "All tests passed ..."
    Totals totals = makeTotals(
        /*tc_passed*/2, /*tc_failed*/0, /*tc_failedOk*/0, /*tc_skipped*/0,
        /*as_passed*/3, /*as_failed*/0, /*as_failedOk*/0, /*as_skipped*/0);

    printTestRunTotals(os, colour, totals);

    const std::string out = os.str();
    EXPECT_NE(out.find("All tests passed"), std::string::npos);

    // These substrings should appear regardless of colour/spacing
    // e.g. "(3 assertions in 2 test cases)"
    EXPECT_NE(out.find("3"), std::string::npos);
    EXPECT_NE(out.find("assertion"), std::string::npos); // "assertion(s)" via pluralise
    EXPECT_NE(out.find("2"), std::string::npos);
    EXPECT_NE(out.find("test case"), std::string::npos); // "test case(s)" via pluralise

    // The implementation appends a newline at the end
    EXPECT_EQ(out.back(), '\n');
}

// -----------------------------------------------------------------------------
// Mixed results -> tabular summary path.
// We avoid formatting assumptions by checking for presence of row labels and
// the relevant numbers in output.
// -----------------------------------------------------------------------------
TEST(PrintTestRunTotalsTest_825, MixedResults_PrintsSummaryRowsAndColumns_825) {
    std::ostringstream os;
    NoopColourImpl colour;

    // Setup: a mix including skipped and "failed as expected"
    // Total test cases: 2 passed, 1 failed, 1 failedButOk, 1 skipped => 5 total
    // Assertions: 4 passed, 2 failed, 1 failedButOk, 3 skipped => total 10,
    // but the "total assertion count" printed is total - skipped = 7.
    Totals totals = makeTotals(
        /*tc_passed*/2, /*tc_failed*/1, /*tc_failedOk*/1, /*tc_skipped*/1,
        /*as_passed*/4, /*as_failed*/2, /*as_failedOk*/1, /*as_skipped*/3);

    printTestRunTotals(os, colour, totals);

    const std::string out = os.str();

    // Row labels that should exist
    EXPECT_NE(out.find("test cases"), std::string::npos);
    EXPECT_NE(out.find("assertions"), std::string::npos);

    // Column labels that should exist
    EXPECT_NE(out.find("passed"), std::string::npos);
    EXPECT_NE(out.find("failed"), std::string::npos);
    EXPECT_NE(out.find("skipped"), std::string::npos);
    EXPECT_NE(out.find("failed as expected"), std::string::npos);

    // Numbers that should appear somewhere in the summary.
    // Test cases row first column shows total test cases (5)
    EXPECT_NE(out.find("5"), std::string::npos);

    // Assertions row first column shows total assertions minus skipped (7)
    // We don't rely on exact column placement, just presence.
    EXPECT_NE(out.find("7"), std::string::npos);

    // Spot-check presence of other counts we fed in:
    // passed: tc=2, as=4
    EXPECT_NE(out.find("2"), std::string::npos);
    EXPECT_NE(out.find("4"), std::string::npos);
    // failed: tc=1, as=2
    // (already checked "2" above; also look for "1")
    EXPECT_NE(out.find("1"), std::string::npos);
    // skipped: tc=1, as row shows 0 by design; we at least see "0"
    EXPECT_NE(out.find("0"), std::string::npos);
    // failed as expected: tc=1, as=1
    // "1" already checked; presence is sufficient without formatting reliance
}

// -----------------------------------------------------------------------------
// Edge: assertions.total() == 0 but some tests exist (e.g., all skipped).
// Should go through the summary path, not the "All tests passed" path.
// -----------------------------------------------------------------------------
TEST(PrintTestRunTotalsTest_825, ZeroAssertions_SummaryStillPrinted_825) {
    std::ostringstream os;
    NoopColourImpl colour;

    Totals totals = makeTotals(
        /*tc_passed*/0, /*tc_failed*/0, /*tc_failedOk*/0, /*tc_skipped*/3,
        /*as_passed*/0, /*as_failed*/0, /*as_failedOk*/0, /*as_skipped*/0);

    printTestRunTotals(os, colour, totals);

    const std::string out = os.str();

    // Should NOT be the "no tests ran" special case (there are 3 skipped test cases)
    EXPECT_EQ(out.find("No tests ran"), std::string::npos);

    // Should NOT be the "all tests passed" path because assertions.total() == 0
    EXPECT_EQ(out.find("All tests passed"), std::string::npos);

    // Should contain summary row labels
    EXPECT_NE(out.find("test cases"), std::string::npos);
    EXPECT_NE(out.find("assertions"), std::string::npos);

    // Presence of "skipped" column and expected numbers
    EXPECT_NE(out.find("skipped"), std::string::npos);
    EXPECT_NE(out.find("3"), std::string::npos); // total/skipped test cases visible somewhere
}

