#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/filename.cc"



namespace {



class FileNameTest_327 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(FileNameTest_327, LogFileName_ReturnsCorrectFormat_327) {

    std::string dbname = "testdb";

    uint64_t number = 1;

    EXPECT_EQ("testdb/000001.log", leveldb::LogFileName(dbname, number));

}



TEST_F(FileNameTest_327, LogFileName_BoundaryCondition_MinNumber_327) {

    std::string dbname = "testdb";

    uint64_t number = 1;

    EXPECT_EQ("testdb/000001.log", leveldb::LogFileName(dbname, number));

}



TEST_F(FileNameTest_327, LogFileName_BoundaryCondition_MaxNumber_327) {

    std::string dbname = "testdb";

    uint64_t number = 999999;

    EXPECT_EQ("testdb/099999.log", leveldb::LogFileName(dbname, number));

}



TEST_F(FileNameTest_327, LogFileName_ExceptionalCase_ZeroNumber_327) {

    std::string dbname = "testdb";

    uint64_t number = 0;

    EXPECT_DEATH(leveldb::LogFileName(dbname, number), "");

}



}  // namespace
