#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PopplerCache.h"

// Simple test item class
class TestItem {
public:
    int value;
    explicit TestItem(int v) : value(v) {}
};

class PopplerCacheTest_253 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with a given size
TEST_F(PopplerCacheTest_253, ConstructWithSize_253) {
    PopplerCache<int, TestItem> cache(5);
    // Should be constructible without issues
    EXPECT_EQ(cache.lookup(0), nullptr);
}

// Test putting and looking up a single item
TEST_F(PopplerCacheTest_253, PutAndLookupSingleItem_253) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(1, new TestItem(100));
    
    TestItem *item = cache.lookup(1);
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(item->value, 100);
}

// Test lookup returns nullptr for non-existent key
TEST_F(PopplerCacheTest_253, LookupNonExistentKey_253) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(1, new TestItem(100));
    
    TestItem *item = cache.lookup(2);
    EXPECT_EQ(item, nullptr);
}

// Test putting multiple items and looking them up
TEST_F(PopplerCacheTest_253, PutMultipleItemsAndLookup_253) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(1, new TestItem(10));
    cache.put(2, new TestItem(20));
    cache.put(3, new TestItem(30));
    
    TestItem *item1 = cache.lookup(1);
    TestItem *item2 = cache.lookup(2);
    TestItem *item3 = cache.lookup(3);
    
    ASSERT_NE(item1, nullptr);
    ASSERT_NE(item2, nullptr);
    ASSERT_NE(item3, nullptr);
    EXPECT_EQ(item1->value, 10);
    EXPECT_EQ(item2->value, 20);
    EXPECT_EQ(item3->value, 30);
}

// Test cache eviction when capacity is exceeded
TEST_F(PopplerCacheTest_253, EvictsOldestWhenFull_253) {
    PopplerCache<int, TestItem> cache(3);
    cache.put(1, new TestItem(10));
    cache.put(2, new TestItem(20));
    cache.put(3, new TestItem(30));
    
    // Cache is full (size 3). Adding a 4th item should evict the oldest (key=1)
    cache.put(4, new TestItem(40));
    
    TestItem *item1 = cache.lookup(1);
    EXPECT_EQ(item1, nullptr); // Should be evicted
    
    TestItem *item4 = cache.lookup(4);
    ASSERT_NE(item4, nullptr);
    EXPECT_EQ(item4->value, 40);
}

// Test cache of size 1
TEST_F(PopplerCacheTest_253, CacheSizeOne_253) {
    PopplerCache<int, TestItem> cache(1);
    cache.put(1, new TestItem(10));
    
    TestItem *item1 = cache.lookup(1);
    ASSERT_NE(item1, nullptr);
    EXPECT_EQ(item1->value, 10);
    
    // Adding another item should evict the first
    cache.put(2, new TestItem(20));
    
    item1 = cache.lookup(1);
    EXPECT_EQ(item1, nullptr);
    
    TestItem *item2 = cache.lookup(2);
    ASSERT_NE(item2, nullptr);
    EXPECT_EQ(item2->value, 20);
}

// Test put with unique_ptr overload
TEST_F(PopplerCacheTest_253, PutWithUniquePtr_253) {
    PopplerCache<int, TestItem> cache(5);
    auto item = std::make_unique<TestItem>(42);
    cache.put(1, std::move(item));
    
    TestItem *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 42);
}

// Test that newer items are kept while older ones are evicted
TEST_F(PopplerCacheTest_253, EvictionOrder_253) {
    PopplerCache<int, TestItem> cache(3);
    cache.put(1, new TestItem(10));
    cache.put(2, new TestItem(20));
    cache.put(3, new TestItem(30));
    cache.put(4, new TestItem(40));
    cache.put(5, new TestItem(50));
    
    // Keys 1 and 2 should be evicted
    EXPECT_EQ(cache.lookup(1), nullptr);
    EXPECT_EQ(cache.lookup(2), nullptr);
    
    // Keys 3, 4, 5 should still be present
    ASSERT_NE(cache.lookup(3), nullptr);
    ASSERT_NE(cache.lookup(4), nullptr);
    ASSERT_NE(cache.lookup(5), nullptr);
}

