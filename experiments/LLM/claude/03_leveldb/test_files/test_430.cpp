#include "gtest/gtest.h"
#include "leveldb/cache.h"
#include "util/coding.h"
#include <string>
#include <vector>

namespace leveldb {

// Helper function to create a Slice key from an integer
static std::string EncodeKey(int k) {
  std::string result;
  PutFixed32(&result, k);
  return result;
}

// Simple deleter that tracks deletions
static int deleted_keys[1024];
static int deleted_values[1024];
static int deleter_count = 0;

static void ResetDeleters() {
  deleter_count = 0;
  memset(deleted_keys, 0, sizeof(deleted_keys));
  memset(deleted_values, 0, sizeof(deleted_values));
}

static void Deleter(const Slice& key, void* v) {
  if (deleter_count < 1024) {
    deleted_keys[deleter_count] = DecodeFixed32(key.data());
    deleted_values[deleter_count] = reinterpret_cast<uintptr_t>(v);
    deleter_count++;
  }
}

class CacheTest_430 : public ::testing::Test {
 protected:
  void SetUp() override {
    ResetDeleters();
    cache_ = NewLRUCache(capacity_);
  }

  void TearDown() override {
    delete cache_;
  }

  Cache::Handle* Insert(int key, int value, int charge = 1) {
    return cache_->Insert(EncodeKey(key), reinterpret_cast<void*>(value),
                          charge, &Deleter);
  }

  int Lookup(int key) {
    Cache::Handle* h = cache_->Lookup(EncodeKey(key));
    if (h == nullptr) return -1;
    int val = reinterpret_cast<uintptr_t>(cache_->Value(h));
    cache_->Release(h);
    return val;
  }

  void Erase(int key) {
    cache_->Erase(EncodeKey(key));
  }

  static const size_t capacity_ = 100;
  Cache* cache_ = nullptr;
};

TEST_F(CacheTest_430, NewCacheIsEmpty_430) {
  EXPECT_EQ(-1, Lookup(0));
  EXPECT_EQ(-1, Lookup(1));
  EXPECT_EQ(-1, Lookup(100));
}

TEST_F(CacheTest_430, InsertAndLookup_430) {
  Insert(1, 100);
  Insert(2, 200);

  EXPECT_EQ(100, Lookup(1));
  EXPECT_EQ(200, Lookup(2));
  EXPECT_EQ(-1, Lookup(3));
}

TEST_F(CacheTest_430, InsertDuplicateKeyOverwrites_430) {
  Insert(1, 100);
  EXPECT_EQ(100, Lookup(1));

  Insert(1, 200);
  EXPECT_EQ(200, Lookup(1));
}

TEST_F(CacheTest_430, EraseRemovesEntry_430) {
  Insert(1, 100);
  EXPECT_EQ(100, Lookup(1));

  Erase(1);
  EXPECT_EQ(-1, Lookup(1));
}

TEST_F(CacheTest_430, EraseNonexistentKeyIsNoOp_430) {
  // Should not crash
  Erase(999);
  EXPECT_EQ(-1, Lookup(999));
}

TEST_F(CacheTest_430, EvictionOnCapacityExceeded_430) {
  // Insert entries with charge=1, exceeding capacity of 100
  for (int i = 0; i < 200; i++) {
    Insert(i, i + 1000);
  }

  // Some early entries should have been evicted
  int evicted = 0;
  int present = 0;
  for (int i = 0; i < 200; i++) {
    if (Lookup(i) == -1) {
      evicted++;
    } else {
      present++;
    }
  }

  // With capacity 100 and charge 1 each, roughly 100 should remain
  EXPECT_GT(evicted, 0);
  EXPECT_LE(present, 100);
}

TEST_F(CacheTest_430, LRUEvictionOrder_430) {
  // Fill cache to capacity
  for (int i = 0; i < 100; i++) {
    Insert(i, i + 1000);
  }

  // Access some entries to make them recently used
  for (int i = 0; i < 50; i++) {
    Lookup(i);
  }

  // Insert more to trigger eviction
  for (int i = 100; i < 150; i++) {
    Insert(i, i + 1000);
  }

  // Recently accessed entries (0-49) should still be present
  int recently_used_present = 0;
  for (int i = 0; i < 50; i++) {
    if (Lookup(i) != -1) {
      recently_used_present++;
    }
  }

  // Not recently accessed entries (50-99) should have some evicted
  int not_recently_used_present = 0;
  for (int i = 50; i < 100; i++) {
    if (Lookup(i) != -1) {
      not_recently_used_present++;
    }
  }

  // We expect that recently used entries survive better than non-recently used
  EXPECT_GT(recently_used_present, not_recently_used_present);
}

TEST_F(CacheTest_430, DeleterCalledOnEviction_430) {
  ResetDeleters();
  Insert(1, 42);
  
  // Force eviction by filling cache
  for (int i = 1000; i < 1200; i++) {
    Insert(i, i);
  }

  // Check that the deleter was called for key 1
  bool found = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 1 && deleted_values[i] == 42) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(CacheTest_430, DeleterCalledOnErase_430) {
  ResetDeleters();
  Insert(5, 55);
  Erase(5);

  bool found = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 5 && deleted_values[i] == 55) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(CacheTest_430, DeleterCalledOnOverwrite_430) {
  ResetDeleters();
  Insert(7, 70);
  Insert(7, 77);

  // The old value (70) should have been deleted
  bool found_old = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 7 && deleted_values[i] == 70) {
      found_old = true;
      break;
    }
  }
  EXPECT_TRUE(found_old);
}

