// File: version_set_pick_compaction_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/options.h"

using ::testing::NotNull;
using ::testing::IsNull;

namespace leveldb {

namespace {

// Minimal fixture that builds a VersionSet using only public constructor args.
// NOTE: Replace BytewiseComparator() with your project’s user comparator if different.
class VersionSetPickCompactionTest_173 : public ::testing::Test {
protected:
  Env* env_ = Env::Default();
  Options options_;
  InternalKeyComparator icmp_{BytewiseComparator()};
  // TableCache is usually required by VersionSet but not exercised by PickCompaction’s
  // interface-level behavior in the “no compaction” case. Provide nullptr or a real
  // instance depending on your test harness; both are black-box valid so long as
  // VersionSet’s ctor accepts it.
  TableCache* table_cache_ = nullptr;

  // Use a unique DB name per test to avoid any cross-test filesystem effects.
  std::string dbname_ = "PickCompactionTestDB_173";

  // SUT
  std::unique_ptr<VersionSet> vs_;

  void SetUp() override {
    options_.env = env_;
    vs_.reset(new VersionSet(dbname_, &options_, table_cache_, &icmp_));
  }
};

}  // namespace

// -----------------------------------------------------------------------------
// Normal operation (freshly constructed VersionSet)
//
// Behavior under test:
//  - When there is neither size-compaction nor seek-compaction needed,
//    PickCompaction() must return nullptr.
//  - This should be true immediately after construction, before any versions or
//    files are logged/applied.
// -----------------------------------------------------------------------------
TEST_F(VersionSetPickCompactionTest_173, FreshSet_ReturnsNull_173) {
  // Act
  Compaction* c = vs_->PickCompaction();

  // Assert
  EXPECT_THAT(c, IsNull()) << "Fresh VersionSet should not immediately request a compaction.";
}

// -----------------------------------------------------------------------------
// Boundary/safety: Idempotent null behavior
//
// Behavior under test:
//  - Multiple calls in a row should remain safe and keep returning nullptr
//    (no latent state change) when no compaction is needed.
//  - This verifies there are no side effects *observable* via the interface.
// -----------------------------------------------------------------------------
TEST_F(VersionSetPickCompactionTest_173, RepeatedCalls_NoCompactionRemainNull_173) {
  Compaction* c1 = vs_->PickCompaction();
  Compaction* c2 = vs_->PickCompaction();

  EXPECT_THAT(c1, IsNull());
  EXPECT_THAT(c2, IsNull());
}

// -----------------------------------------------------------------------------
// Size compaction path (interface-driven setup)
//
// Behavior goal (observable):
//  - When the current version’s level L has accumulated enough bytes/files that
//    the system decides size-based compaction is needed, PickCompaction()
//    should return a non-null Compaction with level() == L and at least one
//    input file in "which == 0".
//
// Black-box setup (do not touch internals):
//  1) Use VersionEdit to AddFile(...) at target level (e.g., L=0 or L=1) with
//     smallest/largest InternalKeys covering some user key range.
//  2) Call VersionSet::LogAndApply(&edit, /*mu=*/nullptr) to install the edit.
//  3) Optionally call any public method that triggers Finalize/score computation
//     if your tree requires that sequence (commonly LogAndApply does).
//
// Note: This test is SKIPPED here because the partial headers in the prompt do
// not include VersionEdit’s AddFile signature (it exists in the full codebase).
// Uncomment and complete the marked lines in your repository to enable.
// -----------------------------------------------------------------------------
TEST_F(VersionSetPickCompactionTest_173, DISABLED_SizeCompaction_ReturnsNonNullWithLevelInputs_173) {
  GTEST_SKIP() << "Enable in full codebase: add files via VersionEdit::AddFile and LogAndApply to trigger size compaction.";

  // --- Example (enable in your repo) ---
  // VersionEdit edit;
  // // Construct smallest/largest internal keys using only public API
  // InternalKey smallest(Slice("a"), /*seq=*/1, kTypeValue);
  // InternalKey largest (Slice("z"), /*seq=*/1, kTypeValue);
  // // Add a file large enough to push compaction score >= 1 for level 0 (or L)
  // edit.AddFile(/*level=*/0, /*number=*/123, /*file_size=*/HugeEnough, smallest, largest);
  // ASSERT_OK(vs_->LogAndApply(&edit, /*mu=*/nullptr));

  // Compaction* c = vs_->PickCompaction();
  // ASSERT_THAT(c, NotNull());
  // EXPECT_EQ(c->level(), 0);                     // Observable via public Compaction::level()
  // EXPECT_GE(c->num_input_files(0), 1);          // Observable: at least one input
  // // Clean up per interface:
  // c->ReleaseInputs();
  // delete c;
}

// -----------------------------------------------------------------------------
// Seek compaction path (interface-driven setup)
//
// Behavior goal (observable):
//  - When a file’s seek limit is exhausted (via public Get/UpdateStats path),
//    the system should need a seek-based compaction, and PickCompaction()
//    returns a non-null Compaction whose level matches the file’s level,
//    with that file present among inputs[0] (observable via num_input_files/input).
//
// Black-box setup (do not touch internals):
//  1) Install a version with at least one file using VersionEdit + LogAndApply.
//  2) Exercise Version::Get / Version::UpdateStats or RecordReadSample via
//     public methods sufficiently to drive “seek compaction” state.
//  3) Call PickCompaction() and assert non-null + inputs exist.
//
// Note: This test is SKIPPED here due to missing full public hooks in the prompt.
// -----------------------------------------------------------------------------
TEST_F(VersionSetPickCompactionTest_173, DISABLED_SeekCompaction_ReturnsNonNullWithTriggeredFile_173) {
  GTEST_SKIP() << "Enable in full codebase: drive seek-compaction via public Get/UpdateStats or RecordReadSample.";

  // --- Example (enable in your repo) ---
  // VersionEdit edit;
  // InternalKey smallest(Slice("k1"), /*seq=*/1, kTypeValue);
  // InternalKey largest (Slice("k9"), /*seq=*/1, kTypeValue);
  // edit.AddFile(/*level=*/1, /*number=*/200, /*file_size=*/SomeSize, smallest, largest);
  // ASSERT_OK(vs_->LogAndApply(&edit, /*mu=*/nullptr));
  //
  // // Drive seeks on the current version through public API:
  // std::string value;
  // GetStats stats;
  // for (int i = 0; i < EnoughToExhaustAllowedSeeks; ++i) {
  //   ASSERT_TRUE(vs_->current()->UpdateStats(stats) || true);  // or RecordReadSample, depending on your API
  // }
  //
  // Compaction* c = vs_->PickCompaction();
  // ASSERT_THAT(c, NotNull());
  // EXPECT_EQ(c->level(), 1);
  // EXPECT_GE(c->num_input_files(0), 1);
  // c->ReleaseInputs();
  // delete c;
}

}  // namespace leveldb
