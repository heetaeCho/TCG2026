// File: walker_dtor_reset_test_214.cc
#include <gtest/gtest.h>

// The header under test
#include "re2/walker-inl.h"

namespace {

using re2::Regexp;

// A minimal alias to make the nested template type easier to spell.
// From the (known) interface, Walker is nested under Regexp<T>.
template <typename T>
using WalkerT = typename Regexp::Walker<T>;  // Adjust if your project uses Regexp<T>::Walker

// NOTE:
// We treat Walker as a black box. The only observable contract we can
// assert from the snippet is that ~Walker() invokes Reset() internally.
// Since Reset() has no externally visible effects in the provided interface,
// we verify the safety of destruction in common usage patterns without
// reusing the object post-destruction (which would be UB).

// TEST 1: Basic construction/destruction should be safe.
// Covers: normal operation.
TEST(WalkerDestructor_214, SmokeDestruct_214) {
  // Stack allocation then end-of-scope destruction.
  WalkerT<int> w;
  // If ~Walker() didn't call Reset() safely, this scope exit could crash/throw.
  SUCCEED();
}

// TEST 2: Explicit Reset before destructor should also be safe.
// Covers: boundary/sequence safety (Reset called explicitly, then destructor calls it again).
TEST(WalkerDestructor_214, ResetThenDestructSafe_214) {
  auto* w = new WalkerT<int>();
  // Call Reset() explicitly; destructor will also call Reset().
  w->Reset();
  // Heap destruction path.
  delete w;
  SUCCEED();
}

// TEST 3: Multiple lifetimes should be independently safe.
// Covers: repeated construction/destruction (idempotence of destructor behavior).
TEST(WalkerDestructor_214, MultipleLifetimes_214) {
  {
    WalkerT<float> w1;
    // scope end -> ~Walker()
  }
  {
    WalkerT<void*> w2;
    // scope end -> ~Walker()
  }
  SUCCEED();
}

}  // namespace
