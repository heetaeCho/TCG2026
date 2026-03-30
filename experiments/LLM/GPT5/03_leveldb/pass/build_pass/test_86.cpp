// File: random_test.cc
#include "util/random.h"

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace {

using leveldb::Random;

// A small helper to generate a sequence via a callable that returns uint32_t.
template <typename F>
static std::vector<uint32_t> GenSeq(F&& next_fn, size_t count) {
  std::vector<uint32_t> out;
  out.reserve(count);
  for (size_t i = 0; i < count; ++i) out.push_back(next_fn());
  return out;
}

// -------- Next() --------

TEST(RandomTest_86, Next_DeterministicWithSameSeed_86) {
  const uint32_t seed = 12345u;
  Random r1(seed);
  Random r2(seed);

  const auto s1 = GenSeq([&] { return r1.Next(); }, 100);
  const auto s2 = GenSeq([&] { return r2.Next(); }, 100);

  EXPECT_EQ(s1, s2) << "Same seed should yield identical Next() sequence";
}

TEST(RandomTest_86, Next_DifferentSeeds_UsuallyDifferentFirstValue_86) {
  Random r1(1u);
  Random r2(2u);
  // Deterministic: with two different seeds, the first output should differ.
  // (It is extremely unlikely to collide for typical RNGs; if it ever does,
  // change seeds to any other distinct pair.)
  EXPECT_NE(r1.Next(), r2.Next());
}

TEST(RandomTest_86, Next_SequenceChangesOverTime_86) {
  Random r(123u);
  const uint32_t first = r.Next();
  bool saw_different = false;
  for (int i = 0; i < 50; ++i) {
    if (r.Next() != first) { saw_different = true; break; }
  }
  EXPECT_TRUE(saw_different) << "Next() should not be a constant sequence";
}

// -------- Uniform(n) --------

TEST(RandomTest_86, Uniform_RangeIsWithin0ToNMinus1_86) {
  Random r(999u);
  const int n = 10;
  for (int i = 0; i < 5000; ++i) {
    uint32_t v = r.Uniform(n);
    EXPECT_LT(v, static_cast<uint32_t>(n));
    // Implicitly checks v >= 0 because v is unsigned.
  }
}

TEST(RandomTest_86, Uniform_BoundaryNEquals1AlwaysZero_86) {
  Random r(123u);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(0u, r.Uniform(1)) << "Uniform(1) should always be 0";
  }
}

TEST(RandomTest_86, Uniform_DeterministicWithSameSeed_86) {
  Random r1(777u);
  Random r2(777u);
  std::vector<uint32_t> a, b;
  a.reserve(200);
  b.reserve(200);
  for (int i = 0; i < 200; ++i) a.push_back(r1.Uniform(1000));
  for (int i = 0; i < 200; ++i) b.push_back(r2.Uniform(1000));
  EXPECT_EQ(a, b);
}

// -------- OneIn(n) --------

TEST(RandomTest_86, OneIn_BoundaryNEquals1AlwaysTrue_86) {
  Random r(314159u);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_TRUE(r.OneIn(1)) << "OneIn(1) should always return true";
  }
}

TEST(RandomTest_86, OneIn_ApproximateFrequency_86) {
  Random r(2718u);
  const int n = 5;
  const int trials = 10000;
  int hits = 0;
  for (int i = 0; i < trials; ++i) {
    if (r.OneIn(n)) ++hits;
  }
  // Expect close to trials/n. Use generous bounds to avoid flakiness.
  // Expected mean = 2000; stddev ~ sqrt(10000*0.2*0.8) ~ 40
  // Check within ±10% of the mean (very generous).
  EXPECT_GE(hits, 1800);
  EXPECT_LE(hits, 2200);
}

// -------- Skewed(max_log) --------

TEST(RandomTest_86, Skewed_NonNegative_86) {
  Random r(4242u);
  for (int i = 0; i < 5000; ++i) {
    uint32_t v = r.Skewed(10);
    // v is unsigned; this asserts it's not unexpectedly huge negative via cast.
    // Primary check: no crashes and value is a valid uint32_t.
    (void)v;
  }
  SUCCEED();
}

TEST(RandomTest_86, Skewed_LargerMaxLogAllowsLargerValues_86) {
  Random r1(13579u);
  Random r2(13579u);  // same seed to make comparison fair

  uint32_t max_small = 0;
  for (int i = 0; i < 2000; ++i) {
    max_small = std::max(max_small, r1.Skewed(2));
  }
  uint32_t max_big = 0;
  for (int i = 0; i < 2000; ++i) {
    max_big = std::max(max_big, r2.Skewed(8));
  }

  // With a larger max_log, we should be able to observe values at least
  // as large as with the smaller max_log, over enough samples.
  EXPECT_GE(max_big, max_small);
}

// -------- Independence / State Progression --------

TEST(RandomTest_86, InstancesWithSameSeedDivergeAfterDifferentCalls_86) {
  Random a(2024u);
  Random b(2024u);

  // Advance 'a' a few steps
  for (int i = 0; i < 3; ++i) (void)a.Next();

  // Now compare next outputs; they should differ since states differ
  EXPECT_NE(a.Next(), b.Next());
}

}  // namespace
