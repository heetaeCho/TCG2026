#include <gtest/gtest.h>

#include "leveldb/options.h"



namespace leveldb {



class TableCacheSizeTest_299 : public ::testing::Test {

protected:

    Options options_;

};



TEST_F(TableCacheSizeTest_299, NormalOperation_299) {

    options_.max_open_files = 1010;

    EXPECT_EQ(TableCacheSize(options_), 1000);

}



TEST_F(TableCacheSizeTest_299, BoundaryConditionZeroMaxOpenFiles_299) {

    options_.max_open_files = 0;

    EXPECT_EQ(TableCacheSize(options_), -10);

}



TEST_F(TableCacheSizeTest_299, BoundaryConditionMinValueMaxOpenFiles_299) {

    options_.max_open_files = 10;

    EXPECT_EQ(TableCacheSize(options_), 0);

}



TEST_F(TableCacheSizeTest_299, BoundaryConditionLessThanNonTableCacheFiles_299) {

    options_.max_open_files = 5;

    EXPECT_EQ(TableCacheSize(options_), -5);

}



} // namespace leveldb
