#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

// Test normal creation with a typical capacity
TEST(LevelDBCacheCreateLRU_280, NormalCapacity_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(1024);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

// Test creation with zero capacity
TEST(LevelDBCacheCreateLRU_280, ZeroCapacity_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(0);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

// Test creation with a very large capacity
TEST(LevelDBCacheCreateLRU_280, LargeCapacity_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(1024 * 1024 * 1024);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

// Test creation with capacity of 1
TEST(LevelDBCacheCreateLRU_280, MinimalCapacity_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(1);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

// Test creation with max size_t value
TEST(LevelDBCacheCreateLRU_280, MaxCapacity_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(static_cast<size_t>(-1));
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

// Test multiple cache creations to ensure independence
TEST(LevelDBCacheCreateLRU_280, MultipleCaches_280) {
  leveldb_cache_t* cache1 = leveldb_cache_create_lru(100);
  leveldb_cache_t* cache2 = leveldb_cache_create_lru(200);
  ASSERT_NE(cache1, nullptr);
  ASSERT_NE(cache2, nullptr);
  ASSERT_NE(cache1, cache2);
  leveldb_cache_destroy(cache1);
  leveldb_cache_destroy(cache2);
}

// Test that the created cache can be used with leveldb options
TEST(LevelDBCacheCreateLRU_280, UsableWithOptions_280) {
  leveldb_cache_t* cache = leveldb_cache_create_lru(8 * 1024 * 1024);
  ASSERT_NE(cache, nullptr);

  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);

  // Setting the cache on options should not crash
  leveldb_options_set_cache(options, cache);

  leveldb_options_destroy(options);
  leveldb_cache_destroy(cache);
}
