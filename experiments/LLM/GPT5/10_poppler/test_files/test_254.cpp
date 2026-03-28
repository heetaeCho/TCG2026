// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_poppler_cache_254.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "poppler/PopplerCache.h"

namespace {

struct TestItem {
  explicit TestItem(int v_) : v(v_) {}
  ~TestItem() { ++dtorCount; }

  int v;
  static int dtorCount;
};

int TestItem::dtorCount = 0;

template <typename CacheT>
void ResetDtorCount() {
  TestItem::dtorCount = 0;
  (void)sizeof(CacheT);
}

} // namespace

// Compile-time interface expectations (TEST_ID: 254)
static_assert(!std::is_copy_constructible_v<PopplerCache<int, TestItem>>,
              "PopplerCache should not be copy constructible");
static_assert(!std::is_copy_assignable_v<PopplerCache<int, TestItem>>,
              "PopplerCache should not be copy assignable");

TEST(PopplerCacheTest_254, LookupOnEmptyReturnsNull_254) {
  PopplerCache<int, TestItem> cache(/*cacheSizeA=*/2);

  EXPECT_EQ(cache.lookup(1), nullptr);
  EXPECT_EQ(cache.lookup(0), nullptr);
  EXPECT_EQ(cache.lookup(-123), nullptr);
}

TEST(PopplerCacheTest_254, PutUniquePtrThenLookupReturnsSameItem_254) {
  PopplerCache<int, TestItem> cache(/*cacheSizeA=*/2);

  cache.put(7, std::make_unique<TestItem>(42));

  TestItem* item = cache.lookup(7);
  ASSERT_NE(item, nullptr);
  EXPECT_EQ(item->v, 42);

  // Unrelated key should still miss.
  EXPECT_EQ(cache.lookup(8), nullptr);
}

TEST(PopplerCacheTest_254, PutBeyondCapacityEvictsOldestInsertedKey_254) {
  PopplerCache<int, TestItem> cache(/*cacheSizeA=*/2);

  cache.put(1, std::make_unique<TestItem>(100));
  cache.put(2, std::make_unique<TestItem>(200));

  ASSERT_NE(cache.lookup(1), nullptr);
  ASSERT_NE(cache.lookup(2), nullptr);

  // Exceed capacity: one entry must be evicted.
  cache.put(3, std::make_unique<TestItem>(300));

  TestItem* v3 = cache.lookup(3);
  ASSERT_NE(v3, nullptr);
  EXPECT_EQ(v3->v, 300);

  // Based on the observable behavior of the provided put() implementation:
  // the oldest entry is removed when capacity is exceeded.
  EXPECT_EQ(cache.lookup(1), nullptr);
  ASSERT_NE(cache.lookup(2), nullptr);
  EXPECT_EQ(cache.lookup(2)->v, 200);
}

TEST(PopplerCacheTest_254, EvictionDeletesItemAndCacheDestructionDeletesRemaining_254) {
  using CacheT = PopplerCache<int, TestItem>;
  ResetDtorCount<CacheT>();

  {
    CacheT cache(/*cacheSizeA=*/1);

    cache.put(10, std::make_unique<TestItem>(10));
    EXPECT_EQ(TestItem::dtorCount, 0);

    // This should evict key 10's item.
    cache.put(20, std::make_unique<TestItem>(20));
    EXPECT_EQ(TestItem::dtorCount, 1);

    // Ensure new item is present.
    TestItem* item = cache.lookup(20);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->v, 20);
  }

  // Remaining item should be destroyed when cache goes out of scope.
  EXPECT_EQ(TestItem::dtorCount, 2);
}

TEST(PopplerCacheTest_254, PutRawPointerTransfersOwnership_254) {
  using CacheT = PopplerCache<int, TestItem>;
  ResetDtorCount<CacheT>();

  {
    CacheT cache(/*cacheSizeA=*/1);

    auto* raw = new TestItem(123);
    cache.put(5, raw);

    TestItem* item = cache.lookup(5);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->v, 123);

    EXPECT_EQ(TestItem::dtorCount, 0);
  }

  // If ownership was transferred, the item should be deleted on cache destruction.
  EXPECT_EQ(TestItem::dtorCount, 1);
}