#include "gtest/gtest.h"
#include "db/table_cache.h"
#include "leveldb/cache.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "util/testutil.h"

#include <string>
#include <cstdint>

namespace leveldb {

class TableCacheTest_352 : public testing::Test {
 protected:
  void SetUp() override {
    // Use an in-memory environment or default environment
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/table_cache_test";
    env_->CreateDir(dbname_);
    options_.env = env_;
  }

  void TearDown() override {
    // Clean up
  }

  // Helper to create a simple table file with the given file_number
  void CreateTableFile(uint64_t file_number, const std::string& key,
                       const std::string& value) {
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* wfile;
    ASSERT_TRUE(env_->NewWritableFile(fname, &wfile).ok());

    TableBuilder* builder = new TableBuilder(options_, wfile);
    builder->Add(key, value);
    ASSERT_TRUE(builder->Finish().ok());
    ASSERT_TRUE(wfile->Close().ok());

    file_size_ = builder->FileSize();
    delete builder;
    delete wfile;
  }

  std::string dbname_;
  Env* env_;
  Options options_;
  uint64_t file_size_ = 0;

 private:
  static std::string TableFileName(const std::string& dbname,
                                   uint64_t number) {
    char buf[100];
    std::snprintf(buf, sizeof(buf), "/%06llu.ldb",
                  static_cast<unsigned long long>(number));
    return dbname + buf;
  }
};

// Test that TableCache can be constructed and destructed without issues
TEST_F(TableCacheTest_352, ConstructAndDestruct_352) {
  TableCache* cache = new TableCache(dbname_, options_, 10);
  ASSERT_NE(cache, nullptr);
  delete cache;
}

// Test Evict on a file number that was never cached (should not crash)
TEST_F(TableCacheTest_352, EvictNonExistentFile_352) {
  TableCache cache(dbname_, options_, 10);
  // Evicting a file that was never loaded should be a no-op and not crash
  cache.Evict(999);
  cache.Evict(0);
  cache.Evict(UINT64_MAX);
}

// Test that NewIterator returns an error iterator when the file doesn't exist
TEST_F(TableCacheTest_352, NewIteratorFileNotFound_352) {
  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;
  Table* tableptr = nullptr;
  Iterator* iter = cache.NewIterator(ropts, 12345, 100, &tableptr);
  ASSERT_NE(iter, nullptr);
  // The file doesn't exist, so the iterator should have a non-ok status
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

// Test that Get returns an error when the file doesn't exist
TEST_F(TableCacheTest_352, GetFileNotFound_352) {
  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;
  bool called = false;
  auto handler = [](void* arg, const Slice& key, const Slice& value) {
    *reinterpret_cast<bool*>(arg) = true;
  };
  Status s = cache.Get(ropts, 12345, 100, "somekey", &called, handler);
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(called);
}

// Test that we can create a table file, read it via NewIterator, and find the key
TEST_F(TableCacheTest_352, NewIteratorReadsExistingTable_352) {
  CreateTableFile(1, "hello", "world");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;
  Table* tableptr = nullptr;
  Iterator* iter = cache.NewIterator(ropts, 1, file_size_, &tableptr);
  ASSERT_NE(iter, nullptr);
  ASSERT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "hello");
  EXPECT_EQ(iter->value().ToString(), "world");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test that Get successfully retrieves a key from a table file
TEST_F(TableCacheTest_352, GetRetrievesKey_352) {
  CreateTableFile(2, "testkey", "testvalue");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  struct Result {
    std::string key;
    std::string value;
    bool called = false;
  };
  Result result;

  auto handler = [](void* arg, const Slice& key, const Slice& value) {
    Result* r = reinterpret_cast<Result*>(arg);
    r->key = key.ToString();
    r->value = value.ToString();
    r->called = true;
  };

  Status s = cache.Get(ropts, 2, file_size_, "testkey", &result, handler);
  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(result.called);
  EXPECT_EQ(result.value, "testvalue");
}

// Test that Get does not call handler for a non-existent key in the table
TEST_F(TableCacheTest_352, GetNonExistentKey_352) {
  CreateTableFile(3, "existingkey", "existingvalue");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  bool called = false;
  auto handler = [](void* arg, const Slice& key, const Slice& value) {
    *reinterpret_cast<bool*>(arg) = true;
  };

  Status s = cache.Get(ropts, 3, file_size_, "nonexistent", &called, handler);
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(called);
}

// Test that Evict removes a cached table, so subsequent access re-reads from disk
TEST_F(TableCacheTest_352, EvictRemovesCachedEntry_352) {
  CreateTableFile(4, "key4", "value4");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  // First access: loads into cache
  {
    Table* tableptr = nullptr;
    Iterator* iter = cache.NewIterator(ropts, 4, file_size_, &tableptr);
    ASSERT_TRUE(iter->status().ok());
    iter->SeekToFirst();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "key4");
    delete iter;
  }

  // Evict
  cache.Evict(4);

  // Access again: should still work (re-read from disk)
  {
    Table* tableptr = nullptr;
    Iterator* iter = cache.NewIterator(ropts, 4, file_size_, &tableptr);
    ASSERT_TRUE(iter->status().ok());
    iter->SeekToFirst();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "key4");
    delete iter;
  }
}

