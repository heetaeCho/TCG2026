#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/cache.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockCache : public Cache {

public:

    MOCK_METHOD(void, Release, (Handle * handle), (override));

    MOCK_METHOD(Handle *, Insert, (const Slice & key, void * value, size_t charge, void (*)(const Slice &, void *) deleter), (override));

    MOCK_METHOD(Handle *, Lookup, (const Slice & key), (override));

    MOCK_METHOD(void *, Value, (Handle * handle), (override));

    MOCK_METHOD(void, Erase, (const Slice & key), (override));

    MOCK_METHOD(uint64_t, NewId, (), (override));

    MOCK_METHOD(size_t, TotalCharge, (), (override));

    MOCK_METHOD(void, Prune, (), (override));

};



class ReleaseBlockTest_422 : public ::testing::Test {

protected:

    MockCache mock_cache;

    Cache* cache_ptr = &mock_cache;

    Slice key = "test_key";

    void* value = reinterpret_cast<void*>(123);

    size_t charge = 100;

    Cache::Handle* handle;



    void SetUp() override {

        handle = mock_cache.Insert(key, value, charge, nullptr);

    }



    void TearDown() override {

        if (handle) {

            mock_cache.Release(handle);

            handle = nullptr;

        }

    }

};



TEST_F(ReleaseBlockTest_422, ReleaseCallsCacheRelease_422) {

    EXPECT_CALL(mock_cache, Release(handle)).Times(1);

    leveldb::ReleaseBlock(cache_ptr, handle);

}



TEST_F(ReleaseBlockTest_422, ReleaseWithNullHandleDoesNotCallCacheRelease_422) {

    EXPECT_CALL(mock_cache, Release(_)).Times(0);

    leveldb::ReleaseBlock(cache_ptr, nullptr);

}
