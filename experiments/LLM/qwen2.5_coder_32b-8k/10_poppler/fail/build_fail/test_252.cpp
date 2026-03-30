#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PopplerCache.h"

#include <memory>



// Mock Item and Key classes for testing purposes

class MockItem {};

using Key = int;



// Test fixture for PopplerCache tests

class PopplerCacheTest_252 : public ::testing::Test {

protected:

    std::size_t cacheSize = 10;

    PopplerCache<Key, MockItem> cache;



    PopplerCacheTest_252() : cache(cacheSize) {}

};



// Test normal operation of lookup

TEST_F(PopplerCacheTest_252, LookupNonExistentKey_ReturnsNullptr_252) {

    Key key = 1;

    EXPECT_EQ(cache.lookup(key), nullptr);

}



TEST_F(PopplerCacheTest_252, LookupExistingKey_ReturnsItemPointer_252) {

    Key key = 1;

    auto item = std::make_unique<MockItem>();

    cache.put(key, std::move(item));



    EXPECT_NE(cache.lookup(key), nullptr);

}



// Test boundary conditions

TEST_F(PopplerCacheTest_252, LookupKeyAfterPutting_ReturnsSamePointer_252) {

    Key key = 1;

    auto item = new MockItem();

    cache.put(key, item);



    EXPECT_EQ(cache.lookup(key), item);

}



TEST_F(PopplerCacheTest_252, LookupMostRecentlyAccessedKey_ReturnsItemPointer_252) {

    Key key1 = 1, key2 = 2;

    auto item1 = new MockItem();

    auto item2 = new MockItem();

    cache.put(key1, item1);

    cache.put(key2, item2);



    cache.lookup(key1); // Accessing key1 to make it the most recently accessed

    EXPECT_EQ(cache.lookup(key1), item1);

}



// Test exceptional or error cases (if observable through the interface)

TEST_F(PopplerCacheTest_252, PutNullPointer_ItemIsNotAdded_252) {

    Key key = 1;

    cache.put(key, static_cast<MockItem*>(nullptr));



    EXPECT_EQ(cache.lookup(key), nullptr);

}



// Test verification of external interactions

// No mocks are needed for this class based on the provided interface



```


