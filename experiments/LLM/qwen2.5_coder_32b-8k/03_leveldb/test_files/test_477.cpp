#include <gtest/gtest.h>

#include "util/random.h"



using namespace leveldb;



class RandomTest_477 : public ::testing::Test {

protected:

    Random random;

    

    RandomTest_477() : random(1) {}  // Initialize with a seed of 1 for consistency

};



TEST_F(RandomTest_477, Next_ReturnsValidValue_477) {

    uint32_t result = random.Next();

    EXPECT_GE(result, 0);

    EXPECT_LE(result, 0x7fffffffu);

}



TEST_F(RandomTest_477, Uniform_BoundaryConditions_477) {

    EXPECT_EQ(random.Uniform(1), 0);  // n = 1 should always return 0

    EXPECT_LE(random.Uniform(2), 1);  // n = 2 should return either 0 or 1

}



TEST_F(RandomTest_477, Uniform_ExceptionalCases_477) {

    EXPECT_THROW(random.Uniform(0), std::invalid_argument);  // n = 0 should throw an exception

}



TEST_F(RandomTest_477, OneIn_NormalOperation_477) {

    bool result = random.OneIn(1);

    EXPECT_TRUE(result);  // OneIn(1) should always return true



    int count_true = 0;

    const int trials = 10000;

    for (int i = 0; i < trials; ++i) {

        if (random.OneIn(2)) ++count_true;

    }

    EXPECT_GE(count_true, trials / 3);  // Expect about half true, but with some margin

    EXPECT_LE(count_true, 2 * trials / 3);

}



TEST_F(RandomTest_477, OneIn_BoundaryConditions_477) {

    EXPECT_TRUE(random.OneIn(1));  // n = 1 should always return true

    EXPECT_FALSE(random.OneIn(std::numeric_limits<int>::max()));  // n very large should rarely return true

}



TEST_F(RandomTest_477, OneIn_ExceptionalCases_477) {

    EXPECT_THROW(random.OneIn(0), std::invalid_argument);  // n = 0 should throw an exception

}



TEST_F(RandomTest_477, Skewed_NormalOperation_477) {

    uint32_t result = random.Skewed(1);

    EXPECT_GE(result, 0);

    EXPECT_LE(result, (1 << 1) - 1);



    result = random.Skewed(10);

    EXPECT_GE(result, 0);

    EXPECT_LE(result, (1 << 10) - 1);

}



TEST_F(RandomTest_477, Skewed_BoundaryConditions_477) {

    EXPECT_EQ(random.Skewed(0), 0);  // max_log = 0 should always return 0

}
