#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "leveldb/write_batch.h"



using namespace leveldb;

using testing::_;

using testing::Eq;



class DBTest_316 : public ::testing::Test {

protected:

    Options options;

    DB* db = nullptr;

    WriteOptions write_options;



    virtual void SetUp() {

        Status status = DB::Open(options, "/tmp/testdb", &db);

        ASSERT_TRUE(status.ok()) << "Unable to open/create test database";

    }



    virtual void TearDown() {

        delete db;

    }

};



TEST_F(DBTest_316, PutNormalOperation_316) {

    Slice key("testkey");

    Slice value("testvalue");



    Status status = db->Put(write_options, key, value);

    EXPECT_TRUE(status.ok());

}



TEST_F(DBTest_316, PutEmptyKey_316) {

    Slice empty_key("");

    Slice value("testvalue");



    Status status = db->Put(write_options, empty_key, value);

    EXPECT_TRUE(status.IsInvalidArgument()) << "Inserting an empty key should return an invalid argument error";

}



TEST_F(DBTest_316, PutEmptyValue_316) {

    Slice key("testkey");

    Slice empty_value("");



    Status status = db->Put(write_options, key, empty_value);

    EXPECT_TRUE(status.ok()) << "Inserting a key with an empty value should succeed";

}



TEST_F(DBTest_316, PutLargeKeyAndValue_316) {

    std::string large_key(1024 * 1024, 'a'); // 1MB key

    std::string large_value(1024 * 1024, 'b'); // 1MB value



    Slice key(large_key);

    Slice value(large_value);



    Status status = db->Put(write_options, key, value);

    EXPECT_TRUE(status.ok()) << "Inserting a large key and value should succeed";

}



TEST_F(DBTest_316, PutSyncOptionTrue_316) {

    write_options.sync = true;

    Slice key("testkey");

    Slice value("testvalue");



    Status status = db->Put(write_options, key, value);

    EXPECT_TRUE(status.ok()) << "Inserting with sync option set to true should succeed";

}
