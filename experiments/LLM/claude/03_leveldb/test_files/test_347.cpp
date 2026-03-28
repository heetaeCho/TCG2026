#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/table_cache.h"
#include "leveldb/env.h"
#include "leveldb/table.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"
#include "util/testutil.h"
#include "db/filename.h"
#include "leveldb/table_builder.h"

#include <string>
#include <memory>

namespace leveldb {

class TableCacheTest_347 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/table_cache_test_347";
    env_->CreateDir(dbname_);
    options_.env = env_;
    cache_ = new TableCache(dbname_, options_, 10);
  }

  void TearDown() override {
    delete cache_;
    // Clean up files
    std::vector<std::string> files;
    env_->GetChildren(dbname_, &files);
    for (const auto& f : files) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  // Helper to create an SST file with some entries
  void CreateSSTable(uint64_t file_number, uint64_t* file_size,
                     const std::vector<std::pair<std::string, std::string>>& entries) {
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* wfile;
    ASSERT_TRUE(env_->NewWritableFile(fname, &wfile).ok());
    TableBuilder builder(options_, wfile);
    for (const auto& entry : entries) {
      builder.Add(entry.first, entry.second);
    }
    ASSERT_TRUE(builder.Finish().ok());
    *file_size = builder.FileSize();
    ASSERT_TRUE(wfile->Close().ok());
    delete wfile;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* cache_;
};

// Test that TableCache can be constructed and destroyed without issues
TEST_F(TableCacheTest_347, ConstructAndDestroy_347) {
  // Simply constructing and destroying (in TearDown) should work
  SUCCEED();
}

// Test creating a TableCache with a small capacity
TEST_F(TableCacheTest_347, SmallCapacity_347) {
  TableCache small_cache(dbname_, options_, 1);
  // Should not crash
  SUCCEED();
}

// Test that Get works on a valid table file
TEST_F(TableCacheTest_347, GetExistingKey_347) {
  uint64_t file_size;
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  CreateSSTable(1, &file_size, entries);

  ReadOptions ropts;
  Saver saver;
  std::string found_value;

  // Use NewIterator to verify the table can be opened
  Iterator* iter = cache_->NewIterator(ropts, 1, file_size);
  ASSERT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "value1");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test NewIterator on a non-existent file returns error
TEST_F(TableCacheTest_347, NewIteratorNonExistentFile_347) {
  ReadOptions ropts;
  Iterator* iter = cache_->NewIterator(ropts, 99999, 100);
  EXPECT_FALSE(iter->status().ok());
  delete iter;
}

// Test that Evict removes cached table entry
TEST_F(TableCacheTest_347, EvictRemovesCachedEntry_347) {
  uint64_t file_size;
  std::vector<std::pair<std::string, std::string>> entries = {
      {"key1", "value1"},
  };
  CreateSSTable(2, &file_size, entries);

  // Open the table
  ReadOptions ropts;
  Iterator* iter = cache_->NewIterator(ropts, 2, file_size);
  ASSERT_TRUE(iter->status().ok());
  delete iter;

  // Evict it
  cache_->Evict(2);

  // Should still be able to reopen it (file still exists)
  iter = cache_->NewIterator(ropts, 2, file_size);
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test that Evict on non-cached file doesn't crash
TEST_F(TableCacheTest_347, EvictNonCachedFile_347) {
  cache_->Evict(12345);
  SUCCEED();
}

// Test that cache eviction works when capacity is exceeded (exercises DeleteEntry)
TEST_F(TableCacheTest_347, CacheEvictionDeletesEntry_347) {
  // Create a cache with capacity of 2
  delete cache_;
  cache_ = new TableCache(dbname_, options_, 2);

  uint64_t file_size1, file_size2, file_size3;
  CreateSSTable(10, &file_size1, {{"a", "1"}});
  CreateSSTable(11, &file_size2, {{"b", "2"}});
  CreateSSTable(12, &file_size3, {{"c", "3"}});

  ReadOptions ropts;

  // Open 3 tables, which should cause eviction of at least one
  Iterator* iter1 = cache_->NewIterator(ropts, 10, file_size1);
  ASSERT_TRUE(iter1->status().ok());
  delete iter1;

  Iterator* iter2 = cache_->NewIterator(ropts, 11, file_size2);
  ASSERT_TRUE(iter2->status().ok());
  delete iter2;

  Iterator* iter3 = cache_->NewIterator(ropts, 12, file_size3);
  ASSERT_TRUE(iter3->status().ok());
  delete iter3;

  // All should still be openable (files exist on disk)
  iter1 = cache_->NewIterator(ropts, 10, file_size1);
  ASSERT_TRUE(iter1->status().ok());
  delete iter1;
}

// Test multiple opens of the same file reuse cached entry
TEST_F(TableCacheTest_347, MultipleOpensOfSameFile_347) {
  uint64_t file_size;
  CreateSSTable(20, &file_size, {{"hello", "world"}});

  ReadOptions ropts;
  Iterator* iter1 = cache_->NewIterator(ropts, 20, file_size);
  ASSERT_TRUE(iter1->status().ok());

  Iterator* iter2 = cache_->NewIterator(ropts, 20, file_size);
  ASSERT_TRUE(iter2->status().ok());

  iter1->SeekToFirst();
  iter2->SeekToFirst();
  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter1->key().ToString(), "hello");
  EXPECT_EQ(iter2->key().ToString(), "hello");

  delete iter1;
  delete iter2;
}

// Test empty table
TEST_F(TableCacheTest_347, EmptyTable_347) {
  uint64_t file_size;
  CreateSSTable(30, &file_size, {});

  ReadOptions ropts;
  Iterator* iter = cache_->NewIterator(ropts, 30, file_size);
  ASSERT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test Evict followed by reopen exercises DeleteEntry path
TEST_F(TableCacheTest_347, EvictThenReopen_347) {
  uint64_t file_size;
  CreateSSTable(40, &file_size, {{"x", "y"}});

  ReadOptions ropts;

  // Open
  Iterator* iter = cache_->NewIterator(ropts, 40, file_size);
  ASSERT_TRUE(iter->status().ok());
  delete iter;

  // Evict (triggers DeleteEntry)
  cache_->Evict(40);

  // Reopen
  iter = cache_->NewIterator(ropts, 40, file_size);
  ASSERT_TRUE(iter->status().ok());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->value().ToString(), "y");
  delete iter;
}

// Test destruction of TableCache with cached entries exercises DeleteEntry
TEST_F(TableCacheTest_347, DestructionWithCachedEntries_347) {
  uint64_t file_size;
  CreateSSTable(50, &file_size, {{"k", "v"}});

  ReadOptions ropts;
  Iterator* iter = cache_->NewIterator(ropts, 50, file_size);
  ASSERT_TRUE(iter->status().ok());
  delete iter;

  // cache_ will be deleted in TearDown, which should clean up all entries
  // via DeleteEntry without crashing
}

}  // namespace leveldb
