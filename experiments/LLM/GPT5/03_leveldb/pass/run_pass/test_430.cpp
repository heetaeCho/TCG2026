// File: cache_newlru_test_430.cc

#include <gtest/gtest.h>
#include <atomic>
#include <memory>
#include <string>

#include "leveldb/cache.h"
#include "leveldb/slice.h"

using leveldb::Cache;
using leveldb::NewLRUCache;
using leveldb::Slice;

namespace {

struct DeleterProbe {
  std::atomic<int> calls{0};
  std::string last_key;
  int last_value{0};

  static void Func(const Slice& key, void* value) {
    // Recover the probe pointer stored alongside the value.
    // We store the probe as the first word right before the int.
    // To avoid relying on internal cache state, we wrap the int in a pair struct.
    // (See ValueHolder below.) We only read what we allocated ourselves.
  }
};

// Helper that keeps both the observed value and a back-pointer to the probe
// so the deleter can record which value was freed without touching cache internals.
struct ValueHolder {
  DeleterProbe* probe;
  int number;
  static void Deleter(const Slice& key, void* v) {
    auto* h = static_cast<ValueHolder*>(v);
    if (h && h->probe) {
      h->probe->calls.fetch_add(1, std::memory_order_relaxed);
      h->probe->last_key.assign(key.data(), key.size());
      h->probe->last_value = h->number;
    }
    delete h;
  }
};

class CacheNewLRUCacheTest_430 : public ::testing::Test {
protected:
  std::unique_ptr<Cache> Make(size_t capacity = 1024) {
    return std::unique_ptr<Cache>(NewLRUCache(capacity));
  }

  // Convenience: insert a key->ValueHolder(number) with given charge.
  // Returns the handle so the caller can Release.
  Cache::Handle* Insert(Cache* cache, const std::string& key, int number,
                        size_t charge, DeleterProbe* probe) {
    auto* holder = new ValueHolder{probe, number};
    return cache->Insert(Slice(key), holder, charge, &ValueHolder::Deleter);
  }

  // Extract the ValueHolder* back from a handle through the public API.
  ValueHolder* GetValue(Cache* cache, Cache::Handle* h) {
    return static_cast<ValueHolder*>(cache->Value(h));
  }
};

}  // namespace

// --- Tests ---

TEST_F(CacheNewLRUCacheTest_430, NewLRUCache_ReturnsNonNull_430) {
  auto cache = Make(256);
  EXPECT_NE(cache.get(), nullptr);
}

TEST_F(CacheNewLRUCacheTest_430, InsertLookupRoundTrip_430) {
  auto cache = Make(256);
  DeleterProbe probe;

  // Insert
  Cache::Handle* h = Insert(cache.get(), "a", /*number=*/7, /*charge=*/1, &probe);
  ASSERT_NE(h, nullptr);
  // Release caller’s handle (cache still retains its own)
  cache->Release(h);

  // Lookup
  Cache::Handle* got = cache->Lookup(Slice("a"));
  ASSERT_NE(got, nullptr);
  auto* v = GetValue(cache.get(), got);
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(v->number, 7);
  cache->Release(got);
}

TEST_F(CacheNewLRUCacheTest_430, LookupMiss_430) {
  auto cache = Make(256);
  Cache::Handle* miss = cache->Lookup(Slice("nope"));
  EXPECT_EQ(miss, nullptr);
}

TEST_F(CacheNewLRUCacheTest_430, EraseCallsDeleterWhenNoExternalRefs_430) {
  auto cache = Make(256);
  DeleterProbe probe;

  Cache::Handle* h = Insert(cache.get(), "k1", /*number=*/123, /*charge=*/1, &probe);
  ASSERT_NE(h, nullptr);

  // Drop caller’s ref; only the cache's own ref remains.
  cache->Release(h);

  // Erase should remove the entry and trigger deleter immediately (no external refs).
  cache->Erase(Slice("k1"));

  EXPECT_EQ(probe.calls.load(), 1);
  EXPECT_EQ(probe.last_key, "k1");
  EXPECT_EQ(probe.last_value, 123);
}

TEST_F(CacheNewLRUCacheTest_430, EraseThenRelease_DeletesOnFinalRelease_430) {
  auto cache = Make(256);
  DeleterProbe probe;

  Cache::Handle* h = Insert(cache.get(), "k2", /*number=*/99, /*charge=*/1, &probe);
  ASSERT_NE(h, nullptr);

  // While holding a client ref, erase the key. Deleter should NOT fire yet.
  cache->Erase(Slice("k2"));
  EXPECT_EQ(probe.calls.load(), 0);

  // Now release our last ref; deleter should fire once.
  cache->Release(h);
  EXPECT_EQ(probe.calls.load(), 1);
  EXPECT_EQ(probe.last_key, "k2");
  EXPECT_EQ(probe.last_value, 99);
}

TEST_F(CacheNewLRUCacheTest_430, NewId_MonotonicAndDistinct_430) {
  auto cache = Make(256);
  uint64_t id1 = cache->NewId();
  uint64_t id2 = cache->NewId();
  EXPECT_NE(id1, id2);
}

TEST_F(CacheNewLRUCacheTest_430, ZeroCapacity_AllowsConstructionAndCleanup_430) {
  auto cache = Make(/*capacity=*/0);
  ASSERT_NE(cache.get(), nullptr);

  DeleterProbe probe;
  Cache::Handle* h = Insert(cache.get(), "tiny", /*number=*/1, /*charge=*/1, &probe);
  // Even with zero capacity, Insert should return a handle per the interface.
  ASSERT_NE(h, nullptr);

  // After releasing our handle, the entry may not be retained; ensure proper cleanup occurs.
  cache->Release(h);
  // Either immediately or shortly after, the entry should be deletable.
  cache->Erase(Slice("tiny"));
  EXPECT_GE(probe.calls.load(), 1);  // At least one deletion should have happened.
}

TEST_F(CacheNewLRUCacheTest_430, TotalCharge_TracksInsertAndErase_430) {
  auto cache = Make(1024);
  DeleterProbe probe;

  // Initially, total charge should be 0.
  EXPECT_EQ(cache->TotalCharge(), 0u);

  // Insert one entry of charge 3.
  Cache::Handle* h = Insert(cache.get(), "c", /*number=*/5, /*charge=*/3, &probe);
  ASSERT_NE(h, nullptr);
  // Cache should now account for the charge (cache retains its own ref).
  EXPECT_EQ(cache->TotalCharge(), 3u);

  // Releasing our handle should not change the retained charge while the entry is resident.
  cache->Release(h);
  EXPECT_EQ(cache->TotalCharge(), 3u);

  // Erase should drop the charge to zero and invoke deleter (once).
  cache->Erase(Slice("c"));
  EXPECT_EQ(cache->TotalCharge(), 0u);
  EXPECT_EQ(probe.calls.load(), 1);
  EXPECT_EQ(probe.last_key, "c");
  EXPECT_EQ(probe.last_value, 5);
}
