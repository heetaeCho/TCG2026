#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "leveldb/write_batch.h"



using namespace leveldb;



class DBTest_317 : public ::testing::Test {

protected:

    DB* db_;

    Options options_;

    WriteOptions write_options_;

    Slice key_;

    Status status_;



    void SetUp() override {

        status_ = DB::Open(options_, "/tmp/testdb", &db_);

        ASSERT_TRUE(status_.ok()) << "Failed to open database: " << status_.ToString();

        key_ = Slice("test_key");

    }



    void TearDown() override {

        delete db_;

    }

};



TEST_F(DBTest_317, DeleteExistingKey_317) {

    // Arrange

    Status put_status = db_->Put(write_options_, key_, Slice("value"));

    ASSERT_TRUE(put_status.ok()) << "Failed to put key: " << put_status.ToString();



    // Act

    status_ = db_->Delete(write_options_, key_);



    // Assert

    EXPECT_TRUE(status_.ok());

}



TEST_F(DBTest_317, DeleteNonExistingKey_317) {

    // Arrange & Act

    status_ = db_->Delete(write_options_, key_);



    // Assert

    EXPECT_TRUE(status_.IsNotFound()) << "Expected not found error, got: " << status_.ToString();

}



TEST_F(DBTest_317, DeleteWithSyncOption_317) {

    // Arrange

    WriteOptions sync_opt;

    sync_opt.sync = true;



    Status put_status = db_->Put(sync_opt, key_, Slice("value"));

    ASSERT_TRUE(put_status.ok()) << "Failed to put key: " << put_status.ToString();



    // Act

    status_ = db_->Delete(sync_opt, key_);



    // Assert

    EXPECT_TRUE(status_.ok());

}



TEST_F(DBTest_317, DeleteEmptyKey_317) {

    // Arrange & Act

    Slice empty_key;

    status_ = db_->Delete(write_options_, empty_key);



    // Assert

    EXPECT_TRUE(status_.IsInvalidArgument()) << "Expected invalid argument error, got: " << status_.ToString();

}



TEST_F(DBTest_317, DeleteNullKey_317) {

    // Arrange & Act

    Slice null_key(nullptr, 0);

    status_ = db_->Delete(write_options_, null_key);



    // Assert

    EXPECT_TRUE(status_.IsInvalidArgument()) << "Expected invalid argument error, got: " << status_.ToString();

}
