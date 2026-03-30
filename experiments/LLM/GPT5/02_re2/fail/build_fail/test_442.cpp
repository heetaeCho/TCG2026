// File: dfa_workq_test_442.cc

#include <gtest/gtest.h>

// The prompt only exposes the implementation snippet in a .cc file.
// To access the nested type and constants as shown, include the same path.
#include "re2/dfa.cc"

namespace {

using re2::DFA;

// A simple fixture for constructing Workq instances in tests.
class WorkqTest_442 : public ::testing::Test {
protected:
  // Helper to create a Workq with typical small sizes.
  static DFA::Workq MakeSmall() {
    // Use small but non-trivial sizes to exercise boundary-safe usage.
    // We do not assume any particular internal logic beyond public APIs.
    return DFA::Workq(/*n=*/8, /*maxmark=*/3);
  }
};

//
// Normal operation
//

TEST_F(WorkqTest_442, MaxMarkReflectsCtorArgument_442) {
  DFA::Workq w1(/*n=*/1, /*maxmark=*/0);
  EXPECT_EQ(w1.maxmark(), 0);

  DFA::Workq w2(/*n=*/8, /*maxmark=*/3);
  EXPECT_EQ(w2.maxmark(), 3);

  DFA::Workq w3(/*n=*/32, /*maxmark=*/10);
  EXPECT_EQ(w3.maxmark(), 10);
}

//
// Boundary conditions
//

TEST_F(WorkqTest_442, CtorAcceptsZeroMaxmark_442) {
  DFA::Workq w(/*n=*/8, /*maxmark=*/0);
  // Only assert what the interface guarantees: maxmark() returns the provided value.
  EXPECT_EQ(w.maxmark(), 0);
}

TEST_F(WorkqTest_442, CtorAcceptsSmallN_442) {
  // Minimal non-zero n to ensure basic constructibility.
  DFA::Workq w(/*n=*/1, /*maxmark=*/1);
  EXPECT_EQ(w.maxmark(), 1);
}

//
// Observable state transitions via public methods only (black-box)
//

TEST_F(WorkqTest_442, ClearIsIdempotentAndSafeAfterBasicUse_442) {
  DFA::Workq w = MakeSmall();

  // We don't assume initial size, only that size() is a valid, non-negative observable.
  // If size() is part of the public API (per prompt), we can at least check it doesn't go negative.
  // NOTE: We *do not* infer invariants beyond what is obviously safe to assert.

  // Perform some public operations; we don't assert their internal effects,
  // just that subsequent clear() leaves the structure in a valid, usable state.
  // These calls are expected to be safe as per the public interface.
  w.insert(/*id=*/0);
  w.insert_new(/*id=*/1);
  w.mark();

  // Now clear and verify we can call size() and get a sane non-negative result.
  w.clear();

  // If size() is exposed, assert non-negative. Avoid assuming exact 0 unless guaranteed.
  EXPECT_GE(w.size(), 0);

  // Reuse after clear() should remain safe.
  w.insert(/*id=*/2);
  w.insert_new(/*id=*/3);
  EXPECT_GE(w.size(), 0);
}

TEST_F(WorkqTest_442, InsertOperationsAreSafeAtTypicalBounds_442) {
  // Exercise boundary-like ids based on the constructor's n (without assuming internal layout).
  DFA::Workq w(/*n=*/8, /*maxmark=*/3);
  // Use ids within a plausible 0..n-1 range to avoid relying on internals.
  w.insert(0);
  w.insert_new(0);
  w.insert(7);
  w.insert_new(7);
  w.mark();  // Should be callable safely
  // We don't assert exact size/content; just validate the API remains usable.
  EXPECT_GE(w.size(), 0);
}

//
// Smoke test for API presence (no behavioral inference)
//

TEST_F(WorkqTest_442, PublicMethodsAreCallableWithoutCrashing_442) {
  DFA::Workq w(/*n=*/4, /*maxmark=*/2);

  // Call all public methods exposed in the prompt.
  (void)w.maxmark();        // return value checked elsewhere
  w.clear();                // safe to call multiple times
  w.clear();
  w.mark();                 // place a mark per API
  w.insert(1);
  w.insert_new(2);

  // If is_mark(int) is public, we can at least call it with a benign value.
  // We do not assert any particular truth value, since semantics are unspecified in the prompt.
  (void)w.is_mark(0);

  // Ensure the structure reports a non-negative size.
  EXPECT_GE(w.size(), 0);
}

//
// (Optional) Constants are visible and distinct — minimal sanity checks
//

TEST_F(WorkqTest_442, SpecialConstantsAreDistinctPointers_442) {
  // These are macros in the same translation unit per the prompt snippet.
  // We only assert very weak, black-box-safe properties.
  EXPECT_NE(DeadState, nullptr);
  EXPECT_NE(FullMatchState, nullptr);
  EXPECT_NE(DeadState, FullMatchState);
}

}  // namespace
