// File: pcre_hitlimit_test.cc
#include <gtest/gtest.h>
#include "re2/util/pcre.h"

using re2::PCRE;

class PCRE_HitLimitTest_197 : public ::testing::Test {
protected:
    // Use the simplest available constructor from the public interface.
    // We do not make assumptions about internal initialization beyond
    // what is observable via public methods.
    PCRE MakeSimple() {
        return PCRE("a");  // Treat as a benign, valid pattern.
    }
};

// [Normal] HitLimit is a stable, query-only check (no side effects).
TEST_F(PCRE_HitLimitTest_197, HitLimit_IsIdempotent_197) {
    PCRE re = MakeSimple();

    const bool first = re.HitLimit();
    const bool second = re.HitLimit();
    const bool third = re.HitLimit();

    // Calling HitLimit repeatedly should not, by itself, change the result.
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// [Boundary] Immediately after construction, ClearHitLimit keeps/sets the state to "not hit".
TEST_F(PCRE_HitLimitTest_197, ClearHitLimit_MakesNotHit_197) {
    PCRE re = MakeSimple();

    // Regardless of initial state, after ClearHitLimit() we expect "no limit hit".
    re.ClearHitLimit();
    EXPECT_FALSE(re.HitLimit());

    // Calling ClearHitLimit() again should remain "not hit".
    re.ClearHitLimit();
    EXPECT_FALSE(re.HitLimit());
}

// [Behavioral contract] ClearHitLimit does not flip to "hit" on its own.
TEST_F(PCRE_HitLimitTest_197, ClearHitLimit_HasNoAdverseSideEffects_197) {
    PCRE re = MakeSimple();

    // Snapshot the current state, clear, and verify we are not "hit".
    const bool before = re.HitLimit();
    re.ClearHitLimit();
    // After a clear operation, HitLimit should be false (i.e., not hit).
    EXPECT_FALSE(re.HitLimit());

    // And subsequent calls to HitLimit remain consistent (no hidden mutation).
    EXPECT_FALSE(re.HitLimit());

    // If the initial snapshot already was false, we've verified stability;
    // if it was true, we've verified that ClearHitLimit successfully resets
    // to a not-hit state and remains there.
    (void)before; // Silence unused warning in case builds enable -Wunused.
}
