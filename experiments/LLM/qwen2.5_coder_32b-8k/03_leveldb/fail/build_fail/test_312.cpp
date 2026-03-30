#include <gtest/gtest.h>

#include "leveldb/db.h"

#include "leveldb/options.h"

#include "leveldb/slice.h"



namespace leveldb {



class DBImplTest : public ::testing::Test {

protected:

    Options options;

    std::string dbname = "testdb";

    DB* db;

    WriteOptions write_options;



    void SetUp() override {

        Status status = DB::Open(options, dbname, &db);

        ASSERT_TRUE(status.ok()) << "Failed to open database: " << status.ToString();

    }



    void TearDown() override {

        delete db;

    }

};



TEST_F(DBImplTest_312, DeleteNonExistentKey_ReturnsOK_312) {

    Slice key("non_existent_key");

    Status s = db->Delete(write_options, key);

    EXPECT_TRUE(s.ok());

}



TEST_F(DBImplTest_312, DeleteExistingKey_ReturnsOK_312) {

    Slice key("test_key");

    Slice value("test_value");



    // First put the key-value pair

    Status put_status = db->Put(write_options, key, value);

    EXPECT_TRUE(put_status.ok());



    // Then delete the key

    Status delete_status = db->Delete(write_options, key);

    EXPECT_TRUE(delete_status.ok());

}



TEST_F(DBImplTest_312, DeleteEmptyKey_ReturnsInvalidArgument_312) {

    Slice empty_key("");

    Status s = db->Delete(write_options, empty_key);

    EXPECT_EQ(s.code(), Status::kInvalidArgument);

}



TEST_F(DBImplTest_312, DeleteLongKey_ReturnsOK_312) {

    std::string long_key_str(1024, 'a'); // Create a 1KB key

    Slice long_key(long_key_str.c_str(), long_key_str.size());

    Slice value("test_value");



    // First put the key-value pair

    Status put_status = db->Put(write_options, long_key, value);

    EXPECT_TRUE(put_status.ok());



    // Then delete the key

    Status delete_status = db->Delete(write_options, long_key);

    EXPECT_TRUE(delete_status.ok());

}



TEST_F(DBImplTest_312, DeleteKeyAfterSyncOption_ReturnsOK_312) {

    Slice key("sync_test_key");

    Slice value("test_value");



    // Set sync option to true

    WriteOptions sync_write_options = write_options;

    sync_write_options.sync = true;



    // First put the key-value pair with sync option

    Status put_status = db->Put(sync_write_options, key, value);

    EXPECT_TRUE(put_status.ok());



    // Then delete the key with sync option

    Status delete_status = db->Delete(sync_write_options, key);

    EXPECT_TRUE(delete_status.ok());

}



}  // namespace leveldb
