// File: dfa_statesaver_restore_test_452.cc

#include <gtest/gtest.h>

namespace re2 {

// Forward declarations that match the provided interface snippets.
class DFA {
 public:
  class State;
  class StateSaver {
   public:
    explicit StateSaver(DFA* dfa, State* state);
    ~StateSaver();
    State* Restore();
  };
};

}  // namespace re2

// The partial code shows these macros defined in dfa.cc.
// We recreate the same constants here to construct the "special" states
// that StateSaver is expected to short-circuit-return from Restore().
namespace {
using re2::DFA;

// Mirrors the values shown in the provided partial implementation.
#define DeadState reinterpret_cast<DFA::State*>(1)
#define FullMatchState reinterpret_cast<DFA::State*>(2)

}  // namespace

// --- Tests ---

// Verifies: When constructed with the "dead" special state, Restore()
// returns that same special state (observable behavior), without requiring
// any access to private/internal DFA internals.
TEST(DFA_StateSaverRestore_452, Restore_ReturnsDeadState_WhenSpecial_452) {
  re2::DFA* dfa = nullptr;  // Allowed: Restore should short-circuit for special states.
  DFA::StateSaver saver(dfa, DeadState);

  DFA::State* restored = saver.Restore();

  ASSERT_EQ(restored, DeadState) << "Restore() must return the same special dead state.";
}

// Verifies: When constructed with the "full match" special state, Restore()
// returns that same special state.
TEST(DFA_StateSaverRestore_452, Restore_ReturnsFullMatchState_WhenSpecial_452) {
  re2::DFA* dfa = nullptr;  // Not used by Restore() for special states.
  DFA::StateSaver saver(dfa, FullMatchState);

  DFA::State* restored = saver.Restore();

  ASSERT_EQ(restored, FullMatchState) << "Restore() must return the same special full-match state.";
}

// Verifies a boundary/safety condition we can observe via the interface:
// With a null DFA pointer, Restore() still succeeds when the input state is
// special (because it should short-circuit and not dereference the DFA).
TEST(DFA_StateSaverRestore_452, Restore_DoesNotDependOnDFA_ForSpecialStates_452) {
  re2::DFA* dfa = nullptr;
  DFA::StateSaver saver_dead(dfa, DeadState);
  DFA::StateSaver saver_full(dfa, FullMatchState);

  EXPECT_EQ(saver_dead.Restore(), DeadState);
  EXPECT_EQ(saver_full.Restore(), FullMatchState);
}

#undef DeadState
#undef FullMatchState
