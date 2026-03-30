#include "gtest/gtest.h"

#include "db/repair.h"

#include "leveldb/options.h"



using namespace leveldb;



class RepairDBTest_294 : public ::testing::Test {

protected:

    std::string dbname;

    Options options;



    void SetUp() override {

        dbname = "/tmp/testdb";

        options.create_if_missing = true;

    }

};



TEST_F(RepairDBTest_294, NormalOperation_294) {

    Status status = RepairDB(dbname, options);

    EXPECT_TRUE(status.ok()) << "Expected normal operation to succeed.";

}



TEST_F(RepairDBTest_294, DatabaseAlreadyExists_ErrorIfExists_294) {

    options.error_if_exists = true;

    Status status = RepairDB(dbname, options);

    if (!status.ok()) {  // Ensure db is created first

        ASSERT_TRUE(status.IsNotFound());

        Status create_status = DB::Open(options, dbname, nullptr);

        EXPECT_TRUE(create_status.ok()) << "Failed to create database for test setup.";



        status = RepairDB(dbname, options);

        EXPECT_TRUE(status.IsIOError()) << "Expected IOError when repairing a db that already exists with error_if_exists set.";

    }

}



TEST_F(RepairDBTest_294, InvalidDatabaseName_294) {

    dbname = "";

    Status status = RepairDB(dbname, options);

    EXPECT_FALSE(status.ok()) << "Expected failure for invalid database name.";

}



TEST_F(RepairDBTest_294, NullComparator_294) {

    options.comparator = nullptr;

    Status status = RepairDB(dbname, options);

    EXPECT_TRUE(status.IsInvalidArgument()) << "Expected invalid argument error when comparator is null.";

}



TEST_F(RepairDBTest_294, NullEnv_294) {

    options.env = nullptr;

    Status status = RepairDB(dbname, options);

    EXPECT_TRUE(status.IsInvalidArgument()) << "Expected invalid argument error when env is null.";

}
