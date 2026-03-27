#include <gtest/gtest.h>

#include "leveldb/options.h"

#include "db/version_set.cc"



namespace leveldb {



class MaxFileSizeForLevelTest_129 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(MaxFileSizeForLevelTest_129, DefaultMaxFileSize_129) {

    int level = 0; // Assuming any level should return the default max_file_size

    uint64_t expected_max_file_size = options.max_file_size;

    EXPECT_EQ(MaxFileSizeForLevel(&options, level), expected_max_file_size);

}



TEST_F(MaxFileSizeForLevelTest_129, LevelBoundaryCheck_129) {

    int level = 0; // Assuming any level should return the default max_file_size

    uint64_t expected_max_file_size = options.max_file_size;

    EXPECT_EQ(MaxFileSizeForLevel(&options, level), expected_max_file_size);



    level = 999; // Testing with a large level number

    EXPECT_EQ(MaxFileSizeForLevel(&options, level), expected_max_file_size);

}



TEST_F(MaxFileSizeForLevelTest_129, CustomMaxFileSize_129) {

    options.max_file_size = 4 * 1024 * 1024; // Setting a custom max_file_size

    int level = 0; // Assuming any level should return the default max_file_size

    uint64_t expected_max_file_size = options.max_file_size;

    EXPECT_EQ(MaxFileSizeForLevel(&options, level), expected_max_file_size);

}



} // namespace leveldb
