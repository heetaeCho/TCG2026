// File: version_set_newfilenumber_test.cc

#include <gtest/gtest.h>
#include <set>
#include <vector>

// Assume the real project provides the full header and dependencies.
#include "db/version_set.h"

namespace leveldb {

TEST(VersionSetTest_72, NewFileNumber_IncrementsMonotonically_72) {
  VersionSet vs;  // Using the available constructor in the real codebase

  const uint64_t first = vs.NewFileNumber();
  const uint64_t second = vs.NewFileNumber();

  // Observable behavior: each call returns a larger number than the previous one.
  EXPECT_LT(first, second);
  EXPECT_EQ(first + 1, second);
}

TEST(VersionSetTest_72, NewFileNumber_ManyCalls_StrictlyIncreasing_72) {
  VersionSet vs;

  constexpr int kCalls = 1000;
  uint64_t prev = vs.NewFileNumber();
  for (int i = 1; i < kCalls; ++i) {
    uint64_t cur = vs.NewFileNumber();
    EXPECT_GT(cur, prev) << "NewFileNumber() must be strictly increasing";
    prev = cur;
  }
}

TEST(VersionSetTest_72, NewFileNumber_ReturnsUniqueValues_72) {
  VersionSet vs;

  constexpr int kCalls = 1024;
  std::set<uint64_t> seen;
  for (int i = 0; i < kCalls; ++i) {
    uint64_t num = vs.NewFileNumber();
    // Uniqueness is observable: the same value should never be returned twice.
    auto inserted = seen.insert(num).second;
    EXPECT_TRUE(inserted) << "Duplicate file number observed: " << num;
  }
  EXPECT_EQ(static_cast<size_t>(kCalls), seen.size());
}

TEST(VersionSetTest_72, NewFileNumber_IndependentAcrossInstances_72) {
  // We do not assume or assert any particular starting value.
  // We only verify that each instance maintains its own increasing sequence.
  VersionSet a;
  VersionSet b;

  const uint64_t a1 = a.NewFileNumber();
  const uint64_t a2 = a.NewFileNumber();
  const uint64_t b1 = b.NewFileNumber();
  const uint64_t b2 = b.NewFileNumber();

  EXPECT_LT(a1, a2) << "Instance A sequence must increase";
  EXPECT_LT(b1, b2) << "Instance B sequence must increase";

  // Cross-instance relation is not specified; avoid asserting equality/inequality
  // of starting points. We only ensure each instance is internally consistent.
}

}  // namespace leveldb
