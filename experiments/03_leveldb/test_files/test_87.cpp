#include <gtest/gtest.h>

#include "util/random.h"



using namespace leveldb;



class RandomTest_87 : public ::testing::Test {

protected:

    Random random_;



    RandomTest_87() : random_(12345) {}

};



TEST_F(RandomTest_87, UniformBasic_87) {

    // Test that the return value of Uniform is within the expected range [0, n).

    int n = 10;

    for (int i = 0; i < 1000; ++i) {

        uint32_t result = random_.Uniform(n);

        EXPECT_GE(result, 0);

        EXPECT_LT(result, n);

    }

}



TEST_F(RandomTest_87, UniformBoundary_87) {

    // Test boundary condition where n is 1.

    int n = 1;

    for (int i = 0; i < 100; ++i) {

        uint32_t result = random_.Uniform(n);

        EXPECT_EQ(result, 0);

    }

}



TEST_F(RandomTest_87, UniformZeroN_87) {

    // Test edge case where n is 0. This should not happen as per the function signature,

    // but we can still check for potential undefined behavior or crashes.

    int n = 0;

    EXPECT_THROW(random_.Uniform(n), std::exception);

}



TEST_F(RandomTest_87, OneInBasic_87) {

    // Test that OneIn returns true approximately 1/n of the time.

    int n = 10;

    int count_true = 0;

    for (int i = 0; i < 1000; ++i) {

        if (random_.OneIn(n)) {

            count_true++;

        }

    }

    EXPECT_NEAR(count_true, 100, 30); // Allow some deviation due to randomness

}



TEST_F(RandomTest_87, OneInBoundary_87) {

    // Test boundary condition where n is 1. OneIn(1) should always return true.

    int n = 1;

    for (int i = 0; i < 100; ++i) {

        EXPECT_TRUE(random_.OneIn(n));

    }

}



TEST_F(RandomTest_87, OneInZeroN_87) {

    // Test edge case where n is 0. This should not happen as per the function signature,

    // but we can still check for potential undefined behavior or crashes.

    int n = 0;

    EXPECT_THROW(random_.OneIn(n), std::exception);

}
