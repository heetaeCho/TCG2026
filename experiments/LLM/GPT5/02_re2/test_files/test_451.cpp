// File: dfa_statesaver_test_451.cc
#include <gtest/gtest.h>
#include <type_traits>

// The real project should expose DFA/StateSaver via a public header.
// If your tree uses a different include (e.g., "re2/dfa.h"), adjust accordingly.
#include "re2/dfa.h"

namespace {

using re2::DFA;

// Reproduce the *publicly visible/partial* special-state encodings provided in the prompt.
// We NEVER dereference these; we only use them for identity/equality checks, treating
// the implementation as a black box (no inference of internal logic).
static DFA::State* kDeadStatePtr      = reinterpret_cast<DFA::State*>(1);
static DFA::State* kFullMatchStatePtr = reinterpret_cast<DFA::State*>(2);

// Simple fixture to group tests for readability.
class DFAStateSaverTest_451 : public ::testing::Test {};

}  // namespace

// Verifies the class’s copy/assignment constraints are enforced by the type system.
// This uses only the public type and does not rely on internal details.
TEST_F(DFAStateSaverTest_451, TypeTraits_CopyAndAssignAreDisabled_451) {
  // Copy constructible/assignable should be false per the provided interface.
  static_assert(!std::is_copy_constructible<DFA::StateSaver>::value,
                "StateSaver must not be copy-constructible");
  static_assert(!std::is_copy_assignable<DFA::StateSaver>::value,
                "StateSaver must not be copy-assignable");
  SUCCEED();  // Compile-time check is the essence; keep the test green at runtime.
}

// Normal operation (special state): constructing with DeadState should be valid,
// Restore() should return the same pointer, and destruction should not crash.
TEST_F(DFAStateSaverTest_451, Restore_ReturnsSamePointer_ForDeadState_451) {
  DFA dfa;  // Treat as black box; just needed to satisfy the ctor signature.
  DFA::StateSaver saver(&dfa, kDeadStatePtr);

  DFA::State* restored_first = saver.Restore();
  EXPECT_EQ(restored_first, kDeadStatePtr);

  // Calling Restore() again should remain safe and consistent (observable behavior).
  DFA::State* restored_second = saver.Restore();
  EXPECT_EQ(restored_second, kDeadStatePtr);
}

// Normal operation (special state): constructing with FullMatchState should be valid,
// Restore() should return the same pointer, and destruction should not crash.
TEST_F(DFAStateSaverTest_451, Restore_ReturnsSamePointer_ForFullMatchState_451) {
  DFA dfa;  // Black-box DFA
  DFA::StateSaver saver(&dfa, kFullMatchStatePtr);

  DFA::State* restored_first = saver.Restore();
  EXPECT_EQ(restored_first, kFullMatchStatePtr);

  DFA::State* restored_second = saver.Restore();
  EXPECT_EQ(restored_second, kFullMatchStatePtr);
}

// Boundary-ish scenario using multiple special states: ensure independent savers
// do not interfere with each other and each returns its own original pointer.
TEST_F(DFAStateSaverTest_451, MultipleIndependentSavers_WithSpecialStates_451) {
  DFA dfa;  // Black-box DFA

  DFA::StateSaver saver_dead(&dfa, kDeadStatePtr);
  DFA::StateSaver saver_full(&dfa, kFullMatchStatePtr);

  EXPECT_EQ(saver_dead.Restore(), kDeadStatePtr);
  EXPECT_EQ(saver_full.Restore(), kFullMatchStatePtr);

  // Re-check to ensure idempotent observable behavior.
  EXPECT_EQ(saver_dead.Restore(), kDeadStatePtr);
  EXPECT_EQ(saver_full.Restore(), kFullMatchStatePtr);
}

// (Optional boundary check) If nullptr is accepted by the public interface,
// Restore() should round-trip nullptr safely. This test does not assume any
// internal behavior other than "returns a State*"; if your API disallows nullptr,
// feel free to remove this test.
TEST_F(DFAStateSaverTest_451, Restore_AllowsNullptrIfAccepted_451) {
  DFA dfa;  // Black-box DFA
  DFA::State* const input = nullptr;

  DFA::StateSaver saver(&dfa, input);
  DFA::State* restored = saver.Restore();

  // Observable expectation: if nullptr was given, we get nullptr back.
  // If your implementation forbids nullptr at runtime, this test will surface it.
  EXPECT_EQ(restored, nullptr);
}
