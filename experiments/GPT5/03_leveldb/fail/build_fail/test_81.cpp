// File: compaction_num_input_files_test_81.cc
#include <gtest/gtest.h>
#include "db/version_set.h"

// Forward-declared factory expected to be provided by your test harness/codebase.
// See test body for how we handle absence gracefully.
namespace leveldb {
Compaction* MakeTestCompaction();  // Provide this in your test build, or return nullptr to skip.
}

namespace {

class CompactionNumInputFilesTest_81 : public ::testing::Test {
protected:
  void SetUp() override {
    compaction_ = leveldb::MakeTestCompaction();
    if (!compaction_) {
      GTEST_SKIP() << "MakeTestCompaction() not available; skipping until test helper is wired.";
    }
  }

  leveldb::Compaction* compaction_ = nullptr;
};

// ---------- Normal operation ----------

TEST_F(CompactionNumInputFilesTest_81, ReturnsNonNegativeForWhich0_81) {
  ASSERT_NE(compaction_, nullptr);
  // We can’t assume exact counts without mutators; just verify well-formed, non-negative result.
  const int count = compaction_->num_input_files(0);
  EXPECT_GE(count, 0) << "num_input_files(0) should be >= 0";
}

TEST_F(CompactionNumInputFilesTest_81, ReturnsNonNegativeForWhich1_81) {
  ASSERT_NE(compaction_, nullptr);
  const int count = compaction_->num_input_files(1);
  EXPECT_GE(count, 0) << "num_input_files(1) should be >= 0";
}

// ---------- Boundary conditions ----------
//
// NOTE: The provided inline definition uses `inputs_[which]` with no bounds check.
// Calling with an out-of-range index would be undefined behavior. Because black-box
// tests shouldn’t enforce UB or rely on crashes/ASAN, we mark these tests as
// disabled placeholders. If your production wrapper enforces bounds or returns a
// documented error behavior, replace these with concrete expectations.

TEST_F(CompactionNumInputFilesTest_81, DISABLED_OutOfRangeNegativeIndex_81) {
  ASSERT_NE(compaction_, nullptr);
  // If your environment defines behavior for negative indices, assert it here.
  // Otherwise keep disabled to avoid UB.
  (void)compaction_;
}

TEST_F(CompactionNumInputFilesTest_81, DISABLED_OutOfRangeLargeIndex_81) {
  ASSERT_NE(compaction_, nullptr);
  // If your environment defines behavior for which >= 2, assert it here.
  (void)compaction_;
}

// ---------- Observable consistency checks ----------
//
// If your test helper can prepare a compaction where at least one side has files,
// you can assert monotonicity across consecutive queries (pure accessor).

TEST_F(CompactionNumInputFilesTest_81, MultipleCallsConsistent_81) {
  ASSERT_NE(compaction_, nullptr);
  const int a0 = compaction_->num_input_files(0);
  const int a1 = compaction_->num_input_files(0);
  EXPECT_EQ(a0, a1) << "Accessor should be stable across repeated calls.";

  const int b0 = compaction_->num_input_files(1);
  const int b1 = compaction_->num_input_files(1);
  EXPECT_EQ(b0, b1) << "Accessor should be stable across repeated calls.";
}

}  // namespace
