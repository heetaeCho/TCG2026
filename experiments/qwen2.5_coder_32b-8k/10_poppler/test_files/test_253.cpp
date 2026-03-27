#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PopplerCache.h"



using namespace testing;



class PopplerCacheTest_253 : public Test {

protected:

    using Key = std::string;

    using Item = int;

    const size_t cacheSize = 5;

    PopplerCache<Key, Item> cache{cacheSize};



    std::unique_ptr<Item> createItem(int value) {

        return std::make_unique<Item>(value);

    }

};



TEST_F(PopplerCacheTest_253, PutSingleEntry_253) {

    auto item = createItem(1);

    cache.put("key1", std::move(item));

}



TEST_F(PopplerCacheTest_253, PutMultipleEntriesWithinCapacity_253) {

    for (size_t i = 0; i < cacheSize; ++i) {

        auto item = createItem(i);

        cache.put("key" + std::to_string(i), std::move(item));

    }

}



TEST_F(PopplerCacheTest_253, PutEntriesExceedingCapacity_253) {

    for (size_t i = 0; i < cacheSize * 2; ++i) {

        auto item = createItem(i);

        cache.put("key" + std::to_string(i), std::move(item));

    }

}



TEST_F(PopplerCacheTest_253, PutSameKeyMultipleTimes_253) {

    for (size_t i = 0; i < cacheSize; ++i) {

        auto item = createItem(i);

        cache.put("key1", std::move(item));

    }

}



TEST_F(PopplerCacheTest_253, PutNullPointer_253) {

    cache.put("key1", static_cast<Item*>(nullptr));

}
