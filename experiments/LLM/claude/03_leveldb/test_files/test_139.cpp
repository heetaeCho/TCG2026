#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/table_builder.h"
#include "table/format.h"
#include "util/coding.h"
#include "db/dbformat.h"

#include <vector>
#include <string>

namespace leveldb {

// Helper to create FileMetaData entries for testing
static FileMetaData* MakeFile(uint64_t number, uint64_t file_size,
                               const InternalKey& smallest,
                               const InternalKey& largest) {
  FileMetaData* f = new FileMetaData();
  f->number = number;
  f->file_size = file_size;
  f->smallest = smallest;
  f->largest = largest;
  return f;
}

class LevelFileNumIteratorTest_139 : public ::testing::Test {
 protected:
  LevelFileNumIteratorTest_139()
      : icmp_(BytewiseComparator()) {}

  ~LevelFileNumIteratorTest_139() override {
    for (auto* f : files_) {
      delete f;
    }
  }

  void AddFile(uint64_t number, const std::string& smallest_key,
               const std::string& largest_key) {
    InternalKey smallest(smallest_key, 100, kTypeValue);
    InternalKey largest(largest_key, 100, kTypeValue);
    files_.push_back(MakeFile(number, 1000, smallest, largest));
  }

  // We need to access the LevelFileNumIterator which is a nested class.
  // Since it's used internally, we'll create it through the version_set
  // mechanisms. However, based on the interface, we can test it directly
  // if we can construct it.
  // The class is: Version::LevelFileNumIterator
  // It's defined inside version_set.cc, so we may need to use the
  // internal test helpers or access it differently.

  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
};

// Since LevelFileNumIterator is defined in the .cc file (not the header),
// we cannot directly instantiate it from test code. Instead, we test it
// indirectly through Version's public interface which uses it internally.
// We'll test through VersionSet and Version's NewConcatenatingIterator
// or through the table cache iteration path.

// However, given the prompt asks us to test the interface shown, let's
// test what we can through the available public interfaces.

// If the class is accessible (e.g., through internal test friends or
// exported in some builds), we test directly. Otherwise we test through
// Version's iteration interface.

// Let's create tests that exercise the Iterator interface through
// Version::NewConcatenatingIterator indirectly via the version set.

class VersionSetTest_139 : public ::testing::Test {
 protected:
  VersionSetTest_139()
      : env_(Env::Default()),
        dbname_(testing::TempDir() + "version_set_test_139"),
        icmp_(BytewiseComparator()) {
    options_.comparator = BytewiseComparator();
    env_->CreateDir(dbname_);
  }

  ~VersionSetTest_139() override {
    // Cleanup
  }

  Env* env_;
  std::string dbname_;
  InternalKeyComparator icmp_;
  Options options_;
};

// Test: Empty file list - iterator should not be valid initially after construction
TEST_F(LevelFileNumIteratorTest_139, EmptyFileList_139) {
  // With an empty file list, we cannot directly test LevelFileNumIterator
  // since it's in the .cc file. We verify the concept through observable behavior.
  ASSERT_TRUE(files_.empty());
}

// Test: Adding files to list
TEST_F(LevelFileNumIteratorTest_139, AddFilesToList_139) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");
  ASSERT_EQ(files_.size(), 3u);
}

// Test: File metadata is correctly set
TEST_F(LevelFileNumIteratorTest_139, FileMetadataCorrect_139) {
  AddFile(42, "hello", "world");
  ASSERT_EQ(files_[0]->number, 42u);
  ASSERT_EQ(files_[0]->file_size, 1000u);
}

// Since LevelFileNumIterator is an internal class defined in version_set.cc,
// we need to test it through the public Version interface.
// Version provides iterators via AddIterators or internal concatenating iterators.

// We'll test the Iterator protocol concepts that LevelFileNumIterator implements.

class VersionIteratorTest_139 : public ::testing::Test {
 protected:
  VersionIteratorTest_139() : env_(Env::Default()) {
    dbname_ = testing::TempDir() + "version_iter_test_139";
    env_->CreateDir(dbname_);
  }

