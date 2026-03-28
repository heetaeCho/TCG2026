#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PopplerCache.h"

// Test fixture for PopplerCache tests
class PopplerCacheTest_254 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created cache has no entries (lookup returns nullptr)
TEST_F(PopplerCacheTest_254, EmptyCacheLookupReturnsNull_254) {
    PopplerCache<int, std::string> cache(5);
    EXPECT_EQ(cache.lookup(0), nullptr);
    EXPECT_EQ(cache.lookup(1), nullptr);
    EXPECT_EQ(cache.lookup(-1), nullptr);
}

// Test that putting an item and looking it up returns the correct item
TEST_F(PopplerCacheTest_254, PutAndLookupSingleItem_254) {
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("hello"));
    std::string *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "hello");
}

// Test that looking up a non-existent key returns nullptr
TEST_F(PopplerCacheTest_254, LookupNonExistentKeyReturnsNull_254) {
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("hello"));
    EXPECT_EQ(cache.lookup(2), nullptr);
}

// Test that putting multiple items works correctly
TEST_F(PopplerCacheTest_254, PutMultipleItemsAndLookup_254) {
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    std::string *r1 = cache.lookup(1);
    std::string *r2 = cache.lookup(2);
    std::string *r3 = cache.lookup(3);

    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    ASSERT_NE(r3, nullptr);
    EXPECT_EQ(*r1, "one");
    EXPECT_EQ(*r2, "two");
    EXPECT_EQ(*r3, "three");
}

// Test that cache evicts the oldest entry when full
TEST_F(PopplerCacheTest_254, EvictsOldestWhenFull_254) {
    PopplerCache<int, std::string> cache(3);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    // Cache is full, adding a 4th element should evict key 1 (oldest)
    cache.put(4, std::make_unique<std::string>("four"));

    EXPECT_EQ(cache.lookup(1), nullptr); // evicted
    ASSERT_NE(cache.lookup(2), nullptr);
    EXPECT_EQ(*cache.lookup(2), "two");
    ASSERT_NE(cache.lookup(3), nullptr);
    EXPECT_EQ(*cache.lookup(3), "three");
    ASSERT_NE(cache.lookup(4), nullptr);
    EXPECT_EQ(*cache.lookup(4), "four");
}

// Test cache of size 1
TEST_F(PopplerCacheTest_254, CacheSizeOne_254) {
    PopplerCache<int, std::string> cache(1);
    cache.put(1, std::make_unique<std::string>("one"));
    ASSERT_NE(cache.lookup(1), nullptr);
    EXPECT_EQ(*cache.lookup(1), "one");

    // Adding another should evict the first
    cache.put(2, std::make_unique<std::string>("two"));
    EXPECT_EQ(cache.lookup(1), nullptr);
    ASSERT_NE(cache.lookup(2), nullptr);
    EXPECT_EQ(*cache.lookup(2), "two");
}

// Test that the most recently inserted items survive eviction
TEST_F(PopplerCacheTest_254, MostRecentSurvivesEviction_254) {
    PopplerCache<int, std::string> cache(2);
    cache.put(1, std::make_unique<std::string>("one"));
    cache.put(2, std::make_unique<std::string>("two"));
    cache.put(3, std::make_unique<std::string>("three"));

    // Key 1 should be evicted (oldest)
    EXPECT_EQ(cache.lookup(1), nullptr);
    ASSERT_NE(cache.lookup(2), nullptr);
    ASSERT_NE(cache.lookup(3), nullptr);

    cache.put(4, std::make_unique<std::string>("four"));
    // Key 2 should be evicted now
    EXPECT_EQ(cache.lookup(2), nullptr);
    ASSERT_NE(cache.lookup(3), nullptr);
    ASSERT_NE(cache.lookup(4), nullptr);
}

