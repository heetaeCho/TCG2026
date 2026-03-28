// File: regexp_incref_test_335.cc
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include "re2/regexp.h"

namespace {

using re2::Regexp;

// Small helper to create a simple Regexp instance via public API.
// We avoid relying on internal constructors or state.
static Regexp* MakeSimpleRegexp() {
  // Flags are intentionally zeroed; tests must not infer internal behavior.
  return Regexp::NewLiteral('a', static_cast<Regexp::ParseFlags>(0));
}

// --- Tests ---

// Verifies: Incref returns the same pointer (chainable usage) — normal operation.
TEST(RegexpIncrefTest_335, ReturnsSamePointer_335) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  Regexp* ret = re->Incref();
  EXPECT_EQ(ret, re) << "Incref() should return the same object pointer";

  // Cleanup: balance the extra reference + the original one.
  re->Decref();  // undo the Incref above
  re->Decref();  // drop the factory's initial ref (may delete)
}

// Verifies: Ref() increases by 1 after a single Incref — normal operation.
TEST(RegexpIncrefTest_335, IncreasesRefCountByOne_335) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();  // observable via public API
  re->Incref();
  const int after = re->Ref();

  // For the non-saturation path, Ref() should increase by exactly 1.
  // (If implementation ever saturates, this test still exercises normal path.)
  EXPECT_EQ(after, before + 1) << "Ref() should increase by exactly 1 after Incref()";

  // Cleanup: balance references
  re->Decref();  // undo the Incref above
  re->Decref();  // drop the factory's initial ref
}

// Verifies: Multiple Incref calls increase the observable ref count cumulatively,
// and multiple Decref calls bring it back — boundary-ish (bulk usage) scenario.
TEST(RegexpIncrefTest_335, ManyIncrefThenDecrefRestoresCount_335) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  constexpr int kN = 100;  // keep modest to avoid assumptions about kMaxRef
  for (int i = 0; i < kN; ++i) {
    re->Incref();
  }

  const int mid = re->Ref();
  // In the non-saturation region this should be before + kN.
  // Using equality here (not >=) because kN is small and should not hit saturation.
  EXPECT_EQ(mid, before + kN);

  // Decrease references back to the original count (do not delete yet).
  for (int i = 0; i < kN; ++i) {
    re->Decref();
  }
  const int restored = re->Ref();
  EXPECT_EQ(restored, before) << "Ref count should be restored after paired Decref() calls";

  // Final cleanup: drop the original reference.
  re->Decref();
}

// Verifies: Basic thread-safety/interaction — concurrent increments on the same
// instance reflect in the observable ref count after joining.
// This also indirectly exercises the once-initialization path if the
// implementation uses it internally.
TEST(RegexpIncrefTest_335, ConcurrentIncrefAccumulates_335) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  constexpr int kThreads = 4;
  constexpr int kPerThread = 50;

  auto worker = [re]() {
    for (int i = 0; i < kPerThread; ++i) {
      re->Incref();
    }
  };

  std::vector<std::thread> threads;
  threads.reserve(kThreads);
  for (int i = 0; i < kThreads; ++i) threads.emplace_back(worker);
  for (auto& t : threads) t.join();

  const int after = re->Ref();
  EXPECT_EQ(after, before + kThreads * kPerThread)
      << "Ref() should reflect the total number of increments performed";

  // Bring the count back down to the original value (do not delete yet).
  for (int i = 0; i < kThreads * kPerThread; ++i) {
    re->Decref();
  }
  const int restored = re->Ref();
  EXPECT_EQ(restored, before) << "Ref count should restore after paired Decref()";

  // Final cleanup.
  re->Decref();
}

}  // namespace