// Test that after Evict + file deletion, the file can no longer be opened
TEST_F(TableCacheTest_352, EvictThenDeleteFile_352) {
  CreateTableFile(5, "key5", "value5");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  // Load into cache
  {
    Table* tableptr = nullptr;
    Iterator* iter = cache.NewIterator(ropts, 5, file_size_, &tableptr);
    ASSERT_TRUE(iter->status().ok());
    delete iter;
  }

  // Evict from cache
  cache.Evict(5);

  // Delete the underlying file
  char buf[100];
  std::snprintf(buf, sizeof(buf), "/%06llu.ldb", 5ULL);
  std::string fname = dbname_ + buf;
  env_->RemoveFile(fname);

  // Now trying to open should fail
  {
    Table* tableptr = nullptr;
    Iterator* iter = cache.NewIterator(ropts, 5, file_size_, &tableptr);
    EXPECT_FALSE(iter->status().ok());
    delete iter;
  }
}

// Test NewIterator with tableptr set to nullptr (should still work)
TEST_F(TableCacheTest_352, NewIteratorNullTablePtr_352) {
  CreateTableFile(6, "key6", "value6");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  Iterator* iter = cache.NewIterator(ropts, 6, file_size_, nullptr);
  ASSERT_NE(iter, nullptr);
  ASSERT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key6");

  delete iter;
}

// Test multiple Evicts on the same file number (should not crash)
TEST_F(TableCacheTest_352, DoubleEvict_352) {
  CreateTableFile(7, "key7", "value7");

  TableCache cache(dbname_, options_, 10);
  ReadOptions ropts;

  // Load into cache
  {
    Iterator* iter = cache.NewIterator(ropts, 7, file_size_, nullptr);
    ASSERT_TRUE(iter->status().ok());
    delete iter;
  }

  cache.Evict(7);
  cache.Evict(7);  // Second evict should be a no-op
}

// Test with boundary file numbers
TEST_F(TableCacheTest_352, EvictBoundaryFileNumbers_352) {
  TableCache cache(dbname_, options_, 10);
  // These should not crash
  cache.Evict(0);
  cache.Evict(1);
  cache.Evict(UINT64_MAX);
  cache.Evict(UINT64_MAX - 1);
}

// Test with a small cache size (1 entry)
TEST_F(TableCacheTest_352, SmallCacheSize_352) {
  CreateTableFile(10, "key10", "value10");
  CreateTableFile(11, "key11", "value11");

  TableCache cache(dbname_, options_, 1);
  ReadOptions ropts;

  // Load file 10
  {
    Iterator* iter = cache.NewIterator(ropts, 10, file_size_, nullptr);
    ASSERT_TRUE(iter->status().ok());
    iter->SeekToFirst();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "key10");
    delete iter;
  }

  // Create file 11 with potentially different size - need to track it
  uint64_t file_size_11 = file_size_;

  // Load file 11 - this might evict file 10 from the cache due to size=1
  {
    Iterator* iter = cache.NewIterator(ropts, 11, file_size_11, nullptr);
    ASSERT_TRUE(iter->status().ok());
    iter->SeekToFirst();
    ASSERT_TRUE(iter->Valid());
    EXPECT_EQ(iter->key().ToString(), "key11");
    delete iter;
  }
}

}  // namespace leveldb
