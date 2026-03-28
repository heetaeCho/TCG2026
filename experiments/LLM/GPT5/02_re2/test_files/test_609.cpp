// File: nfa_constructor_test_609.cc
#include <gtest/gtest.h>
#include "re2/prog.h"
#include "re2/nfa.cc"  // or the appropriate header that declares re2::NFA

namespace re2 {

// Basic sanity: constructing with a default Prog should succeed and not throw.
// (Observable: no crash/exception.)
TEST(NFAConstructorTest_609, ConstructWithDefaultProg_NoThrow_609) {
  Prog prog;  // default constructed
  // Construction itself is the observable behavior: it should not crash or throw.
  EXPECT_NO_THROW({
    NFA nfa(&prog);
  });
}

// The constructor reads from Prog but must not modify observable Prog state.
// We check various observable fields via public getters.
TEST(NFAConstructorTest_609, DoesNotModifyProgObservableState_609) {
  Prog prog;

  // Arrange: set a variety of observable fields.
  prog.set_start(123);
  prog.set_start_unanchored(456);
  prog.set_anchor_start(true);
  prog.set_anchor_end(true);
  prog.set_dfa_mem(987654321LL);
  // Also flip reversed flag if available via setter.
  prog.set_reversed(true);

  // Capture baseline via public getters.
  const int start_before = prog.start();
  const int start_unanchored_before = prog.start_unanchored();
  const bool anchor_start_before = prog.anchor_start();
  const bool anchor_end_before = prog.anchor_end();
  const int64_t dfa_mem_before = prog.dfa_mem();
  const bool reversed_before = prog.reversed();

  // Act: construct NFA
  NFA nfa(&prog);

  // Assert: observable Prog state is unchanged.
  EXPECT_EQ(start_before, prog.start());
  EXPECT_EQ(start_unanchored_before, prog.start_unanchored());
  EXPECT_EQ(anchor_start_before, prog.anchor_start());
  EXPECT_EQ(anchor_end_before, prog.anchor_end());
  EXPECT_EQ(dfa_mem_before, prog.dfa_mem());
  EXPECT_EQ(reversed_before, prog.reversed());
}

// Boundary-ish check: default Prog typically has size() == 0;
// constructing NFA should not alter Prog size (observable by getter).
TEST(NFAConstructorTest_609, DoesNotChangeProgSize_609) {
  Prog prog;
  const int size_before = prog.size();  // observable
  NFA nfa(&prog);
  EXPECT_EQ(size_before, prog.size());
}

// Exceptional/error case observable via death test: passing nullptr is invalid
// because the constructor immediately dereferences 'prog' (based on interface usage).
// We expect a crash (death) when constructed with nullptr.
TEST(NFAConstructorDeathTest_609, NullProgPointerCausesDeath_609) {
#ifndef NDEBUG
  // In debug builds we expect a CHECK/assertion or null deref crash.
  ASSERT_DEATH(
      {
        NFA* nfa = nullptr;
        // Use a separate block to ensure construction attempt is the only action.
        nfa = new NFA(static_cast<Prog*>(nullptr));
        // Prevent unused variable warnings, though we never get here.
        delete nfa;
      },
      ".*");
#else
  // In release builds, behavior on nullptr may be undefined; at minimum ensure it crashes or throws.
  // If the environment doesn't support death tests in release, we still try to assert death.
  ASSERT_DEATH(
      {
        NFA* nfa = new NFA(static_cast<Prog*>(nullptr));
        delete nfa;
      },
      ".*");
#endif
}

}  // namespace re2
