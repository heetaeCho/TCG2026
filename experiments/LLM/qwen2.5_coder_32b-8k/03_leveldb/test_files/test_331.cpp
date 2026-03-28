#include <gtest/gtest.h>

#include <string>

#include "db/filename.h"



class CurrentFileNameTest_331 : public ::testing::Test {

protected:

    std::string dbname;

    

    void SetUp() override {

        dbname = "test_db";

    }

};



TEST_F(CurrentFileNameTest_331, NormalOperation_331) {

    EXPECT_EQ(leveldb::CurrentFileName(dbname), "test_db/CURRENT");

}



TEST_F(CurrentFileNameTest_331, EmptyDbName_331) {

    dbname = "";

    EXPECT_EQ(leveldb::CurrentFileName(dbname), "/CURRENT");

}



TEST_F(CurrentFileNameTest_331, DbNameWithTrailingSlash_331) {

    dbname = "test_db/";

    EXPECT_EQ(leveldb::CurrentFileName(dbname), "test_db//CURRENT");

}
