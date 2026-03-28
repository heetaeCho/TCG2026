#include <gtest/gtest.h>

#include "leveldb/options.h"



namespace leveldb {



class TargetFileSizeTest : public ::testing::Test {

protected:

    Options options;

};



TEST_F(TargetFileSizeTest_125, NormalOperation_125) {

    options.max_file_size = 4 * 1024 * 1024; // 4MB

    EXPECT_EQ(TargetFileSize(&options), 4 * 1024 * 1024);

}



TEST_F(TargetFileSizeTest_125, BoundaryCondition_ZeroMaxFileSize_125) {

    options.max_file_size = 0;

    EXPECT_EQ(TargetFileSize(&options), 0);

}



TEST_F(TargetFileSizeTest_125, BoundaryCondition_MaxValue_125) {

    options.max_file_size = std::numeric_limits<size_t>::max();

    EXPECT_EQ(TargetFileSize(&options), std::numeric_limits<size_t>::max());

}



} // namespace leveldb
