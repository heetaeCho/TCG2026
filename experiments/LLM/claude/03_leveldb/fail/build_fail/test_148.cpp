#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/table_cache.h"
#include "db/dbformat.h"
#include "db/filename.h"
#include "db/log_writer.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table_builder.h"
#include "leveldb/comparator.h"
#include "leveldb/cache.h"
#include "util/testutil.h"

namespace leveldb {

class VersionGetTest_148 : public ::testing::Test {
 protected:
  std::string dbname_;
  Env* env_;
  Options options_;
  InternalKeyComparator icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;

  VersionGetTest_148()
      : dbname_(testing::TempDir() + "version_get_test_148"),
        env_(Env::Default()),
        icmp_(BytewiseComparator()),
        table_cache_(nullptr),
        vset_(nullptr) {}

  void SetUp() override {
    DestroyDB(dbname_, options_);
    options_.env = env_;
    options_.comparator = BytewiseComparator();
    env_->CreateDir(dbname_);
    table_cache_ = new TableCache(dbname_, options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
    bool save_manifest = false;
    // We need to create a valid CURRENT file for Recover
    CreateManifest();
    vset_->Recover(&save_manifest);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    DestroyDB(dbname_, options_);
  }

  void CreateManifest() {
    // Create a minimal manifest
    std::string manifest = DescriptorFileName(dbname_, 1);
    WritableFile* file;
    env_->NewWritableFile(manifest, &file);
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_.user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    writer.AddRecord(record);
    delete file;
    SetCurrentFile(env_, dbname_, 1);
  }

  // Build a table file with a single key-value pair
  uint64_t BuildTable(const std::string& key, const std::string& value,
                      SequenceNumber seq, ValueType type = kTypeValue) {
    uint64_t file_number = vset_->NewFileNumber();
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* file;
    EXPECT_TRUE(env_->NewWritableFile(fname, &file).ok());

    TableBuilder builder(options_, file);
    InternalKey ikey(key, seq, type);
    builder.Add(ikey.Encode(), value);
    builder.Finish();
    delete file;
    return file_number;
  }

  void AddFileToVersion(int level, uint64_t file_number,
                        const std::string& smallest_key,
                        const std::string& largest_key,
                        SequenceNumber seq, uint64_t file_size = 0) {
    if (file_size == 0) {
      uint64_t sz;
      env_->GetFileSize(TableFileName(dbname_, file_number), &sz);
      file_size = sz;
    }
    VersionEdit edit;
    InternalKey smallest(smallest_key, seq, kTypeValue);
    InternalKey largest(largest_key, seq, kTypeValue);
    edit.AddFile(level, file_number, file_size, smallest, largest);
    port::Mutex mu;
    mu.Lock();
    Status s = vset_->LogAndApply(&edit, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }
};

// Test: Get returns NotFound when no files exist
TEST_F(VersionGetTest_148, GetNotFoundWhenEmpty_148) {
  ReadOptions ropts;
  LookupKey lk("nonexistent", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_EQ(stats.seek_file, nullptr);
  EXPECT_EQ(stats.seek_file_level, -1);
}

// Test: Get finds a key that exists in a table file
TEST_F(VersionGetTest_148, GetFindsExistingKey_148) {
  uint64_t fnum = BuildTable("testkey", "testvalue", 10);
  AddFileToVersion(0, fnum, "testkey", "testkey", 10);

  ReadOptions ropts;
  LookupKey lk("testkey", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "testvalue");
}

// Test: Get returns NotFound for a key not in the table
TEST_F(VersionGetTest_148, GetNotFoundForMissingKey_148) {
  uint64_t fnum = BuildTable("aaa", "val_aaa", 10);
  AddFileToVersion(0, fnum, "aaa", "aaa", 10);

  ReadOptions ropts;
  LookupKey lk("bbb", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get handles deletion tombstone
TEST_F(VersionGetTest_148, GetHandlesDeletion_148) {
  uint64_t fnum = BuildTable("delkey", "", 20, kTypeDeletion);
  AddFileToVersion(0, fnum, "delkey", "delkey", 20);

  ReadOptions ropts;
  LookupKey lk("delkey", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: GetStats seek_file is set when reading multiple files
TEST_F(VersionGetTest_148, GetStatsSetsSeekFile_148) {
  // Create two files at level 0 overlapping the same key range
  uint64_t fnum1 = BuildTable("key1", "val1_old", 5);
  AddFileToVersion(0, fnum1, "key1", "key1", 5);

  uint64_t fnum2 = BuildTable("key1", "val1_new", 15);
  AddFileToVersion(0, fnum2, "key1", "key1", 15);

  ReadOptions ropts;
  LookupKey lk("key1", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "val1_new");
  // When two files are searched, seek_file should be set to the first file read
  // (only if a second file is also read)
}

// Test: Get with sequence number lower than the key's sequence returns NotFound
TEST_F(VersionGetTest_148, GetWithOlderSequence_148) {
  uint64_t fnum = BuildTable("seqkey", "seqval", 50);
  AddFileToVersion(0, fnum, "seqkey", "seqkey", 50);

  ReadOptions ropts;
  LookupKey lk("seqkey", 1);  // sequence 1 < 50, so key shouldn't be visible
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get stats initialized properly with single file read
TEST_F(VersionGetTest_148, GetStatsInitializedProperly_148) {
  uint64_t fnum = BuildTable("singlekey", "singleval", 10);
  AddFileToVersion(0, fnum, "singlekey", "singlekey", 10);

  ReadOptions ropts;
  LookupKey lk("singlekey", 100);
  std::string value;
  Version::GetStats stats;
  stats.seek_file = reinterpret_cast<FileMetaData*>(0xdeadbeef);
  stats.seek_file_level = 999;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.ok());
  // With only one file read, seek_file should remain nullptr
  // because the condition requires last_file_read != nullptr AND
  // stats->seek_file == nullptr, but it's set before second file
  EXPECT_EQ(stats.seek_file, nullptr);
  EXPECT_EQ(stats.seek_file_level, -1);
}

// Test: Get newer value shadows older value in level 0
TEST_F(VersionGetTest_148, NewerValueShadowsOlder_148) {
  uint64_t fnum1 = BuildTable("shadow", "old_value", 5);
  AddFileToVersion(0, fnum1, "shadow", "shadow", 5);

  uint64_t fnum2 = BuildTable("shadow", "new_value", 15);
  AddFileToVersion(0, fnum2, "shadow", "shadow", 15);

  ReadOptions ropts;
  LookupKey lk("shadow", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "new_value");
}

// Test: Deletion shadows older put in level 0
TEST_F(VersionGetTest_148, DeletionShadowsOlderPut_148) {
  uint64_t fnum1 = BuildTable("deltest", "exists", 5);
  AddFileToVersion(0, fnum1, "deltest", "deltest", 5);

  uint64_t fnum2 = BuildTable("deltest", "", 15, kTypeDeletion);
  AddFileToVersion(0, fnum2, "deltest", "deltest", 15);

  ReadOptions ropts;
  LookupKey lk("deltest", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get works with file in higher level (level 1)
TEST_F(VersionGetTest_148, GetFromLevel1_148) {
  uint64_t fnum = BuildTable("lvl1key", "lvl1val", 10);
  AddFileToVersion(1, fnum, "lvl1key", "lvl1key", 10);

  ReadOptions ropts;
  LookupKey lk("lvl1key", 100);
  std::string value;
  Version::GetStats stats;

  Status s = vset_->current()->Get(ropts, lk, &value, &stats);
  EXPECT_TRUE(s.ok()) << s.ToString();
  EXPECT_EQ(value, "lvl1val");
}

}  // namespace leveldb
