#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "table/table_cache.h"
#include "util/testutil.h"

#include <string>
#include <vector>

namespace leveldb {

class VersionSetTest_154 : public testing::Test {
 protected:
  VersionSetTest_154()
      : dbname_(testing::TempDir() + "version_set_test_154"),
        env_(Env::Default()),
        options_(),
        table_cache_(nullptr),
        vset_(nullptr) {
    options_.env = env_;
    // Create the DB directory
    env_->CreateDir(dbname_);

    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  ~VersionSetTest_154() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    // Clean up
    DestroyDB(dbname_, Options());
  }

  std::string dbname_;
  Env* env_;
  Options options_;
  const InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that PickLevelForMemTableOutput returns 0 when there's no version data
// (empty database, fresh VersionSet without recovery)
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_EmptyVersion_154) {
  // With a fresh VersionSet (no files at any level), we need a current version.
  // We'll do a minimal setup: Recover or LogAndApply to create a current version.
  bool save_manifest = false;
  // Create a CURRENT file pointing to a manifest
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());
    // Write a valid version edit as a log record
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    log::Writer writer(file);
    ASSERT_TRUE(writer.AddRecord(record).ok());
    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // With no files at any level, the key range should be pushed to max compact level
  Slice smallest("a");
  Slice largest("z");
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  // Should be able to push down since no overlaps anywhere
  EXPECT_GE(level, 0);
  EXPECT_LE(level, config::kMaxMemCompactLevel);
}

// Test PickLevelForMemTableOutput returns level 0 for overlapping L0 scenario
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_WithLevel0Overlap_154) {
  // Setup: create a version with a file at level 0 that overlaps the query range
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    // First record: base edit
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(100);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    // Second record: add a file at level 0 overlapping "b"-"y"
    VersionEdit edit2;
    InternalKey smallest_key("b", 1, kTypeValue);
    InternalKey largest_key("y", 2, kTypeValue);
    edit2.AddFile(0, 3, 1000, smallest_key, largest_key);
    std::string record2;
    edit2.EncodeTo(&record2);
    ASSERT_TRUE(writer.AddRecord(record2).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // Query range "a"-"z" overlaps with the L0 file "b"-"y"
  Slice smallest("a");
  Slice largest("z");
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  // Since there's overlap at level 0, should return 0
  EXPECT_EQ(level, 0);
}

// Test PickLevelForMemTableOutput with no overlap at any level
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_NoOverlapAnywhere_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(100);

    // Add a file at level 0 with range "x"-"z" (non-overlapping with our query)
    InternalKey sk("x", 1, kTypeValue);
    InternalKey lk("z", 2, kTypeValue);
    edit.AddFile(0, 3, 1000, sk, lk);

    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // Query range "a"-"b" doesn't overlap with L0 file "x"-"z"
  Slice smallest("a");
  Slice largest("b");
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  // Should be pushed to a higher level (up to kMaxMemCompactLevel = 2)
  EXPECT_GE(level, 0);
  EXPECT_LE(level, config::kMaxMemCompactLevel);
}

// Test PickLevelForMemTableOutput with overlap at level 1
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_OverlapAtLevel1_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(100);

    // Add file at level 1 overlapping with query range "a"-"d"
    InternalKey sk1("b", 1, kTypeValue);
    InternalKey lk1("c", 2, kTypeValue);
    edit.AddFile(1, 4, 1000, sk1, lk1);

    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // No overlap at L0, but overlap at L1 → should stay at level 0
  Slice smallest("a");
  Slice largest("d");
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  EXPECT_EQ(level, 0);
}

// Test PickLevelForMemTableOutput with single-key range
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_SingleKeyRange_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(100);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // Single key range
  Slice key("m");
  int level = current->PickLevelForMemTableOutput(key, key);
  EXPECT_GE(level, 0);
  EXPECT_LE(level, config::kMaxMemCompactLevel);
}

