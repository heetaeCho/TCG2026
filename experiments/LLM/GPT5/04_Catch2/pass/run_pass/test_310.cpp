// File: tests/totals_delta_310_tests.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/catch_totals.hpp"

using Catch::Counts;
using Catch::Totals;

namespace {

// Helpers to keep tests readable (use only public interface)
Totals makeTotalsWithAssertions(uint64_t passed, uint64_t failed, uint64_t failedButOk, uint64_t skipped) {
    Totals t;
    t.assertions.passed = passed;
    t.assertions.failed = failed;
    t.assertions.failedButOk = failedButOk;
    t.assertions.skipped = skipped;
    return t;
}

} // namespace

// Normal case: no new assertions -> considered a passed test case
TEST(TotalsDeltaTest_310, Delta_NoNewAssertions_IncrementsPassedCase_310) {
    Totals prev = makeTotalsWithAssertions(5, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(5, 0, 0, 0);

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.passed, 1u);
    EXPECT_EQ(diff.testCases.failed, 0u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
}

// Normal case: new failed assertions -> one failed test case recorded
TEST(TotalsDeltaTest_310, Delta_NewFailedAssertions_IncrementsFailedCase_310) {
    Totals prev = makeTotalsWithAssertions(2, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(3, 2, 0, 0); // some additional passed too, but failures are decisive

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.failed, 1u);
    EXPECT_EQ(diff.testCases.passed, 0u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
}

// Normal case: new failed-but-ok assertions (no new failures) -> one failedButOk test case
TEST(TotalsDeltaTest_310, Delta_NewFailedButOk_IncrementsFailedButOkCase_310) {
    Totals prev = makeTotalsWithAssertions(10, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(12, 0, 3, 0);

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.failedButOk, 1u);
    EXPECT_EQ(diff.testCases.passed, 0u);
    EXPECT_EQ(diff.testCases.failed, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
}

// Normal case: new skipped assertions only -> one skipped test case
TEST(TotalsDeltaTest_310, Delta_NewSkipped_IncrementsSkippedCase_310) {
    Totals prev = makeTotalsWithAssertions(4, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(4, 0, 0, 2);

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.skipped, 1u);
    EXPECT_EQ(diff.testCases.passed, 0u);
    EXPECT_EQ(diff.testCases.failed, 0u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
}

// Normal case: only new passed assertions -> one passed test case
TEST(TotalsDeltaTest_310, Delta_OnlyNewPassedAssertions_IncrementsPassedCase_310) {
    Totals prev = makeTotalsWithAssertions(0, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(7, 0, 0, 0);

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.passed, 1u);
    EXPECT_EQ(diff.testCases.failed, 0u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
}

// Boundary: multiple new failures still count as a single failed test case
TEST(TotalsDeltaTest_310, Delta_MultipleNewFailures_CountsAsSingleFailedCase_310) {
    Totals prev = makeTotalsWithAssertions(0, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(0, 5, 0, 0);

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.failed, 1u);
    EXPECT_EQ(diff.testCases.passed, 0u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
}

// Boundary: precedence — failed > failedButOk > skipped
TEST(TotalsDeltaTest_310, Delta_Priority_FailedBeatsOthers_310) {
    Totals prev = makeTotalsWithAssertions(1, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(2, 1, 2, 3); // all three increased; failed should dominate

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.failed, 1u);
    EXPECT_EQ(diff.testCases.failedButOk, 0u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
    EXPECT_EQ(diff.testCases.passed, 0u);
}

// Boundary: precedence — failedButOk beats skipped when there are no new failures
TEST(TotalsDeltaTest_310, Delta_Priority_FailedButOkBeatsSkipped_310) {
    Totals prev = makeTotalsWithAssertions(0, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(0, 0, 1, 5); // no failures; both fbo and skipped increased

    Totals diff = now.delta(prev);

    EXPECT_EQ(diff.testCases.failedButOk, 1u);
    EXPECT_EQ(diff.testCases.skipped, 0u);
    EXPECT_EQ(diff.testCases.failed, 0u);
    EXPECT_EQ(diff.testCases.passed, 0u);
}

// Behavior check: delta should not mutate the inputs
TEST(TotalsDeltaTest_310, Delta_DoesNotMutateInputs_310) {
    Totals prev = makeTotalsWithAssertions(3, 0, 0, 0);
    Totals now  = makeTotalsWithAssertions(5, 0, 0, 0);

    Totals prevCopy = prev;
    Totals nowCopy  = now;

    (void)now.delta(prev);

    // Inputs remain unchanged
    EXPECT_EQ(prev.assertions.passed, prevCopy.assertions.passed);
    EXPECT_EQ(prev.assertions.failed, prevCopy.assertions.failed);
    EXPECT_EQ(prev.assertions.failedButOk, prevCopy.assertions.failedButOk);
    EXPECT_EQ(prev.assertions.skipped, prevCopy.assertions.skipped);

    EXPECT_EQ(now.assertions.passed, nowCopy.assertions.passed);
    EXPECT_EQ(now.assertions.failed, nowCopy.assertions.failed);
    EXPECT_EQ(now.assertions.failedButOk, nowCopy.assertions.failedButOk);
    EXPECT_EQ(now.assertions.skipped, nowCopy.assertions.skipped);

    // No assumptions about testCases fields in inputs; only ensuring no mutation of assertions.
}

