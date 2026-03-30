// PopplerCache_lookup_test_252.cpp
// Unit tests for PopplerCache (TEST_ID: 252)

#include <gtest/gtest.h>

#include <memory>

#include "./TestProjects/poppler/poppler/PopplerCache.h"

// A small helper type whose lifetime is observable via destructor count.
struct CountingItem {
  static int dtorCount;
  int value;

  explicit CountingItem(int v) : value(v) {}
  ~CountingItem() { ++dtorCount; }

  CountingItem(const CountingItem&) = delete;
  CountingItem& operator=(const CountingItem&) = delete;
};

int CountingItem::dtorCount = 0;

class PopplerCacheTest_252 : public ::testing::Test {
protected:
  void SetUp() override { CountingItem::dtorCount = 0; }
  void TearDown() override { /* nothing */ }
};

TEST_F(PopplerCacheTest_252, EmptyCacheLookupReturnsNull_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);

  EXPECT_EQ(cache.lookup(1), nullptr);
  EXPECT_EQ(cache.lookup(0), nullptr);
  EXPECT_EQ(cache.lookup(-123), nullptr);
}

TEST_F(PopplerCacheTest_252, LookupMissingKeyReturnsNull_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);

  cache.put(1, std::make_unique<CountingItem>(10));
  cache.put(2, std::make_unique<CountingItem>(20));

  EXPECT_EQ(cache.lookup(3), nullptr);
  EXPECT_EQ(cache.lookup(-1), nullptr);
}

TEST_F(PopplerCacheTest_252, PutWithRawPointerThenLookupReturnsSamePointer_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);

  auto* raw = new CountingItem(123);
  cache.put(7, raw);

  CountingItem* lookedUp = cache.lookup(7);
  ASSERT_NE(lookedUp, nullptr);
  EXPECT_EQ(lookedUp, raw);
  EXPECT_EQ(lookedUp->value, 123);

  // Repeated lookups should keep returning the same stored item pointer.
  EXPECT_EQ(cache.lookup(7), raw);
}

TEST_F(PopplerCacheTest_252, PutWithUniquePtrThenLookupReturnsNonNullAndMatchesValue_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);

  cache.put(42, std::make_unique<CountingItem>(900));

  CountingItem* lookedUp = cache.lookup(42);
  ASSERT_NE(lookedUp, nullptr);
  EXPECT_EQ(lookedUp->value, 900);
}

TEST_F(PopplerCacheTest_252, PutSameKeyTwiceLookupReturnsMostRecentlyPutItem_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);

  auto* first = new CountingItem(1);
  cache.put(5, first);
  ASSERT_EQ(cache.lookup(5), first);
  EXPECT_EQ(cache.lookup(5)->value, 1);

  auto* second = new CountingItem(2);
  cache.put(5, second);

  CountingItem* lookedUp = cache.lookup(5);
  ASSERT_NE(lookedUp, nullptr);
  EXPECT_EQ(lookedUp, second);
  EXPECT_EQ(lookedUp->value, 2);
}

TEST_F(PopplerCacheTest_252, CacheSizeOneSecondPutMakesFirstKeyUnavailable_252) {
  PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/1);

  cache.put(1, std::make_unique<CountingItem>(111));
  ASSERT_NE(cache.lookup(1), nullptr);

  cache.put(2, std::make_unique<CountingItem>(222));

  // With a size-1 cache, only one key should remain available.
  EXPECT_EQ(cache.lookup(1), nullptr);
  CountingItem* v2 = cache.lookup(2);
  ASSERT_NE(v2, nullptr);
  EXPECT_EQ(v2->value, 222);
}

TEST_F(PopplerCacheTest_252, ItemsAreDestroyedWhenCacheGoesOutOfScope_252) {
  EXPECT_EQ(CountingItem::dtorCount, 0);

  {
    PopplerCache<int, CountingItem> cache(/*cacheSizeA=*/4);
    cache.put(1, std::make_unique<CountingItem>(10));
    cache.put(2, std::make_unique<CountingItem>(20));
    cache.put(3, std::make_unique<CountingItem>(30));

    // Still alive while cache is in scope.
    EXPECT_EQ(CountingItem::dtorCount, 0);
  }

  // All stored items should be destroyed when the cache is destroyed.
  EXPECT_EQ(CountingItem::dtorCount, 3);
}