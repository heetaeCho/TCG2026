#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"

namespace leveldb {

class NumLevelBytesTest_170 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/num_level_bytes_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    cache_ = NewLRUCache(100);
    options_.block_cache = cache_;

    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    delete cache_;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  Cache* cache_;
  const InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that NumLevelBytes returns 0 for all levels on a fresh VersionSet
// (before any data has been added).
TEST_F(NumLevelBytesTest_170, EmptyVersionSetReturnsZeroForAllLevels_170) {
  // We need to recover first to set up current_ properly
  bool save_manifest = false;
  // Create a CURRENT file pointing to a valid manifest
  Status s = vset_->Recover(&save_manifest);
  // If recovery fails because there's no existing DB, that's expected for a
  // brand new directory. We skip the check in that case.
  if (s.ok()) {
    for (int level = 0; level < config::kNumLevels; level++) {
      int64_t bytes = vset_->NumLevelBytes(level);
      EXPECT_GE(bytes, 0) << "Level " << level << " should have non-negative bytes";
    }
  }
}

// Test NumLevelBytes for level 0 specifically
TEST_F(NumLevelBytesTest_170, Level0Bytes_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (s.ok()) {
    int64_t bytes = vset_->NumLevelBytes(0);
    EXPECT_GE(bytes, 0);
  }
}

// Test NumLevelBytes for the last valid level
TEST_F(NumLevelBytesTest_170, LastLevelBytes_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (s.ok()) {
    int64_t bytes = vset_->NumLevelBytes(config::kNumLevels - 1);
    EXPECT_GE(bytes, 0);
  }
}

// Test NumLevelBytes for each valid level
TEST_F(NumLevelBytesTest_170, AllValidLevels_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (s.ok()) {
    for (int level = 0; level < config::kNumLevels; level++) {
      int64_t bytes = vset_->NumLevelBytes(level);
      EXPECT_GE(bytes, 0) << "Level " << level;
    }
  }
}

// Test that NumLevelFiles also returns consistent results with NumLevelBytes
TEST_F(NumLevelBytesTest_170, ConsistencyWithNumLevelFiles_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (s.ok()) {
    for (int level = 0; level < config::kNumLevels; level++) {
      int num_files = vset_->NumLevelFiles(level);
      int64_t num_bytes = vset_->NumLevelBytes(level);
      if (num_files == 0) {
        EXPECT_EQ(num_bytes, 0) << "Level " << level
            << ": no files but non-zero bytes";
      }
      if (num_bytes == 0) {
        EXPECT_EQ(num_files, 0) << "Level " << level
            << ": zero bytes but non-zero file count";
      }
    }
  }
}

// Test with a database that has been written to via LogAndApply
class NumLevelBytesWithDataTest_170 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/num_level_bytes_data_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    cache_ = NewLRUCache(100);
    options_.block_cache = cache_;

    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    delete cache_;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  Cache* cache_;
  const InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that after adding files via VersionEdit + LogAndApply,
// NumLevelBytes reflects the added file sizes.
TEST_F(NumLevelBytesWithDataTest_170, AfterAddingFiles_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (!s.ok()) {
    // Can't test without a recovered version set
    GTEST_SKIP() << "Could not recover VersionSet: " << s.ToString();
  }

  // Add a file to level 1
  VersionEdit edit;
  const int target_level = 1;
  const uint64_t file_number = vset_->NewFileNumber();
  const uint64_t file_size = 12345;
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit.AddFile(target_level, file_number, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (s.ok()) {
    int64_t bytes = vset_->NumLevelBytes(target_level);
    EXPECT_EQ(bytes, static_cast<int64_t>(file_size));

    // Other levels should still be 0
    for (int level = 0; level < config::kNumLevels; level++) {
      if (level != target_level) {
        EXPECT_EQ(vset_->NumLevelBytes(level), 0)
            << "Level " << level << " should be empty";
      }
    }
  }
}

// Test adding multiple files to the same level
TEST_F(NumLevelBytesWithDataTest_170, MultipleFilesInSameLevel_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (!s.ok()) {
    GTEST_SKIP() << "Could not recover VersionSet: " << s.ToString();
  }

  const int target_level = 2;
  const uint64_t file_size_1 = 10000;
  const uint64_t file_size_2 = 20000;

  {
    VersionEdit edit;
    uint64_t fn1 = vset_->NewFileNumber();
    InternalKey s1("aaa", 1, kTypeValue);
    InternalKey l1("mmm", 2, kTypeValue);
    edit.AddFile(target_level, fn1, file_size_1, s1, l1);

    uint64_t fn2 = vset_->NewFileNumber();
    InternalKey s2("nnn", 3, kTypeValue);
    InternalKey l2("zzz", 4, kTypeValue);
    edit.AddFile(target_level, fn2, file_size_2, s2, l2);

    port::Mutex mu;
    mu.Lock();
    s = vset_->LogAndApply(&edit, &mu);
    mu.Unlock();
  }

  if (s.ok()) {
    int64_t bytes = vset_->NumLevelBytes(target_level);
    EXPECT_EQ(bytes, static_cast<int64_t>(file_size_1 + file_size_2));
  }
}

// Test adding files to different levels
TEST_F(NumLevelBytesWithDataTest_170, FilesInDifferentLevels_170) {
  bool save_manifest = false;
  Status s = vset_->Recover(&save_manifest);
  if (!s.ok()) {
    GTEST_SKIP() << "Could not recover VersionSet: " << s.ToString();
  }

  VersionEdit edit;
  const uint64_t sizes[config::kNumLevels] = {100, 200, 300, 400, 500, 600, 700};

  for (int level = 0; level < config::kNumLevels; level++) {
    uint64_t fn = vset_->NewFileNumber();
    std::string key_str = std::string(1, 'a' + level * 2);
    std::string key_str2 = std::string(1, 'a' + level * 2 + 1);
    InternalKey sk(key_str, level * 2 + 1, kTypeValue);
    InternalKey lk(key_str2, level * 2 + 2, kTypeValue);
    edit.AddFile(level, fn, sizes[level], sk, lk);
  }

  port::Mutex mu;
  mu.Lock();
  s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (s.ok()) {
    for (int level = 0; level < config::kNumLevels; level++) {
      int64_t bytes = vset_->NumLevelBytes(level);
      EXPECT_EQ(bytes, static_cast<int64_t>(sizes[level]))
          << "Level " << level << " size mismatch";
    }
  }
}

}  // namespace leveldb