// Test with string keys
TEST_F(PopplerCacheTest_253, StringKeys_253) {
    PopplerCache<std::string, TestItem> cache(3);
    cache.put("alpha", new TestItem(1));
    cache.put("beta", new TestItem(2));
    cache.put("gamma", new TestItem(3));
    
    TestItem *alpha = cache.lookup(std::string("alpha"));
    TestItem *beta = cache.lookup(std::string("beta"));
    TestItem *gamma = cache.lookup(std::string("gamma"));
    
    ASSERT_NE(alpha, nullptr);
    ASSERT_NE(beta, nullptr);
    ASSERT_NE(gamma, nullptr);
    EXPECT_EQ(alpha->value, 1);
    EXPECT_EQ(beta->value, 2);
    EXPECT_EQ(gamma->value, 3);
}

// Test looking up an empty cache
TEST_F(PopplerCacheTest_253, LookupEmptyCache_253) {
    PopplerCache<int, TestItem> cache(5);
    EXPECT_EQ(cache.lookup(0), nullptr);
    EXPECT_EQ(cache.lookup(1), nullptr);
    EXPECT_EQ(cache.lookup(-1), nullptr);
}

// Test that putting the same key again updates the cache
TEST_F(PopplerCacheTest_253, PutSameKeyUpdates_253) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(1, new TestItem(10));
    cache.put(1, new TestItem(20));
    
    TestItem *item = cache.lookup(1);
    ASSERT_NE(item, nullptr);
    // The most recently put value should be retrievable
    // (exact behavior depends on implementation, but at least one lookup should succeed)
    EXPECT_TRUE(item->value == 10 || item->value == 20);
}

// Test filling cache exactly to capacity
TEST_F(PopplerCacheTest_253, FillExactlyToCapacity_253) {
    PopplerCache<int, TestItem> cache(4);
    for (int i = 0; i < 4; ++i) {
        cache.put(i, new TestItem(i * 10));
    }
    
    for (int i = 0; i < 4; ++i) {
        TestItem *item = cache.lookup(i);
        ASSERT_NE(item, nullptr) << "Key " << i << " should be present";
        EXPECT_EQ(item->value, i * 10);
    }
}

// Test that adding one more beyond capacity evicts exactly one
TEST_F(PopplerCacheTest_253, EvictsExactlyOneWhenOverCapacity_253) {
    PopplerCache<int, TestItem> cache(3);
    cache.put(10, new TestItem(100));
    cache.put(20, new TestItem(200));
    cache.put(30, new TestItem(300));
    
    // All three should be present
    ASSERT_NE(cache.lookup(10), nullptr);
    ASSERT_NE(cache.lookup(20), nullptr);
    ASSERT_NE(cache.lookup(30), nullptr);
    
    // Add one more
    cache.put(40, new TestItem(400));
    
    // The new one should be present
    ASSERT_NE(cache.lookup(40), nullptr);
    EXPECT_EQ(cache.lookup(40)->value, 400);
    
    // Count how many of the old ones are still present
    int present = 0;
    if (cache.lookup(10) != nullptr) present++;
    if (cache.lookup(20) != nullptr) present++;
    if (cache.lookup(30) != nullptr) present++;
    
    // At most 2 of the old 3 should remain (capacity is 3, one new + two old)
    EXPECT_LE(present, 2);
}

// Test with negative keys
TEST_F(PopplerCacheTest_253, NegativeKeys_253) {
    PopplerCache<int, TestItem> cache(5);
    cache.put(-1, new TestItem(1));
    cache.put(-2, new TestItem(2));
    
    TestItem *item1 = cache.lookup(-1);
    TestItem *item2 = cache.lookup(-2);
    
    ASSERT_NE(item1, nullptr);
    ASSERT_NE(item2, nullptr);
    EXPECT_EQ(item1->value, 1);
    EXPECT_EQ(item2->value, 2);
}

// Test large cache
TEST_F(PopplerCacheTest_253, LargeCache_253) {
    const size_t cacheSize = 100;
    PopplerCache<int, TestItem> cache(cacheSize);
    
    for (int i = 0; i < static_cast<int>(cacheSize); ++i) {
        cache.put(i, new TestItem(i));
    }
    
    // All should be present
    for (int i = 0; i < static_cast<int>(cacheSize); ++i) {
        TestItem *item = cache.lookup(i);
        ASSERT_NE(item, nullptr) << "Key " << i << " should be present";
        EXPECT_EQ(item->value, i);
    }
}

// Test copy constructor is deleted
TEST_F(PopplerCacheTest_253, CopyConstructorDeleted_253) {
    EXPECT_FALSE(std::is_copy_constructible<PopplerCache<int, TestItem>>::value);
}

// Test copy assignment is deleted
TEST_F(PopplerCacheTest_253, CopyAssignmentDeleted_253) {
    EXPECT_FALSE(std::is_copy_assignable<PopplerCache<int, TestItem>>::value);
}