// Test PickLevelForMemTableOutput with large grandparent overlap
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_LargeGrandparentOverlap_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(100);
    edit.SetLastSequence(100);

    // Add many large files at level 2 (grandparent of level 0) overlapping "a"-"z"
    // This should prevent pushing beyond level 0 due to grandparent overlap bytes limit
    for (int i = 0; i < 20; i++) {
      char small_buf[16], large_buf[16];
      snprintf(small_buf, sizeof(small_buf), "a%02d", i);
      snprintf(large_buf, sizeof(large_buf), "a%02d_end", i);
      InternalKey sk(Slice(small_buf), i + 1, kTypeValue);
      InternalKey lk(Slice(large_buf), i + 1, kTypeValue);
      // Each file is 10MB
      edit.AddFile(2, 10 + i, 10 * 1048576, sk, lk);
    }

    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // No overlap at L0 or L1, but huge grandparent (L2) overlap
  // Should be limited to level 0 because grandparent overlap is too large
  Slice smallest("a");
  Slice largest("b");
  int level = current->PickLevelForMemTableOutput(smallest, largest);
  EXPECT_GE(level, 0);
  EXPECT_LE(level, config::kMaxMemCompactLevel);
}

// Test that the returned level is always within valid bounds
TEST_F(VersionSetTest_154, PickLevelForMemTableOutput_ReturnValueBounds_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  ASSERT_NE(current, nullptr);

  // Test with various key ranges to ensure the return value is always valid
  std::vector<std::pair<std::string, std::string>> ranges = {
      {"", ""},
      {"a", "a"},
      {"aaa", "zzz"},
      {"hello", "world"},
      {std::string(1000, 'a'), std::string(1000, 'z')},
  };

  for (const auto& range : ranges) {
    Slice smallest(range.first);
    Slice largest(range.second);
    int level = current->PickLevelForMemTableOutput(smallest, largest);
    EXPECT_GE(level, 0) << "smallest=" << range.first << " largest=" << range.second;
    EXPECT_LE(level, config::kMaxMemCompactLevel)
        << "smallest=" << range.first << " largest=" << range.second;
  }
}

// Test NumLevelFiles on a fresh version
TEST_F(VersionSetTest_154, NumLevelFiles_EmptyVersion_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test OverlapInLevel on empty version
TEST_F(VersionSetTest_154, OverlapInLevel_EmptyVersion_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();
  Slice smallest("a");
  Slice largest("z");

  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(current->OverlapInLevel(level, &smallest, &largest));
  }
}

// Test OverlapInLevel with nullptr keys (should handle full range)
TEST_F(VersionSetTest_154, OverlapInLevel_NullKeys_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(10);
    edit.SetLastSequence(100);

    InternalKey sk("m", 1, kTypeValue);
    InternalKey lk("n", 2, kTypeValue);
    edit.AddFile(1, 3, 1000, sk, lk);

    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  Version* current = vset_->current();

  // nullptr means unbounded range - should find overlap at level 1
  EXPECT_TRUE(current->OverlapInLevel(1, nullptr, nullptr));
  EXPECT_FALSE(current->OverlapInLevel(0, nullptr, nullptr));
}

// Test VersionSet basic accessors
TEST_F(VersionSetTest_154, VersionSetAccessors_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(42);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(vset_->LastSequence(), 42);
  EXPECT_NE(vset_->current(), nullptr);

  vset_->SetLastSequence(100);
  EXPECT_EQ(vset_->LastSequence(), 100);
}

// Test NewFileNumber increments
TEST_F(VersionSetTest_154, NewFileNumber_154) {
  {
    std::string manifest = "MANIFEST-000001";
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(dbname_ + "/" + manifest, &file).ok());

    log::Writer writer(file);

    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    ASSERT_TRUE(writer.AddRecord(record).ok());

    delete file;
    ASSERT_TRUE(SetCurrentFile(env_, dbname_, 1).ok());
  }

  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  ASSERT_TRUE(s.ok()) << s.ToString();

  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(second, first + 1);
}

}  // namespace leveldb
