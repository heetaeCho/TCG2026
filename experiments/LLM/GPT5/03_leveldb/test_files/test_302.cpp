// File: db_impl_compact_range_test_302.cc
#include <gtest/gtest.h>
#include "db/db_impl.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

using namespace leveldb;

// NOTE:
// These tests focus on validating interface-level, observable behavior:
//  - Precondition assertions on `level`
//  - Acceptance of nullptr vs non-null `begin`/`end` Slices
// No internal state or behavior is inferred or accessed.

class DBImplCompactRangeTest_302 : public ::testing::Test {
protected:
  // In many build setups, DBImpl is constructible with default/placeholder args,
  // or a convenient factory exists. If your environment requires specific setup,
  // adapt the fixture accordingly, but do not access internal state.
  //
  // If DBImpl requires a complex constructor in your codebase,
  // consider providing a minimal test harness/fixture already available
  // in your repo that yields a valid DBImpl instance for black-box calls.
  //
  // For the purposes of these tests, we assume a default-constructible DBImpl
  // is available or that your test environment provides a helper.
  //
  // Replace the line below with your actual construction path if needed.
  DBImpl* db_ = nullptr;

  void SetUp() override {
    // If your DBImpl requires specific construction, replace this with your helper.
    // e.g., db_ = NewTestDBImpl();  // <- project-provided helper
    //
    // If DBImpl is default-constructible (in your provided partial code), use:
    db_ = new DBImpl();  // Adjust if your environment differs.
  }

  void TearDown() override {
    delete db_;
    db_ = nullptr;
  }
};

// ---------- Death tests for level preconditions (asserts) ----------

// level must be >= 0
TEST_F(DBImplCompactRangeTest_302, NegativeLevel_TriggersAssert_302) {
  ASSERT_NE(db_, nullptr);
  EXPECT_DEATH(
      {
        db_->TEST_CompactRange(-1, /*begin=*/nullptr, /*end=*/nullptr);
      },
      "");  // assert() failure
}

// level + 1 < config::kNumLevels  => level must be <= kNumLevels - 2
TEST_F(DBImplCompactRangeTest_302, LevelAtMaxTriggersAssert_302) {
  ASSERT_NE(db_, nullptr);
  const int invalid_level = config::kNumLevels - 1;  // e.g., 6 for kNumLevels=7
  EXPECT_DEATH(
      {
        db_->TEST_CompactRange(invalid_level, /*begin=*/nullptr, /*end=*/nullptr);
      },
      "");
}

// ---------- Valid boundary levels should pass the assertion checks ----------

TEST_F(DBImplCompactRangeTest_302, LevelZeroWithNullBounds_DoesNotAssert_302) {
  ASSERT_NE(db_, nullptr);
  // This should pass initial asserts. We only verify it doesn't immediately assert.
  // (No assumptions about internal scheduling/compaction progress.)
  // If your environment may block due to background scheduling, consider adding
  // a project-provided non-blocking harness for TEST_CompactRange.
  db_->TEST_CompactRange(/*level=*/0, /*begin=*/nullptr, /*end=*/nullptr);
}

TEST_F(DBImplCompactRangeTest_302, MaxValidLevelWithNullBounds_DoesNotAssert_302) {
  ASSERT_NE(db_, nullptr);
  const int max_valid = config::kNumLevels - 2;  // e.g., 5 when kNumLevels=7
  db_->TEST_CompactRange(max_valid, /*begin=*/nullptr, /*end=*/nullptr);
}

// ---------- begin/end provided vs nullptr should be accepted by the API ----------

TEST_F(DBImplCompactRangeTest_302, NonNullBeginNullEnd_DoesNotAssert_302) {
  ASSERT_NE(db_, nullptr);
  Slice begin_key("a");
  db_->TEST_CompactRange(/*level=*/0, &begin_key, /*end=*/nullptr);
}

TEST_F(DBImplCompactRangeTest_302, NullBeginNonNullEnd_DoesNotAssert_302) {
  ASSERT_NE(db_, nullptr);
  Slice end_key("z");
  db_->TEST_CompactRange(/*level=*/0, /*begin=*/nullptr, &end_key);
}

TEST_F(DBImplCompactRangeTest_302, NonNullBeginAndEnd_DoesNotAssert_302) {
  ASSERT_NE(db_, nullptr);
  Slice begin_key("a");
  Slice end_key("z");
  db_->TEST_CompactRange(/*level=*/0, &begin_key, &end_key);
}
