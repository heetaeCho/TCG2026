#include <gtest/gtest.h>

#include "leveldb/options.h"

#include "db/version_set.h"



using namespace leveldb;



class MaxGrandParentOverlapBytesTest_126 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(MaxGrandParentOverlapBytesTest_126, DefaultMaxFileSize_126) {

    int64_t expected = 10 * TargetFileSize(&options);

    EXPECT_EQ(MaxGrandParentOverlapBytes(&options), expected);

}



TEST_F(MaxGrandParentOverlapBytesTest_126, CustomMaxFileSize_126) {

    options.max_file_size = 5 * 1024 * 1024;

    int64_t expected = 10 * TargetFileSize(&options);

    EXPECT_EQ(MaxGrandParentOverlapBytes(&options), expected);

}



TEST_F(MaxGrandParentOverlapBytesTest_126, ZeroMaxFileSize_126) {

    options.max_file_size = 0;

    int64_t expected = 10 * TargetFileSize(&options);

    EXPECT_EQ(MaxGrandParentOverlapBytes(&options), expected);

}
