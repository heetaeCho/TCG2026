// File: dfa_statesaver_test_605.cc
#include <gtest/gtest.h>

namespace re2 {
// Forward declarations sufficient for testing the public interface
class DFA {
 public:
  struct State;
  class StateSaver {
   public:
    explicit StateSaver(DFA* dfa, State* state);
    ~StateSaver();
    State* Restore();
  };
};
}  // namespace re2

using re2::DFA;

// NOTE: We intentionally avoid including or relying on internal headers or
// private state. We only use the public constructor, destructor, and Restore().
// The tests below exercise behavior that is observable for "special states".

class DFASpecialStateSaverTest_605 : public ::testing::Test {};

// Tests that constructing with the "dead state" special pointer and restoring
// yields the same special pointer. This validates observable behavior without
// assuming internal implementation details.
TEST_F(DFASpecialStateSaverTest_605, RestoreReturnsSamePointerForDeadState_605) {
  // DeadState is represented by the special integral pointer value 1
  // per the provided partial code. We avoid depending on macros by using
  // the same value directly.
  auto* const kDeadState = reinterpret_cast<DFA::State*>(1);

  DFA* dummy_dfa = nullptr;  // Not dereferenced by the observable path we test.
  DFA::StateSaver saver(dummy_dfa, kDeadState);

  DFA::State* restored = saver.Restore();
  EXPECT_EQ(restored, kDeadState);
}

// Tests that constructing with the "full match" special pointer and restoring
// yields the same special pointer. Again, this is purely observable behavior.
TEST_F(DFASpecialStateSaverTest_605, RestoreReturnsSamePointerForFullMatchState_605) {
  // FullMatchState is represented by the special integral pointer value 2.
  auto* const kFullMatchState = reinterpret_cast<DFA::State*>(2);

  DFA* dummy_dfa = nullptr;  // Not dereferenced by the observable path we test.
  DFA::StateSaver saver(dummy_dfa, kFullMatchState);

  DFA::State* restored = saver.Restore();
  EXPECT_EQ(restored, kFullMatchState);
}

// Smoke test: constructing and destroying with a special state should not crash.
// This ensures basic lifecycle behavior is valid via the public interface.
TEST_F(DFASpecialStateSaverTest_605, ConstructAndDestructWithSpecialStateDoesNotCrash_605) {
  auto* const kDeadState = reinterpret_cast<DFA::State*>(1);
  DFA* dummy_dfa = nullptr;
  {
    DFA::StateSaver saver(dummy_dfa, kDeadState);
    // No further action; scope exit triggers destructor.
  }
  SUCCEED();
}
