// File: version_set_markfilenumberused_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <string>

#include "db/version_set.h"         // VersionSet
#include "leveldb/options.h"        // Options
#include "leveldb/comparator.h"     // BytewiseComparator
#include "leveldb/env.h"            // Env

namespace leveldb {

class VersionSetTest_165 : public ::testing::Test {
 protected:
  // Helper to build a minimal, valid VersionSet for our tests.
  // We pass nullptr for TableCache because tests only touch file-number APIs.
  VersionSet MakeVS(const std::string& dbname = "MarkFileNumberUsedTestDB_165") {
    opts_.env = Env::Default();
    return VersionSet(dbname, &opts_, /*table_cache=*/nullptr,
                      /*cmp=*/&icmp_);
  }

  Options opts_;
  InternalKeyComparator icmp_{BytewiseComparator()};
};

// [Normal] Marking a large used number should bump the next allocation to number+1.
TEST_F(VersionSetTest_165, MarkGreaterAdvancesNext_165) {
  VersionSet vs = MakeVS();

  const uint64_t used = 100;
  vs.MarkFileNumberUsed(used);

  const uint64_t next = vs.NewFileNumber();
  EXPECT_EQ(next, used + 1) << "Next allocated file number should be used+1 when marking a larger used number.";
}

// [Boundary] Marking a number smaller than the already-advanced next should NOT reduce it.
TEST_F(VersionSetTest_165, MarkSmallerDoesNotDecrease_165) {
  VersionSet vs = MakeVS();

  // Allocate one number to advance internal "next".
  const uint64_t first = vs.NewFileNumber();  // Observe via public API only.

  // Mark a strictly smaller number than the last allocated.
  ASSERT_GT(first, 0u);
  vs.MarkFileNumberUsed(first - 1);

  // Next allocation should continue to be the immediate successor of 'first'.
  const uint64_t second = vs.NewFileNumber();
  EXPECT_EQ(second, first + 1) << "Marking a smaller number must not decrease the next allocation.";
}

// [Boundary] Marking exactly the last allocated number should NOT change the next allocation.
TEST_F(VersionSetTest_165, MarkLastAllocatedNoChange_165) {
  VersionSet vs = MakeVS();

  const uint64_t last_alloc = vs.NewFileNumber();  // Allocate one
  vs.MarkFileNumberUsed(last_alloc);               // Mark exactly that number as used

  const uint64_t next = vs.NewFileNumber();
  EXPECT_EQ(next, last_alloc + 1) << "Marking the last allocated number must not change the next allocation.";
}

// [Behavior] Multiple marks should move the next allocation monotonically to the highest used+1.
TEST_F(VersionSetTest_165, MultipleMarksMonotonic_165) {
  VersionSet vs = MakeVS();

  vs.MarkFileNumberUsed(50);
  uint64_t n1 = vs.NewFileNumber();
  EXPECT_EQ(n1, 51u);

  // Mark a smaller number afterwards; should have no effect.
  vs.MarkFileNumberUsed(40);
  uint64_t n2 = vs.NewFileNumber();
  EXPECT_EQ(n2, 52u);

  // Mark a larger number; should bump to that larger+1.
  vs.MarkFileNumberUsed(60);
  uint64_t n3 = vs.NewFileNumber();
  EXPECT_EQ(n3, 61u);
}

// [Boundary/Large] Marking a very large number near the uint64_t max should bump to number+1 safely.
TEST_F(VersionSetTest_165, MarkVeryLargeAdvancesNext_165) {
  VersionSet vs = MakeVS();

  const uint64_t big = std::numeric_limits<uint64_t>::max() - 10ULL;
  vs.MarkFileNumberUsed(big);

  const uint64_t next = vs.NewFileNumber();
  EXPECT_EQ(next, big + 1ULL)
      << "Next allocation should be big+1 when marking a very large used number (without overflow).";
}

}  // namespace leveldb
