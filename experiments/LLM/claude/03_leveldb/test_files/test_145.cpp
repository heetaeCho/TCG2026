#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/dbformat.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/table.h"
#include "util/testutil.h"

#include <memory>
#include <string>
#include <vector>
#include <set>

namespace leveldb {

class VersionSetTest_145 : public ::testing::Test {
 protected:
  std::string dbname_;
  Env* env_;
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;

  VersionSetTest_145()
      : dbname_(testing::TempDir() + "/version_set_test_145"),
        env_(Env::Default()),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr),
        vset_(nullptr) {
    options_.env = env_;
    options_.comparator = BytewiseComparator();
  }

  void SetUp() override {
    ASSERT_LEVELDB_OK(env_->CreateDir(dbname_));
    table_cache_ = new TableCache(dbname_, options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    // Clean up test directory
    std::vector<std::string> filenames;
    env_->GetChildren(dbname_, &filenames);
    for (const auto& f : filenames) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }
};

// Test that a fresh VersionSet has expected initial state
TEST_F(VersionSetTest_145, InitialState_145) {
  // Before Recover, current_ may be nullptr, but after construction
  // we can check basic accessors
  EXPECT_EQ(0ULL, vset_->LastSequence());
  EXPECT_EQ(0ULL, vset_->LogNumber());
  EXPECT_EQ(0ULL, vset_->PrevLogNumber());
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_145, NewFileNumberIncrement_145) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(first + 1, second);
}

// Test ReuseFileNumber
TEST_F(VersionSetTest_145, ReuseFileNumber_145) {
  uint64_t num = vset_->NewFileNumber();
  vset_->ReuseFileNumber(num);
  uint64_t reused = vset_->NewFileNumber();
  EXPECT_EQ(num, reused);
}

// Test SetLastSequence and LastSequence
TEST_F(VersionSetTest_145, SetAndGetLastSequence_145) {
  vset_->SetLastSequence(100);
  EXPECT_EQ(100ULL, vset_->LastSequence());
  vset_->SetLastSequence(200);
  EXPECT_EQ(200ULL, vset_->LastSequence());
}

// Test MarkFileNumberUsed
TEST_F(VersionSetTest_145, MarkFileNumberUsed_145) {
  vset_->MarkFileNumberUsed(1000);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_GT(next, 1000ULL);
}

// Test ManifestFileNumber
TEST_F(VersionSetTest_145, ManifestFileNumber_145) {
  // Initially 0 before Recover
  EXPECT_EQ(0ULL, vset_->ManifestFileNumber());
}

// Test NumLevelFiles on empty version set after Recover
TEST_F(VersionSetTest_145, NumLevelFilesAfterRecover_145) {
  // Create CURRENT file pointing to a manifest
  // First write a valid manifest
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    // Write empty version edit as snapshot
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  // Write CURRENT file
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, vset_->NumLevelFiles(level));
  }
}

// Test NumLevelBytes on empty version
TEST_F(VersionSetTest_145, NumLevelBytesEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, vset_->NumLevelBytes(level));
  }
}

// Test current() returns non-null after Recover
TEST_F(VersionSetTest_145, CurrentAfterRecover_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  EXPECT_NE(nullptr, vset_->current());
}

// Test AddIterators on empty version produces empty iterator list
TEST_F(VersionSetTest_145, AddIteratorsEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  ReadOptions ropts;
  std::vector<Iterator*> iters;
  v->AddIterators(ropts, &iters);
  EXPECT_EQ(0u, iters.size());

  for (auto* it : iters) {
    delete it;
  }
}

// Test NeedsCompaction on fresh version
TEST_F(VersionSetTest_145, NeedsCompactionFresh_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  // Empty DB shouldn't need compaction
  EXPECT_FALSE(vset_->NeedsCompaction());
}

// Test AddLiveFiles on empty version
TEST_F(VersionSetTest_145, AddLiveFilesEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.empty());
}

// Test DebugString on current version
TEST_F(VersionSetTest_145, DebugStringNotEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test LevelSummary
TEST_F(VersionSetTest_145, LevelSummary_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  EXPECT_NE(nullptr, summary);
  EXPECT_GT(strlen(summary), 0u);
}

// Test Ref and Unref on Version
TEST_F(VersionSetTest_145, VersionRefUnref_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  // Ref and Unref should be balanced - version should survive
  v->Ref();
  v->Unref();
  // current() should still be valid
  EXPECT_EQ(v, vset_->current());
}

// Test OverlapInLevel on empty version
TEST_F(VersionSetTest_145, OverlapInLevelEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  Slice small_key("a");
  Slice large_key("z");

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small_key, &large_key));
  }
}

// Test GetOverlappingInputs on empty version
TEST_F(VersionSetTest_145, GetOverlappingInputsEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 100, kTypeValue);
  std::vector<FileMetaData*> inputs;

  for (int level = 0; level < config::kNumLevels; level++) {
    inputs.clear();
    v->GetOverlappingInputs(level, &begin, &end, &inputs);
    EXPECT_TRUE(inputs.empty());
  }
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionSetTest_145, PickLevelForMemTableOutputEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  Slice small_key("a");
  Slice large_key("z");
  int level = v->PickLevelForMemTableOutput(small_key, large_key);
  // Level should be >= 0
  EXPECT_GE(level, 0);
  EXPECT_LT(level, config::kNumLevels);
}

// Test NumFiles on empty version
TEST_F(VersionSetTest_145, NumFilesEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  Version* v = vset_->current();
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

// Test LogAndApply with a simple edit
TEST_F(VersionSetTest_145, LogAndApplySimple_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  // Apply an empty edit
  VersionEdit edit;
  edit.SetLogNumber(vset_->LogNumber());
  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test MaxNextLevelOverlappingBytes on empty version
TEST_F(VersionSetTest_145, MaxNextLevelOverlappingBytesEmpty_145) {
  std::string manifest = dbname_ + "/MANIFEST-000001";
  {
    WritableFile* file;
    ASSERT_LEVELDB_OK(env_->NewWritableFile(manifest, &file));
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_LEVELDB_OK(writer.AddRecord(record));
    delete file;
  }
  ASSERT_LEVELDB_OK(SetCurrentFile(env_, dbname_, 1));

  bool save_manifest = false;
  ASSERT_LEVELDB_OK(vset_->Recover(&save_manifest));

  int64_t max_overlap = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(0, max_overlap);
}

}  // namespace leveldb
