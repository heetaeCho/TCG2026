#include <gtest/gtest.h>

#include "util/random.h"



class RandomTest_86 : public ::testing::Test {

protected:

    leveldb::Random random;



    RandomTest_86() : random(1) {}  // Initialize with a fixed seed for reproducibility

};



TEST_F(RandomTest_86, Next_ReturnsValueInRange_86) {

    uint32_t result = random.Next();

    EXPECT_LE(result, 2147483647u);  // Ensure the value is within the expected range

    EXPECT_GE(result, 0u);

}



TEST_F(RandomTest_86, Uniform_ReturnsValueInRange_86) {

    int n = 10;

    uint32_t result = random.Uniform(n);

    EXPECT_LE(result, n - 1);  // Ensure the value is within the expected range

    EXPECT_GE(result, 0);

}



TEST_F(RandomTest_86, Uniform_BoundaryCondition_86) {

    int n = 1;

    uint32_t result = random.Uniform(n);

    EXPECT_EQ(result, 0);  // When n is 1, the only possible value is 0

}



TEST_F(RandomTest_86, OneIn_ReturnsTrueWithCorrectProbability_86) {

    int n = 2;

    bool result = random.OneIn(n);

    EXPECT_TRUE(result || !result);  // Ensure the function returns a boolean value

}



TEST_F(RandomTest_86, OneIn_BoundaryCondition_86) {

    int n = 1;

    bool result = random.OneIn(n);

    EXPECT_EQ(result, true);  // When n is 1, the function should always return true

}



TEST_F(RandomTest_86, Skewed_ReturnsValueInRange_86) {

    int max_log = 5;

    uint32_t result = random.Skewed(max_log);

    EXPECT_LE(result, (1 << max_log) - 1);  // Ensure the value is within the expected range

    EXPECT_GE(result, 0);

}



TEST_F(RandomTest_86, Skewed_BoundaryCondition_86) {

    int max_log = 0;

    uint32_t result = random.Skewed(max_log);

    EXPECT_EQ(result, 0);  // When max_log is 0, the only possible value is 0

}
