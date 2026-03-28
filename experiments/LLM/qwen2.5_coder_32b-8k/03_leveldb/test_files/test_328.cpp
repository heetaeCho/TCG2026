#include <gtest/gtest.h>

#include <string>

#include "db/filename.h"



class TableFileNameTest_328 : public ::testing::Test {};



TEST_F(TableFileNameTest_328, NormalOperation_328) {

    std::string dbname = "testdb";

    uint64_t number = 1;

    std::string expected = "testdb/000001.ldb";

    EXPECT_EQ(leveldb::TableFileName(dbname, number), expected);

}



TEST_F(TableFileNameTest_328, BoundaryConditionMinNumber_328) {

    std::string dbname = "testdb";

    uint64_t number = 1; // Minimum valid number as per assert

    std::string expected = "testdb/000001.ldb";

    EXPECT_EQ(leveldb::TableFileName(dbname, number), expected);

}



TEST_F(TableFileNameTest_328, LargeNumber_328) {

    std::string dbname = "testdb";

    uint64_t number = 987654321;

    std::string expected = "testdb/0987654321.ldb";

    EXPECT_EQ(leveldb::TableFileName(dbname, number), expected);

}



TEST_F(TableFileNameTest_328, ZeroNumber_ShouldAssert_328) {

    std::string dbname = "testdb";

    uint64_t number = 0;

#ifdef NDEBUG

    // If assertions are disabled, we can't test this directly.

    EXPECT_NO_THROW(leveldb::TableFileName(dbname, number));

#else

    EXPECT_DEATH(leveldb::TableFileName(dbname, number), "Assertion.*failed");

#endif

}



TEST_F(TableFileNameTest_328, EmptyDbName_328) {

    std::string dbname = "";

    uint64_t number = 1;

    std::string expected = "/000001.ldb"; // Assuming no special handling for empty dbname

    EXPECT_EQ(leveldb::TableFileName(dbname, number), expected);

}
