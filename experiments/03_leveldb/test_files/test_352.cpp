#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/table_cache.h"

#include "leveldb/cache.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



class MockCache : public Cache {

public:

    MOCK_METHOD1(Erase, void(const Slice& key));

};



class TableCacheTest_352 : public ::testing::Test {

protected:

    Options options_;

    std::string dbname_ = "test_db";

    int entries_ = 10;

    MockCache* mock_cache_;

    TableCache* table_cache_;



    TableCacheTest_352() {

        mock_cache_ = new MockCache();

        table_cache_ = new TableCache(dbname_, options_, entries_);

        table_cache_->cache_ = mock_cache_;

    }



    ~TableCacheTest_352() override {

        delete table_cache_;

        delete mock_cache_;

    }

};



TEST_F(TableCacheTest_352, EvictCallsEraseOnCache_352) {

    uint64_t file_number = 123;

    char buf[sizeof(file_number)];

    EncodeFixed64(buf, file_number);

    Slice key(buf, sizeof(buf));



    EXPECT_CALL(*mock_cache_, Erase(key)).Times(1);



    table_cache_->Evict(file_number);

}



TEST_F(TableCacheTest_352, EvictWithZeroFileNumber_352) {

    uint64_t file_number = 0;

    char buf[sizeof(file_number)];

    EncodeFixed64(buf, file_number);

    Slice key(buf, sizeof(buf));



    EXPECT_CALL(*mock_cache_, Erase(key)).Times(1);



    table_cache_->Evict(file_number);

}



TEST_F(TableCacheTest_352, EvictWithMaxFileNumber_352) {

    uint64_t file_number = UINT64_MAX;

    char buf[sizeof(file_number)];

    EncodeFixed64(buf, file_number);

    Slice key(buf, sizeof(buf));



    EXPECT_CALL(*mock_cache_, Erase(key)).Times(1);



    table_cache_->Evict(file_number);

}
