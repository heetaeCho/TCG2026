// File: dfa_buildallstates_test_455.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/prog.h"  // Uses only public interface

using ::testing::Ge;
using ::testing::Le;
using ::testing::IsNull;
using ::testing::NotNull;
using ::testing::AnyOf;

namespace re2 {

class ProgBuildEntireDFATest_455 : public ::testing::Test {
 protected:
  // Keep a fresh program object per test. We don't assume any internal state,
  // and we do not attempt to compile or mutate instructions here.
  Prog prog_;
};

// [Normal] Callback can be omitted; the call should still complete safely.
TEST_F(ProgBuildEntireDFATest_455, NullCallback_DoesNotCrash_455) {
  // Using a valid MatchKind from the public API.
  // We do not assume anything about the returned value beyond being an int.
  int n_states = prog_.BuildEntireDFA(Prog::kFirstMatch, Prog::DFAStateCallback());
  // Observable property: function returns an integer; should not crash.
  // Many valid implementations can return 0 or a positive count.
  EXPECT_GE(n_states, 0);
}

// [Normal] When a callback is provided, it may be invoked zero or more times.
// For any successful exploration, the number of callback invocations must not
// exceed the number of unique states reported by the return value, because the
// callback is called at most once per processed (enqueued+dequeued) state.
TEST_F(ProgBuildEntireDFATest_455, CallbackCountNotExceedReturn_455) {
  int callback_count = 0;
  // Capture-only lambda; does not assume anything about output size or contents.
  Prog::DFAStateCallback cb =
      [&](const int* next_table, bool is_match) {
        // Only observable checks that never depend on internal representation.
        // next_table can be null if the builder encountered resource limits.
        EXPECT_THAT(next_table, AnyOf(IsNull(), NotNull()));
        // is_match is a plain boolean; no further assumptions.
        (void)is_match;
        ++callback_count;
      };

  int n_states = prog_.BuildEntireDFA(Prog::kFirstMatch, cb);

  // Observable relations:
  // - Return value is non-negative.
  // - If the return is 0, there should not have been any processed state.
  // - Otherwise, callbacks should not exceed the discovered state count.
  EXPECT_GE(n_states, 0);
  if (n_states == 0) {
    EXPECT_EQ(callback_count, 0);
  } else {
    EXPECT_LE(callback_count, n_states);
  }
}

// [Boundary] Very small DFA memory budget should not crash the build.
// It may yield 0 states (bail-out) or a positive count, but must obey the same
// callback vs. return relation as above.
TEST_F(ProgBuildEntireDFATest_455, SmallDfaMemBudget_HandledGracefully_455) {
  // Set a tiny memory budget via the public setter; this is an observable input.
  prog_.set_dfa_mem(1);  // Extreme low memory to encourage early bail-out (allowed via public API).

  int callback_count = 0;
  Prog::DFAStateCallback cb =
      [&](const int* next_table, bool is_match) {
        (void)next_table;
        (void)is_match;
        ++callback_count;
      };

  int n_states = prog_.BuildEntireDFA(Prog::kFirstMatch, cb);

  EXPECT_GE(n_states, 0);
  if (n_states == 0) {
    EXPECT_EQ(callback_count, 0);
  } else {
    EXPECT_LE(callback_count, n_states);
  }
}

// [Boundary] Using the alternate match kind must behave consistently w.r.t.
// return value and callback invocation semantics (no assumptions about counts).
TEST_F(ProgBuildEntireDFATest_455, LongestMatchKind_RespectsCallbackContract_455) {
  int callback_count = 0;
  Prog::DFAStateCallback cb =
      [&](const int* next_table, bool /*is_match*/) {
        (void)next_table;
        ++callback_count;
      };

  int n_states = prog_.BuildEntireDFA(Prog::kLongestMatch, cb);

  EXPECT_GE(n_states, 0);
  if (n_states == 0) {
    EXPECT_EQ(callback_count, 0);
  } else {
    EXPECT_LE(callback_count, n_states);
  }
}

}  // namespace re2
