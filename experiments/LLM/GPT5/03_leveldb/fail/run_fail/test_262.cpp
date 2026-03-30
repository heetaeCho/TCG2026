// File: db/c_options_set_cache_test.cc

#include <gtest/gtest.h>

// --- Minimal public-facing declarations based on the prompt ---
// We only declare what's necessary to observe effects via the interface,
// without re-implementing internal logic.

namespace leveldb {
class Cache;  // Incomplete type is fine for pointer equality checks.

// Minimal Options with only the field we need to observe.
// Default-construct to nullptr to allow boundary checks safely.
struct Options {
  Cache* block_cache;
  Options() : block_cache(nullptr) {}
};
}  // namespace leveldb

// C-API wrapper structs as given in the prompt.
struct leveldb_options_t { leveldb::Options rep; };
struct leveldb_cache_t  { leveldb::Cache*  rep; };

// Function under test (from db/c.cc).
extern "C" void leveldb_options_set_cache(leveldb_options_t* opt,
                                          leveldb_cache_t* c);

// ----------------------------- Tests -----------------------------

// Normal operation: sets block_cache to the cache rep pointer.
TEST(LevelDBOptionsSetCache_262, SetsCachePointer_262) {
  leveldb_options_t opt;                 // opt.rep.block_cache starts as nullptr
  leveldb_cache_t cache;

  // Use a non-null, non-dereferenced sentinel pointer for equality check.
  auto* fake_cache_ptr = reinterpret_cast<leveldb::Cache*>(0x1);
  cache.rep = fake_cache_ptr;

  leveldb_options_set_cache(&opt, &cache);

  EXPECT_EQ(opt.rep.block_cache, fake_cache_ptr)
      << "block_cache should be set to the provided cache rep pointer.";
}

// Boundary: cache wrapper provided but its rep is nullptr.
TEST(LevelDBOptionsSetCache_262, SetsNullWhenCacheRepIsNull_262) {
  leveldb_options_t opt;
  // Pre-seed to a non-null value to ensure it actually changes to nullptr.
  opt.rep.block_cache = reinterpret_cast<leveldb::Cache*>(0x2);

  leveldb_cache_t cache;
  cache.rep = nullptr;

  leveldb_options_set_cache(&opt, &cache);

  EXPECT_EQ(opt.rep.block_cache, nullptr)
      << "block_cache should become nullptr when cache->rep is nullptr.";
}

// Overwrite behavior: previously set block_cache should be overwritten.
TEST(LevelDBOptionsSetCache_262, OverwritesExistingCache_262) {
  leveldb_options_t opt;
  auto* old_ptr = reinterpret_cast<leveldb::Cache*>(0x3);
  auto* new_ptr = reinterpret_cast<leveldb::Cache*>(0x4);

  // Seed existing value.
  opt.rep.block_cache = old_ptr;

  leveldb_cache_t cache;
  cache.rep = new_ptr;

  leveldb_options_set_cache(&opt, &cache);

  EXPECT_NE(opt.rep.block_cache, old_ptr)
      << "block_cache should not retain the old pointer.";
  EXPECT_EQ(opt.rep.block_cache, new_ptr)
      << "block_cache should be updated to the new pointer.";
}

// Defensive shape test: calling with a valid opt and a valid cache wrapper
// should only touch block_cache (we can at least ensure it remains consistent
// across multiple calls with differing pointers).
TEST(LevelDBOptionsSetCache_262, IdempotentAcrossDifferentInputs_262) {
  leveldb_options_t opt;

  leveldb_cache_t cacheA;
  leveldb_cache_t cacheB;

  auto* ptrA = reinterpret_cast<leveldb::Cache*>(0x10);
  auto* ptrB = reinterpret_cast<leveldb::Cache*>(0x20);

  cacheA.rep = ptrA;
  cacheB.rep = ptrB;

  leveldb_options_set_cache(&opt, &cacheA);
  EXPECT_EQ(opt.rep.block_cache, ptrA);

  leveldb_options_set_cache(&opt, &cacheB);
  EXPECT_EQ(opt.rep.block_cache, ptrB)
      << "block_cache should reflect the most recent call.";
}
