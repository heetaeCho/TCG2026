// File: tests/ColumnBeginTests_51.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test.
// Adjust the include path if your project structure differs.
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

// Test fixture kept minimal per constraints — no peeking at internals.
class ColumnBeginTest_51 : public ::testing::Test {};

// [Normal] begin() on non-empty text should not equal end()
TEST_F(ColumnBeginTest_51, BeginNotEqualEndOnNonEmpty_51) {
    Column col{"Hello world"};
    auto it = col.begin();
    auto ed = col.end();

    // Observable behavior: non-empty column should start with a valid iterator
    EXPECT_NE(it, ed);
}

// [Boundary] begin() on empty text should equal end()
TEST_F(ColumnBeginTest_51, BeginEqualsEndOnEmpty_51) {
    Column col{""};
    auto it = col.begin();
    auto ed = col.end();

    EXPECT_EQ(it, ed);
}

// [Normal] Multiple calls to begin() are consistent (idempotent)
TEST_F(ColumnBeginTest_51, MultipleBeginCallsAreEqual_51) {
    Column col{"abc"};
    auto it1 = col.begin();
    auto it2 = col.begin();

    EXPECT_EQ(it1, it2);
}

// [Normal] Copy-constructed iterator compares equal to original begin()
TEST_F(ColumnBeginTest_51, CopyConstructedIteratorEqualToBegin_51) {
    Column col{"Sample"};
    auto it = col.begin();
    auto copy = it; // copy-construct

    EXPECT_EQ(it, copy);
}

// [Normal] Post-increment from begin() is well-formed and makes progress on short text
// For a short word that fits within default width, we expect exactly one iteration.
// After a single post-increment, iterator should reach end().
TEST_F(ColumnBeginTest_51, PostIncrementReachesEndForSingleChunk_51) {
    Column col{"Hi"};
    auto it = col.begin();
    auto ed = col.end();

    // Sanity: non-empty -> begin != end
    ASSERT_NE(it, ed);

    auto before = it++;
    // The "before" should have been a valid position
    EXPECT_NE(before, ed);
    // After consuming the single chunk/line, iterator should now be end
    EXPECT_EQ(it, ed);
}

// [Normal/Const-correctness] begin() must be callable on const objects and support range-for
TEST_F(ColumnBeginTest_51, ConstBeginUsableInRangeFor_51) {
    const Column col{"OneLine"};
    size_t count = 0;

    // We do not assert on the dereferenced values (internal formatting is a black box).
    // We only count iterations to verify iterability from const.
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }

    // For a short string that fits default width, expect exactly one iteration.
    EXPECT_EQ(count, 1u);
}

// [Boundary/Progress] Iterating from begin() to end() should terminate in finite steps
// (defensive check to ensure iterator progresses and does not loop forever).
TEST_F(ColumnBeginTest_51, IteratorTerminatesWithinReasonableSteps_51) {
    Column col{
        "This is a somewhat longer sentence intended only to ensure "
        "that advancing the iterator eventually reaches end()."
    };

    auto it = col.begin();
    auto ed = col.end();

    // If empty, it == ed and the loop will not run; that's fine.
    // Otherwise, we loop with a guard to ensure termination.
    size_t steps = 0;
    const size_t kSafetyCap = 1000; // generous upper bound; should never be hit

    while (it != ed && steps < kSafetyCap) {
        ++it;
        ++steps;
    }

    // We either started at end (empty) or reached end within the safety cap.
    EXPECT_LT(steps, kSafetyCap);
}
