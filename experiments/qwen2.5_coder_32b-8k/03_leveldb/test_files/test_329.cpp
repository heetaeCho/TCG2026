#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/filename.cc"



namespace leveldb {



class SSTTableFileNameTest_329 : public ::testing::Test {

protected:

    std::string dbname = "test_db";

};



TEST_F(SSTTableFileNameTest_329, ValidNumber_ReturnsCorrectFileName_329) {

    uint64_t number = 1;

    EXPECT_EQ(SSTTableFileName(dbname, number), "test_db/000001.sst");

}



TEST_F(SSTTableFileNameTest_329, LargeNumber_ReturnsCorrectFileName_329) {

    uint64_t number = 987654321;

    EXPECT_EQ(SSTTableFileName(dbname, number), "test_db/987654321.sst");

}



TEST_F(SSTTableFileNameTest_329, BoundaryCondition_ZeroNumber_ThrowsAssertion_329) {

    uint64_t number = 0;

    EXPECT_DEATH(SSTTableFileName(dbname, number), "assertion failed");

}



} // namespace leveldb
