// File: db/version_set_reusefilenumber_test_73.cc

#include "db/version_set.h"

#include "gtest/gtest.h"

// LevelDB headers needed only to construct VersionSet
#include "db/dbformat.h"               // InternalKeyComparator
#include "leveldb/comparator.h"        // BytewiseComparator()
#include "leveldb/options.h"           // Options
#include "leveldb/env.h"               // Env::Default()

namespace leveldb {

class VersionSetTest_73 : public ::testing::Test {
protected:
  VersionSetTest_73()
      : icmp_(BytewiseComparator()),
        dbname_("reuse_file_number_test_db"),
        table_cache_(nullptr) {
    options_.env = Env::Default();
  }

  InternalKeyComparator icmp_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;  // Not used by these tests
};

/**
 * Behavior: If next_file_number_ == file_number + 1, ReuseFileNumber(file_number)
 * makes the next allocation return file_number again.
 */
TEST_F(VersionSetTest_73, ReuseWhenNextIsFilePlusOne_73) {
  VersionSet vs(dbname_, &options_, table_cache_, &icmp_);

  // Allocate once to advance the internal "next" counter.
  const uint64_t first = vs.NewFileNumber();

  // Now next is (first + 1). Reusing 'first' should roll it back.
  vs.ReuseFileNumber(first);

  // The next allocation should return 'first' again (i.e., reused).
  EXPECT_EQ(first, vs.NewFileNumber());
}

/**
 * Behavior: If next_file_number_ != file_number + 1, ReuseFileNumber(file_number)
 * must have no effect on the next allocation.
 */
TEST_F(VersionSetTest_73, NoEffectWhenNextIsNotFilePlusOne_73) {
  VersionSet vs(dbname_, &options_, table_cache_, &icmp_);

  const uint64_t a = vs.NewFileNumber();  // e.g., 2
  const uint64_t b = vs.NewFileNumber();  // e.g., 3
  (void)a;

  // Currently next is b + 1. Attempt to reuse 'a' (which is not next - 1) should do nothing.
  vs.ReuseFileNumber(a);

  // Next allocation should be (b + 1) rather than 'a'.
  EXPECT_EQ(b + 1, vs.NewFileNumber());
}

/**
 * Boundary: Immediately after construction, next is the initial value (commonly 2).
 * Reusing (initial - 1) should roll back to that (e.g., 1), making the next allocation that value.
 */
TEST_F(VersionSetTest_73, ReuseInitialBoundary_73) {
  VersionSet vs(dbname_, &options_, table_cache_, &icmp_);

  // Without any prior allocations, next should be (kInitialNext).
  // Reusing (kInitialNext - 1) should make the next allocation that value.
  // We do this without assuming the literal initial constant by observing behavior:
  const uint64_t observed_next = vs.NewFileNumber();  // pull current "next"
  // Bring the state back to "observed_next" by reusing it, then allocate once.
  vs.ReuseFileNumber(observed_next);
  EXPECT_EQ(observed_next, vs.NewFileNumber());

  // Now, immediately after the above allocation, next == observed_next + 1.
  // Reuse (observed_next) again should make the next allocation return observed_next.
  vs.ReuseFileNumber(observed_next);
  EXPECT_EQ(observed_next, vs.NewFileNumber());
}

/**
 * Robustness: Reusing the same file number in separate cycles should consistently work
 * only when the precondition (next == file+1) holds.
 */
TEST_F(VersionSetTest_73, ReuseTwiceWithAllocations_73) {
  VersionSet vs(dbname_, &options_, table_cache_, &icmp_);

  const uint64_t x = vs.NewFileNumber();        // allocate x
  vs.ReuseFileNumber(x);                        // next == x+1 -> roll back to x
  EXPECT_EQ(x, vs.NewFileNumber());             // returns x

  // Next is now x+1 again. Reuse x once more should roll it back again.
  vs.ReuseFileNumber(x);
  EXPECT_EQ(x, vs.NewFileNumber());             // returns x again

  // If we now try to reuse a number that is not (next - 1), it should have no effect.
  // After the previous allocation, next == x+1. Trying to reuse (x-1) should do nothing.
  vs.ReuseFileNumber(x - 1);
  EXPECT_EQ(x + 1, vs.NewFileNumber());         // unaffected; proceeds normally
}

}  // namespace leveldb
