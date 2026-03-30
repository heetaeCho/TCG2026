#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/hash_collision_bench.cc"



// Assuming random function is part of a class or namespace for testing purposes.

class RandomFunctionTest_119 : public ::testing::Test {

protected:

    void SetUp() override {

        // Seed the random number generator if necessary

        srand(static_cast<unsigned int>(time(0)));

    }

};



TEST_F(RandomFunctionTest_119, ReturnsValueWithinRange_119) {

    int low = 5;

    int high = 10;

    int result = random(low, high);

    EXPECT_GE(result, low);

    EXPECT_LE(result, high);

}



TEST_F(RandomFunctionTest_119, BoundaryConditionLowEqualsHigh_119) {

    int low = 7;

    int high = 7;

    int result = random(low, high);

    EXPECT_EQ(result, low);

}



TEST_F(RandomFunctionTest_119, LargeRange_119) {

    int low = -1000;

    int high = 1000;

    int result = random(low, high);

    EXPECT_GE(result, low);

    EXPECT_LE(result, high);

}



TEST_F(RandomFunctionTest_119, NegativeRange_119) {

    int low = -20;

    int high = -10;

    int result = random(low, high);

    EXPECT_GE(result, low);

    EXPECT_LE(result, high);

}

```


