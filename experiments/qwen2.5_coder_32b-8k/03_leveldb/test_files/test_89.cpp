#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "util/random.h"



namespace {



class RandomTest : public ::testing::Test {

protected:

    leveldb::Random random;



    RandomTest() : random(42) {}  // Using a fixed seed for reproducibility

};



TEST_F(RandomTest_89, Next_ReturnsDifferentValues_89) {

    uint32_t first = random.Next();

    uint32_t second = random.Next();

    EXPECT_NE(first, second);

}



TEST_F(RandomTest_89, Uniform_ReturnsValueWithinRange_89) {

    for (int i = 1; i <= 100; ++i) {

        uint32_t value = random.Uniform(i);

        EXPECT_GE(value, 0);

        EXPECT_LT(value, i);

    }

}



TEST_F(RandomTest_89, Uniform_ZeroRangeThrowsOrReturnsZero_89) {

    // Assuming Uniform(0) returns 0 based on common behavior

    uint32_t value = random.Uniform(0);

    EXPECT_EQ(value, 0);

}



TEST_F(RandomTest_89, OneIn_ReturnsTrueWithProbability_89) {

    int count_true = 0;

    const int trials = 10000;

    const int n = 10;



    for (int i = 0; i < trials; ++i) {

        if (random.OneIn(n)) {

            ++count_true;

        }

    }



    // Expecting approximately 1/n of the calls to return true

    EXPECT_NEAR(count_true, trials / static_cast<double>(n), trials * 0.05);

}



TEST_F(RandomTest_89, OneIn_ZeroProbabilityAlwaysTrue_89) {

    for (int i = 0; i < 100; ++i) {

        EXPECT_TRUE(random.OneIn(0));

    }

}



TEST_F(RandomTest_89, Skewed_ReturnsValueWithinSkewedRange_89) {

    const int max_log = 5;

    uint32_t max_value = (1 << max_log);



    for (int i = 0; i < 1000; ++i) {

        uint32_t value = random.Skewed(max_log);

        EXPECT_GE(value, 1);

        EXPECT_LE(value, max_value);

    }

}



}  // namespace
