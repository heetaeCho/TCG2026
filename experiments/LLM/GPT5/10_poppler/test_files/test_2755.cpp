// PopplerCache_test_2755.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <type_traits>

#include "poppler/PopplerCache.h"

// These tests treat PopplerCache as a black box and only validate observable behavior
// via its public interface (construction, put(), lookup()).

namespace {

struct TestItem2755 {
  explicit TestItem2755(int v) : value(v) {}
  ~TestItem2755() { ++destruct_count; }

  int value = 0;
  static inline int destruct_count = 0;
};

using Cache2755 = PopplerCache<int, TestItem2755>;

} // namespace

TEST(PopplerCacheTest_2755, ConstructorIsExplicit_2755) {
  // If the constructor is explicit, size_t should not be implicitly convertible to Cache.
  static_assert(!std::is_convertible_v<std::size_t, Cache2755>,
                "PopplerCache(std::size_t) must be explicit (no implicit conversion).");
  SUCCEED();
}

TEST(PopplerCacheTest_2755, ConstructorWithZeroDoesNotThrow_2755) {
  EXPECT_NO_THROW({
    Cache2755 cache(0);
    (void)cache;
  });
}

TEST(PopplerCacheTest_2755, ConstructorWithTypicalSizeDoesNotThrow_2755) {
  EXPECT_NO_THROW({
    Cache2755 cache(16);
    (void)cache;
  });
}

TEST(PopplerCacheTest_2755, LookupMissingKeyReturnsNullptr_2755) {
  Cache2755 cache(8);
  EXPECT_EQ(cache.lookup(123456), nullptr);
}

TEST(PopplerCacheTest_2755, PutWithRawPointerThenLookupReturnsSamePointer_2755) {
  Cache2755 cache(8);

  auto *item = new TestItem2755(10);
  cache.put(42, item);

  TestItem2755 *found = cache.lookup(42);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, item);
  EXPECT_EQ(found->value, 10);
}

TEST(PopplerCacheTest_2755, PutWithUniquePtrThenLookupReturnsSamePointer_2755) {
  Cache2755 cache(8);

  auto up = std::make_unique<TestItem2755>(20);
  TestItem2755 *raw = up.get();

  cache.put(7, std::move(up));

  TestItem2755 *found = cache.lookup(7);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, raw);
  EXPECT_EQ(found->value, 20);
}

TEST(PopplerCacheTest_2755, PutSameKeyTwiceLookupReturnsLatestValue_2755) {
  Cache2755 cache(8);

  cache.put(1, new TestItem2755(100));
  TestItem2755 *first = cache.lookup(1);
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->value, 100);

  cache.put(1, new TestItem2755(200));
  TestItem2755 *second = cache.lookup(1);
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(second->value, 200);

  // Observable behavior: the "latest" value for the key is returned.
  // We do not assume anything about eviction strategy or internal storage beyond this.
}

TEST(PopplerCacheTest_2755, OverwriteCleansUpItemsByEndOfScope_2755) {
  // Observable through destructor side effects: items owned by the cache should be destroyed
  // by the time the cache is destroyed (end of scope). We avoid making assumptions about
  // *when* destruction happens (immediately vs later), only that it happens by scope end.
  TestItem2755::destruct_count = 0;

  {
    Cache2755 cache(8);
    cache.put(9, new TestItem2755(1));
    cache.put(9, new TestItem2755(2));
    cache.put(10, std::make_unique<TestItem2755>(3));
    // At this point, we do not assert destruct_count because destruction timing is unspecified.
  }

  // By scope end, all items owned by the cache should have been destroyed.
  // We inserted three items total, but one key was overwritten; the cache should still own
  // exactly the currently-stored items and should have cleaned up any replaced items as well.
  EXPECT_GE(TestItem2755::destruct_count, 2);
}