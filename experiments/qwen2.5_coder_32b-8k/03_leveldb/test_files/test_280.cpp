#include <gtest/gtest.h>

#include "db/c.cc"



// Assuming leveldb_cache_create_lru and Cache are part of the namespace or linked correctly



TEST(LeveldbCacheCreateLRUTest_280, CreateWithValidCapacity_280) {

    size_t capacity = 1024;

    leveldb_cache_t* cache = leveldb_cache_create_lru(capacity);

    ASSERT_NE(cache, nullptr);

    delete cache;

}



TEST(LeveldbCacheCreateLRUTest_280, CreateWithZeroCapacity_280) {

    size_t capacity = 0;

    leveldb_cache_t* cache = leveldb_cache_create_lru(capacity);

    ASSERT_NE(cache, nullptr);

    delete cache;

}



TEST(LeveldbCacheCreateLRUTest_280, CreateWithLargeCapacity_280) {

    size_t capacity = 1024 * 1024 * 1024; // 1GB

    leveldb_cache_t* cache = leveldb_cache_create_lru(capacity);

    ASSERT_NE(cache, nullptr);

    delete cache;

}



// Assuming there are no observable exceptional cases for this function based on the provided interface



TEST(LeveldbCacheCreateLRUTest_280, CreateMultipleCaches_280) {

    size_t capacity = 1024;

    leveldb_cache_t* cache1 = leveldb_cache_create_lru(capacity);

    leveldb_cache_t* cache2 = leveldb_cache_create_lru(capacity);

    ASSERT_NE(cache1, nullptr);

    ASSERT_NE(cache2, nullptr);

    delete cache1;

    delete cache2;

}
