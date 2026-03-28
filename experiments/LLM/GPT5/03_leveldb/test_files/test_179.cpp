// File: compaction_is_trivial_move_test_179.cc
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/testharness.h"
#include "util/logging.h"
#include "port/port.h"

#include <gtest/gtest.h>

namespace leveldb {

namespace {

// Small helper to build InternalKeys for file bounds
static InternalKey IKey(const std::string& user, SequenceNumber seq = 0,
                        ValueType vt = kTypeValue) {
  InternalKey ikey;
  ikey.Set(user, seq, vt);
  return ikey;
}

// Helper to add a file via VersionEdit and apply to VersionSet (black-box)
static void AddFileAndApply(VersionSet* vset,
                            int level,
                            uint64_t number,
                            uint64_t file_size,
                            const std::string& smallest_user_key,
                            const std::string& largest_user_key,
                            port::Mutex* mu) {
  VersionEdit edit;
  edit.SetComparatorName(vset->current()->DebugString()); // comparator name is required by edits typically; using something stable from current version
  edit.AddFile(level, number,
               IKey(smallest_user_key),
               IKey(largest_user_key),
               file_size);
  ASSERT_TRUE(vset->LogAndApply(&edit, mu).ok());
}

} // namespace

class CompactionIsTrivialMoveTest_179 : public ::testing::Test {
protected:
  // Basic components set up using only public interfaces
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_; // May be unused by the tested paths
  std::unique_ptr<VersionSet> vset_;
  port::Mutex mu_;

  CompactionIsTrivialMoveTest_179()
  : icmp_(BytewiseComparator()) {
    // Configure options to keep thresholds small & deterministic without assuming internals
    options_.env = Env::Default();
    options_.comparator = BytewiseComparator();
    options_.write_buffer_size = 64 << 10;
    options_.max_file_size = 1 << 10; // 1 KiB target file size for small thresholds

    // TableCache can be null in some paths, but create a minimal one if your codebase requires.
    // In LevelDB it’s usually constructed with dbname & options' cache; for pure black-box we avoid relying on it.
    table_cache_ = nullptr;

    vset_ = std::make_unique<VersionSet>("CompactionIsTrivialMoveTestDB_179",
                                         &options_,
                                         table_cache_,
                                         &icmp_);
    bool dummy_save = false;
    ASSERT_TRUE(vset_->Recover(&dummy_save).ok());
  }
};

// Normal operation: exactly one input file at level L and zero at L+1, with no grandparent overlap => trivial move.
TEST_F(CompactionIsTrivialMoveTest_179, OneInputNoNextLevelInputs_NoGrandparents_ReturnsTrue_179) {
  // Arrange: L0 has one file [a, k]; L1 empty; L2+ empty
  AddFileAndApply(vset_.get(), /*level=*/0, /*number=*/100, /*size=*/200,
                  /*smallest=*/"a", /*largest=*/"k", &mu_);

  // Act: Build a compaction covering exactly that range using only public API
  InternalKey begin = IKey("a");
  InternalKey end   = IKey("k");
  std::unique_ptr<Compaction> c(vset_->CompactRange(/*level=*/0, &begin, &end));
  ASSERT_NE(c, nullptr) << "CompactRange should return a compaction for the specified range";

  // Sanity checks via public accessors (black-box)
  EXPECT_EQ(0, c->level());
  EXPECT_EQ(1, c->num_input_files(/*which=*/0));
  EXPECT_EQ(0, c->num_input_files(/*which=*/1));

  // Assert: Trivial move expected
  EXPECT_TRUE(c->IsTrivialMove());
}

// Boundary: more than one input file on the source level => not a trivial move.
TEST_F(CompactionIsTrivialMoveTest_179, MultipleInputsOnSourceLevel_ReturnsFalse_179) {
  // Arrange: L0 has two disjoint files: [a, c] and [d, f]; L1 empty
  AddFileAndApply(vset_.get(), 0, 101, 128, "a", "c", &mu_);
  AddFileAndApply(vset_.get(), 0, 102, 128, "d", "f", &mu_);

  // Act: Request a compaction that spans both files
  InternalKey begin = IKey("a");
  InternalKey end   = IKey("f");
  std::unique_ptr<Compaction> c(vset_->CompactRange(/*level=*/0, &begin, &end));
  ASSERT_NE(c, nullptr);

  // Verify via public accessors
  EXPECT_EQ(0, c->level());
  EXPECT_GE(c->num_input_files(/*which=*/0), 2) << "Compaction should include both L0 files";

  // Assert
  EXPECT_FALSE(c->IsTrivialMove());
}

// Exceptional/edge: one input at source level but grandparent overlap exceeds allowed threshold => not a trivial move.
TEST_F(CompactionIsTrivialMoveTest_179, OneInputButGrandparentOverlapTooLarge_ReturnsFalse_179) {
  // Arrange:
  // L0: one file [m, t]
  AddFileAndApply(vset_.get(), 0, 201, 256, "m", "t", &mu_);

  // L1: empty to keep num_input_files(1) == 0 condition otherwise satisfied
  // L2 (grandparents): add overlapping files whose total size is large.
  // We do not assume threshold internals; we just add several reasonably sized files to create
  // a non-trivial overlap scenario for the compaction selection.
  AddFileAndApply(vset_.get(), 2, 301, 2048, "l", "o", &mu_);  // overlaps start
  AddFileAndApply(vset_.get(), 2, 302, 2048, "p", "r", &mu_);  // overlaps middle
  AddFileAndApply(vset_.get(), 2, 303, 2048, "s", "u", &mu_);  // overlaps end

  // Act: Compaction for [m, t]
  InternalKey begin = IKey("m");
  InternalKey end   = IKey("t");
  std::unique_ptr<Compaction> c(vset_->CompactRange(/*level=*/0, &begin, &end));
  ASSERT_NE(c, nullptr);

  // Verify single input on source level and none on next
  EXPECT_EQ(1, c->num_input_files(/*which=*/0));
  EXPECT_EQ(0, c->num_input_files(/*which=*/1));

  // Assert: Due to heavy grandparent overlap, should NOT be a trivial move
  EXPECT_FALSE(c->IsTrivialMove());
}

} // namespace leveldb
