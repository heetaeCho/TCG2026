#include <gtest/gtest.h>

#include "db/version_set.cc"

#include "leveldb/options.h"



using namespace leveldb;



class MaxBytesForLevelTest_128 : public ::testing::Test {

protected:

    Options options;

};



TEST_F(MaxBytesForLevelTest_128, Level0Default_128) {

    int level = 0;

    double expected = 10 * 1048576.0;

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}



TEST_F(MaxBytesForLevelTest_128, Level1Default_128) {

    int level = 1;

    double expected = 10 * 1048576.0;

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}



TEST_F(MaxBytesForLevelTest_128, Level2Default_128) {

    int level = 2;

    double expected = 100 * 1048576.0;

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}



TEST_F(MaxBytesForLevelTest_128, Level3Default_128) {

    int level = 3;

    double expected = 1000 * 1048576.0;

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}



TEST_F(MaxBytesForLevelTest_128, BoundaryConditionNegativeLevel_128) {

    int level = -1;

    double expected = 10 * 1048576.0; // Should behave like level 0

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}



TEST_F(MaxBytesForLevelTest_128, BoundaryConditionLargeLevel_128) {

    int level = 10;

    double expected = 1e9 * 1048576.0; // Level 9 should be the largest calculable value

    EXPECT_EQ(MaxBytesForLevel(&options, level), expected);

}
