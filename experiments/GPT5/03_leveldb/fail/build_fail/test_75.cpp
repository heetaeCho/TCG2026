// File: version_set_set_last_sequence_test_75.cc
#include "db/version_set.h"

#include "db/table_cache.h"
#include "db/dbformat.h"          // InternalKeyComparator
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "gtest/gtest.h"

using namespace leveldb;

class VersionSetSetLastSequenceTest_75 : public ::testing::Test {
protected:
  std::string dbname_ = "verset_set_last_sequence_test_75";
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_ = nullptr;

  VersionSetSetLastSequenceTest_75()
      : icmp_(BytewiseComparator()) {
    options_.env = Env::Default();
    options_.comparator = BytewiseComparator();
  }

  void SetUp() override {
    // Create a small table cache; VersionSet's ctor only stores the pointer.
    table_cache_ = new TableCache(dbname_, &options_, /*entries=*/16);
  }

  void TearDown() override {
    delete table_cache_;
    table_cache_ = nullptr;
  }

  // Helper to build a fresh VersionSet instance.
  std::unique_ptr<VersionSet> MakeVS() {
    return std::unique_ptr<VersionSet>(
        new VersionSet(dbname_, &options_, table_cache_, &icmp_));
  }
};

// Normal: setting a larger sequence updates LastSequence
TEST_F(VersionSetSetLastSequenceTest_75, SetIncreasesMonotonically_75) {
  auto vs = MakeVS();

  // Start from default (implementation initializes to 0).
  vs->SetLastSequence(5);
  EXPECT_EQ(vs->LastSequence(), 5u);

  vs->SetLastSequence(10);
  EXPECT_EQ(vs->LastSequence(), 10u);
}

// Boundary: setting to zero is allowed
TEST_F(VersionSetSetLastSequenceTest_75, AcceptsZero_75) {
  auto vs = MakeVS();

  vs->SetLastSequence(0);
  EXPECT_EQ(vs->LastSequence(), 0u);
}

// Boundary: setting to the same value is allowed (non-decreasing)
TEST_F(VersionSetSetLastSequenceTest_75, AcceptsEqualValue_75) {
  auto vs = MakeVS();

  vs->SetLastSequence(7);
  EXPECT_EQ(vs->LastSequence(), 7u);

  // Setting the same value again should be fine and remain unchanged.
  vs->SetLastSequence(7);
  EXPECT_EQ(vs->LastSequence(), 7u);
}

// Exceptional/Error (observable via assert): decreasing should fail
// Use death test only for debug builds where the assert is active.
#if !defined(NDEBUG)
TEST_F(VersionSetSetLastSequenceTest_75, RejectsDecrease_Death_75) {
  auto vs = MakeVS();

  vs->SetLastSequence(9);
  ASSERT_EQ(vs->LastSequence(), 9u);

  // Decreasing should trigger the internal assert.
  EXPECT_DEATH(vs->SetLastSequence(8), ".*");
}
#endif
