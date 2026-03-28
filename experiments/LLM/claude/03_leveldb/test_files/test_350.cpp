#include "gtest/gtest.h"
#include "db/table_cache.h"
#include "leveldb/cache.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "util/testutil.h"

#include <cstdint>
#include <string>

namespace leveldb {

class TableCacheTest_350 : public testing::Test {
 protected:
  void SetUp() override {
    // Use an in-memory environment
    env_ = Env::Default();
    options_.env = env_;
    dbname_ = test::TmpDir() + "/table_cache_test";
    env_->CreateDir(dbname_);
    cache_entries_ = 100;
    table_cache_ = new TableCache(dbname_, options_, cache_entries_);
  }

  void TearDown() override {
    delete table_cache_;
  }

  // Helper to create a valid SSTable file on disk with the given file_number
  // and populate it with some key-value pairs.
  // Returns the file size.
  uint64_t CreateTable(uint64_t file_number,
                       const std::vector<std::pair<std::string, std::string>>& kv_pairs) {
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* file;
    Status s = env_->NewWritableFile(fname, &file);
    EXPECT_TRUE(s.ok()) << s.ToString();

    TableBuilder builder(options_, file);
    for (const auto& kv : kv_pairs) {
      builder.Add(kv.first, kv.second);
    }
    s = builder.Finish();
    EXPECT_TRUE(s.ok()) << s.ToString();
    
    uint64_t file_size = builder.FileSize();
    s = file->Close();
    EXPECT_TRUE(s.ok()) << s.ToString();
    delete file;

    return file_size;
  }

  std::string TableFileName(const std::string& dbname, uint64_t number) {
    char buf[100];
    std::snprintf(buf, sizeof(buf), "/%06llu.ldb",
                  static_cast<unsigned long long>(number));
    return dbname + buf;
  }

  Env* env_;
  Options options_;
  std::string dbname_;
  int cache_entries_;
  TableCache* table_cache_;
};

// Test that NewIterator returns a valid iterator for an existing table file
TEST_F(TableCacheTest_350, NewIteratorValidFile_350) {
  uint64_t file_number = 1;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Table* tableptr = nullptr;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr);

  ASSERT_TRUE(iter->status().ok()) << iter->status().ToString();
  EXPECT_NE(tableptr, nullptr);

  // Verify we can iterate through all entries
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test that NewIterator returns an error iterator for a non-existent file
TEST_F(TableCacheTest_350, NewIteratorNonExistentFile_350) {
  ReadOptions read_options;
  uint64_t file_number = 999;
  uint64_t file_size = 100;
  Table* tableptr = nullptr;

  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr);

  EXPECT_FALSE(iter->status().ok());
  EXPECT_EQ(tableptr, nullptr);
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test that NewIterator works when tableptr is nullptr
TEST_F(TableCacheTest_350, NewIteratorNullTablePtr_350) {
  uint64_t file_number = 2;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "111"},
      {"bbb", "222"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, nullptr);

  ASSERT_TRUE(iter->status().ok()) << iter->status().ToString();

  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "aaa");
  EXPECT_EQ(iter->value().ToString(), "111");

  delete iter;
}

// Test that the same file can be opened multiple times (cache hit)
TEST_F(TableCacheTest_350, NewIteratorCacheHit_350) {
  uint64_t file_number = 3;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"x", "1"},
      {"y", "2"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Table* tableptr1 = nullptr;
  Table* tableptr2 = nullptr;

  Iterator* iter1 = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr1);
  ASSERT_TRUE(iter1->status().ok());
  EXPECT_NE(tableptr1, nullptr);

  Iterator* iter2 = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr2);
  ASSERT_TRUE(iter2->status().ok());
  EXPECT_NE(tableptr2, nullptr);

  // Both should point to the same cached table
  EXPECT_EQ(tableptr1, tableptr2);

  delete iter1;
  delete iter2;
}

// Test Evict removes the cached entry, and subsequent access still works (re-opens file)
TEST_F(TableCacheTest_350, EvictAndReopen_350) {
  uint64_t file_number = 4;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"hello", "world"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Table* tableptr1 = nullptr;
  Iterator* iter1 = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr1);
  ASSERT_TRUE(iter1->status().ok());
  EXPECT_NE(tableptr1, nullptr);
  delete iter1;

  // Evict the entry
  table_cache_->Evict(file_number);

  // Should still be able to re-open
  Table* tableptr2 = nullptr;
  Iterator* iter2 = table_cache_->NewIterator(read_options, file_number, file_size, &tableptr2);
  ASSERT_TRUE(iter2->status().ok());
  EXPECT_NE(tableptr2, nullptr);

  iter2->SeekToFirst();
  EXPECT_TRUE(iter2->Valid());
  EXPECT_EQ(iter2->key().ToString(), "hello");
  EXPECT_EQ(iter2->value().ToString(), "world");

  delete iter2;
}

