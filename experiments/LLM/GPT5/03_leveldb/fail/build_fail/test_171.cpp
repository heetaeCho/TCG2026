// File: db/version_set_max_next_level_overlapping_bytes_test.cc

#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/env.h"
#include "gtest/gtest.h"

namespace leveldb {

class MaxNextLevelOBTest_171 : public ::testing::Test {
protected:
  Env* env_;
  std::string dbname_;
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;

  MaxNextLevelOBTest_171()
      : env_(Env::Default()),
        dbname_("MaxNextLevelOBTest_171"),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr),
        vset_(nullptr) {
    options_.env = env_;
    options_.comparator = BytewiseComparator();
    // Small cache size is OK; we don't read data in these tests.
    table_cache_ = new TableCache(dbname_, &options_, /*entries=*/10);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  ~MaxNextLevelOBTest_171() override {
    delete vset_;
    delete table_cache_;
    // No filesystem cleanup necessary for logic-only tests
  }

  // Helper to build an InternalKey [user, seq=1, kTypeValue]
  InternalKey IK(const std::string& user) {
    InternalKey ik;
    ik.Set(user, /*seq=*/1, kTypeValue);
    return ik;
  }

  // Add a file via VersionEdit and apply it to VersionSet.
  void AddFileAndApply(int level,
                       uint64_t number,
                       uint64_t file_size,
                       const std::string& smallest_user_key,
                       const std::string& largest_user_key) {
    VersionEdit edit;
    edit.AddFile(level, number, file_size, IK(smallest_user_key), IK(largest_user_key));
    // LogAndApply requires a mutex pointer by interface; for unit tests a nullptr
    // is acceptable if the implementation tolerates it (common in LevelDB tests).
    // We rely on observable success/failure via returned Status.
    port::Mutex mu;
    ASSERT_TRUE(vset_->LogAndApply(&edit, &mu).ok());
  }

  int64_t M() { return vset_->MaxNextLevelOverlappingBytes(); }
};

// =============== Tests ===============

// [Empty DB] Expect 0.
TEST_F(MaxNextLevelOBTest_171, ReturnsZeroWhenNoFiles_171) {
  EXPECT_EQ(0, M());
}

// [No overlap across L1->L2] Files exist but do not overlap; expect 0.
TEST_F(MaxNextLevelOBTest_171, NoOverlapReturnsZero_171) {
  // Level 1: [a..b], [m..n]
  AddFileAndApply(/*level=*/1, /*number=*/11, /*size=*/100, "a", "b");
  AddFileAndApply(/*level=*/1, /*number=*/12, /*size=*/200, "m", "n");

  // Level 2: disjoint far ranges [c..d], [x..z] (no overlap with L1 ranges)
  AddFileAndApply(/*level=*/2, /*number=*/21, /*size=*/300, "c", "d");
  AddFileAndApply(/*level=*/2, /*number=*/22, /*size=*/400, "x", "z");

  EXPECT_EQ(0, M());
}

// [Single overlap] One L1 file overlaps two L2 files; expect sum of overlapping L2 sizes.
TEST_F(MaxNextLevelOBTest_171, SingleFileOverlapsMultipleNextLevelFiles_171) {
  // L1: one file [k..t]
  AddFileAndApply(/*level=*/1, /*number=*/101, /*size=*/123, "k", "t");

  // L2: three files, two overlap with [k..t]
  // Overlapping: [h..m] (overlaps at k..m) size=1000, and [r..z] size=2000
  // Non-overlap: [a..c] size=999 (entirely before)
  AddFileAndApply(/*level=*/2, /*number=*/201, /*size=*/999,  "a", "c");   // no overlap
  AddFileAndApply(/*level=*/2, /*number=*/202, /*size=*/1000, "h", "m");  // overlap
  AddFileAndApply(/*level=*/2, /*number=*/203, /*size=*/2000, "r", "z");  // overlap

  // Expect sum of sizes of overlapping L2 files: 1000 + 2000 = 3000
  EXPECT_EQ(3000, M());
}

// [Multiple levels considered; maximum chosen] Provide L1->L2 overlap sum = 1500,
// and L2->L3 overlap sum = 3500. Expect 3500 (max).
TEST_F(MaxNextLevelOBTest_171, ChoosesMaximumAcrossLevels_171) {
  // ---- L1 & L2 overlap sums to 1500
  AddFileAndApply(/*level=*/1, /*number=*/111, /*size=*/1, "p", "t");
  AddFileAndApply(/*level=*/2, /*number=*/211, /*size=*/500, "o", "q");  // overlaps
  AddFileAndApply(/*level=*/2, /*number=*/212, /*size=*/1000,"s", "u");  // overlaps
  AddFileAndApply(/*level=*/2, /*number=*/213, /*size=*/50,  "a", "b");  // no overlap
  // Sum(L2 overlapping) = 500 + 1000 = 1500

  // ---- L2 & L3 overlap sums to 3500
  // Need at least one L2 file to be the "current level" for L=2 iteration
  AddFileAndApply(/*level=*/2, /*number=*/214, /*size=*/1, "k", "m");       // L2 file examined
  AddFileAndApply(/*level=*/3, /*number=*/301, /*size=*/1500, "j", "l");    // overlap with [k..m]
  AddFileAndApply(/*level=*/3, /*number=*/302, /*size=*/2000, "l", "x");    // overlap with [k..m]
  AddFileAndApply(/*level=*/3, /*number=*/303, /*size=*/70,   "a", "b");    // no overlap

  EXPECT_EQ(3500, M());
}

// [Boundary: level-0 ignored] Provide a massive L0->L1 overlap, and a smaller L1->L2 overlap.
// The function iterates levels 1..kNumLevels-2 only, so it must ignore L0. Expect the smaller L1->L2 sum.
TEST_F(MaxNextLevelOBTest_171, IgnoresLevelZeroInComputation_171) {
  // Huge L0-L1 overlap (should be ignored by the implementation)
  AddFileAndApply(/*level=*/0, /*number=*/1,  /*size=*/999999, "a", "z");
  AddFileAndApply(/*level=*/1, /*number=*/2,  /*size=*/10,     "b", "y");   // next level target for L0, but L0 isn't scanned

  // A small but valid L1->L2 overlap that should be considered
  AddFileAndApply(/*level=*/1, /*number=*/10, /*size=*/123,    "k", "t");
  AddFileAndApply(/*level=*/2, /*number=*/20, /*size=*/321,    "m", "s");   // overlaps
  AddFileAndApply(/*level=*/2, /*number=*/21, /*size=*/100,    "a", "b");   // no overlap

  // Expect only the L1->L2 overlap to count: 321
  EXPECT_EQ(321, M());
}

}  // namespace leveldb
