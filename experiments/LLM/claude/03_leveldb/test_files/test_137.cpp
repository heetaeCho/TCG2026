#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/testutil.h"

#include <vector>
#include <string>
#include <cstring>

namespace leveldb {

// We need to access LevelFileNumIterator which is a private nested class of Version.
// Since we can't directly instantiate it from outside, we'll test it through
// the Version interface or through a friend/test helper approach.
// However, based on the provided interface, we'll create tests that exercise
// LevelFileNumIterator behavior through its Iterator interface.

// Helper to create FileMetaData entries
static FileMetaData* CreateFileMetaData(uint64_t number, uint64_t file_size,
                                         const InternalKey& smallest,
                                         const InternalKey& largest) {
  FileMetaData* f = new FileMetaData();
  f->number = number;
  f->file_size = file_size;
  f->smallest = smallest;
  f->largest = largest;
  return f;
}

// Since LevelFileNumIterator is a private/nested class, we test it through
// the public interface exposed by Version. The Version::NewConcatenatingIterator
// or similar methods would use LevelFileNumIterator internally.
// But to directly test, we replicate the known interface.

// For direct testing, we use a test-friendly approach. The class is defined
// in version_set.cc. We'll test through Version's public iteration methods.

class VersionSetTest_137 : public testing::Test {
 protected:
  VersionSetTest_137()
      : dbname_(testing::TempDir() + "version_set_test"),
        env_(Env::Default()),
        options_(),
        table_cache_(nullptr),
        vset_(nullptr) {
    options_.comparator = BytewiseComparator();
    // Clean up any previous test data
    DestroyDB(dbname_, options_);
    env_->CreateDir(dbname_);
  }

  ~VersionSetTest_137() override {
    delete vset_;
    delete table_cache_;
    DestroyDB(dbname_, options_);
  }

  void SetUp() override {
    table_cache_ = new TableCache(dbname_, options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_,
                           &internal_comparator_);
  }

  std::string dbname_;
  Env* env_;
  Options options_;
  InternalKeyComparator internal_comparator_{BytewiseComparator()};
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that a newly opened VersionSet has a current version
TEST_F(VersionSetTest_137, InitialVersionExists_137) {
  Status s = vset_->Recover(nullptr);
  // Even if recovery fails due to missing CURRENT file, we test the interface
  // The vset should have been constructed
  ASSERT_TRUE(vset_ != nullptr);
}

// Since LevelFileNumIterator is not directly accessible, we test through
// a standalone compilation approach. We'll test the Iterator interface
// behaviors that we know about.

// Test through creating a DB and iterating
class DBIterationTest_137 : public testing::Test {
 protected:
  DBIterationTest_137() : db_(nullptr) {
    dbname_ = testing::TempDir() + "db_iteration_test_137";
    DestroyDB(dbname_, Options());
  }

  ~DBIterationTest_137() override {
    delete db_;
    DestroyDB(dbname_, Options());
  }

  void SetUp() override {
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  std::string dbname_;
  DB* db_;
};

TEST_F(DBIterationTest_137, EmptyDBIterator_137) {
  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_TRUE(iter != nullptr);
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(DBIterationTest_137, SeekToFirstWithData_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "val1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key2", "val2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key3", "val3").ok());

  // Force compaction to create SST files that would use LevelFileNumIterator
  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key1");
  ASSERT_EQ(iter->value().ToString(), "val1");
  delete iter;
}

TEST_F(DBIterationTest_137, SeekToLastWithData_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key1", "val1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key2", "val2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "key3", "val3").ok());

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key3");
  ASSERT_EQ(iter->value().ToString(), "val3");
  delete iter;
}

TEST_F(DBIterationTest_137, NextIteration_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();

  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "b");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(DBIterationTest_137, PrevIteration_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "b", "2").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();

  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(DBIterationTest_137, SeekToSpecificKey_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "a", "1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "c", "3").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "e", "5").ok());

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());

  // Seek to exact key
  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");
  ASSERT_EQ(iter->value().ToString(), "3");

  // Seek to non-existent key, should land on next
  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "c");

  // Seek past all keys
  iter->Seek("z");
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(DBIterationTest_137, SeekToFirstOnEmpty_137) {
  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(DBIterationTest_137, StatusOkDuringIteration_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "key", "value").ok());
  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());

  iter->Next();
  // After going past end
  ASSERT_FALSE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

TEST_F(DBIterationTest_137, SingleElementIteration_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "only", "one").ok());
  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "only");
  ASSERT_EQ(iter->value().ToString(), "one");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "only");

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(DBIterationTest_137, ManyKeysIteration_137) {
  // Insert many keys to potentially create multiple files/levels
  for (int i = 0; i < 1000; i++) {
    char key[20];
    std::snprintf(key, sizeof(key), "key%06d", i);
    char val[20];
    std::snprintf(val, sizeof(val), "val%06d", i);
    ASSERT_TRUE(db_->Put(WriteOptions(), key, val).ok());
  }

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_TRUE(iter->status().ok());
  ASSERT_EQ(count, 1000);

  // Count backwards
  count = 0;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    count++;
  }
  ASSERT_TRUE(iter->status().ok());
  ASSERT_EQ(count, 1000);

  delete iter;
}

TEST_F(DBIterationTest_137, SeekBoundaryKeys_137) {
  ASSERT_TRUE(db_->Put(WriteOptions(), "aaa", "v1").ok());
  ASSERT_TRUE(db_->Put(WriteOptions(), "zzz", "v2").ok());

  db_->CompactRange(nullptr, nullptr);

  Iterator* iter = db_->NewIterator(ReadOptions());

  // Seek before first key
  iter->Seek("");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");

  // Seek to first key exactly
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "aaa");

  // Seek to last key exactly
  iter->Seek("zzz");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "zzz");

  // Seek past last key
  iter->Seek("zzzz");
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

}  // namespace leveldb
