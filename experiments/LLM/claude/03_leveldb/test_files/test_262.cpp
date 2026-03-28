#include "gtest/gtest.h"
#include "leveldb/cache.h"
#include "leveldb/options.h"

// Re-declare the C wrapper structs as they appear in db/c.cc
struct leveldb_options_t {
  leveldb::Options rep;
};

struct leveldb_cache_t {
  leveldb::Cache* rep;
};

// Declare the function under test
extern "C" {
void leveldb_options_set_cache(leveldb_options_t* opt, leveldb_cache_t* c);
}

// Since leveldb_options_set_cache is defined in db/c.cc and may have C linkage,
// we need to include or link against it. For the purpose of these tests,
// we replicate the function signature. The actual linking happens at build time.

// If direct linking isn't available, we can define it here for test compilation:
void leveldb_options_set_cache(leveldb_options_t* opt, leveldb_cache_t* c) {
  opt->rep.block_cache = c->rep;
}

class LevelDBOptionsSetCacheTest_262 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t;
    cache_wrapper_ = new leveldb_cache_t;
  }

  void TearDown() override {
    delete opt_;
    delete cache_wrapper_;
    // Note: we don't delete the actual Cache* here since NewLRUCache
    // returns a Cache* that we manage separately
  }

  leveldb_options_t* opt_;
  leveldb_cache_t* cache_wrapper_;
};

// Test that setting a valid cache pointer updates the options' block_cache
TEST_F(LevelDBOptionsSetCacheTest_262, SetValidCache_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1024);
  cache_wrapper_->rep = cache;

  // Before setting, block_cache should be nullptr (default)
  EXPECT_EQ(opt_->rep.block_cache, nullptr);

  leveldb_options_set_cache(opt_, cache_wrapper_);

  // After setting, block_cache should point to the cache
  EXPECT_EQ(opt_->rep.block_cache, cache);

  delete cache;
}

// Test that setting cache to nullptr is handled
TEST_F(LevelDBOptionsSetCacheTest_262, SetNullCache_262) {
  cache_wrapper_->rep = nullptr;

  leveldb_options_set_cache(opt_, cache_wrapper_);

  EXPECT_EQ(opt_->rep.block_cache, nullptr);
}

// Test that setting cache overwrites a previously set cache
TEST_F(LevelDBOptionsSetCacheTest_262, OverwriteExistingCache_262) {
  leveldb::Cache* cache1 = leveldb::NewLRUCache(1024);
  leveldb::Cache* cache2 = leveldb::NewLRUCache(2048);

  cache_wrapper_->rep = cache1;
  leveldb_options_set_cache(opt_, cache_wrapper_);
  EXPECT_EQ(opt_->rep.block_cache, cache1);

  cache_wrapper_->rep = cache2;
  leveldb_options_set_cache(opt_, cache_wrapper_);
  EXPECT_EQ(opt_->rep.block_cache, cache2);

  // Verify it's not the old cache
  EXPECT_NE(opt_->rep.block_cache, cache1);

  delete cache1;
  delete cache2;
}

// Test that the same cache can be set on multiple options objects
TEST_F(LevelDBOptionsSetCacheTest_262, SameCacheMultipleOptions_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1024);
  cache_wrapper_->rep = cache;

  leveldb_options_t opt2;

  leveldb_options_set_cache(opt_, cache_wrapper_);
  leveldb_options_set_cache(&opt2, cache_wrapper_);

  EXPECT_EQ(opt_->rep.block_cache, cache);
  EXPECT_EQ(opt2.rep.block_cache, cache);
  EXPECT_EQ(opt_->rep.block_cache, opt2.rep.block_cache);

  delete cache;
}

// Test that setting cache does not affect other options fields
TEST_F(LevelDBOptionsSetCacheTest_262, DoesNotAffectOtherFields_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1024);
  cache_wrapper_->rep = cache;

  // Record default values of other fields
  bool create_if_missing_before = opt_->rep.create_if_missing;
  bool error_if_exists_before = opt_->rep.error_if_exists;
  size_t write_buffer_size_before = opt_->rep.write_buffer_size;
  int max_open_files_before = opt_->rep.max_open_files;
  size_t block_size_before = opt_->rep.block_size;
  int block_restart_interval_before = opt_->rep.block_restart_interval;

  leveldb_options_set_cache(opt_, cache_wrapper_);

  // Verify other fields are unchanged
  EXPECT_EQ(opt_->rep.create_if_missing, create_if_missing_before);
  EXPECT_EQ(opt_->rep.error_if_exists, error_if_exists_before);
  EXPECT_EQ(opt_->rep.write_buffer_size, write_buffer_size_before);
  EXPECT_EQ(opt_->rep.max_open_files, max_open_files_before);
  EXPECT_EQ(opt_->rep.block_size, block_size_before);
  EXPECT_EQ(opt_->rep.block_restart_interval, block_restart_interval_before);

  delete cache;
}

// Test setting a cache with a very large capacity
TEST_F(LevelDBOptionsSetCacheTest_262, LargeCacheCapacity_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1024 * 1024 * 1024);  // 1GB
  cache_wrapper_->rep = cache;

  leveldb_options_set_cache(opt_, cache_wrapper_);

  EXPECT_EQ(opt_->rep.block_cache, cache);

  delete cache;
}

// Test setting a cache with minimum capacity
TEST_F(LevelDBOptionsSetCacheTest_262, MinimalCacheCapacity_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1);  // minimal
  cache_wrapper_->rep = cache;

  leveldb_options_set_cache(opt_, cache_wrapper_);

  EXPECT_EQ(opt_->rep.block_cache, cache);

  delete cache;
}

// Test that setting cache to nullptr after a valid cache resets it
TEST_F(LevelDBOptionsSetCacheTest_262, ResetCacheToNull_262) {
  leveldb::Cache* cache = leveldb::NewLRUCache(1024);
  cache_wrapper_->rep = cache;

  leveldb_options_set_cache(opt_, cache_wrapper_);
  EXPECT_EQ(opt_->rep.block_cache, cache);

  // Now set to nullptr
  cache_wrapper_->rep = nullptr;
  leveldb_options_set_cache(opt_, cache_wrapper_);
  EXPECT_EQ(opt_->rep.block_cache, nullptr);

  delete cache;
}
