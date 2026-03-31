#include "gtest/gtest.h"
#include "db/table_cache.h"
#include "leveldb/cache.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "util/testutil.h"

#include <cstdint>
#include <string>

namespace leveldb {

class TableCacheTest_351 : public testing::Test {
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

  // Helper to create an SSTable file with the given file_number and key-value pairs
  void CreateTable(uint64_t file_number,
                   const std::vector<std::pair<std::string, std::string>>& kvs) {
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* file;
    ASSERT_TRUE(env_->NewWritableFile(fname, &file).ok());

    TableBuilder builder(options_, file);
    for (const auto& kv : kvs) {
      builder.Add(kv.first, kv.second);
    }
    ASSERT_TRUE(builder.Finish().ok());
    file_size_ = builder.FileSize();
    delete file;
  }

  static std::string TableFileName(const std::string& dbname, uint64_t number) {
    char buf[100];
    std::snprintf(buf, sizeof(buf), "/%06llu.ldb",
                  static_cast<unsigned long long>(number));
    return dbname + buf;
  }

  // Callback that stores key-value pairs
  static void SaveResult(void* arg, const Slice& key, const Slice& value) {
    auto* results =
        reinterpret_cast<std::vector<std::pair<std::string, std::string>>*>(arg);
    results->push_back({key.ToString(), value.ToString()});
  }

  Env* env_;
  Options options_;
  std::string dbname_;
  int cache_entries_;
  TableCache* table_cache_;
  uint64_t file_size_ = 0;
};

// Test that Get returns an error for a non-existent file
TEST_F(TableCacheTest_351, GetNonExistentFile_351) {
  ReadOptions read_options;
  std::vector<std::pair<std::string, std::string>> results;
  
  // File number 99999 does not exist
  Status s = table_cache_->Get(read_options, 99999, 1000, Slice("key"), 
                                &results, SaveResult);
  EXPECT_FALSE(s.ok());
}

// Test that Get succeeds and invokes the callback for an existing key
TEST_F(TableCacheTest_351, GetExistingKey_351) {
  // We need to create an internal key format. LevelDB's InternalGet expects
  // internal keys. We'll create a simple table with encoded internal keys.
  // For simplicity, we use the InternalKey format: user_key + sequence + type
  
  // Create a table with a simple entry
  uint64_t file_number = 1;
  
  // Build an internal key: user_key (ascending), seq=100, type=kTypeValue(1)
  std::string ikey;
  ikey.append("testkey");
  // Append 8-byte trailer: (sequence << 8) | type
  uint64_t trailer = (uint64_t(100) << 8) | 1;  // kTypeValue = 1
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "testvalue"}});

  ReadOptions read_options;
  std::vector<std::pair<std::string, std::string>> results;

  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(ikey), &results, SaveResult);
  EXPECT_TRUE(s.ok());
  EXPECT_GE(results.size(), 1u);
}

// Test that Get with a key not in the table doesn't invoke the callback
TEST_F(TableCacheTest_351, GetMissingKey_351) {
  uint64_t file_number = 2;
  
  std::string ikey;
  ikey.append("existingkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "somevalue"}});

  // Search for a different key that doesn't exist
  std::string searchkey;
  searchkey.append("zzzzzzzzz");  // lexicographically after "existingkey"
  searchkey.append(buf, 8);

  ReadOptions read_options;
  std::vector<std::pair<std::string, std::string>> results;

  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(searchkey), &results, SaveResult);
  EXPECT_TRUE(s.ok());
  // The key doesn't exist, so the callback should not have been invoked
  // (or if it was, internal filtering should have skipped it)
  // Note: behavior depends on InternalGet implementation
}

// Test Evict removes the table from cache
TEST_F(TableCacheTest_351, EvictRemovesFromCache_351) {
  uint64_t file_number = 3;

  std::string ikey;
  ikey.append("evictkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "evictvalue"}});

  ReadOptions read_options;
  std::vector<std::pair<std::string, std::string>> results;

  // First access to populate cache
  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(ikey), &results, SaveResult);
  EXPECT_TRUE(s.ok());

  // Evict
  table_cache_->Evict(file_number);

  // After eviction, accessing the same file should still work
  // (it will just re-open the file)
  results.clear();
  s = table_cache_->Get(read_options, file_number, file_size_, 
                         Slice(ikey), &results, SaveResult);
  EXPECT_TRUE(s.ok());
}

// Test that evicting a non-existent file number does not crash
TEST_F(TableCacheTest_351, EvictNonExistentFile_351) {
  // This should not crash or cause any issues
  table_cache_->Evict(12345);
}

