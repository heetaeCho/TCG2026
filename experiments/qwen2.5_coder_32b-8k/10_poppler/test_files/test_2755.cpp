#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PopplerCache.h"



class MockItem {

public:

    virtual ~MockItem() = default;

};



using CacheType = PopplerCache<std::string, MockItem>;



class PopplerCacheTest_2755 : public ::testing::Test {

protected:

    void SetUp() override {

        cache = std::make_unique<CacheType>(cacheSize);

    }



    void TearDown() override {

        cache.reset();

    }



    static constexpr size_t cacheSize = 10;

    std::unique_ptr<CacheType> cache;

};



TEST_F(PopplerCacheTest_2755, LookupNonExistentKey_ReturnsNullptr_2755) {

    auto result = cache->lookup("nonexistent");

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerCacheTest_2755, PutAndGetItem_SameInstanceReturned_2755) {

    auto item = std::make_unique<MockItem>();

    MockItem* rawItem = item.get();

    cache->put("key1", std::move(item));

    EXPECT_EQ(cache->lookup("key1"), rawItem);

}



TEST_F(PopplerCacheTest_2755, PutMultipleItems_AllAreRetrievable_2755) {

    auto item1 = std::make_unique<MockItem>();

    auto item2 = std::make_unique<MockItem>();

    cache->put("key1", std::move(item1));

    cache->put("key2", std::move(item2));

    EXPECT_NE(cache->lookup("key1"), nullptr);

    EXPECT_NE(cache->lookup("key2"), nullptr);

}



TEST_F(PopplerCacheTest_2755, PutSameKey_ReplacesOldItem_2755) {

    auto item1 = std::make_unique<MockItem>();

    cache->put("key1", std::move(item1));

    auto firstLookup = cache->lookup("key1");



    auto item2 = std::make_unique<MockItem>();

    cache->put("key1", std::move(item2));



    EXPECT_NE(cache->lookup("key1"), nullptr);

    EXPECT_NE(cache->lookup("key1"), firstLookup);

}



TEST_F(PopplerCacheTest_2755, CacheSizeReserve_CapacityMatchesInitialSize_2755) {

    EXPECT_GE(cache->entries.capacity(), cacheSize);

}
