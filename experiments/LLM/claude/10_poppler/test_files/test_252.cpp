#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PopplerCache.h"

// Test fixture for PopplerCache tests
class PopplerCacheTest_252 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that lookup returns nullptr on an empty cache
TEST_F(PopplerCacheTest_252, LookupOnEmptyCacheReturnsNull_252)
{
    PopplerCache<int, std::string> cache(5);
    EXPECT_EQ(cache.lookup(42), nullptr);
}

// Test that after putting an item, lookup returns it
TEST_F(PopplerCacheTest_252, PutAndLookupSingleItem_252)
{
    PopplerCache<int, std::string> cache(5);
    auto item = std::make_unique<std::string>("hello");
    std::string *rawPtr = item.get();
    cache.put(1, std::move(item));
    EXPECT_EQ(cache.lookup(1), rawPtr);
}

// Test that lookup for a non-existent key returns nullptr
TEST_F(PopplerCacheTest_252, LookupNonExistentKeyReturnsNull_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("hello"));
    EXPECT_EQ(cache.lookup(2), nullptr);
}

// Test that multiple items can be stored and looked up
TEST_F(PopplerCacheTest_252, PutAndLookupMultipleItems_252)
{
    PopplerCache<int, std::string> cache(5);
    auto item1 = std::make_unique<std::string>("one");
    auto item2 = std::make_unique<std::string>("two");
    auto item3 = std::make_unique<std::string>("three");
    std::string *raw1 = item1.get();
    std::string *raw2 = item2.get();
    std::string *raw3 = item3.get();
    cache.put(1, std::move(item1));
    cache.put(2, std::move(item2));
    cache.put(3, std::move(item3));
    EXPECT_EQ(cache.lookup(1), raw1);
    EXPECT_EQ(cache.lookup(2), raw2);
    EXPECT_EQ(cache.lookup(3), raw3);
}

// Test that looking up the front element (most recently used) works without rotation
TEST_F(PopplerCacheTest_252, LookupFrontElementDirectly_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("first"));
    cache.put(2, std::make_unique<std::string>("second"));
    // After put(2, ...), key 2 should be the most recent (front)
    // Looking up key 2 should find it at front
    std::string *result = cache.lookup(2);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, "second");
}

// Test that looking up a non-front element rotates it to front
TEST_F(PopplerCacheTest_252, LookupNonFrontElementMovesToFront_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("first"));
    cache.put(2, std::make_unique<std::string>("second"));
    cache.put(3, std::make_unique<std::string>("third"));

    // Lookup key 1 (which should be at the back)
    std::string *result = cache.lookup(1);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, "first");

    // Now key 1 should be at front; looking it up again should still work
    result = cache.lookup(1);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, "first");
}

// Test cache with size 1
TEST_F(PopplerCacheTest_252, CacheSizeOne_252)
{
    PopplerCache<int, std::string> cache(1);
    cache.put(1, std::make_unique<std::string>("one"));
    EXPECT_NE(cache.lookup(1), nullptr);
    EXPECT_EQ(*cache.lookup(1), "one");

    // Adding another item should evict the first (if cache enforces size limit)
    cache.put(2, std::make_unique<std::string>("two"));
    // Key 2 should be found
    EXPECT_NE(cache.lookup(2), nullptr);
    EXPECT_EQ(*cache.lookup(2), "two");
}

// Test that the cache evicts items when full
TEST_F(PopplerCacheTest_252, CacheEvictsWhenFull_252)
{
    PopplerCache<int, std::string> cache(3);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    // All three should be present
    EXPECT_NE(cache.lookup(1), nullptr);
    EXPECT_NE(cache.lookup(2), nullptr);
    EXPECT_NE(cache.lookup(3), nullptr);

    // Adding a 4th item should evict the least recently used
    cache.put(4, std::make_unique<std::string>("four"));
    EXPECT_NE(cache.lookup(4), nullptr);
    EXPECT_EQ(*cache.lookup(4), "four");
}

// Test using raw pointer put interface
TEST_F(PopplerCacheTest_252, PutWithRawPointer_252)
{
    PopplerCache<int, std::string> cache(5);
    std::string *rawItem = new std::string("raw");
    cache.put(10, rawItem);
    EXPECT_EQ(cache.lookup(10), rawItem);
    EXPECT_EQ(*cache.lookup(10), "raw");
}

// Test with string keys
TEST_F(PopplerCacheTest_252, StringKeyLookup_252)
{
    PopplerCache<std::string, int> cache(5);
    cache.put("alpha", std::make_unique<int>(100));
    cache.put("beta", std::make_unique<int>(200));

    EXPECT_NE(cache.lookup("alpha"), nullptr);
    EXPECT_EQ(*cache.lookup("alpha"), 100);
    EXPECT_NE(cache.lookup("beta"), nullptr);
    EXPECT_EQ(*cache.lookup("beta"), 200);
    EXPECT_EQ(cache.lookup("gamma"), nullptr);
}

// Test repeated lookups maintain correct pointers
TEST_F(PopplerCacheTest_252, RepeatedLookupsSamePointer_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("persistent"));

    std::string *first = cache.lookup(1);
    std::string *second = cache.lookup(1);
    std::string *third = cache.lookup(1);

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_NE(first, nullptr);
}

// Test that LRU ordering is maintained through lookups
TEST_F(PopplerCacheTest_252, LRUOrderingAfterLookups_252)
{
    PopplerCache<int, std::string> cache(3);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    // Access key 1 to make it most recently used
    cache.lookup(1);

    // Now add key 4 - should evict the least recently used (key 2 or key 3)
    cache.put(4, std::make_unique<std::string>("four"));

    // Key 1 should still be present (was recently accessed)
    EXPECT_NE(cache.lookup(1), nullptr);
    // Key 4 should be present
    EXPECT_NE(cache.lookup(4), nullptr);
}

// Test replacing an existing key
TEST_F(PopplerCacheTest_252, PutDuplicateKey_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("original"));
    EXPECT_EQ(*cache.lookup(1), "original");

    cache.put(1, std::make_unique<std::string>("replaced"));
    // After putting with the same key, lookup should find something
    std::string *result = cache.lookup(1);
    EXPECT_NE(result, nullptr);
}

// Test with large number of items exceeding cache size
TEST_F(PopplerCacheTest_252, ManyItemsExceedCacheSize_252)
{
    PopplerCache<int, int> cache(3);
    for (int i = 0; i < 100; i++) {
        cache.put(i, std::make_unique<int>(i * 10));
    }
    // The last few items should be in the cache
    EXPECT_NE(cache.lookup(99), nullptr);
    EXPECT_EQ(*cache.lookup(99), 990);
}

// Test lookup with zero-value key
TEST_F(PopplerCacheTest_252, ZeroValueKey_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(0, std::make_unique<std::string>("zero"));
    EXPECT_NE(cache.lookup(0), nullptr);
    EXPECT_EQ(*cache.lookup(0), "zero");
}

// Test negative keys
TEST_F(PopplerCacheTest_252, NegativeKeys_252)
{
    PopplerCache<int, std::string> cache(5);
    cache.put(-1, std::make_unique<std::string>("neg_one"));
    cache.put(-2, std::make_unique<std::string>("neg_two"));

    EXPECT_NE(cache.lookup(-1), nullptr);
    EXPECT_EQ(*cache.lookup(-1), "neg_one");
    EXPECT_NE(cache.lookup(-2), nullptr);
    EXPECT_EQ(*cache.lookup(-2), "neg_two");
    EXPECT_EQ(cache.lookup(-3), nullptr);
}
