// db_impl_compaction_stats_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// The header under test
#include "db/db_impl.h"

namespace {

using leveldb::DBImpl::CompactionStats;

class CompactionStatsTest_293 : public ::testing::Test {
protected:
  static CompactionStats Make(int64_t micros, int64_t read, int64_t written) {
    CompactionStats s;
    // Public fields: setting via the public interface is allowed.
    s.micros = micros;
    s.bytes_read = read;
    s.bytes_written = written;
    return s;
  }
};

// Verifies the default-constructed values are zeroed.
TEST_F(CompactionStatsTest_293, DefaultConstructedIsZero_293) {
  CompactionStats s;
  EXPECT_EQ(0, s.micros);
  EXPECT_EQ(0, s.bytes_read);
  EXPECT_EQ(0, s.bytes_written);
}

// Verifies Add aggregates each field independently and correctly.
TEST_F(CompactionStatsTest_293, AddAggregatesFields_293) {
  CompactionStats base = Make(10, 20, 30);
  const CompactionStats delta = Make(1, 2, 3);

  base.Add(delta);

  EXPECT_EQ(11, base.micros);
  EXPECT_EQ(22, base.bytes_read);
  EXPECT_EQ(33, base.bytes_written);
}

// Verifies Add is cumulative over multiple calls.
TEST_F(CompactionStatsTest_293, MultipleAddsAreCumulative_293) {
  CompactionStats base = Make(5, 5, 5);
  const CompactionStats d1 = Make(7, 8, 9);
  const CompactionStats d2 = Make(10, 20, 30);

  base.Add(d1);
  base.Add(d2);

  EXPECT_EQ(5 + 7 + 10, base.micros);
  EXPECT_EQ(5 + 8 + 20, base.bytes_read);
  EXPECT_EQ(5 + 9 + 30, base.bytes_written);
}

// Verifies Add with zero deltas leaves values unchanged.
TEST_F(CompactionStatsTest_293, AddZeroIsNoOp_293) {
  CompactionStats base = Make(123, 456, 789);
  const CompactionStats zero;  // default-constructed to zeros

  base.Add(zero);

  EXPECT_EQ(123, base.micros);
  EXPECT_EQ(456, base.bytes_read);
  EXPECT_EQ(789, base.bytes_written);
}

// Verifies Add accepts negative values (since fields are int64_t).
TEST_F(CompactionStatsTest_293, AddAllowsNegativeValues_293) {
  CompactionStats base = Make(100, 200, 300);
  const CompactionStats neg = Make(-10, -20, -30);

  base.Add(neg);

  EXPECT_EQ(90, base.micros);
  EXPECT_EQ(180, base.bytes_read);
  EXPECT_EQ(270, base.bytes_written);
}

// Boundary: adding large but safe values near int64_t limits (no overflow).
TEST_F(CompactionStatsTest_293, AddNearInt64MaxWithoutOverflow_293) {
  const int64_t kMax = std::numeric_limits<int64_t>::max();
  // Choose values that keep sums strictly below kMax to avoid UB/overflow.
  CompactionStats base = Make(kMax - 100, kMax - 200, kMax - 300);
  const CompactionStats delta = Make(50, 100, 150);

  base.Add(delta);

  EXPECT_EQ(kMax - 50, base.micros);
  EXPECT_EQ(kMax - 100, base.bytes_read);
  EXPECT_EQ(kMax - 150, base.bytes_written);
}

// API behavior check: the const reference argument to Add must not be modified.
TEST_F(CompactionStatsTest_293, AddDoesNotModifyArgument_293) {
  CompactionStats base = Make(1, 2, 3);
  const CompactionStats delta_before = Make(4, 5, 6);
  CompactionStats delta_copy = delta_before;  // snapshot

  base.Add(delta_before);

  // Base changed:
  EXPECT_EQ(1 + 4, base.micros);
  EXPECT_EQ(2 + 5, base.bytes_read);
  EXPECT_EQ(3 + 6, base.bytes_written);

  // Argument unchanged (observable via comparing to the snapshot).
  EXPECT_EQ(delta_copy.micros, delta_before.micros);
  EXPECT_EQ(delta_copy.bytes_read, delta_before.bytes_read);
  EXPECT_EQ(delta_copy.bytes_written, delta_before.bytes_written);
}

}  // namespace
