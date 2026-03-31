#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PopplerCache.h"

// Test fixture for PopplerCache tests
class PopplerCacheTest_1240 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created cache returns nullptr for any lookup
TEST_F(PopplerCacheTest_1240, LookupOnEmptyCacheReturnsNull_1240)
{
    PopplerCache<int, std::string> cache(5);
    EXPECT_EQ(cache.lookup(0), nullptr);
    EXPECT_EQ(cache.lookup(1), nullptr);
    EXPECT_EQ(cache.lookup(42), nullptr);
}

// Test that putting an item and looking it up returns the correct item
TEST_F(PopplerCacheTest_1240, PutAndLookupSingleItem_1240)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("hello"));
    std::string *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "hello");
}

// Test that looking up a key that was never inserted returns nullptr
TEST_F(PopplerCacheTest_1240, LookupNonExistentKeyReturnsNull_1240)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("hello"));
    EXPECT_EQ(cache.lookup(2), nullptr);
}

// Test putting multiple items and looking them all up
TEST_F(PopplerCacheTest_1240, PutMultipleItemsAndLookup_1240)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    std::string *r1 = cache.lookup(1);
    std::string *r2 = cache.lookup(2);
    std::string *r3 = cache.lookup(3);

    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(*r1, "one");
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(*r2, "two");
    ASSERT_NE(r3, nullptr);
    EXPECT_EQ(*r3, "three");
}

// Test that cache evicts the oldest item when full
TEST_F(PopplerCacheTest_1240, EvictsOldestItemWhenFull_1240)
{
    PopplerCache<int, std::string> cache(3);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    // Cache is full (size 3), inserting a 4th should evict the oldest (key=1)
    cache.put(4, std::make_unique<std::string>("four"));

    EXPECT_EQ(cache.lookup(1), nullptr);  // evicted

    std::string *r2 = cache.lookup(2);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(*r2, "two");

    std::string *r3 = cache.lookup(3);
    ASSERT_NE(r3, nullptr);
    EXPECT_EQ(*r3, "three");

    std::string *r4 = cache.lookup(4);
    ASSERT_NE(r4, nullptr);
    EXPECT_EQ(*r4, "four");
}

// Test cache of size 1
TEST_F(PopplerCacheTest_1240, CacheSizeOne_1240)
{
    PopplerCache<int, std::string> cache(1);
    cache.put(1, std::make_unique<std::string>("one"));

    std::string *r1 = cache.lookup(1);
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(*r1, "one");

    // Inserting a second item should evict the first
    cache.put(2, std::make_unique<std::string>("two"));
    EXPECT_EQ(cache.lookup(1), nullptr);

    std::string *r2 = cache.lookup(2);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(*r2, "two");
}

// Test that eviction continues to work correctly with many insertions
TEST_F(PopplerCacheTest_1240, EvictionWithManyInsertions_1240)
{
    PopplerCache<int, std::string> cache(3);

    for (int i = 0; i < 10; i++) {
        cache.put(i, std::make_unique<std::string>(std::to_string(i)));
    }

    // Only the last 3 items should remain: 7, 8, 9
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(cache.lookup(i), nullptr) << "Key " << i << " should have been evicted";
    }

    for (int i = 7; i < 10; i++) {
        std::string *r = cache.lookup(i);
        ASSERT_NE(r, nullptr) << "Key " << i << " should be in cache";
        EXPECT_EQ(*r, std::to_string(i));
    }
}

// Test with string keys
TEST_F(PopplerCacheTest_1240, StringKeysWork_1240)
{
    PopplerCache<std::string, int> cache(3);
    cache.put("alpha", std::make_unique<int>(1));
    cache.put("beta", std::make_unique<int>(2));
    cache.put("gamma", std::make_unique<int>(3));

    int *ra = cache.lookup("alpha");
    ASSERT_NE(ra, nullptr);
    EXPECT_EQ(*ra, 1);

    int *rb = cache.lookup("beta");
    ASSERT_NE(rb, nullptr);
    EXPECT_EQ(*rb, 2);

    int *rg = cache.lookup("gamma");
    ASSERT_NE(rg, nullptr);
    EXPECT_EQ(*rg, 3);

    EXPECT_EQ(cache.lookup("delta"), nullptr);
}

// Test that putting the same key again updates the value (or adds duplicate)
TEST_F(PopplerCacheTest_1240, PutSameKeyUpdatesOrAdds_1240)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("first"));
    cache.put(1, std::make_unique<std::string>("second"));

    std::string *r = cache.lookup(1);
    ASSERT_NE(r, nullptr);
    // The most recent put should be found first
    EXPECT_EQ(*r, "second");
}

// Test that cache with larger capacity holds all items
TEST_F(PopplerCacheTest_1240, LargerCacheHoldsAllItems_1240)
{
    PopplerCache<int, int> cache(100);
    for (int i = 0; i < 100; i++) {
        cache.put(i, std::make_unique<int>(i * 10));
    }

    for (int i = 0; i < 100; i++) {
        int *r = cache.lookup(i);
        ASSERT_NE(r, nullptr) << "Key " << i << " should be in cache";
        EXPECT_EQ(*r, i * 10);
    }
}

// Test that after filling the cache, the capacity boundary is respected
TEST_F(PopplerCacheTest_1240, CapacityBoundaryExact_1240)
{
    PopplerCache<int, int> cache(5);

    // Fill exactly to capacity
    for (int i = 0; i < 5; i++) {
        cache.put(i, std::make_unique<int>(i));
    }

    // All 5 should be present
    for (int i = 0; i < 5; i++) {
        EXPECT_NE(cache.lookup(i), nullptr) << "Key " << i << " should be present";
    }

    // Adding one more should evict the oldest (key 0)
    cache.put(5, std::make_unique<int>(5));
    EXPECT_EQ(cache.lookup(0), nullptr);
    EXPECT_NE(cache.lookup(5), nullptr);

    // Keys 1-5 should still be present
    for (int i = 1; i <= 5; i++) {
        EXPECT_NE(cache.lookup(i), nullptr) << "Key " << i << " should be present";
    }
}

// Test with zero key
TEST_F(PopplerCacheTest_1240, ZeroKeyWorks_1240)
{
    PopplerCache<int, std::string> cache(3);
    cache.put(0, std::make_unique<std::string>("zero"));

    std::string *r = cache.lookup(0);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(*r, "zero");
}

// Test with negative keys
TEST_F(PopplerCacheTest_1240, NegativeKeysWork_1240)
{
    PopplerCache<int, std::string> cache(3);
    cache.put(-1, std::make_unique<std::string>("negative one"));
    cache.put(-2, std::make_unique<std::string>("negative two"));

    std::string *r1 = cache.lookup(-1);
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(*r1, "negative one");

    std::string *r2 = cache.lookup(-2);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(*r2, "negative two");
}

// Test that the returned pointer remains valid as long as the item is in cache
TEST_F(PopplerCacheTest_1240, PointerStabilityWhileInCache_1240)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("stable"));

    std::string *ptr1 = cache.lookup(1);

    // Add more items but don't evict key 1
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    std::string *ptr2 = cache.lookup(1);
    ASSERT_NE(ptr2, nullptr);
    EXPECT_EQ(*ptr2, "stable");
}
