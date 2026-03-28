// File: prog_set_reversed_test_118.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

using re2::Prog;

// NOTE: Tests rely ONLY on observable behavior through the public API.
// We do not assume or inspect private state.

// Default behavior: a freshly constructed Prog should report a concrete
// (observable) reversed() value. We verify it and then only use the API to
// change & read it in subsequent tests.

TEST(ProgReversedTest_118, DefaultIsFalse_118) {
  Prog p;
  // Observable expectation: initial reversed() state is false
  // (verified via the public getter).
  EXPECT_FALSE(p.reversed());
}

TEST(ProgReversedTest_118, SetTrueThenGetTrue_118) {
  Prog p;
  p.set_reversed(true);
  EXPECT_TRUE(p.reversed());
}

TEST(ProgReversedTest_118, ToggleTrueThenFalse_118) {
  Prog p;
  p.set_reversed(true);
  ASSERT_TRUE(p.reversed());  // sanity check via public API
  p.set_reversed(false);
  EXPECT_FALSE(p.reversed());
}

TEST(ProgReversedTest_118, IdempotentWhenSettingSameValueTrue_118) {
  Prog p;
  p.set_reversed(true);
  ASSERT_TRUE(p.reversed());
  // Setting the same value again should leave the observable state unchanged.
  p.set_reversed(true);
  EXPECT_TRUE(p.reversed());
}

TEST(ProgReversedTest_118, IdempotentWhenSettingSameValueFalse_118) {
  Prog p;
  // Start from default observed state, then set to false explicitly,
  // and verify no change when setting false again.
  p.set_reversed(false);
  ASSERT_FALSE(p.reversed());
  p.set_reversed(false);
  EXPECT_FALSE(p.reversed());
}

TEST(ProgReversedTest_118, MultipleInstancesIndependent_118) {
  Prog a;
  Prog b;

  // Change only one instance and verify independence through public API.
  a.set_reversed(true);

  EXPECT_TRUE(a.reversed());
  EXPECT_FALSE(b.reversed());
}

TEST(ProgReversedTest_118, WorksWithConstAccess_118) {
  Prog p;
  p.set_reversed(true);
  const Prog& cp = p;
  // Ensure the observable state is retrievable via a const-qualified access.
  EXPECT_TRUE(cp.reversed());
}
