#include <gtest/gtest.h>

#include "db/filename.h"



class FilenameTest_334 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary.

};



TEST_F(FilenameTest_334, InfoLogFileName_NormalOperation_334) {

    std::string dbname = "testdb";

    std::string expected = "testdb/LOG";

    EXPECT_EQ(leveldb::InfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_334, InfoLogFileName_EmptyString_334) {

    std::string dbname = "";

    std::string expected = "/LOG";

    EXPECT_EQ(leveldb::InfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_334, InfoLogFileName_TrailingSlash_334) {

    std::string dbname = "testdb/";

    std::string expected = "testdb//LOG";

    EXPECT_EQ(leveldb::InfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_334, InfoLogFileName_SpacesInName_334) {

    std::string dbname = "test db";

    std::string expected = "test db/LOG";

    EXPECT_EQ(leveldb::InfoLogFileName(dbname), expected);

}
