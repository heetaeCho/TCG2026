// File: ./TestProjects/re2/re2/tests/prog_list_count_119_test.cc

#include "gtest/gtest.h"
#include "re2/prog.h"

namespace {

using re2::Prog;

// A simple fixture in case future setup/teardown is needed.
class ProgListCountTest_119 : public ::testing::Test {};

// [Normal] Freshly constructed object exposes an observable initial value.
TEST_F(ProgListCountTest_119, DefaultIsDeterministic_119) {
  Prog p;
  // Only observable behavior: call list_count() and assert a concrete value.
  // The provided constructor in the known deps initializes it to 0, and this
  // is observable via the public getter.
  EXPECT_EQ(0, p.list_count());
}

// [Boundary] Repeated calls should be stable (no hidden side effects).
TEST_F(ProgListCountTest_119, RepeatedCallsAreIdempotent_119) {
  Prog p;
  int first = p.list_count();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(first, p.list_count()) << "list_count() changed across calls";
  }
}

// [Boundary] Multiple independent instances should not affect each other.
TEST_F(ProgListCountTest_119, IndependentInstancesHaveIndependentState_119) {
  Prog a;
  Prog b;

  // Observable: both start with the same visible value.
  EXPECT_EQ(0, a.list_count());
  EXPECT_EQ(0, b.list_count());

  // No public API to mutate list_count_, so we only verify independence at creation.
  // (This guards against accidental shared state.)
  EXPECT_EQ(a.list_count(), b.list_count());
}

// [Robustness] Using a const-qualified reference should still allow reading.
TEST_F(ProgListCountTest_119, CallableThroughConstReference_119) {
  Prog p;
  const Prog& cp = p;
  EXPECT_EQ(0, cp.list_count());
}

}  // namespace