TEST_F(CacheTest_430, ReleaseHandle_430) {
  Cache::Handle* h = Insert(1, 100);
  ASSERT_NE(h, nullptr);
  cache_->Release(h);

  // After release, we should still be able to look it up
  EXPECT_EQ(100, Lookup(1));
}

TEST_F(CacheTest_430, HandleHeldPreventsDelete_430) {
  ResetDeleters();

  Cache::Handle* h = cache_->Insert(EncodeKey(1), reinterpret_cast<void*>(100),
                                     1, &Deleter);
  // Erase while handle is held
  Erase(1);

  // Lookup should fail (removed from cache)
  EXPECT_EQ(-1, Lookup(1));

  // But deleter should not have been called yet because handle is still held
  bool found = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 1 && deleted_values[i] == 100) {
      found = true;
      break;
    }
  }
  EXPECT_FALSE(found);

  // Now release the handle
  cache_->Release(h);

  // Deleter should have been called now
  found = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 1 && deleted_values[i] == 100) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(CacheTest_430, ZeroCapacityCache_430) {
  delete cache_;
  cache_ = NewLRUCache(0);

  Insert(1, 100);
  // With zero capacity, entries may be immediately evicted
  // Just verify it doesn't crash
  Lookup(1);
}

TEST_F(CacheTest_430, LargeChargeEntry_430) {
  // Insert an entry with charge larger than capacity
  Insert(1, 100, 200);
  // The behavior is implementation-defined; just verify no crash
  // It may or may not be present
  Lookup(1);
}

TEST_F(CacheTest_430, NewId_430) {
  uint64_t id1 = cache_->NewId();
  uint64_t id2 = cache_->NewId();
  EXPECT_NE(id1, id2);
}

TEST_F(CacheTest_430, Prune_430) {
  Insert(1, 100);
  Insert(2, 200);

  // Prune should remove entries not in active use
  cache_->Prune();

  // After prune, entries not held by handles may be removed
  // This is implementation-defined behavior; just ensure no crash
}

TEST_F(CacheTest_430, TotalCharge_430) {
  EXPECT_EQ(0, cache_->TotalCharge());

  Insert(1, 100, 10);
  EXPECT_GE(cache_->TotalCharge(), 10);

  Insert(2, 200, 20);
  EXPECT_GE(cache_->TotalCharge(), 20);
}

TEST_F(CacheTest_430, ManyEntries_430) {
  // Stress test with many insertions
  for (int i = 0; i < 10000; i++) {
    Insert(i, i + 1);
  }

  // Most recent entries should be findable
  for (int i = 9900; i < 10000; i++) {
    EXPECT_EQ(i + 1, Lookup(i));
  }
}

TEST_F(CacheTest_430, InsertReturnsNonNullHandle_430) {
  Cache::Handle* h = Insert(42, 420);
  ASSERT_NE(h, nullptr);
  cache_->Release(h);
}

TEST_F(CacheTest_430, ValueFromHandle_430) {
  Cache::Handle* h = Insert(10, 999);
  ASSERT_NE(h, nullptr);
  EXPECT_EQ(999, reinterpret_cast<uintptr_t>(cache_->Value(h)));
  cache_->Release(h);
}

TEST_F(CacheTest_430, MultipleNewIdCalls_430) {
  std::vector<uint64_t> ids;
  for (int i = 0; i < 100; i++) {
    ids.push_back(cache_->NewId());
  }
  // All IDs should be unique
  for (size_t i = 0; i < ids.size(); i++) {
    for (size_t j = i + 1; j < ids.size(); j++) {
      EXPECT_NE(ids[i], ids[j]);
    }
  }
}

TEST_F(CacheTest_430, PruneRemovesUnpinnedEntries_430) {
  Insert(1, 100);
  Insert(2, 200);

  // Hold a handle to entry 2
  Cache::Handle* h = cache_->Lookup(EncodeKey(2));
  ASSERT_NE(h, nullptr);

  cache_->Prune();

  // Entry 1 (unpinned) might be removed
  // Entry 2 (pinned) should still be accessible via the handle
  EXPECT_EQ(200, reinterpret_cast<uintptr_t>(cache_->Value(h)));

  cache_->Release(h);
}

TEST_F(CacheTest_430, DeleterCalledOnCacheDestruction_430) {
  ResetDeleters();

  Cache* temp_cache = NewLRUCache(100);
  temp_cache->Insert(EncodeKey(42), reinterpret_cast<void*>(4200), 1, &Deleter);

  delete temp_cache;

  // Deleter should have been called
  bool found = false;
  for (int i = 0; i < deleter_count; i++) {
    if (deleted_keys[i] == 42 && deleted_values[i] == 4200) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

}  // namespace leveldb