// Test Get on a valid file with a matching key
TEST_F(TableCacheTest_350, GetExistingKey_350) {
  uint64_t file_number = 5;
  // Keys must be in sorted order for leveldb table
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "val_alpha"},
      {"beta", "val_beta"},
      {"gamma", "val_gamma"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;

  struct GetResult {
    std::string found_key;
    std::string found_value;
    bool called = false;
  };

  GetResult result;
  auto saver = [](void* arg, const Slice& k, const Slice& v) {
    GetResult* r = reinterpret_cast<GetResult*>(arg);
    r->found_key = k.ToString();
    r->found_value = v.ToString();
    r->called = true;
  };

  Status s = table_cache_->Get(read_options, file_number, file_size,
                               "beta", &result, saver);
  EXPECT_TRUE(s.ok()) << s.ToString();
  EXPECT_TRUE(result.called);
  // The key returned by InternalGet might be the internal key; at minimum
  // the callback should have been invoked.
}

// Test Get on a non-existent file returns an error
TEST_F(TableCacheTest_350, GetNonExistentFile_350) {
  ReadOptions read_options;
  bool called = false;
  auto saver = [](void* arg, const Slice& k, const Slice& v) {
    *reinterpret_cast<bool*>(arg) = true;
  };

  Status s = table_cache_->Get(read_options, 9999, 100, "somekey", &called, saver);
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(called);
}

// Test NewIterator with an empty table
TEST_F(TableCacheTest_350, NewIteratorEmptyTable_350) {
  uint64_t file_number = 6;
  std::vector<std::pair<std::string, std::string>> kvs = {};
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, nullptr);
  ASSERT_TRUE(iter->status().ok()) << iter->status().ToString();

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek functionality through the iterator
TEST_F(TableCacheTest_350, NewIteratorSeek_350) {
  uint64_t file_number = 7;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
      {"ccc", "3"},
      {"ddd", "4"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, nullptr);
  ASSERT_TRUE(iter->status().ok());

  iter->Seek("bbb");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "bbb");
  EXPECT_EQ(iter->value().ToString(), "2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "ccc");

  delete iter;
}

// Test SeekToLast
TEST_F(TableCacheTest_350, NewIteratorSeekToLast_350) {
  uint64_t file_number = 8;
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"},
      {"last", "2"},
  };
  uint64_t file_size = CreateTable(file_number, kvs);

  ReadOptions read_options;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, file_size, nullptr);
  ASSERT_TRUE(iter->status().ok());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "last");
  EXPECT_EQ(iter->value().ToString(), "2");

  delete iter;
}

// Test that Evict on a non-cached file number doesn't crash
TEST_F(TableCacheTest_350, EvictNonExistent_350) {
  // Should not crash or cause issues
  table_cache_->Evict(12345);
}

// Test that error iterator from non-existent file is not valid
TEST_F(TableCacheTest_350, ErrorIteratorNotValid_350) {
  ReadOptions read_options;
  Table* tableptr = nullptr;
  Iterator* iter = table_cache_->NewIterator(read_options, 77777, 500, &tableptr);

  EXPECT_FALSE(iter->Valid());
  EXPECT_FALSE(iter->status().ok());
  EXPECT_EQ(tableptr, nullptr);

  // Seeking on error iterator should still keep it invalid
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test multiple different files
TEST_F(TableCacheTest_350, MultipleDifferentFiles_350) {
  uint64_t fn1 = 10, fn2 = 11;
  uint64_t fs1 = CreateTable(fn1, {{"a", "1"}, {"b", "2"}});
  uint64_t fs2 = CreateTable(fn2, {{"c", "3"}, {"d", "4"}});

  ReadOptions ro;
  Table* t1 = nullptr;
  Table* t2 = nullptr;

  Iterator* iter1 = table_cache_->NewIterator(ro, fn1, fs1, &t1);
  Iterator* iter2 = table_cache_->NewIterator(ro, fn2, fs2, &t2);

  ASSERT_TRUE(iter1->status().ok());
  ASSERT_TRUE(iter2->status().ok());
  EXPECT_NE(t1, nullptr);
  EXPECT_NE(t2, nullptr);
  EXPECT_NE(t1, t2);

  iter1->SeekToFirst();
  ASSERT_TRUE(iter1->Valid());
  EXPECT_EQ(iter1->key().ToString(), "a");

  iter2->SeekToFirst();
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter2->key().ToString(), "c");

  delete iter1;
  delete iter2;
}

}  // namespace leveldb
