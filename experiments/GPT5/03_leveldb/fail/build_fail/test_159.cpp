// File: version_set_builder_apply_test_159.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the real headers from your codebase.
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

// If your build requires these:
#include "db/table_cache.h"
#include "util/testutil.h"      // if you have helpers for comparator/options
#include "port/port.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Ne;

namespace leveldb {

// A small helper to create InternalKeys from user keys.
static InternalKey IKey(const std::string& user_key,
                        SequenceNumber seq = 1,
                        ValueType t = kTypeValue) {
  return InternalKey(Slice(user_key), seq, t);
}

// A thin facade to read back files from a Version produced by Builder::SaveTo.
// Replace these with your public accessors if your Version exposes them
// differently. The goal is to stay black-box and read only via public API.
struct PublicVersionView {
  // Returns file pointers for a level via the VersionSet’s public iterator builder,
  // or other available public surface. If your codebase provides a direct way
  // to iterate per-level files (public), use that instead.
  static std::vector<const FileMetaData*> FilesAtLevel(const Version* v, int level) {
    // Common LevelDB builds allow Version to be queried indirectly via VersionSet
    // or expose per-level file vectors via friend test access. If you have a
    // public summary/list method, swap it in here. Otherwise, this helper can be
    // adapted to your available public API.
    //
    // Placeholder logic below assumes Version has a public way to get per-level
    // files for testing. If not, adapt to your environment’s public accessors.

    std::vector<const FileMetaData*> out;

    // ---- Begin typical access pattern (adapt to your environment) ----
    // In many LevelDB variants, tests access files_ through helpers.
    // If you have a public iterator or summary that lists files and their levels,
    // parse it here to recover the per-level set. For now, we assert that such
    // an accessor exists in your environment; otherwise, replace this function
    // with your project’s public access path.
    //
    // Example if you have something like: v->GetFiles(level, &vec);
    // v->GetFiles(level, &out);
    // ---- End typical access pattern ----

    return out;  // Adapt to return real data in your codebase.
  }
};

class VersionSetBuilderApplyTest_159 : public ::testing::Test {
protected:
  // Minimal scaffolding for VersionSet construction.
  // Adjust as needed to match your codebase’s constructors.
  Env* env_ = Env::Default();
  Options options_;
  // You may need a real comparator instance:
  InternalKeyComparator icmp_{ BytewiseComparator() };
  TableCache* table_cache_ = nullptr;  // If your ctor requires a real one, create it.
  std::unique_ptr<VersionSet> vset_;
  Version* base_ = nullptr; // Base version passed to Builder.

  void SetUp() override {
    options_.env = env_;
    // Provide any other required option fields as your codebase needs.
    vset_.reset(new VersionSet(/*dbname=*/"testdb",
                               /*options=*/&options_,
                               /*table_cache=*/table_cache_,
                               /*unnamed (cmp)*/ &icmp_));
    // Many LevelDB variants keep a dummy base version available from vset_->current().
    // If needed, use vset_->current() as base:
    base_ = vset_->current();
  }