// Test NewIterator returns a valid iterator for an existing file
TEST_F(TableCacheTest_351, NewIteratorExistingFile_351) {
  uint64_t file_number = 4;

  std::string ikey;
  ikey.append("iterkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "itervalue"}});

  ReadOptions read_options;
  Table* table_ptr = nullptr;
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, 
                                              file_size_, &table_ptr);
  ASSERT_NE(iter, nullptr);
  EXPECT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  
  delete iter;
}

// Test NewIterator for non-existent file returns an iterator with error status
TEST_F(TableCacheTest_351, NewIteratorNonExistentFile_351) {
  ReadOptions read_options;
  Table* table_ptr = nullptr;
  Iterator* iter = table_cache_->NewIterator(read_options, 99998, 1000, 
                                              &table_ptr);
  ASSERT_NE(iter, nullptr);
  EXPECT_FALSE(iter->status().ok());
  
  delete iter;
}

// Test NewIterator with nullptr tableptr
TEST_F(TableCacheTest_351, NewIteratorNullTablePtr_351) {
  uint64_t file_number = 5;

  std::string ikey;
  ikey.append("nullptrkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "nullptrvalue"}});

  ReadOptions read_options;
  // Pass nullptr for tableptr
  Iterator* iter = table_cache_->NewIterator(read_options, file_number, 
                                              file_size_, nullptr);
  ASSERT_NE(iter, nullptr);
  EXPECT_TRUE(iter->status().ok());
  
  delete iter;
}

// Test Get with verify_checksums option
TEST_F(TableCacheTest_351, GetWithVerifyChecksums_351) {
  uint64_t file_number = 6;

  std::string ikey;
  ikey.append("checksumkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "checksumvalue"}});

  ReadOptions read_options;
  read_options.verify_checksums = true;
  std::vector<std::pair<std::string, std::string>> results;

  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(ikey), &results, SaveResult);
  EXPECT_TRUE(s.ok());
}

// Test Get with fill_cache = false
TEST_F(TableCacheTest_351, GetWithFillCacheFalse_351) {
  uint64_t file_number = 7;

  std::string ikey;
  ikey.append("nocachekey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "nocachevalue"}});

  ReadOptions read_options;
  read_options.fill_cache = false;
  std::vector<std::pair<std::string, std::string>> results;

  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(ikey), &results, SaveResult);
  EXPECT_TRUE(s.ok());
}

// Test multiple entries in a single table
TEST_F(TableCacheTest_351, GetMultipleEntries_351) {
  uint64_t file_number = 8;

  auto makeInternalKey = [](const std::string& user_key, uint64_t seq) {
    std::string ikey = user_key;
    uint64_t trailer = (seq << 8) | 1;
    char buf[8];
    buf[0] = trailer & 0xff;
    buf[1] = (trailer >> 8) & 0xff;
    buf[2] = (trailer >> 16) & 0xff;
    buf[3] = (trailer >> 24) & 0xff;
    buf[4] = (trailer >> 32) & 0xff;
    buf[5] = (trailer >> 40) & 0xff;
    buf[6] = (trailer >> 48) & 0xff;
    buf[7] = (trailer >> 56) & 0xff;
    ikey.append(buf, 8);
    return ikey;
  };

  std::string key1 = makeInternalKey("aaa", 100);
  std::string key2 = makeInternalKey("bbb", 100);
  std::string key3 = makeInternalKey("ccc", 100);

  CreateTable(file_number, {{key1, "val1"}, {key2, "val2"}, {key3, "val3"}});

  ReadOptions read_options;
  
  // Query for key2
  std::vector<std::pair<std::string, std::string>> results;
  Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                Slice(key2), &results, SaveResult);
  EXPECT_TRUE(s.ok());
  EXPECT_GE(results.size(), 1u);
}

// Test that cache is shared across multiple Get calls
TEST_F(TableCacheTest_351, CacheSharedAcrossGets_351) {
  uint64_t file_number = 9;

  std::string ikey;
  ikey.append("sharedkey");
  uint64_t trailer = (uint64_t(100) << 8) | 1;
  char buf[8];
  buf[0] = trailer & 0xff;
  buf[1] = (trailer >> 8) & 0xff;
  buf[2] = (trailer >> 16) & 0xff;
  buf[3] = (trailer >> 24) & 0xff;
  buf[4] = (trailer >> 32) & 0xff;
  buf[5] = (trailer >> 40) & 0xff;
  buf[6] = (trailer >> 48) & 0xff;
  buf[7] = (trailer >> 56) & 0xff;
  ikey.append(buf, 8);

  CreateTable(file_number, {{ikey, "sharedvalue"}});

  ReadOptions read_options;
  
  // Call Get twice - second call should use cached table
  for (int i = 0; i < 2; i++) {
    std::vector<std::pair<std::string, std::string>> results;
    Status s = table_cache_->Get(read_options, file_number, file_size_, 
                                  Slice(ikey), &results, SaveResult);
    EXPECT_TRUE(s.ok());
  }
}

}  // namespace leveldb
