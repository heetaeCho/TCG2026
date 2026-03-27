// TEST_ID: 253
//
// Unit tests for PopplerCache (template) based only on its public interface and
// observable behavior.
//
// File under test: ./TestProjects/poppler/poppler/PopplerCache.h

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Adjust include path if needed for your build layout.
#include "PopplerCache.h"

namespace {

struct TrackedItem {
  static int liveCount;
  static int destroyedCount;

  int value;

  explicit TrackedItem(int v) : value(v) { ++liveCount; }
  ~TrackedItem() {
    --liveCount;
    ++destroyedCount;
  }

  static void ResetCounters() {
    liveCount = 0;
    destroyedCount = 0;
  }
};

int TrackedItem::liveCount = 0;
int TrackedItem::destroyedCount = 0;

class PopplerCacheTest_253 : public ::testing::Test {
protected:
  void SetUp() override { TrackedItem::ResetCounters(); }
  void TearDown() override {
    // Ensure tests don't leak items in a way that hides cache ownership issues.
    EXPECT_EQ(TrackedItem::liveCount, 0);
  }
};

} // namespace

TEST_F(PopplerCacheTest_253, PutRawPointerThenLookupFindsItem_253) {
  PopplerCache<std::string, TrackedItem> cache(/*cacheSizeA=*/2);

  cache.put("k1", new TrackedItem(11));
  TrackedItem *found = cache.lookup("k1");

  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->value, 11);
}

TEST_F(PopplerCacheTest_253, PutUniquePtrMovesOwnershipAndLookupFindsItem_253) {
  PopplerCache<std::string, TrackedItem> cache(/*cacheSizeA=*/2);

  std::unique_ptr<TrackedItem> item = std::make_unique<TrackedItem>(42);
  TrackedItem *rawBeforeMove = item.get();
  ASSERT_NE(rawBeforeMove, nullptr);

  cache.put("k1", std::move(item));

  // Ownership should have been transferred into the cache.
  EXPECT_EQ(item, nullptr);

  TrackedItem *found = cache.lookup("k1");
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, rawBeforeMove);
  EXPECT_EQ(found->value, 42);
}

TEST_F(PopplerCacheTest_253, EvictsWhenCapacityExceeded_SizeOne_253) {
  {
    PopplerCache<std::string, TrackedItem> cache(/*cacheSizeA=*/1);

    cache.put("a", new TrackedItem(1));
    EXPECT_NE(cache.lookup("a"), nullptr);

    cache.put("b", new TrackedItem(2));
    EXPECT_NE(cache.lookup("b"), nullptr);

    // With capacity 1, only one key should remain discoverable.
    EXPECT_EQ(cache.lookup("a"), nullptr);

    // One item should have been destroyed due to eviction.
    EXPECT_EQ(TrackedItem::destroyedCount, 1);
    EXPECT_EQ(TrackedItem::liveCount, 1);
  }
  // Remaining cached item should be destroyed when cache is destroyed.
  EXPECT_EQ(TrackedItem::destroyedCount, 2);
  EXPECT_EQ(TrackedItem::liveCount, 0);
}

TEST_F(PopplerCacheTest_253, EvictionOrderMatchesRecentInsertions_SizeTwo_253) {
  {
    PopplerCache<std::string, TrackedItem> cache(/*cacheSizeA=*/2);

    cache.put("k1", new TrackedItem(100));
    cache.put("k2", new TrackedItem(200));

    // Both should be present initially.
    ASSERT_NE(cache.lookup("k1"), nullptr);
    ASSERT_NE(cache.lookup("k2"), nullptr);

    // Adding a third should evict exactly one entry.
    cache.put("k3", new TrackedItem(300));

    EXPECT_NE(cache.lookup("k2"), nullptr);
    EXPECT_NE(cache.lookup("k3"), nullptr);
    EXPECT_EQ(cache.lookup("k1"), nullptr);

    EXPECT_EQ(TrackedItem::destroyedCount, 1);
    EXPECT_EQ(TrackedItem::liveCount, 2);
  }
  EXPECT_EQ(TrackedItem::destroyedCount, 3);
  EXPECT_EQ(TrackedItem::liveCount, 0);
}

TEST_F(PopplerCacheTest_253, LookupMissingKeyReturnsNull_253) {
  PopplerCache<std::string, TrackedItem> cache(/*cacheSizeA=*/2);

  EXPECT_EQ(cache.lookup("does-not-exist"), nullptr);

  cache.put("exists", new TrackedItem(7));
  EXPECT_EQ(cache.lookup("still-missing"), nullptr);
  EXPECT_NE(cache.lookup("exists"), nullptr);
}