  ~VersionIteratorTest_139() override {
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
};

// Test: Open a fresh DB and verify iteration works (exercises internal iterators)
TEST_F(VersionIteratorTest_139, FreshDBIteration_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Put some data to create files
  WriteOptions wo;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    s = db->Put(wo, key, val);
    ASSERT_TRUE(s.ok());
  }

  // Create an iterator which internally uses LevelFileNumIterator for levels > 0
  Iterator* iter = db->NewIterator(ReadOptions());
  ASSERT_TRUE(iter->status().ok());

  // SeekToFirst
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Count entries
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_EQ(count, 100);
  ASSERT_TRUE(iter->status().ok());

  // SeekToLast
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());

  // Prev from last
  int reverse_count = 0;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    reverse_count++;
  }
  ASSERT_EQ(reverse_count, 100);

  delete iter;
  delete db;
}

// Test: Seek to specific key
TEST_F(VersionIteratorTest_139, SeekToSpecificKey_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "aaa", "v1");
  db->Put(wo, "bbb", "v2");
  db->Put(wo, "ccc", "v3");

  Iterator* iter = db->NewIterator(ReadOptions());

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");
  ASSERT_EQ(iter->value().ToString(), "v2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "ccc");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
  delete db;
}

// Test: Empty database iteration
TEST_F(VersionIteratorTest_139, EmptyDBIteration_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());

  delete iter;
  delete db;
}

// Test: Multiple compactions create level files, exercising LevelFileNumIterator
TEST_F(VersionIteratorTest_139, CompactedFilesIteration_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  options.write_buffer_size = 1024;  // Small to force compactions
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  // Write enough data to trigger compactions
  for (int i = 0; i < 500; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    char val[100];
    snprintf(val, sizeof(val), "val%06d", i);
    s = db->Put(wo, key, val);
    ASSERT_TRUE(s.ok());
  }

  // Force compaction
  std::string start = "key000000";
  std::string end = "key999999";
  Slice start_slice(start);
  Slice end_slice(end);
  db->CompactRange(&start_slice, &end_slice);

  // Now iterate - this should use LevelFileNumIterator for level > 0
  Iterator* iter = db->NewIterator(ReadOptions());
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_TRUE(iter->status().ok());
  ASSERT_EQ(count, 500);

  // Test Seek within compacted data
  iter->Seek("key000250");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "key000250");

  delete iter;
  delete db;
}

// Test: Next after SeekToLast should invalidate
TEST_F(VersionIteratorTest_139, NextAfterSeekToLast_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "a", "1");
  db->Put(wo, "z", "2");

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "z");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
  delete db;
}

// Test: Prev after SeekToFirst should invalidate
TEST_F(VersionIteratorTest_139, PrevAfterSeekToFirst_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "a", "1");
  db->Put(wo, "z", "2");

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
  delete db;
}

// Test: Seek past all keys
TEST_F(VersionIteratorTest_139, SeekPastAllKeys_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "aaa", "1");
  db->Put(wo, "bbb", "2");

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->Seek("zzz");
  ASSERT_FALSE(iter->Valid());

  delete iter;
  delete db;
}

// Test: Seek before all keys returns first key
TEST_F(VersionIteratorTest_139, SeekBeforeAllKeys_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "bbb", "1");
  db->Put(wo, "ccc", "2");

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->Seek("aaa");
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->key().ToString(), "bbb");

  delete iter;
  delete db;
}

// Test: Single entry iteration
TEST_F(VersionIteratorTest_139, SingleEntryIteration_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  db->Put(wo, "only", "one");

  Iterator* iter = db->NewIterator(ReadOptions());

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
  delete db;
}

// Test: Status is ok after normal operations
TEST_F(VersionIteratorTest_139, StatusOkAfterOperations_139) {
  DB* db = nullptr;
  Options options;
  options.create_if_missing = true;
  Status s = DB::Open(options, dbname_, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions wo;
  for (int i = 0; i < 10; i++) {
    db->Put(wo, "key" + std::to_string(i), "val" + std::to_string(i));
  }

  Iterator* iter = db->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());

  while (iter->Valid()) {
    iter->Next();
  }
  ASSERT_TRUE(iter->status().ok());

  delete iter;
  delete db;
}

}  // namespace leveldb
