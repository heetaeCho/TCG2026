#include <gtest/gtest.h>

#include "db/db_impl.h"

#include "leveldb/status.h"

#include "leveldb/write_batch.h"



namespace leveldb {



class DBImplTest_311 : public ::testing::Test {

protected:

    DBImpl* db_;

    WriteOptions write_options_;



    void SetUp() override {

        Options options;

        Status status = DB::Open(options, "/tmp/testdb", &db_);

        ASSERT_TRUE(status.ok()) << "Failed to open database";

    }



    void TearDown() override {

        delete db_;

    }

};



TEST_F(DBImplTest_311, PutNormalOperation_311) {

    Slice key("key1");

    Slice value("value1");

    Status status = db_->Put(write_options_, key, value);

    EXPECT_TRUE(status.ok()) << "Put operation failed unexpectedly";

}



TEST_F(DBImplTest_311, PutEmptyKey_311) {

    Slice empty_key("");

    Slice value("value1");

    Status status = db_->Put(write_options_, empty_key, value);

    EXPECT_TRUE(status.ok() || status.IsInvalidArgument()) << "Put operation with empty key failed unexpectedly";

}



TEST_F(DBImplTest_311, PutEmptyValue_311) {

    Slice key("key1");

    Slice empty_value("");

    Status status = db_->Put(write_options_, key, empty_value);

    EXPECT_TRUE(status.ok()) << "Put operation with empty value failed unexpectedly";

}



TEST_F(DBImplTest_311, PutLargeKey_311) {

    std::string large_key(1024 * 1024, 'a'); // 1MB key

    Slice key(large_key);

    Slice value("value1");

    Status status = db_->Put(write_options_, key, value);

    EXPECT_TRUE(status.ok()) << "Put operation with large key failed unexpectedly";

}



TEST_F(DBImplTest_311, PutLargeValue_311) {

    Slice key("key1");

    std::string large_value(1024 * 1024, 'a'); // 1MB value

    Slice value(large_value);

    Status status = db_->Put(write_options_, key, value);

    EXPECT_TRUE(status.ok()) << "Put operation with large value failed unexpectedly";

}



TEST_F(DBImplTest_311, PutSameKeyMultipleTimes_311) {

    Slice key("key1");

    Slice value1("value1");

    Slice value2("value2");



    Status status = db_->Put(write_options_, key, value1);

    EXPECT_TRUE(status.ok()) << "First put operation failed unexpectedly";



    status = db_->Put(write_options_, key, value2);

    EXPECT_TRUE(status.ok()) << "Second put operation with same key failed unexpectedly";

}



TEST_F(DBImplTest_311, PutWithSyncOption_311) {

    write_options_.sync = true;

    Slice key("key1");

    Slice value("value1");

    Status status = db_->Put(write_options_, key, value);

    EXPECT_TRUE(status.ok()) << "Put operation with sync option failed unexpectedly";

}



} // namespace leveldb