// Test with string keys
TEST_F(PopplerCacheTest_254, StringKeys_254) {
    PopplerCache<std::string, int> cache(3);
    cache.put("alpha", std::make_unique<int>(1));
    cache.put("beta", std::make_unique<int>(2));
    cache.put("gamma", std::make_unique<int>(3));

    ASSERT_NE(cache.lookup("alpha"), nullptr);
    EXPECT_EQ(*cache.lookup("alpha"), 1);
    ASSERT_NE(cache.lookup("beta"), nullptr);
    EXPECT_EQ(*cache.lookup("beta"), 2);
    ASSERT_NE(cache.lookup("gamma"), nullptr);
    EXPECT_EQ(*cache.lookup("gamma"), 3);

    EXPECT_EQ(cache.lookup("delta"), nullptr);
}

// Test eviction ordering with many insertions
TEST_F(PopplerCacheTest_254, EvictionOrderingManyInsertions_254) {
    PopplerCache<int, int> cache(3);
    for (int i = 0; i < 10; i++) {
        cache.put(i, std::make_unique<int>(i * 10));
    }

    // Only the last 3 entries should remain: 7, 8, 9
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(cache.lookup(i), nullptr) << "Key " << i << " should have been evicted";
    }
    for (int i = 7; i < 10; i++) {
        ASSERT_NE(cache.lookup(i), nullptr) << "Key " << i << " should be in cache";
        EXPECT_EQ(*cache.lookup(i), i * 10);
    }
}

// Test that putting a duplicate key adds a new entry (both may exist or old one gets pushed out)
TEST_F(PopplerCacheTest_254, PutDuplicateKey_254) {
    PopplerCache<int, std::string> cache(5);
    cache.put(1, std::make_unique<std::string>("first"));
    cache.put(1, std::make_unique<std::string>("second"));

    // Lookup should find at least one entry for key 1
    std::string *result = cache.lookup(1);
    ASSERT_NE(result, nullptr);
    // The most recent insertion should be found first (inserted at front)
    EXPECT_EQ(*result, "second");
}

// Test larger cache size
TEST_F(PopplerCacheTest_254, LargerCacheSize_254) {
    PopplerCache<int, int> cache(100);
    for (int i = 0; i < 100; i++) {
        cache.put(i, std::make_unique<int>(i));
    }

    // All 100 entries should be present
    for (int i = 0; i < 100; i++) {
        ASSERT_NE(cache.lookup(i), nullptr) << "Key " << i << " should be in cache";
        EXPECT_EQ(*cache.lookup(i), i);
    }

    // Adding one more should evict key 0 (the oldest)
    cache.put(100, std::make_unique<int>(100));
    EXPECT_EQ(cache.lookup(0), nullptr);
    ASSERT_NE(cache.lookup(100), nullptr);
    EXPECT_EQ(*cache.lookup(100), 100);
}

// Test with negative keys
TEST_F(PopplerCacheTest_254, NegativeKeys_254) {
    PopplerCache<int, int> cache(3);
    cache.put(-1, std::make_unique<int>(10));
    cache.put(-2, std::make_unique<int>(20));
    cache.put(0, std::make_unique<int>(0));

    ASSERT_NE(cache.lookup(-1), nullptr);
    EXPECT_EQ(*cache.lookup(-1), 10);
    ASSERT_NE(cache.lookup(-2), nullptr);
    EXPECT_EQ(*cache.lookup(-2), 20);
    ASSERT_NE(cache.lookup(0), nullptr);
    EXPECT_EQ(*cache.lookup(0), 0);
}

// Test that the pointer returned by lookup is valid and modifiable
TEST_F(PopplerCacheTest_254, LookupReturnsModifiablePointer_254) {
    PopplerCache<int, int> cache(5);
    cache.put(42, std::make_unique<int>(100));

    int *ptr = cache.lookup(42);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 100);

    // Modify through pointer
    *ptr = 200;

    // Lookup again should reflect the change
    int *ptr2 = cache.lookup(42);
    ASSERT_NE(ptr2, nullptr);
    EXPECT_EQ(*ptr2, 200);
}
