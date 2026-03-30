#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/cache.h"

#include "db/table_cache.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class CacheMock : public Cache {

public:

    MOCK_METHOD(void, Release, (Handle* handle), (override));

    MOCK_METHOD(Handle*, Insert, (const Slice& key, void* value, size_t charge, void (*deleter)(const Slice&, void*)), (override));

    MOCK_METHOD(Handle*, Lookup, (const Slice& key), (override));

    MOCK_METHOD(void*, Value, (Handle* handle), (override));

    MOCK_METHOD(void, Erase, (const Slice& key), (override));

    MOCK_METHOD(uint64_t, NewId, (), (override));

    MOCK_METHOD(size_t, TotalCharge, (), (override));

    MOCK_METHOD(void, Prune, (), (override));

};



class CacheTest_348 : public ::testing::Test {

protected:

    void SetUp() override {

        cache = new CacheMock();

    }



    void TearDown() override {

        delete cache;

    }



    Cache* cache;

};



TEST_F(CacheTest_348, InsertAndLookup_NormalOperation_348) {

    Slice key("test_key");

    void* value = reinterpret_cast<void*>(123);

    size_t charge = 10;



    EXPECT_CALL(*cache, Insert(key, value, charge, _))

        .WillOnce(Return(reinterpret_cast<Cache::Handle*>(1)));



    Cache::Handle* handle = cache->Insert(key, value, charge, nullptr);



    EXPECT_CALL(*cache, Lookup(key))

        .WillOnce(Return(handle));



    EXPECT_EQ(cache->Lookup(key), handle);

}



TEST_F(CacheTest_348, InsertAndRelease_NormalOperation_348) {

    Slice key("test_key");

    void* value = reinterpret_cast<void*>(123);

    size_t charge = 10;



    EXPECT_CALL(*cache, Insert(key, value, charge, _))

        .WillOnce(Return(reinterpret_cast<Cache::Handle*>(1)));



    Cache::Handle* handle = cache->Insert(key, value, charge, nullptr);



    EXPECT_CALL(*cache, Release(handle));



    cache->Release(handle);

}



TEST_F(CacheTest_348, InsertAndValue_NormalOperation_348) {

    Slice key("test_key");

    void* value = reinterpret_cast<void*>(123);

    size_t charge = 10;



    EXPECT_CALL(*cache, Insert(key, value, charge, _))

        .WillOnce(Return(reinterpret_cast<Cache::Handle*>(1)));



    Cache::Handle* handle = cache->Insert(key, value, charge, nullptr);



    EXPECT_CALL(*cache, Value(handle))

        .WillOnce(Return(value));



    EXPECT_EQ(cache->Value(handle), value);

}



TEST_F(CacheTest_348, Erase_NormalOperation_348) {

    Slice key("test_key");



    EXPECT_CALL(*cache, Erase(key));



    cache->Erase(key);

}



TEST_F(CacheTest_348, NewId_NormalOperation_348) {

    EXPECT_CALL(*cache, NewId())

        .WillOnce(Return(1));



    EXPECT_EQ(cache->NewId(), 1);

}



TEST_F(CacheTest_348, TotalCharge_NormalOperation_348) {

    EXPECT_CALL(*cache, TotalCharge())

        .WillOnce(Return(100));



    EXPECT_EQ(cache->TotalCharge(), 100);

}



TEST_F(CacheTest_348, Prune_NormalOperation_348) {

    EXPECT_CALL(*cache, Prune());



    cache->Prune();

}
