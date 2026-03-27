#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "leveldb/status.h"

#include "leveldb/options.h"



using namespace leveldb;



class DBTest_318 : public ::testing::Test {

protected:

    Options options_;

    std::string dbname_ = "testdb";

    DB* db_ = nullptr;

};



TEST_F(DBTest_318, OpenNonExistentDatabaseWithoutCreateIfMissing_318) {

    Status s = DB::Open(options_, dbname_, &db_);

    EXPECT_TRUE(s.IsIOError());

}



TEST_F(DBTest_318, OpenNonExistentDatabaseWithCreateIfMissing_318) {

    options_.create_if_missing = true;

    Status s = DB::Open(options_, dbname_, &db_);

    EXPECT_OK(s);

    delete db_;

}



TEST_F(DBTest_318, ReopenExistingDatabase_318) {

    options_.create_if_missing = true;

    Status s = DB::Open(options_, dbname_, &db_);

    EXPECT_OK(s);

    delete db_;



    s = DB::Open(options_, dbname_, &db_);

    EXPECT_OK(s);

    delete db_;

}



TEST_F(DBTest_318, OpenDatabaseWithErrorIfExists_318) {

    options_.create_if_missing = true;

    Status s = DB::Open(options_, dbname_, &db_);

    EXPECT_OK(s);

    delete db_;



    options_.error_if_exists = true;

    s = DB::Open(options_, dbname_, &db_);

    EXPECT_TRUE(s.IsIOError());

}



TEST_F(DBTest_318, OpenDatabaseWithInvalidEnv_318) {

    options_.env = nullptr;

    Status s = DB::Open(options_, dbname_, &db_);

    EXPECT_TRUE(s.IsInvalidArgument());

}