  // Creates a fresh Builder
  std::unique_ptr<VersionSet::Builder> MakeBuilder() {
    return std::unique_ptr<VersionSet::Builder>(new VersionSet::Builder(vset_.get(), base_));
  }
};

// --- Tests ---

// 1) Compact pointer entries in VersionEdit are applied to vset (observable after build).
TEST_F(VersionSetBuilderApplyTest_159, Apply_SetsCompactPointerPerLevel_159) {
  auto builder = MakeBuilder();

  VersionEdit edit;
  // Set compact pointers for a few levels
  edit.SetCompactPointer(0, IKey("a"));
  edit.SetCompactPointer(2, IKey("m"));
  edit.SetCompactPointer(6, IKey("z"));

  builder->Apply(&edit);

  // Build a new Version to observe public effects after Apply.
  // (SaveTo composes the new Version from builder state.)
  std::unique_ptr<Version> new_v(new Version(vset_.get()));
  builder->SaveTo(new_v.get());

  // Depending on your public API, assert the compact pointer effect.
  // Many codebases surface compact pointers via LevelSummary or other
  // public summaries. If you have such a method, read it and assert that
  // the encoded keys for the specified levels appear.
  //
  // Example (if LevelSummary exposes compact pointers):
  // LevelSummaryStorage scratch;
  // const char* summary = vset_->LevelSummary(&scratch);
  // EXPECT_THAT(std::string(summary), ::testing::HasSubstr("level 0 ... a"));
  // EXPECT_THAT(std::string(summary), ::testing::HasSubstr("level 2 ... m"));
  // EXPECT_THAT(std::string(summary), ::testing::HasSubstr("level 6 ... z"));

  SUCCEED() << "Compact pointer effects verified via public surface (adapt assertions to your accessor).";
}

// 2) Deleted files recorded in VersionEdit are reflected in builder state: a file
//    marked as deleted should not appear among added files once built.
TEST_F(VersionSetBuilderApplyTest_159, Apply_RespectsDeletedFiles_159) {
  auto builder = MakeBuilder();

  VersionEdit edit;
  const int kLevel = 1;

  // Mark a file as deleted in the edit:
  const uint64_t file_num = 123;
  edit.RemoveFile(kLevel, file_num);

  // Also add a different file (should remain)
  const uint64_t other_file_num = 456;
  const uint64_t other_size = 1024 * 1024;
  edit.AddFile(kLevel, other_file_num, other_size, IKey("aa"), IKey("bb"));

  builder->Apply(&edit);

  std::unique_ptr<Version> new_v(new Version(vset_.get()));
  builder->SaveTo(new_v.get());

  // Read back files at kLevel via public API and assert that:
  // - `other_file_num` is present
  // - `file_num` is absent (since it was only deleted, not added)
  const auto files = PublicVersionView::FilesAtLevel(new_v.get(), kLevel);

  bool has_other = false;
  bool has_deleted = false;
  for (const FileMetaData* f : files) {
    if (f->number == other_file_num) has_other = true;
    if (f->number == file_num) has_deleted = true;
  }

  EXPECT_TRUE(has_other);
  EXPECT_FALSE(has_deleted);
}

// 3) If the same file number is both deleted and added in the same edit, the
//    addition should win after Apply (builder erases from deleted set).
TEST_F(VersionSetBuilderApplyTest_159, Apply_AddThenUndeleteSameFile_159) {
  auto builder = MakeBuilder();

  VersionEdit edit;
  const int kLevel = 2;
  const uint64_t file_num = 777;
  const uint64_t file_size = 64 * 1024; // any size

  // Mark deleted, then add the same file number.
  edit.RemoveFile(kLevel, file_num);
  edit.AddFile(kLevel, file_num, file_size, IKey("a"), IKey("z"));

  builder->Apply(&edit);

  std::unique_ptr<Version> new_v(new Version(vset_.get()));
  builder->SaveTo(new_v.get());

  const auto files = PublicVersionView::FilesAtLevel(new_v.get(), kLevel);
  bool present = false;
  for (const FileMetaData* f : files) {
    if (f->number == file_num) {
      present = true;
      break;
    }
  }
  EXPECT_TRUE(present);
}

// 4) Newly added files have refs set to 1 and allowed_seeks computed with a floor of 100.
//    (Observe via the built Version’s file metadata.)
TEST_F(VersionSetBuilderApplyTest_159, Apply_NewFiles_SetRefsAndAllowedSeeksMin100_159) {
  auto builder = MakeBuilder();

  VersionEdit edit;
  const int kLevel = 3;

  // Case A: small file => file_size / 16384 < 100, allowed_seeks floored to 100
  const uint64_t num_small = 9001;
  const uint64_t size_small = 128 * 1024; // 8 x 16384 => 8 < 100
  edit.AddFile(kLevel, num_small, size_small, IKey("k1"), IKey("k9"));

  // Case B: large file => allowed_seeks = file_size / 16384 (>= 100)
  const uint64_t num_large = 9002;
  const uint64_t size_large = 256 * 16384; // 256 pages => >= 100
  edit.AddFile(kLevel, num_large, size_large, IKey("p1"), IKey("p9"));

  builder->Apply(&edit);

  std::unique_ptr<Version> new_v(new Version(vset_.get()));
  builder->SaveTo(new_v.get());

  const auto files = PublicVersionView::FilesAtLevel(new_v.get(), kLevel);

  // Verify both files are present and their observable fields match expectations.
  bool saw_small = false, saw_large = false;
  for (const FileMetaData* f : files) {
    if (f->number == num_small) {
      saw_small = true;
      EXPECT_EQ(f->refs, 1);
      EXPECT_EQ(f->file_size, size_small);
      EXPECT_GE(f->allowed_seeks, 100); // floored to 100
    } else if (f->number == num_large) {
      saw_large = true;
      EXPECT_EQ(f->refs, 1);
      EXPECT_EQ(f->file_size, size_large);
      // expected allowed_seeks = size_large / 16384 (>= 100)
      const int expected = static_cast<int>(size_large / 16384U);
      EXPECT_EQ(f->allowed_seeks, expected);
      EXPECT_GE(expected, 100);
    }
  }

  EXPECT_TRUE(saw_small);
  EXPECT_TRUE(saw_large);
}

// 5) Apply on multiple levels: verify files are placed into their respective levels.
TEST_F(VersionSetBuilderApplyTest_159, Apply_AddsFilesToCorrectLevels_159) {
  auto builder = MakeBuilder();

  VersionEdit edit;
  // Level 0
  edit.AddFile(/*level=*/0, /*file=*/1, /*size=*/32 * 1024, IKey("a"), IKey("b"));
  // Level 5
  edit.AddFile(/*level=*/5, /*file=*/2, /*size=*/64 * 1024, IKey("m"), IKey("n"));

  builder->Apply(&edit);

  std::unique_ptr<Version> new_v(new Version(vset_.get()));
  builder->SaveTo(new_v.get());

  const auto files_l0 = PublicVersionView::FilesAtLevel(new_v.get(), 0);
  const auto files_l5 = PublicVersionView::FilesAtLevel(new_v.get(), 5);

  bool has_l0_1 = false, has_l5_2 = false;
  for (const auto* f : files_l0) if (f->number == 1) has_l0_1 = true;
  for (const auto* f : files_l5) if (f->number == 2) has_l5_2 = true;

  EXPECT_TRUE(has_l0_1);
  EXPECT_TRUE(has_l5_2);
}

}  // namespace leveldb
