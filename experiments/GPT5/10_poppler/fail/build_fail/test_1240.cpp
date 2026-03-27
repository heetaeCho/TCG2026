#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "PopplerCache.h"

// Mock class for Item to control its behavior in tests
class MockItem : public Item {
public:
    MOCK_METHOD(void, doSomething, (), (const));
};

// Test Fixture for PopplerCache
template <typename Key, typename Item>
class PopplerCacheTest : public ::testing::Test {
protected:
    std::size_t cacheSize = 3;
    PopplerCache<Key, Item> cache{cacheSize};

    PopplerCacheTest() = default;
    ~PopplerCacheTest() override = default;
};

// Test case for normal operation: putting and looking up items
TEST_F(PopplerCacheTest<int, MockItem>, PutAndLookupNormalOperation_1240) {
    auto item = std::make_unique<MockItem>();
    EXPECT_CALL(*item, doSomething()).Times(1);
    cache.put(1, std::move(item));

    auto *retrievedItem = cache.lookup(1);
    ASSERT_NE(retrievedItem, nullptr);
    retrievedItem->doSomething();  // Verify interaction
}

// Test case for boundary condition: when cache reaches its capacity
TEST_F(PopplerCacheTest<int, MockItem>, CacheCapacity_1241) {
    auto item1 = std::make_unique<MockItem>();
    auto item2 = std::make_unique<MockItem>();
    auto item3 = std::make_unique<MockItem>();
    auto item4 = std::make_unique<MockItem>();

    EXPECT_CALL(*item1, doSomething()).Times(1);
    EXPECT_CALL(*item2, doSomething()).Times(1);
    EXPECT_CALL(*item3, doSomething()).Times(1);
    EXPECT_CALL(*item4, doSomething()).Times(1);

    cache.put(1, std::move(item1));
    cache.put(2, std::move(item2));
    cache.put(3, std::move(item3));

    // Cache is full after 3 items, the next put should evict the first item (key 1)
    cache.put(4, std::move(item4));

    // Lookup key 1 should return nullptr because it was evicted
    EXPECT_EQ(cache.lookup(1), nullptr);
    auto *retrievedItem = cache.lookup(2);
    ASSERT_NE(retrievedItem, nullptr);
    retrievedItem->doSomething();  // Verify interaction
}

// Test case for boundary condition: lookup on empty cache
TEST_F(PopplerCacheTest<int, MockItem>, LookupOnEmptyCache_1242) {
    auto *retrievedItem = cache.lookup(1);
    EXPECT_EQ(retrievedItem, nullptr);  // Cache is empty, lookup should return nullptr
}

// Test case for exceptional case: invalid key lookup
TEST_F(PopplerCacheTest<int, MockItem>, LookupInvalidKey_1243) {
    auto item = std::make_unique<MockItem>();
    EXPECT_CALL(*item, doSomething()).Times(1);
    cache.put(1, std::move(item));

    auto *retrievedItem = cache.lookup(2);  // This key is not in the cache
    EXPECT_EQ(retrievedItem, nullptr);  // Lookup should return nullptr for an invalid key
}

// Test case for cache eviction when the cache size is set to 1
TEST_F(PopplerCacheTest<int, MockItem>, CacheEviction_1244) {
    PopplerCache<int, MockItem> smallCache(1);
    auto item1 = std::make_unique<MockItem>();
    auto item2 = std::make_unique<MockItem>();

    EXPECT_CALL(*item1, doSomething()).Times(1);
    EXPECT_CALL(*item2, doSomething()).Times(1);

    smallCache.put(1, std::move(item1));
    smallCache.put(2, std::move(item2));

    // After putting the second item, the first one should be evicted
    EXPECT_EQ(smallCache.lookup(1), nullptr);
    auto *retrievedItem = smallCache.lookup(2);
    ASSERT_NE(retrievedItem, nullptr);
    retrievedItem->doSomething();  // Verify interaction
}