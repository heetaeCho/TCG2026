// File: db_cache_create_lru_test_280.cc

#include <gtest/gtest.h>
#include <cstddef>
#include <string>

// Use LevelDB C++ cache API to observe behavior.
#include "leveldb/cache.h"
#include "leveldb/slice.h"

// Extern C for the C API function under test.
extern "C" {
  // Forward declaration of the opaque C type and factory we are testing.
  typedef struct leveldb_cache_t leveldb_cache_t;
  leveldb_cache_t* leveldb_cache_create_lru(size_t capacity);
}

// The prompt exposes the struct layout (public member), which we treat as part of the interface.
struct leveldb_cache_t { leveldb::Cache* rep; };

// ---- Test fixture ----
class CacheCreateLRUTest_280 : public ::testing::Test {
protected:
  // Simple deleter for cache entries: deletes the stored int*.
  static void IntDeleter(const leveldb::Slice&, void* value) {
    delete static_cast<int*>(value);
  }

  static leveldb::Slice S(const char* s) { return leveldb::Slice(s); }
};

// [Normal] Creating with positive capacity yields a valid wrapper & cache rep.
TEST_F(CacheCreateLRUTest_280, CreateWithPositiveCapacity_YieldsNonNull_280) {
  const size_t capacity = 1024;
  leveldb_cache_t* c = leveldb_cache_create_lru(capacity);

  ASSERT_NE(c, nullptr);
  ASSERT_NE(c->rep, nullptr);

  // Basic sanity: Insert/Lookup through the public Cache API.
  auto* h = c->rep->Insert(S("k"), new int(7), /*charge=*/1, &IntDeleter);
  ASSERT_NE(h, nullptr);
  c->rep->Release(h);

  h = c->rep->Lookup(S("k"));
  ASSERT_NE(h, nullptr);
  auto* v = static_cast<int*>(c->rep->Value(h));
  EXPECT_EQ(*v, 7);
  c->rep->Release(h);

  // Note: We intentionally do not destroy the cache because a destroy function
  // is not part of the provided interface.
}

// [Boundary] Zero capacity: wrapper and rep should still be constructed (no crash).
TEST_F(CacheCreateLRUTest_280, CreateWithZeroCapacity_RepIsNonNull_280) {
  leveldb_cache_t* c = leveldb_cache_create_lru(0);
  ASSERT_NE(c, nullptr);
  ASSERT_NE(c->rep, nullptr);
  // We avoid asserting eviction semantics here to keep behavior black-box safe.
}

// [Behavior] Two independent caches do not share entries.
TEST_F(CacheCreateLRUTest_280, IndependentInstances_IsolatedKeyspaces_280) {
  leveldb_cache_t* c1 = leveldb_cache_create_lru(128);
  leveldb_cache_t* c2 = leveldb_cache_create_lru(128);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  ASSERT_NE(c1->rep, nullptr);
  ASSERT_NE(c2->rep, nullptr);

  // Put same key into cache #1 only.
  auto* h1 = c1->rep->Insert(S("shared_key"), new int(42), /*charge=*/1, &IntDeleter);
  ASSERT_NE(h1, nullptr);
  c1->rep->Release(h1);

  // Lookup in cache #1 succeeds.
  h1 = c1->rep->Lookup(S("shared_key"));
  ASSERT_NE(h1, nullptr);
  EXPECT_EQ(*static_cast<int*>(c1->rep->Value(h1)), 42);
  c1->rep->Release(h1);

  // Lookup in cache #2 should fail (isolation).
  auto* h2 = c2->rep->Lookup(S("shared_key"));
  EXPECT_EQ(h2, nullptr);
}

// [Capacity/Boundary] Small capacity should enforce LRU behavior (observable via API).
TEST_F(CacheCreateLRUTest_280, CapacityIsHonored_LRUEvictionObservable_280) {
  // Capacity small enough that three 50-charge inserts cannot all co-exist.
  const size_t capacity = 100;
  leveldb_cache_t* c = leveldb_cache_create_lru(capacity);
  ASSERT_NE(c, nullptr);
  ASSERT_NE(c->rep, nullptr);

  // Insert k1, k2 (both fit).
  auto* h = c->rep->Insert(S("k1"), new int(1), /*charge=*/50, &IntDeleter);
  ASSERT_NE(h, nullptr);
  c->rep->Release(h);

  h = c->rep->Insert(S("k2"), new int(2), /*charge=*/50, &IntDeleter);
  ASSERT_NE(h, nullptr);
  c->rep->Release(h);

  // Touch k1 to make it most-recently used; k2 becomes LRU.
  h = c->rep->Lookup(S("k1"));
  ASSERT_NE(h, nullptr);
  c->rep->Release(h);

  // Insert k3; this should evict k2 if capacity was correctly applied.
  h = c->rep->Insert(S("k3"), new int(3), /*charge=*/50, &IntDeleter);
  ASSERT_NE(h, nullptr);
  c->rep->Release(h);

  // k1 should still be present (recently used).
  h = c->rep->Lookup(S("k1"));
  ASSERT_NE(h, nullptr);
  EXPECT_EQ(*static_cast<int*>(c->rep->Value(h)), 1);
  c->rep->Release(h);

  // k2 should be evicted.
  h = c->rep->Lookup(S("k2"));
  EXPECT_EQ(h, nullptr);

  // k3 should be present.
  h = c->rep->Lookup(S("k3"));
  ASSERT_NE(h, nullptr);
  EXPECT_EQ(*static_cast<int*>(c->rep->Value(h)), 3);
  c->rep->Release(h);
}

// [Stress/Normal] Large capacity still supports basic operations without eviction pressure.
TEST_F(CacheCreateLRUTest_280, LargeCapacity_BasicInsertLookup_280) {
  const size_t capacity = 1 << 20; // ~1MB
  leveldb_cache_t* c = leveldb_cache_create_lru(capacity);
  ASSERT_NE(c, nullptr);
  ASSERT_NE(c->rep, nullptr);

  // Insert a few items and verify lookups.
  for (int i = 0; i < 5; ++i) {
    std::string key = "key" + std::to_string(i);
    auto* h = c->rep->Insert(S(key.c_str()), new int(i), /*charge=*/10, &CacheCreateLRUTest_280::IntDeleter);
    ASSERT_NE(h, nullptr);
    c->rep->Release(h);
  }

  for (int i = 0; i < 5; ++i) {
    std::string key = "key" + std::to_string(i);
    auto* h = c->rep->Lookup(S(key.c_str()));
    ASSERT_NE(h, nullptr) << "Missing: " << key;
    EXPECT_EQ(*static_cast<int*>(c->rep->Value(h)), i);
    c->rep->Release(h);
  }
}
