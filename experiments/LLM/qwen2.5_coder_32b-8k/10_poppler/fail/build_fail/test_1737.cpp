#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/CairoOutputDev.h"



using namespace testing;



// Test fixture for StructParentsMcidHash

class StructParentsMcidHashTest_1737 : public ::testing::Test {

protected:

    CairoOutputDev::StructParentsMcidHash hashFunction;

};



// Test normal operation with typical values

TEST_F(StructParentsMcidHashTest_1737, HashNormalValues_1737) {

    std::pair<int, int> pair = {123, 456};

    size_t expectedHash = (123 << 16) | 456;

    EXPECT_EQ(hashFunction(pair), expectedHash);

}



// Test boundary conditions with minimum values

TEST_F(StructParentsMcidHashTest_1737, HashMinValues_1737) {

    std::pair<int, int> pair = {0, 0};

    size_t expectedHash = 0;

    EXPECT_EQ(hashFunction(pair), expectedHash);

}



// Test boundary conditions with maximum values

TEST_F(StructParentsMcidHashTest_1737, HashMaxValues_1737) {

    std::pair<int, int> pair = {0xFFFF, 0xFFFF};

    size_t expectedHash = (0xFFFF << 16) | 0xFFFF;

    EXPECT_EQ(hashFunction(pair), expectedHash);

}



// Test boundary conditions with maximum value for first element and zero for second

TEST_F(StructParentsMcidHashTest_1737, HashMaxFirstZeroSecond_1737) {

    std::pair<int, int> pair = {0xFFFF, 0};

    size_t expectedHash = (0xFFFF << 16);

    EXPECT_EQ(hashFunction(pair), expectedHash);

}



// Test boundary conditions with zero for first element and maximum value for second

TEST_F(StructParentsMcidHashTest_1737, HashZeroFirstMaxSecond_1737) {

    std::pair<int, int> pair = {0, 0xFFFF};

    size_t expectedHash = 0xFFFF;

    EXPECT_EQ(hashFunction(pair), expectedHash);

}



// Test boundary conditions with negative values

TEST_F(StructParentsMcidHashTest_1737, HashNegativeValues_1737) {

    std::pair<int, int> pair = {-1, -1};

    size_t expectedHash = ((-1) << 16) | (-1);

    EXPECT_EQ(hashFunction(pair), expectedHash);

}
