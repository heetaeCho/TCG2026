#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PopplerCache.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockItem {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



using Key = int;

using Item = MockItem;



TEST_F(PopplerCacheTest_254, PutIncreasesCountBelowCapacity_254) {

    PopplerCache<Key, Item> cache(3);

    auto item1 = std::make_unique<Item>();

    cache.put(1, std::move(item1));

    EXPECT_EQ(cache.lookup(1)->dummyMethod(), void());

}



TEST_F(PopplerCacheTest_254, PutReplacesOldestEntryWhenAtCapacity_254) {

    PopplerCache<Key, Item> cache(3);

    auto item1 = std::make_unique<Item>();

    auto item2 = std::make_unique<Item>();

    auto item3 = std::make_unique<Item>();

    auto item4 = std::make_unique<Item>();



    cache.put(1, std::move(item1));

    cache.put(2, std::move(item2));

    cache.put(3, std::move(item3));

    cache.put(4, std::move(item4));



    EXPECT_EQ(cache.lookup(1), nullptr);

    EXPECT_NE(cache.lookup(2), nullptr);

    EXPECT_NE(cache.lookup(3), nullptr);

    EXPECT_NE(cache.lookup(4), nullptr);

}



TEST_F(PopplerCacheTest_254, PutSameKeyReplacesExistingEntry_254) {

    PopplerCache<Key, Item> cache(3);

    auto item1 = std::make_unique<Item>();

    auto item2 = std::make_unique<Item>();



    cache.put(1, std::move(item1));

    cache.put(1, std::move(item2));



    EXPECT_EQ(cache.lookup(1)->dummyMethod(), void());

}



TEST_F(PopplerCacheTest_254, LookupNonExistentKeyReturnsNull_254) {

    PopplerCache<Key, Item> cache(3);

    EXPECT_EQ(cache.lookup(99), nullptr);

}



TEST_F(PopplerCacheTest_254, PutZeroCapacityDoesNotStoreEntries_254) {

    PopplerCache<Key, Item> cache(0);

    auto item1 = std::make_unique<Item>();

    cache.put(1, std::move(item1));

    EXPECT_EQ(cache.lookup(1), nullptr);

}
