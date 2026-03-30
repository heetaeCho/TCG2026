#include <gtest/gtest.h>

#include "db/filename.h"



class FilenameTest_335 : public ::testing::Test {};



TEST_F(FilenameTest_335, OldInfoLogFileName_ReturnsCorrectPath_335) {

    std::string dbname = "/var/log";

    std::string expected = "/var/log/LOG.old";

    EXPECT_EQ(leveldb::OldInfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_335, OldInfoLogFileName_EmptyDbName_ReturnsLOGOld_335) {

    std::string dbname = "";

    std::string expected = "/LOG.old";

    EXPECT_EQ(leveldb::OldInfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_335, OldInfoLogFileName_DbNameWithTrailingSlash_ReturnsCorrectPath_335) {

    std::string dbname = "/var/log/";

    std::string expected = "/var/log/LOG.old";

    EXPECT_EQ(leveldb::OldInfoLogFileName(dbname), expected);

}



TEST_F(FilenameTest_335, OldInfoLogFileName_DbNameWithSpaces_ReturnsCorrectPath_335) {

    std::string dbname = "my db name";

    std::string expected = "my db name/LOG.old";

    EXPECT_EQ(leveldb::OldInfoLogFileName(dbname), expected);

}
