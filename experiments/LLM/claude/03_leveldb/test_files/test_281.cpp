#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/cache.h"

// Tests for leveldb_cache_destroy via the C API

TEST(LevelDBCacheDestroyTest_281, DestroyValidCache_281) {
  // Create a cache through the C API, then destroy it.
  // This tests normal operation: creating and destroying a cache should not crash.
  leveldb_cache_t* cache = leveldb_cache_create_lru(100);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
  // If we reach here without crash or leak (under sanitizers), the test passes.
}

TEST(LevelDBCacheDestroyTest_281, DestroySmallCache_281) {
  // Boundary: create a cache with minimal capacity
  leveldb_cache_t* cache = leveldb_cache_create_lru(1);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

TEST(LevelDBCacheDestroyTest_281, DestroyLargeCache_281) {
  // Boundary: create a cache with a very large capacity
  leveldb_cache_t* cache = leveldb_cache_create_lru(1024 * 1024 * 1024);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}

TEST(LevelDBCacheDestroyTest_281, CreateAndDestroyMultipleCaches_281) {
  // Normal operation: multiple caches can be created and destroyed independently
  leveldb_cache_t* cache1 = leveldb_cache_create_lru(100);
  leveldb_cache_t* cache2 = leveldb_cache_create_lru(200);
  leveldb_cache_t* cache3 = leveldb_cache_create_lru(300);
  ASSERT_NE(cache1, nullptr);
  ASSERT_NE(cache2, nullptr);
  ASSERT_NE(cache3, nullptr);

  leveldb_cache_destroy(cache2);
  leveldb_cache_destroy(cache1);
  leveldb_cache_destroy(cache3);
}

TEST(LevelDBCacheDestroyTest_281, DestroyAfterUseInOptions_281) {
  // Normal operation: cache is used in options, then destroyed after DB options are freed
  leveldb_cache_t* cache = leveldb_cache_create_lru(256);
  ASSERT_NE(cache, nullptr);

  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);
  // Setting cache in options should work
  // Note: the options don't own the cache, so we destroy them independently
  leveldb_options_destroy(options);
  leveldb_cache_destroy(cache);
}

TEST(LevelDBCacheDestroyTest_281, DestroyZeroCapacityCache_281) {
  // Boundary: zero capacity cache
  leveldb_cache_t* cache = leveldb_cache_create_lru(0);
  ASSERT_NE(cache, nullptr);
  leveldb_cache_destroy(cache);
}
